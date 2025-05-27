/*===========================================================================
 *
 * File:    EsmRegion.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmRegion.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmRegion.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmRegion::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_BNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CNAM,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_SNAM,
		CEsmSubSNAM::Create
	},
	{
		MWESM_SUBREC_WEAT,
		CEsmSubWEAT::Create
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
 * Class CEsmRegion Constructor
 *
 *=========================================================================*/
CEsmRegion::CEsmRegion() {
	//DEFINE_FUNCTION("CEsmRegion::CEsmRegion()");
	m_pNameData = NULL;
	m_pWeatherData = NULL;
	m_pCreatureData = NULL;
	m_pColorData = NULL;
}

/*===========================================================================
 *      End of Class CEsmRegion Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmRegion::Destroy(void) {
	//DEFINE_FUNCTION("CEsmRegion::Destroy()");
	m_pNameData = NULL;
	m_pWeatherData = NULL;
	m_pCreatureData = NULL;
	m_pColorData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmRegion::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmRegion::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmRegion *pRegion;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_REGN)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pRegion = (CEsmRegion *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pRegion->GetName(), false);

		case ESM_FIELD_CREATURE:
			return StringCompare(GetCreature(), pRegion->GetCreature(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRegion::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmRegion::Create(void) {
	DEFINE_FUNCTION("CEsmRegion::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmRegion);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmRegion::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmRegion::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_WEAT);
	AllocateSubRecord(MWESM_SUBREC_CNAM);
	m_pWeatherData->CreateNew();
	m_pColorData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmRegion::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmRegion Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmRegion::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_CREATURE:
			return GetCreature();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmRegion::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmRegion::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pNameData = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_BNAM)) {
		m_pCreatureData = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_WEAT)) {
		m_pWeatherData = (CEsmSubWEAT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CNAM)) {
		m_pColorData = (CEsmSubLong *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmRegion::CEsmRegion()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRegion Method - void SetCreature (pString);
 *
 *=========================================================================*/
void CEsmRegion::SetCreature(const TCHAR *pString) {
	/* Delete the creature record */
	if (pString == NULL || *pString == NULL_CHAR) {
		if (m_pCreatureData != NULL) {
			DeleteSubRecords(MWESM_SUBREC_BNAM);
		}

		m_pCreatureData = NULL;
	} else {
		if (m_pCreatureData == NULL) {
			AllocateSubRecord(MWESM_SUBREC_BNAM);
		}

		m_pCreatureData->SetName(pString);
	}
}

/*===========================================================================
 *      End of Class Method CEsmRegion::SetCreature()
 *=========================================================================*/
