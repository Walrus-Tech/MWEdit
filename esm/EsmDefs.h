/*===========================================================================
 *
 * File:    Esmdefs.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 5, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMDEFS_H
#define __ESMDEFS_H


#include "dl_err.h"


/* Number of enchantments for alchemy and enchant items */
#define MWESM_MAX_ENCHANTS       8

/* ESM record and sub-record name length */
#define MWESM_TYPE_SIZE          4

/* Maximum length of IDs */
#define MWESM_ID_MAXSIZE         32
#define MWESM_ID_MAXSIZE2        64

/* Number of magic effects/skills/etc.... */
#define MWESM_MAX_EFFECTS        143
#define MWESM_MAX_SKILLS         27
#define MWESM_MAX_ATTRIBUTES     8

/* Biped body part IDs */
#define MWESM_BIPEDPART_MIN      0
#define MWESM_BIPEDPART_MAX      26

/* Fields for general list output */
#define ESM_FIELD_ID             200
#define ESM_FIELD_COUNT          1
#define ESM_FIELD_NAME           2
#define ESM_FIELD_SCRIPT         3
#define ESM_FIELD_MODEL          4
#define ESM_FIELD_INVENTORY      5
#define ESM_FIELD_ICON           ESM_FIELD_INVENTORY
#define ESM_FIELD_PERSIST        6
#define ESM_FIELD_BLOCKED        7
#define ESM_FIELD_WEIGHT         8
#define ESM_FIELD_COST           9
#define ESM_FIELD_VALUE          10
#define ESM_FIELD_AUTOCALC       11
#define ESM_FIELD_TYPE           12
#define ESM_FIELD_QUALITY        13
#define ESM_FIELD_CLASS          14
#define ESM_FIELD_HEALTH         15
#define ESM_FIELD_ENCHANT        16
#define ESM_FIELD_ENCHANTPTS     17
#define ESM_FIELD_RATING         18
#define ESM_FIELD_RACE           19
#define ESM_FIELD_PART           20
#define ESM_FIELD_FEMALE         21
#define ESM_FIELD_PLAYABLE       22
#define ESM_FIELD_CHANGED        23
#define ESM_FIELD_SCROLL         24
#define ESM_FIELD_TEACHES        25
#define ESM_FIELD_ORGANIC        26
#define ESM_FIELD_RESPAWN        27
#define ESM_FIELD_ITEMLIST       28
#define ESM_FIELD_SOUND          29
#define ESM_FIELD_LEVEL          30
#define ESM_FIELD_ESSENTIAL      31
#define ESM_FIELD_MOVEMENT       32
#define ESM_FIELD_WEAPSHLD       33
#define ESM_FIELD_WEAPSHIELD     ESM_FIELD_WEAPSHLD
#define ESM_FIELD_BIPED          34
#define ESM_FIELD_BIPEDAL        ESM_FIELD_BIPED
#define ESM_FIELD_CHARGE         35
#define ESM_FIELD_EFFECT1        36
#define ESM_FIELD_EFFECT2        37
#define ESM_FIELD_EFFECT3        38
#define ESM_FIELD_EFFECT4        39
#define ESM_FIELD_ALLPC          40
#define ESM_FIELD_LIST           41
#define ESM_FIELD_TIME           42
#define ESM_FIELD_RADIUS         43
#define ESM_FIELD_USES           44
#define ESM_FIELD_FACTION        45
#define ESM_FIELD_RANK           46
#define ESM_FIELD_ANIMATION      47
#define ESM_FIELD_PCSTART        48
#define ESM_FIELD_SPEED          49
#define ESM_FIELD_REACH          50
#define ESM_FIELD_CHOPMIN        51
#define ESM_FIELD_CHOPMAX        52
#define ESM_FIELD_THRUSTMIN      53
#define ESM_FIELD_THRUSTMAX      54
#define ESM_FIELD_SLASHMIN       55
#define ESM_FIELD_SLASHMAX       56
#define ESM_FIELD_IGNORERESIST   57
#define ESM_FIELD_SKILL          58
#define ESM_FIELD_TEXT           59
#define ESM_FIELD_CHANCENONE     60
#define ESM_FIELD_CALCEACH       61
#define ESM_FIELD_UNKNOWN        62
#define ESM_FIELD_ITEMTYPE       63
#define ESM_FIELD_CUSTOM         64
#define ESM_FIELD_VOLUME         65
#define ESM_FIELD_MINRANGE       66
#define ESM_FIELD_MAXRANGE       67
#define ESM_FIELD_SCHOOL         69
#define ESM_FIELD_NPCID          70
#define ESM_FIELD_DISPOSITION    71
#define ESM_FIELD_NPCFACTION     72
#define ESM_FIELD_NPCCELL        73
#define ESM_FIELD_INFOFUNC1      74
#define ESM_FIELD_INFOFUNC2      75
#define ESM_FIELD_INFOFUNC3      76
#define ESM_FIELD_INFOFUNC4      77
#define ESM_FIELD_INFOFUNC5      78
#define ESM_FIELD_INFOFUNC6      79
#define ESM_FIELD_ATTRIBUTE      80
#define ESM_FIELD_CREATURE       81
#define ESM_FIELD_REGION         82
#define ESM_FIELD_GRID           83
#define ESM_FIELD_REFCOUNT       84
#define ESM_FIELD_USERDATA       85
#define ESM_FIELD_TOPIC          86
#define ESM_FIELD_PREV           87
#define ESM_FIELD_NEXT           88
#define ESM_FIELD_CELLX          89
#define ESM_FIELD_CELLY          90
#define ESM_FIELD_CELL           91
#define ESM_FIELD_DATA           92
#define ESM_FIELD_DELETE         93
#define ESM_FIELD_DESC           94
#define ESM_FIELD_EFFECT         95
#define ESM_FIELD_ITEM           96 /* Fields added v0.5.6 */
#define ESM_FIELD_ITEMEX         97
#define ESM_FIELD_SPELL          98
#define ESM_FIELD_HEAD           99
#define ESM_FIELD_HAIR           100
#define ESM_FIELD_BLOOD          101
#define ESM_FIELD_STRENGTH       102
#define ESM_FIELD_AGILITY        103
#define ESM_FIELD_ENDURANCE      104
#define ESM_FIELD_LUCK           105
#define ESM_FIELD_PERSONALITY    106
#define ESM_FIELD_WILLPOWER      107
#define ESM_FIELD_INTELLIGENCE   108
#define ESM_FIELD_GOLD           109
#define ESM_FIELD_FATIGUE        110
#define ESM_FIELD_SPELLPTS       111
#define ESM_FIELD_FIGHT          112
#define ESM_FIELD_ALARM          113
#define ESM_FIELD_FLEE           114
#define ESM_FIELD_HELLO          115
#define ESM_FIELD_NPCAPPARATUS   116
#define ESM_FIELD_NPCARMORS      117
#define ESM_FIELD_NPCBOOKS       118
#define ESM_FIELD_NPCCLOTHING    119
#define ESM_FIELD_NPCINGREDIANTS 120
#define ESM_FIELD_NPCLIGHTS      121
#define ESM_FIELD_NPCLOCKPICKS   122
#define ESM_FIELD_NPCMISC        123
#define ESM_FIELD_NPCPROBES      124
#define ESM_FIELD_NPCPOTIONS     125
#define ESM_FIELD_NPCREPAIRITEMS 126
#define ESM_FIELD_NPCMAGICITEMS  127
#define ESM_FIELD_NPCSPELLS      128
#define ESM_FIELD_NPCWEAPONS     129
#define ESM_FIELD_TRADEGOLD      130
#define ESM_FIELD_NPCENCHANT     131
#define ESM_FIELD_NPCSPELLMAKER  132
#define ESM_FIELD_NPCTRAINING    133
#define ESM_FIELD_NPCREPAIRS     134
#define ESM_FIELD_NPCTRAVEL1     135
#define ESM_FIELD_NPCTRAVEL2     136
#define ESM_FIELD_NPCTRAVEL3     137
#define ESM_FIELD_NPCTRAVEL4     138

