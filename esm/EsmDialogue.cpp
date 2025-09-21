/*===========================================================================
 *
 * File:    EsmDialogue.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmDialogue.h"


DEFINE_FILE("EsmDialogue.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmDialogue::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubRecord::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Begin Dialogue Type Array
 *
 *=========================================================================*/
const TCHAR *l_DialogueTypes[] = {
	_T("Topic"),
	_T("Voice"),
	_T("Greeting"),
	_T("Persuasion"),
	_T("Journal")
};


/*===========================================================================
 *
 * Class CEsmDialogue Constructor
 *
 *=========================================================================*/
CEsmDialogue::CEsmDialogue() {
	//DEFINE_FUNCTION("CEsmDialogue::CEsmDialogue()");
	m_pData = NULL;
}


/*===========================================================================
 *
 * Class CEsmDialogue Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmDialogue::Destroy() {
	//DEFINE_FUNCTION("CEsmDialogue::Destroy()");
	m_pData = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmDialogue Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmDialogue::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmDialogue *pDialog;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_DIAL)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pDialog = (CEsmDialogue *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return StringCompare(GetDialogType(), pDialog->GetDialogType(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmDialogue Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmDialogue::Create() {
	DEFINE_FUNCTION("CEsmDialogue::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmDialogue);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmDialogue Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmDialogue::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	m_pData->CreateNew(1);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmDialogue Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmDialogue::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return GetDialogType();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class TCHAR* CEsmDialogue Method - const GetItemType (void);
 *
 *=========================================================================*/
const TCHAR *CEsmDialogue::GetItemType() {
	switch (GetDialogTypeID()) {
		case MWESM_DIALTYPE_TOPIC:
			return _T("Dialogue");

		case MWESM_DIALTYPE_VOICE:
			return _T("Voice");

		case MWESM_DIALTYPE_GREETING:
			return _T("Greeting");

		case MWESM_DIALTYPE_PERSUASION:
			return _T("Persuasion");

		case MWESM_DIALTYPE_JOURNAL:
			return _T("Journal");

		default:
			return _T("Dialogue");
	}
}


/*===========================================================================
 *
 * Class CEsmDialogue Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmDialogue::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMDialogType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMDialogType(const int Type) {
	if (Type < MWESM_DIALTYPE_MIN || Type > MWESM_DIALTYPE_MAX) {
		return _T("Unknown");
	}

	return l_DialogueTypes[Type];
}
