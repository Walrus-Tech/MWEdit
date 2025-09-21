/*===========================================================================
 *
 * File:    EsmItem1.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "esmitem1.h"


DEFINE_FILE("EsmItem1.cpp");


/*===========================================================================
 *
 * Class CEsmItem1 Constructor
 *
 *=========================================================================*/
CEsmItem1::CEsmItem1() {
	//DEFINE_FUNCTION("CEsmItem1::CEsmItem1()");
	m_pModel = NULL;
	m_pName = NULL;
	m_pScript = NULL;
}


/*===========================================================================
 *
 * Class CEsmItem1 Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmItem1::Destroy() {
	//DEFINE_FUNCTION("CEsmItem1::Destroy()");
	/* Clear the references */
	m_pModel = NULL;
	m_pName = NULL;
	m_pScript = NULL;
	/* Call the base class method */
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmItem1 Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmItem1::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	//DEFINE_FUNCTION("CEsmItem1::CompareFields()");
	CEsmItem1 *pRecord1;

	/* Ensure the correct type */
	if ((MWESM_CLASSTYPE_ITEM1 & pRecord->GetClassType()) == 0) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pRecord1 = (CEsmItem1 *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pRecord1->GetName(), FALSE);

		case ESM_FIELD_SCRIPT:
			return StringCompare(GetScript(), pRecord1->GetScript(), FALSE);

		case ESM_FIELD_MODEL:
			return StringCompare(GetModel(), pRecord1->GetModel(), FALSE);

		default: /* Call the base class method */
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmItem1 Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmItem1::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_MODL);
}


/*===========================================================================
 *
 * Class TCHAR* CEsmItem1 Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmItem1::GetFieldString(const int FieldID) {
	//DEFINE_FUNCTION("CEsmItem1::GetFieldString()");
	switch (FieldID) {
		case ESM_FIELD_NAME:
			if (m_pName == NULL) {
				return _T("");
			}

			return m_pName->GetName();

		case ESM_FIELD_SCRIPT:
			if (m_pScript == NULL) {
				return _T("");
			}

			return m_pScript->GetName();

		case ESM_FIELD_MODEL:
			if (m_pModel == NULL) {
				return _T("");
			}

			return m_pModel->GetName();

		default:    /* Call the base class record */
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmItem1 Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmItem1::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_MODL)) {
		m_pModel = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_SCRI)) {
		m_pScript = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmItem1 Method - void SetScript (pScript);
 *
 *=========================================================================*/
void CEsmItem1::SetScript(const TCHAR *pScript) {
	DEFINE_FUNCTION("CEsmItem1::SetScript()");

	/* Should we delete the current enchant? */
	if (pScript == NULL || *pScript == NULL_CHAR) {
		if (m_pScript != NULL) {
			RemoveSubRecord(m_pScript);
		}

		m_pScript = NULL;
	}
	/* Create a new enchant sub-record */
	else if (m_pScript == NULL) {
		AllocateSubRecord(MWESM_SUBREC_SCRI);
		ASSERT(m_pScript != NULL);
		m_pScript->SetName(pScript);
	} else {
		m_pScript->SetName(pScript);
	}
}


/*===========================================================================
 *
 * Class CEsmItem1 Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmItem1::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return true;

		case ESM_FIELD_SCRIPT:
			SetScript(pString);
			return true;

		case ESM_FIELD_MODEL:
			SetModel(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
