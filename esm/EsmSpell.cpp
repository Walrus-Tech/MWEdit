/*===========================================================================
 *
 * File:    EsmSpell.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmSpell.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmSpell.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Spell Type Array
 *
 *=========================================================================*/
const TCHAR *l_SpellTypes[] = {
	_T("Spell"),
	_T("Ability"),
	_T("Blight"),
	_T("Disease"),
	_T("Curse"),
	_T("Power"),

};
/*===========================================================================
 *      End of Local Spell Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmSpell::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SPDT,
		CEsmSubSPDT::Create
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
 * Class CEsmSpell Constructor
 *
 *=========================================================================*/
CEsmSpell::CEsmSpell() {
	//DEFINE_FUNCTION("CEsmSpell::CEsmSpell()");
	m_pSpellData = NULL;
	m_pName = NULL;
}

/*===========================================================================
 *      End of Class CEsmSpell Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmSpell::Destroy() {
	//DEFINE_FUNCTION("CEsmSpell::Destroy()");
	m_pSpellData = NULL;
	m_pName = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmSpell::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmSpell::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmSpell *pSpell;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_SPEL)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSpell = (CEsmSpell *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pSpell->GetName(), false);

		case ESM_FIELD_AUTOCALC:
			return (int)IsAutoCalc() - (int)pSpell->IsAutoCalc();

		case ESM_FIELD_PCSTART:
			return (int)IsPCStart() - (int)pSpell->IsPCStart();

		case ESM_FIELD_COST:
			return GetSpellCost() - pSpell->GetSpellCost();

		case ESM_FIELD_TYPE:
			return StringCompare(GetSpellType(), pSpell->GetSpellType(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmSpell::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmSpell::Create() {
	DEFINE_FUNCTION("CEsmSpell::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmSpell);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmSpell::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmSpell::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_SPDT);
	m_pSpellData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmSpell::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmSpell Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmSpell::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetName();

		case ESM_FIELD_AUTOCALC:
			return BOOLTOYESNO(IsAutoCalc());

		case ESM_FIELD_PCSTART:
			return BOOLTOYESNO(IsPCStart());

		case ESM_FIELD_COST:
			snprintf(s_Buffer, 31, _T("%ld"), GetSpellCost());
			return s_Buffer;

		case ESM_FIELD_TYPE:
			return GetSpellType();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmSpell::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmSpell::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_SPDT)) {
		m_pSpellData = (CEsmSubSPDT *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmSpell::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSpell Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmSpell::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_NAME:
			SetName(pString);
			return true;

		case ESM_FIELD_AUTOCALC:
			SetAutoCalc(StringToBoolean(pString));
			return true;

		case ESM_FIELD_PCSTART:
			SetPCStart(StringToBoolean(pString));
			return true;

		case ESM_FIELD_COST:
			SetSpellCost(atoi(pString));
			return true;

		case ESM_FIELD_TYPE: {
			int Type = GetESMSpellType(pString);

			if (Type >= 0) {
				SetSpellType(Type);
			}

			return true;
		}
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmSpell::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMSpellType (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMSpellType(const int Type) {
	/* Check for a valid input type */
	if (Type < MWESM_SPELLTYPE_MIN || Type > MWESM_SPELLTYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the type string from the name array */
	return l_SpellTypes[Type];
}

int GetESMSpellType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_SPELLTYPE_MIN; Index <= MWESM_SPELLTYPE_MAX; Index++) {
		if (stricmp(pString, l_SpellTypes[Index]) == 0) {
			return Index;
		}
	}

	return -1;
}

/*===========================================================================
 *      End of Function TCHAR* GetESMSpellType()
 *=========================================================================*/
