/*
 *  zonemgr.h
 *  Copyright 2001,2007 Zaphod (dohpaz@users.sourceforge.net). All Rights Reserved.
 *  Copyright 2002-2012, 2012-2019 by the respective ShowEQ Developers
 *  Portions Copyright 2003 Fee (fee@users.sourceforge.net)
 *
 *  Contributed to ShowEQ by Zaphod (dohpaz@users.sourceforge.net)
 *  for use under the terms of the GNU General Public License,
 *  incorporated herein by reference.
 *
 *  This file is part of ShowEQ.
 *  http://www.sourceforge.net/projects/seq
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "zonemgr.h"
#include "packet.h"
#include "main.h"
#include "everquest.h"
#include "diagnosticmessages.h"
#include "netstream.h"

#include <QFile>
#include <QDataStream>
#include <QRegularExpression>

//----------------------------------------------------------------------
// constants
static const char magicStr[5] = "zon2"; // magic is the size of uint32_t + a null
static const uint32_t* magic = (uint32_t*)magicStr;
const float defaultZoneExperienceMultiplier = 0.75;

// Sequence of signals on initial entry into eq from character select screen
// EQPacket                              ZoneMgr                       isZoning
// ----------                            -------                       --------
// zoneEntry(ClientZoneEntryStruct)      zoneBegin()                   true
// PlayerProfile(charProfileStruct)      zoneBegin(shortName)          false
// zoneNew(newZoneStruct)                zoneEnd(shortName, longName)  false
//
// Sequence of signals on when zoning from zone A to zone B
// EQPacket                              ZoneMgr                       isZoning
// ----------                            -------                       --------
// zoneChange(zoneChangeStruct, client)                                true
// zoneChange(zoneChangeStruct, server)  zoneChanged(shortName)        true
// zoneEntry(ClientZoneEntryStruct)      zoneBegin()                   false
// PlayerProfile(charProfileStruct)      zoneBegin(shortName)          false
// zoneNew(newZoneStruct)                zoneEnd(shortName, longName)  false
//
ZoneMgr::ZoneMgr(QObject* parent, const char* name)
  : QObject(parent),
    m_zoning(false),
    m_zone_exp_multiplier(defaultZoneExperienceMultiplier),
    m_zonePointCount(0),
    m_zonePoints(0)
{
  setObjectName(name);
  m_shortZoneName = "unknown";
  m_longZoneName = "unknown";
  m_zoning = false;

  if (showeq_params->restoreZoneState)
    restoreZoneState();
}

ZoneMgr::~ZoneMgr()
{
  if (m_zonePoints)
    delete [] m_zonePoints;
}

struct ZoneNames
{
  const char* shortName;
  const char* longName;
};

static const ZoneNames zoneNames[] =
{
#include "zones.h"
};

QString ZoneMgr::zoneNameFromID(uint16_t zoneId)
{
   const char* zoneName = NULL;
   if ((zoneId & 0x0fff) < (sizeof(zoneNames) / sizeof(ZoneNames)))
       zoneName = zoneNames[zoneId & 0x0fff].shortName;

   if (zoneName != NULL)
      return zoneName;

   seqDebug("ZoneMgr::zoneNameFromID: zone name not found: zoneId=%d", zoneId);
   QString tmpStr;
   tmpStr = QString::asprintf("unk_zone_%d", zoneId);
   return tmpStr;
}

QString ZoneMgr::zoneLongNameFromID(uint16_t zoneId)
{
   const char* zoneName = NULL;
   if ((zoneId & 0x0fff) < (sizeof(zoneNames) / sizeof(ZoneNames)))
       zoneName = zoneNames[zoneId & 0x0fff].longName;

   if (zoneName != NULL)
      return zoneName;

   seqDebug("ZoneMgr::zoneLongNameFromID: zone name not found: zoneId=%d", zoneId);
   QString tmpStr;
   tmpStr = QString::asprintf("unk_zone_%d", zoneId);
   return tmpStr;
}

const zonePointStruct* ZoneMgr::zonePoint(uint32_t zoneTrigger)
{
  if (!m_zonePoints)
    return 0;

  for (size_t i = 0; i < m_zonePointCount; i++)
    if (m_zonePoints[i].zoneTrigger == zoneTrigger)
      return &m_zonePoints[i];

  return 0;
}

void ZoneMgr::saveZoneState(void)
{
  QFile keyFile(showeq_params->saveRestoreBaseFilename + "Zone.dat");
  if (keyFile.open(QIODevice::WriteOnly))
  {
    QDataStream d(&keyFile);
    // write the magic string
    d << *magic;

    d << m_longZoneName;
    d << m_shortZoneName;
  }
}

void ZoneMgr::restoreZoneState(void)
{
  QString fileName = showeq_params->saveRestoreBaseFilename + "Zone.dat";
  QFile keyFile(fileName);
  if (keyFile.open(QIODevice::ReadOnly))
  {
    QDataStream d(&keyFile);

    // check the magic string
    uint32_t magicTest;
    d >> magicTest;

    if (magicTest != *magic)
    {
      seqWarn("Failure loading %s: Bad magic string!",
              fileName.toLatin1().data());
      return;
    }

    d >> m_longZoneName;
    d >> m_shortZoneName;

    seqInfo("Restored Zone: %s (%s)!",
            m_shortZoneName.toLatin1().data(),
            m_longZoneName.toLatin1().data());
  }
  else
  {
    seqWarn("Failure loading %s: Unable to open!",
            fileName.toLatin1().data());
  }
}

void ZoneMgr::zoneEntryClient(const uint8_t* data, size_t len, uint8_t dir)
{
  const ClientZoneEntryStruct* zsentry = (const ClientZoneEntryStruct*)data;

  m_shortZoneName = "unknown";
  m_longZoneName = "unknown";
  m_zone_exp_multiplier = defaultZoneExperienceMultiplier;
  m_zoning = false;

  emit zoneBegin();
  emit zoneBegin(zsentry, len, dir);

  if (showeq_params->saveZoneState)
    saveZoneState();
}

int32_t ZoneMgr::fillProfileStruct(charProfileStruct *player, const uint8_t *data, size_t len, bool checkLen)
{
  // EQ Mac OP_PlayerProfile after eqmac_decoder's decrypt+inflate is the
  // 8460-byte fixed Mac PlayerProfile_Struct. Direct memcpy.
  if (len < sizeof(charProfileStruct)) {
    if (checkLen) {
      seqDebug("ZoneMgr::fillProfileStruct: short read len=%zu < %zu",
               len, sizeof(charProfileStruct));
    }
    return 0;
  }
  memcpy(player, data, sizeof(charProfileStruct));
  return static_cast<int32_t>(sizeof(charProfileStruct));
}



void ZoneMgr::zonePlayer(const uint8_t* data, size_t len)
{
  charProfileStruct *player = new charProfileStruct;

  memset(player,0,sizeof(charProfileStruct));

  fillProfileStruct(player,data,len,false); // don't bother checking the length since it's always going to not match up

  const QString newShortName = zoneNameFromID(player->zoneId);
  const bool zoneChanged = (newShortName != m_shortZoneName) || m_zoning;

  m_shortZoneName = newShortName;
  m_longZoneName = zoneLongNameFromID(player->zoneId);
  m_zone_exp_multiplier = defaultZoneExperienceMultiplier;
  m_zoning = false;

  // EQ Mac/Quarm resends OP_PlayerProfile periodically (stat sync) without
  // a real zone transition. Only re-emit zoneBegin when the zone actually
  // changed or we were mid-zone, otherwise downstream slots like
  // loadZoneMap reload the SOE map every refresh.
  if (zoneChanged)
    emit zoneBegin(m_shortZoneName);
  emit playerProfile(player);

  if (showeq_params->saveZoneState)
    saveZoneState();
}

void ZoneMgr::zoneChange(const uint8_t* data, size_t len, uint8_t dir)
{
  const zoneChangeStruct* zoneChange = (const zoneChangeStruct*)data;
  m_shortZoneName = zoneNameFromID(zoneChange->zoneId);
  m_longZoneName = zoneLongNameFromID(zoneChange->zoneId);
  m_zone_exp_multiplier = defaultZoneExperienceMultiplier;
  m_zoning = true;

  if (dir == DIR_Server)
    emit zoneChanged(m_shortZoneName);
    emit zoneChanged(zoneChange, len, dir);

  if (showeq_params->saveZoneState)
    saveZoneState();
}

void ZoneMgr::zoneNew(const uint8_t* data, size_t len, uint8_t dir)
{
  newZoneStruct *zoneNew = new newZoneStruct;
  memset (zoneNew, 0, sizeof (newZoneStruct));
  NetStream netStream (data, len);

  QString shortName = netStream.readText ();
  if (shortName.length ())
    strcpy (zoneNew->shortName, shortName.toLatin1().data());

  QString longName = netStream.readText ();
  if (longName.length ())
    strcpy (zoneNew->longName, longName.toLatin1().data());

  netStream.skipBytes (2);

  QString zonefile = netStream.readText ();
  if (zonefile.length ())
    strcpy (zoneNew->zonefile, zonefile.toLatin1().data());

  netStream.skipBytes (90);

  union { uint32_t n; float f; } x;
  x.n = netStream.readUInt32NC();
  zoneNew->zone_exp_multiplier = x.f;

  netStream.skipBytes (28);

  x.n = netStream.readUInt32NC();
  zoneNew->safe_y = x.f;
  x.n = netStream.readUInt32NC();
  zoneNew->safe_x = x.f;
  x.n = netStream.readUInt32NC();
  zoneNew->safe_z = x.f;

  m_safePoint.setPoint(lrintf(zoneNew->safe_x), lrintf(zoneNew->safe_y),
		       lrintf(zoneNew->safe_z));
  m_zone_exp_multiplier = zoneNew->zone_exp_multiplier;

  // ZBNOTE: Apparently these come in with the localized names, which means we 
  //         may not wish to use them for zone short names.  
  //         An example of this is: shortZoneName 'ecommons' in German comes 
  //         in as 'OGemeinl'.  OK, now that we have figured out the zone id
  //         issue, we'll only use this short zone name if there isn't one or
  //         it is an unknown zone.
  if (m_shortZoneName.isEmpty() || m_shortZoneName.startsWith("unk"))
  {
    m_shortZoneName = zoneNew->shortName;

    // LDoN likes to append a _262 to the zonename. Get rid of it.
    QRegularExpression rx("_\\d+$");
    m_shortZoneName.replace( rx, "");

    // 2020-01-20 patch seems to have added _progress suffix to certain
    // zone names, presumably for the progression servers. This happens in
    // ToV DZs for sure, but there may be others.
    QRegularExpression rz("_progress$");
    m_shortZoneName.replace(rz, "");

    // some zones are getting a suffix of _int (particularly guild halls)
    // which causes failure to load maps.
    QRegularExpression ry("_int$");
    m_shortZoneName.replace(ry, "");

    //anniversary missions
    QRegularExpression rw("_errand$");
    m_shortZoneName.replace(rw, "");
  }

  m_longZoneName = zoneNew->longName;
  m_zoning = false;

#if 1 // ZBTEMP
  seqDebug("Welcome to lovely downtown '%s' with an experience multiplier of %f",
	 zoneNew->longName, zoneNew->zone_exp_multiplier);
  seqDebug("Safe Point (%f, %f, %f)", 
	 zoneNew->safe_x, zoneNew->safe_y, zoneNew->safe_z);
#endif // ZBTEMP
  
//   seqDebug("zoneNew: m_short(%s) m_long(%s)",
//      (const char*)m_shortZoneName,
//      (const char*)m_longZoneName);
  
  emit zoneEnd(m_shortZoneName, m_longZoneName);

  if (showeq_params->saveZoneState)
    saveZoneState();

  delete zoneNew;
}


