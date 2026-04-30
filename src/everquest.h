/*
 *  everquest.h
 *  Copyright 2001-2019 by the respective ShowEQ Developers
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


/*
** Please be kind and remember to correctly re-order
** the values in here whenever you add a new item,
** thanks.  - Andon
*/

/*
** Structures used in the network layer of Everquest
*/

#ifndef EQSTRUCT_H
#define EQSTRUCT_H

#include "config.h"

#ifdef __FreeBSD__
#include <sys/types.h>
#else
#include <cstdint>
#endif

/*
** ShowEQ specific definitions
*/
// Statistical list defines
#define LIST_HP                         0
#define LIST_MANA                       1
#define LIST_STAM                       2
#define LIST_EXP                        3
#define LIST_FOOD                       4
#define LIST_WATR                       5
#define LIST_STR                        6
#define LIST_STA                        7
#define LIST_CHA                        8
#define LIST_DEX                        9
#define LIST_INT                        10
#define LIST_AGI                        11
#define LIST_WIS                        12
#define LIST_MR                         13
#define LIST_FR                         14
#define LIST_CR                         15
#define LIST_DR                         16
#define LIST_PR                         17
#define LIST_AC                         18
#define LIST_ALTEXP                     19
#define LIST_MAXLIST                    20 

/*
** MOB Spawn Type
*/
#define SPAWN_PLAYER                    0
#define SPAWN_NPC                       1
#define SPAWN_PC_CORPSE                 2
#define SPAWN_NPC_CORPSE                3
#define SPAWN_NPC_UNKNOWN               4
#define SPAWN_DROP                      6
#define SPAWN_DOOR                      7
#define SPAWN_SELF                      10

/* 
** Diety List
*/
#define DEITY_UNKNOWN                   0
#define DEITY_AGNOSTIC			396
#define DEITY_BRELL			202
#define DEITY_CAZIC			203
#define DEITY_EROL			204
#define DEITY_BRISTLE			205
#define DEITY_INNY			206
#define DEITY_KARANA			207
#define DEITY_MITH			208
#define DEITY_PREXUS			209
#define DEITY_QUELLIOUS			210
#define DEITY_RALLOS			211
#define DEITY_SOLUSEK			213
#define DEITY_TRIBUNAL			214
#define DEITY_TUNARE			215
#define DEITY_BERT			201	
#define DEITY_RODCET			212
#define DEITY_VEESHAN			216

//Team numbers for Deity teams
#define DTEAM_GOOD			1
#define DTEAM_NEUTRAL			2
#define DTEAM_EVIL			3
#define DTEAM_OTHER			5

//Team numbers for Race teams
#define RTEAM_HUMAN			1
#define RTEAM_ELF			2
#define RTEAM_DARK			3
#define RTEAM_SHORT			4
#define RTEAM_OTHER			5

//Maximum limits of certain types of data
#define MAX_KNOWN_SKILLS                100
#define MAX_SPELL_SLOTS                 16
#define MAX_KNOWN_LANGS                 32
#define MAX_SPELLBOOK_SLOTS             800
#define MAX_GROUP_MEMBERS               6
#define MAX_BUFFS                       42
#define MAX_GUILDS                      32768
#define MAX_AA                          300
#define MAX_BANDOLIERS                  20
#define MAX_POTIONS_IN_BELT             5
#define MAX_TRIBUTES                    5
#define MAX_DISCIPLINES                 300

//Item Flags
#define ITEM_NORMAL                     0x0000
#define ITEM_NORMAL1                    0x0031
#define ITEM_NORMAL2                    0x0036
#define ITEM_NORMAL3                    0x315f
#define ITEM_NORMAL4                    0x3336
#define ITEM_NORMAL5                    0x0032
#define ITEM_NORMAL6                    0x0033
#define ITEM_NORMAL7                    0x0034
#define ITEM_NORMAL8                    0x0039
#define ITEM_CONTAINER                  0x7900
#define ITEM_CONTAINER_PLAIN            0x7953
#define ITEM_BOOK                       0x7379
#define ITEM_VERSION                    0xFFFF

// Item spellId no spell value
#define ITEM_SPELLID_NOSPELL            0xffff

// Item Field Count
#define ITEM_FIELD_SEPERATOR_COUNT      117
#define ITEM_CMN_FIELD_SEPERATOR_COUNT  102

//Combat Flags
#define COMBAT_MISS					0
#define COMBAT_BLOCK					-1
#define COMBAT_PARRY					-2
#define COMBAT_RIPOSTE					-3
#define COMBAT_DODGE					-4

#define PLAYER_CLASSES     16
#define PLAYER_RACES       15

#define MAX_PLAYER_LEVEL    130

/*
** Item Packet Type
*/
enum ItemPacketType
{
  ItemPacketViewLink		= 0x00,
  ItemPacketMerchant		= 0x64,
  ItemPacketLoot		= 0x66,
  ItemPacketTrade		= 0x67,
  ItemPacketSummonItem		= 0x6a,
  ItemPacketWorldContainer      = 0x6b
};

/*
** Item types
*/
enum ItemType
{
  ItemTypeCommon	= 0,
  ItemTypeContainer	= 1,
  ItemTypeBook		= 2
};

/*
** Chat Colors
*/
enum ChatColor
{
  CC_Default               = 0,
  CC_DarkGrey              = 1,
  CC_DarkGreen             = 2,
  CC_DarkBlue              = 3,
  CC_Purple                = 5,
  CC_LightGrey             = 6,
  CC_User_Say              = 256,
  CC_User_Tell             = 257,
  CC_User_Group            = 258,
  CC_User_Guild            = 259,
  CC_User_OOC              = 260,
  CC_User_Auction          = 261,
  CC_User_Shout            = 262,
  CC_User_Emote            = 263,
  CC_User_Spells           = 264,
  CC_User_YouHitOther      = 265,
  CC_User_OtherHitYou      = 266,
  CC_User_YouMissOther     = 267,
  CC_User_OtherMissYou     = 268,
  CC_User_Duels            = 269,
  CC_User_Skills           = 270,
  CC_User_Disciplines      = 271,
  CC_User_Default          = 273,
  CC_User_MerchantOffer    = 275,
  CC_User_MerchantExchange = 276,
  CC_User_YourDeath        = 277,
  CC_User_OtherDeath       = 278,
  CC_User_OtherHitOther    = 279,
  CC_User_OtherMissOther   = 280,
  CC_User_Who              = 281,
  CC_User_Yell             = 282,
  CC_User_NonMelee         = 283,
  CC_User_SpellWornOff     = 284,
  CC_User_MoneySplit       = 285,
  CC_User_Loot             = 286,
  CC_User_Random           = 287,
  CC_User_OtherSpells      = 288,
  CC_User_SpellFailure     = 289,
  CC_User_ChatChannel      = 290,
  CC_User_Chat1            = 291,
  CC_User_Chat2            = 292,
  CC_User_Chat3            = 293,
  CC_User_Chat4            = 294,
  CC_User_Chat5            = 295,
  CC_User_Chat6            = 296,
  CC_User_Chat7            = 297,
  CC_User_Chat8            = 298,
  CC_User_Chat9            = 299,
  CC_User_Chat10           = 300,
  CC_User_MeleeCrit        = 301,
  CC_User_SpellCrit        = 302,
  CC_User_TooFarAway       = 303,
  CC_User_NPCRampage       = 304,
  CC_User_NPCFurry         = 305,
  CC_User_NPCEnrage        = 306,
  CC_User_EchoSay          = 307,
  CC_User_EchoTell         = 308,
  CC_User_EchoGroup        = 309,
  CC_User_EchoGuild        = 310,
  CC_User_EchoOOC          = 311,
  CC_User_EchoAuction      = 312,
  CC_User_EchoShout        = 313,
  CC_User_EchoEmote        = 314,
  CC_User_EchoChat1        = 315,
  CC_User_EchoChat2        = 316,
  CC_User_EchoChat3        = 317,
  CC_User_EchoChat4        = 318,
  CC_User_EchoChat5        = 319,
  CC_User_EchoChat6        = 320,
  CC_User_EchoChat7        = 321,
  CC_User_EchoChat8        = 322,
  CC_User_EchoChat9        = 323,
  CC_User_EchoChat10       = 324,
  CC_User_UnusedAtThisTime = 325,
  CC_User_ItemTags         = 326,
  CC_User_RaidSay          = 327,
  CC_User_MyPet            = 328,
  CC_User_DamageShield     = 329,
};

/*
** Group Update actions
*/
enum GroupUpdateAction
{
  GUA_Joined = 0,
  GUA_Left = 1,
  GUA_LastLeft = 6,
  GUA_FullGroupInfo = 7,
  GUA_MakeLeader = 8,
  GUA_Started = 9,
};

/**
 * Leadership AAs enum, used to index into leadershipAAs in charProfileStruct
 */
enum LeadershipAAIndex
{
  groupMarkNPC = 0,
  groupNPCHealth,
  groupDelegateMainAssist,
  groupDelegateMarkNPC,
  groupUnknown4,
  groupUnknown5,
  groupInspectBuffs,
  groupUnknown7,
  groupSpellAwareness,
  groupOffenseEnhancement,
  groupManaEnhancement,
  groupHealthEnhancement,
  groupHealthRegeneration,
  groupFindPathToPC,
  groupHealthOfTargetsTarget,
  groupUnknown15,
  raidMarkNPC,                                   //0x10
  raidNPCHealth,
  raidDelegateMainAssist,
  raidDelegateMarkNPC,
  raidUnknown4,
  raidUnknown5,
  raidUnknown6,
  raidSpellAwareness,
  raidOffenseEnhancement,
  raidManaEnhancement,
  raidHealthEnhancement,
  raidHealthRegeneration,
  raidFindPathToPC,
  raidHealthOfTargetsTarget,
  raidUnknown14,
  raidUnknown15,
  MAX_LEAD_AA //=32
};

