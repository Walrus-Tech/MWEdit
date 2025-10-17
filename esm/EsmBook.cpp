/*===========================================================================
 *
 * File:    EsmBook.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "esm/EsmBook.h"


DEFINE_FILE("EsmBook.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmBook::s_SubRecCreate[] = {
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
		MWESM_SUBREC_ENAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_BKDT,
		CEsmSubBKDT::Create
	},
	{
		MWESM_SUBREC_TEXT,
		CEsmSubName::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmBook Constructor
 *
 *=========================================================================*/
CEsmBook::CEsmBook() {
	//DEFINE_FUNCTION("CEsmBook::CEsmBook()");
	m_pBookData = NULL;
	m_pText = NULL;
}


/*===========================================================================
 *
 * Class CEsmBook Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmBook::Destroy() {
	//DEFINE_FUNCTION("CEsmBook::Destroy()");
	m_pBookData = NULL;
	m_pText = NULL;
	CEsmItem3::Destroy();
}


/*===========================================================================
 *
 * Class CEsmBook Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmBook::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmBook::CompareFields()");
	CEsmBook *pBook;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_BOOK)) {
		return CEsmItem3::CompareFields(FieldID, pRecord);
	}

	pBook = (CEsmBook *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_SCROLL:
			return (int)IsScroll() - (int)pBook->IsScroll();

		case ESM_FIELD_SKILL:
		case ESM_FIELD_TEACHES:
			return StringCompare(GetESMSkill(GetSkillID()),
			                     GetESMSkill(pBook->GetSkillID()),
			                     false);;

		default:
			return CEsmItem3::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBook Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmBook::Create() {
	DEFINE_FUNCTION("CEsmBook::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmBook);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmBook Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmBook::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem3::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_BKDT);
	AllocateSubRecord(MWESM_SUBREC_TEXT);
	m_pBookData->CreateNew();
	m_pText->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmBook Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmBook::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmBook::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ENCHANTPTS:
			snprintf(s_Buffer, 31, _T("%ld"), GetEnchantPts());
			return s_Buffer;

		case ESM_FIELD_SKILL:
		case ESM_FIELD_TEACHES:
			return GetESMSkill(GetSkillID());

		case ESM_FIELD_SCROLL:
			return BOOLTOYESNO(IsScroll());

		case ESM_FIELD_TEXT:
			return GetBookText();

		default:
			return CEsmItem3::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmBook Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmBook::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_BKDT)) {
		m_pBookData = (CEsmSubBKDT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_TEXT)) {
		m_pText = (CEsmSubName *)pSubRecord;
	} else {
		CEsmItem3::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBook Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmBook::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ENCHANTPTS:
			SetEnchantPts(atoi(pString));
			return true;

		case ESM_FIELD_SKILL:
		case ESM_FIELD_TEACHES: {
			int Skill = GetESMSkill(pString);

			if (Skill >= 0) {
				SetSkillID(Skill);
			}

			return true;
		}

		case ESM_FIELD_SCROLL:
			SetScroll(StringToBoolean(pString));
			return true;

		case ESM_FIELD_TEXT:
			SetBookText(pString);
			return true;
	};

	/* No matching field found */
	return CEsmItem3::SetFieldValue(FieldID, pString);
}
