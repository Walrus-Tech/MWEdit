/*===========================================================================
 *
 * File:    EsmRace.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMRACE_H
#define __ESMRACE_H


#include "EsmRecord.h"
#include "EsmSubNameFix.h"
#include "EsmSubName.h"
#include "EsmSubName32.h"
#include "EsmSubRADT.h"


/*===========================================================================
 *
 * Begin Class CEsmRace Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmRace : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pNameData;
	CEsmSubRADT *m_pRaceData;
	CEsmSubName *m_pDescData;


  public:
	/* Class Constructors/Destructors */
	CEsmRace();
	//virtual ~CEsmRace() { Destroy(); }
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
		return _T("Race");
	}

	/* Get class members */
	racedata_t *GetRaceData() {
		return m_pRaceData ? m_pRaceData->GetRaceData() : NULL;
	}

	const TCHAR *GetName() {
		return m_pNameData ? m_pNameData->GetName() : _T("");
	}

	const TCHAR *GetDescription() {
		return m_pDescData ? m_pDescData->GetName() : _T("");
	}

	bool IsPlayable() {
		return m_pRaceData ? ((GetRaceData()->Flags & MWESM_RACEFLAG_PLAYABLE) != 0) : false;
	}

	bool IsBeastRace() {
		return m_pRaceData ? ((GetRaceData()->Flags & MWESM_RACEFLAG_BEAST) != 0) : false;
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pString) {
		if (m_pNameData) {
			m_pNameData->SetName(pString);
		}
	}

	void SetDescription(const TCHAR *pString) {
		if (m_pDescData) {
			m_pDescData->SetName(pString);
		}
	}

	void SetPlayable(const bool Flag) {
		if (!GetRaceData()) {
			return;
		}

		if (Flag) {
			GetRaceData()->Flags |= MWESM_RACEFLAG_PLAYABLE;
		} else {
			GetRaceData()->Flags &= ~MWESM_RACEFLAG_PLAYABLE;
		}
	}

	void SetBeastRace(const bool Flag) {
		if (!GetRaceData()) {
			return;
		}

		if (Flag) {
			GetRaceData()->Flags |= MWESM_RACEFLAG_BEAST;
		} else {
			GetRaceData()->Flags &= ~MWESM_RACEFLAG_BEAST;
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