/* Special columns */
#define ESMSUBLIST_FIELD_MOD     0x1000
#define ESMSUBLIST_FIELD_INDEX   0x1100
#define ESMSUBLIST_FIELD_MASK    0xFF00

/* Record names */
#define MWESM_REC_ACTI _T("ACTI")
#define MWESM_REC_ALCH _T("ALCH")
#define MWESM_REC_APPA _T("APPA")
#define MWESM_REC_ARMO _T("ARMO")
#define MWESM_REC_BSGN _T("BSGN")
#define MWESM_REC_BODY _T("BODY")
#define MWESM_REC_BOOK _T("BOOK")
#define MWESM_REC_CELL _T("CELL")
#define MWESM_REC_CLAS _T("CLAS")
#define MWESM_REC_CLOT _T("CLOT")
#define MWESM_REC_CONT _T("CONT")
#define MWESM_REC_CREA _T("CREA")
#define MWESM_REC_DIAL _T("DIAL")
#define MWESM_REC_DOOR _T("DOOR")
#define MWESM_REC_ENCH _T("ENCH")
#define MWESM_REC_FACT _T("FACT")
#define MWESM_REC_GLOB _T("GLOB")
#define MWESM_REC_GMST _T("GMST")
#define MWESM_REC_INFO _T("INFO")
#define MWESM_REC_INGR _T("INGR")
#define MWESM_REC_LAND _T("LAND")
#define MWESM_REC_LEVC _T("LEVC")
#define MWESM_REC_LEVI _T("LEVI")
#define MWESM_REC_LIGH _T("LIGH")
#define MWESM_REC_LOCK _T("LOCK")
#define MWESM_REC_MGEF _T("MGEF")
#define MWESM_REC_MISC _T("MISC")
#define MWESM_REC_NPC_ _T("NPC_")
#define MWESM_REC_PROB _T("PROB")
#define MWESM_REC_RACE _T("RACE")
#define MWESM_REC_REGN _T("REGN")
#define MWESM_REC_REPA _T("REPA")
#define MWESM_REC_SCPT _T("SCPT")
#define MWESM_REC_SCRI _T("SCRI")
#define MWESM_REC_SKIL _T("SKIL")
#define MWESM_REC_SNDG _T("SNDG")
#define MWESM_REC_SOUN _T("SOUN")
#define MWESM_REC_SPEL _T("SPEL")
#define MWESM_REC_SSCR _T("SSCR")
#define MWESM_REC_STAT _T("STAT")
#define MWESM_REC_WEAP _T("WEAP")
#define MWESM_REC_TES3 _T("TES3")

