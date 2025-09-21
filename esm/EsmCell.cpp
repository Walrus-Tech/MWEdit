/*===========================================================================
 *
 * File:    EsmCell.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 * 5 October 2003
 *  - Added the FindCellRef() method.
 *
 *=========================================================================*/

#include "EsmCell.h"
#include "EsmFile.h"


DEFINE_FILE("EsmCell.cpp");

int g_NextCellRefIndex = 1; /* Used for cell reference indices */


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmCell::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameNull::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubCellDATA::Create
	},
	/*{
	 *	MWESM_SUBREC_DATA,
	 *	CEsmSubPos6::Create
	 *},*/
	{
		MWESM_SUBREC_RGNN,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_NAM0,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_NAM5,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_AMBI,
		CEsmSubAMBI::Create
	},
	{
		MWESM_SUBREC_WHGT,
		CEsmSubFloat::Create
	},
	{
		MWESM_SUBREC_FRMR,
		CEsmSubFRMR::Create
	},
	{
		MWESM_SUBREC_DELE,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_XSCL,
		CEsmSubFloat::Create
	},
	{
		MWESM_SUBREC_DODT,
		CEsmSubPos6::Create
	},
	{
		MWESM_SUBREC_DNAM,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_FLTV,
		CEsmSubFloat::Create
	},
	{
		MWESM_SUBREC_KNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_TNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_UNAM,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_ANAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_BNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_INTV,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_NAM9,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_XSOL,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CREF,
		CEsmSubCellRef::Create
	}, /* Not a 'real' sub-record */
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmCell Constructor
 *
 *=========================================================================*/
CEsmCell::CEsmCell() {
	//DEFINE_FUNCTION("CEsmCell::CEsmCell()");
	m_pCellData = NULL;
	m_pCountData = NULL;
	m_pRegionData = NULL;
	m_pLightData = NULL;
	m_pWaterData = NULL;
	m_pLastCellRef = NULL;
	m_RefCount = 0;
}


/*===========================================================================
 *
 * Class CEsmCell Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmCell::Destroy() {
	//DEFINE_FUNCTION("CEsmCell::Destroy()");
	m_pCellData = NULL;
	m_pCountData = NULL;
	m_pRegionData = NULL;
	m_pLightData = NULL;
	m_pWaterData = NULL;
	m_pLastCellRef = NULL;
	m_RefCount = 0;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmCell Method - CEsmSubRecord* AllocNewSubRecord (pType);
 *
 * Allocates a new subrecord of the given type.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmCell::AllocNewSubRecord(const TCHAR *pType, const long RecordSize) {
	/* Check for the special DATA type */
	if (TSTRNICMP(pType, MWESM_SUBREC_DATA, 4) == 0) {
		CEsmSubRecord *pSubRecord;

		/* Create and initialize the new record */
		if (RecordSize == sizeof(celldata_t)) {
			pSubRecord = CEsmSubCellDATA::Create();
		} else if (RecordSize == sizeof(pos6data_t)) {
			pSubRecord = CEsmSubPos6::Create();
		} else {
			return (CEsmRecord::AllocNewSubRecord(pType, RecordSize));
		}

		pSubRecord->SetType(pType);
		pSubRecord->SetRecordSize(RecordSize);
		return pSubRecord;
	}

	return CEsmRecord::AllocNewSubRecord(pType, RecordSize);
}


/*===========================================================================
 *
 * Class CEsmCell Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmCell::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmCell *pCell;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_CELL)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pCell = (CEsmCell *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pCell->GetName(), false);

		case ESM_FIELD_REGION:
			return StringCompare(GetRegion(), pCell->GetRegion(), false);

		case ESM_FIELD_GRID:
			return GetGridX() * 100 - pCell->GetGridX() * 100 + GetGridY() - pCell->GetGridY();

		case ESM_FIELD_REFCOUNT:
			return GetRefCount() - pCell->GetRefCount();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - void CopyCellBase (pCell);
 *
 * Copies just the base cell data, not any cell reference sub-records.
 *
 *=========================================================================*/
