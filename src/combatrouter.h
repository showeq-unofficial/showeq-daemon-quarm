#pragma once

#include <QObject>
#include <QString>
#include <cstdint>
#include <cstddef>

class SpawnShell;
class Spells;

// Combat event emitter for the websocket layer. Originally fed by
// OP_Action2 (post-EQMac). On EQ Mac the equivalent signal would come
// from OP_Action (different struct shape), which has not been re-wired
// yet — the class is kept as a dormant signal source so SessionAdapter
// stays compilable. No slot is currently registered; combatEvent never
// fires until a Mac-shaped action parser lands.
class CombatRouter : public QObject {
    Q_OBJECT
public:
    CombatRouter(SpawnShell* spawnShell, Spells* spells,
                 QObject* parent = nullptr);

signals:
    void combatEvent(uint32_t sourceId, const QString& sourceName,
                     uint32_t targetId, const QString& targetName,
                     uint32_t type, int32_t damage,
                     uint32_t spellId, const QString& spellName);

private:
    SpawnShell* m_spawnShell;
    Spells*     m_spells;
};