/* Subrecord types */
#define MWESM_SUBREC_AADT _T("AADT")
#define MWESM_SUBREC_AI_A _T("AI_A")
#define MWESM_SUBREC_AI_E _T("AI_E")
#define MWESM_SUBREC_AI_F _T("AI_F")
#define MWESM_SUBREC_AI_T _T("AI_T")
#define MWESM_SUBREC_AI_W _T("AI_W")
#define MWESM_SUBREC_AIDT _T("AIDT")
#define MWESM_SUBREC_ALDT _T("ALDT")
#define MWESM_SUBREC_AMBI _T("AMBI")
#define MWESM_SUBREC_ANAM _T("ANAM")
#define MWESM_SUBREC_AODT _T("AODT")
#define MWESM_SUBREC_ASND _T("ASND")
#define MWESM_SUBREC_AVFX _T("AVFX")
#define MWESM_SUBREC_BKDT _T("BKDT")
#define MWESM_SUBREC_BNAM _T("BNAM")
#define MWESM_SUBREC_BSND _T("BSND")
#define MWESM_SUBREC_BVFX _T("BVFX")
#define MWESM_SUBREC_BYDT _T("BYDT")
#define MWESM_SUBREC_CLDT _T("CLDT")
#define MWESM_SUBREC_CNAM _T("CNAM")
#define MWESM_SUBREC_CNDT _T("CNDT")
#define MWESM_SUBREC_CSND _T("CSND")
#define MWESM_SUBREC_CTDT _T("CTDT")
#define MWESM_SUBREC_CVFX _T("CVFX")
#define MWESM_SUBREC_DATA _T("DATA")
#define MWESM_SUBREC_DELE _T("DELE")
#define MWESM_SUBREC_DESC _T("DESC")
#define MWESM_SUBREC_DNAM _T("DNAM")
#define MWESM_SUBREC_DODT _T("DODT")
#define MWESM_SUBREC_ENAM _T("ENAM")
#define MWESM_SUBREC_ENDT _T("ENDT")
#define MWESM_SUBREC_FADT _T("FADT")
#define MWESM_SUBREC_FNAM _T("FNAM")
#define MWESM_SUBREC_FLAG _T("FLAG")
#define MWESM_SUBREC_FLTV _T("FLTV")
#define MWESM_SUBREC_FRMR _T("FRMR")
#define MWESM_SUBREC_HEDR _T("HEDR")
#define MWESM_SUBREC_HSND _T("HSND")
#define MWESM_SUBREC_HVFX _T("HVFX")
#define MWESM_SUBREC_INAM _T("INAM")
#define MWESM_SUBREC_INDX _T("INDX")
#define MWESM_SUBREC_INTV _T("INTV")
#define MWESM_SUBREC_IRDT _T("IRDT")
#define MWESM_SUBREC_ITEX _T("ITEX")
#define MWESM_SUBREC_KNAM _T("KNAM")
#define MWESM_SUBREC_LHDT _T("LHDT")
#define MWESM_SUBREC_LKDT _T("LKDT")
#define MWESM_SUBREC_MAST _T("MAST")
#define MWESM_SUBREC_MCDT _T("MCDT")
#define MWESM_SUBREC_MEDT _T("MEDT")
#define MWESM_SUBREC_MODL _T("MODL")
#define MWESM_SUBREC_NAME _T("NAME")
#define MWESM_SUBREC_NAM0 _T("NAM0")
#define MWESM_SUBREC_NAM5 _T("NAM5")
#define MWESM_SUBREC_NAM9 _T("NAM9")
#define MWESM_SUBREC_NNAM _T("NNAM")
#define MWESM_SUBREC_NPCO _T("NPCO")
#define MWESM_SUBREC_NPCS _T("NPCS")
#define MWESM_SUBREC_NPDT _T("NPDT") /* For NPCs */
#define MWESM_SUBREC_CRDT _T("NPDT") /* For creatures */
#define MWESM_SUBREC_ONAM _T("ONAM")
#define MWESM_SUBREC_PBDT _T("PBDT")
#define MWESM_SUBREC_PNAM _T("PNAM")
#define MWESM_SUBREC_PTEX _T("PTEX")
#define MWESM_SUBREC_QSTF _T("QSTF")
#define MWESM_SUBREC_QSTN _T("QSTN")
#define MWESM_SUBREC_QSTR _T("QSTR")
#define MWESM_SUBREC_RADT _T("RADT")
#define MWESM_SUBREC_RIDT _T("RIDT")
#define MWESM_SUBREC_RNAM _T("RNAM")
#define MWESM_SUBREC_RGNN _T("RGNN")
#define MWESM_SUBREC_SCHD _T("SCHD")
#define MWESM_SUBREC_SCDT _T("SCDT")
#define MWESM_SUBREC_SCTX _T("SCTX")
#define MWESM_SUBREC_SCRI _T("SCRI")
#define MWESM_SUBREC_SCVR _T("SCVR")
#define MWESM_SUBREC_SKDT _T("SKDT")
#define MWESM_SUBREC_SNAM _T("SNAM")
#define MWESM_SUBREC_SPDT _T("SPDT")
#define MWESM_SUBREC_STRV _T("STRV")
#define MWESM_SUBREC_TEXT _T("TEXT")
#define MWESM_SUBREC_TNAM _T("TNAM")
#define MWESM_SUBREC_UNAM _T("UNAM")
#define MWESM_SUBREC_VCLR _T("VCLR")
#define MWESM_SUBREC_VHGT _T("VHGT")
#define MWESM_SUBREC_VNML _T("VNML")
#define MWESM_SUBREC_VTEX _T("VTEX")
#define MWESM_SUBREC_WEAT _T("WEAT")
#define MWESM_SUBREC_WHGT _T("WHGT")
#define MWESM_SUBREC_WNAM _T("WNAM")
#define MWESM_SUBREC_WPDT _T("WPDT")
#define MWESM_SUBREC_XSCL _T("XSCL")
#define MWESM_SUBREC_XSOL _T("XSOL")

