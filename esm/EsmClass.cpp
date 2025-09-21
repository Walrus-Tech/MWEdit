/*===========================================================================
 *
 * File:    EsmClass.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmClass.h"


DEFINE_FILE("EsmClass.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmClass::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DESC,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_CLDT,
		CEsmSubCLDT::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmClass Constructor
 *
 *=========================================================================*/
CEsmClass::CEsmClass() {
	//DEFINE_FUNCTION("CEsmClass::CEsmClass()");
	m_pName = NULL;
	m_pData = NULL;
	m_pDescription = NULL;
}


/*===========================================================================
 *
 * Class CEsmClass Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmClass::Destroy() {
	//DEFINE_FUNCTION("CEsmClass::Destroy()");
	m_pName = NULL;
	m_pData = NULL;
	m_pDescription = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmClass Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmClass::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmClass *pClass;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_CLAS)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pClass = (CEsmClass *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pClass->GetName(), false);

		case ESM_FIELD_PLAYABLE:
			return (int)IsPlayable() - (int)pClass->IsPlayable();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmClass Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmClass::Create() {
	DEFINE_FUNCTION("CEsmClass::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmClass);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmClass Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmClass::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_DESC);
	AllocateSubRecord(MWESM_SUBREC_CLDT);
	m_pData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmClass Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmClass::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_PLAYABLE:
			return BOOLTOYESNO(IsPlayable());

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmClass Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmClass::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DESC)) {
		m_pDescription = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CLDT)) {
		m_pData = (CEsmSubCLDT *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmClass Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmClass::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return true;

		case ESM_FIELD_DESC:
			SetDescription(pString);
			return true;

		case ESM_FIELD_PLAYABLE:
			SetPlayable(StringToBoolean(pString));
			return true;
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
