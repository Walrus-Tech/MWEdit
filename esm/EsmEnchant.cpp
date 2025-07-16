/*===========================================================================
 *
 * File:    EsmEnchant.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmEnchant.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmEnchant.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Type String Arrays
 *
 *=========================================================================*/
const TCHAR *l_EnchantTypes[] = {
	_T("Cast Once"),
	_T("Cast On Strike"),
	_T("Cast When Used"),
	_T("Constant Effect")
};

const TCHAR *l_EnchantRanges[] = {
	_T("Self"),
	_T("Touch"),
	_T("Target")
};
/*===========================================================================
 *      End of Local Type String Arrays
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmEnchant::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ENDT,
		CEsmSubENDT::Create
	},
	{
		MWESM_SUBREC_ENAM,
		CEsmSubENAM::Create
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
 * Class CEsmEnchant Constructor
 *
 *=========================================================================*/
CEsmEnchant::CEsmEnchant() {
	//DEFINE_FUNCTION("CEsmEnchant::CEsmEnchant()");
	m_pEnchantData = NULL;
}

/*===========================================================================
 *      End of Class CEsmEnchant Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmEnchant::Destroy() {
	//DEFINE_FUNCTION("CEsmEnchant::Destroy()");
	m_pEnchantData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmEnchant::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmEnchant::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmEnchant *pEnchant;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_ENCH)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pEnchant = (CEsmEnchant *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_CHARGE:
			return GetCharge() - pEnchant->GetCharge();

		case ESM_FIELD_COST:
			return GetEnchantCost() - pEnchant->GetEnchantCost();

		case ESM_FIELD_TYPE:
			return StringCompare(GetEnchantType(), pEnchant->GetEnchantType(), false);

		case ESM_FIELD_AUTOCALC:
			return (int)IsAutoCalc() - (int)pEnchant->IsAutoCalc();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmEnchant::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmEnchant::Create() {
	DEFINE_FUNCTION("CEsmEnchant::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmEnchant);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmEnchant::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmEnchant::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_ENDT);
	m_pEnchantData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmEnchant::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmEnchant Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmEnchant::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_CHARGE:
			snprintf(s_Buffer, 31, _T("%ld"), GetCharge());
			return s_Buffer;

		case ESM_FIELD_COST:
			snprintf(s_Buffer, 31, _T("%ld"), GetEnchantCost());
			return s_Buffer;

		case ESM_FIELD_TYPE:
			return GetEnchantType();

		case ESM_FIELD_AUTOCALC:
			return BOOLTOYESNO(IsAutoCalc());

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmEnchant::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmEnchant::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_ENDT)) {
		m_pEnchantData = (CEsmSubENDT *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmEnchant::CEsmEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmEnchant Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmEnchant::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_CHARGE:
			SetCharge(atoi(pString));
			return true;

		case ESM_FIELD_COST:
			SetEnchantCost(atoi(pString));
			return true;

		case ESM_FIELD_TYPE: {
			int Type = GetESMEnchantType(pString);

			if (Type >= 0) {
				SetEnchantType(Type);
			}

			return true;
		}

		case ESM_FIELD_AUTOCALC:
			SetAutoCalc(StringToBoolean(pString));
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmEnchant::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMEnchantType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMEnchantType(const int Type) {
	/* Check for a valid input type */
	if (Type < MWESM_ENCHTYPE_MIN || Type > MWESM_ENCHTYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the type string from the name array */
	return l_EnchantTypes[Type];
}


bool GetESMEnchantType(int &OutType, const TCHAR *pString) {
	int Index;

	for (Index = MWESM_ENCHTYPE_MIN; Index <= MWESM_ENCHTYPE_MAX; Index++) {
		if (_stricmp(l_EnchantTypes[Index], pString) == 0) {
			OutType = Index;
			return true;
		}
	}

	/* Check old string values */
	if (_stricmp(pString, _T("Cast Strikes")) == 0) {
		OutType = MWESM_ENCHTYPE_CASTSTRIKES;
		return true;
	}

	return false;
}


int GetESMEnchantType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_ENCHTYPE_MIN; Index <= MWESM_ENCHTYPE_MAX; Index++) {
		if (_stricmp(l_EnchantTypes[Index], pString) == 0) {
			return Index;
		}
	}

	/* Check old string values */
	if (_stricmp(pString, _T("Cast Strikes")) == 0) {
		return MWESM_ENCHTYPE_CASTSTRIKES;
	}

	return MWESM_ENCHTYPE_MIN;
}

/*===========================================================================
 *      End of Function TCHAR* GetESMEnchantType()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMEnchantRangeType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMEnchantRangeType(const int Type) {
	/* Check for a valid input type */
	if (Type < MWESM_ENCHANTRANGE_MIN || Type > MWESM_ENCHANTRANGE_MAX) {
		return _T("Unknown");
	}

	/* Return the type string from the name array */
	return l_EnchantRanges[Type];
}


bool GetESMEnchantRangeType(int &OutType, const TCHAR *pString) {
	int Index;

	for (Index = MWESM_ENCHANTRANGE_MIN; Index <= MWESM_ENCHANTRANGE_MAX; Index++) {
		if (_stricmp(l_EnchantRanges[Index], pString) == 0) {
			OutType = Index;
			return true;
		}
	}

	return false;
}


int GetESMEnchantRangeType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_ENCHANTRANGE_MIN; Index <= MWESM_ENCHANTRANGE_MAX; Index++) {
		if (_stricmp(l_EnchantRanges[Index], pString) == 0) {
			return Index;
		}
	}

	return MWESM_ENCHANTRANGE_MIN;
}

/*===========================================================================
 *      End of Function TCHAR* GetESMEnchantRangeType()
 *=========================================================================*/
