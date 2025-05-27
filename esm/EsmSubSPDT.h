/*===========================================================================
 *
 * File:    EsmsubPBDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSPDT_H
#define __ESMSUBSPDT_H


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

/* Spell types */
#define MWESM_SPELLTYPE_MIN       0
#define MWESM_SPELLTYPE_SPELL     0
#define MWESM_SPELLTYPE_ABILITY   1
#define MWESM_SPELLTYPE_BLIGHT    2
#define MWESM_SPELLTYPE_DISEASE   3
#define MWESM_SPELLTYPE_CURSE     4
#define MWESM_SPELLTYPE_POWER     5
#define MWESM_SPELLTYPE_MAX       5

/* Spell flags */
#define MWESM_SPELLFLAG_AUTOCALC  0x0001
#define MWESM_SPELLFLAG_PCSTART   0x0002
#define MWESM_SPELLFLAG_SUCCEEDS  0x0004

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
	long Type;
	long SpellCost;
	long Flags;
} spelldata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubSPDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSPDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubSPDT();
	//virtual ~CEsmSubSPDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSPDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(spelldata_t));
		m_RecordSize = sizeof(spelldata_t);
		memset(m_pData, 0, sizeof(spelldata_t));
	}

	/* Get class members */
	spelldata_t *GetSpellData(void) {
		return ((spelldata_t *)m_pData);
	}

	long GetSpellType(void) {
		return (GetSpellData()->Type);
	}

	long GetSpellCost(void) {
		return (GetSpellData()->SpellCost);
	}

	long GetFlags(void) {
		return (GetSpellData()->Flags);
	}

	bool IsAutoCalc(void) {
		return ((GetFlags() & MWESM_SPELLFLAG_AUTOCALC) != 0);
	}

	bool IsPCStart(void) {
		return ((GetFlags() & MWESM_SPELLFLAG_PCSTART) != 0);
	}

	bool IsSucceeds(void) {
		return ((GetFlags() & MWESM_SPELLFLAG_SUCCEEDS) != 0);
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetSpellData()->Flags |= Flag;
		} else {
			GetSpellData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetSpellType(const long Value) {
		if (Value >= MWESM_SPELLTYPE_MIN && Value <= MWESM_SPELLTYPE_MAX) {
			GetSpellData()->Type = Value;
		}
	}

	void SetSpellCost(const long Value) {
		GetSpellData()->SpellCost = Value;
	}

	void SetAutoCalc(const bool Flag) {
		SetFlag(MWESM_SPELLFLAG_AUTOCALC, Flag);
	}

	void SetPCStart(const bool Flag) {
		SetFlag(MWESM_SPELLFLAG_PCSTART, Flag);
	}

	void SetSucceeds(const bool Flag) {
		SetFlag(MWESM_SPELLFLAG_SUCCEEDS, Flag);
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
