/*===========================================================================
 *
 * File:    EsmFaction.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMFACTION_H
#define __ESMFACTION_H


#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubLong.h"
#include "EsmSubName32.h"
#include "EsmSubFADT.h"


/*===========================================================================
 *
 * Begin Class CEsmFaction Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmFaction : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pName;
	CEsmSubFADT *m_pFactionData;
	CEsmSubName32 *m_pRankNames[MWESM_FACTION_NUMRANKS];
	int m_NumRankNames;


  public:
	/* Class Constructors/Destructors */
	CEsmFaction();
	//virtual ~CEsmFaction() { Destroy(); }
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
		return _T("Faction");
	}

	/* Get class members */
	factiondata_t *GetFactionData() {
		return m_pFactionData ? m_pFactionData->GetFactionData() : NULL;
	}

	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	bool IsHidden() {
		return m_pFactionData ? m_pFactionData->IsHidden() : false;
	}

	const TCHAR *GetRankName(const int Rank);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pString) {
		if (m_pName) {
			m_pName->SetName(pString);
		}
	}

	void SetHidden(const bool Flag) {
		if (m_pFactionData) {
			m_pFactionData->SetHidden(Flag);
		}
	}

	void SetRankName(const int Rank, const TCHAR *pString);

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
