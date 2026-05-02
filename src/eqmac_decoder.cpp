// EQMac OldStream inbound decoder. See eqmac_decoder.h for design notes
// and wire-format reference.

#include "eqmac_decoder.h"
#include "diagnosticmessages.h"

#include <cstring>
#include <zlib.h>

namespace {

inline uint16_t readBE16(const uint8_t* p) {
  return (uint16_t(p[0]) << 8) | p[1];
}

// Field sizes used by DecodePacket. The trailing 4 bytes are a CRC32 the
// real client/server validate; EQMacEmu's DecodePacket also doesn't check it
// (eq_packet.cpp:633 "TODO: Do we want to check crc checksum on the incoming
// packets?") — we just strip them off the end the same way.
constexpr size_t kCrcTrailerLen = 4;

// ---------------------------------------------------------------------------
// EQ Mac payload obfuscation. Three forms exist in
// EQMacEmu/common/packet_functions.cpp; all use fixed constants (no session
// key). For OP_ZoneSpawns and OP_NewSpawn the encoder pipes data through
// DeflatePacket -> EncryptZoneSpawnPacket. For OP_PlayerProfile it's
// DeflatePacket -> EncryptProfilePacket. We invert each in place.

constexpr uint16_t kAppOpZoneSpawns    = 0x5f41;
constexpr uint16_t kAppOpNewSpawn      = 0x6b42;
constexpr uint16_t kAppOpPlayerProfile = 0x3640;

inline uint64_t rol64(uint64_t x, unsigned n) {
  return (x << n) | (x >> (64 - n));
}
inline uint64_t ror64(uint64_t x, unsigned n) {
  return (x >> n) | (x << (64 - n));
}

// Inverse of EncryptZoneSpawnPacket. Operates in place on the int64-aligned
// prefix; trailing bytes (size & 7) pass through verbatim, matching the
// encoder.
void decryptZoneSpawn(uint8_t* buf, size_t size) {
  const size_t n = size >> 3;
  if (n == 0) return;
  uint64_t* data = reinterpret_cast<uint64_t*>(buf);
  uint64_t crypt = 0;
  for (size_t i = 0; i < n; ++i) {
    uint64_t e = data[i];
    e = e + crypt;
    e = ror64(e, 14);
    e = e - 0x659365E7ULL;
    e = ror64(e, 29);
    const uint64_t p = e;
    data[i] = p;
    crypt = crypt + p - 0x659365E7ULL;
  }
  // Final unswap: encoder swapped data[0] and data[n/2] *before* rotating.
  if (n >= 2) {
    const size_t m = n / 2;
    const uint64_t tmp = data[0];
    data[0] = data[m];
    data[m] = tmp;
  }
}

// Inverse of EncryptProfilePacket.
void decryptProfile(uint8_t* buf, size_t size) {
  const size_t n = size >> 3;
  if (n == 0) return;
  uint64_t* data = reinterpret_cast<uint64_t*>(buf);
  uint64_t crypt = 0x659365E7ULL;  // initial value (different from zone-spawn)
  for (size_t i = 0; i < n; ++i) {
    uint64_t e = data[i];
    e = e + crypt;
    e = ror64(e, 7);
    e = e - 0x422437A9ULL;
    // Forward used `(data[i]>>0x19) | (data[i]<<0x27)` which is ROR by 25.
    // Inverse is ROL by 25.
    e = rol64(e, 25);
    const uint64_t p = e;
    data[i] = p;
    crypt = crypt + p - 0x422437A9ULL;
  }
  if (n >= 2) {
    const size_t m = n / 2;
    const uint64_t tmp = data[0];
    data[0] = data[m];
    data[m] = tmp;
  }
}

// Inflate a zlib-deflated buffer into `out`. Returns inflated size or 0 on
// failure. Caller sizes `out` generously — Mac payloads cap around 90 KB
// (msg_eq_netplayerbuff uses an 89,600-byte static buffer).
size_t inflateBuffer(const uint8_t* in, size_t inLen, uint8_t* out, size_t outCap) {
  z_stream zs{};
  zs.next_in = const_cast<Bytef*>(in);
  zs.avail_in = uInt(inLen);
  zs.next_out = out;
  zs.avail_out = uInt(outCap);
  if (inflateInit2(&zs, 15) != Z_OK) return 0;
  const int rv = inflate(&zs, Z_FINISH);
  const size_t total = zs.total_out;
  inflateEnd(&zs);
  if (rv != Z_STREAM_END) {
    seqDebug("EQMacDecoder: inflate failed (rv=%d, in=%zu, out=%zu)", rv, inLen, total);
    return 0;
  }
  return total;
}

constexpr size_t kInflateOutCap = 96 * 1024;  // headroom over the 89,600 client buf

} // namespace