/**
 * Recast timer types. Used as an off set to charProfileStruct timers.
 */
enum RecastTypes
{
  RecastTimer0 = 0,
  RecastTimer1,
  WeaponHealClickTimer,                          // 2
  MuramiteBaneNukeClickTimer,                    // 3
  RecastTimer4,
  DispellClickTimer,                             // 5 (also click heal orbs?)
  EpicTimer,                                     // 6
  OoWBPClickTimer,                               // 7
  VishQuestClassItemTimer,                       // 8
  HealPotionTimer,                               // 9
  RecastTimer10,
  RecastTimer11,
  RecastTimer12,
  RecastTimer13,
  RecastTimer14,
  RecastTimer15,
  RecastTimer16,
  RecastTimer17,
  RecastTimer18,
  ModRodTimer,                                   // 19
  MAX_RECAST_TYPES                               // 20
};


/*
** Compiler override to ensure
** byte aligned structures
*/
#pragma pack(1)

/*
**            Generic Structures used in specific
**                      structures below
*/

// OpCode stuff (all kinda silly, but until we stop including the OpCode everywhere)...
struct opCodeStruct
{
    int16_t opCode;

  // kinda silly -- this is required for us to be able to stuff them in a QValueList
  bool operator== ( const opCodeStruct t ) const
  {
    return ( opCode == t.opCode);
  }
  bool operator== ( uint16_t opCode2 ) const
  {
    return ( opCode == opCode2 );
  }
};

/**
 * Session request on a stream. This is sent by the client to initiate
 * a session with the zone or world server.
 * 
 * Size: 12 Octets
 */
struct SessionRequestStruct
{
/*0000*/ uint32_t unknown0000;
/*0004*/ uint32_t sessionId;
/*0008*/ uint32_t maxLength;
/*0012*/
};

/**
 * Session response on a stream. This is the server replying to a session
 * request with session information.
 *
 * Size: 19 Octets
 */
struct SessionResponseStruct
{
/*0000*/ uint32_t sessionId;
/*0004*/ uint32_t key;
/*0008*/ uint16_t unknown0008;
/*0010*/ uint8_t unknown0010;
/*0011*/ uint32_t maxLength;
/*0015*/ uint32_t unknown0015;
/*0019*/
};

/**
 * Session disconnect on a stream. This is the server telling the client to
 * close a stream.
 *
 * Size: 9 Octets
 */
struct SessionDisconnectStruct
{
/*0000*/ uint8_t unknown0000;
/*0001*/ uint32_t sessionId;
/*0005*/ uint8_t unknown[4];
/*0009*/
};

/* 
 * Used in charProfileStruct
 * Size: 4 Octets
 */
struct Color_Struct
{
  union
  {
    struct
    {
/*0000*/uint8_t blue;
/*0001*/uint8_t red;
/*0002*/uint8_t green;
/*0003*/uint8_t unknown0003;
    } rgb;
/*0000*/uint32_t color;
  };
};

/*
* Used in charProfileStruct. Buffs
* Length: 110 Octets
*/
// EQ Mac SpellBuff_Struct (10 bytes). From mac_structs.h:461.
struct spellBuff
{
/*0000*/ uint8_t  bufftype;                      // 0=hidden, 1=permanent, 2=timed, 4=reverse-tap
/*0001*/ uint8_t  level;                         // Caster level
/*0002*/ uint8_t  bard_modifier;
/*0003*/ uint8_t  activated;
/*0004*/ uint16_t spellid;
/*0006*/ uint16_t duration;                      // ticks remaining
/*0008*/ uint16_t counters;                      // rune amount / counters
/*0010*/
};


/* 
 * Used in charProfileStruct
 * Size: 12 Octets
 */
struct AA_Array
{
/*000*/ uint32_t AA;
/*004*/ uint32_t value;
/*008*/ uint32_t unknown008;
/*012*/
};

/**
 * Used in charProfileStruct. An item inline in the stream, used in Bandolier and Potion Belt.
 * Size: 72 Octets 
 */
struct InlineItem
{
/*000*/ uint32_t itemId;
/*004*/ uint32_t icon;
/*008*/ char itemName[64];
/*072*/
};

/**
 * Used in charProfileStruct. Contents of a Bandolier.
 * Size: 320 Octets 
 */
struct BandolierStruct
{
/*000*/ char bandolierName[32];
/*032*/ InlineItem mainHand;
/*104*/ InlineItem offHand;
/*176*/ InlineItem range;
/*248*/ InlineItem ammo;
/*320*/
};

/**
 * Used in charProfileStruct. A tribute a player can have loaded.
 * Size: 8 Octets 
 */
struct TributeStruct
{
/*000*/ uint32_t tribute;
/*004*/ uint32_t rank;
/*008*/
};

/**
 * Used in charProfileStruct. A bind point.
 * Size: 20 Octets
 */
struct BindStruct
{
/*000*/ uint32_t zoneId;
/*004*/ float x;
/*008*/ float y;
/*012*/ float z;
/*016*/ float heading;
/*020*/
};

/*
 * Used in charProfileStruct. Visible Equipment.
 * Size: 20 Octets
 */
struct EquipStruct
{
/*00*/ uint32_t equip0;
/*04*/ uint32_t equip1;
/*08*/ uint32_t equip2;
/*12*/ uint32_t itemId;
/*16*/ uint32_t equip3;
/*20*/
};

/*
** Type:   Zone Change Request (before hand)
** Length: 100 Octets
** OpCode: ZoneChangeCode
*/
// EQ Mac OP_ZoneChange body (76 bytes). Layout from
// EQMacEmu/common/eq_packet_structs.h::ZoneChange_Struct.
struct zoneChangeStruct
{
/*0000*/ char     name[64];                      // Character Name
/*0064*/ uint16_t zoneId;
/*0066*/ uint16_t zone_reason;
/*0068*/ uint16_t unknown0068[2];
/*0072*/ int8_t   success;                       // 0=client→server, 1=server→client, -X=error
/*0073*/ uint8_t  error[3];                      // 0=ok, ffffff=error
/*0076*/
};


/*
** Client Zone Entry struct
** Length: 88 Octets
** OpCode: ZoneEntryCode (when direction == client)
*/
// EQ Mac OP_ZoneEntry (client direction) body. EQMacEmu's
// ClientZoneEntry_Struct is just `uint32 + char_name[64]` = 68 bytes,
// which matches the wire size. (server direction sends ServerZoneEntry,
// a different layout.)
struct ClientZoneEntryStruct
{
/*0000*/ uint32_t unknown0000;
/*0004*/ char     name[64];                      // Character Name
/*0068*/
};


/*
** New Zone Code
** Length: 936 Octets
** OpCode: NewZoneCode
*/
struct newZoneStruct
{
/*0000*/ char    name[64];                       // Character name
/*0064*/ char    shortName[32];                  // Zone Short Name (maybe longer?)
/*0096*/ char    unknown0096[96];
/*0192*/ char    longName[278];                  // Zone Long Name
/*0470*/ uint8_t ztype;                          // Zone type
/*0471*/ uint8_t fog_red[4];                     // Zone fog (red)
/*0475*/ uint8_t fog_green[4];                   // Zone fog (green)
/*0479*/ uint8_t fog_blue[4];                    // Zone fog (blue)
/*0483*/ uint8_t unknown0483[55];                // *** Placeholder
/*0538*/ uint8_t sky;                            // Zone sky
/*0539*/ uint8_t unknown0539[13];                // *** Placeholder
/*0551*/ float   zone_exp_multiplier;            // Experience Multiplier
/*0556*/ float   safe_y;                         // Zone Safe Y
/*0560*/ float   safe_x;                         // Zone Safe X
/*0564*/ float   safe_z;                         // Zone Safe Z
/*0568*/ float   unknown0568;                    // *** Placeholder
/*0572*/ float   unknown0572;                    // *** Placeholder
/*0576*/ float   underworld;                     // Underworld
/*0580*/ float   minclip;                        // Minimum view distance
/*0584*/ float   maxclip;                        // Maximum view distance
/*0588*/ uint8_t unknown0588[84];                // *** Placeholder
/*0672*/ char    zonefile[64];                   // Zone file name?
/*0736*/ uint8_t unknown0736[36];                // *** Placeholder (12/05/2006)
/*0772*/ uint8_t unknown0772[32];                // *** Placeholder (02/13/2007)
/*0804*/ uint8_t unknown0804[12];                // *** Placeholder 
/*0816*/ uint8_t unknown0816[4];                 // *** Placeholder (06/29/2005)
/*0820*/ uint8_t unknown0820[4];                 // *** Placeholder (09/13/2005)
/*0824*/ uint8_t unknown0824[4];                 // *** Placeholder (02/21/2006)
/*0828*/ uint8_t unknown0828[36];                // *** Placeholder (06/13/2006)
/*0864*/ uint8_t unknown0864[12];                // *** Placeholder (12/05/2006)
/*0876*/ uint8_t unknown0876[8];                 // *** Placeholder (02/13/2007)
/*0884*/ uint8_t unknown0884[4];                 // *** Placeholder (11/24/2007)
/*0888*/ uint8_t unknown0888[4];                 // *** Placeholder (01/17/2008)
/*0892*/ uint8_t unknown0892[4];                 // *** Placeholder (09/03/2008)
/*0896*/ uint8_t unknown0896[4];                 // *** Placeholder (10/07/2008)
/*0900*/ uint8_t unknown0900[8];                 // *** Placeholder (11/04/2009)
/*0908*/ uint8_t unknown0908[4];                 // *** Placeholder (12/15/2009)
/*0912*/ uint8_t unknown0912[4];                 // *** Placeholder (11/15/2011)
/*0916*/ uint8_t unknown0916[4];                 // *** Placeholder (04/29/2014)
/*0920*/ uint8_t unknown0920[4];                 // *** Placeholder (10/28/2014)
/*0924*/ uint8_t unknown0924[4];                 // *** Placeholder (03/16/2016)
/*0928*/ uint8_t unknown0928[8];		 // *** Placeholder (09/21/2016)
/*0936*/
};


