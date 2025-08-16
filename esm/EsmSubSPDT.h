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


#include "EsmSubBase.h"


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


#pragma pack(push, 1)

typedef struct {
	long Type;
	long SpellCost;
	long Flags;
} spelldata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubSPDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSPDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubSPDT();
	//virtual ~CEsmSubSPDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSPDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(spelldata_t));
		m_RecordSize = sizeof(spelldata_t);
		memset(m_pData, 0, sizeof(spelldata_t));
	}

	/* Get class members */
	spelldata_t *GetSpellData() {
		return (spelldata_t *)m_pData;
	}

	long GetSpellType() {
		return GetSpellData()->Type;
	}

	long GetSpellCost() {
		return GetSpellData()->SpellCost;
	}

	long GetFlags() {
		return GetSpellData()->Flags;
	}

	bool IsAutoCalc() {
		return (GetFlags() & MWESM_SPELLFLAG_AUTOCALC) != 0;
	}

	bool IsPCStart() {
		return (GetFlags() & MWESM_SPELLFLAG_PCSTART) != 0;
	}

	bool IsSucceeds() {
		return (GetFlags() & MWESM_SPELLFLAG_SUCCEEDS) != 0;
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


#endif
