/*===========================================================================
 *
 * File:    EsmStatic.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmStatic.h"


DEFINE_FILE("EsmStatic.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmStatic::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_MODL,
		CEsmSubNameFix::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmStatic Constructor
 *
 *=========================================================================*/
CEsmStatic::CEsmStatic() {
	//DEFINE_FUNCTION("CEsmStatic::CEsmStatic()");
	m_pModel = NULL;
}


/*===========================================================================
 *
 * Class CEsmStatic Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmStatic::Destroy() {
	//DEFINE_FUNCTION("CEsmStatic::Destroy()");
	m_pModel = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmStatic Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmStatic::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmStatic *pStatic;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_STAT)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pStatic = (CEsmStatic *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_MODEL:
			return StringCompare(GetModel(), pStatic->GetModel(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmStatic Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmStatic::Create() {
	DEFINE_FUNCTION("CEsmStatic::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmStatic);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmStatic Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmStatic::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_MODL);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmStatic Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmStatic::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_MODEL:
			return GetModel();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmStatic Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmStatic::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_MODL)) {
		m_pModel = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmStatic Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmStatic::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_MODEL:
			SetModel(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