/* Not an actual sub-record, used for cell reference objects  */
#define MWESM_SUBREC_CREF _T("CREF")

/* Skills */
#define MWESM_SKILL_MIN              0
#define MWESM_SKILL_BLOCK            0
#define MWESM_SKILL_ARMORER          1
#define MWESM_SKILL_MEDIUMARMOR      2
#define MWESM_SKILL_HEAVYARMOR       3
#define MWESM_SKILL_BLUNTWEAPON      4
#define MWESM_SKILL_LONGBLADE        5
#define MWESM_SKILL_AXE              6
#define MWESM_SKILL_SPEAR            7
#define MWESM_SKILL_ATHLETICS        8
#define MWESM_SKILL_ENCHANT          9
#define MWESM_SKILL_DESTRUCTION      10
#define MWESM_SKILL_ALTERATION       11
#define MWESM_SKILL_ILLUSION         12
#define MWESM_SKILL_CONJURATION      13
#define MWESM_SKILL_MYSTICISM        14
#define MWESM_SKILL_RESTORATION      15
#define MWESM_SKILL_ALCHEMY          16
#define MWESM_SKILL_UNARMORED        17
#define MWESM_SKILL_SECURITY         18
#define MWESM_SKILL_SNEAK            19
#define MWESM_SKILL_ACROBATICS       20
#define MWESM_SKILL_LIGHTARMOR       21
#define MWESM_SKILL_SHORTBLADE       22
#define MWESM_SKILL_MARKSMAN         23
#define MWESM_SKILL_MERCANTILET      24
#define MWESM_SKILL_SPEECHCRAFT      25
#define MWESM_SKILL_HANDTOHAND       26
#define MWESM_SKILL_MAX              26