/**
 * Player Profile. Common part of charProfileStruct shared between
 * shrouding and zoning profiles.
 *
 * NOTE: Offsets are kept in here relative to OP_PlayerProfile to ease in
 *       diagnosing changes in that struct.
 */
// EQ Mac PlayerProfile_Struct (8460 bytes). Flat layout from
// EQMacEmu/common/patches/mac_structs.h::PlayerProfile_Struct. Field names
// follow the showeq legacy where slots reference them (curHp not cur_hp,
// MANA not mana, sSpellBook not spell_book, lastName not last_name,
// guildID not guild_id) so existing slot code compiles without rewriting
// every field access.
//
// charProfileStruct is the public name (used at the OP_PlayerProfile
// dispatch boundary); playerProfileStruct is an alias retained for the
// loadProfile() signature. There is no `profile.` indirection on EQ Mac —
// the wire is a single flat struct.
struct charProfileStruct
{
/*0000*/ uint32_t checksum;
/*0004*/ uint8_t  unknown0004[2];
/*0006*/ char     name[64];                       // Player first name
/*0070*/ char     lastName[66];                   // Surname (legacy showeq: lastName)
/*0136*/ uint32_t uniqueGuildID;
/*0140*/ uint8_t  gender;
/*0141*/ char     genderchar[1];
/*0142*/ uint16_t race;
/*0144*/ uint16_t class_;
/*0146*/ uint16_t bodytype;
/*0148*/ uint8_t  level;
/*0149*/ char     levelchar[3];
/*0152*/ uint32_t exp;
/*0156*/ int16_t  points;                         // Practice points
/*0158*/ int16_t  MANA;                           // current mana
/*0160*/ int16_t  curHp;                          // current hp
/*0162*/ uint16_t status;
/*0164*/ int16_t  STR;
/*0166*/ int16_t  STA;
/*0168*/ int16_t  CHA;
/*0170*/ int16_t  DEX;
/*0172*/ int16_t  INT;
/*0174*/ int16_t  AGI;
/*0176*/ int16_t  WIS;
/*0178*/ uint8_t  face;
/*0179*/ uint8_t  EquipType[9];
/*0188*/ uint32_t EquipColor[9];                  // Tint per slot (Tint_Struct = uint32)
/*0224*/ int16_t  inventory[30];
/*0284*/ uint8_t  languages[32];                  // First MAX_KNOWN_LANGS used
/*0316*/ uint8_t  invItemProperties[300];         // ItemProperties_Struct[30] (10 bytes each)
/*0616*/ spellBuff buffs[15];                     // 150 bytes
/*0766*/ int16_t  containerinv[80];
/*0926*/ int16_t  cursorbaginventory[10];
/*0946*/ uint8_t  bagItemProperties[800];         // ItemProperties_Struct[80]
/*1746*/ uint8_t  cursorItemProperties[100];      // ItemProperties_Struct[10]
/*1846*/ int16_t  sSpellBook[256];                // 512 bytes (showeq legacy name)
/*2358*/ uint8_t  unknown2358[512];
/*2870*/ int16_t  sMemSpells[8];                  // 16 bytes (legacy showeq name)
/*2886*/ uint8_t  unknown2886[16];
/*2902*/ uint16_t available_slots;
/*2904*/ float    y;
/*2908*/ float    x;
/*2912*/ float    z;
/*2916*/ float    heading;
/*2920*/ uint32_t position;
/*2924*/ int32_t  platinum;
/*2928*/ int32_t  gold;
/*2932*/ int32_t  silver;
/*2936*/ int32_t  copper;
/*2940*/ int32_t  platinum_bank;
/*2944*/ int32_t  gold_bank;
/*2948*/ int32_t  silver_bank;
/*2952*/ int32_t  copper_bank;
/*2956*/ int32_t  platinum_cursor;
/*2960*/ int32_t  gold_cursor;
/*2964*/ int32_t  silver_cursor;
/*2968*/ int32_t  copper_cursor;
/*2972*/ int32_t  currency[4];
/*2988*/ int16_t  skills[100];                    // First MAX_KNOWN_SKILLS used
/*3188*/ int16_t  innate_skills[25];
/*3238*/ uint8_t  air_supply;
/*3239*/ uint8_t  texture;
/*3240*/ float    height;
/*3244*/ float    width;
/*3248*/ float    length;
/*3252*/ float    view_height;
/*3256*/ char     boat[32];
/*3288*/ uint8_t  unknown3288[60];
/*3348*/ uint8_t  autosplit;
/*3349*/ uint8_t  unknown3349[43];
/*3392*/ uint8_t  expansions;
/*3393*/ uint8_t  unknown3393[23];
/*3416*/ int32_t  hunger_level;
/*3420*/ int32_t  thirst_level;
/*3424*/ spellBuff buff_unknown3424[2];           // 20 bytes
/*3444*/ uint32_t zoneId;
/*3448*/ uint8_t  unknown3448[126];
/*3574*/ spellBuff buffs_ext[15];                 // 150 bytes
/*3724*/ uint16_t buff_caster_id[30];
/*3784*/ uint32_t bind_point_zone[5];
/*3804*/ float    bind_y[5];
/*3824*/ float    bind_x[5];
/*3844*/ float    bind_z[5];
/*3864*/ float    bind_heading[5];
/*3884*/ uint8_t  bankinvitemproperties[80];      // ItemProperties_Struct[8]
/*3964*/ uint8_t  bankbagitemproperties[800];     // ItemProperties_Struct[80]
/*4764*/ uint32_t login_time;
/*4768*/ int16_t  bank_inv[8];
/*4784*/ int16_t  bank_cont_inv[80];
/*4944*/ uint16_t deity;
/*4946*/ uint16_t guildID;                        // guild_id (legacy: guildID)
/*4948*/ uint32_t birthday;
/*4952*/ uint32_t lastlogin;
/*4956*/ uint32_t timePlayedMin;
/*4960*/ int8_t   thirst_level_unused;
/*4961*/ int8_t   hunger_level_unused;
/*4962*/ int8_t   fatigue;
/*4963*/ uint8_t  pvp;
/*4964*/ uint8_t  level2;
/*4965*/ uint8_t  anon;
/*4966*/ uint8_t  gm;
/*4967*/ uint8_t  guildrank;                      // 0=member, 1=officer, 2=leader
/*4968*/ uint8_t  intoxication;
/*4969*/ uint8_t  eqbackground;
/*4970*/ uint8_t  unknown4970[2];
/*4972*/ uint32_t spellSlotRefresh[8];
/*5004*/ uint32_t unknown5004;
/*5008*/ uint32_t abilitySlotRefresh;
/*5012*/ char     groupMembers[6][64];
/*5396*/ uint8_t  unknown5396[20];
/*5416*/ uint32_t groupdat;
/*5420*/ uint32_t expAA;                          // Post60 / AA exp
/*5424*/ uint8_t  title;
/*5425*/ uint8_t  perAA;
/*5426*/ uint8_t  haircolor;
/*5427*/ uint8_t  beardcolor;
/*5428*/ uint8_t  eyecolor1;
/*5429*/ uint8_t  eyecolor2;
/*5430*/ uint8_t  hairstyle;
/*5431*/ uint8_t  beard;
/*5432*/ uint8_t  luclinface;
/*5433*/ uint32_t item_material[9];               // TextureProfile (9 × uint32)
/*5469*/ uint8_t  unknown5469[143];
/*5612*/ uint8_t  aa_array[240];                  // AA_Array (compact)
/*5852*/ uint32_t ATR_DIVINE_RES_timer;
/*5856*/ uint32_t ATR_FREE_HOT_timer;
/*5860*/ uint32_t ATR_TARGET_DA_timer;
/*5864*/ uint32_t SptWoodTimer;
/*5868*/ uint32_t DireCharmTimer;
/*5872*/ uint32_t ATR_STRONG_ROOT_timer;
/*5876*/ uint32_t ATR_MASOCHISM_timer;
/*5880*/ uint32_t ATR_MANA_BURN_timer;
/*5884*/ uint32_t ATR_GATHER_MANA_timer;
/*5888*/ uint32_t ATR_PET_LOH_timer;
/*5892*/ uint32_t ExodusTimer;
/*5896*/ uint32_t ATR_MASS_FEAR_timer;
/*5900*/ uint16_t air_remaining;
/*5902*/ uint16_t aapoints;
/*5904*/ uint32_t MGBTimer;
/*5908*/ uint8_t  unknown5908[91];
/*5999*/ int8_t   mBitFlags[6];
/*6005*/ uint8_t  unknown6005[707];
/*6712*/ uint32_t PoPSpellTimer;
/*6716*/ uint32_t LastShield;
/*6720*/ uint32_t LastModulated;
/*6724*/ uint8_t  unknown6724[1736];
/*8460*/
};

