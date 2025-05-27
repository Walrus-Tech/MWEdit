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


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubSPDT.h"
#include "EsmSubENAM.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
const TCHAR *GetESMSpellType(const int Type);
int GetESMSpellType(const TCHAR *pString);
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSpell Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSpell : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pName;    /* Reference to sub-records */
	CEsmSubSPDT *m_pSpellData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSpell();
	//virtual ~CEsmSpell() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Spell");
	}

	/* Get class members */
	spelldata_t *GetSpellData(void) {
		return (m_pSpellData ? m_pSpellData->GetSpellData() : NULL);
	}

	const TCHAR *GetName(void) {
		return (m_pName ? m_pName->GetName() : _T(""));
	}

	const TCHAR *GetSpellType(void) {
		return GetESMSpellType(GetSpellTypeID());
	}

	int GetSpellTypeID(void) {
		return (m_pSpellData ? GetSpellData()->Type : 0);
	}

	long GetFlags(void) {
		return (m_pSpellData ? GetSpellData()->Flags : 0);
	}

	long GetSpellCost(void) {
		return (m_pSpellData ? GetSpellData()->SpellCost : 0);
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

/*===========================================================================
 *      End of Class CEsmSpell Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmSpell.H
 *=========================================================================*/
