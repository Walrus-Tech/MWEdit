/*===========================================================================
 *
 * File:    EsmSkill.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "EsmSkill.h"


DEFINE_FILE("EsmSkill.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmSkill::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_INDX,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_DESC,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_SKDT,
		CEsmSubSKDT::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmSkill Constructor
 *
 *=========================================================================*/
CEsmSkill::CEsmSkill() {
	//DEFINE_FUNCTION("CEsmSkill::CEsmSkill()");
	m_pIndexData = NULL;
	m_pSkillData = NULL;
	m_pDescData = NULL;
}


/*===========================================================================
 *
 * Class CEsmSkill Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmSkill::Destroy() {
	//DEFINE_FUNCTION("CEsmSkill::Destroy()");
	m_pIndexData = NULL;
	m_pSkillData = NULL;
	m_pDescData = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmSkill Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmSkill::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmSkill *pSkill;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_SKIL)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSkill = (CEsmSkill *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pSkill->GetName(), false);

		case ESM_FIELD_TYPE:
			return StringCompare(GetType(), pSkill->GetType(), false);

		case ESM_FIELD_ATTRIBUTE:
			return StringCompare(GetAttribute(), pSkill->GetAttribute(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmSkill Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmSkill::Create() {
	DEFINE_FUNCTION("CEsmSkill::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmSkill);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmSkill Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmSkill::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_INDX);
	AllocateSubRecord(MWESM_SUBREC_DESC);
	AllocateSubRecord(MWESM_SUBREC_SKDT);
	m_pIndexData->CreateNew();
	m_pSkillData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmSkill Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmSkill::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_TYPE:
			return GetType();;

		case ESM_FIELD_ATTRIBUTE:
			return GetAttribute();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmSkill Method - bool IsSame (pRecord);
 *
 * Checks if the input record is the same CELL as the current record.
 * For interior cells the ID is checked, and for exterior cells the grid
 * location is checked.
 *
 *=========================================================================*/
bool CEsmSkill::IsSame(CEsmRecord *pRecord) {
	/* Check types */
	if (!pRecord->IsType(MWESM_REC_SKIL)) {
		return false;
	}

	CEsmSkill *pSkill = (CEsmSkill *)pRecord;

	/* Check the skill indices */
	if (GetSkillID() == pSkill->GetSkillID()) {
		return true;
	}

	return false;
}


/*===========================================================================
 *
 * Class CEsmSkill Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmSkill::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_INDX)) {
		m_pIndexData = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DESC)) {
		m_pDescData = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_SKDT)) {
		m_pSkillData = (CEsmSubSKDT *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmSkill Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmSkill::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_DESC:
			SetDescription(pString);
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
