/*===========================================================================
 *
 * File:    EsmSubCellRef.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 * 5 October 2003
 *  - Updated the IsSame() method to deal with the new CEsmSubFRMR record
 *    type for cell reference indices.
 *  - Added the GetFieldString() method.
 *
 *=========================================================================*/
#include "esm/EsmSubCellRef.h"
#include "esm/EsmSubNameFix.h"
#include "esm/EsmSubLong.h"
#include "esm/EsmCell.h"


DEFINE_FILE("EsmSubCellRef.cpp");


/*===========================================================================
 *
 * Class CEsmSubCellRef Constructor
 *
 *=========================================================================*/
CEsmSubCellRef::CEsmSubCellRef() : m_SubRecArray(0) {
	//DEFINE_FUNCTION("CEsmSubCellRef::CEsmSubCellRef()");
	m_IsActive = false;
	m_pRecInfo = NULL;
	m_pCell = NULL;
	m_UserData = 0;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmSubCellRef::Destroy() {
	//DEFINE_FUNCTION("CEsmSubCellRef::Destroy()");
	ClearSubRecArray();
	m_IsActive = false;
	m_pRecInfo = NULL;
	m_pCell = NULL;
	CEsmSubRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void ClearSubRecArray (void);
 *
 * Deletes all record in the cellref array.
 *
 *=========================================================================*/
void CEsmSubCellRef::ClearSubRecArray() {
	DEFINE_FUNCTION("CEsmSubCellRef::ClearSubRecArray()");
	CEsmSubRecord *pSubRec;
	int Index;

	for (Index = 0; Index < m_SubRecArray.GetSize(); Index++) {
		pSubRec = m_SubRecArray.GetAt(Index);
		DestroyPointer(pSubRec);
	}

	m_SubRecArray.RemoveAll();
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void Copy (pSubRecord);
 *
 *=========================================================================*/
void CEsmSubCellRef::Copy(CEsmSubRecord *pSubRecord) {
	CEsmSubRecord *pSubRec;
	CEsmSubRecord *pNewSubRec;
	CEsmSubCellRef *pCellRef;
	int Index;
	/* Clear the current contents */
	Destroy();

	/* Only copy records of the same type */
	if (!pSubRecord->IsType(MWESM_SUBREC_CREF)) {
		return;
	}

	m_Type.SetType(pSubRecord->GetType());
	pCellRef = (CEsmSubCellRef *)pSubRecord;
	m_pRecInfo = pCellRef->GetRecInfo();
	m_IsActive = pCellRef->IsActive();
	m_pCell = pCellRef->GetCell();

	/* Copy all sub-records */
	for (Index = 0; Index < pCellRef->GetNumSubRecs(); Index++) {
		pSubRec = pCellRef->GetSubRec(Index);
		pNewSubRec = m_pCell->AllocNewSubRecord(pSubRec->GetType(), pSubRec->GetRecordSize());
		pNewSubRec->Copy(pSubRec);
		m_SubRecArray.Add(pNewSubRec);
	}
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - CEsmSubRecord* Create (void);
 *
 *=========================================================================*/
CEsmSubRecord *CEsmSubCellRef::Create() {
	CEsmSubRecord *pSubRecord;
	CreatePointerL(pSubRecord, CEsmSubCellRef);
	return pSubRecord;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void CreateNew (pCell);
 *
 *=========================================================================*/
void CEsmSubCellRef::CreateNew(CEsmCell *pCell) {
	CEsmSubRecord::CreateNew();
	SetType(MWESM_SUBREC_CREF);
	m_pCell = pCell;

	if (m_pCell != NULL) {
		CEsmSubRecord* pSubRecord;
		pSubRecord = m_pCell->AllocNewSubRecord(MWESM_SUBREC_FRMR);
		pSubRecord->CreateNew();
		AddSubRec(pSubRecord);
		pSubRecord = m_pCell->AllocNewSubRecord(MWESM_SUBREC_NAME);
		pSubRecord->CreateNew();
		AddSubRec(pSubRecord);
		pSubRecord = m_pCell->AllocNewSubRecord(MWESM_SUBREC_DATA, sizeof(pos6data_t));
		pSubRecord->CreateNew();
		AddSubRec(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - CEsmSubRecord* FindSubRecord (pType);
 *
 * Finds the sub-record of the given type.  Cell-references should contain
 * only one of each type.  Returns NULL if the sub-record is not found.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmSubCellRef::FindSubRecord(const TCHAR *pType) {
	CEsmSubRecord *pSubRec;
	int Index;

	for (Index = 0; Index < m_SubRecArray.GetSize(); Index++) {
		pSubRec = m_SubRecArray.GetAt(Index);

		if (pSubRec->IsType(pType)) {
			return pSubRec;
		}
	}

	return NULL;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - bool Find (FindData);
 *
 * Returns true if the given text existing in the sub-record data.  Default
 * implementation does a binary check of the sub-record data (not case
 * sensitive).  Stops searching on the first match.
 *
 *=========================================================================*/
bool CEsmSubCellRef::Find(esmfind_t &FindData) {
	CEsmSubRecord *pSubRec;
	bool Result;
	int Index;

	/* Search all sub-records */
	for (Index = 0; Index < m_SubRecArray.GetSize(); Index++) {
		pSubRec = m_SubRecArray.GetAt(Index);
		Result = pSubRec->Find(FindData);

		if (Result) {
			return true;
		}
	}

	/* No match */
	return false;
}


/*===========================================================================
 *
 * Class TCHAR* CEsmSubCellRef Method - const TCHAR* GetFieldString (FieldID);
 *
 * Returns a string representation of a specified sub-record field. Uses
 * a local static string buffer.
 *
 *=========================================================================*/
const TCHAR *CEsmSubCellRef::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[64];

	switch (FieldID) {
		case ESMSUBLIST_FIELD_MOD:
			snprintf(s_Buffer, 31, _T("%s%s"), IsActive() ? "*" : "", IsDeleted() ? "D" : "");
			return s_Buffer;

		case ESMSUBLIST_FIELD_INDEX: {
			CEsmSubFRMR *pIndex = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);

			if (pIndex == NULL) {
				strnncpy(s_Buffer, _T("?"), 32);
			} else {
				snprintf(s_Buffer, 32, _T("0x%06lX-%02X"), pIndex->GetIndex(), pIndex->GetFlag());
			}

			return s_Buffer;
		}

		default:
			return _T("");
	}
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - int GetIndex (void);
 *
 * Returns the FRMR reference index.
 *
 *=========================================================================*/
int CEsmSubCellRef::GetIndex() {
	CEsmSubFRMR *pIndex = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);

	if (pIndex != 0) {
		return pIndex->GetIndex();
	}

	return -1;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - pos6data_t* GetLocation (void);
 *
 * Gets the reference location data.
 *
 *=========================================================================*/
pos6data_t *CEsmSubCellRef::GetLocation() {
	CEsmSubPos6 *pPos = (CEsmSubPos6 *)FindSubRecord(MWESM_SUBREC_DATA);

	if (pPos != NULL) {
		return pPos->GetPosData();
	}

	return NULL;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - bool IsReference (pID);
 *
 * Returns true if the reference is for the given record ID.
 *
 *=========================================================================*/
bool CEsmSubCellRef::IsReference(const TCHAR *pID) {
	CEsmSubName *pName = (CEsmSubName *)FindSubRecord(MWESM_SUBREC_NAME);

	if (pName == NULL) {
		return false;
	}

	//SystemLog.Printf(_T("\t\t\t'%s'(%4.4s) ?= '%s'"), pName->GetName(), pName->GetType(), pID);
	return StringCompare(pName->GetName(), pID, false) == 0;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - bool IsSame (pCellRef);
 *
 * Returns true if the given input record is the same object reference as
 * the current object.
 *
 *=========================================================================*/
bool CEsmSubCellRef::IsSame(CEsmSubCellRef *pCellRef) {
	CEsmSubNameFix *pName1;
	CEsmSubNameFix *pName2;
	CEsmSubFRMR *pIndex1;
	CEsmSubFRMR *pIndex2;

	/* Check the object names */
	pName1 = (CEsmSubNameFix *)FindSubRecord(MWESM_SUBREC_NAME);
	pName2 = (CEsmSubNameFix *)pCellRef->FindSubRecord(MWESM_SUBREC_NAME);

	if (pName1 == NULL || pName2 == NULL) {
		return false;
	}

	//SystemLog.Printf ("Compare '%s' and '%s'", pName1->GetName(), pName2->GetName());
	if (_stricmp(pName1->GetName(), pName2->GetName()) != 0) {
		return false;
	}

	/* Check the object indices */
	pIndex1 = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);
	pIndex2 = (CEsmSubFRMR *)pCellRef->FindSubRecord(MWESM_SUBREC_FRMR);

	if (pIndex1 == NULL || pIndex2 == NULL) {
		return false;
	}

	//SystemLog.Printf ("\t\tCompare '%ld' and '%ld'", pIndex1->GetValue(), pIndex2->GetValue());

	if (pIndex1->GetIndex() == pIndex2->GetIndex()) {
		return true;
	}

	return false;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - bool IsUsed (pID) const;
 *
 * Checks if the given ID is used in the cell reference sub-record, returning
 * true if it does.
 *
 *=========================================================================*/
bool CEsmSubCellRef::IsUsed(const TCHAR *pID) {
	CEsmSubRecord *pSubRecord;
	bool Result;
	int Index;

	for (Index = 0; Index < m_SubRecArray.GetNumElements(); Index++) {
		pSubRecord = m_SubRecArray.GetAt(Index);
		Result = pSubRecord->IsUsed(pID);

		if (Result) {
			return true;
		}
	}

	return false;
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void :SetDelete (Flag);
 *
 * Deletes or undeletes the cell reference.
 *
 *=========================================================================*/
void CEsmSubCellRef::SetDelete(const bool Flag) {
	DEFINE_FUNCTION("CEsmSubCellRef:SetDelete()");
	CEsmSubLong *pDeleteRec;
	/* Find the delete sub-record */
	pDeleteRec = (CEsmSubLong *)FindSubRecord(MWESM_SUBREC_DELE);

	if (Flag) {
		if (pDeleteRec != NULL) {
			return;
		}

		if (m_pCell == NULL) {
			return;
		}

		pDeleteRec = (CEsmSubLong *)m_pCell->AllocNewSubRecord(MWESM_SUBREC_DELE);
		pDeleteRec->CreateNew();
		AddSubRec(pDeleteRec);
		pDeleteRec->SetValue(0);
	} else if (pDeleteRec != NULL) {
		m_SubRecArray.DeleteElement(pDeleteRec);
		DestroyPointer(pDeleteRec);
	}
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void SetIndex (Index, Flag);
 *
 * Sets the FRMR index value.
 *
 *=========================================================================*/
void CEsmSubCellRef::SetIndex(const long Index, const byte Flag) {
	CEsmSubFRMR *pFRMRRec;
	/* Find the name sub-record, create if required */
	pFRMRRec = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);

	if (pFRMRRec == NULL) {
		if (m_pCell == NULL) {
			return;
		}

		pFRMRRec = (CEsmSubFRMR *)m_pCell->AllocNewSubRecord(MWESM_SUBREC_FRMR);
		pFRMRRec->CreateNew();
		m_SubRecArray.AddHead(pFRMRRec); /* Important that it is the first sub-record */
	}

	pFRMRRec->SetIndex(Index);
	pFRMRRec->SetFlag(Flag);
}

void CEsmSubCellRef::SetFRMRFlag(const byte Flag) {
	CEsmSubFRMR *pFRMRRec;
	/* Find the name sub-record, create if required */
	pFRMRRec = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);

	if (pFRMRRec == NULL) {
		if (m_pCell == NULL) {
			return;
		}

		pFRMRRec = (CEsmSubFRMR *)m_pCell->AllocNewSubRecord(MWESM_SUBREC_FRMR);
		pFRMRRec->CreateNew();
		m_SubRecArray.AddHead(pFRMRRec); /* Important that it is the first sub-record */
	}

	pFRMRRec->SetFlag(Flag);
}

void CEsmSubCellRef::SetFRMRIndex(const long Index) {
	CEsmSubFRMR *pFRMRRec;
	/* Find the name sub-record, create if required */
	pFRMRRec = (CEsmSubFRMR *)FindSubRecord(MWESM_SUBREC_FRMR);

	if (pFRMRRec == NULL) {
		if (m_pCell == NULL) {
			return;
		}

		pFRMRRec = (CEsmSubFRMR *)m_pCell->AllocNewSubRecord(MWESM_SUBREC_FRMR);
		pFRMRRec->CreateNew();
		m_SubRecArray.AddHead(pFRMRRec); /* Important that it is the first sub-record */
	}

	pFRMRRec->SetIndex(Index);
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - void SetRefName (pName);
 *
 * Sets the cell reference NAME ID.
 *
 *=========================================================================*/
void CEsmSubCellRef::SetRefName(const TCHAR *pName) {
	CEsmSubName *pNameRec;
	/* Find the name sub-record, create if required */
	pNameRec = (CEsmSubName *)FindSubRecord(MWESM_SUBREC_NAME);

	if (pNameRec == NULL) {
		if (m_pCell == NULL) {
			return;
		}

		pNameRec = (CEsmSubName *)m_pCell->AllocNewSubRecord(MWESM_SUBREC_NAME);
		pNameRec->CreateNew();
		AddSubRec(pNameRec);
	}

	pNameRec->SetName(pName);
}


/*===========================================================================
 *
 * Class CEsmSubCellRef Method - bool Write (File);
 *
 * Outputs all the sub-records contained within the cell reference.
 *
 *=========================================================================*/
bool CEsmSubCellRef::Write(CGenFile &File) {
	CEsmSubRecord *pSubRec;
	bool Result;
	int Index;

	for (Index = 0; Index < m_SubRecArray.GetSize(); Index++) {
		pSubRec = m_SubRecArray.GetAt(Index);
		Result = pSubRec->Write(File);

		if (!Result) {
			return false;
		}
	}

	return true;
}
