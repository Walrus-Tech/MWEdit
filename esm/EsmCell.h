/*===========================================================================
 *
 * File:    EsmCell.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCELL_H
#define __ESMCELL_H


#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubNameFix.h"
#include "EsmSubLong.h"
#include "EsmSubPos6.h"
#include "EsmSubCellDATA.h"
#include "EsmSubFloat.h"
#include "EsmSubByte.h"
#include "EsmSubFloat.h"
#include "EsmSubAMBI.h"
#include "EsmSubCellRef.h"
#include "EsmSubFRMR.h"


/*===========================================================================
 *
 * Begin Class CEsmCell Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmCell : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubCellDATA *m_pCellData;
	CEsmSubNameFix *m_pRegionData;
	CEsmSubLong *m_pCountData;
	CEsmSubAMBI *m_pLightData;
	CEsmSubFloat *m_pWaterData;

	CEsmSubCellRef *m_pLastCellRef;
	int m_RefCount;


	/* Input sub-records */
	virtual bool ReadData(CGenFile &File);


  public:
	/* Class Constructors/Destructors */
	CEsmCell();
	//virtual ~CEsmCell() { Destroy(); }
	virtual void Destroy();

	/* Add a cell reference to the cell */
	void AddCellRef(CEsmSubCellRef *pCellRef) {
		pCellRef->SetCell(this);
		m_SubRecords.Add(pCellRef);
	}

	/* Allocate subrecords */
	virtual CEsmSubRecord *AllocNewSubRecord(const TCHAR *pType, const long RecordSize = 0);

	/* Copy only the base cell data */
	void CopyCellBase(CEsmCell *pCell);
	virtual void Copy(CEsmRecord *pRecord);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Find a cell reference in the cel */
	CEsmSubCellRef *FindCellRef(CEsmSubCellRef *pCellRef);
	CEsmSubCellRef *FindActiveCellRef(CEsmSubCellRef *pCellRef);
	CEsmSubCellRef *FindFirstCellRef(CEsmRecord *pRecord);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Cell");
	}

	/* Get class members */
	celldata_t *GetCellData() {
		return m_pCellData ? m_pCellData->GetCellData() : NULL;
	}

	ambidata_t *GetAMBIData() {
		return m_pLightData ? m_pLightData->GetAMBIData() : NULL;
	}

	float GetWaterHeight() {
		return m_pWaterData ? m_pWaterData->GetValue() : 0;
	}

	const TCHAR *GetRegion() {
		return m_pRegionData ? m_pRegionData->GetName() : _T("");
	}

	const TCHAR *GetName();
	const TCHAR *GetGrid();
	long GetRefCount();
	long GetGridX() {
		return m_pCellData == NULL ? 0 : m_pCellData->GetGridX();
	}

	long GetGridY() {
		return m_pCellData == NULL ? 0 : m_pCellData->GetGridY();
	}

	long GetFlags() {
		return m_pCellData == NULL ? 0 : m_pCellData->GetFlags();
	}

	long GetCount() {
		return m_RefCount;
	}

	bool IsInterior() {
		return m_pCellData == NULL ? false : m_pCellData->IsInterior();
	}

	virtual bool IsSame(CEsmRecord *pRecord);

	/* Cell reference index methods */
	int GetNextRefIndex();
	bool IsValidRefIndex(const int Index);

	/* Returns true if the record currently contains the given reference */
	bool HasCellRef(CEsmSubCellRef *pCellRef);

	/* Changes the total cell reference count */
	void DecCount() {
		m_RefCount--;

		if (m_pCountData != NULL) {
			m_pCountData->SetValue(m_pCountData->GetValue() - 1);
		}
	}

	void IncCount() {
		m_RefCount++;

		if (m_pCountData != NULL) {
			m_pCountData->SetValue(m_pCountData->GetValue() + 1);
		}
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetRegion(const TCHAR *pString);
	void SetWaterHeight(const float Value) {
		if (m_pWaterData) {
			m_pWaterData->SetValue(Value);
		}
	}

	void SetExterior() {
		if (m_pCellData != NULL) {
			m_pCellData->SetInterior(false);
		}
	}

	void SetInterior() {
		if (m_pCellData != NULL) {
			m_pCellData->SetInterior(true);
		}
	}

	void SetGridX(const int Value) {
		if (m_pCellData != NULL) {
			m_pCellData->SetGridX(Value);
		}
	}

	void SetGridY(const int Value) {
		if (m_pCellData != NULL) {
			m_pCellData->SetGridY(Value);
		}
	}

	void SetHasWater(const bool Flag);
	void SetSleepIllegal(const bool Flag);
	void SetLikeExterior(const bool Flag);
};


#endif
