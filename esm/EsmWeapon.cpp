/*===========================================================================
 *
 * File:    EsmWeapon.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmWeapon.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmWeapon.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmWeapon::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_MODL,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_ITEX,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_SCRI,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_ENAM,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_WPDT,
		CEsmSubWPDT::Create
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
 * Begin Local Weapon Type Array
 *
 *=========================================================================*/
const TCHAR *l_WeaponTypes[] = {
	_T("Short Blade"),
	_T("Long Blade"),
	_T("Long Blade, 2-Hand"),
	_T("Blunt"),
	_T("Blunt, 2-Close"),
	_T("Blunt, 2-Wide"),
	_T("Spear"),
	_T("Axe"),
	_T("Axe, 2-Hand"),
	_T("Bow"),
	_T("Crossbow"),
	_T("Thrown"),
	_T("Arrow"),
	_T("Bolt")
};
/*===========================================================================
 *      End of Local Weapon Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Constructor
 *
 *=========================================================================*/
CEsmWeapon::CEsmWeapon() {
	//DEFINE_FUNCTION("CEsmWeapon::CEsmWeapon()");
	m_pWeaponData = NULL;
}

/*===========================================================================
 *      End of Class CEsmWeapon Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmWeapon::Destroy(void) {
	//DEFINE_FUNCTION("CEsmWeapon::Destroy()");
	m_pWeaponData = NULL;
	CEsmItem3::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmWeapon::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmWeapon::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmWeapon::CompareFields()");
	CEsmWeapon *pWeapon;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_WEAP)) {
		return CEsmItem3::CompareFields(FieldID, pRecord);
	}

	pWeapon = (CEsmWeapon *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_HEALTH:
			return GetHealth() - pWeapon->GetHealth();

		case ESM_FIELD_SPEED:
			return (int)(GetSpeed() * 100 - pWeapon->GetSpeed() * 100);

		case ESM_FIELD_REACH:
			return (int)(GetReach() * 100 - pWeapon->GetReach() * 100);

		case ESM_FIELD_CHOPMIN:
			return GetChopMin() - pWeapon->GetChopMin();

		case ESM_FIELD_CHOPMAX:
			return GetChopMax() - pWeapon->GetChopMax();

		case ESM_FIELD_SLASHMIN:
			return GetSlashMin() - pWeapon->GetSlashMin();

		case ESM_FIELD_SLASHMAX:
			return GetSlashMax() - pWeapon->GetSlashMax();

		case ESM_FIELD_THRUSTMIN:
			return GetThrustMin() - pWeapon->GetThrustMin();

		case ESM_FIELD_THRUSTMAX:
			return GetThrustMax() - pWeapon->GetThrustMax();

		case ESM_FIELD_IGNORERESIST:
			return (int)IsIgnoreResist() - (int)pWeapon->IsIgnoreResist();

		case ESM_FIELD_TYPE:
			return StringCompare(GetWeaponType(), pWeapon->GetWeaponType(), FALSE);

		default:
			return CEsmItem3::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmWeapon::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmWeapon::Create(void) {
	DEFINE_FUNCTION("CEsmWeapon::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmWeapon);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmWeapon::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmWeapon::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem3::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_WPDT);
	m_pWeaponData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmWeapon::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmWeapon Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmWeapon::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmWeapon::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return (GetWeaponType());

		case ESM_FIELD_HEALTH:
			snprintf(s_Buffer, 31, _T("%d"), GetHealth());
			return (s_Buffer);

		case ESM_FIELD_SPEED:
			snprintf(s_Buffer, 31, _T("%.2f"), GetSpeed());
			return (s_Buffer);

		case ESM_FIELD_REACH:
			snprintf(s_Buffer, 31, _T("%.2f"), GetReach());
			return (s_Buffer);

		case ESM_FIELD_CHOPMIN:
			snprintf(s_Buffer, 31, _T("%d"), GetChopMin());
			return (s_Buffer);

		case ESM_FIELD_CHOPMAX:
			snprintf(s_Buffer, 31, _T("%d"), GetChopMax());
			return (s_Buffer);

		case ESM_FIELD_SLASHMIN:
			snprintf(s_Buffer, 31, _T("%d"), GetSlashMin());
			return (s_Buffer);

		case ESM_FIELD_SLASHMAX:
			snprintf(s_Buffer, 31, _T("%d"), GetSlashMax());
			return (s_Buffer);

		case ESM_FIELD_THRUSTMIN:
			snprintf(s_Buffer, 31, _T("%d"), GetThrustMin());
			return (s_Buffer);

		case ESM_FIELD_THRUSTMAX:
			snprintf(s_Buffer, 31, _T("%d"), GetThrustMax());
			return (s_Buffer);

		case ESM_FIELD_IGNORERESIST:
			return BOOLTOYESNO(IsIgnoreResist());

		default:
			return CEsmItem3::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmWeapon::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmWeapon::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_WPDT)) {
		m_pWeaponData = (CEsmSubWPDT *)pSubRecord;
	} else {
		CEsmItem3::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmWeapon::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmWeapon Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmWeapon::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_TYPE: {
			int Type = GetESMWeaponType(pString);

			if (Type >= 0) {
				SetWeaponType(Type);
			}

			return (true);
		}

		case ESM_FIELD_HEALTH:
			SetHealth(atoi(pString));
			return (true);

		case ESM_FIELD_SPEED:
			SetSpeed((float)atof(pString));
			return (true);

		case ESM_FIELD_REACH:
			SetReach((float)atof(pString));
			return (true);

		case ESM_FIELD_CHOPMIN:
			SetChopMin(atoi(pString));
			return (true);

		case ESM_FIELD_CHOPMAX:
			SetChopMax(atoi(pString));
			return (true);

		case ESM_FIELD_SLASHMIN:
			SetSlashMin(atoi(pString));
			return (true);

		case ESM_FIELD_SLASHMAX:
			SetSlashMax(atoi(pString));
			return (true);

		case ESM_FIELD_THRUSTMIN:
			SetThrustMin(atoi(pString));
			return (true);

		case ESM_FIELD_THRUSTMAX:
			SetThrustMax(atoi(pString));
			return (true);

		case ESM_FIELD_IGNORERESIST:
			SetIgnoreResist(StringToBoolean(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmItem3::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmWeapon::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMWeaponType (Type);
 *
 * Converts an weapon type value into a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *GetESMWeaponType(const int Type) {
	/* Check for a valid input type */
	if (Type < MWESM_WEAPONTYPE_MIN || Type > MWESM_WEAPONTYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the type string from the name array */
	return l_WeaponTypes[Type];
}

