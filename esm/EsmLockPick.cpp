/*===========================================================================
 *
 * File:    EsmLockPick.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmLockPick.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmLockPick.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmLockPick::s_SubRecCreate[] = {
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
		CEsmSubName::Create
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
		MWESM_SUBREC_LKDT,
		CEsmSubLKDT::Create
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
 * Class CEsmLockPick Constructor
 *
 *=========================================================================*/
CEsmLockPick::CEsmLockPick() {
	//DEFINE_FUNCTION("CEsmLockPick::CEsmLockPick()");
	m_pLockData = NULL;
}

/*===========================================================================
 *      End of Class CEsmLockPick Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmLockPick::Destroy() {
	//DEFINE_FUNCTION("CEsmLockPick::Destroy()");
	m_pLockData = NULL;
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmLockPick::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmLockPick::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmLockPick::CompareFields()");
	CEsmLockPick *pLock;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_LOCK)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pLock = (CEsmLockPick *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_QUALITY:
			return (int)(GetQuality() * 100 - pLock->GetQuality() * 100);

		case ESM_FIELD_USES:
			return GetUses() - pLock->GetUses();

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmLockPick::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmLockPick::Create() {
	DEFINE_FUNCTION("CEsmLockPick::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmLockPick);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmLockPick::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmLockPick::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_LKDT);
	m_pLockData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmLockPick::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmLockPick Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmLockPick::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmLockPick::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_USES:
			snprintf(s_Buffer, 31, _T("%ld"), GetUses());
			return s_Buffer;

		case ESM_FIELD_QUALITY:
			snprintf(s_Buffer, 31, _T("%.2f"), GetQuality());
			return s_Buffer;

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmLockPick::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmLockPick::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_LKDT)) {
		m_pLockData = (CEsmSubLKDT *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmLockPick::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLockPick Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmLockPick::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_USES:
			SetUses(atol(pString));
			return true;

		case ESM_FIELD_QUALITY:
			SetQuality((float)atof(pString));
			return true;
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmLockPick::SetFieldValue()
 *=========================================================================*/
