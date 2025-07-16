/*===========================================================================
 *
 * File:    Esmarmor.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmarmor.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmArmor.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmArmor::s_SubRecCreate[] = {
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
		MWESM_SUBREC_BNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_AODT,
		CEsmSubAODT::Create
	},
	{
		MWESM_SUBREC_INDX,
		CEsmSubByte::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Armor Type Array
 *
 *=========================================================================*/
const TCHAR *l_ArmorTypes[] = {
	_T("Helmet"),
	_T("Cuirass"),
	_T("Left Pauldron"),
	_T("Right Pauldron"),
	_T("Greaves"),
	_T("Boots"),
	_T("Left Gauntlet"),
	_T("Right Gauntlet"),
	_T("Shield"),
	_T("Left Bracer"),
	_T("Right Bracer")
};
/*===========================================================================
 *      End of Local Armor Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Constructor
 *
 *=========================================================================*/
CEsmArmor::CEsmArmor() {
	//DEFINE_FUNCTION("CEsmArmor::CEsmArmor()");
	m_pArmorData = NULL;
}

/*===========================================================================
 *      End of Class CEsmArmor Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmArmor::Destroy() {
	//DEFINE_FUNCTION("CEsmArmor::Destroy()");
	m_pArmorData = NULL;
	CEsmItem3::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmArmor::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmArmor::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmArmor::CompareFields()");
	CEsmArmor *pArmor;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_ARMO)) {
		return CEsmItem3::CompareFields(FieldID, pRecord);
	}

	pArmor = (CEsmArmor *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_HEALTH:
			ASSERT(m_pArmorData != NULL);
			return GetArmorData()->Health - pArmor->GetArmorData()->Health;

		case ESM_FIELD_RATING:
			ASSERT(m_pArmorData != NULL);
			return GetArmorData()->Rating - pArmor->GetArmorData()->Rating;

		case ESM_FIELD_TYPE:
			return StringCompare(GetArmorType(), pArmor->GetArmorType(), FALSE);

		default:
			return CEsmItem3::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmArmor::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmArmor::Create() {
	DEFINE_FUNCTION("CEsmArmor::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmArmor);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmArmor::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmArmor::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem3::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_AODT);
	m_pArmorData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmArmor::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmArmor Method - const GetArmorType (void) const;
 *
 * Returns the armor type as a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmArmor::GetArmorType() {
	if (GetArmorData() == NULL) {
		return _T("Unknown");
	}

	return GetESMArmorType(GetArmorData()->Type);
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmArmor::GetArmorType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmArmor Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmArmor::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmArmor::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			ASSERT(GetArmorData() != NULL);
			return GetArmorType();

		case ESM_FIELD_CLASS:
			return "?";

		case ESM_FIELD_HEALTH:
			ASSERT(GetArmorData() != NULL);
			snprintf(s_Buffer, 31, _T("%ld"), GetArmorData()->Health);
			return s_Buffer;

		case ESM_FIELD_RATING:
			ASSERT(GetArmorData() != NULL);
			snprintf(s_Buffer, 31, _T("%ld"), GetArmorData()->Rating);
			return s_Buffer;

		default:
			return CEsmItem3::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmArmor::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmArmor::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_AODT)) {
		m_pArmorData = (CEsmSubAODT *)pSubRecord;
	} else {
		CEsmItem3::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmArmor::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmArmor Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmArmor::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_TYPE: {
			int Type = GetESMArmorType(pString);

			if (Type >= 0) {
				SetArmorType(Type);
			}

			return true;
		}

		case ESM_FIELD_HEALTH:
			SetArmorHealth(atol(pString));
			return true;

		case ESM_FIELD_RATING:
			SetArmorRating(atol(pString));
			return true;
	};

	/* No matching field found */
	return CEsmItem3::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmArmor::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMArmorType (ArmorType);
 *
 * Converts an armor type value into a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *GetESMArmorType(const int ArmorType) {
	/* Check for a valid armor type */
	if (ArmorType < MWESM_ARMORTYPE_MIN || ArmorType > MWESM_ARMORTYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the armor type string from the name array */
	return l_ArmorTypes[ArmorType];
}

bool GetESMArmorType(int &OutIndex, const TCHAR *pString) {
	int Index;

	/* Check for a valid armor type */
	for (Index = MWESM_ARMORTYPE_MIN; Index <= MWESM_ARMORTYPE_MAX; Index++) {
		if (_stricmp(l_ArmorTypes[Index], pString) == 0) {
			OutIndex = Index;
			return true;
		}
	}

	return false;
}

int GetESMArmorType(const TCHAR *pString) {
	int Index;

	if (!GetESMArmorType(Index, pString)) {
		return MWESM_ARMORTYPE_MAX;
	}

	return Index;
}

/*===========================================================================
 *      End of Function TCHAR* GetESMArmorType()
 *=========================================================================*/
