/*===========================================================================
 *
 * File:    EsmInfo.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmInfo.h"
#include "EsmSubFloat.h"
#include "EsmDialogue.h"
#include <ctype.h>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmInfo.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmInfo::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_INAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_PNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_NNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubInfoDATA::Create
	},
	{
		MWESM_SUBREC_ONAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_RNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ANAM,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_DNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_NAME,
		CEsmSubName512::Create
	},
	{
		MWESM_SUBREC_SNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SCVR,
		CEsmSubSCVR::Create
	},
	{
		MWESM_SUBREC_INTV,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_FLTV,
		CEsmSubFloat::Create
	},
	{
		MWESM_SUBREC_BNAM,
		CEsmSubName::Create
	},
	{
		MWESM_SUBREC_QSTN,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_QSTR,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_QSTF,
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
 * Begin Function Array
 *
 *=========================================================================*/
esmfuncinfo_t l_InfoFuncData[] = {
	{
		*(short *)"00",
		"Rank Low"
	},
	{
		*(short *)"01",
		"Rank High"
	},
	{
		*(short *)"02",
		"Rank Requirement"
	},
	{
		*(short *)"03",
		"Reputation"
	},
	{
		*(short *)"04",
		"Health Percent"
	},
	{
		*(short *)"05",
		"PC Reputation"
	},
	{
		*(short *)"06",
		"PC Level"
	},
	{
		*(short *)"07",
		"PC Health Percent"
	},
	{
		*(short *)"08",
		"PC Magicka"
	},
	{
		*(short *)"09",
		"PC Fatigue"
	},
	{
		*(short *)"10",
		"PC Strength"
	},
	{
		*(short *)"11",
		"PC Block"
	},
	{
		*(short *)"12",
		"PC Armorer"
	},
	{
		*(short *)"13",
		"PC Medium Armor"
	},
	{
		*(short *)"14",
		"PC Heavy Armor"
	},
	{
		*(short *)"15",
		"PC Blunt Weapon"
	},
	{
		*(short *)"16",
		"PC Long Blade"
	},
	{
		*(short *)"17",
		"PC Axe"
	},
	{
		*(short *)"18",
		"PC Spear"
	},
	{
		*(short *)"19",
		"PC Athletics"
	},
	{
		*(short *)"20",
		"PC Enchant"
	},
	{
		*(short *)"21",
		"PC Destruction"
	},
	{
		*(short *)"22",
		"PC Alteration"
	},
	{
		*(short *)"23",
		"PC Illusion"
	},
	{
		*(short *)"24",
		"PC Conjuration"
	},
	{
		*(short *)"25",
		"PC Mysticism"
	},
	{
		*(short *)"26",
		"PC Restoration"
	},
	{
		*(short *)"27",
		"PC Alchemy"
	},
	{
		*(short *)"28",
		"PC Unarmored"
	},
	{
		*(short *)"29",
		"PC Security"
	},
	{
		*(short *)"30",
		"PC Sneak"
	},
	{
		*(short *)"31",
		"PC Acrobatics"
	},
	{
		*(short *)"32",
		"PC Light Armor"
	},
	{
		*(short *)"33",
		"PC Short Blade"
	},
	{
		*(short *)"34",
		"PC Marksman"
	},
	{
		*(short *)"35",
		"PC Mercantile"
	},
	{
		*(short *)"36",
		"PC Speechcraft"
	},
	{
		*(short *)"37",
		"PC Hand-to-Hand"
	},
	{
		*(short *)"38",
		"PC Gender"
	},
	{
		*(short *)"39",
		"PC Expelled"
	},
	{
		*(short *)"40",
		"PC Common Disease"
	},
	{
		*(short *)"41",
		"PC Blight Disease"
	},
	{
		*(short *)"42",
		"PC Clothing Modifier"
	},
	{
		*(short *)"43",
		"PC Crime Level"
	},
	{
		*(short *)"44",
		"Same Gender"
	},
	{
		*(short *)"45",
		"Same Race"
	},
	{
		*(short *)"46",
		"Same Faction"
	},
	{
		*(short *)"47",
		"Faction Rank Diff"
	},
	{
		*(short *)"48",
		"Detected"
	},
	{
		*(short *)"49",
		"Alarmed"
	},
	{
		*(short *)"50",
		"Choice"
	},
	{
		*(short *)"51",
		"PC Intelligence"
	},
	{
		*(short *)"52",
		"PC Willpower"
	},
	{
		*(short *)"53",
		"PC Agility"
	},
	{
		*(short *)"54",
		"PC Speed"
	},
	{
		*(short *)"55",
		"PC Endurance"
	},
	{
		*(short *)"56",
		"PC Personality"
	},
	{
		*(short *)"57",
		"PC Luck"
	},
	{
		*(short *)"58",
		"PC Corprus"
	},
	{
		*(short *)"59",
		"Weather"
	},
	{
		*(short *)"60",
		"PC Vampire"
	},
	{
		*(short *)"61",
		"Level"
	},
	{
		*(short *)"62",
		"Attacked"
	},
	{
		*(short *)"63",
		"Talked to PC"
	},
	{
		*(short *)"64",
		"PC Health"
	},
	{
		*(short *)"65",
		"Creature Target"
	},
	{
		*(short *)"66",
		"Friend Hit"
	},
	{
		*(short *)"67",
		"Fight"
	},
	{
		*(short *)"69",
		"Hello"
	},
	{
		*(short *)"69",
		"Alarm"
	},
	{
		*(short *)"70",
		"Flee"
	},
	{
		*(short *)"71",
		"Should Attack"
	},
	{
		*(short *)"sX",
		"Variable"
	},
	{
		*(short *)"JX",
		"Journal"
	},
	{
		*(short *)"IX",
		"Item"
	},
	{
		*(short *)"DX",
		"Dead"
	},
	{
		*(short *)"XX",
		"Not ID"
	},
	{
		*(short *)"FX",
		"Not Faction"
	},
	{
		*(short *)"CX",
		"Not Class"
	},
	{
		*(short *)"RX",
		"Not Race"
	},
	{
		*(short *)"LX",
		"Not Cell"
	},
	{
		NULL,
		NULL
	}
};
/*===========================================================================
 *      End of Function Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Constructor
 *
 *=========================================================================*/
