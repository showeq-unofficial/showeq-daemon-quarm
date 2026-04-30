/*
 * checkpoint.h — small JSON snapshot of slow-moving daemon state.
 *
 * Persists the player identity (name, level, class, ...) and current
 * zone short/long name across daemon restarts, so the web UI doesn't
 * spend the first ~60s of a fresh daemon process showing "unknown"
 * while it waits for the next periodic OP_PlayerProfile.
 *
 * Volatile state — the spawn list, buffs, group roster — is
 * deliberately NOT persisted; it would be wrong far more often than
 * it would be useful. Those refill from the wire as packets arrive.
 */

#pragma once

#include <QString>
#include <QtGlobal>
#include <cstdint>
#include <optional>

class QFileInfo;

struct CheckpointData
{
    qint64   written_at_unix = 0;

    // Player identity.
    uint16_t player_id       = 0;
    QString  player_name;
    QString  player_last_name;
    uint8_t  player_class    = 0;
    uint8_t  player_level    = 0;
    uint16_t player_race     = 0;
    uint16_t player_deity    = 0;
    uint8_t  player_gender   = 0;
    uint32_t current_exp     = 0;
    uint32_t max_exp         = 0;
    uint32_t current_alt_exp = 0;
    uint16_t current_aa_pts  = 0;

    // Zone identity.
    QString  short_zone_name;
    QString  long_zone_name;
};

namespace Checkpoint
{

bool save(const QFileInfo& info, CheckpointData data);

// Returns nullopt if the file is missing, malformed, has a mismatched
// schema version, or was written longer than `max_age_seconds` ago.
std::optional<CheckpointData> load(const QFileInfo& info,
                                   qint64 max_age_seconds);

} // namespace Checkpoint
