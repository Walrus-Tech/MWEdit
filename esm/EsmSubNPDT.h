/*===========================================================================
 *
 * File:    EsmsubNPDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * For the NPDT data in the NPC records.
 *
 *=========================================================================*/
#ifndef __ESMSUBNPDT_H
#define __ESMSUBNPDT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* NPC flags */
#define MWESM_NPCFLAG_FEMALE      0x0001
#define MWESM_NPCFLAG_ESSENTIAL   0x0002
#define MWESM_NPCFLAG_RESPAWN     0x0004
#define MWESM_NPCFLAG_NONE        0x0008
#define MWESM_NPCFLAG_AUTOCALC    0x0010
#define MWESM_NPCFLAG_DEFAULT     0x0018

#define MWESM_NPCFLAG_BLOODRED    0x0000
#define MWESM_NPCFLAG_BLOODSKEL   0x0400
#define MWESM_NPCFLAG_BLOODMETAL  0x0800
#define MWESM_NPCFLAG_BLOODMASK   0x0F00

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	short Level;
	char Strength;
	char Intelligence;
	char Willpower;
	char Agility;
	char Speed;
	char Endurance;
	char Personality;
	char Luck;
	char Skills[MWESM_MAX_SKILLS];
	char Reputation;
	short Health;
	short SpellPts;
	short Fatigue;
	char Disposition;
	char FactionID;
	char Rank;
	char Unknown1;
	long Gold;
} npclongdata_t;

/* Auto-calc version */
typedef struct {
	short Level;
	char Disposition;
	char FactionID;
	char Rank;
	char Unknown1;
	char Unknown2;
	char Unknown3;
	long Gold;
} npcshortdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubNPDTS Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubNPDTS : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubNPDT();
	//virtual ~CEsmSubNPDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNPDTS);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(npcshortdata_t));
		m_RecordSize = sizeof(npcshortdata_t);
		memset(m_pData, 0, sizeof(npcshortdata_t));
	}

	/* Get class members */
	npcshortdata_t *GetNPCData (void) {
		return ((npcshortdata_t *) m_pData);
	}

	short GetLevel (void) {
		return (GetNPCData()->Level);
	}

	char GetDisposition (void) {
		return (GetNPCData()->Disposition);
	}

	char GetFactionID (void) {
		return (GetNPCData()->FactionID);
	}

	char GetRank (void) {
		return (GetNPCData()->Rank);
	}

	char GetUnknown1 (void) {
		return (GetNPCData()->Unknown1);
	}

	char GetUnknown2 (void) {
		return (GetNPCData()->Unknown2);
	}

	char GetUnknown3 (void) {
		return (GetNPCData()->Unknown3);
	}

	long GetGold (void) {
		return (GetNPCData()->Gold);
	}

	/* Set class members */
	void SetLevel (const short Value) {
		GetNPCData()->Level = Value;
	}

	void SetGold (const long Value) {
		GetNPCData()->Gold = Value;
	}

	void SetDisposition (const char Value) {
		GetNPCData()->Disposition = Value;
	}

	void SetFactionID (const char Value) {
		GetNPCData()->FactionID = Value;
	}

	void SetRank (const char Value) {
		GetNPCData()->Rank = Value;
	}

	void SetUnknown1 (const char Value) {
		GetNPCData()->Unknown1 = Value;
	}

	void SetUnknown2 (const char Value) {
		GetNPCData()->Unknown2 = Value;
	}

	void SetUnknown3 (const char Value) {
		GetNPCData()->Unknown3 = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubNPDT Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubNPDTL Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubNPDTL : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubNPDTL();
	//virtual ~CEsmSubNPDTL() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNPDTL);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(npclongdata_t));
		m_RecordSize = sizeof(npclongdata_t);
		memset(m_pData, 0, sizeof(npclongdata_t));
	}

	/* Get class members */
	npclongdata_t *GetNPCData (void) {
		return ((npclongdata_t *) m_pData);
	}

	short GetLevel (void) {
		return (GetNPCData()->Level);
	}

	char GetDisposition (void) {
		return (GetNPCData()->Disposition);
	}

	char GetFactionID (void) {
		return (GetNPCData()->FactionID);
	}

	char GetRank (void) {
		return (GetNPCData()->Rank);
	}

	char GetUnknown1 (void) {
		return (GetNPCData()->Unknown1);
	}

	long GetGold (void) {
		return (GetNPCData()->Gold);
	}

	char GetStrength (void) {
		return (GetNPCData()->Strength);
	}

	char GetIntelligence (void) {
		return (GetNPCData()->Intelligence);
	}

	char GetWillpower (void) {
		return (GetNPCData()->Willpower);
	}

	char GetAgility (void) {
		return (GetNPCData()->Agility);
	}

	char GetSpeed (void) {
		return (GetNPCData()->Speed);
	}

	char GetEndurance (void) {
		return (GetNPCData()->Endurance);
	}

	char GetPersonality (void) {
		return (GetNPCData()->Personality);
	}

	char GetLuck (void) {
		return (GetNPCData()->Luck);
	}

	char GetReputation (void) {
		return (GetNPCData()->Reputation);
	}

	short GetHealth (void) {
		return (GetNPCData()->Health);
	}

	short GetSpellPts (void) {
		return (GetNPCData()->SpellPts);
	}

	short GetFatigue (void) {
		return (GetNPCData()->Fatigue);
	}

	bool IsValidSkill (const int Index) {
		return (Index >= 0 && Index < MWESM_MAX_SKILLS);
	}

	char GetSkill (const int Index) {
		return (IsValidSkill(Index) ? GetNPCData()->Skills[Index] : 0);
	}

	/* Set class members */
	void SetLevel (const short Value) {
		GetNPCData()->Level = Value;
	}

	void SetGold (const long Value) {
		GetNPCData()->Gold = Value;
	}

	void SetDisposition (const char Value) {
		GetNPCData()->Disposition = Value;
	}

	void SetFactionID (const char Value) {
		GetNPCData()->FactionID = Value;
	}

	void SetRank (const char Value) {
		GetNPCData()->Rank = Value;
	}

	void SetUnknown1 (const char Value) {
		GetNPCData()->Unknown1 = Value;
	}

	void SetStrength (const char Value) {
		GetNPCData()->Strength = Value;
	}

	void SetIntelligence (const char Value) {
		GetNPCData()->Intelligence = Value;
	}

	void SetWillpower (const char Value) {
		GetNPCData()->Willpower = Value;
	}

	void SetAgility (const char Value) {
		GetNPCData()->Agility = Value;
	}

	void SetSpeed (const char Value) {
		GetNPCData()->Speed = Value;
	}

	void SetEndurance (const char Value) {
		GetNPCData()->Endurance = Value;
	}

	void SetPersonality (const char Value) {
		GetNPCData()->Personality = Value;
	}

	void SetLuck (const char Value) {
		GetNPCData()->Luck = Value;
	}

	void SetReputation (const char Value) {
		GetNPCData()->Reputation = Value;
	}

	void SetHealth (const short Value) {
		GetNPCData()->Health = Value;
	}

	void SetSpellPts (const short Value) {
		GetNPCData()->SpellPts = Value;
	}

	void SetFatigue (const short Value) {
		GetNPCData()->Fatigue = Value;
	}

	void SetSkill (const int Index, const char Value) {
		if (IsValidSkill(Index)) {
			GetNPCData()->Skills[Index] = Value;
		}
	}

};

/*===========================================================================
 *      End of Class CEsmSubNPDT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubaCRDT.H
 *=========================================================================*/
