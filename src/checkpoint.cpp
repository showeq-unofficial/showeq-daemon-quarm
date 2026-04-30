#include "checkpoint.h"

#include "diagnosticmessages.h"

#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

namespace {
constexpr int kSchemaVersion = 1;
}

bool Checkpoint::save(const QFileInfo& info, CheckpointData data)
{
    data.written_at_unix = QDateTime::currentSecsSinceEpoch();

    QJsonObject root;
    root["version"]          = kSchemaVersion;
    root["written_at_unix"]  = static_cast<qint64>(data.written_at_unix);
    root["player_id"]        = data.player_id;
    root["player_name"]      = data.player_name;
    root["player_last_name"] = data.player_last_name;
    root["player_class"]     = data.player_class;
    root["player_level"]     = data.player_level;
    root["player_race"]      = data.player_race;
    root["player_deity"]     = data.player_deity;
    root["player_gender"]    = data.player_gender;
    root["current_exp"]      = static_cast<qint64>(data.current_exp);
    root["max_exp"]          = static_cast<qint64>(data.max_exp);
    root["current_alt_exp"]  = static_cast<qint64>(data.current_alt_exp);
    root["current_aa_pts"]   = data.current_aa_pts;
    root["short_zone_name"]  = data.short_zone_name;
    root["long_zone_name"]   = data.long_zone_name;

    QFile f(info.absoluteFilePath());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        seqWarn("Checkpoint::save: cannot open '%s' for writing",
                info.absoluteFilePath().toLatin1().data());
        return false;
    }
    const auto bytes = QJsonDocument(root).toJson(QJsonDocument::Indented);
    if (f.write(bytes) != bytes.size()) {
        seqWarn("Checkpoint::save: short write to '%s'",
                info.absoluteFilePath().toLatin1().data());
        return false;
    }
    return true;
}

std::optional<CheckpointData> Checkpoint::load(const QFileInfo& info,
                                               qint64 max_age_seconds)
{
    if (!info.exists()) return std::nullopt;

    const qint64 now   = QDateTime::currentSecsSinceEpoch();
    const qint64 mtime = info.lastModified().toSecsSinceEpoch();
    if (max_age_seconds > 0 && (now - mtime) > max_age_seconds) {
        seqInfo("Checkpoint at '%s' is %lld s old (>%lld); skipping restore",
                info.absoluteFilePath().toLatin1().data(),
                static_cast<long long>(now - mtime),
                static_cast<long long>(max_age_seconds));
        return std::nullopt;
    }

    QFile f(info.absoluteFilePath());
    if (!f.open(QIODevice::ReadOnly)) {
        seqWarn("Checkpoint::load: cannot open '%s'",
                info.absoluteFilePath().toLatin1().data());
        return std::nullopt;
    }

    QJsonParseError err;
    const auto doc = QJsonDocument::fromJson(f.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        seqWarn("Checkpoint::load: parse error in '%s': %s",
                info.absoluteFilePath().toLatin1().data(),
                err.errorString().toLatin1().data());
        return std::nullopt;
    }

    const auto root = doc.object();
    if (root["version"].toInt() != kSchemaVersion) {
        seqInfo("Checkpoint at '%s' has schema version %d (want %d); skipping",
                info.absoluteFilePath().toLatin1().data(),
                root["version"].toInt(), kSchemaVersion);
        return std::nullopt;
    }

    CheckpointData out;
    out.written_at_unix  = root["written_at_unix"].toVariant().toLongLong();
    out.player_id        = static_cast<uint16_t>(root["player_id"].toInt());
    out.player_name      = root["player_name"].toString();
    out.player_last_name = root["player_last_name"].toString();
    out.player_class     = static_cast<uint8_t>(root["player_class"].toInt());
    out.player_level     = static_cast<uint8_t>(root["player_level"].toInt());
    out.player_race      = static_cast<uint16_t>(root["player_race"].toInt());
    out.player_deity     = static_cast<uint16_t>(root["player_deity"].toInt());
    out.player_gender    = static_cast<uint8_t>(root["player_gender"].toInt());
    out.current_exp      = static_cast<uint32_t>(root["current_exp"].toVariant().toULongLong());
    out.max_exp          = static_cast<uint32_t>(root["max_exp"].toVariant().toULongLong());
    out.current_alt_exp  = static_cast<uint32_t>(root["current_alt_exp"].toVariant().toULongLong());
    out.current_aa_pts   = static_cast<uint16_t>(root["current_aa_pts"].toInt());
    out.short_zone_name  = root["short_zone_name"].toString();
    out.long_zone_name   = root["long_zone_name"].toString();
    return out;
}
