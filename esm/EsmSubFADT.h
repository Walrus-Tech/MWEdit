/*===========================================================================
 *
 * File:    EsmsubFADT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBFADT_H
#define __ESMSUBFADT_H


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

/* Flags */
#define MWESM_FACTFLAG_HIDDEN     1

/* Default number of ranks */
#define MWESM_FACTION_NUMRANKS    10

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

/* Rank structure */
typedef struct {
	long Attribute1;
	long Attribute2;
	long Skill1;
	long Skill2;
	long Faction;
} rankdata_t;

typedef struct {
	long AttributeID1;
	long AttributeID2;
	rankdata_t RankData[MWESM_FACTION_NUMRANKS];
	long SkillID1;
	long SkillID2;
	long SkillID3;
	long SkillID4;
	long SkillID5;
	long SkillID6;
	long Unknown;
	long Flags;
} factiondata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubFADT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubFADT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubFADT();
	//virtual ~CEsmSubFADT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubFADT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(factiondata_t));
		m_RecordSize = sizeof(factiondata_t);
		memset(m_pData, 0, sizeof(factiondata_t));
		GetFactionData()->AttributeID1 = 0;
		GetFactionData()->AttributeID2 = 1;
		GetFactionData()->SkillID1 = 0;
		GetFactionData()->SkillID2 = 1;
		GetFactionData()->SkillID3 = 2;
		GetFactionData()->SkillID4 = 3;
		GetFactionData()->SkillID5 = 4;
		GetFactionData()->SkillID6 = 5;
		GetFactionData()->Unknown = -1;
	}

	/* Get class methods */
	factiondata_t *GetFactionData(void) {
		return ((factiondata_t *)m_pData);
	}

	long GetAttributeID1(void) {
		return (GetFactionData()->AttributeID1);
	}

	long GetAttributeID2(void) {
		return (GetFactionData()->AttributeID2);
	}

	long GetSkillID1(void) {
		return (GetFactionData()->SkillID1);
	}

	long GetSkillID2(void) {
		return (GetFactionData()->SkillID2);
	}

	long GetSkillID3(void) {
		return (GetFactionData()->SkillID3);
	}

	long GetSkillID4(void) {
		return (GetFactionData()->SkillID4);
	}

	long GetSkillID5(void) {
		return (GetFactionData()->SkillID5);
	}

	long GetSkillID6(void) {
		return (GetFactionData()->SkillID6);
	}

	long GetUnknown(void) {
		return (GetFactionData()->Unknown);
	}

	long GetFlags(void) {
		return (GetFactionData()->Flags);
	}

	rankdata_t *GetRankData(const int Index) {
		return (IsValidRank(Index) ? & (GetFactionData()->RankData[Index]) : NULL);
	}

	bool IsValidRank(const int Index) {
		return (Index >= 0 && Index < MWESM_FACTION_NUMRANKS);
	}

	bool IsHidden(void) {
		return ((GetFlags() & MWESM_FACTFLAG_HIDDEN) != 0);
	}

	/* Set/clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetFactionData()->Flags |= Flag;
		} else {
			GetFactionData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetAttributeID1(const long Value) {
		GetFactionData()->AttributeID1 = Value;
	}

	void SetAttributeID2(const long Value) {
		GetFactionData()->AttributeID2 = Value;
	}

	void SetSkillID1(const long Value) {
		GetFactionData()->SkillID1 = Value;
	}

	void SetSkillID2(const long Value) {
		GetFactionData()->SkillID2 = Value;
	}

	void SetSkillID3(const long Value) {
		GetFactionData()->SkillID3 = Value;
	}

	void SetSkillID4(const long Value) {
		GetFactionData()->SkillID4 = Value;
	}

	void SetSkillID5(const long Value) {
		GetFactionData()->SkillID5 = Value;
	}

	void SetSkillID6(const long Value) {
		GetFactionData()->SkillID6 = Value;
	}

	void SetUnknown(const long Value) {
		GetFactionData()->Unknown = Value;
	}

	void SetHidden(const bool Flag) {
		SetFlag(MWESM_FACTFLAG_HIDDEN, Flag);
	}

};

/*===========================================================================
 *      End of Class CEsmSubFADT Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File EsmSubFADT.H
 *=========================================================================*/
