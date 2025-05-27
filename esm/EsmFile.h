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


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmTES3.h"
#include "EsmActivator.h"
#include "EsmAlchemy.h"
#include "EsmApparatus.h"
#include "EsmArmor.h"
#include "EsmBirthSign.h"
#include "EsmBodyPart.h"
#include "EsmBook.h"
#include "EsmCell.h"
#include "EsmClass.h"
#include "EsmClothing.h"
#include "EsmContainer.h"
#include "EsmCreature.h"
#include "EsmDialogue.h"
#include "EsmDoor.h"
#include "EsmEnchant.h"
#include "EsmFaction.h"
#include "EsmGameSetting.h"
#include "EsmGlobal.h"
#include "EsmInfo.h"
#include "EsmIngrediant.h"
#include "EsmLand.h"
#include "EsmLevelCrea.h"
#include "EsmLevelItem.h"
#include "EsmLight.h"
#include "EsmLockPick.h"
#include "EsmMisc.h"
#include "EsmNpc.h"
#include "EsmProbe.h"
#include "EsmRace.h"
#include "EsmRegion.h"
#include "EsmRepair.h"
#include "EsmScript.h"
#include "EsmSkill.h"
#include "EsmSound.h"
#include "EsmSoundGen.h"
#include "EsmSpell.h"
#include "EsmStartScript.h"
#include "EsmStatic.h"
#include "EsmWeapon.h"
#include "EsmMagicEffect.h"
#include "EsmGlobal.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Callback event codes */
#define ESM_CALLBACK_RECORD 1

/* Number of records between the callback function when loading/saving */
#define ESM_CALLBACK_RATE 25

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Array of record pointers */
typedef TPtrArray<CEsmRecord> CEsmRecArray;

/* Callback function type */
typedef int (*ESMFILE_CALLBACK) (const int Event,
                                 const TCHAR *pMessage,
                                 const float Percent,
                                 long UserData);

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmFile Definition
 *
 * Class to handle one ESM or ESP file.
 *
 *=========================================================================*/
class CEsmFile {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CSString m_Filename;
	long m_FileSize;
	bool m_IsMaster;
	bool m_IsActive;

	CEsmRecArray m_Records;
	ESMFILE_CALLBACK m_CallBack;
	long m_CallBackData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmFile();
	virtual ~CEsmFile() {
		Destroy();
	}

	virtual void Destroy(void);

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
	void CreateNew(void);

	/* Remove a record from the array */
	void DeleteRecord(CEsmRecord *pRecord) {
		m_Records.DeleteElement(pRecord);
	}

	/* Access particular records */
	CEsmRecord *FindFirst(const TCHAR *pType, int &ArrayIndex);
	CEsmRecord *FindNext(const TCHAR *pType, int &ArrayIndex);
	CEsmRecord *GetRecord(const int Index) {
		return (m_Records.GetAt(Index));
	}

	int FindRecord(CEsmRecord *pRecord) {
		return (m_Records.FindElement(pRecord));
	}

	/* Get class members */
	const TCHAR *GetFilename(void) const {
		return (m_Filename);
	}

	int GetNumRecords(void) const {
		return (m_Records.GetSize());
	}

	bool IsMaster(void) const {
		return (m_IsMaster);
	}

	bool IsActive(void) const {
		return (m_IsActive);
	}

	long GetFileSize(void) const {
		return (m_FileSize);
	}

	CEsmRecArray *GetRecords(void) {
		return (&m_Records);
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

/*===========================================================================
 *      End of Class CEsmFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin More Type Definitions
 *
 *=========================================================================*/

/* Holds information on each record in the ESM/ESP files */
struct esmrecinfo_t {
	CEsmRecord *pRecord;    /* Reference to the 'latest' record */
	CEsmFile *pFile;      /* Which file is the record used from? */
	long UserData;
};

/* Array of esm record structures */
typedef TPtrArray<esmrecinfo_t> CEsmRecInfoArray;

/* Array of files */
typedef TPtrArray<CEsmFile> CEsmFileArray;

/*===========================================================================
 *      End of More Type Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmfile.H
 *=========================================================================*/