// On EQ Mac there is no separate inner profile struct — playerProfileStruct
// is just an alias for charProfileStruct. The Player::loadProfile signature
// continues to compile.
using playerProfileStruct = charProfileStruct;

#if 1
struct playerAAStruct {
/*    0 */  uint8_t unknown0;
  union {
    uint8_t unnamed[17];
    struct _named {  
/*    1 */  uint8_t innate_strength;
/*    2 */  uint8_t innate_stamina;
/*    3 */  uint8_t innate_agility;
/*    4 */  uint8_t innate_dexterity;
/*    5 */  uint8_t innate_intelligence;
/*    6 */  uint8_t innate_wisdom;
/*    7 */  uint8_t innate_charisma;
/*    8 */  uint8_t innate_fire_protection;
/*    9 */  uint8_t innate_cold_protection;
/*   10 */  uint8_t innate_magic_protection;
/*   11 */  uint8_t innate_poison_protection;
/*   12 */  uint8_t innate_disease_protection;
/*   13 */  uint8_t innate_run_speed;
/*   14 */  uint8_t innate_regeneration;
/*   15 */  uint8_t innate_metabolism;
/*   16 */  uint8_t innate_lung_capacity;
/*   17 */  uint8_t first_aid;
    } named;
  } general_skills;
  union {
    uint8_t unnamed[17];
    struct _named {
/*   18 */  uint8_t healing_adept;
/*   19 */  uint8_t healing_gift;
/*   20 */  uint8_t unknown20;
/*   21 */  uint8_t spell_casting_reinforcement;
/*   22 */  uint8_t mental_clarity;
/*   23 */  uint8_t spell_casting_fury;
/*   24 */  uint8_t chanelling_focus;
/*   25 */  uint8_t unknown25;
/*   26 */  uint8_t unknown26;
/*   27 */  uint8_t unknown27;
/*   28 */  uint8_t natural_durability;
/*   29 */  uint8_t natural_healing;
/*   30 */  uint8_t combat_fury;
/*   31 */  uint8_t fear_resistance;
/*   32 */  uint8_t finishing_blow;
/*   33 */  uint8_t combat_stability;
/*   34 */  uint8_t combat_agility;
    } named;
  } archetype_skills;
  union {
    uint8_t unnamed[93];
    struct _name {
/*   35 */  uint8_t mass_group_buff;             // All group-buff-casting classes(?)
// ===== Cleric =====
/*   36 */  uint8_t divine_resurrection;
/*   37 */  uint8_t innate_invis_to_undead;      // cleric, necromancer
/*   38 */  uint8_t celestial_regeneration;
/*   39 */  uint8_t bestow_divine_aura;
/*   40 */  uint8_t turn_undead;
/*   41 */  uint8_t purify_soul;
// ===== Druid =====
/*   42 */  uint8_t quick_evacuation;            // wizard, druid
/*   43 */  uint8_t exodus;                      // wizard, druid
/*   44 */  uint8_t quick_damage;                // wizard, druid
/*   45 */  uint8_t enhanced_root;               // druid
/*   46 */  uint8_t dire_charm;                  // enchanter, druid, necromancer
// ===== Shaman =====
/*   47 */  uint8_t cannibalization;
/*   48 */  uint8_t quick_buff;                  // shaman, enchanter
/*   49 */  uint8_t alchemy_mastery;
/*   50 */  uint8_t rabid_bear;
// ===== Wizard =====
/*   51 */  uint8_t mana_burn;
/*   52 */  uint8_t improved_familiar;
/*   53 */  uint8_t nexus_gate;
// ===== Enchanter  =====
/*   54 */  uint8_t unknown54;
/*   55 */  uint8_t permanent_illusion;
/*   56 */  uint8_t jewel_craft_mastery;
/*   57 */  uint8_t gather_mana;
// ===== Mage =====
/*   58 */  uint8_t mend_companion;              // mage, necromancer
/*   59 */  uint8_t quick_summoning;
/*   60 */  uint8_t frenzied_burnout;
/*   61 */  uint8_t elemental_form_fire;
/*   62 */  uint8_t elemental_form_water;
/*   63 */  uint8_t elemental_form_earth;
/*   64 */  uint8_t elemental_form_air;
/*   65 */  uint8_t improved_reclaim_energy;
/*   66 */  uint8_t turn_summoned;
/*   67 */  uint8_t elemental_pact;
// ===== Necromancer =====
/*   68 */  uint8_t life_burn;
/*   69 */  uint8_t dead_mesmerization;
/*   70 */  uint8_t fearstorm;
/*   71 */  uint8_t flesh_to_bone;
/*   72 */  uint8_t call_to_corpse;
// ===== Paladin =====
/*   73 */  uint8_t divine_stun;
/*   74 */  uint8_t improved_lay_of_hands;
/*   75 */  uint8_t slay_undead;
/*   76 */  uint8_t act_of_valor;
/*   77 */  uint8_t holy_steed;
/*   78 */  uint8_t fearless;                    // paladin, shadowknight

/*   79 */  uint8_t two_hand_bash;               // paladin, shadowknight
// ===== Ranger =====
/*   80 */  uint8_t innate_camouflage;           // ranger, druid
/*   81 */  uint8_t ambidexterity;               // all "dual-wield" users
/*   82 */  uint8_t archery_mastery;             // ranger
/*   83 */  uint8_t unknown83;
/*   84 */  uint8_t endless_quiver;              // ranger
// ===== Shadow Knight =====
/*   85 */  uint8_t unholy_steed;
/*   86 */  uint8_t improved_harm_touch;
/*   87 */  uint8_t leech_touch;
/*   88 */  uint8_t unknown88;
/*   89 */  uint8_t soul_abrasion;
// ===== Bard =====
/*   90 */  uint8_t instrument_mastery;
/*   91 */  uint8_t unknown91;
/*   92 */  uint8_t unknown92;
/*   93 */  uint8_t unknown93;
/*   94 */  uint8_t jam_fest;
/*   95 */  uint8_t unknown95;
/*   96 */  uint8_t unknown96;
// ===== Monk =====
/*   97 */  uint8_t critical_mend;
/*   98 */  uint8_t purify_body;
/*   99 */  uint8_t unknown99;
/*  100 */  uint8_t rapid_feign;
/*  101 */  uint8_t return_kick;
// ===== Rogue =====
/*  102 */  uint8_t escape;
/*  103 */  uint8_t poison_mastery;
/*  104 */  uint8_t double_riposte;              // all "riposte" users
/*  105 */  uint8_t unknown105;
/*  106 */  uint8_t unknown106;
/*  107 */  uint8_t purge_poison;                // rogue
// ===== Warrior =====
/*  108 */  uint8_t flurry;
/*  109 */  uint8_t rampage;
/*  110 */  uint8_t area_taunt;
/*  111 */  uint8_t warcry;
/*  112 */  uint8_t bandage_wound;
// ===== (Other) =====
/*  113 */  uint8_t spell_casting_reinforcement_mastery; // all "pure" casters
/*  114 */  uint8_t unknown114;
/*  115 */  uint8_t extended_notes;              // bard
/*  116 */  uint8_t dragon_punch;                // monk
/*  117 */  uint8_t strong_root;                 // wizard
/*  118 */  uint8_t singing_mastery;             // bard
/*  119 */  uint8_t body_and_mind_rejuvenation;  // paladin, ranger, bard
/*  120 */  uint8_t physical_enhancement;        // paladin, ranger, bard
/*  121 */  uint8_t adv_trap_negotiation;        // rogue, bard
/*  122 */  uint8_t acrobatics;                  // all "safe-fall" users
/*  123 */  uint8_t scribble_notes;              // bard
/*  124 */  uint8_t chaotic_stab;                // rogue
/*  125 */  uint8_t pet_discipline;              // all pet classes except enchanter
/*  126 */  uint8_t unknown126;
/*  127 */  uint8_t unknown127;
    } named;
  } class_skills;
};
#endif

/*
** Generic Spawn Struct 
** Length: Variable.
** Used in: 
**   dbSpawnStruct
**   petStruct
**   spawnShroudOther
**   spawnShroudSelf
*/

