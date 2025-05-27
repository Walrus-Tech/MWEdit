/*===========================================================================
 *
 * File:    Esmrecord.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmrecord.h"
#include "esmfile.h"
#include "EsmSubName.h"
#include "EsmSubNameFix.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmRecord.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmRecord::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_DELE,
		CEsmSubLong::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Constructor
 *
 *=========================================================================*/
CEsmRecord::CEsmRecord() : m_SubRecords(0) {
	//DEFINE_FUNCTION("CEsmRecord::CEsmRecord()");
	m_Header1 = 0;
	m_Flags = 0;
	m_RecordSize = 0;
	m_RefCount = 0;
	m_UserData = 0;
	m_pFile = NULL;
	m_pDelete = NULL;
	m_pID = NULL;
	m_pPrevRecord = NULL;
}

/*===========================================================================
 *      End of Class CEsmRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmRecord::Destroy(void) {
	//DEFINE_FUNCTION("CEsmRecord::Destroy()");
	CEsmSubRecord *pSubRecord;
	int Index;

	/* Delete all allocated sub-records */
	for (Index = 0; Index < m_SubRecords.GetSize(); Index++) {
		pSubRecord = m_SubRecords.GetAt(Index);
		DestroyPointer(pSubRecord);
	}

	m_RecordSize = 0;
	m_Flags = 0;
	m_RefCount = 0;
	m_pDelete = NULL;
	m_pID = NULL;
	m_pPrevRecord = NULL;
	m_SubRecords.RemoveAll();
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmSubRecord* AllocNewSubRecord (pType);
 *
 * Allocates a new subrecord of the given type.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmRecord::AllocNewSubRecord(const TCHAR *pType, const long RecordSize) {
	const esmsubreccreate_t *SubRecCreate = GetSubRecCreate();
	CEsmSubRecord *pSubRecord;
	int Index;

	for (Index = 0; SubRecCreate[Index].Type != NULL; Index++) {
		if (SubRecCreate[Index].IsType(pType)) {
			break;
		}
	}

	/* Try and find the record in the base array, if required */
	if (SubRecCreate != s_SubRecCreate && SubRecCreate[Index].Type == NULL) {
		SubRecCreate = s_SubRecCreate;

		for (Index = 0; SubRecCreate[Index].Type != NULL; Index++) {
			if (SubRecCreate[Index].IsType(pType)) {
				break;
			}
		}
	}

	/* Create and initialize the new record */
	pSubRecord = SubRecCreate[Index].CreateMethod();
	pSubRecord->SetType(pType);
	pSubRecord->SetRecordSize(RecordSize);
	return (pSubRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::AllocNewSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmSubRecord* AllocateSubRecord (pType, RecordSize);
 *
 * Allocates a sub-record based on the input sub-record type string.
 * Creates a default CEsmSubRecord object if the type is not known.
 * Protected class virtual method.  Adds the sub-record to the sub-record
 * array and sets the record type;
 *
 *=========================================================================*/
CEsmSubRecord *CEsmRecord::AllocateSubRecord(const TCHAR *pType, const long RecordSize) {
	DEFINE_FUNCTION("CEsmRecord::AllocateSubRecord()");
	CEsmSubRecord *pSubRecord;
	pSubRecord = AllocNewSubRecord(pType, RecordSize);
	/* Add the subrecord to the subrecord array */
	m_SubRecords.Add(pSubRecord);
	/* Call the add event */
	OnAddSubRecord(pSubRecord);
	return (pSubRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::AllocateSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmRecord::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmRecord::CompareFields()");

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetFieldString(ESM_FIELD_NAME),
			                     pRecord->GetFieldString(ESM_FIELD_NAME),
			                     FALSE);

		case ESM_FIELD_ID:
			return StringCompare(GetID(), pRecord->GetID(), FALSE);

		case ESM_FIELD_ITEMTYPE:
			return StringCompare(GetItemType(), pRecord->GetItemType(), FALSE);

		case ESM_FIELD_COUNT:
			return (int)(m_RefCount - pRecord->GetRefCount());

		case ESM_FIELD_PERSIST:
			return (int)IsPersist() - (int)pRecord->IsPersist();

		case ESM_FIELD_BLOCKED:
			return (int)IsBlocked() - (int)pRecord->IsBlocked();

		case ESM_FIELD_CHANGED:         /* Note this is reversed on purpose */
			return ((int)pRecord->GetFile()->IsActive() + pRecord->IsDeleted() * 10)
			        - ((int)GetFile()->IsActive() + IsDeleted() * 10);

		case ESM_FIELD_USERDATA:
			return GetUserData() - pRecord->GetUserData();

		default:
			return StringCompare(GetFieldString(FieldID), pRecord->GetFieldString(FieldID), FALSE);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - void Copy (pRecord);
 *
 * Copies the values from the given record.
 *
 *=========================================================================*/
void CEsmRecord::Copy(CEsmRecord *pRecord) {
	CEsmSubRecord *pSubRecord;
	CEsmSubRecord *pSourceSubRec;
	int Index;
	/* Delete the current contents, if any */
	Destroy();
	/* Copy the base record properties */
	m_pFile = pRecord->m_pFile;
	m_Type.SetType(pRecord->m_Type);
	m_Header1 = pRecord->m_Header1;
	m_Flags = pRecord->m_Flags;
	m_RecordSize = pRecord->m_RecordSize;
	m_RefCount = pRecord->m_RefCount;
	m_SubRecords.SetMaxElements(pRecord->m_SubRecords.GetSize());

	/* Copy all the sub-records */
	for (Index = 0; Index < pRecord->m_SubRecords.GetSize(); Index++) {
		pSourceSubRec = pRecord->m_SubRecords.GetAt(Index);
		pSubRecord = AllocateSubRecord(pSourceSubRec->GetType());
		pSubRecord->Copy(pSourceSubRec);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmRecord::Create(void) {
	DEFINE_FUNCTION("CEsmRecord::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmRecord);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmSubRecord* CreateCopy (pSubRecord);
 *
 *=========================================================================*/
CEsmSubRecord *CEsmRecord::CreateCopy(CEsmSubRecord *pSubRecord) {
	CEsmSubRecord *pNewSubRecord = AllocNewSubRecord(pSubRecord->GetType());
	pNewSubRecord->Copy(pSubRecord);
	return (pNewSubRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::CreateCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmRecord::CreateNew(CEsmFile *pFile) {
	/* Delete the current contents of the record */
	Destroy();
	/* Set the common record options */
	m_pFile = pFile;
	m_Flags = 0;
	m_Header1 = 0;
	m_RecordSize = 0;
	m_RefCount = 0;

	/* Create the record ID if required */
	if (!IsType(MWESM_REC_TES3)
	    && !IsType(MWESM_REC_MGEF)
	    && !IsType(MWESM_REC_INFO)
	    && !IsType(MWESM_REC_SKIL)
	    && !IsType(MWESM_REC_SCPT)
	    && !IsType(MWESM_REC_SSCR)) {
		AllocateSubRecord(MWESM_SUBREC_NAME);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRecord::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - void DeleteToggle (void);
 *
 * Deletes or undeletes the record.
 *
 *=========================================================================*/
void CEsmRecord::DeleteToggle(void) {
	DEFINE_FUNCTION("CEsmRecord::DeleteToggle()");

	if (IsDeleted()) {
		DeleteSubRecords(MWESM_SUBREC_DELE);
		m_pDelete = NULL;
	} else {
		AllocateSubRecord(MWESM_SUBREC_DELE);
		ASSERT(m_pDelete != NULL);
		m_pDelete->CreateNew();
	}
}

/*===========================================================================
 *      End of Class Method CEsmRecord::DeleteToggle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - int DeleteSubRecords (pType);
 *
 * Deletes all sub-records of the given type from the record.  Returns the
 * number of sub-records deleted.
 *
 *=========================================================================*/
int CEsmRecord::DeleteSubRecords(const TCHAR *pType) {
	DEFINE_FUNCTION("CEsmRecord::DeleteSubRecords()");
	CEsmSubRecord *pSubRecord;
	int Count = 0;
	int Index;

	for (Index = 0; Index < m_SubRecords.GetSize(); Index++) {
		pSubRecord = m_SubRecords.GetAt(Index);

		if (pSubRecord->IsType(pType)) {
			m_SubRecords.RemoveAt(Index);
			DestroyPointer(pSubRecord);
			Index--;
			Count++;
		}
	}

	return (Count);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::DeleteSubRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmSubRecord* FindNext (pType, ArrayIndex);
 *
 * Find the next sub-record of the given type after the given array index.
 * Returns NULL if it is not found.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmRecord::FindNext(const TCHAR *pType, int &ArrayIndex) {
	CEsmSubRecord *pSubRecord;

	for (ArrayIndex++; ArrayIndex < m_SubRecords.GetSize(); ArrayIndex++) {
		pSubRecord = m_SubRecords.GetAt(ArrayIndex);

		if (pSubRecord->IsType(pType)) {
			return (pSubRecord);
		}
	}

	return (NULL);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::FindNext()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool Find (FindData);
 *
 * Returns true if the record contains the given text string. Default
 * implementation does a binary search of all sub-records. Stops searching
 * at the first match.
 *
 *=========================================================================*/
bool CEsmRecord::Find(esmfind_t &FindData) {
	CEsmSubRecord *pSubRec;
	bool Result;
	int Index;

	/* Search all sub-records */
	for (Index = 0; Index < m_SubRecords.GetSize(); Index++) {
		pSubRec = m_SubRecords.GetAt(Index);
		Result = pSubRec->Find(FindData);

		if (Result) {
			return (true);
		}
	}

	/* No match */
	return (false);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmRecord Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmRecord::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ID:
			return (GetID());

		case ESM_FIELD_ITEMTYPE:
			return (GetItemType());

		case ESM_FIELD_COUNT:
			snprintf(s_Buffer, 31, _T("%ld"), m_RefCount);
			return (s_Buffer);

		case ESM_FIELD_USERDATA:
			snprintf(s_Buffer, 31, _T("%ld"), m_UserData);
			return (s_Buffer);

		case ESM_FIELD_PERSIST:
			return (BOOLTOYESNO(IsPersist()));

		case ESM_FIELD_BLOCKED:
			return (BOOLTOYESNO(IsBlocked()));

		case ESM_FIELD_CHANGED:
			if (m_pFile == NULL) {
				snprintf(s_Buffer, 31, _T("%s"), IsDeleted() ? "D" : "");
			} else {
				snprintf(s_Buffer,
				         31,
				         _T("%s%s"),
				         m_pFile->IsActive() ? "*" : "",
				         IsDeleted() ? "D" : "");
			}

			return s_Buffer;

		default:
			return _T("");
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmRecord::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool IsSame (pRecord) const;
 *
 * Checks if the two records are describing the same item.  By default it
 * merely checks the type and IDs.
 *
 *=========================================================================*/
bool CEsmRecord::IsSame(CEsmRecord *pRecord) {
	/* Check types first */
	if (!IsType(pRecord->GetType())) {
		return (false);
	}

	/* Objects are the same type, not check their IDs */
	const TCHAR *pName1 = GetID();
	const TCHAR *pName2 = pRecord->GetID();

	if (pName1 == NULL || pName2 == NULL) {
		return (false);
	}

	if (*pName1 == NULL_CHAR || *pName2 == NULL_CHAR) {
		return (false);
	}

	return (TSTRNICMP(pName1, pName2, MWESM_ID_MAXSIZE2) == 0);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::IsSame()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool IsUsed (pID);
 *
 * Returns true if the input record Id is used in the current record.
 *
 *=========================================================================*/
bool CEsmRecord::IsUsed(const TCHAR *pID) {
	CEsmSubRecord *pSubRecord;
	int Index;
	int Result;

	/* Ignore if this record might be the same */
	if (IsID(pID)) {
		return (false);
	}

	/* Look through all sub-records */
	for (Index = 0; Index < m_SubRecords.GetNumElements(); Index++) {
		pSubRecord = m_SubRecords.GetAt(Index);
		Result = pSubRecord->IsUsed(pID);

		if (Result) {
			return (true);
		}
	}

	/* No match found */
	return (false);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::IsUsed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmRecord::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DELE)) {
		m_pDelete = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NAME)) {
		m_pID = (CEsmSubName *)pSubRecord;
	}
}

/*===========================================================================
 *      End of Class Event CEsmRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool Read (File);
 *
 * Inputs the record from the current position in the file (after the
 * record type string). Returns false on any error.
 *
 *=========================================================================*/
bool CEsmRecord::Read(CGenFile &File) {
	bool Result;
	/* Delete the current record information, if any */
	Destroy();
	/* Input the record header and sub-record data */
	Result = ReadHeader(File);

	if (Result) {
		Result = ReadData(File);
	}

	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool ReadData (File);
 *
 * Protected clss virtual method to input the sub-record data from the current
 * position in the file.  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmRecord::ReadData(CGenFile &File) {
	DEFINE_FUNCTION("CEsmRecord::ReadData()");
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
			return (false);
		}

		/* Allocate the subrecord pointer */
		pSubRecord = AllocateSubRecord(Type, RecordSize);
		/* Read the sub-record data */
		Result = pSubRecord->Read(File);

		if (!Result) {
			return (true);
		}
	}

	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool ReadHeader (File);
 *
 * Protected clss virtual method to input the record header from the current
 * position in the file (after the record type string).  Returns false on
 * any error.
 *
 *=========================================================================*/
bool CEsmRecord::ReadHeader(CGenFile &File) {
	bool Result;
	Result = File.ReadLong(m_RecordSize);
	Result &= File.ReadLong(m_Header1);
	Result &= File.ReadLong(m_Flags);
	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::ReadHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool RemoveSubRecord (pSubRecord);
 *
 *=========================================================================*/
bool CEsmRecord::RemoveSubRecord(CEsmSubRecord *pSubRecord) {
	DEFINE_FUNCTION("CEsmRecord::RemoveSubRecord()");

	/* Ensure valid input */
	if (pSubRecord == NULL) {
		return (false);
	}

	m_SubRecords.DeleteElement(pSubRecord);
	DestroyPointer(pSubRecord);
	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::RemoveSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - void SetDelete (Flag);
 *
 * Deletes or undeletes the record.
 *
 *=========================================================================*/
void CEsmRecord::SetDelete(const bool Flag) {
	DEFINE_FUNCTION("CEsmRecord::SetDelete()");

	if (!Flag) {
		DeleteSubRecords(MWESM_SUBREC_DELE);
		m_pDelete = NULL;
	} else if (m_pDelete == NULL) {
		AllocateSubRecord(MWESM_SUBREC_DELE);
		ASSERT(m_pDelete != NULL);
		m_pDelete->CreateNew();
	}
}

/*===========================================================================
 *      End of Class Method CEsmRecord::SetDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmRecord::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ID:
			if (*pString == NULL_CHAR) {
				return (false);
			}

			SetID(pString);
			return (true);

		case ESM_FIELD_COUNT:
			m_RefCount = atoi(pString);
			return (true);

		case ESM_FIELD_USERDATA:
			m_UserData = atol(pString);
			return (true);

		case ESM_FIELD_PERSIST:
			SetPersist(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_BLOCKED:
			SetBlocked(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_DELETE:
			SetDelete(StringToBoolean(pString));
			return (true);
	};

	/* No matching field found */
	ErrorHandler.AddError(ERR_BADINPUT, _T("Unknown field ID %d specified!"), FieldID);

	return (false);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool Write (File);
 *
 * Output the entire record to the given file. Returns false on any error.
 *
 *=========================================================================*/
bool CEsmRecord::Write(CGenFile &File) {
	bool Result;
	long StartOffset;
	long EndOffset;
	/* Output the record header */
	Result = WriteHeader(File);

	if (!Result) {
		return (false);
	}

	/* Save the start of the sub-record data */
	StartOffset = File.Tell();
	/* Output the record sub-records */
	Result = WriteData(File);

	if (!Result) {
		return (false);
	}

	/* Update the record size */
	EndOffset = File.Tell();
	File.Seek(StartOffset - MWESM_RECSIZE_OFFSET, SEEK_SET);
	m_RecordSize = EndOffset - StartOffset;
	Result = File.WriteLong(m_RecordSize);
	File.Seek(EndOffset, SEEK_SET);
	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool WriteHeader (File);
 *
 * Outputs the record header at the current position in the file.  Returns
 * false on any error. Protected class virtual method.
 *
 *=========================================================================*/
bool CEsmRecord::WriteHeader(CGenFile &File) {
	bool Result;
	Result = File.Write(m_Type.pType, MWESM_TYPE_SIZE);
	Result &= File.WriteLong(m_RecordSize); /* This will be updated after the sub-records have been written */
	Result &= File.WriteLong(m_Header1);
	Result &= File.WriteLong(m_Flags);
	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::WriteHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - bool WriteData (File);
 *
 * Protected class virtual method to output the record sub-record data to
 * the file.  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmRecord::WriteData(CGenFile &File) {
	bool Result;
	int Index;

	/* Output all sub-records in the array */
	for (Index = 0; Index < m_SubRecords.GetSize(); Index++) {
		Result = m_SubRecords.GetAt(Index)->Write(File);

		if (!Result) {
			return (false);
		}
	}

	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmRecord::WriteData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int _cdecl EsmRecordSort (pElem1, pElem2, lUserData);
 *
 * Compares two Records using their IDs.
 *
 *=========================================================================*/
int _cdecl EsmRecordSort(const void *pElem1, const void *pElem2, const long lUserData) {
	CEsmRecord *pRecord1 = (CEsmRecord *)pElem1;
	CEsmRecord *pRecord2 = (CEsmRecord *)pElem2;
	return StringCompare(pRecord1->GetID(), pRecord2->GetID(), false);
}

/*===========================================================================
 *      End of Function _cdecl EsmRecordSort()
 *=========================================================================*/
