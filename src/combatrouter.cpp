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