EQMacDecoder::EQMacDecoder() = default;

void EQMacDecoder::reset() {
  m_fragments.clear();
  m_lastArq = -1;
}

// Wrapper that intercepts the obfuscated+compressed app opcodes and emits
// the decoded plaintext payload to the underlying callback. Other opcodes
// pass through unchanged.
namespace {
void emitWithDecode(uint16_t opcode, const uint8_t* data, size_t len,
                     const EQMacDecoder::AppPacketCallback& cb) {
  if (opcode == kAppOpZoneSpawns || opcode == kAppOpNewSpawn ||
      opcode == kAppOpPlayerProfile) {
    if (len == 0) { cb(opcode, data, len); return; }
    // Decrypt in a writable scratch buffer.
    static thread_local std::vector<uint8_t> scratch;
    scratch.assign(data, data + len);
    if (opcode == kAppOpPlayerProfile) {
      decryptProfile(scratch.data(), scratch.size());
    } else {
      decryptZoneSpawn(scratch.data(), scratch.size());
    }
    // Inflate.
    static thread_local std::vector<uint8_t> inflated;
    if (inflated.size() < kInflateOutCap) inflated.resize(kInflateOutCap);
    const size_t outLen =
        inflateBuffer(scratch.data(), scratch.size(),
                      inflated.data(), inflated.size());
    if (outLen == 0) {
      seqDebug("EQMacDecoder: decrypt/inflate produced 0 bytes for op 0x%04x (in=%zu)",
               opcode, len);
      return;
    }
    cb(opcode, inflated.data(), outLen);
    return;
  }
  cb(opcode, data, len);
}
} // namespace

