/*===========================================================================
 *
 * File:    EsmItem2.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmitem2.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmItem2.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Constructor
 *
 *=========================================================================*/
CEsmItem2::CEsmItem2() {
	//DEFINE_FUNCTION("CEsmItem2::CEsmItem2()");
	m_pIcon = NULL;
}

/*===========================================================================
 *      End of Class CEsmItem2 Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmItem2::Destroy() {
	//DEFINE_FUNCTION("CEsmItem2::Destroy()");
	/* Clear the references */
	m_pIcon = NULL;
	/* Call the base class method */
	CEsmItem1::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmItem2::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmItem2::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	//DEFINE_FUNCTION("CEsmItem2::CompareFields()");
	CEsmItem2 *pRecord2;

	/* Ensure the correct type */
	if ((MWESM_CLASSTYPE_ITEM2 & pRecord->GetClassType()) == 0) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pRecord2 = (CEsmItem2 *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_ICON:
			return StringCompare(GetIcon(), pRecord2->GetIcon(), FALSE);

		case ESM_FIELD_WEIGHT:
			return (int)(GetWeight() * 100 - pRecord2->GetWeight() * 100);

		case ESM_FIELD_VALUE:
			return (int)(GetValue() - pRecord2->GetValue());

		default:    /* Call the base class method */
			return CEsmItem1::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmItem2::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmItem2::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem1::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_ITEX);
}

/*===========================================================================
 *      End of Class Method CEsmItem1::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmItem2 Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmItem2::GetFieldString(const int FieldID) {
	//DEFINE_FUNCTION("CEsmItem2::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ICON:
			if (m_pIcon == NULL) {
				return _T("");
			}

			return m_pIcon->GetName();

		case ESM_FIELD_WEIGHT:
			snprintf(s_Buffer, 31, _T("%.2f"), GetWeight());
			return s_Buffer;

		case ESM_FIELD_VALUE:
			snprintf(s_Buffer, 31, _T("%lu"), (unsigned long)GetValue());
			return s_Buffer;

		default:    /* Call the base class record */
			return CEsmItem1::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmItem2::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmItem2::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_ITEX)) {
		m_pIcon = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmItem1::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmItem2::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmItem2::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ICON:
			SetIcon(pString);
			return true;

		case ESM_FIELD_WEIGHT:
			SetWeight((float)atof(pString));
			return true;

		case ESM_FIELD_VALUE:
			SetValue(atol(pString));
			return true;
	}

	/* No matching field found */
	return CEsmItem1::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmItem2::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmItem2 Method - void SetIcon (pIcon);
 *
 *=========================================================================*/
void CEsmItem2::SetIcon(const TCHAR *pIcon) {
	DEFINE_FUNCTION("CEsmItem2::SetIcon()");

	/* Should we delete the current enchant? */
	if (pIcon == NULL || *pIcon == NULL_CHAR) {
		if (m_pIcon != NULL) {
			RemoveSubRecord(m_pIcon);
		}

		m_pIcon = NULL;
	} else if (m_pIcon == NULL) { /* Create a new enchant sub-record */
		AllocateSubRecord(MWESM_SUBREC_ITEX);
		ASSERT(m_pIcon != NULL);
		m_pIcon->SetName(pIcon);
	} else {
		m_pIcon->SetName(pIcon);
	}
}

/*===========================================================================
 *      End of Class Method CEsmItem2::SetIcon()
 *=========================================================================*/
