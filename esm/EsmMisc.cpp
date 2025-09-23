/*===========================================================================
 *
 * File:    EsmMisc.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "EsmMisc.h"


DEFINE_FILE("EsmMisc.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmMisc::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_MODL,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ITEX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SCRI,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_MCDT,
		CEsmSubMCDT::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmMisc Constructor
 *
 *=========================================================================*/
CEsmMisc::CEsmMisc() {
	//DEFINE_FUNCTION("CEsmMisc::CEsmMisc()");
	m_pMiscData = NULL;
}


/*===========================================================================
 *
 * Class CEsmMisc Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmMisc::Destroy() {
	//DEFINE_FUNCTION("CEsmMisc::Destroy()");
	m_pMiscData = NULL;
	CEsmItem2::Destroy();
}


/*===========================================================================
 *
 * Class CEsmMisc Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmMisc::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmMisc::CompareFields()");
	CEsmMisc *pMisc;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_MISC)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pMisc = (CEsmMisc *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			return GetUnknown() - pMisc->GetUnknown();

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmMisc Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmMisc::Create() {
	DEFINE_FUNCTION("CEsmMisc::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmMisc);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmMisc Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmMisc::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_MCDT);
	m_pMiscData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmMisc Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmMisc::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			snprintf(s_Buffer, 31, _T("%ld"), GetUnknown());
			return s_Buffer;

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmMisc Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmMisc::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_MCDT)) {
		m_pMiscData = (CEsmSubMCDT *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmMisc Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmMisc::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			GetMiscData()->Unknown = atol(pString);
			return true;
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}
