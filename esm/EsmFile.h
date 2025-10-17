/*===========================================================================
 *
 * File:    Esmfile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMFILE_H
#define __ESMFILE_H


#include "esm/EsmRecord.h"
#include "esm/EsmTES3.h"
#include "esm/EsmActivator.h"
#include "esm/EsmAlchemy.h"
#include "esm/EsmApparatus.h"
#include "esm/EsmArmor.h"
#include "esm/EsmBirthSign.h"
#include "esm/EsmBodyPart.h"
#include "esm/EsmBook.h"
#include "esm/EsmCell.h"
#include "esm/EsmClass.h"
#include "esm/EsmClothing.h"
#include "esm/EsmContainer.h"
#include "esm/EsmCreature.h"
#include "esm/EsmDialogue.h"
#include "esm/EsmDoor.h"
#include "esm/EsmEnchant.h"
#include "esm/EsmFaction.h"
#include "esm/EsmGameSetting.h"
#include "esm/EsmGlobal.h"
#include "esm/EsmInfo.h"
#include "esm/EsmIngrediant.h"
#include "esm/EsmLand.h"
#include "esm/EsmLevelCrea.h"
#include "esm/EsmLevelItem.h"
#include "esm/EsmLight.h"
#include "esm/EsmLockPick.h"
#include "esm/EsmMisc.h"
#include "esm/EsmNpc.h"
#include "esm/EsmProbe.h"
#include "esm/EsmRace.h"
#include "esm/EsmRegion.h"
#include "esm/EsmRepair.h"
#include "esm/EsmScript.h"
#include "esm/EsmSkill.h"
#include "esm/EsmSound.h"
#include "esm/EsmSoundGen.h"
#include "esm/EsmSpell.h"
#include "esm/EsmStartScript.h"
#include "esm/EsmStatic.h"
#include "esm/EsmWeapon.h"
#include "esm/EsmMagicEffect.h"
#include "esm/EsmGlobal.h"


/* Callback event codes */
#define ESM_CALLBACK_RECORD 1

/* Number of records between the callback function when loading/saving */
#define ESM_CALLBACK_RATE   25


/* Array of record pointers */
typedef TPtrArray<CEsmRecord> CEsmRecArray;

/* Callback function type */
typedef int (*ESMFILE_CALLBACK) (const int Event,
                                 const TCHAR *pMessage,
                                 const float Percent,
                                 long UserData);


/*===========================================================================
 *
 * Begin Class CEsmFile Definition
 *
 * Class to handle one ESM or ESP file.
 *
 *=========================================================================*/
class CEsmFile {
  protected:
	CSString m_Filename;
	long m_FileSize;
	bool m_IsMaster;
	bool m_IsActive;

	CEsmRecArray m_Records;
	ESMFILE_CALLBACK m_CallBack;
	long m_CallBackData;


  public:
	/* Class Constructors/Destructors */
	CEsmFile();
	virtual ~CEsmFile() {
		Destroy();
	}

	virtual void Destroy();

	/* Add a record to the file */
	void AddRecord(CEsmRecord *pRecord) {
		m_Records.Add(pRecord);
	}

	void AddRecord(CEsmRecord *pRecord, CEsmRecord *pInsertAfter);

	/* Allocate a new record */
	virtual CEsmRecord *AllocNewRecord(const TCHAR *pType);
	virtual CEsmRecord *AllocateRecord(const TCHAR *pType);
	virtual CEsmRecord *CreateNewRecord(const TCHAR *pType);

	/* Create a copy of a record */
	CEsmRecord *CopyRecord(CEsmRecord *pRecord);
	CEsmRecord *CreateCopy(CEsmRecord *pRecord);

	/* Create a new, empty, plugin */
	void CreateNew();

	/* Remove a record from the array */
	void DeleteRecord(CEsmRecord *pRecord) {
		m_Records.DeleteElement(pRecord);
	}

	/* Access particular records */
	CEsmRecord *FindFirst(const TCHAR *pType, int &ArrayIndex);
	CEsmRecord *FindNext(const TCHAR *pType, int &ArrayIndex);
	CEsmRecord *GetRecord(const int Index) {
		return m_Records.GetAt(Index);
	}

	int FindRecord(CEsmRecord *pRecord) {
		return (m_Records.FindElement(pRecord));
	}

	/* Get class members */
	const TCHAR *GetFilename() const {
		return m_Filename;
	}

	int GetNumRecords() const {
		return m_Records.GetSize();
	}

	bool IsMaster() const {
		return m_IsMaster;
	}

	bool IsActive() const {
		return m_IsActive;
	}

	long GetFileSize() const {
		return m_FileSize;
	}

	CEsmRecArray *GetRecords() {
		return &m_Records;
	}

	/* Read the entire file */
	bool Read(const TCHAR *pFilename);

	/* Set the callback function for load/saves */
	void SetCallback(ESMFILE_CALLBACK CallBack, const long UserData) {
		m_CallBack = CallBack;
		m_CallBackData = UserData;
	}

	/* Set class methods */
	void SetMaster(const bool Flag) {
		m_IsMaster = Flag;
	}

	void SetActive(const bool Flag) {
		m_IsActive = Flag;
	}

	/* Write the entire file */
	bool Write(const TCHAR *pFilename);
};


/* Holds information on each record in the ESM/ESP files */
struct esmrecinfo_t {
	CEsmRecord *pRecord; /* Reference to the 'latest' record */
	CEsmFile *pFile;     /* Which file is the record used from? */
	long UserData;
};

/* Array of esm record structures */
typedef TPtrArray<esmrecinfo_t> CEsmRecInfoArray;

/* Array of files */
typedef TPtrArray<CEsmFile> CEsmFileArray;


#endif
