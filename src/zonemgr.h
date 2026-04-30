/*
 *  zonemgr.h
 *  Copyright 2001 Zaphod (dohpaz@users.sourceforge.net). All Rights Reserved.
 *  Copyright 2002-2012, 2019 by the respective ShowEQ Developers
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

#ifndef ZONEMGR_H
#define ZONEMGR_H

#include <QObject>
#include <QString>

#include "point.h"

//----------------------------------------------------------------------
// forward declarations
struct ClientZoneEntryStruct;
struct ServerZoneEntryStruct;
struct charProfileStruct;
struct zoneChangeStruct;
struct newZoneStruct;
struct zonePointStruct;

class ZoneMgr : public QObject
{
  Q_OBJECT

 public:
  ZoneMgr(QObject* parent = 0, const char* name =0);
  virtual ~ZoneMgr();

  QString zoneNameFromID(uint16_t zoneId);
  QString zoneLongNameFromID(uint16_t zoneId);
  bool isZoning() const { return m_zoning; }
  const QString& shortZoneName() const { return m_shortZoneName; }
  const QString& longZoneName() const { return m_longZoneName; }
  const Point3D<int16_t>& safePoint() const { return m_safePoint; }
  float zoneExpMultiplier() { return m_zone_exp_multiplier; }
  const zonePointStruct* zonePoint(uint32_t zoneTrigger);

 public slots:
  void saveZoneState(void);
  void restoreZoneState(void);

  // Seed the zone identity from a Checkpoint. Emits zoneBegin so
  // downstream slots (loadZoneMap, filterMgr->loadZone) wire up the
  // map + filter for the restored zone immediately, instead of
  // waiting for the next OP_PlayerProfile or zoneChange to arrive.
  void applyCheckpoint(const QString& shortName, const QString& longName);

 protected slots:
  void zoneEntryClient(const uint8_t* zsentry, size_t, uint8_t);
  void zonePlayer(const uint8_t* zsentry, size_t len);
  void zoneChange(const uint8_t* zoneChange, size_t, uint8_t);
  void zoneNew(const uint8_t* zoneNew, size_t, uint8_t);
  int32_t fillProfileStruct(charProfileStruct *player, const uint8_t *data, size_t len, bool checkLen);

 signals:
  void zoneBegin();
  void zoneBegin(const QString& shortZoneName);
  void zoneBegin(const ClientZoneEntryStruct* zsentry, size_t len, uint8_t dir);
  void playerProfile(const charProfileStruct* player);
  void zoneChanged(const QString& shortZoneName);
  void zoneChanged(const zoneChangeStruct*, size_t, uint8_t);
  void zoneEnd(const QString& shortZoneName, const QString& longZoneName);
  
 private:
  QString m_longZoneName;
  QString m_shortZoneName;
  bool m_zoning;
  Point3D<int16_t>  m_safePoint;
  float m_zone_exp_multiplier;
  size_t m_zonePointCount;
  zonePointStruct* m_zonePoints;
};

#endif // ZONEMGR
