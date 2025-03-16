/*===========================================================================
 *
 * File:    EsmDialogue.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmDialogue.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmDialogue.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmDialogue::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_DATA, CEsmSubRecord::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


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
 *      End of Dialogue Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Constructor
 *
 *=========================================================================*/
CEsmDialogue::CEsmDialogue () {
	//DEFINE_FUNCTION("CEsmDialogue::CEsmDialogue()");
	m_pData = NULL;
}

/*===========================================================================
 *      End of Class CEsmDialogue Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmDialogue::Destroy (void) {
	//DEFINE_FUNCTION("CEsmDialogue::Destroy()");
	m_pData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmDialogue::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmDialogue::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmDialogue* pDialog;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_DIAL)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pDialog = (CEsmDialogue *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return StringCompare(GetDialogType(), pDialog->GetDialogType(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmDialogue::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmDialogue::Create (void) {
	DEFINE_FUNCTION("CEsmDialogue::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmDialogue);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmDialogue::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmDialogue::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	m_pData->CreateNew(1);
}

/*===========================================================================
 *      End of Class Method CEsmDialogue::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmDialogue Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmDialogue::GetFieldString (const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return GetDialogType();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmDialogue::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmDialogue Method - const GetItemType (void);
 *
 *=========================================================================*/
const TCHAR *CEsmDialogue::GetItemType (void) {
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
 *      End of Class Method TCHAR* CEsmDialogue::GetItemType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmDialogue Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmDialogue::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmArmor::CEsmDialogue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMDialogType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMDialogType (const int Type) {
	if (Type < MWESM_DIALTYPE_MIN || Type > MWESM_DIALTYPE_MAX) {
		return _T("Unknown");
	}

	return l_DialogueTypes[Type];
}

/*===========================================================================
 *      End of Function TCHAR* GetESMDialogType()
 *=========================================================================*/
