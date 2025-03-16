/*===========================================================================
 *
 * File:    EsmCreature.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmCreature.h"
#include "EsmSubNPCS.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmCreature.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Creature Type String Arra
 *
 *=========================================================================*/
const TCHAR *l_CreatureTypes[] = {
	_T("Creature"),
	_T("Daedra"),
	_T("Undead"),
	_T("Humanoid")
};
/*===========================================================================
 *      End of Creature Type String Arra
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmCreature::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MODL, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_SCRI, CEsmSubNameFix::Create },
	{ MWESM_SUBREC_CRDT, CEsmSubCRDT::Create },
	{ MWESM_SUBREC_NPCO, CEsmSubNPCO::Create },
	{ MWESM_SUBREC_FLAG, CEsmSubLong::Create },
	{ MWESM_SUBREC_AIDT, CEsmSubAIDT::Create },
	{ MWESM_SUBREC_NPCO, CEsmSubNPCO::Create },
	{ MWESM_SUBREC_NPCS, CEsmSubNPCS::Create },
	{ MWESM_SUBREC_CNAM, CEsmSubNameFix::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Constructor
 *
 *=========================================================================*/
CEsmCreature::CEsmCreature () {
	//DEFINE_FUNCTION("CEsmCreature::CEsmCreature()");
	m_pCreatureData = NULL;
	m_pFlag = NULL;
	m_pAIData = NULL;
	m_pSound = NULL;
}

/*===========================================================================
 *      End of Class CEsmCreature Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmCreature::Destroy (void) {
	//DEFINE_FUNCTION("CEsmCreature::Destroy()");
	m_pCreatureData = NULL;
	m_pFlag = NULL;
	m_pAIData = NULL;
	m_pSound = NULL;
	CEsmItem1::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmCreature::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmCreature::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmCreature* pCreature;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_CREA)) {
		return CEsmItem1::CompareFields(FieldID, pRecord);
	}

	pCreature = (CEsmCreature *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return StringCompare(GetCreaType(), pCreature->GetCreaType(), false);

		case ESM_FIELD_LEVEL:
			return GetLevel() - pCreature->GetLevel();

		case ESM_FIELD_ESSENTIAL:
			return (int)IsEssential() - (int)pCreature->IsEssential();

		case ESM_FIELD_RESPAWN:
			return (int)IsRespawn() - (int)pCreature->IsRespawn();

		case ESM_FIELD_MOVEMENT:
			return StringCompare(GetMoveType(), pCreature->GetMoveType(), false);

		case ESM_FIELD_WEAPSHIELD:
			return (int)IsWeapShield() - (int)pCreature->IsWeapShield();

		case ESM_FIELD_BIPEDAL:
			return (int)IsBiped() - (int)pCreature->IsBiped();

		case ESM_FIELD_SOUND:
			return StringCompare(GetSound(), pCreature->GetSound(), false);

		default:
			return CEsmItem1::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method   DEFINE_FUNCTION("CEsmArmor::CompareFields()");::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmCreature::Create (void) {
	DEFINE_FUNCTION("CEsmCreature::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmCreature);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmCreature::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmCreature::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmItem1::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_CRDT);
	AllocateSubRecord(MWESM_SUBREC_FLAG);
	AllocateSubRecord(MWESM_SUBREC_AIDT);
	m_pAIData->CreateNew();
	m_pCreatureData->CreateNew();
	m_pFlag->CreateNew();
	m_pFlag->SetFlag(MWESM_CREAFLAG_DEFAULT);
}

/*===========================================================================
 *      End of Class Method CEsmCreature::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmCreature Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmCreature::GetFieldString (const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_TYPE:
			return GetCreaType();

		case ESM_FIELD_LEVEL:
			snprintf (s_Buffer, 31, _T("%ld"), GetLevel());
			return (s_Buffer);

		case ESM_FIELD_ESSENTIAL:
			return BOOLTOYESNO(IsEssential());

		case ESM_FIELD_RESPAWN:
			return BOOLTOYESNO(IsRespawn());

		case ESM_FIELD_MOVEMENT:
			return GetMoveType();

		case ESM_FIELD_WEAPSHIELD:
			return BOOLTOYESNO(IsWeapShield());

		case ESM_FIELD_BIPEDAL:
			return BOOLTOYESNO(IsBiped());

		case ESM_FIELD_SOUND:
			return ((m_pSound == NULL) ? _T("") : m_pSound->GetName());

		default:
			return CEsmItem1::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmCreature::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmCreature Method - const GetMoveType (void);
 *
 *=========================================================================*/
