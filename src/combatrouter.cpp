#include "combatrouter.h"

#include "everquest.h"
#include "spawn.h"
#include "spawnshell.h"
#include "spells.h"

CombatRouter::CombatRouter(SpawnShell* spawnShell, Spells* spells,
                           QObject* parent)
    : QObject(parent)
    , m_spawnShell(spawnShell)
    , m_spells(spells)
{
}

// Returns the human-readable form of a spawn's name. For NPCs that's
// the cleanedName (drops the trailing instance digits and unescapes
// underscores into spaces — "a_pyre_beetle25" → "a pyre beetle"); for
// PCs it's the name verbatim. We deliberately skip the article-move
// done by transformedName() ("a pyre beetle" → "pyre beetle, a") since
// combat log lines read more naturally with the article in front.
static QString lookupSpawnName(SpawnShell* shell, uint16_t id)
{
    if (!shell || id == 0) return QString();
    const Item* it = shell->findID(tSpawn, id);
    if (!it) it = shell->findID(tPlayer, id);
    if (!it) return QString();
    if (const Spawn* sp = dynamic_cast<const Spawn*>(it)) {
        return sp->cleanedName();
    }
    return it->name();
}

static QString lookupSpellName(Spells* spells, uint16_t spellId)
{
    if (!spells || spellId == 0 || spellId == 0xffff) return QString();
    if (const Spell* s = spells->spell(spellId)) return s->name();
    return QString();
}

void CombatRouter::action(const uint8_t* data, size_t len, uint8_t /*dir*/)
{
    if (!data || len < sizeof(actionStruct)) return;
    const auto* a = reinterpret_cast<const actionStruct*>(data);

    const uint16_t spellId = a->spell;
    const QString sourceName = lookupSpawnName(m_spawnShell, a->source);
    const QString targetName = lookupSpawnName(m_spawnShell, a->target);
    const QString spellName  = lookupSpellName(m_spells, spellId);

    // OP_Action announces the cast — no damage value attached. The
    // matching OP_Damage carries the int32 damage amount.
    emit combatEvent(a->source, sourceName,
                     a->target, targetName,
                     static_cast<uint32_t>(a->type),
                     0,
                     static_cast<uint32_t>(spellId),
                     spellName);
}

void CombatRouter::damage(const uint8_t* data, size_t len, uint8_t /*dir*/)
{
    if (!data || len < sizeof(damageStruct)) return;
    const auto* d = reinterpret_cast<const damageStruct*>(data);

    const uint16_t spellId = d->spellid;
    const QString sourceName = lookupSpawnName(m_spawnShell, d->source);
    const QString targetName = lookupSpawnName(m_spawnShell, d->target);
    const QString spellName  = lookupSpellName(m_spells, spellId);

    emit combatEvent(d->source, sourceName,
                     d->target, targetName,
                     static_cast<uint32_t>(d->type),
                     d->damage,
                     static_cast<uint32_t>(spellId),
                     spellName);
}
