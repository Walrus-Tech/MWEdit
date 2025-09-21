/*===========================================================================
 *
 * File:    EsmApparatus.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmApparatus.h"


DEFINE_FILE("EsmApparatus.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmApparatus::s_SubRecCreate[] = {
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
		MWESM_SUBREC_AADT,
		CEsmSubAADT::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Begin Local Apparatus Type Array
 *
 *=========================================================================*/
const TCHAR *l_ApparatusTypes[] = {
	_T("Mortar and Pestle"),
	_T("Albemic"),
	_T("Calcinator"),
	_T("Retort")
};


/*===========================================================================
 *
 * Class CEsmApparatus Constructor
 *
 *=========================================================================*/
CEsmApparatus::CEsmApparatus() {
	//DEFINE_FUNCTION("CEsmApparatus::CEsmApparatus()");
	m_pAppaData = NULL;
}


/*===========================================================================
 *
 * Class CEsmApparatus Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmApparatus::Destroy() {
	//DEFINE_FUNCTION("CEsmApparatus::Destroy()");
	m_pAppaData = NULL;
	CEsmItem2::Destroy();
}


/*===========================================================================
 *
 * Class CEsmApparatus Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmApparatus::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmApparatus::CompareFields()");
	CEsmApparatus *pApparatus;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_APPA)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pApparatus = (CEsmApparatus *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_QUALITY:
			ASSERT(GetAppaData() != NULL);
			return (int)(GetAppaData()->Quality * 100 - pApparatus->GetAppaData()->Quality * 100);

		case ESM_FIELD_TYPE:
			return StringCompare(GetAppaType(), pApparatus->GetAppaType(), FALSE);

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmApparatus Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmApparatus::Create() {
	DEFINE_FUNCTION("CEsmApparatus::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmApparatus);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmApparatus Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmApparatus::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_AADT);
	m_pAppaData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmApparatus Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmApparatus::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmApparatus::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_QUALITY:
			ASSERT(GetAppaData() != NULL);
			snprintf(s_Buffer, 31, _T("%.2f"), GetAppaData()->Quality);
			return s_Buffer;

		case ESM_FIELD_TYPE:
			ASSERT(m_pAppaData != NULL);
			return GetAppaType();

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmApparatus Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmApparatus::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_AADT)) {
		m_pAppaData = (CEsmSubAADT *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmApparatus Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmApparatus::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_QUALITY:
			SetQuality((float)atof(pString));
			return true;

		case ESM_FIELD_TYPE:
			int Type = GetESMAppaType(pString);

			if (Type >= 0) {
				SetAppaType(Type);
			}

			return true;
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMAppaType (AppaType);
 *
 *=========================================================================*/
const TCHAR *GetESMAppaType(const int AppaType) {
	/* Check for a valid apparatus type */
	if (AppaType < MWESM_APPATYPE_MIN || AppaType > MWESM_APPATYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the apparatus type string from the name array */
	return l_ApparatusTypes[AppaType];
}

int GetESMAppaType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_APPATYPE_MIN; Index <= MWESM_APPATYPE_MAX; Index++) {
		if (stricmp(l_ApparatusTypes[Index], pString) == 0) {
			return Index;
		}
	}

	/* Return the apparatus type string from the name array */
	return -1;
}
