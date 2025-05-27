/*===========================================================================
 *
 * File:    EsmFaction.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmFaction.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmFaction.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmFaction::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_RNAM,
		CEsmSubName32::Create
	},
	{
		MWESM_SUBREC_ANAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_INTV,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_FADT,
		CEsmSubFADT::Create
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
 * Class CEsmFaction Constructor
 *
 *=========================================================================*/
CEsmFaction::CEsmFaction() {
	//DEFINE_FUNCTION("CEsmFaction::CEsmFaction()");
	m_pName = NULL;
	m_pFactionData = NULL;
	m_NumRankNames = 0;
}

/*===========================================================================
 *      End of Class CEsmFaction Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmFaction::Destroy(void) {
	//DEFINE_FUNCTION("CEsmFaction::Destroy()");
	m_pName = NULL;
	m_pFactionData = NULL;
	m_NumRankNames = 0;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmFaction::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmFaction::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmFaction *pFaction;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_FACT)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pFaction = (CEsmFaction *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pFaction->GetName(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmFaction::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmFaction::Create(void) {
	DEFINE_FUNCTION("CEsmFaction::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmFaction);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFaction::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmFaction::CreateNew(CEsmFile *pFile) {
	CEsmSubRecord *pSubRec;
	int Index;
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);

	for (Index = 0; Index < MWESM_FACTION_NUMRANKS; Index++) {
		pSubRec = AllocateSubRecord(MWESM_SUBREC_RNAM);
		pSubRec->CreateNew();
	}

	AllocateSubRecord(MWESM_SUBREC_FADT);
	m_pFactionData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmFaction::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmFaction Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmFaction::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmFaction::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmFaction Method - const GetRankName (Rank);
 *
 * Returns the rank name for the given rank (0 to 9) or NULL if it is not
 * defined.
 *
 *=========================================================================*/
const TCHAR *CEsmFaction::GetRankName(const int Rank) {
	if (Rank < 0 || Rank >= m_NumRankNames) {
		return _T("");
	}

	if (m_pRankNames[Rank] == NULL) {
		return _T("");
	}

	return m_pRankNames[Rank]->GetName();
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmFaction::GetRankName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmFaction::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FADT)) {
		m_pFactionData = (CEsmSubFADT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_RNAM)) {
		if (m_NumRankNames < MWESM_FACTION_NUMRANKS) {
			m_pRankNames[m_NumRankNames] = (CEsmSubName32 *)pSubRecord;
			m_NumRankNames++;
		}
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmFaction::CEsmFaction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmFaction::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return (true);
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmFaction::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFaction Method - void SetRankName (Rank, pString);
 *
 * Sets the given rank name (0 to 9).
 *
 *=========================================================================*/
void CEsmFaction::SetRankName(const int Rank, const TCHAR *pString) {
	int Index;

	/* Ignore any invalid input */
	if (Rank < 0 || Rank >= MWESM_FACTION_NUMRANKS) {
		return;
	}

	/* Create the rank name if required */
	for (Index = m_NumRankNames; Index < Rank; Index++) {
		AllocateSubRecord(MWESM_SUBREC_RNAM);
	}

	/* Check array pointer just in case */
	if (m_pRankNames[Rank] == NULL) {
		return;
	}

	m_pRankNames[Rank]->SetName(pString);
}

/*===========================================================================
 *      End of Class Method CEsmFaction::SetRankName()
 *=========================================================================*/
