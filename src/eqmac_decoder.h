// EQMac (Quarm / EQ Mac OldStream) inbound protocol decoder.
//
// Ported from EQMacEmu/common/eq_packet.cpp::EQOldPacket::DecodePacket and
// EQMacEmu/common/eq_stream.cpp::EQOldStream::ProcessPacket, scoped to the
// inbound (sniff) path. EQ Mac uses the 2001-era OldStream framing — NOT
// the post-2005 SEQ EQProtocolPacket layout that the parent showeq-daemon
// targets. Wire shape, all multi-byte fields BE:
//
//   [2-byte HDR_INFO bit-flags]
//   [2-byte dwSEQ]
//   [2-byte dwARSP            if HDR.b2_ARSP]
//   [2-byte b3ARSP            if HDR.b3_Unknown]
//   [b4_size bytes ack_fields if (HDR.b4..b7) != 0]
//   [2-byte dwARQ             if HDR.a1_ARQ]
//   [6-byte fraginfo          if HDR.a3_Fragment]
//   [2-byte dbASQ             if HDR.a4_ASQ && HDR.a1_ARQ
//    1-byte dbASQ_high        else if HDR.a4_ASQ]
//   [2-byte dwOpCode          if not closing and not mid-fragment]
//   [variable payload]
//   [4-byte CRC32 trailer]
//
// HDR bit fields are LSB-first within each byte (gcc default on x86 LE),
// matching EQMacEmu's struct EQPACKET_HDR_INFO. Authoritative opcode names
// and IDs live in EQMacEmu/utils/patches/patch_Mac.conf — NOT opcodes.conf
// which is the generic EQEmu file.

#ifndef EQMAC_DECODER_H
#define EQMAC_DECODER_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

class EQMacDecoder
{
public:
  // Per-decoded-app-packet callback. opcode is in EQMac canonical form
  // (the 16-bit value from patch_Mac.conf — same byte order as
  // ntohs(*(uint16*)wire)). data points into a transient buffer owned by
  // the decoder; copy it if you need to retain it past the callback.
  using AppPacketCallback =
    std::function<void(uint16_t opcode, const uint8_t* data, size_t len)>;

  EQMacDecoder();

  // Feed one UDP payload (everything after the IP+UDP headers). Triggers
  // zero or more cb invocations as the wrapper layers unfold.
  void process(const uint8_t* buffer, size_t length, const AppPacketCallback& cb);

  // Drop session/fragment state, e.g. on stream restart.
  void reset();

  // Diagnostics — stub for compatibility with the prior decoder API.
  bool sessionEstablished() const { return false; }
  uint32_t sessionKey() const { return 0; }

private:
  // In-flight cross-packet fragment assembly, keyed by fraginfo.dwSeq.
  struct FragmentGroup
  {
    uint16_t opcode = 0;
    uint16_t total = 0;
    uint16_t received_count = 0;
    std::vector<bool> received;        // size == total once initialized
    std::vector<uint8_t> data;         // body, appended in fragCurr order
  };

  std::unordered_map<uint16_t, FragmentGroup> m_fragments;
};

#endif // EQMAC_DECODER_H
