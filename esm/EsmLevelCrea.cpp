/*===========================================================================
 *
 * File:    EsmLevelCrea.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmLevelCrea.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmLevelCrea.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmLevelCrea::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_NNAM,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_INDX,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_CNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_INTV,
		CEsmSubShort::Create
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
 * Class CEsmLevelCrea Constructor
 *
 *=========================================================================*/
CEsmLevelCrea::CEsmLevelCrea() {
	//DEFINE_FUNCTION("CEsmLevelCrea::CEsmLevelCrea()");
	m_pData = NULL;
	m_pNNam = NULL;
	m_pIndex = NULL;
}

/*===========================================================================
 *      End of Class CEsmLevelCrea Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmLevelCrea::Destroy(void) {
	//DEFINE_FUNCTION("CEsmLevelCrea::Destroy()");
	m_pData = NULL;
	m_pNNam = NULL;
	m_pIndex = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmLevelCrea::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmLevelCrea::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmLevelCrea *pLevelCrea;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_LEVC)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pLevelCrea = (CEsmLevelCrea *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_ALLPC:
			return (int)IsAllPC() - (int)pLevelCrea->IsAllPC();

		case ESM_FIELD_LIST:
			return (0);

		case ESM_FIELD_CHANCENONE:
			return GetChanceNone() - pLevelCrea->GetChanceNone();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmLevelCrea::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmLevelCrea::Create(void) {
	DEFINE_FUNCTION("CEsmLevelCrea::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmLevelCrea);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmLevelCrea::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmLevelCrea::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_NNAM);
	AllocateSubRecord(MWESM_SUBREC_INDX);
	m_pIndex->CreateNew();
	m_pData->CreateNew();
	m_pNNam->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmLevelCrea::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmLevelCrea Method - const TCHR* GetCreaListString (void);
 *
 * Uses a local static buffer to create a list of the current creatures
 * in the levelled list (up to 256 bytes).
 *
 *=========================================================================*/
const TCHAR *CEsmLevelCrea::GetCreaListString(void) {
	static TCHAR s_Buffer[256];
	TCHAR TempBuffer[32];
	CEsmSubNameFix *pNameSubRec;
	CEsmSubRecord *pLevelSubRec;
	int ArrayIndex;
	int BufferLength;
	int StringLength;
	pNameSubRec = (CEsmSubNameFix *)FindFirst(MWESM_SUBREC_CNAM, ArrayIndex);
	s_Buffer[0] = NULL_CHAR;
	BufferLength = 0;

	while (pNameSubRec != NULL) {
		pLevelSubRec = GetSubRecord(ArrayIndex + 1);

		if (pLevelSubRec->IsType(MWESM_SUBREC_INTV)) {
			StringLength = TSTRLEN(pNameSubRec->GetName());

			if (StringLength + BufferLength > 255) {
				break;
			}

			TSTRCPY(s_Buffer + BufferLength, pNameSubRec->GetName());
			BufferLength += StringLength;
			snprintf(TempBuffer,
			         31,
			         _T(" (%d), "),
			         (int)((CEsmSubShort *)pLevelSubRec)->GetValue());
			StringLength = TSTRLEN(TempBuffer);

			if (StringLength + BufferLength > 255) {
				break;
			}

			TSTRCPY(s_Buffer + BufferLength, TempBuffer);
			BufferLength += StringLength;
		}

		pNameSubRec = (CEsmSubNameFix *)FindNext(MWESM_SUBREC_CNAM, ArrayIndex);
	}

	return (s_Buffer);
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmLevelCrea::GetCreaListString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmLevelCrea Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmLevelCrea::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ALLPC:
			return (BOOLTOYESNO(IsAllPC()));

		case ESM_FIELD_LIST:
			return GetCreaListString();

		case ESM_FIELD_CHANCENONE:
			snprintf(s_Buffer, 31, _T("%d"), GetChanceNone());
			return (s_Buffer);

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmLevelCrea::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmLevelCrea::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NNAM)) {
		m_pNNam = (CEsmSubByte *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_INDX)) {
		m_pIndex = (CEsmSubLong *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmLevelCrea::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLevelCrea Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmLevelCrea::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ALLPC:
			SetAllPC(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_CHANCENONE:
			SetChanceNone(atoi(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmLevelCrea::SetFieldValue()
 *=========================================================================*/
