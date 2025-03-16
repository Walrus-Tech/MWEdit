/*===========================================================================
 *
 * File:    EsmRace.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmRace.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmRace.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmRace::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_DESC, CEsmSubName::Create },
	{ MWESM_SUBREC_NPCS, CEsmSubName32::Create },
	{ MWESM_SUBREC_RADT, CEsmSubRADT::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Constructor
 *
 *=========================================================================*/
CEsmRace::CEsmRace () {
	//DEFINE_FUNCTION("CEsmRace::CEsmRace()");
	m_pNameData = NULL;
	m_pDescData = NULL;
	m_pRaceData = NULL;
}

/*===========================================================================
 *      End of Class CEsmRace Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmRace::Destroy (void) {
	//DEFINE_FUNCTION("CEsmRace::Destroy()");
	m_pNameData = NULL;
	m_pDescData = NULL;
	m_pRaceData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmRace::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmRace::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmRace* pRace;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_RACE)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pRace = (CEsmRace *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pRace->GetName(), false);

		case ESM_FIELD_PLAYABLE:
			return (int)IsPlayable() - (int)pRace->IsPlayable();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRace::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmRace::Create (void) {
	DEFINE_FUNCTION("CEsmRace::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmRace);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRace::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmRace::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_RADT);
	AllocateSubRecord(MWESM_SUBREC_DESC);
	m_pRaceData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmRace::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmRace Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmRace::GetFieldString (const int FieldID) {
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
 *      End of Class Method TCHAR* CEsmRace::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmRace::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pNameData = (CEsmSubNameFix *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_RADT)) {
		m_pRaceData = (CEsmSubRADT *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DESC)) {
		m_pDescData = (CEsmSubName *) pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmRace::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRace Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmRace::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return (true);

		case ESM_FIELD_DESC:
			SetDescription(pString);
			return (true);

		case ESM_FIELD_PLAYABLE:
			SetPlayable(StringToBoolean(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmRace::SetFieldValue()
 *=========================================================================*/
