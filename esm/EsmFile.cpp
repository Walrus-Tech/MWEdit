/*===========================================================================
 *
 * File:    Esmfile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmfile.h"


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
DEFINE_FILE("EsmFile.cpp");
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Record Create Array
 *
 *=========================================================================*/
static esmreccreate_t l_RecCreate[] = {
	{
		MWESM_REC_TES3,
		CEsmTES3::Create
	},
	{
		MWESM_REC_ACTI,
		CEsmActivator::Create
	},
	{
		MWESM_REC_ALCH,
		CEsmAlchemy::Create
	},
	{
		MWESM_REC_APPA,
		CEsmApparatus::Create
	},
	{
		MWESM_REC_ARMO,
		CEsmArmor::Create
	},
	{
		MWESM_REC_BODY,
		CEsmBodyPart::Create
	},
	{
		MWESM_REC_BOOK,
		CEsmBook::Create
	},
	{
		MWESM_REC_BSGN,
		CEsmBirthSign::Create
	},
	{
		MWESM_REC_CELL,
		CEsmCell::Create
	},
	{
		MWESM_REC_CLAS,
		CEsmClass::Create
	},
	{
		MWESM_REC_CLOT,
		CEsmClothing::Create
	},
	{
		MWESM_REC_CONT,
		CEsmContainer::Create
	},
	{
		MWESM_REC_CREA,
		CEsmCreature::Create
	},
	{
		MWESM_REC_DIAL,
		CEsmDialogue::Create
	},
	{
		MWESM_REC_DOOR,
		CEsmDoor::Create
	},
	{
		MWESM_REC_ENCH,
		CEsmEnchant::Create
	},
	{
		MWESM_REC_FACT,
		CEsmFaction::Create
	},
	{
		MWESM_REC_GLOB,
		CEsmGlobal::Create
	},
	{
		MWESM_REC_GMST,
		CEsmGameSetting::Create
	},
	{
		MWESM_REC_INFO,
		CEsmInfo::Create
	},
	{
		MWESM_REC_INGR,
		CEsmIngrediant::Create
	},
	{
		MWESM_REC_LAND,
		CEsmLand::Create
	},
	{
		MWESM_REC_LEVC,
		CEsmLevelCrea::Create
	},
	{
		MWESM_REC_LEVI,
		CEsmLevelItem::Create
	},
	{
		MWESM_REC_LIGH,
		CEsmLight::Create
	},
	{
		MWESM_REC_LOCK,
		CEsmLockPick::Create
	},
	{
		MWESM_REC_MGEF,
		CEsmMagicEffect::Create
	},
	{
		MWESM_REC_MISC,
		CEsmMisc::Create
	},
	{
		MWESM_REC_NPC_,
		CEsmNpc::Create
	},
	{
		MWESM_REC_PROB,
		CEsmProbe::Create
	},
	{
		MWESM_REC_RACE,
		CEsmRace::Create
	},
	{
		MWESM_REC_REGN,
		CEsmRegion::Create
	},
	{
		MWESM_REC_REPA,
		CEsmRepair::Create
	},
	{
		MWESM_REC_SCPT,
		CEsmScript::Create
	},
	{
		MWESM_REC_SKIL,
		CEsmSkill::Create
	},
	{
		MWESM_REC_SNDG,
		CEsmSoundGen::Create
	},
	{
		MWESM_REC_SOUN,
		CEsmSound::Create
	},
	{
		MWESM_REC_SPEL,
		CEsmSpell::Create
	},
	{
		MWESM_REC_SSCR,
		CEsmStartScript::Create
	},
	{
		MWESM_REC_STAT,
		CEsmStatic::Create
	},
	{
		MWESM_REC_WEAP,
		CEsmWeapon::Create
	},
	{
		NULL,
		CEsmRecord::Create
	}    /* Must be last record */
};
/*===========================================================================
 *      End of Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Constructor
 *
 *=========================================================================*/
CEsmFile::CEsmFile() : m_Records(0) {
	//DEFINE_FUNCTION("CEsmFile::CEsmFile()");
	m_CallBack = NULL;
	m_CallBackData = 0;
	m_IsActive = NULL;
	m_IsMaster = NULL;
	m_FileSize = 0;
}

