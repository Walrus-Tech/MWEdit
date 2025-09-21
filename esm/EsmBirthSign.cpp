/*===========================================================================
 *
 * File:    EsmBirthSign.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmBirthSign.h"


DEFINE_FILE("EsmBirthSign.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmBirthSign::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_TNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DESC,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_NPCS,
		CEsmSubName32::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmBirthSign Constructor
 *
 *=========================================================================*/
CEsmBirthSign::CEsmBirthSign() {
	//DEFINE_FUNCTION("CEsmBirthSign::CEsmBirthSign()");
	m_pNameData = NULL;
	m_pTextureData = NULL;
	m_pDescData = NULL;
}


/*===========================================================================
 *
 * Class CEsmBirthSign Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmBirthSign::Destroy() {
	//DEFINE_FUNCTION("CEsmBirthSign::Destroy()");
	m_pNameData = NULL;
	m_pDescData = NULL;
	m_pTextureData = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmBirthSign Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmBirthSign::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmBirthSign *pSign;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_CLAS)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSign = (CEsmBirthSign *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pSign->GetName(), false);

		case ESM_FIELD_ICON:
			return StringCompare(GetTexture(), pSign->GetTexture(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBirthSign Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmBirthSign::Create() {
	DEFINE_FUNCTION("CEsmBirthSign::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmBirthSign);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmBirthSign Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmBirthSign::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_TNAM);
	AllocateSubRecord(MWESM_SUBREC_DESC);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmBirthSign Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmBirthSign::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_ICON:
			return GetTexture();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmBirthSign Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmBirthSign::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pNameData = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DESC)) {
		m_pDescData = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_TNAM)) {
		m_pTextureData = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBirthSign Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmBirthSign::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return true;

		case ESM_FIELD_DESC:
			SetName(pString);
			return true;

		case ESM_FIELD_ICON:
			SetTexture(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
