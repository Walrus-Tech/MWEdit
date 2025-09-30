/*===========================================================================
 *
 * File:    EsmBodyPart.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "EsmBodyPart.h"


DEFINE_FILE("EsmBodyPart.cpp");


/*===========================================================================
 *
 * Begin Local Type String Arrays
 *
 *=========================================================================*/
const TCHAR *l_BodyPartTypes[] = {
	_T("Skin"),
	_T("Clothing"),
	_T("Armor")
};

const TCHAR *l_BodyParts[] = {
	_T("Head"),
	_T("Hair"),
	_T("Neck"),
	_T("Chest"),
	_T("Groin"),
	_T("Hand"),
	_T("Wrist"),
	_T("Forearm"),
	_T("Upperarm"),
	_T("Foot"),
	_T("Ankle"),
	_T("Knee"),
	_T("Upperleg"),
	_T("Clavicle"),
	_T("Tail")
} ;


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmBodyPart::s_SubRecCreate[] = {
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
		MWESM_SUBREC_BYDT,
		CEsmSubBYDT::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmBodyPart Constructor
 *
 *=========================================================================*/
CEsmBodyPart::CEsmBodyPart() {
	//DEFINE_FUNCTION("CEsmBodyPart::CEsmBodyPart()");
	m_pName = NULL;
	m_pBodyData = NULL;
	m_pModel = NULL;
}


/*===========================================================================
 *
 * Class CEsmBodyPart Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmBodyPart::Destroy() {
	//DEFINE_FUNCTION("CEsmBodyPart::Destroy()");
	m_pName = NULL;
	m_pBodyData = NULL;
	m_pModel = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmBodyPart Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmBodyPart::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmBodyPart *pBody;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_BODY)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pBody = (CEsmBodyPart *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_MODEL:
			return StringCompare(GetModel(), pBody->GetModel());

		case ESM_FIELD_NAME:
		case ESM_FIELD_RACE:
			return StringCompare(GetRace(), pBody->GetRace());

		case ESM_FIELD_FEMALE:
			return (int)IsFemale() - (int)pBody->IsFemale();

		case ESM_FIELD_PLAYABLE:
			return (int)IsPlayable() - (int)pBody->IsPlayable();

		case ESM_FIELD_TYPE:
			return StringCompare(GetBodyPartType(), pBody->GetBodyPartType());

		case ESM_FIELD_PART:
			return StringCompare(GetBodyPart(), pBody->GetBodyPart());

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBodyPart Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmBodyPart::Create() {
	DEFINE_FUNCTION("CEsmBodyPart::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmBodyPart);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmBodyPart Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmBodyPart::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_FNAM);
	AllocateSubRecord(MWESM_SUBREC_MODL);
	AllocateSubRecord(MWESM_SUBREC_BYDT);
	m_pBodyData->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmBodyPart Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmBodyPart::GetFieldString(const int FieldID) {
	switch (FieldID) {
		case ESM_FIELD_MODEL:
			return GetModel();

		case ESM_FIELD_NAME:
		case ESM_FIELD_RACE:
			return GetRace();

		case ESM_FIELD_FEMALE:
			return BOOLTOYESNO(IsFemale());

		case ESM_FIELD_TYPE:
			return GetBodyPartType();

		case ESM_FIELD_PART:
			return GetBodyPart();

		case ESM_FIELD_PLAYABLE:
			return BOOLTOYESNO(IsPlayable());

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmBodyPart Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmBodyPart::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_BYDT)) {
		m_pBodyData = (CEsmSubBYDT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_MODL)) {
		m_pModel = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmBodyPart Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmBodyPart::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_MODEL:
			SetModel(pString);
			return true;

		case ESM_FIELD_NAME:
		case ESM_FIELD_RACE:
			SetRace(pString);
			return true;

		case ESM_FIELD_FEMALE:
			SetFemale(StringToBoolean(pString));
			return true;

		case ESM_FIELD_TYPE: {
			int Type = GetESMBodyPartType(pString);

			if (Type >= 0) {
				SetBodyPartType(Type);
			}

			return true;
		}

		case ESM_FIELD_PART: {
			int Type = GetESMBodyPart(pString);

			if (Type >= 0) {
				SetBodyPart(Type);
			}

			return true;
		}

		case ESM_FIELD_PLAYABLE:
			SetPlayable(StringToBoolean(pString));
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMBodyPart (Part);
 *
 * Converts a part value into a string.
 *
 *=========================================================================*/
const TCHAR *GetESMBodyPart(const int Part) {
	if (Part < MWESM_PART_MIN || Part > MWESM_PART_MAX) {
		return _T("Unknown");
	}

	return l_BodyParts[Part];
}

int GetESMBodyPart(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_PART_MIN; Index <= MWESM_PART_MAX; Index++) {
		if (stricmp(l_BodyParts[Index], pString) == 0) {
			return Index;
		}
	}

	return -1;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMBodyPartType (PartType);
 *
 * Converts a part type into a string.
 *
 *=========================================================================*/
const TCHAR *GetESMBodyPartType(const int PartType) {
	if (PartType < MWESM_PARTTYPE_MIN || PartType > MWESM_PARTTYPE_MAX) {
		return _T("Unknown");
	}

	return l_BodyPartTypes[PartType];
}

int GetESMBodyPartType(const TCHAR *pString) {
	int Index;

	for (Index = MWESM_PARTTYPE_MIN; Index <= MWESM_PARTTYPE_MAX; Index++) {
		if (stricmp(l_BodyPartTypes[Index], pString) == 0) {
			return Index;
		}
	}

	return -1;
}