// Fixed-length struct that we'll fill with data from the variable-length packet,
// unnecessary fields removed, arranged in order with the packet.
// EQ Mac wire-layout Spawn_Struct (224 bytes). Layout from
// EQMacEmu/common/patches/mac_structs.h::Spawn_Struct, with field names
// adapted to the legacy showeq names that the SpawnShell / Spawn / Player
// code paths reference (e.g. `y` not `y_pos`, `curHp` not `cur_hp`,
// `guildID` not `GuildID`, `lastName` not `Surname`). Offsets are
// byte-exact under the file's enclosing #pragma pack(1).
struct spawnStruct
{
/*0000*/ uint32_t random_dontuse;
/*0004*/ int8_t   accel;
/*0005*/ uint8_t  heading;                       // 0..255
/*0006*/ int8_t   deltaHeading;
/*0007*/ int16_t  y;                             // y_pos
/*0009*/ int16_t  x;                             // x_pos
/*0011*/ int16_t  z;                             // z_pos
/*0013*/ uint32_t deltaY:11, deltaZ:11, deltaX:10;
/*0017*/ uint8_t  void1;
/*0018*/ uint16_t petOwnerId;
/*0020*/ uint8_t  animation;
/*0021*/ uint8_t  haircolor;
/*0022*/ uint8_t  beardcolor;
/*0023*/ uint8_t  eyecolor1;
/*0024*/ uint8_t  eyecolor2;
/*0025*/ uint8_t  hairstyle;
/*0026*/ uint8_t  beard;
/*0027*/ uint8_t  title_id;                      // Was Mac `title`; renamed to avoid collision with the title[] string field at the end on post-EQMac structs (this is just an id byte).
/*0028*/ float    size;
/*0032*/ float    walkspeed;
/*0036*/ float    runspeed;
/*0040*/ uint32_t equipcolors[9];                // Tint per slot (helm/chest/arms/wrist/hands/legs/feet/primary/secondary)
/*0076*/ uint16_t spawnId;                       // spawn_id
/*0078*/ int16_t  bodytype;
/*0080*/ int16_t  curHp;                         // cur_hp
/*0082*/ int16_t  guildID;                       // GuildID
/*0084*/ uint16_t race;
/*0086*/ uint8_t  NPC;                           // 0=PC, 1=NPC, 2=PC-corpse, 3=NPC-corpse, 5=unknown, 10=self
/*0087*/ uint8_t  class_;
/*0088*/ uint8_t  gender;                        // 0=male, 1=female, 2=other
/*0089*/ uint8_t  level;
/*0090*/ uint8_t  invis;
/*0091*/ uint8_t  sneaking;
/*0092*/ uint8_t  pvp;
/*0093*/ uint8_t  anim_type;
/*0094*/ uint8_t  light;
/*0095*/ int8_t   anon;                          // 0=normal, 1=anon, 2=role
/*0096*/ int8_t   AFK;
/*0097*/ int8_t   summoned_pc;
/*0098*/ int8_t   LD;                            // linkdead flag
/*0099*/ int8_t   GM;
/*0100*/ int8_t   flymode;
/*0101*/ int8_t   bodytexture;
/*0102*/ int8_t   helm;
/*0103*/ uint8_t  face;
/*0104*/ uint16_t equipment[9];                  // Worn equipment ids per slot
/*0122*/ int16_t  guildrank;
/*0124*/ int16_t  deity;
/*0126*/ int8_t   temporaryPet;
/*0127*/ char     name[64];
/*0191*/ char     lastName[32];                  // Mac field name `Surname`
/*0223*/ uint8_t  void_;
/*0224*/
};


// EQ Mac OP_ZoneEntry server direction — 356 bytes. From
// EQMacEmu/common/eq_packet_structs.h::ServerZoneEntry_Struct.
struct ServerZoneEntryStruct
{
/*0000*/ uint8_t  checksum[4];
/*0004*/ uint8_t  type;
/*0005*/ char     name[64];
/*0069*/ uint8_t  sze_unknown0069;
/*0070*/ uint16_t unknown0070;
/*0072*/ uint32_t zoneId;
/*0076*/ float    y;
/*0080*/ float    x;
/*0084*/ float    z;
/*0088*/ float    heading;
/*0092*/ float    physicsinfo[8];
/*0124*/ int32_t  prev;
/*0128*/ int32_t  next;
/*0132*/ int32_t  corpse;
/*0136*/ int32_t  LocalInfo;
/*0140*/ int32_t  My_Char;
/*0144*/ float    view_height;
/*0148*/ float    sprite_oheight;
/*0152*/ uint16_t sprite_oheights;
/*0154*/ uint16_t petOwnerId;
/*0156*/ uint32_t max_hp;
/*0160*/ uint32_t curHP;
/*0164*/ uint16_t guildID;
/*0166*/ uint8_t  socket[6];
/*0172*/ uint8_t  NPC;
/*0173*/ uint8_t  class_;
/*0174*/ uint16_t race;
/*0176*/ uint8_t  gender;
/*0177*/ uint8_t  level;
/*0178*/ uint8_t  invis;
/*0179*/ uint8_t  sneaking;
/*0180*/ uint8_t  pvp;
/*0181*/ uint8_t  anim_type;
/*0182*/ uint8_t  light;
/*0183*/ int8_t   face;
/*0184*/ uint16_t equipment[9];
/*0202*/ uint16_t equipment_unknown;
/*0204*/ uint32_t equipcolors[9];
/*0240*/ uint32_t bodytexture;
/*0244*/ float    size;
/*0248*/ float    width;
/*0252*/ float    length;
/*0256*/ uint32_t helm;
/*0260*/ float    walkspeed;
/*0264*/ float    runspeed;
/*0268*/ int8_t   LD;
/*0269*/ int8_t   GM;
/*0270*/ int16_t  flymode;
/*0272*/ int32_t  bodytype;
/*0276*/ int32_t  view_player;
/*0280*/ uint8_t  anon;
/*0281*/ uint16_t avatar;
/*0283*/ uint8_t  AFK;
/*0284*/ uint8_t  summoned_pc;
/*0285*/ uint8_t  title;
/*0286*/ uint8_t  extra[18];
/*0304*/ char     lastName[32];
/*0336*/ uint16_t guildrank;
/*0338*/ uint16_t deity;
/*0340*/ int8_t   animation;
/*0341*/ uint8_t  haircolor;
/*0342*/ uint8_t  beardcolor;
/*0343*/ uint8_t  eyecolor1;
/*0344*/ uint8_t  eyecolor2;
/*0345*/ uint8_t  hairstyle;
/*0346*/ uint8_t  beard;
/*0347*/ uint32_t SerialNumber;
/*0351*/ char     m_bTemporaryPet[4];
/*0355*/ uint8_t  void_;
/*0356*/
};

/*
** Generic Door Struct
** Length: 136 Octets
** Used in: 
**    OP_SpawnDoor
**
*/

struct doorStruct
{
/*0000*/ char    name[32];                       // Filename of Door?
/*0016*/ // uint8_t unknown016[16];              // ***Placeholder
/*0032*/ float   y;                              // y loc
/*0036*/ float   x;                              // x loc
/*0040*/ float   z;                              // z loc
/*0044*/ float   heading;                        // heading
/*0048*/ uint32_t incline;                       // incline
/*0052*/ uint8_t unknown0048[20];		 // seems to be a copy of the previous 5 fields?
/*0072*/ uint32_t size;                          // size
/*0076*/ uint8_t unknown0056[4];                 // ***Placeholder
/*0080*/ uint8_t doorId;                         // door's id #
/*0081*/ uint8_t opentype;                       // open type
/*0082*/ uint8_t spawnstate;                     // spawn state
/*0083*/ uint8_t invertstate;                    // invert state
/*0084*/ uint32_t zonePoint;
/*0088*/ uint8_t unknown068[28];                 // ***Placeholder
/*0116*/ uint8_t unknown096[20];                  // ***Placeholder
/*0132*/
}; 

/*
** Drop Item On Ground
** Length: Variable
** OpCode: MakeDropCode
*/
// Note: Unknowns and other members removed that we don't use since we
//       now only fill this with data we need from the serialized packet
struct makeDropStruct
{
   uint32_t dropId;                              // DropID
   float    heading;                             // Heading
   float    z;                                   // Z Position
   float    x;                                   // X Position
   float    y;                                   // Y Position
   char     idFile[30];                          // ACTOR ID - The client reads 30 bytes from the packet
                                                 //          - 20100210 eqgame.exe in EQItemList::UnpackNetData
};

/*
** ZonePoint
** Length: 24 Octets
** Sent as part of zonePointsStruct
*/

struct zonePointStruct
{
  /*0000*/ uint32_t zoneTrigger;
  /*0004*/ float    y;
  /*0008*/ float    x;
  /*0012*/ float    z;
  /*0016*/ float    heading;
  /*0020*/ uint16_t zoneId;
  /*0022*/ uint16_t zoneInstance;
  /*0024*/
};


/*
** Time of Day
** Length: 8 Octets
** OpCode: TimeOfDayCode
*/
// EQ Mac OP_TimeOfDay body — 6 bytes (no trailing padding). Matches the
// wire size seen in opcode-stats.
struct timeOfDayStruct
{
/*0000*/ uint8_t  hour;                          // Hour (1-24)
/*0001*/ uint8_t  minute;                        // Minute (0-59)
/*0002*/ uint8_t  day;                           // Day (1-28)
/*0003*/ uint8_t  month;                         // Month (1-12)
/*0004*/ uint16_t year;                          // Year
/*0006*/
};

/*
** Item Packet Struct - Works on a variety of item operations
** Packet Types: See ItemPacketType enum
** Length: Variable
** OpCode: ItemCode
*/
struct itemPacketStruct
{
/*000*/	ItemPacketType	packetType;              // See ItemPacketType for more info.
/*004*/	char		serializedItem[0];
/*xx*/
};

/*
** Item Info Request Struct 
** Length: 80 Octets 
** OpCode: ItemInfoCode
*/
struct itemInfoReqStruct
{
/*000*/ uint32_t itemNr;                         // ItemNr 
/*004*/ uint32_t requestSeq;                     // Request sequence number
/*008*/ char     name[64];                       // Item name
/*072*/ uint8_t unknown0006[8];                  // Placeholder
/*080*/
};

