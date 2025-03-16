/*===========================================================================
 *
 * File:    EsmSound.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmSound.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmSound.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmSound::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM, CEsmSubName::Create },
	{ MWESM_SUBREC_DATA, CEsmSubDATA::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Constructor
 *
 *=========================================================================*/
CEsmSound::CEsmSound () {
	//DEFINE_FUNCTION("CEsmSound::CEsmSound()");
	m_pData = NULL;
	m_pName = NULL;
}

/*===========================================================================
 *      End of Class CEsmSound Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmSound::Destroy (void) {
	//DEFINE_FUNCTION("CEsmSound::Destroy()");
	m_pData = NULL;
	m_pName = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmSound::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmSound::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmSound* pSound;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_SOUN)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pSound = (CEsmSound *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_VOLUME:
			return (int)(GetVolume() * 100 - pSound->GetVolume() * 100);

		case ESM_FIELD_MINRANGE:
			return GetMinRange() - pSound->GetMinRange();

		case ESM_FIELD_MAXRANGE:
			return GetMaxRange() - pSound->GetMaxRange();

		case ESM_FIELD_NAME:
			return StringCompare(GetName(), pSound->GetName(), false);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmSound::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmSound::Create (void) {
	DEFINE_FUNCTION("CEsmSound::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmSound);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmSound::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmSound::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_NAME);
	AllocateSubRecord(MWESM_SUBREC_DATA);
	m_pData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmSound::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmSound Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmSound::GetFieldString (const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_VOLUME:
			snprintf (s_Buffer, 31, _T("%.2f"), GetVolume());
			return (s_Buffer);

		case ESM_FIELD_MINRANGE:
			snprintf (s_Buffer, 31, _T("%d"), (int)GetMinRange());
			return (s_Buffer);

		case ESM_FIELD_MAXRANGE:
			snprintf (s_Buffer, 31, _T("%d"), (int)GetMaxRange());
			return (s_Buffer);

		case ESM_FIELD_NAME:
			return GetName();

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmSound::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmSound::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = (CEsmSubDATA *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubName *) pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmSound::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSound Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmSound::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_VOLUME:
			SetVolume((float) atof(pString));
			return (true);

		case ESM_FIELD_MINRANGE:
			SetMinRange(atoi(pString));
			return (true);

		case ESM_FIELD_MAXRANGE:
			SetMaxRange(atoi(pString));
			return (true);

		case ESM_FIELD_NAME:
			SetName(pString);
			return (true);
	};

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmSound::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Set Class Members
 *
 *=========================================================================*/
void CEsmSound::SetVolume (const float Volume) {
	if (m_pData == NULL) {
		return;
	}

	if (Volume < 1.0) {
		GetSoundData()->Volume = 0;
	} else if (Volume > 1.0f) {
		GetSoundData()->Volume = 255;
	} else {
		GetSoundData()->Volume = (byte) (Volume * 255);
	}
}


void CEsmSound::SetMinRange (const int Range) {
	if (m_pData == NULL) {
		return;
	}

	if (Range < 0) {
		GetSoundData()->MinRange = 0;
	} else if (Range > 255) {
		GetSoundData()->MinRange = 255;
	} else {
		GetSoundData()->MinRange = (byte) Range;
	}
}


void CEsmSound::SetMaxRange (const int Range) {
	if (m_pData == NULL) {
		return;
	}

	if (Range < 0) {
		GetSoundData()->MaxRange = 0;
	} else if (Range > 255) {
		GetSoundData()->MaxRange = 255;
	} else {
		GetSoundData()->MaxRange = (byte) Range;
	}
}

/*===========================================================================
 *      End of Set Class Members
 *=========================================================================*/

