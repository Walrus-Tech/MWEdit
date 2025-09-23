/*===========================================================================
 *
 * File:    EsmItem3.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "esmitem3.h"


DEFINE_FILE("EsmItem3.cpp");


/*===========================================================================
 *
 * Class CEsmItem3 Constructor
 *
 *=========================================================================*/
CEsmItem3::CEsmItem3() {
	//DEFINE_FUNCTION("CEsmItem3::CEsmItem3()");
	m_pEnchant = NULL;
}


/*===========================================================================
 *
 * Class CEsmItem3 Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmItem3::Destroy() {
	//DEFINE_FUNCTION("CEsmItem3::Destroy()");
	/* Clear the references */
	m_pEnchant = NULL;
	/* Call the base class method */
	CEsmItem2::Destroy();
}


/*===========================================================================
 *
 * Class CEsmItem3 Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmItem3::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	//DEFINE_FUNCTION("CEsmItem3::CompareFields()");
	CEsmItem3 *pRecord3;

	/* Ensure the correct type */
	if ((MWESM_CLASSTYPE_ITEM3 & pRecord->GetClassType()) == 0) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pRecord3 = (CEsmItem3 *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_ENCHANT:
			return StringCompare(GetEnchant(), pRecord3->GetEnchant(), FALSE);

		case ESM_FIELD_ENCHANTPTS:
			return (int)(GetEnchantPts() - pRecord3->GetEnchantPts());

		default:    /* Call the base class method */
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmItem3 Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmItem3::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
}


/*===========================================================================
 *
 * Class TCHAR* CEsmItem3 Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmItem3::GetFieldString(const int FieldID) {
	//DEFINE_FUNCTION("CEsmItem3::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ENCHANT:
			if (m_pEnchant == NULL) {
				return _T("");
			}

			return m_pEnchant->GetName();

		case ESM_FIELD_ENCHANTPTS:
			snprintf(s_Buffer, 31, _T("%ld"), GetEnchantPts());
			return s_Buffer;

		default:    /* Call the base class record */
			return CEsmItem2::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmItem3 Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmItem3::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_ENAM)) {
		m_pEnchant = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmItem3 Method - void SetEnchant (pEnchant);
 *
 *=========================================================================*/
void CEsmItem3::SetEnchant(const TCHAR *pEnchant) {
	DEFINE_FUNCTION("CEsmItem3::SetEnchant()");

	/* Should we delete the current enchant? */
	if (pEnchant == NULL || *pEnchant == NULL_CHAR) {
		if (m_pEnchant != NULL) {
			RemoveSubRecord(m_pEnchant);
		}

		m_pEnchant = NULL;
	} else if (m_pEnchant == NULL) { /* Create a new enchant sub-record */
		AllocateSubRecord(MWESM_SUBREC_ENAM);
		ASSERT(m_pEnchant != NULL);
		m_pEnchant->SetName(pEnchant);
	} else {
		m_pEnchant->SetName(pEnchant);
	}
}


/*===========================================================================
 *
 * Class CEsmItem3 Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmItem3::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ENCHANT:
			SetEnchant(pString);
			return true;

		case ESM_FIELD_ENCHANTPTS:
			SetEnchantPts(atol(pString));
			return true;
	}

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}