/*===========================================================================
 *      End of Function TCHAR* GetESMWeaponType()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int GetESMWeaponType (String);
 *
 * Converts a weapon type string into a numeric value. Returns
 * MWESM_WEAPONTYPE_SHORT on default.
 *
 *=========================================================================*/
int GetESMWeaponType(const TCHAR *pString) {
	int Index;

	/* Check for a valid input type */
	for (Index = MWESM_WEAPONTYPE_MIN; Index <= MWESM_WEAPONTYPE_MAX; Index++) {
		if ( _stricmp(l_WeaponTypes[Index], pString) == 0) {
			return (Index);
		}
	}

	return (MWESM_WEAPONTYPE_SHORT);
}

/*===========================================================================
 *      End of Function GetESMWeaponType()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsESMWeaponRange (Type);
 *
 * Returns true if the weapon type is a range type weapon.
 *
 *=========================================================================*/
bool IsESMWeaponRange(const int Type) {
	if (Type == MWESM_WEAPONTYPE_THROWN) {
		return (true);
	}

	if (Type == MWESM_WEAPONTYPE_ARROW) {
		return (true);
	}

	if (Type == MWESM_WEAPONTYPE_BOLT) {
		return (true);
	}

	return (false);
}

/*===========================================================================
 *      End of Function IsESMWeaponRange()
 *=========================================================================*/