void EQMacDecoder::process(const uint8_t* buf, size_t len,
                            const AppPacketCallback& cb) {
  // Minimum legal EQOldPacket is 10 bytes (HDR + SEQ + at least 6 trailing).
  // Mirrors eq_packet.cpp:630.
  if (len < 10) return;

  // ---- HDR_INFO (2 bytes, LSB-first bit-fields) ----
  const uint8_t a = buf[0];
  const uint8_t b = buf[1];
  const bool a1_ARQ      = (a >> 1) & 1;
  const bool a2_Closing  = (a >> 2) & 1;
  const bool a3_Fragment = (a >> 3) & 1;
  const bool a4_ASQ      = (a >> 4) & 1;
  const bool a6_Closing  = (a >> 6) & 1;
  const bool b2_ARSP     = (b >> 2) & 1;
  const bool b3_Unknown  = (b >> 3) & 1;
  const uint8_t b4_size  =
      ((b >> 4) & 1) |
      (((b >> 5) & 1) << 1) |
      (((b >> 6) & 1) << 2) |
      (((b >> 7) & 1) << 3);

  size_t off = 4;  // past HDR (2) + dwSEQ (2)

  // ---- dwARSP (b2_ARSP) ----
  if (b2_ARSP) {
    if (off + 2 > len) return;
    off += 2;
  }

  // ---- b3ARSP (b3_Unknown) ----
  if (b3_Unknown) {
    if (off + 2 > len) return;
    off += 2;
  }

  // ---- ack_fields (b4..b7 encode the size in bytes) ----
  if (b4_size > 0) {
    if (off + b4_size > len) return;
    off += b4_size;
  }

  // ---- dwARQ (a1_ARQ) ----
  uint16_t dwARQ = 0;
  bool haveARQ = false;
  if (a1_ARQ) {
    if (off + 2 > len) return;
    dwARQ = readBE16(buf + off);
    haveARQ = true;
    off += 2;
  }

  // Drop retransmits. EQOldStream re-sends the same application message
  // (same dwARQ, fresh dwSEQ) until ack'd; without this the daemon
  // dispatches each retransmit as a fresh app-packet, which manifests
  // as e.g. OP_ZoneChange firing every ~450ms forever after a real zone
  // transition. Strictly-monotonic check via signed 16-bit difference
  // tolerates the natural 0xFFFF→0x0000 wrap (delta becomes a small
  // positive after wrap, not a huge negative). On stream restart
  // m_lastArq resets to -1, so the first ARQ packet always passes.
  if (haveARQ) {
    if (m_lastArq < 0) {
      m_lastArq = dwARQ;
    } else {
      const int16_t delta =
          static_cast<int16_t>(dwARQ - static_cast<uint16_t>(m_lastArq));
      if (delta <= 0) {
        // Already seen this ARQ (or older). Drop the retransmit.
        return;
      }
      m_lastArq = dwARQ;
    }
  }

  // ---- fraginfo (a3_Fragment) ----
  uint16_t fragSeq = 0;
  uint16_t fragCurr = 0;
  uint16_t fragTotal = 0;
  if (a3_Fragment) {
    if (off + 6 > len) return;
    fragSeq   = readBE16(buf + off);
    fragCurr  = readBE16(buf + off + 2);
    fragTotal = readBE16(buf + off + 4);
    off += 6;
  }

  // ---- ASQ (a4_ASQ, possibly combined with a1_ARQ for 2 bytes) ----
  if (a4_ASQ && a1_ARQ) {
    if (off + 2 > len) return;
    off += 2;
  } else if (a4_ASQ) {
    if (off + 1 > len) return;
    off += 1;
  }

  // ---- Closing-pair → no opcode/payload ----
  if (a2_Closing && a6_Closing) return;

  // ---- Need room for opcode (2) + at-least-empty-payload (0) + CRC (4).
  // Mirror DecodePacket's "if(length-size > 4 && !closing)" guard at
  // eq_packet.cpp:719.
  if (len <= off + kCrcTrailerLen) return;

  // ---- dwOpCode (only on the first fragment, or non-fragment packet) ----
  uint16_t opcode = 0;
  if (fragCurr == 0) {
    if (off + 2 > len) return;
    opcode = readBE16(buf + off);
    off += 2;
  }

  // ---- payload length: trim 4-byte CRC trailer (DecodePacket does the same).
  if (len < off + kCrcTrailerLen) return;
  const size_t extraSize = len - off - kCrcTrailerLen;
  const uint8_t* payload = buf + off;

  if (a3_Fragment) {
    if (fragTotal == 0) return;  // malformed
    auto& fg = m_fragments[fragSeq];
    if (fragCurr == 0) {
      // First fragment; (re)initialize the group.
      fg.opcode = opcode;
      fg.total = fragTotal;
      fg.received_count = 0;
      fg.received.assign(fragTotal, false);
      fg.data.clear();
    }
    if (fragCurr >= fg.received.size()) {
      // Fragment count grew past initial total — drop the group.
      m_fragments.erase(fragSeq);
      return;
    }
    if (fg.received[fragCurr]) {
      // Duplicate fragment; ignore.
      return;
    }
    fg.received[fragCurr] = true;
    fg.received_count++;
    // Append in arrival order. Out-of-order arrival will scramble the body
    // — acceptable for v1 since EQMacEmu's ARQ buffering keeps fragments
    // in-order in practice. If we need strict ordering later we can index
    // by fragCurr into a pre-sized buffer.
    fg.data.insert(fg.data.end(), payload, payload + extraSize);

    if (fg.received_count == fg.total) {
      emitWithDecode(fg.opcode, fg.data.data(), fg.data.size(), cb);
      m_fragments.erase(fragSeq);
    }
    return;
  }

  // ---- Single-packet app message ----
  if (opcode != 0) {
    emitWithDecode(opcode, payload, extraSize, cb);
  }
}