CEsmInfo::CEsmInfo() {
	//DEFINE_FUNCTION("CEsmInfo::CEsmInfo()");
	m_pPrevName = NULL;
	m_pNextName = NULL;
	m_pData = NULL;
	m_pName = NULL;
	m_pActor = NULL;
	m_pRace = NULL;
	m_pClass = NULL;
	m_pFaction = NULL;
	m_pCell = NULL;
	m_pPCFaction = NULL;
	m_pSound = NULL;
	m_pResult = NULL;
	m_pDialParent = NULL;
}

/*===========================================================================
 *      End of Class CEsmInfo Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmInfo::Destroy(void) {
	//DEFINE_FUNCTION("CEsmInfo::Destroy()");
	m_pPrevName = NULL;
	m_pNextName = NULL;
	m_pData = NULL;
	m_pName = NULL;
	m_pActor = NULL;
	m_pRace = NULL;
	m_pClass = NULL;
	m_pFaction = NULL;
	m_pCell = NULL;
	m_pPCFaction = NULL;
	m_pSound = NULL;
	m_pResult = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmInfo::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmInfo::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmInfo *pInfo;
	TCHAR Buffer[128];

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_INFO)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pInfo = (CEsmInfo *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return StringCompare(GetResponse(), pInfo->GetResponse(), false);

		case ESM_FIELD_DISPOSITION:
			return GetDisposition() - pInfo->GetDisposition();

		case ESM_FIELD_NPCID:
			return StringCompare(GetActor(), pInfo->GetActor(), false);

		case ESM_FIELD_NPCFACTION:
			return StringCompare(GetFaction(), pInfo->GetFaction(), false);

		case ESM_FIELD_NPCCELL:
			return StringCompare(GetCell(), pInfo->GetCell(), false);

		case ESM_FIELD_INFOFUNC1:
			strnncpy(Buffer, GetFuncText(0), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(0), false);

		case ESM_FIELD_INFOFUNC2:
			strnncpy(Buffer, GetFuncText(1), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(1), false);

		case ESM_FIELD_INFOFUNC3:
			strnncpy(Buffer, GetFuncText(2), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(2), false);

		case ESM_FIELD_INFOFUNC4:
			strnncpy(Buffer, GetFuncText(3), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(3), false);

		case ESM_FIELD_INFOFUNC5:
			strnncpy(Buffer, GetFuncText(4), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(4), false);

		case ESM_FIELD_INFOFUNC6:
			strnncpy(Buffer, GetFuncText(5), 127);
			return StringCompare(Buffer, pInfo->GetFuncText(5), false);

		case ESM_FIELD_TOPIC:
			if (m_pDialParent == NULL || pInfo->GetDialParent() == NULL) {
				return (0);
			}

			return StringCompare(m_pDialParent->GetID(), pInfo->GetDialParent()->GetID(), false);

		case ESM_FIELD_PREV:
			return (StringCompare(GetPrevName(), pInfo->GetPrevName(), false));

		case ESM_FIELD_NEXT:
			return (StringCompare(GetNextName(), pInfo->GetNextName(), false));

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmInfo::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmInfo::Create(void) {
	DEFINE_FUNCTION("CEsmInfo::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmInfo);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmInfo::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmInfo::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_INAM);
	AllocateSubRecord(MWESM_SUBREC_PNAM);
	AllocateSubRecord(MWESM_SUBREC_NNAM);
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_NAME);
	m_pData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmInfo::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmInfo Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmInfo::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_NAME:
			return GetResponse();

		case ESM_FIELD_NPCID:
			return GetActor();

		case ESM_FIELD_NPCFACTION:
			return GetFaction();

		case ESM_FIELD_NPCCELL:
			return GetCell();

		case ESM_FIELD_INFOFUNC1:
			return GetFuncText(0);

		case ESM_FIELD_INFOFUNC2:
			return GetFuncText(1);

		case ESM_FIELD_INFOFUNC3:
			return GetFuncText(2);

		case ESM_FIELD_INFOFUNC4:
			return GetFuncText(3);

		case ESM_FIELD_INFOFUNC5:
			return GetFuncText(4);

		case ESM_FIELD_INFOFUNC6:
			return GetFuncText(5);

		case ESM_FIELD_DISPOSITION:
			snprintf(s_Buffer, 31, _T("%d"), GetDisposition());
			return (s_Buffer);

		case ESM_FIELD_NEXT:
			strnncpy(s_Buffer, GetNextName(), 31);
			return (s_Buffer);

		case ESM_FIELD_PREV:
			strnncpy(s_Buffer, GetPrevName(), 31);
			return (s_Buffer);

		case ESM_FIELD_TOPIC:
			if (m_pDialParent == NULL) {
				s_Buffer[0] = NULL_CHAR;
			} else {
				strnncpy(s_Buffer, m_pDialParent->GetID(), MWESM_ID_MAXSIZE);
			}

			return (s_Buffer);

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmInfo::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmInfo Method - const GetFuncText (Index);
 *
 * Returns a text representation for the given info function.  Returns
 * an empty string on any error.  Uses a local static string buffer.
 *
 *=========================================================================*/