/*===========================================================================
 *      End of Class CEsmFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmFile::Destroy(void) {
	//DEFINE_FUNCTION("CEsmFile::Destroy()");
	CEsmRecord *pRecord;
	int Index;

	/* Delete all allocated records */
	for (Index = 0; Index < m_Records.GetSize(); Index++) {
		pRecord = m_Records.GetAt(Index);
		DestroyPointer(pRecord);
	}

	m_Records.RemoveAll();
}

/*===========================================================================
 *      End of Class Method CEsmFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - void AddRecord (pRecord, pInsertAfter);
 *
 * Adds the record to the file but after the given record.
 *
 *=========================================================================*/
void CEsmFile::AddRecord(CEsmRecord *pRecord, CEsmRecord *pInsertAfter) {
	int Index;

	if (pInsertAfter == NULL) {
		AddRecord(pRecord);
		return;
	}

	/* try and find the record */
	Index = m_Records.FindElement(pInsertAfter);

	if (Index < 0) {
		m_Records.Add(pRecord);
	} else {
		m_Records.Insert(pRecord, Index);
	}
}

/*===========================================================================
 *      End of Class Method CEsmFile::AddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* AllocateRecord (pType);
 *
 * Allocates a record according to the input type.If the type is not known,
 * the base record type is returned (CEsmRecord).  The record is added
 * to the record array and it's type is set.
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::AllocateRecord(const TCHAR *pType) {
	CEsmRecord *pRecord;
	pRecord = AllocNewRecord(pType);
	/* Add it to the array */
	m_Records.Add(pRecord);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFile::AllocateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* AllocNewRecord (pType);
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::AllocNewRecord(const TCHAR *pType) {
	CEsmRecord *pRecord;
	int Index;

	for (Index = 0; l_RecCreate[Index].Type != NULL; Index++) {
		if (l_RecCreate[Index].IsType(pType)) {
			break;
		}
	}

	/* Create and initialize the new record */
	pRecord = l_RecCreate[Index].CreateMethod();
	pRecord->SetType(pType);
	pRecord->SetFile(this);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFile::AllocNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* CopyRecord (pRecord);
 *
 * Creates a copy of the given record and adds it to the current file.
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::CopyRecord(CEsmRecord *pRecord) {
	CEsmRecord *pNewRecord = AllocateRecord(pRecord->GetType());

	/* Special case for CELL record */
	if (pRecord->IsType(MWESM_REC_CELL)) {
		((CEsmCell *)pNewRecord)->CopyCellBase((CEsmCell *)pRecord);
		pNewRecord->SetFile(this);
	} else {
		pNewRecord->Copy(pRecord);
		pNewRecord->SetFile(this);
	}

	return (pNewRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFile::CopyRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* CreateCopy (pRecord);
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::CreateCopy(CEsmRecord *pRecord) {
	CEsmRecord *pNewRecord = AllocNewRecord(pRecord->GetType());
	pNewRecord->Copy(pRecord);
	return (pNewRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFile::CreateCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - void CreateNew (void);
 *
 * Creates a new, empty, plugin file.
 *
 *=========================================================================*/
void CEsmFile::CreateNew(void) {
	CEsmRecord *pRecord;
	/* Delete the current contents of the file, if any */
	Destroy();
	/* Add the default TES3 entry */
	pRecord = AllocateRecord(MWESM_REC_TES3);
	pRecord->CreateNew(this);
}

/*===========================================================================
 *      End of Class Method CEsmFile::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* CreateNewRecord (pType);
 *
 * Same as AllocateRecord() but initializes the new record with CreateNew()
 * in addition to adding it to the file. Returns NULL on any error.
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::CreateNewRecord(const TCHAR *pType) {
	CEsmRecord *pNewRecord;
	/* Attempt to create the new record */
	pNewRecord = AllocateRecord(pType);

	/* Initialize the new record on success */
	if (pNewRecord != NULL) {
		pNewRecord->CreateNew(this);
	}

	return (pNewRecord);
}

/*===========================================================================
 *      End of Class Method CEsmFile::CreateNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* FindFirst (pType, ArrayIndex);
 *
 * Finds the first record with the given type.  Returns NULL if none was
 * found.  Updates the arrayindex as well so you can use it with FindNext.
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::FindFirst(const TCHAR *pType, int &ArrayIndex) {
	ArrayIndex = -1;
	return FindNext(pType, ArrayIndex);
}

/*===========================================================================
 *      End of Class Method CEsmFile::FindFirst()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - CEsmRecord* FindNext (pType, ArrayIndex);
 *
 * Finds the next record of the given type after the input arrayindex.
 * Returns the record and updates the arrayindex on success, or returns
 * NULL on any error.
 *
 *=========================================================================*/
CEsmRecord *CEsmFile::FindNext(const TCHAR *pType, int &ArrayIndex) {
	CEsmRecord *pRecord;
	ArrayIndex++;

	for (; ArrayIndex < m_Records.GetSize(); ArrayIndex++) {
		pRecord = m_Records.GetAt(ArrayIndex);

		if (pRecord->IsType(pType)) {
			return (pRecord);
		}
	}

	return (NULL);
}

/*===========================================================================
 *      End of Class Method CEsmFile::FindNext()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - bool Read (pFilename);
 *
 * Inputs the given ESM/ESP file. Returns false on any error.
 *
 *=========================================================================*/
bool CEsmFile::Read(const TCHAR *pFilename) {
	//DEFINE_FUNCTION("CEsmFile::Read()");
	CGenFile File;
	CEsmDialogue *pLastDial = NULL;
	CEsmRecord *pRecord;
	TCHAR Type[MWESM_TYPE_SIZE];
	TCHAR Buffer[256];
	bool Result;
	float Percent;
	/* Delete the current record information, if any */
	Destroy();
	/* Attempt to open file for input */
	Result = File.Open(pFilename, "rb");

	if (!Result) {
		return (false);
	}

	m_Filename = pFilename;
	m_FileSize = File.GetFileSize();

	/* Input the entire file */
	while (!File.IsEOF() && File.Tell() < m_FileSize) {
		/* Input the record type string */
		Result = File.Read(Type, MWESM_TYPE_SIZE);

		if (!Result) {
			return (false);
		}

		/* Allocate the appropriate record */
		pRecord = AllocateRecord(Type);
		//SystemLog.Printf ("%4.4s, 0x%08X", Type, File.Tell());

		if (TSTRNICMP(Type, MWESM_REC_DIAL, 4) == 0) {
			pLastDial = (CEsmDialogue *)pRecord;
		} else if (TSTRNICMP(Type, MWESM_REC_INFO, 4) == 0) {
			((CEsmInfo *)pRecord)->SetDialParent(pLastDial);
		}

		/* Call the callback function if set */
		if (m_CallBack != NULL && (m_Records.GetSize() % ESM_CALLBACK_RATE) == 0) {
			Percent = File.Tell() * 100.0f / m_FileSize;
			snprintf(Buffer, 255, _T("%4.4s (%ld)"), Type, m_Records.GetSize());
			m_CallBack(ESM_CALLBACK_RECORD, Buffer, Percent, m_CallBackData);
		}

		/* Input the record */
		Result = pRecord->Read(File);

		if (!Result) {
			return (false);
		}
	}

	File.Close();
	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmFile::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmFile Method - bool Write (pFilename);
 *
 * Outputs the file to the given filename.  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmFile::Write(const TCHAR *pFilename) {
	CEsmTES3 *pHeader;
	headerdata_t *pHeaderData;
	CGenFile File;
	TCHAR Buffer[256];
	int Index;
	bool Result;
	float Percent;
	/* Update the plugin's header record first */
	pHeader = (CEsmTES3 *)FindFirst(MWESM_REC_TES3, Index);

	if (pHeader != NULL) {
		pHeaderData = pHeader->GetHeaderData();
	}

	if (pHeaderData != NULL) {
		pHeaderData->NumRecords = m_Records.GetSize();
	}

	/* Attempt to open file for output */
	Result = File.Open(pFilename, "wb");

	if (!Result) {
		return (false);
	}

	/* Input all the file records */
	for (Index = 0; Index < m_Records.GetSize(); Index++) {
		/* Call the callback function if set */
		if (m_CallBack != NULL) {
			Percent = Index * 100.0f / m_Records.GetSize();
			snprintf(Buffer,
			         255,
			         _T("%4.4s (%ld of %ld)"),
			         m_Records.GetAt(Index)->GetType(),
			         Index,
			         m_Records.GetSize());
			m_CallBack(ESM_CALLBACK_RECORD, Buffer, Percent, m_CallBackData);
		}

		Result = m_Records.GetAt(Index)->Write(File);

		if (!Result) {
			return (false);
		}
	}

	m_FileSize = File.Tell();
	File.Close();
	return (true);
}

/*===========================================================================
 *      End of Class Method CEsmFile::Write()
 *=========================================================================*/
