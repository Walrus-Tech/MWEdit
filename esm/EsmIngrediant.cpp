/*===========================================================================
 *
 * File:    EsmIngrediant.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmIngrediant.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmIngrediant.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmIngrediant::s_SubRecCreate[] = {
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
		MWESM_SUBREC_IRDT,
		CEsmSubIRDT::Create
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
 * Class CEsmIngrediant Constructor
 *
 *=========================================================================*/
CEsmIngrediant::CEsmIngrediant() {
	//DEFINE_FUNCTION("CEsmIngrediant::CEsmIngrediant()");
	m_pIngreData = NULL;
}

/*===========================================================================
 *      End of Class CEsmIngrediant Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmIngrediant::Destroy() {
	//DEFINE_FUNCTION("CEsmIngrediant::Destroy()");
	m_pIngreData = NULL;
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmIngrediant::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmIngrediant::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmIngrediant::CompareFields()");
	CEsmIngrediant *pIngre;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_INGR)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pIngre = (CEsmIngrediant *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_EFFECT1:
			return StringCompare(GetEffect(0), pIngre->GetEffect(0), false);

		case ESM_FIELD_EFFECT2:
			return StringCompare(GetEffect(1), pIngre->GetEffect(1), false);

		case ESM_FIELD_EFFECT3:
			return StringCompare(GetEffect(2), pIngre->GetEffect(2), false);

		case ESM_FIELD_EFFECT4:
			return StringCompare(GetEffect(3), pIngre->GetEffect(3), false);

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmIngrediant::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmIngrediant::Create() {
	DEFINE_FUNCTION("CEsmIngrediant::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmIngrediant);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmIngrediant::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmIngrediant::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_IRDT);
	m_pIngreData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmIngrediant::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmIngrediant Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmIngrediant::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmIngrediant::GetFieldString()");

	switch (FieldID) {
		case ESM_FIELD_EFFECT1:
			return GetEffect(0);

		case ESM_FIELD_EFFECT2:
			return GetEffect(1);

		case ESM_FIELD_EFFECT3:
			return GetEffect(2);

		case ESM_FIELD_EFFECT4:
			return GetEffect(3);

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmIngrediant::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmIngrediant::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_IRDT)) {
		m_pIngreData = (CEsmSubIRDT *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmIngrediant::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmIngrediant Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmIngrediant::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_EFFECT1: {
			int Effect = GetESMEffectID(pString);

			if (Effect >= 0) {
				GetIngreData()->EffectID[0] = Effect;
			}

			return true;
		}

		case ESM_FIELD_EFFECT2: {
			int Effect = GetESMEffectID(pString);

			if (Effect >= 0) {
				GetIngreData()->EffectID[1] = Effect;
			}

			return true;
		}

		case ESM_FIELD_EFFECT3: {
			int Effect = GetESMEffectID(pString);

			if (Effect >= 0) {
				GetIngreData()->EffectID[2] = Effect;
			}

			return true;
		}

		case ESM_FIELD_EFFECT4: {
			int Effect = GetESMEffectID(pString);

			if (Effect >= 0) {
				GetIngreData()->EffectID[3] = Effect;
			}

			return true;
		}
	}

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmIngrediant::SetFieldValue()
 *=========================================================================*/