/*
** Item Info Response Struct
** Length: Variable
** OpCode: ItemInfoCode
*/
struct itemInfoStruct
{
/*000*/	uint32_t	requestSeq;              // Corresponds to sequence # in req
/*004*/	char		serializedItem[0];
/*xxx*/
};

/*
** Simple Spawn Update
** Length: 14 Octets
** OpCode: MobUpdateCode
*/


// EQ Mac spawn position update — 15 bytes per entry. OP_MobUpdate batches
// these as [int32_t numUpdates][N × spawnPositionUpdate] (mobUpdateStruct
// wrapper). Layout from EQMacEmu/utils/structs/seq/everquest.h:319.
struct spawnPositionUpdate
{
/*0000*/ uint16_t spawnId;                // Id of spawn to update
/*0002*/ int8_t   animation;              // Animation spawn is currently using
/*0003*/ int8_t   heading;                // Heading
/*0004*/ int8_t   deltaHeading;           // Heading change
/*0005*/ int16_t  y;                      // New Y position
/*0007*/ int16_t  x;                      // New X position
/*0009*/ int16_t  z;                      // New Z position
/*0011*/ signed   deltaY:10;              // Y velocity
         unsigned spacer1:1;
         signed   deltaZ:10;
         unsigned spacer2:1;
         signed   deltaX:10;
};

// OP_MobUpdate body: count-prefixed array of spawnPositionUpdate. EQ Mac
// wire is `[int32_t numUpdates][N × spawnPositionUpdate]`. (The seq/everquest.h
// reference shows a 6-byte header [opCode + version + numUpdates] from an
// older era; on Quarm the wire only carries the 4-byte count.)
struct mobUpdateStruct
{
/*0000*/ int32_t  numUpdates;             // Number of spawn updates
/*0004*/ struct spawnPositionUpdate spawnUpdate[0];
};


/*
** Illusion a spawn
** Length: 336 Octets
** OpCode: Illusion
*/
struct spawnIllusionStruct
{
/*0000*/ uint32_t   spawnId;                     // Spawn id of the target
/*0004*/ char       name[64];                    // Name of the target
/*0068*/ uint32_t   race;                        // New race
/*0072*/ uint8_t    gender;                      // New gender (0=male, 1=female)
/*0073*/ uint8_t    texture;                     // ???
/*0074*/ uint8_t    helm;                        // ???
/*0075*/ uint8_t    unknown0075;                 // ***Placeholder
/*0076*/ uint32_t   unknown0076;                 // ***Placeholder
/*0080*/ uint32_t   face;                        // New face
/*0084*/ uint8_t    unknown0084[248];            // ***Placeholder
/*0336*/
};





/*
**                 ShowEQ Specific Structures
*/



/*
** Server System Message
** Length: Variable Length
** OpCode: SysMsgCode
*/

struct sysMsgStruct
{
/*0000*/ char     message[0];                    // Variable length message
};

/*
** Emote text
** Length: Variable Text
** OpCode: emoteTextCode
*/

struct emoteTextStruct
{
/*0000*/ uint8_t  unknown0000[4];                // ***Placeholder
/*0004*/ char     text[0];                       // Emote `Text
};

/*
** Channel Message received or sent
** Length: Variable
** OpCode: ChannelMessageCode

This is how channelMessageStruct looks on the wire, for reference (8/12/09 eqgame.exe)

char            sender[0];                       // Variable length senders name 
char            target[0];                       // Variable length target characters name
uint32_t        unknown;
uint32_t        language;                        // Language
uint32_t        chanNum;                         // Channel
uint32_t        unknown;
uint8_t         unknown;
uint32_t        skillInLanguage;                 // senders skill in language
char            message[0];                      // Variable length message
uint8_t         unknown;
uint32_t        unknown;
uint32_t        unknown;
char            unknown[0];                      // Variable legth unknown text
uint8_t         unknown;
uint32_t        unknown;

*/

// EQ Mac OP_ChannelMessage body (zone server chat). Layout from
// EQMacEmu/common/eq_packet_structs.h:ChannelMessage_Struct — 136-byte
// header + variable-length NUL-terminated message.
struct channelMessageStruct
{
/*0000*/ char     target[64];                      // Tell recipient
/*0064*/ char     sender[64];                      // Sender's name
/*0128*/ uint16_t language;                        // Language id
/*0130*/ uint16_t chanNum;                         // Channel number
/*0132*/ uint16_t unused_align132;                 // struct alignment padding
/*0134*/ uint16_t skillInLanguage;                 // Sender's skill in this language
/*0136*/ char     message[2048];                   // Variable-length, NUL-terminated
};

/*
** Formatted text messages
** Length: Variable Text
** OpCode: emoteTextCode
*/

struct formattedMessageStruct
{
/*0000*/ uint8_t  unknown0000;
/*0001*/ uint8_t  unknown0001[4];                // ***Placeholder
/*0005*/ uint32_t messageFormat;                 // Indicates the message format
/*0009*/ ChatColor messageColor;                 // Message color
/*0013*/ char     messages[0];                   // no longer null terminated
						 // repeat (4-bytes len, string of len)
};


/*
** Special Message Struct
** Length: Variable Text
** OPCode: OP_SpecialMesg
*/

struct specialMessageStruct
{
  /*0000*/ uint8_t   unknown0000[3];             // message style?
  /*0003*/ ChatColor messageColor;               // message color
  /*0007*/ uint16_t  target;                     // message target
  /*0009*/ uint16_t  padding;                    // padding
  /*0011*/ char      source[0];                  // message text
  /*0xxx*/ uint32_t  unknown0xxx[3];             //***Placeholder
  /*0yyy*/ char      message[0];                 // message text
};

/*
** Guild MOTD Struct
** Length: Variable Text
** OPCode: OP_GuildMOTD
*/
struct guildMOTDStruct
{
  /*0000*/ uint32_t unknown0000;                 //***Placeholder
  /*0004*/ uint32_t unknown0004;		 // added 11/16/2016
  /*0008*/ char     target[64];                  // motd target
  /*0072*/ char     sender[64];                  // motd "sender" (who set it)
  /*0136*/ uint32_t unknown0136;                 //***Placeholder
  /*0140*/ char     message[0];
};



/*
** Consent Response
** Length: 193 Octets
*/

struct consentResponseStruct
{
/*0000*/ char consentee[64];                     // Name of player who was consented
/*0064*/ char consenter[64];                     // Name of player who consented
/*0128*/ uint8_t allow;                          // 00 = deny, 01 = allow
/*0129*/ char corpseZoneName[64];                // Zone where the corpse is
/*0193*/
};

/*
** Grouping Information
** Length: 456 Octets
** OpCode: OP_GroupUpdate
*/


struct groupUpdateStruct
{
/*0000*/ int32_t  action;                        // Group update action
/*0004*/ char     yourname[64];                  // Group Member Names
/*0068*/ char     membername[64];                // Group leader name
/*0132*/ uint8_t  unknown0132[324];              // ***Placeholder
/*456*/
};


/*
** DEPRECATED
** Grouping Information
** Length: 768 Octets
** OpCode: OP_GroupUpdate
*/

struct groupFullUpdateStruct
{
/*0000*/ int32_t  action;
/*0004*/ char     membernames[MAX_GROUP_MEMBERS][64]; // Group Member Names
/*0388*/ char     leader[64];                         // Group leader Name
/*0452*/ char     unknown0452[316];                   // ***Placeholder
/*0768*/
};

/*
** Grouping Invite
** Length 152 Octets
** Opcode OP_GroupInvite
*/

struct groupInviteStruct
{
/*0000*/ char     invitee[64];                   // Invitee's Name
/*0064*/ char     inviter[64];                   // Inviter's Name
/*0128*/ uint8_t  unknown0128[24];               // ***Placeholder
/*0152*/
};

/*
** Grouping Invite Answer - Decline
** Length 156 Octets
** Opcode GroupDeclineCode
*/

struct groupDeclineStruct
{
/*0000*/ char     yourname[64];                  // Player Name
/*0064*/ char     membername[64];                // Invited Member Name
/*0128*/ uint8_t  unknown0128[24];               // ***Placeholder
/*0152*/ uint8_t  reason;                        // Already in Group = 1, Declined Invite = 3
/*0153*/ uint8_t  unknown0149[3];                // ***Placeholder
/*0156*/
};

/*
** Grouping Invite Answer - Accept 
** Length 152 Octets
** Opcode OP_GroupFollow
*/

struct groupFollowStruct
{
/*0000*/ char     unknown0000[64];               // ***Placeholder (zeros)
/*0064*/ char     invitee[64];                   // Invitee's Member Name
/*0128*/ uint8_t  unknown0128[4];                // ***Placeholder
/*0132*/ uint32_t level;                         // Invitee's level
/*0136*/ uint8_t  unknown0136[16];               // ***Placeholder (zeros)
/*0152*/
};

/*
** Group Disbanding
** Length 152 Octets
** Opcode 
*/

struct groupDisbandStruct
{
/*0000*/ char     yourname[64];                  // Player Name
/*0064*/ char     membername[64];                // Invited Member Name
/*0128*/ uint8_t  unknown0128[24];               // ***Placeholder
/*0152*/
};

/*
** Group Leader Change
** Length 152 Octets
** Opcode OP_GroupLeader
*/

struct groupLeaderChangeStruct
{
/*0000*/ char     unknown0000[64];               // ***Placeholder
/*0064*/ char     membername[64];                // Invited Member Name
/*0128*/ uint8_t  unknown0128[24];               // ***Placeholder
/*0152*/
};

