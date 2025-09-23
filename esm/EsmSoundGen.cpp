/*===========================================================================
 *
 * File:    EsmSoundGen.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "EsmSoundGen.h"


DEFINE_FILE("EsmSoundGen.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmSoundGen::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubLong::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Begin String Arrays
 *
 *=========================================================================*/
const TCHAR *l_SoundGenTypes[] = {
	_T("Left Foot"),
	_T("Right Foot"),
	_T("Swim Left"),
	_T("Swim Right"),
	_T("Moan"),
	_T("Roar"),
	_T("Scream"),
	_T("Land"),
};


/*===========================================================================
 *
 * Class CEsmSoundGen Constructor
 *
 *=========================================================================*/
CEsmSoundGen::CEsmSoundGen() {
	//DEFINE_FUNCTION("CEsmSoundGen::CEsmSoundGen()");
	m_pSoundName = NULL;
	m_pTypeData = NULL;
	m_pCreatureName = NULL;
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmSoundGen::Destroy() {
	//DEFINE_FUNCTION("CEsmSoundGen::Destroy()");
	m_pSoundName = NULL;
	m_pTypeData = NULL;
	m_pCreatureName = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmSoundGen::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmSoundGen *pSoundGen;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_SNDG)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSoundGen = (CEsmSoundGen *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_CREATURE:
			return StringCompare(GetCreature(), pSoundGen->GetCreature(), false);

		case ESM_FIELD_TYPE:
			return GetSoundType() - pSoundGen->GetSoundType();

		case ESM_FIELD_SOUND:
			return StringCompare(GetSound(), pSoundGen->GetSound(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmSoundGen::Create() {
	DEFINE_FUNCTION("CEsmSoundGen::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmSoundGen);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmSoundGen::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_SNAM);
	AllocateSubRecord(MWESM_SUBREC_DATA);
	m_pTypeData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmSoundGen Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmSoundGen::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return GetTypeString();

		case ESM_FIELD_SOUND:
			return GetSound();

		case ESM_FIELD_CREATURE:
			return GetCreature();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmSoundGen Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmSoundGen::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_SNAM)) {
		m_pSoundName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CNAM)) {
		m_pCreatureName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pTypeData = (CEsmSubLong *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmSoundGen::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_TYPE: {
			int Type = GetESMSoundGenType(pString);

			if (Type >= 0) {
				SetSoundType(Type);
			}

			return true;
		}

		case ESM_FIELD_SOUND:
			SetSound(pString);
			return true;

		case ESM_FIELD_CREATURE:
			SetCreature(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}


/*===========================================================================
 *
 * Class CEsmSoundGen Method - void SetCreature (pString);
 *
 *=========================================================================*/
void CEsmSoundGen::SetCreature(const TCHAR *pString) {
	/* Delete the creature record */
	if (pString == NULL || *pString == NULL_CHAR) {
		if (m_pCreatureName != NULL) {
			DeleteSubRecords(MWESM_SUBREC_CNAM);
		}

		m_pCreatureName = NULL;
	} else if (m_pCreatureName == NULL) { /* Set the creature record, create if required */
		AllocateSubRecord(MWESM_SUBREC_CNAM);
		m_pCreatureName->SetName(pString);
	} else {
		m_pCreatureName->SetName(pString);
	}
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMSoundGenType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMSoundGenType(const int Type) {
	if (Type < MWESM_SNDGEN_MIN || Type > MWESM_SNDGEN_MAX) {
		return _T("Unknown");
	}

	return l_SoundGenTypes[Type];
}

int GetESMSoundGenType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_SNDGEN_MIN; Index <= MWESM_SNDGEN_MAX; Index++) {
		if (stricmp(pString, l_SoundGenTypes[Index]) == 0) {
			return Index;
		}
	}

	return -1;
}