const TCHAR *CEsmInfo::GetFuncText(const int Index) {
	static TCHAR s_Buffer[128];
	CEsmSubRecord *pSubRec;
	CEsmSubSCVR *pFuncRec;
	infofuncdata_t *pFuncData;
	float FuncValue = 0.0f;
	int ArrayIndex;
	int IndexCount;

	/* Ensure a valid function index */
	if (Index < 0 || Index >= MWESM_INFO_MAXFUNCS) {
		return _T("");
	}

	/* Skip to the appropriate function record */
	pSubRec = FindFirst(MWESM_SUBREC_SCVR, ArrayIndex);
	IndexCount = 0;

	while (pSubRec != NULL && IndexCount < Index) {
		pSubRec = FindNext(MWESM_SUBREC_SCVR, ArrayIndex);
		IndexCount++;
	}

	/* No function for this index */
	if (pSubRec == NULL) {
		return _T("");
	}

	pFuncRec = (CEsmSubSCVR *)pSubRec;
	pFuncData = pFuncRec->GetInfoFuncData();

	if (pFuncData == NULL) {
		return _T("");
	}

	/* Get the long or float data */
	pSubRec = GetSubRecord(ArrayIndex + 1);

	if (pSubRec == NULL) {
		FuncValue = 0.0f;
	} else if (pSubRec->IsType(MWESM_SUBREC_FLTV)) {
		FuncValue = (float)((CEsmSubFloat *)pSubRec)->GetValue();
	} else if (pSubRec->IsType(MWESM_SUBREC_INTV)) {
		FuncValue = (float)((CEsmSubLong *)pSubRec)->GetValue();
	}

	if (pFuncRec->GetInfoFuncData()->Type == MWESM_SCVRFUNC_FUNCTION) {
		snprintf(s_Buffer,
		         127,
		         _T("%s %s %g"),
		         GetESMInfoFunction(pFuncData->Function),
		         GetESMInfoCompareOp(pFuncData->CompareOp),
		         FuncValue);
	} else if (pFuncRec->GetInfoFuncData()->Type == MWESM_SCVRFUNC_NONE) {
		return (_T(""));
	} else {
		snprintf(s_Buffer,
		         127,
		         _T("%s %s %g"),
		         pFuncData->Name,
		         GetESMInfoCompareOp(pFuncData->CompareOp),
		          FuncValue);
	}

	return (s_Buffer);
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmInfo::GetFuncText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - bool IsUsed (pID);
 *
 * Sees if the given ID is used by the given info.
 *
 *=========================================================================*/
bool CEsmInfo::IsUsed(const TCHAR *pID) {
	const TCHAR *pResult;
	const TCHAR *pParse;
	int IDLength = SafeStrLen(pID);

	/* Ignore if there is no result text to look at */
	if (m_pResult == NULL) {
		return CEsmRecord::IsUsed(pID);
	}

	pResult = m_pResult->GetName();
	/* Attempt to find all occurences of the ID in the result text */
	pParse = stristr(pResult, pID);

	while (pParse != NULL) {
		if (iswctype(pParse[-1], _PUNCT | _SPACE)
		    && (iswctype(pParse[IDLength], _PUNCT | _SPACE)
		    || pParse[IDLength] == NULL_CHAR)) {
			return (true);
		}

		pParse = stristr(pParse + IDLength, pID);
	}

	/* Search the remainder of the INFO's sub-records normally */
	return CEsmRecord::IsUsed(pID);
}

/*===========================================================================
 *      End of Class Method CEsmInfo::IsUsed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmInfo::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_INAM)) {
		m_pID = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_PNAM)) {
		m_pPrevName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NNAM)) {
		m_pNextName = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NAME)) {
		m_pName = (CEsmSubName512 *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = (CEsmSubInfoDATA *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_ONAM)) {
		m_pActor = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_RNAM)) {
		m_pRace = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CNAM)) {
		m_pClass = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FNAM)) {
		m_pFaction = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_ANAM)) {
		m_pCell = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DNAM)) {
		m_pPCFaction = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_SNAM)) {
		m_pSound = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_BNAM)) {
		m_pResult = (CEsmSubName *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmInfo::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmInfo Method - void SetResult (pString);
 *
 *=========================================================================*/
void CEsmInfo::SetResult(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pResult != NULL) {
			DeleteSubRecords(MWESM_SUBREC_BNAM);
		}

		m_pResult = NULL;
	} else {
		if (m_pResult == NULL) {
			AllocateSubRecord(MWESM_SUBREC_BNAM);
		}

		m_pResult->SetName(pString);
	}
}