/*
** Delete Self
** Length: 4 Octets
** OpCode: OP_DeleteSpawn
*/

// EQ Mac OP_DeleteSpawn body: just the 2-byte spawnId. Wire confirmed at
// 2 bytes per opcode-stats. (Older protocol generations carried opCode +
// version prefix bytes; EQ Mac doesn't.)
struct deleteSpawnStruct
{
/*0000*/ uint16_t spawnId;                       // Spawn ID to delete
/*0002*/
};


/*
** Remove Drop Item On Ground
** Length: 12 Octets
** OpCode: RemDropCode
*/

struct remDropStruct
{
/*0000*/ uint16_t dropId;                        // ID assigned to drop
/*0002*/ uint8_t  unknown0002[2];                // ***Placeholder
/*0004*/ uint16_t spawnId;                       // ID of player picking item up
/*0006*/ uint8_t  unknown0006[2];                // ***Placeholder
/*0008*/ uint8_t  unknown0008[4];                // added 8/21/2019
/*0012*/
};

/*
** Consider Struct
** Length: 28 Octets
** OpCode: considerCode
*/

struct considerStruct
{
/*0000*/ uint32_t playerid;                      // PlayerID
/*0004*/ uint32_t targetid;                      // TargetID
/*0008*/ int32_t  faction;                       // Faction
/*0012*/ int32_t  level;                         // Level
/*0016*/ int32_t  unknown0016;                   // unknown
/*0020*/ int32_t  unknown0020;                   // unknown (rarity?)
/*0024*/ int32_t  unknown0024;                   // unknown
/*0028*/
};

/*
** Spell Casted On
** Length: 36 Octets
** OpCode: castOnCode
*/

struct castOnStruct
{
/*0000*/ uint16_t targetId;                      // Target ID
/*0002*/ uint8_t  unknown0002[2];                // ***Placeholder
/*0004*/ int16_t  sourceId;                      // ***Source ID
/*0006*/ uint8_t  unknown0006[2];                // ***Placeholder
/*0008*/ uint8_t  unknown0008[24];               // might be some spell info?
/*0032*/ uint16_t spellId;                       // Spell Id
/*0034*/ uint8_t  unknown0034[2];                // ***Placeholder
/*0036*/
};

/*
** Spawn Death Blow
** Length: 40 Octets
** OpCode: NewCorpseCode
*/

// EQ Mac OP_Death — 20 bytes. From eq_packet_structs.h::Death_Struct.
struct newCorpseStruct
{
/*0000*/ uint16_t spawnId;
/*0002*/ uint16_t killerId;
/*0004*/ uint16_t corpseid;
/*0006*/ uint8_t  spawn_level;
/*0007*/ uint8_t  unknown007;
/*0008*/ int16_t  spellId;
/*0010*/ uint8_t  attack_skill;
/*0011*/ uint8_t  unknown011;
/*0012*/ int32_t  damage;
/*0016*/ uint8_t  is_PC;
/*0017*/ uint8_t  unknown015[3];
/*0020*/
};


/*
** Money Loot
** Length: 24 Octets
** OpCode: MoneyOnCorpseCode
*/

// EQ Mac OP_MoneyOnCorpse — 20 bytes. From eq_packet_structs.h.
struct moneyOnCorpseStruct
{
/*0000*/ uint8_t  response;                      // 0=someone else is, 1=OK, 2=not yet
/*0001*/ uint8_t  unknown1;                      // 0x5a
/*0002*/ uint8_t  unknown2;                      // 0x40
/*0003*/ uint8_t  unknown3;                      // 0
/*0004*/ uint32_t platinum;
/*0008*/ uint32_t gold;
/*0012*/ uint32_t silver;
/*0016*/ uint32_t copper;
/*0020*/
};

/*
** Stamina
** Length: 8 Octets
** OpCode: staminaCode
*/

// EQ Mac OP_Stamina — 8 bytes. From eq_packet_structs.h::Stamina_Struct.
struct staminaStruct
{
/*0000*/ int16_t  food;                          // 0..32000
/*0002*/ int16_t  water;                         // 0..32000
/*0004*/ int8_t   fatigue;                       // 0..100
/*0005*/ uint8_t  pad05;
/*0006*/ uint8_t  pad06;
/*0007*/ uint8_t  pad07;
/*0008*/
};

/*
** Battle Code
** Length: 30 Octets
** OpCode: ActionCode
*/

// This can be used to gather info on spells cast on us

// EQ Mac OP_Action — 36 bytes. From eq_packet_structs.h::Action_Struct.
struct actionStruct
{
/*0000*/ uint16_t target;                        // Target entity id
/*0002*/ uint16_t source;                        // Caster entity id
/*0004*/ uint16_t level;                         // Caster level (or potion-only)
/*0006*/ uint16_t target_level;
/*0008*/ int32_t  instrument_mod;                // 10 default; bard songs
/*0012*/ float    force;                         // Push force
/*0016*/ float    sequence;                      // Push heading
/*0020*/ float    pushup_angle;                  // Push pitch
/*0024*/ uint8_t  type;                          // 231 for spells; melee bashes etc.
/*0025*/ uint8_t  unknown25;
/*0026*/ uint16_t spell_id_unused;
/*0028*/ int16_t  tap_amount;
/*0030*/ uint16_t spell;                         // Spell id (real one)
/*0032*/ uint8_t  unknown32;
/*0033*/ uint8_t  buff_unknown;                  // 1=start, 4=success
/*0034*/ uint16_t unknown34;
/*0036*/
};

// EQ Mac OP_Damage — 24 bytes. From eq_packet_structs.h::Damage_Struct.
// Carries the actual damage amount; melee swings, dots, environmental,
// etc. all flow through this opcode after OP_Action announces the cast.
struct damageStruct
{
/*0000*/ uint16_t target;
/*0002*/ uint16_t source;
/*0004*/ uint16_t type;                          // damage type (skill id / spell category)
/*0006*/ uint16_t spellid;
/*0008*/ int32_t  damage;                        // negative = heal
/*0012*/ float    force;
/*0016*/ float    sequence;
/*0020*/ float    pushup_angle;
/*0024*/
};

/*
** client changes target struct
** Length: 4 Octets
** OpCode: clientTargetCode
*/

// EQ Mac OP_TargetMouse — 2 bytes. From eq_packet_structs.h::ClientTarget_Struct.
struct clientTargetStruct
{
/*0000*/ uint16_t newTarget;                     // Target ID
/*0002*/
};

/*
** Info sent when you start to cast a spell
** Length: 39 Octets
** OpCode: StartCastCode
*/

// EQ Mac OP_CastSpell — 12 bytes. From eq_packet_structs.h::CastSpell_Struct.
// Field names re-aliased to legacy showeq names where slots reference them.
struct startCastStruct
{
/*0000*/ uint16_t slot;                          // Spell slot
/*0002*/ uint16_t spellId;                       // Spell id
/*0004*/ uint16_t inventoryslot;                 // 0xFFFF = normal cast, else clicky item slot
/*0006*/ uint16_t targetId;
/*0008*/ uint32_t spell_crc;
/*0012*/
};

/*
** New Mana Amount
** Length: 20 Octets
** OpCode: manaDecrementCode
*/

// EQ Mac OP_ManaChange — 4 bytes. From eq_packet_structs.h::ManaChange_Struct.
struct manaDecrementStruct
{
/*0000*/ uint16_t newMana;                       // New mana amount
/*0002*/ uint16_t spellId;                       // Last spell cast
/*0004*/
};


/*
** Spell Fade Struct
** Length: Variable length
** OpCode: SpellFadedCode
*/
struct spellFadedStruct
{
/*0000*/ uint32_t color;                         // color of the spell fade message
/*0004*/ char     message[0];                    // fade message
/*0???*/ uint8_t  paddingXXX[3];                 // always 0's 
};

/*
** Spell Action Struct
** Length: 11 Octets
** OpCode: BeginCastCode
*/
// EQ Mac OP_BeginCast — 8 bytes. From eq_packet_structs.h::BeginCast_Struct.
// `param1` retains the showeq legacy name; semantically it is `cast_time`
// in milliseconds.
struct beginCastStruct
{
/*0000*/ uint16_t spawnId;                       // Caster's spawn id
/*0002*/ uint16_t spellId;                       // Id of spell being cast
/*0004*/ uint16_t param1;                        // Was `cast_time`: milliseconds
/*0006*/ uint16_t unknown;
/*0008*/
};

/*
** Spell Action Struct
** Length: 16 Octets
** OpCode: MemSpellCode
*/

// EQ Mac OP_MemorizeSpell — 12 bytes. From
// eq_packet_structs.h::MemorizeSpell_Struct. `param1` retains the showeq
// legacy field name; semantically it is `scribing` (0=scribe-to-book,
// 1=memorize, 2=forget, etc.).
struct memSpellStruct
{
/*0000*/ uint32_t slotId;                        // Spell book / memorized slot
/*0004*/ uint32_t spellId;                       // Spell id
/*0008*/ uint32_t param1;                        // Was `scribing`: 0=scribe, 1=mem, 2=forget
/*0012*/
};


/*
** Skill Increment
** Length: 12 Octets
** OpCode: SkillIncCode
*/

