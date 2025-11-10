/*===========================================================================
 *
 * File:    EsmInfo.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMINFO_H
#define __ESMINFO_H


#include "esm/EsmRecord.h"
#include "esm/EsmSubNameFix.h"
#include "esm/EsmSubByte.h"
#include "esm/EsmSubName.h"
#include "esm/EsmSubName512.h"
#include "esm/EsmSubLong.h"
#include "esm/EsmSubInfoDATA.h"
#include "esm/EsmSubSCVR.h"


/* Number of function/variables per info */
#define MWESM_INFO_MAXFUNCS 6


const TCHAR *GetESMInfoGender(const int Type);
const TCHAR *GetESMInfoFunction(const short FuncType);
const TCHAR *GetESMInfoFuncType(const byte FuncType);
const TCHAR *GetESMInfoCompareOp(const byte Type);


/* Used to hold type information on the various function bytes */
typedef struct {
	short Type;
	const TCHAR *pName;
} esmfuncinfo_t;

class CEsmDialogue;


/*===========================================================================
 *
 * Begin Class CEsmInfo Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmInfo : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pPrevName;
	CEsmSubNameFix *m_pNextName;
	CEsmSubInfoDATA *m_pData;
	CEsmSubName512 *m_pName;
	CEsmSubNameFix *m_pActor;
	CEsmSubNameFix *m_pRace;
	CEsmSubNameFix *m_pClass;
	CEsmSubNameFix *m_pFaction;
	CEsmSubName *m_pCell;
	CEsmSubNameFix *m_pPCFaction;
	CEsmSubNameFix *m_pSound;
	CEsmSubName *m_pResult;

	CEsmDialogue *m_pDialParent; /* Parent topic */


  public:
	/* Class Constructors/Destructors */
	CEsmInfo();
	//virtual ~CEsmInfo() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Info");
	}

	/* Get class members */
	infodata_t *GetInfoData() {
		return m_pData ? m_pData->GetInfoData() : NULL;
	}

	const TCHAR *GetResponse() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	const TCHAR *GetResult() {
		return m_pResult ? m_pResult->GetName() : _T("");
	}

	const TCHAR *GetActor() {
		return m_pActor ? m_pActor->GetName() : _T("");
	}

	const TCHAR *GetRace() {
		return m_pRace ? m_pRace->GetName() : _T("");
	}

	const TCHAR *GetClass() {
		return m_pClass ? m_pClass->GetName() : _T("");
	}

	const TCHAR *GetFaction() {
		return m_pFaction ? m_pFaction->GetName() : _T("");
	}

	const TCHAR *GetCell() {
		return m_pCell ? m_pCell->GetName() : _T("");
	}

	const TCHAR *GetPCFaction() {
		return m_pPCFaction ? m_pPCFaction->GetName() : _T("");
	}

	const TCHAR *GetSound() {
		return m_pSound ? m_pSound->GetName() : _T("");
	}

	const TCHAR *GetPrevName() {
		return m_pPrevName ? m_pPrevName->GetName() : _T("");
	}

	const TCHAR *GetNextName() {
		return m_pNextName ? m_pNextName->GetName() : _T("");
	}

	int GetDisposition() {
		return m_pData ? (int)GetInfoData()->Disposition : 0;
	}

	CEsmDialogue *GetDialParent() {
		return m_pDialParent;
	}

	const TCHAR *GetFuncText(const int Index);

	/* Checks if another record is used in this record */
	virtual bool IsUsed(const TCHAR *pID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetResponse(const TCHAR *pString) {
		if (m_pName) {
			m_pName->SetName(pString);
		}
	}

	void SetDisposition(const int Value) {
		if (m_pData) {
			GetInfoData()->Disposition = (byte)Value;
		}
	}

	void SetDialParent(CEsmDialogue *pDial) {
		m_pDialParent = pDial;
	}

	void SetPrevName(const TCHAR *pString) {
		if (m_pPrevName) {
			m_pPrevName->SetName(pString);
		}
	}

	void SetNextName(const TCHAR *pString) {
		if (m_pNextName) {
			m_pNextName->SetName(pString);
		}
	}

	void SetResult(const TCHAR *pString);
	void SetActor(const TCHAR *pString);
	void SetClass(const TCHAR *pString);
	void SetRace(const TCHAR *pString);
	void SetFaction(const TCHAR *pString);
	void SetSound(const TCHAR *pString);
	void SetPCFaction(const TCHAR *pString);
	void SetCell(const TCHAR *pString);
};


#endif
