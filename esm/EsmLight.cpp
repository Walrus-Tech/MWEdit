/*===========================================================================
 *
 * File:    EsmLight.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmLight.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmLight.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmLight::s_SubRecCreate[] = {
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
		MWESM_SUBREC_LHDT,
		CEsmSubLHDT::Create
	},
	{
		MWESM_SUBREC_SNAM,
		CEsmSubNameFix::Create
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
 * Begin Local Apparatus Type Array
 *
 *=========================================================================*/
/*===========================================================================
 *      End of Local Apparatus Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Constructor
 *
 *=========================================================================*/
CEsmLight::CEsmLight() {
	//DEFINE_FUNCTION("CEsmLight::CEsmLight()");
	m_pLightData = NULL;
	m_pSound = NULL;
}

/*===========================================================================
 *      End of Class CEsmLight Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmLight::Destroy() {
	//DEFINE_FUNCTION("CEsmLight::Destroy()");
	m_pLightData = NULL;
	m_pSound = NULL;
	CEsmItem2::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmLight::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmLight::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	DEFINE_FUNCTION("CEsmLight::CompareFields()");
	CEsmLight *pLight;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_LIGH)) {
		return CEsmItem2::CompareFields(FieldID, pRecord);
	}

	pLight = (CEsmLight *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_TIME:
			return GetTime() - pLight->GetTime();

		case ESM_FIELD_RADIUS:
			return GetRadius() - pLight->GetRadius();

		case ESM_FIELD_SOUND:
			return StringCompare(GetSound(), pLight->GetSound(), false);

		default:
			return CEsmItem2::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmLight::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmLight::Create() {
	DEFINE_FUNCTION("CEsmLight::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmLight);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmLight::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmLight::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem2::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_LHDT);
	m_pLightData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmLight::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmLight Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmLight::GetFieldString(const int FieldID) {
	DEFINE_FUNCTION("CEsmLight::GetFieldString()");
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_TIME:
			snprintf(s_Buffer, 31, _T("%ld"), GetTime());
			return s_Buffer;

		case ESM_FIELD_RADIUS:
			snprintf(s_Buffer, 31, _T("%ld"), GetRadius());
			return s_Buffer;

		case ESM_FIELD_SOUND:
			return GetSound();

		default:
			return CEsmItem2::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmLight::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmLight::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_LHDT)) {
		m_pLightData = (CEsmSubLHDT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_SNAM)) {
		m_pSound = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmItem2::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmLight::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLight Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmLight::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_TIME:
			SetTime(atol(pString));
			return true;

		case ESM_FIELD_RADIUS:
			SetRadius(atol(pString));
			return true;

		case ESM_FIELD_SOUND:
			SetSound(pString);
			return true;
	};

	/* No matching field found */
	return CEsmItem2::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmLight::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CEsmLight Set Methods
 *
 *=========================================================================*/
void CEsmLight::SetIcon(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pIcon == NULL) {
			return;
		}

		if (m_pIcon != NULL) {
			RemoveSubRecord(m_pIcon);
		}

		m_pIcon = NULL;
	} else {
		if (m_pIcon == NULL) {
			AllocateSubRecord(MWESM_SUBREC_ITEX);
		}

		m_pIcon->SetName(pString);
	}
}

void CEsmLight::SetName(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pName == NULL) {
			return;
		}

		if (m_pName != NULL) {
			RemoveSubRecord(m_pName);
		}

		m_pName = NULL;
	} else {
		if (m_pName == NULL) {
			AllocateSubRecord(MWESM_SUBREC_FNAM);
		}

		m_pName->SetName(pString);
	}
}

void CEsmLight::SetSound(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pSound == NULL) {
			return;
		}

		if (m_pSound != NULL) {
			RemoveSubRecord(m_pSound);
		}

		m_pSound = NULL;
	} else {
		if (m_pSound == NULL) {
			AllocateSubRecord(MWESM_SUBREC_SNAM);
		}

		m_pSound->SetName(pString);
	}
}

/*===========================================================================
 *      End of CEsmLight Set Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMLightFlicker (Flags);
 *
 *=========================================================================*/
const TCHAR *GetESMLightFlicker(const int Flags) {
	if ((Flags & MWESM_LIGHTFLAG_FLICKER) != 0) {
		return _T("Flicker");
	} else if ((Flags & MWESM_LIGHTFLAG_PULSE) != 0) {
		return _T("Pulse");
	} else if ((Flags & MWESM_LIGHTFLAG_PULSESLOW) != 0) {
		return _T("Pulse Slow");
	} else if ((Flags & MWESM_LIGHTFLAG_FLICKERSLOW) != 0) {
		return _T("Flicker Slow");
	} else {
		return _T("None");
	}
}

/*===========================================================================
 *      End of Function TCHAR* GetESMLightFlicker()
 *=========================================================================*/