const TCHAR *CEsmCreature::GetMoveType (void) {
	if (IsWalks()) {
		return _T("Walks");
	}

	if (IsSwims()) {
		return _T("Swims");
	}

	if (IsFlies()) {
		return _T("Flies");
	}

	if (IsBiped()) {
		return _T("Biped");
	}

	return _T("None");
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmCreature::GetMoveType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmCreature::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_CRDT)) {
		m_pCreatureData = (CEsmSubCRDT *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FLAG)) {
		m_pFlag = (CEsmSubLong *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_AIDT)) {
		m_pAIData = (CEsmSubAIDT *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CNAM)) {
		m_pSound = (CEsmSubNameFix *) pSubRecord;
	} else {
		CEsmItem1::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmCreature::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmCreature::SetFieldValue (const int FieldID, const TCHAR* pString) {
	switch (FieldID) {
		case ESM_FIELD_TYPE: {
			int Type = GetESMCreatureType(pString);

			if (Type >= 0) {
				SetCreaType(Type);
			}

			return (true);
		}

		case ESM_FIELD_LEVEL:
			SetLevel(atoi(pString));
			return (true);

		case ESM_FIELD_ESSENTIAL:
			SetEssential(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_RESPAWN:
			SetRespawn(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_MOVEMENT:
			SetMoveType(pString);
			return (true);

		case ESM_FIELD_WEAPSHIELD:
			SetWeapShield(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_BIPEDAL:
			SetBipedal(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_SOUND:
			SetSound(pString);
			return (true);
	};

	/* No matching field found */
	return CEsmItem1::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmAlchemy::CEsmCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmCreature Method - void SetMoveType (pString);
 *
 *=========================================================================*/
void CEsmCreature::SetMoveType (const TCHAR* pString) {
	if (stricmp(pString, _T("Walks")) == 0) {
		SetWalks(true);
	}

	if (stricmp(pString, _T("Swims")) == 0) {
		SetSwims(true);
	}

	if (stricmp(pString, _T("Flies")) == 0) {
		SetFlies(true);
	}

	if (stricmp(pString, _T("Biped")) == 0) {
		SetBipedal(true);
	}

	if (stricmp(pString, _T("None")) == 0) {
		SetNone(true);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmCreature::SetMoveType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreature Method - void SetSound (pString);
 *
 *=========================================================================*/
void CEsmCreature::SetSound (const TCHAR* pString) {
	if (pString == NULL || *pString == NULL_CHAR) {
		DeleteSubRecords(MWESM_SUBREC_CNAM);
		m_pSound = NULL;
	} else {
		if (m_pSound == NULL) {
			AllocateSubRecord(MWESM_SUBREC_CNAM);
		}

		m_pSound->SetName(pString);
	}
}

/*===========================================================================
 *      End of Class Method CEsmCreature::SetSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMCreatureType (CreaType);
 *
 * Convert a creature type into a string.
 *
 *=========================================================================*/
const TCHAR *GetESMCreatureType (const int CreaType) {
	/* Check for a valid input type */
	if (CreaType < MWESM_CREATYPE_MIN || CreaType > MWESM_CREATYPE_MAX) {
		return _T("Unknown");
	}

	/* Return the type string from the name array */
	return l_CreatureTypes[CreaType];
}


int GetESMCreatureType (const TCHAR *pString) {
	int Index;

	for (Index = MWESM_CREATYPE_MIN; Index <= MWESM_CREATYPE_MAX; Index++) {
		if (stricmp(pString, l_CreatureTypes[Index]) == 0) {
			return (Index);
		}
	}

	return (-1);
}

/*===========================================================================
 *      End of Function TCHAR* GetESMCreatureType()
 *=========================================================================*/