/* Class specialization */
#define MWESM_CLASSSPEC_COMBAT       0
#define MWESM_CLASSSPEC_MAGIC        1
#define MWESM_CLASSSPEC_STEALTH      2

/* Magic effect IDs */
#define MWESM_EFFECT_MIN             0
#define MWESM_EFFECT_WATERBREATH     0
#define MWESM_EFFECT_SWIFTSWIM       1
#define MWESM_EFFECT_WATERWALK       2
#define MWESM_EFFECT_SHIELD          3
#define MWESM_EFFECT_FIRESHIELD      4
#define MWESM_EFFECT_LIGHTSHIELD     5
#define MWESM_EFFECT_FROSTSHIELD     6
#define MWESM_EFFECT_BURDEN          7
#define MWESM_EFFECT_FEATHER         8
#define MWESM_EFFECT_JUMP            9
#define MWESM_EFFECT_LEVITATE        10
#define MWESM_EFFECT_SLOWFALL        11
#define MWESM_EFFECT_LOCK            12
#define MWESM_EFFECT_OPEN            13
#define MWESM_EFFECT_FIREDAMAGE      14
#define MWESM_EFFECT_SHOCKDAMAGE     15
#define MWESM_EFFECT_FROSTDAMAGE     16
#define MWESM_EFFECT_DRAINATTR       17
#define MWESM_EFFECT_DRAINHEALTH     18
#define MWESM_EFFECT_DRAINMAGIC      19
#define MWESM_EFFECT_DRAINFATIGUE    20
#define MWESM_EFFECT_DRAINSKILL      21
#define MWESM_EFFECT_DAMAGEATTR      22
#define MWESM_EFFECT_DAMAGEHEALTH    23
#define MWESM_EFFECT_DAMAGEMAGIC     24
#define MWESM_EFFECT_DAMAGEFATIGUE   25
#define MWESM_EFFECT_DAMAGESKILL     26
#define MWESM_EFFECT_POISON          27
#define MWESM_EFFECT_WEAKFIRE        28
#define MWESM_EFFECT_WEAKFROST       29
#define MWESM_EFFECT_WEAKSHOCK       30
#define MWESM_EFFECT_WEAKMAGIC       31
#define MWESM_EFFECT_WEAKDISEASE     32
#define MWESM_EFFECT_WEAKBLIGHT      33
#define MWESM_EFFECT_WEAKCORPRUS     34
#define MWESM_EFFECT_WEAKPOISON      35
#define MWESM_EFFECT_WEAKWEAPON      36
#define MWESM_EFFECT_DISTWEAPON      37
#define MWESM_EFFECT_DISTARMOR       38
#define MWESM_EFFECT_INVISIBLE       39
#define MWESM_EFFECT_CHAMELEON       40
#define MWESM_EFFECT_LIGHT           41
#define MWESM_EFFECT_SANCTUARY       42
#define MWESM_EFFECT_NIGHTEYE        43
#define MWESM_EFFECT_CHARM           44
#define MWESM_EFFECT_PARALYZE        45
#define MWESM_EFFECT_SILENCE         46
#define MWESM_EFFECT_BLIND           47
#define MWESM_EFFECT_SOUND           48
#define MWESM_EFFECT_CALMHUMAN       49
#define MWESM_EFFECT_CALMCREATURE    50
#define MWESM_EFFECT_FRENZYHUMAN     51
#define MWESM_EFFECT_FRENZYCREATURE  52
#define MWESM_EFFECT_DEMHUMAN        53
#define MWESM_EFFECT_DEMCREATURE     54
#define MWESM_EFFECT_RALLYHUMAN      55
#define MWESM_EFFECT_RALLYCREATURE   56
#define MWESM_EFFECT_DISPEL          57
#define MWESM_EFFECT_SOULTRAP        58
#define MWESM_EFFECT_TELEKINESIS     59
#define MWESM_EFFECT_MARK            60
#define MWESM_EFFECT_RECALL          61
#define MWESM_EFFECT_DIVINE          62
#define MWESM_EFFECT_ALMSIVI         63
#define MWESM_EFFECT_DETECTANIMAL    64
#define MWESM_EFFECT_DETECTENCHANT   65
#define MWESM_EFFECT_DETECTKEY       66
#define MWESM_EFFECT_SPELLABSORP     67
#define MWESM_EFFECT_REFLECT         68
#define MWESM_EFFECT_CUREDISEASE     69
#define MWESM_EFFECT_CUREBLIGHT      70
#define MWESM_EFFECT_CURECORPRUS     71
#define MWESM_EFFECT_CUREPOISON      72
#define MWESM_EFFECT_CUREPARALYSIS   73
#define MWESM_EFFECT_RESTOREATTR     74
#define MWESM_EFFECT_RESTOREHEALTH   75
#define MWESM_EFFECT_RESTOREMAGIC    76
#define MWESM_EFFECT_RESTOREFATIGUE  77
#define MWESM_EFFECT_RESTORESKILL    78
#define MWESM_EFFECT_FORTATTR        79
#define MWESM_EFFECT_FORTHEALTH      80
#define MWESM_EFFECT_FORTMAGIC       81
#define MWESM_EFFECT_FORTFATIGUE     82
#define MWESM_EFFECT_FORTSKILL       83
#define MWESM_EFFECT_FORTMAXMAGIC    84
#define MWESM_EFFECT_ABSORBATTR      85
#define MWESM_EFFECT_ABSORBHEALTH    86
#define MWESM_EFFECT_ABSORBMAGIC     87
#define MWESM_EFFECT_ABSORBFATIGUE   88
#define MWESM_EFFECT_ABSORBSKILL     89
#define MWESM_EFFECT_RESISTFIRE      90
#define MWESM_EFFECT_RESISTFROST     91
#define MWESM_EFFECT_RESISTSHOCK     92
#define MWESM_EFFECT_RESISTMAGIC     93
#define MWESM_EFFECT_RESISTDISEASE   94
#define MWESM_EFFECT_RESISTBLIGHT    95
#define MWESM_EFFECT_RESISTCORPRUS   96
#define MWESM_EFFECT_RESISTPOISON    97
#define MWESM_EFFECT_RESISTWEAPON    98
#define MWESM_EFFECT_RESISTPARALYSIS 99
#define MWESM_EFFECT_REMOVECURSE     100
#define MWESM_EFFECT_TURNUNDEAD      101
#define MWESM_EFFECT_SUMSCAMP        102
#define MWESM_EFFECT_SUMCLANFEAR     103
#define MWESM_EFFECT_SUMDAEDRA       104
#define MWESM_EFFECT_SUMDREMORA      105
#define MWESM_EFFECT_SUMGHOST        106
#define MWESM_EFFECT_SUMSKELETON     107
#define MWESM_EFFECT_SUMBONEWALKER   108
#define MWESM_EFFECT_SUMGBONEWALKER  109
#define MWESM_EFFECT_SUMBONELORD     110
#define MWESM_EFFECT_SUMTWILIGHT     111
#define MWESM_EFFECT_SUMHUNGER       112
#define MWESM_EFFECT_SUMSAINT        113
#define MWESM_EFFECT_SUMFLAMEATRO    114
#define MWESM_EFFECT_SUMFROSTATRO    115
#define MWESM_EFFECT_SUMSTORMATRO    116
#define MWESM_EFFECT_FORTATTACK      117
#define MWESM_EFFECT_COMCREATURE     118
#define MWESM_EFFECT_COMHUMAN        119
#define MWESM_EFFECT_BOUNDDAGGER     120
#define MWESM_EFFECT_BOUNDLONGSWORD  121
#define MWESM_EFFECT_BOUNDMACE       122
#define MWESM_EFFECT_BOUNDAXE        123
#define MWESM_EFFECT_BOUNDSPEAR      124
#define MWESM_EFFECT_BOUNDBOW        125
#define MWESM_EFFECT_EXTRASPELL      126
#define MWESM_EFFECT_BOUNDCUIRASS    127
#define MWESM_EFFECT_BOUNDHELM       128
#define MWESM_EFFECT_BOUNDBOOTS      129
#define MWESM_EFFECT_BOUNDSHIELD     130
#define MWESM_EFFECT_BOUNDGLOVES     131
#define MWESM_EFFECT_CORPRUS         132
#define MWESM_EFFECT_VAMPIRISM       133
#define MWESM_EFFECT_SUMMONSPHERE    134
#define MWESM_EFFECT_SUNDAMAGE       135
#define MWESM_EFFECT_STUNTMAGIC      136
#define MWESM_EFFECT_SUMFABRICANT    137
#define MWESM_EFFECT_SUMCREATURE01   138
#define MWESM_EFFECT_SUMCREATURE02   139
#define MWESM_EFFECT_SUMCREATURE03   140
#define MWESM_EFFECT_SUMCREATURE04   141
#define MWESM_EFFECT_SUMCREATURE05   142
#define MWESM_EFFECT_MAX             142

