#pragma once

#include <QObject>
#include <QString>
#include <cstdint>
#include <cstddef>

class SpawnShell;
class Spells;

// Routes EQ Mac OP_Action (spell-cast announcement) and OP_Damage
// (actual damage event) into structured combatEvent signals consumed
// by SessionAdapter and forwarded to the web client. Sits at the
// daemon level (one instance), so the spawn-id → name and
// spell-id → spell-name lookups happen once per packet rather than
// once per connected client.
class CombatRouter : public QObject {
    Q_OBJECT
public:
    CombatRouter(SpawnShell* spawnShell, Spells* spells,
                 QObject* parent = nullptr);

public slots:
    // Wired to OP_Action by DaemonApp. Mac actionStruct (36 bytes) — the
    // cast/animation announcement. damage is always 0; spellId may be set.
    void action(const uint8_t* data, size_t len, uint8_t dir);

    // Wired to OP_Damage by DaemonApp. Mac damageStruct (24 bytes) — the
    // actual damage delivery (or heal, signalled by negative `damage`).
    void damage(const uint8_t* data, size_t len, uint8_t dir);

signals:
    void combatEvent(uint32_t sourceId, const QString& sourceName,
                     uint32_t targetId, const QString& targetName,
                     uint32_t type, int32_t damage,
                     uint32_t spellId, const QString& spellName);

private:
    SpawnShell* m_spawnShell;
    Spells*     m_spells;
};