void CEsmCell::CopyCellBase(CEsmCell *pCell) {
	CEsmSubRecord *pSubRecord;
	CEsmSubRecord *pSourceSubRec;
	int Index;
	/* Delete the current contents, if any */
	Destroy();

	/* Copy the base record properties */
	m_pFile = pCell->m_pFile;
	m_Type.SetType(pCell->m_Type);
	m_Header1 = pCell->m_Header1;
	m_Flags = pCell->m_Flags;
	m_RecordSize = pCell->m_RecordSize;
	m_RefCount = pCell->m_RefCount;
	m_SubRecords.SetMaxElements(pCell->m_SubRecords.GetSize());

	/* Copy all the sub-records, but not any reference sub-records */
	for (Index = 0; Index < pCell->m_SubRecords.GetSize(); Index++) {
		pSourceSubRec = pCell->m_SubRecords.GetAt(Index);

		if (!pSourceSubRec->IsType(MWESM_SUBREC_CREF)
		    && !pSourceSubRec->IsType(MWESM_SUBREC_NAM0)) {
			pSubRecord = AllocateSubRecord(pSourceSubRec->GetType());
			pSubRecord->Copy(pSourceSubRec);
		}
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - void Copy (pRecord);
 *
 *=========================================================================*/
void CEsmCell::Copy(CEsmRecord *pRecord) {
	CEsmRecord::Copy(pRecord);

	/* Copy some extra cell data if required */
	if (pRecord != NULL && pRecord->IsType(MWESM_REC_CELL)) {
		CEsmCell *pCell = (CEsmCell *)pRecord;
		m_RefCount = pCell->GetRefCount();
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmCell::Create() {
	DEFINE_FUNCTION("CEsmCell::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmCell);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmCell Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmCell::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);

	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_AMBI);
	AllocateSubRecord(MWESM_SUBREC_NAM0);
	m_pCellData->CreateNew();
	m_pLightData->CreateNew();
	m_pCountData->CreateNew();

	/* Default interior cell */
	GetCellData()->Flags = MWESM_CELLFLAG_INTERIOR;
}


/*===========================================================================
 *
 * Class CEsmCell Method - CEsmSubCellRef* FindFirstCellRef (pRecord);
 *
 * Attempts to find and return the first matching cell reference for the
 * given record. Returns NULL on any error.
 *
 *=========================================================================*/
CEsmSubCellRef *CEsmCell::FindFirstCellRef(CEsmRecord *pRecord) {
	CEsmSubCellRef *pCellRef;
	int ArrayIndex;
	/* Look through all cell references */
	pCellRef = (CEsmSubCellRef *)FindFirst(MWESM_SUBREC_CREF, ArrayIndex);
	//SystemLog.Printf (_T("\tFinding References in '%s' (%4.4s)"), GetName(), GetType());

	while (pCellRef != NULL) {
		if (pCellRef->IsReference(pRecord->GetID())) {
			return pCellRef;
		}

		pCellRef = (CEsmSubCellRef *)FindNext(MWESM_SUBREC_CREF, ArrayIndex);
	}

	/* No match found */
	return NULL;
}


/*===========================================================================
 *
 * Class CEsmCell Method - CEsmSubCellRef* FindActiveCellRef (pCellRef);
 *
 * Attempt to find and return the given cell reference. Any 'parent'
 * cells are NOT checked. Returns NULL on any error.
 *
 *=========================================================================*/
CEsmSubCellRef *CEsmCell::FindActiveCellRef(CEsmSubCellRef *pCellRef) {
	CEsmSubCellRef *pFindCellRef;
	int Index;
	/* Search all cell references in the current cell record */
	pFindCellRef = (CEsmSubCellRef *)FindFirst(MWESM_SUBREC_CREF, Index);

	while (pFindCellRef != NULL) {
		if (pFindCellRef->IsSame(pCellRef)) {
			return pFindCellRef;
		}

		pFindCellRef = (CEsmSubCellRef *)FindNext(MWESM_SUBREC_CREF, Index);
	}

	return NULL;
}


/*===========================================================================
 *
 * Class CEsmCell Method - CEsmSubCellRef* FindCellRef (pCellRef);
 *
 * Attempt to find and return the given cell reference. Any 'parent'
 * cells are also checked. Returns NULL on any error.
 *
 *=========================================================================*/
CEsmSubCellRef *CEsmCell::FindCellRef(CEsmSubCellRef *pCellRef) {
	CEsmSubCellRef *pFindCellRef;
	int Index;
	/* Search all cell references in the current cell record */
	pFindCellRef = (CEsmSubCellRef *)FindFirst(MWESM_SUBREC_CREF, Index);

	while (pFindCellRef != NULL) {
		if (pFindCellRef->IsSame(pCellRef)) {
			return pFindCellRef;
		}

		pFindCellRef = (CEsmSubCellRef *)FindNext(MWESM_SUBREC_CREF, Index);
	}

	/* Search any previous cell records if required */
	if (m_pPrevRecord != NULL) {
		return ((CEsmCell *)m_pPrevRecord)->FindCellRef(pCellRef);
	}

	return NULL;
}


/*===========================================================================
 *
 * Class TCHAR* CEsmCell Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmCell::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_REGION:
			return GetRegion();

		case ESM_FIELD_GRID:
			return GetGrid();

		case ESM_FIELD_REFCOUNT:
			snprintf(s_Buffer, 31, _T("%ld"), GetRefCount());
			return s_Buffer;

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class TCHAR* CEsmCell Method - const GetGrid (void);
 *
 *=========================================================================*/
const TCHAR *CEsmCell::GetGrid() {
	static TCHAR s_Buffer[32];

	if (IsInterior()) {
		return _T("Interior");
	}

	snprintf(s_Buffer, 31, _T("%d, %d"), GetGridX(), GetGridY());
	return s_Buffer;
}


/*===========================================================================
 *
 * Class TCHAR* CEsmCell Method - const GetName (void);
 *
 *=========================================================================*/
const TCHAR *CEsmCell::GetName() {
	/* Just return the ID for interior cells */
	if (IsInterior()) {
		return GetID();
	}

	if (GetID() != NULL && GetID()[0] != NULL_CHAR) {
		return GetID();
	}

	if (GetRegion() == NULL) {
		return _T("Unknown");
	}

	return GetRegion();
}


/*===========================================================================
 *
 * Class CEsmCell Method - int GetNextRefIndex (void);
 *
 * Returns the next available cell reference index.
 *
 *=========================================================================*/
int CEsmCell::GetNextRefIndex() {
	bool Result;

	do {
		g_NextCellRefIndex++;
		Result = IsValidRefIndex(g_NextCellRefIndex);
	} while (Result);

	return g_NextCellRefIndex;
}


/*===========================================================================
 *
 * Class CEsmCell Method - long GetRefCount (void) {;
 *
 *=========================================================================*/
long CEsmCell::GetRefCount() {
	//DEFINE_FUNCTION("CEsmCell::GetRefCount()");
	CEsmRecord *pRecord = this;
	CEsmCell *pCell;
	long TotalCount = 0;

	while (pRecord != NULL) {
		if (!pRecord->IsType(MWESM_REC_CELL)) {
			break;
		}

		pCell = (CEsmCell *)pRecord;
		TotalCount += pCell->GetCount();
		pRecord = pRecord->GetPrevRecord();
	}

	return TotalCount;
}


/*===========================================================================
 *
 * Class CEsmCell Method - bool HasCellRef (pCellRef);
 *
 * Returns true if the given cell contains the cell reference. Only checks
 * the current cell, not any 'parent' cells.
 *
 *=========================================================================*/
bool CEsmCell::HasCellRef(CEsmSubCellRef *pCellRef) {
	return FindActiveCellRef(pCellRef) != NULL;
}


/*===========================================================================
 *
 * Class CEsmCell Method - bool IsSame (pRecord);
 *
 * Checks if the input record is the same CELL as the current record.
 * For interior cells the ID is checked, and for exterior cells the grid
 * location is checked.
 *
 *=========================================================================*/
bool CEsmCell::IsSame(CEsmRecord *pRecord) {
	/* Check types */
	if (!pRecord->IsType(MWESM_REC_CELL)) {
		return false;
	}

	/* Check IDs if it is an interior cell */
	if (IsInterior()) {
		return StringCompare(GetID(), pRecord->GetID(), false) == 0;
	}

	CEsmCell *pCell = (CEsmCell *)pRecord;

	/* Check the grid location otherwise */
	if (GetGridX() == pCell->GetGridX() && GetGridY() == pCell->GetGridY()) {
		return true;
	}

	return false;
}


/*===========================================================================
 *
 * Class CEsmCell Method - bool IsValidRefIndex (Index);
 *
 * Returns true if the given reference index is in use in the cell.
 *
 *=========================================================================*/
bool CEsmCell::IsValidRefIndex(const int RefIndex) {
	CEsmSubCellRef *pFindCellRef;
	int Index;
	/* Search all cell references in the current cell record */
	pFindCellRef = (CEsmSubCellRef *)FindFirst(MWESM_SUBREC_CREF, Index);

	while (pFindCellRef != NULL) {
		if (pFindCellRef->GetIndex() == RefIndex) {
			return true;
		}

		pFindCellRef = (CEsmSubCellRef *)FindNext(MWESM_SUBREC_CREF, Index);
	}

	/* Search any previous cell records if required */
	if (m_pPrevRecord != NULL) {
		return ((CEsmCell *)m_pPrevRecord)->IsValidRefIndex(RefIndex);
	}

	return false;
}


/*===========================================================================
 *
 * Class CEsmCell Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmCell::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_NAME)) {
		if (m_pID == NULL) {
			m_pID = (CEsmSubNameNull *)pSubRecord;
		}
	} else if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		if (m_pCellData == NULL) {
			m_pCellData = (CEsmSubCellDATA *)pSubRecord;
		}
	} else if (pSubRecord->IsType(MWESM_SUBREC_RGNN)) {
		m_pRegionData = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NAM0)) {
		m_pCountData = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_AMBI)) {
		m_pLightData = (CEsmSubAMBI *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_WHGT)) {
		m_pWaterData = (CEsmSubFloat *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - bool ReadData (File);
 *
 * Protected clss virtual method to input the sub-record data from the current
 * position in the file.  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmCell::ReadData(CGenFile &File) {
	DEFINE_FUNCTION("CEsmCell::ReadData()");
	CEsmSubRecord *pSubRecord;
	bool Result;
	TCHAR Type[MWESM_TYPE_SIZE];
	long EndOffset;
	long RecordSize;
	/* Compute when we should stop reading the sub-records */
	EndOffset = m_RecordSize + File.Tell();

	/* Input all the sub-records */
	while (File.Tell() < EndOffset) {
		/* Input the sub-record name */
		Result = File.Read(Type, MWESM_TYPE_SIZE);

		if (Result) {
			Result = File.ReadLong(RecordSize);
		}

		if (!Result) {
			return false;
		}

		//SystemLog.Printf ("\t\t%4.4s (0x%08X)", Type, File.Tell());

		/* Start of a cell-ref sub-record */
		if (TSTRNICMP(Type, MWESM_SUBREC_FRMR, 4) == 0) {
			//SystemLog.Printf ("Found FRMR (0x%08X)", File.Tell());
			pSubRecord = AllocateSubRecord(MWESM_SUBREC_CREF, RecordSize);
			m_pLastCellRef = (CEsmSubCellRef *)pSubRecord;
			m_pLastCellRef->SetIsActive(m_pFile->IsActive());
			m_pLastCellRef->SetCell(this);
			m_RefCount++;
			pSubRecord = AllocNewSubRecord(Type, RecordSize);
			m_pLastCellRef->AddSubRec(pSubRecord);
			Result = pSubRecord->Read(File);

			if (!Result) {
				return true;
			}
		} else if (m_pLastCellRef != NULL) { /* Input a cell-ref sub-record */
			//SystemLog.Printf ("Found FRMR Sub-Record %4.4s (0x%08X)", Type, File.Tell());
			pSubRecord = AllocNewSubRecord(Type, RecordSize);
			m_pLastCellRef->AddSubRec(pSubRecord);
			Result = pSubRecord->Read(File);

			if (!Result) {
				return true;
			}
		} else { /* Allocate and read a regular subrecord pointer */
			pSubRecord = AllocateSubRecord(Type, RecordSize);
			Result = pSubRecord->Read(File);

			if (!Result) {
				return true;
			}
		}
	}

	return true;
}


/*===========================================================================
 *
 * Class CEsmCell Method - void SetHasWater (Flag);
 *
 * Sets the has water flag for interior cells.
 *
 *=========================================================================*/
void CEsmCell::SetHasWater(const bool Flag) {
	/* Ensure valid data */
	if (GetCellData() == NULL) {
		return;
	}

	/* Set or clear the cell flag */
	if (Flag) {
		GetCellData()->Flags |= MWESM_CELLFLAG_HASWATER;
	} else {
		GetCellData()->Flags &= ~MWESM_CELLFLAG_HASWATER;
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - void SetLikeExterior (Flag);
 *
 * Sets the like exterior cell option for internal cells under Tribunal or
 * high versions.
 *
 *=========================================================================*/
void CEsmCell::SetLikeExterior(const bool Flag) {
	/* Ensure valid data */
	if (GetCellData() == NULL) {
		return;
	}

	/* Set or clear the cell flag */
	if (Flag) {
		GetCellData()->Flags |= MWESM_CELLFLAG_LIKEEXTERIOR;
	} else {
		GetCellData()->Flags &= ~MWESM_CELLFLAG_LIKEEXTERIOR;
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - void SetSleepIllegal (Flag);
 *
 * Set the sleep-illegal flag for interior cells.
 *
 *=========================================================================*/
void CEsmCell::SetSleepIllegal(const bool Flag) {
	/* Ensure valid data */
	if (GetCellData() == NULL) {
		return;
	}

	/* Set or clear the cell flag */
	if (Flag) {
		GetCellData()->Flags |= MWESM_CELLFLAG_SLEEPILLEGAL;
	} else {
		GetCellData()->Flags &= ~MWESM_CELLFLAG_SLEEPILLEGAL;
	}
}


/*===========================================================================
 *
 * Class CEsmCell Method - void SetRegion (pString);
 *
 *=========================================================================*/
void CEsmCell::SetRegion(const TCHAR *pString) {
	/* Delete the region sub-record */
	if (pString == NULL || *pString == NULL_CHAR) {
		if (m_pRegionData != NULL) {
			DeleteSubRecords(MWESM_SUBREC_RGNN);
		}

		m_pRegionData = NULL;
	} else {
		if (m_pRegionData == NULL) {
			AllocateSubRecord(MWESM_SUBREC_RGNN);
		}

		m_pRegionData->SetName(pString);
	}
}
