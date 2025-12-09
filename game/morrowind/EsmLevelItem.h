/*===========================================================================
 *
 * File:    EsmLevelItem.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMLEVELITEM_H
#define __ESMLEVELITEM_H


#include "esm/EsmRecord.h"
#include "esm/EsmSubName.h"
#include "esm/EsmSubLong.h"
#include "esm/EsmSubShort.h"
#include "esm/EsmSubByte.h"


#define MWESM_LEVITEMFLAG_ALLPC    1
#define MWESM_LEVITEMFLAG_CALCEACH 2


/*===========================================================================
 *
 * Begin Class CEsmLevelItem Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmLevelItem : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubLong *m_pData; /* Reference to sub-records */
	CEsmSubByte *m_pNNam;
	CEsmSubLong *m_pIndex;


  public:
	/* Class Constructors/Destructors */
	CEsmLevelItem();
	//virtual ~CEsmLevelItem() { Destroy(); }
	virtual void Destroy();

	/* Adds an item to the list */
	void AddItem(const TCHAR *pID, const int Value);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Create a string of the items in the levelled list */
	const TCHAR *GetItemListString();

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Level Item");
	}

	/* Get class members */
	long GetDataFlag() {
		return m_pData ? m_pData->GetValue() : 0;
	}

	int GetNNamFlag() {
		return (int)(m_pNNam ? m_pNNam->GetValue() : 0);
	}

	bool IsAllPC() {
		return (GetDataFlag() & MWESM_LEVITEMFLAG_ALLPC) != 0;
	}

	bool IsCalcEach() {
		return (GetDataFlag() & MWESM_LEVITEMFLAG_CALCEACH) != 0;
	}

	int GetChanceNone() {
		return (int)(GetNNamFlag());
	}

	int GetListSize() {
		return m_pIndex ? m_pIndex->GetValue() : 0;
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetChanceNone(const int Value) {
		if (m_pNNam) {
			m_pNNam->SetValue(Value);
		}
	}

	void SetCalcEach(const bool Flag) {
		if (m_pData) {
			m_pData->SetFlag(MWESM_LEVITEMFLAG_CALCEACH, Flag);
		}
	}

	void SetAllPC(const bool Flag) {
		if (m_pData) {
			m_pData->SetFlag(MWESM_LEVITEMFLAG_ALLPC, Flag);
		}
	}

	void SetListSize(const int Value) {
		if (m_pIndex) {
			m_pIndex->SetValue(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
