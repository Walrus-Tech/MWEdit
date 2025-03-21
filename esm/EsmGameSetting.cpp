/*===========================================================================
 *
 * File:    EsmGameSetting.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmGameSetting.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmGameSetting.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmGameSetting::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FLTV, CEsmSubFloat::Create },
	{ MWESM_SUBREC_INTV, CEsmSubLong::Create },
	{ MWESM_SUBREC_STRV, CEsmSubName::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Constructor
 *
 *=========================================================================*/
CEsmGameSetting::CEsmGameSetting () {
	//DEFINE_FUNCTION("CEsmGameSetting::CEsmGameSetting()");
	m_pLongData = NULL;
	m_pStringData = NULL;
	m_pFloatData = NULL;
}

/*===========================================================================
 *      End of Class CEsmGameSetting Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmGameSetting::Destroy (void) {
	//DEFINE_FUNCTION("CEsmGameSetting::Destroy()");
	m_pLongData = NULL;
	m_pStringData = NULL;
	m_pFloatData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmGameSetting::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmGameSetting* pSetting;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_GMST)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSetting = (CEsmGameSetting *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_VALUE:
			return StringCompare(GetValue(), pSetting->GetValue(), false);

		case ESM_FIELD_TYPE:
			return StringCompare(GetTypeString(), pSetting->GetTypeString(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmGameSetting::Create (void) {
	DEFINE_FUNCTION("CEsmGameSetting::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmGameSetting);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmGameSetting::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_STRV);
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmGameSetting Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmGameSetting::GetFieldString (const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_VALUE:
			return GetValue();

		case ESM_FIELD_TYPE:
			return GetTypeString();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmGameSetting::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmGameSetting Method - const TCHAR*  GetTypeString (void);
 *
 *=========================================================================*/
const TCHAR *CEsmGameSetting::GetTypeString (void) {
	switch (GetType()) {
		case MWESM_SETTING_INTEGER:
			return _T("Integer");

		case MWESM_SETTING_FLOAT:
			return _T("Float");

		case MWESM_SETTING_STRING:
			return _T("String");

		default:
			return _T("Unknown");
	}
}

int CEsmGameSetting::GetType (const TCHAR* pString) {
	if (stricmp(pString, _T("Integer")) == 0) {
		return (MWESM_SETTING_INTEGER);
	}

	if (stricmp(pString, _T("Float")) == 0) {
		return (MWESM_SETTING_FLOAT);
	}

	if (stricmp(pString, _T("String")) == 0) {
		return (MWESM_SETTING_STRING);
	}

	return (MWESM_SETTING_INTEGER);
}


int CEsmGameSetting::GetType (void) {
	if (m_pLongData != NULL) {
		return MWESM_SETTING_INTEGER;
	}

	if (m_pFloatData != NULL) {
		return MWESM_SETTING_FLOAT;
	}

	return MWESM_SETTING_STRING;
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmGameSetting::GetType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmGameSetting Method - const TCHAR* GetValue (void);
 *
 * Return a string representation of the current setting value.
 *
 *=========================================================================*/
const TCHAR *CEsmGameSetting::GetValue (void) {
	static TCHAR s_Buffer[32];

	if (m_pStringData != NULL) {
		return (m_pStringData->GetName());
	}

	if (m_pLongData != NULL) {
		snprintf (s_Buffer, 31, _T("%ld"), m_pLongData->GetValue());
		return (s_Buffer);
	}

	if (m_pFloatData != NULL) {
		snprintf (s_Buffer, 31, _T("%g"), m_pFloatData->GetValue());
		return (s_Buffer);
	}

	return _T("");
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmGameSetting::GetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmGameSetting::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_INTV)) {
		m_pLongData = (CEsmSubLong *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FLTV)) {
		m_pFloatData = (CEsmSubFloat *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_STRV)) {
		m_pStringData = (CEsmSubName *) pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmGameSetting::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmGameSetting::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_VALUE:
			SetValue(pString);
			return (true);

		case ESM_FIELD_TYPE:
			SetType(pString);
			return (true);
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmGameSetting Method - void SetGMSTType (pString);
 *
 *=========================================================================*/
void CEsmGameSetting::SetGMSTType (const TCHAR* pString) {
	int Type = GetType(pString);

	switch (Type) {
		case MWESM_SETTING_INTEGER:
			if (m_pLongData != NULL) {
				return;
			}

			DeleteSubRecords(MWESM_SUBREC_FLTV);
			DeleteSubRecords(MWESM_SUBREC_STRV);
			m_pStringData = NULL;
			m_pFloatData = NULL;
			AllocateSubRecord(MWESM_SUBREC_INTV);
			break;

		case MWESM_SETTING_FLOAT:
			if (m_pFloatData != NULL) {
				return;
			}

			DeleteSubRecords(MWESM_SUBREC_INTV);
			DeleteSubRecords(MWESM_SUBREC_STRV);
			m_pLongData = NULL;
			m_pStringData = NULL;
			AllocateSubRecord(MWESM_SUBREC_FLTV);
			break;

		case MWESM_SETTING_STRING:
			if (m_pStringData != NULL) {
				return;
			}

			DeleteSubRecords(MWESM_SUBREC_FLTV);
			DeleteSubRecords(MWESM_SUBREC_INTV);
			m_pLongData = NULL;
			m_pFloatData = NULL;
			AllocateSubRecord(MWESM_SUBREC_STRV);
			break;
	}
}

/*===========================================================================
 *      End of Class Method CEsmGameSetting::SetGMSTType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmGameSetting Method - void SetValue (pString);
 *
 * Sets the setting value.
 *
 *=========================================================================*/
void CEsmGameSetting::SetValue (const TCHAR* pString) {
	static TCHAR s_Buffer[32];

	/* Set according to the current setting value */
	if (m_pLongData != NULL) {
		m_pLongData->SetValue(atoi(pString));
	} else if (m_pFloatData != NULL) {
		m_pFloatData->SetValue((float)atof(pString));
	} else if (m_pStringData != NULL) {
		m_pStringData->SetName(pString);
	}
	/* Create the string by default */
	else {
		AllocateSubRecord(MWESM_SUBREC_STRV);
		m_pStringData->SetName(pString);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmGameSetting::SetValue()
 *=========================================================================*/