void CEsmInfo::SetActor(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pActor != NULL) {
			DeleteSubRecords(MWESM_SUBREC_ONAM);
		}

		m_pActor = NULL;
	} else {
		if (m_pActor == NULL) {
			AllocateSubRecord(MWESM_SUBREC_ONAM);
		}

		m_pActor->SetName(pString);
	}
}


void CEsmInfo::SetClass(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pClass != NULL) {
			DeleteSubRecords(MWESM_SUBREC_CNAM);
		}

		m_pClass = NULL;
	} else {
		if (m_pClass == NULL) {
			AllocateSubRecord(MWESM_SUBREC_CNAM);
		}

		m_pClass->SetName(pString);
	}
}


void CEsmInfo::SetRace(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pRace != NULL) {
			DeleteSubRecords(MWESM_SUBREC_RNAM);
		}

		m_pRace = NULL;
	} else {
		if (m_pRace == NULL) {
			AllocateSubRecord(MWESM_SUBREC_RNAM);
		}

		m_pRace->SetName(pString);
	}
}


void CEsmInfo::SetFaction(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pFaction != NULL) {
			DeleteSubRecords(MWESM_SUBREC_FNAM);
		}

		m_pFaction = NULL;
	} else {
		if (m_pFaction == NULL) {
			AllocateSubRecord(MWESM_SUBREC_FNAM);
		}

		m_pFaction->SetName(pString);
	}
}