/* Spell effect flags */
#define MWESM_EFFECTFLAG_HASDUR      1
#define MWESM_EFFECTFLAG_HASMAG      2
#define MWESM_EFFECTFLAG_TRIB        4
#define MWESM_EFFECTFLAG_ALCHEMY     8
#define MWESM_EFFECTFLAG_SELFONLY    16
#define MWESM_EFFECTFLAG_NOSELF      32
#define MWESM_EFFECTFLAG_BLDM        64

/* Spell schools */
#define MWESM_SCHOOL_MIN             0
#define MWESM_SCHOOL_ALTERATION      0
#define MWESM_SCHOOL_CONJURATION     1
#define MWESM_SCHOOL_DESTRUCTION     2
#define MWESM_SCHOOL_ILLUSION        3
#define MWESM_SCHOOL_MYSTICISM       4
#define MWESM_SCHOOL_RESTORATION     5
#define MWESM_SCHOOL_MAX             5

/* Attribute indices */
#define MWESM_ATTRIBUTE_STR          0
#define MWESM_ATTRIBUTE_INT          1
#define MWESM_ATTRIBUTE_WIL          2
#define MWESM_ATTRIBUTE_AGI          3
#define MWESM_ATTRIBUTE_SPD          4
#define MWESM_ATTRIBUTE_END          5
#define MWESM_ATTRIBUTE_PER          6
#define MWESM_ATTRIBUTE_LUC          7

