/*===========================================================================
 *
 * File:    EsmProbe.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmProbe.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmProbe.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmProbe::s_SubRecCreate[] = {
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
		MWESM_SUBREC_PBDT,
		CEsmSubPBDT::Create
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
 * Class CEsmProbe Constructor
 *
 *=========================================================================*/
CEsmProbe::CEsmProbe() {
	//DEFINE_FUNCTION("CEsmProbe::CEsmProbe()");
	m_pProbeData = NULL;
}

/*===========================================================================
 *      End of Class CEsmProbe Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmProbe::Destroy(void) {
	//DEFINE_FUNCTION("CEsmProbe::Destroy()");
	m_pProbeData = NULL;
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmProbe::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmProbe::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmProbe::CompareFields()");
	CEsmProbe *pProbe;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_PROB)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pProbe = (CEsmProbe *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_QUALITY:
			return (int)(GetQuality() * 100 - pProbe->GetQuality() * 100);

		case ESM_FIELD_USES:
			return GetUses() - pProbe->GetUses();

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmProbe::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmProbe::Create(void) {
	DEFINE_FUNCTION("CEsmProbe::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmProbe);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmProbe::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmProbe::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_PBDT);
	m_pProbeData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmProbe::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmProbe Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmProbe::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmProbe::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_USES:
			snprintf(s_Buffer, 31, _T("%ld"), GetUses());
			return (s_Buffer);

		case ESM_FIELD_QUALITY:
			snprintf(s_Buffer, 31, _T("%.2f"), GetQuality());
			return (s_Buffer);

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmProbe::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmProbe::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_PBDT)) {
		m_pProbeData = (CEsmSubPBDT *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmProbe::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmProbe Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmProbe::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_USES:
			SetUses(atoi(pString));
			return (true);

		case ESM_FIELD_QUALITY:
			SetQuality((float)atof(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmProbe::SetFieldValue()
 *=========================================================================*/