// EQ Mac OP_SkillUpdate — 8 bytes. From eq_packet_structs.h::SkillUpdate_Struct.
struct skillIncStruct
{
/*0000*/ uint32_t skillId;                       // Skill id
/*0004*/ int32_t  value;                         // New value of skill
/*0008*/
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 14 Octets
** Opcode: WearChangeCode
*/

// ZBTEMP: Find newItemID ***
struct wearChangeStruct
{
/*0000*/ uint16_t spawnId;                       // SpawnID
/*0002*/ Color_Struct color;                     // item color
/*0006*/ uint8_t  wearSlotId;                    // Slot ID
/*0007*/ uint8_t  unknown0007[7];                // unknown
/*0014*/
};

/*
** Level Update
** Length: 16 Octets
** OpCode: LevelUpUpdateCode
*/

// EQ Mac OP_LevelUpdate — 12 bytes. From
// EQMacEmu/common/eq_packet_structs.h::LevelUpdate_Struct.
struct levelUpUpdateStruct
{
/*0000*/ uint32_t level;                         // New level
/*0004*/ uint32_t levelOld;                      // Old level
/*0008*/ uint32_t exp;                           // Current Experience
/*0012*/
};

/*
** Experience Update
** Length: 16 Octets
** OpCode: ExpUpdateCode
*/

// EQ Mac OP_ExpUpdate — 4 bytes. From eq_packet_structs.h::ExpUpdate_Struct.
struct expUpdateStruct
{
/*0000*/ uint32_t exp;                           // experience value (x/330)
/*0004*/
};

/*
** Alternate Experience Update
** Length: 12 Octets
** OpCode: AltExpUpdateCode
*/
struct altExpUpdateStruct
{
/*0000*/ uint32_t altexp;                        // alt exp x/330
/*0004*/ uint32_t aapoints;                      // current number of AA points
/*0008*/ uint8_t  percent;                       // percentage in integer form
/*0009*/ uint8_t  unknown0009[3];                // ***Place Holder
/*0012*/
};


/*
** Player Spawn Update
** Length: 27 Octets
** OpCode: SpawnUpdateCode
*/

// EQ Mac OP_WearChange body — 12 bytes. Layout from
// EQMacEmu/common/eq_packet_structs.h::WearChange_Struct.
struct SpawnUpdateStruct
{
/*0000*/ uint16_t spawnId;                       // ID of changed spawn
/*0002*/ uint8_t  wear_slot_id;                  // Equipment slot index
/*0003*/ uint8_t  align03;                       // padding
/*0004*/ uint16_t material;                      // Material/model id
/*0006*/ uint16_t align06;                       // padding
/*0008*/ uint32_t color;                         // Tint as packed uint32 (b/g/r/use_tint)
/*0012*/
};

/*
** NPC Hp Update
** Length: 18 Octets
** Opcode NpcHpUpdateCode
*/

// EQ Mac OP_HPUpdate body (12 bytes). Layout from
// EQMacEmu/common/patches/mac_structs.h::SpawnHPUpdate_Struct.
struct hpNpcUpdateStruct
{
/*0000*/ uint32_t spawnId;                       // Spawn id
/*0004*/ int32_t  curHP;                         // Current HP
/*0008*/ int32_t  maxHP;                         // Maximum HP
/*0012*/
};

/*
** Inspecting Information
** Length: 1956 Octets
** OpCode: InspectDataCode
*/

struct inspectDataStruct
{
/*0000*/ uint8_t  unknown0000[4];                // ***Placeholder
/*0004*/ uint32_t spawnId;                       // Id of spawn inspected
/*0008*/ char     itemNames[23][64];             // 23 items with names 
                                                 // 64 characters long.
/*1480*/ int32_t  icons[23];                     // Icon Information
/*1572*/ char     mytext[200];                   // Player Defined Text Info
/*1772*/ uint8_t  unknown1772[184];              // ***Placeholder
/*1956*/
};


/*
** Interrupt Casting
** Length: 6 Octets + Variable Length Octets
** Opcode: BadCastCode
*/

struct badCastStruct
{
/*0000*/ uint32_t spawnId;                       // Id of who is casting
/*0004*/ char     message[0];                    // Text Message
};

/*
** Random Number Request
** Length: 8 Octets
** OpCode: RandomCode
*/
struct randomReqStruct 
{
/*0000*/ uint32_t bottom;                        // Low number
/*0004*/ uint32_t top;                           // High number
/*0008*/
};

/*
** Random Number Result
** Length: 76 Octets
** OpCode: RandomCode
*/
struct randomStruct 
{
/*0000*/ uint32_t bottom;                        // Low number
/*0004*/ uint32_t top;                           // High number
/*0008*/ uint32_t result;                        // result number
/*0012*/ char     name[64];                      // name rolled by
/*0076*/
};

/*
** Player Position Update
** Length: 28 Octets
** OpCode: PlayerPosCode
*/
// EQ Mac OP_ClientUpdate carries a single 15-byte spawnPositionUpdate for
// both directions (server-broadcast of other players' moves and client-sent
// self-position). Aliasing instead of a separate post-EQMac layout.
using playerSpawnPosStruct = spawnPositionUpdate;

/*
** Self Position Update
** Length: 42 Octets
** OpCode: PlayerPosCode
*/
// EQ Mac self-position update: same 15-byte spawnPositionUpdate as everyone
// else's. The post-EQMac layout (42 bytes with floats) was a later
// generation of the protocol.
using playerSelfPosStruct = spawnPositionUpdate;

/*
** Spawn Appearance
** Length: 8 Octets
** OpCode: spawnAppearanceCode
*/

struct spawnAppearanceStruct
{
/*0000*/ uint16_t spawnId;                       // ID of the spawn
/*0002*/ uint16_t type;                          // Type of data sent
/*0004*/ uint32_t parameter;                     // Values associated with the type
/*0008*/
};








struct moneyUpdateStruct
{
/*0000*/ uint32_t spawnid;                       // ***Placeholder
/*0004*/ uint32_t cointype;                      // Coin Type
/*0008*/ uint32_t amount;                        // Amount
/*0012*/
};





struct tradeSpellBookSlotsStruct
{
/*0000*/ uint32_t slot1;
/*0004*/ uint32_t slot2;
/*0008*/
};




/*
** buffStruct
** Length: 168 Octets
** 
*/

// EQ Mac OP_Buff body — 20 bytes. From
// EQMacEmu/common/eq_packet_structs.h::SpellBuffFade_Struct.
// Field names follow the showeq legacy where slots reference them
// (spawnid, spellid, spellslot, changetype).
struct buffStruct
{
/*0000*/ uint16_t spawnid;                       // entityid
/*0002*/ uint8_t  bufftype;
/*0003*/ uint8_t  level;                         // caster level
/*0004*/ uint8_t  bard_modifier;
/*0005*/ uint8_t  activated;
/*0006*/ uint16_t spellid;
/*0008*/ uint16_t duration;                      // ticks remaining
/*0010*/ uint16_t counters;                      // poison/disease/curse counter or rune amount
/*0012*/ uint16_t spellslot;                     // slot_number (buff window slot)
/*0014*/ uint16_t unk14;
/*0016*/ uint32_t changetype;                    // bufffade: 1=remove, 3=replace, else=update
/*0020*/
};

/*
** Guild Member Update structure 
** Length: 88 Octets
**
*/

struct GuildMemberUpdate
{
/*000*/ uint32_t guildId;                        // guild id
/*004*/ uint8_t  unknown004[4];			         // 4 bytes added 11/16/16
/*008*/ char     name[64];                       // member name
/*072*/ uint16_t zoneId;                         // zone id 
/*074*/ uint16_t zoneInstance;                   // zone instance
/*076*/ uint32_t lastOn;                         // time the player was last on.
/*080*/ uint8_t  unknown080[8];                  // 4 bytes added 11/28/12, +4 added 11/16/16
/*088*/
};



/*
** Item Bazaar Search Result
** Length: 160 Octets
** OpCode: BazaarSearch
*/
struct bazaarSearchResponseStruct 
{
/*0000*/ uint32_t mark;                          // ***unknown***
/*0004*/ uint32_t player_id;                     // trader ID
/*0008*/ char     merchant_name[64];             // trader name
/*0072*/ uint32_t count;                         // Count of items for sale
/*0076*/ uint32_t item_id;                       // ID of item for sale
/*0080*/ uint8_t uknown0080[8];                  // ***unknown***
/*0088*/ char     item_name[64];                 // nul-padded name with appended "(count)"
/*0152*/ uint32_t price;                         // price in copper
/*0156*/ uint8_t uknown0156[4];                  // ***unknown***
/*0160*/
};

/*
bazaarSearchResponseStruct as of 03/13/19
Beginning of packet includes:

	uint32_t player_id;                      // player ID
	uint8_t uknown0004[10];                  // ***unknown***

If there are multiple results, they use the following repeating struct:

		uint8_t uknown0014[21];                 // ***unknown***
		uint32_t price;                         // price in copper
		uint32_t count;                         // Count of items for sale
		uint32_t item_id;                       // ID of item for sale
		uint32_t icon_id;                       // Icon of item for sale
		char     item_name[64];                 // null termintated (00) item name
		uint32_t uknownXXXX;                    // ***unknown***
*/


/*******************************/
/* World Server Structs        */



struct worldMOTDStruct
{
  /*002*/ char    message[0];
  /*???*/ uint8_t unknownXXX[3];
};

// Restore structure packing to default
#pragma pack()

#endif // EQSTRUCT_H

//. .7...6....,X....D4.M.\.....P.v..>..W....
//123456789012345678901234567890123456789012
//000000000111111111122222222223333333333444
