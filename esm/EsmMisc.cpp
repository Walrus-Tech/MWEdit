/*===========================================================================
 *
 * File:    EsmMisc.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmMisc.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmMisc.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmMisc::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MODL, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_ITEX, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_SCRI, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MCDT, CEsmSubMCDT::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Constructor
 *
 *=========================================================================*/
CEsmMisc::CEsmMisc () {
	//DEFINE_FUNCTION("CEsmMisc::CEsmMisc()");
	m_pMiscData = NULL;
}

/*===========================================================================
 *      End of Class CEsmMisc Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmMisc::Destroy (void) {
	//DEFINE_FUNCTION("CEsmMisc::Destroy()");
	m_pMiscData = NULL;
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmMisc::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmMisc::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	DEFINE_FUNCTION("CEsmMisc::CompareFields()");
	CEsmMisc* pMisc;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_MISC)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pMisc = (CEsmMisc *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			return (GetUnknown() - pMisc->GetUnknown());

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmMisc::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmMisc::Create (void) {
	DEFINE_FUNCTION("CEsmMisc::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmMisc);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmMisc::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmMisc::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_MCDT);
	m_pMiscData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmMisc::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmMisc Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmMisc::GetFieldString (const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			snprintf (s_Buffer, 31, _T("%ld"), GetUnknown());
			return (s_Buffer);

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmMisc::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmMisc::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_MCDT)) {
		m_pMiscData = (CEsmSubMCDT *) pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmMisc::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMisc Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmMisc::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_UNKNOWN:
			GetMiscData()->Unknown = atol(pString);
			return (true);
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmMisc::SetFieldValue()
 *=========================================================================*/