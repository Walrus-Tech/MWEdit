/*===========================================================================
 *
 * File:    EsmSpell.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSPELL_H
#define __ESMSPELL_H


#include "esm/EsmRecord.h"
#include "esm/EsmSubName.h"
#include "esm/EsmSubSPDT.h"
#include "esm/EsmSubENAM.h"

const TCHAR *GetESMSpellType(const int Type);
int GetESMSpellType(const TCHAR *pString);


/*===========================================================================
 *
 * Begin Class CEsmSpell Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSpell : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pName; /* Reference to sub-records */
	CEsmSubSPDT *m_pSpellData;


  public:
	/* Class Constructors/Destructors */
	CEsmSpell();
	//virtual ~CEsmSpell() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Spell");
	}

	/* Get class members */
	spelldata_t *GetSpellData() {
		return m_pSpellData ? m_pSpellData->GetSpellData() : NULL;
	}

	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	const TCHAR *GetSpellType() {
		return GetESMSpellType(GetSpellTypeID());
	}

	int GetSpellTypeID() {
		return m_pSpellData ? GetSpellData()->Type : 0;
	}

	long GetFlags() {
		return m_pSpellData ? GetSpellData()->Flags : 0;
	}

	long GetSpellCost() {
		return m_pSpellData ? GetSpellData()->SpellCost : 0;
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

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetSpellType(const int Type) {
		if (m_pSpellData) {
			GetSpellData()->Type = Type;
		}
	}

	void SetSpellCost(const int Cost) {
		if (m_pSpellData) {
			GetSpellData()->SpellCost = Cost;
		}
	}

	void SetName(const TCHAR *pString) {
		if (m_pName) {
			m_pName->SetName(pString);
		}
	}

	void SetAutoCalc(const bool Flag) {
		if (GetSpellData() == NULL) {
			return;
		}

		if (Flag) {
			GetSpellData()->Flags |= MWESM_SPELLFLAG_AUTOCALC;
		} else {
			GetSpellData()->Flags &= ~MWESM_SPELLFLAG_AUTOCALC;
		}
	}

	void SetPCStart(const bool Flag) {
		if (GetSpellData() == NULL) {
			return;
		}

		if (Flag) {
			GetSpellData()->Flags |= MWESM_SPELLFLAG_PCSTART;
		} else {
			GetSpellData()->Flags &= ~MWESM_SPELLFLAG_PCSTART;
		}
	}

	void SetSucceeds(const bool Flag) {
		if (GetSpellData() == NULL) {
			return;
		}

		if (Flag) {
			GetSpellData()->Flags |= MWESM_SPELLFLAG_SUCCEEDS;
		} else {
			GetSpellData()->Flags &= ~MWESM_SPELLFLAG_SUCCEEDS;
		}
	}


	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
