/*===========================================================================
 *
 * File:    EsmAlchemy.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmAlchemy.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmAlchemy.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmAlchemy::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MODL, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_TEXT, CEsmSubNameFix::Create },   /* Not ITEX */
	{ MWESM_SUBREC_SCRI, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_ENAM, CEsmSubENAM::Create },
	{ MWESM_SUBREC_ALDT, CEsmSubALDT::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Constructor
 *
 *=========================================================================*/
CEsmAlchemy::CEsmAlchemy () {
	//DEFINE_FUNCTION("CEsmAlchemy::CEsmAlchemy()");
	m_pAlchemyData = NULL;
}

/*===========================================================================
 *      End of Class CEsmAlchemy Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmAlchemy::Destroy (void) {
	//DEFINE_FUNCTION("CEsmAlchemy::Destroy()");
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmAlchemy::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	DEFINE_FUNCTION("CEsmAlchemy::CompareFields()");
	CEsmAlchemy* pAlchemy;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_ALCH)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pAlchemy = (CEsmAlchemy *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_AUTOCALC:
			ASSERT(GetAlchemyData() != NULL);
			return (GetAlchemyData()->AutoCalc - pAlchemy->GetAlchemyData()->AutoCalc);

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmAlchemy::Create (void) {
	DEFINE_FUNCTION("CEsmAlchemy::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmAlchemy);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmAlchemy::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first (skip CEsmItem2 on purpose due to
	 * the ALCH record using a TEXT instead of a ITEX icon record */
	CEsmItem1::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_TEXT);
	AllocateSubRecord(MWESM_SUBREC_ALDT);
	m_pAlchemyData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmAlchemy Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmAlchemy::GetFieldString (const int FieldID) {
	DEFINE_FUNCTION("CEsmAlchemy::GetFieldString()");

	switch (FieldID) {
		case ESM_FIELD_AUTOCALC:
			ASSERT(GetAlchemyData() != NULL);
			return (BOOLTOYESNO(GetAlchemyData()->AutoCalc != 0));

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmAlchemy::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmAlchemy::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_ALDT)) {
		m_pAlchemyData = (CEsmSubALDT *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_TEXT)) {
		m_pIcon = (CEsmSubNameFix *) pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmAlchemy::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmAlchemy::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_AUTOCALC:
			SetAutoCalc(StringToBoolean(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmAlchemy Method - void SetIcon (pIcon);
 *
 *=========================================================================*/
void CEsmAlchemy::SetIcon (const TCHAR* pIcon) {
	DEFINE_FUNCTION("CEsmAlchemy::SetIcon()");

	/* Should we delete the current enchant? */
	if (pIcon == NULL || *pIcon == NULL_CHAR) {
		if (m_pIcon != NULL) {
			RemoveSubRecord(m_pIcon);
		}

		m_pIcon = NULL;
	}
	/* Create a new enchant sub-record */
	else if (m_pIcon == NULL) {
		AllocateSubRecord(MWESM_SUBREC_TEXT);
		ASSERT(m_pIcon != NULL);
		m_pIcon->SetName(pIcon);
	} else {
		m_pIcon->SetName(pIcon);
	}
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::SetIcon()
 *=========================================================================*/