/* Skill indices */
#define MWESM_SKILL_BLOCK            0
#define MWESM_SKILL_ARMORER          1
#define MWESM_SKILL_MEDARMOR         2
#define MWESM_SKILL_HEAVYARMOR       3
#define MWESM_SKILL_BLUNT            4
#define MWESM_SKILL_LONGBLADE        5
#define MWESM_SKILL_AXE              6
#define MWESM_SKILL_SPEAR            7
#define MWESM_SKILL_ATHLETICS        8
#define MWESM_SKILL_ENCHANT          9
#define MWESM_SKILL_DESTRUCTION      10
#define MWESM_SKILL_ALTERATION       11
#define MWESM_SKILL_ILLUSION         12
#define MWESM_SKILL_CONJURATION      13
#define MWESM_SKILL_MYSTICISM        14
#define MWESM_SKILL_RESTORATION      15
#define MWESM_SKILL_ALCHEMY          16
#define MWESM_SKILL_UNARMORED        17
#define MWESM_SKILL_SECURITY         18
#define MWESM_SKILL_SNEAK            19
#define MWESM_SKILL_ACROBATICS       20
#define MWESM_SKILL_LIGHTARMOR       21
#define MWESM_SKILL_SHORTBLADE       22
#define MWESM_SKILL_MARKSMAN         23
#define MWESM_SKILL_MERCANTILE       24
#define MWESM_SKILL_SPEECHCRAFT      25
#define MWESM_SKILL_HANDTOHAND       26