void CEsmInfo::SetPCFaction(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pPCFaction != NULL) {
			DeleteSubRecords(MWESM_SUBREC_DNAM);
		}

		m_pPCFaction = NULL;
	} else {
		if (m_pPCFaction == NULL) {
			AllocateSubRecord(MWESM_SUBREC_DNAM);
		}

		m_pPCFaction->SetName(pString);
	}
}


void CEsmInfo::SetCell(const TCHAR *pString) {
	if (pString == NULL) {
		if (m_pCell != NULL) {
			DeleteSubRecords(MWESM_SUBREC_ANAM);
		}

		m_pCell = NULL;
	} else {
		if (m_pCell == NULL) {
			AllocateSubRecord(MWESM_SUBREC_ANAM);
		}

		m_pCell->SetName(pString);
	}
}

void CEsmInfo::SetSound(const TCHAR *pString) {
	if (pString == NULL || *pString == NULL_CHAR) {
		if (m_pSound != NULL) {
			DeleteSubRecords(MWESM_SUBREC_SNAM);
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
 *      End of Class Method CEsmInfo::SetResult()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMInfoGender (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMInfoGender(const int Type) {
	switch (Type) {
		case MWESM_INFOGENDER_NONE:
			return _T("");

		case MWESM_INFOGENDER_MALE:
			return _T("Male");

		case MWESM_INFOGENDER_FEMALE:
			return _T("Female");

		default:
			return _T("Unknown");
	}
}

/*===========================================================================
 *      End of Function TCHAR* GetESMInfoGender()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMInfoFunction (FuncType);
 *
 *=========================================================================*/
const TCHAR *GetESMInfoFunction(const short FuncType) {
	int Index;

	for (Index = 0 ; l_InfoFuncData[Index].pName != NULL; Index++) {
		if (FuncType == l_InfoFuncData[Index].Type) {
			return (l_InfoFuncData[Index].pName);
		}
	}

	return _T("Unknown");
}

/*===========================================================================
 *      End of Function TCHAR* GetESMInfoFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMInfoFuncType (FuncType);
 *
 *=========================================================================*/
const TCHAR *GetESMInfoFuncType(const byte FuncType) {
	switch (FuncType) {
		case '0':
			return _T("");

		case '1':
			return _T("Function");

		case '2':
			return _T("Global");

		case '3':
			return _T("Local");

		case '4':
			return _T("Journal");

		case '5':
			return _T("Item");

		case '6':
			return _T("Dead");

		case '7':
			return _T("Not ID");

		case '8':
			return _T("Not Faction");

		case '9':
			return _T("Not Class");

		case 'A':
			return _T("Not Race");

		case 'B':
			return _T("Not Cell");

		case 'C':
			return _T("Not Local");

		default:
			return _T("Unknown");
	}
}

/*===========================================================================
 *      End of Function TCHAR* GetESMInfoFuncType()
 *=========================================================================*/



/*===========================================================================
 *
 * Function - const TCHAR* GetESMInfoCompareOp (Type);
 *
 *=========================================================================*/
const TCHAR *GetESMInfoCompareOp(const byte Type) {
	switch (Type) {
		case '0':
			return _T("=");

		case '1':
			return _T("!=");

		case '2':
			return _T(">");

		case '3':
			return _T(">=");

		case '4':
			return _T("<");

		case '5':
			return _T("<=");

		default:
			return _T("??");
	}
}

/*===========================================================================
 *      End of Function TCHAR* GetESMInfoCompareOp()
 *=========================================================================*/
