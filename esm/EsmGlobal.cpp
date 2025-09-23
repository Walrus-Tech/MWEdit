/*===========================================================================
 *
 * File:    EsmGlobal.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "EsmGlobal.h"


DEFINE_FILE("EsmGlobal.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmGlobal::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_FLTV,
		CEsmSubFloat::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmGlobal Constructor
 *
 *=========================================================================*/
CEsmGlobal::CEsmGlobal() {
	//DEFINE_FUNCTION("CEsmGlobal::CEsmGlobal()");
	m_pTypeData = NULL;
	m_pFloatData = NULL;
}


/*===========================================================================
 *
 * Class CEsmGlobal Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmGlobal::Destroy() {
	//DEFINE_FUNCTION("CEsmGlobal::Destroy()");
	m_pTypeData = NULL;
	m_pFloatData = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmGlobal Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmGlobal::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmGlobal *pGlobal;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_GLOB)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pGlobal = (CEsmGlobal *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_VALUE:
			return (int)(GetValue() * 1000 - pGlobal->GetValue() * 1000);

		case ESM_FIELD_TYPE:
			return (int)(GetType() - pGlobal->GetType());

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmGlobal Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmGlobal::Create() {
	DEFINE_FUNCTION("CEsmGlobal::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmGlobal);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmGlobal Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmGlobal::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_FLTV);
	m_pTypeData->CreateNew();
	m_pFloatData->CreateNew();
	SetType(MWESM_GLOBAL_SHORT);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmGlobal Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmGlobal::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_VALUE:
			if (GetType() == MWESM_GLOBAL_FLOAT) {
				snprintf(s_Buffer, 31, _T("%g"), GetValue());
			} else {
				snprintf(s_Buffer, 31, _T("%d"), (int)GetValue());
			}

			return s_Buffer;

		case ESM_FIELD_TYPE:
			return GetTypeString();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class TCHAR* CEsmGlobal Method - const GetTypeString (void);
 *
 *=========================================================================*/
const TCHAR *CEsmGlobal::GetTypeString() {
	switch (GetType()) {
		case MWESM_GLOBAL_FLOAT:
			return _T("float");

		case MWESM_GLOBAL_LONG:
			return _T("long");

		case MWESM_GLOBAL_SHORT:
			return _T("short");

		default:
			return _T("unknown");
	}
}

int CEsmGlobal::GetTypeID(const TCHAR *pString) {
	if (stricmp(pString, _T("float")) == 0) {
		return MWESM_GLOBAL_FLOAT;
	}

	if (stricmp(pString, _T("long")) == 0) {
		return MWESM_GLOBAL_LONG;
	}

	if (stricmp(pString, _T("short")) == 0) {
		return MWESM_GLOBAL_SHORT;
	}

	return MWESM_GLOBAL_FLOAT;
}


/*===========================================================================
 *
 * Class CEsmGlobal Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmGlobal::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pTypeData = (CEsmSubByte *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FLTV)) {
		m_pFloatData = (CEsmSubFloat *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmGlobal Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmGlobal::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_VALUE:
			SetValue((float)atof(pString));
			return true;

		case ESM_FIELD_TYPE: {
			int Type = GetTypeID(pString);
			SetType(Type);
			return true;
		}
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