/* File extensions and filters */
#define MWESM_SOUND_FILTER    _T("Sound Files (*.wav; *.mp3)|*.wav;*.mp3|WAV Files (*.wav)|*.wav|MP3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*||")
#define MWESM_SOUND_EXT       _T("WAV")
#define MWESM_MODEL_FILTER    _T("NIF Files (*.nif)|*.nif|All Files (*.*)|*.*||")
#define MWESM_MODEL_EXT       _T("NIF")
#define MWESM_ICON_FILTER     _T("Icon Files (*.dds;*.tga;*.bmp)|*.dds;*.tga;*.bmp|DDS Files (*.dds)|*.dds|TGA Files (*.tga)|*.tga|All Files (*.*)|*.*||")
#define MWESM_ICON_EXT        _T("TGA")
#define MWESM_TEXTURE_FILTER  _T("Texture Files (*.dds;*.tga;*.bmp)|*.dds;*.tga;*.bmp|DDS Files (*.dds)|*.dds|TGA Files (*.tga)|*.tga|All Files (*.*)|*.*||")
#define MWESM_TEXTURE_EXT     _T("TGA")

/* Relative Morrowind paths */
#define MWPATH_TEXTURES       _T("Textures\\")
#define MWPATH_MODELS         _T("Meshes\\")
#define MWPATH_SOUNDS         _T("Sound\\")
#define MWPATH_ICONS          _T("Icons\\")
#define MWPATH_DATA           _T("Data Files\\")
#define MWPATH_DATAFILES      MWPATH_DATA


/* Used to hold basic info on the magic effects */
typedef struct esmeffectdata {
	const TCHAR *Name;
	long Flags;
	const TCHAR *ID;

	bool IsID(const TCHAR *pString) {
		return _stricmp(ID, pString) == 0;
	}

	bool HasDuration() const {
		return (Flags & MWESM_EFFECTFLAG_HASDUR) != 0;
	}

	bool HasMagnitude() const {
		return (Flags & MWESM_EFFECTFLAG_HASMAG) != 0;
	}

	bool IsTribunal() const {
		return (Flags & MWESM_EFFECTFLAG_TRIB) != 0;
	}

	bool IsAlchemy() const {
		return (Flags & MWESM_EFFECTFLAG_ALCHEMY) != 0;
	}

	bool IsSelfOnly() const {
		return (Flags & MWESM_EFFECTFLAG_SELFONLY) != 0;
	}

	bool IsNotSelf() const {
		return (Flags & MWESM_EFFECTFLAG_NOSELF) != 0;
	}
} esmeffectdata_t;

/* Holds information on skills */
typedef struct esmskilldata {
	const TCHAR *Name;
	const TCHAR *Action1;
	const TCHAR *Action2;
	const TCHAR *Action3;
	const TCHAR *Action4;
} esmskilldata_t;

/* Holds information on animation groups */
typedef struct esmanimdata {
	const TCHAR *pName;
	short ID;
	short OldID;

	bool IsName(const TCHAR *pString) {
		return _stricmp(pName, pString) == 0;
	}
} esmanimdata_t;


/* Convert skill/effect/attribute/etc... IDs to a string */
const TCHAR *GetESMSkill(const int SkillID);
int GetESMSkill(const TCHAR *pString);
bool GetESMSkill(int &OutSkill, const TCHAR *pString);
const TCHAR *GetESMEffect(const int EffectID);
const TCHAR *GetESMAttribute(const int AttributeID);
bool GetESMAttribute(int &OutAttr, const TCHAR *pString);
int GetESMAttribute(const TCHAR *pString);
const TCHAR *GetESMSpellSchool(const int SpellSchool);
const TCHAR *GetESMClassSpec(const int Spec);
const TCHAR *GetESMSkillAction(const int SkillID, const int Action);
const TCHAR *GetMWBipedPartType(const int Type);

/* Get a magic effect data structure from the effect ID */
const esmeffectdata_t *GetESMEffectData(const int EffectID);
int GetESMEffectID(const TCHAR *pString);
bool GetESMEffectID(int &EffectID, const TCHAR *pString);
int FindESMEffectID(const TCHAR *pEffectID);

/* Convert a field string to an ID */
int GetEsmFieldID(const TCHAR *pString);
const TCHAR *GetEsmFieldName(const int FieldID);

/* Get animation group data */
short GetESMAnimGroupID(const TCHAR *pGroup);
short GetESMAnimGroupOldID(const TCHAR *pGroup);

/* Check the record basic type */
bool IsESMRecordCarryable(const TCHAR *pType);
bool IsESMRecordModel(const TCHAR *pType);

/* Check type of ESM effects */
bool IsESMAttributeEffect(const int EffectID);
bool IsESMSkillEffect(const int EffectID);

/* Remove the quotes from an ID string */
TCHAR *RemoveIDQuotes(TCHAR *pBuffer, const TCHAR *pID);


#endif
