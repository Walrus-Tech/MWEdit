/*===========================================================================
 *
 * File:    Esmstartscript.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 13, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "esm/EsmStartScript.h"


DEFINE_FILE("EsmStartScript.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmStartScript::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_DATA,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmStartScript Constructor
 *
 *=========================================================================*/
CEsmStartScript::CEsmStartScript() {
	//DEFINE_FUNCTION("CEsmStartScript::CEsmStartScript()");
	m_pName = NULL;
}


/*===========================================================================
 *
 * Class CEsmStartScript Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmStartScript::Destroy() {
	//DEFINE_FUNCTION("CEsmStartScript::Destroy()");
	m_pName = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmStartScript Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmStartScript::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmStartScript *pStartScript;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_SSCR)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pStartScript = (CEsmStartScript *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pStartScript->GetName(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmStartScript Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmStartScript::Create() {
	DEFINE_FUNCTION("CEsmStartScript::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmStartScript);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmStartScript Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmStartScript::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_NAME);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmStartScript Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmStartScript::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmStartScript Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmStartScript::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pID = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NAME)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmStartScript Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmStartScript::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
