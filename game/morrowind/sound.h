/*===========================================================================
 *
 * File:    EsmSound.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSOUND_H
#define __ESMSOUND_H


#include "esm/EsmRecord.h"
#include "esm/EsmSubName.h"
#include "esm/EsmSubNameFix.h"
#include "esm/EsmSubDATA.h"


/*===========================================================================
 *
 * Begin Class CEsmSound Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSound : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubDATA *m_pData; /* Reference to sub-records */
	CEsmSubName *m_pName;


  public:
	/* Class Constructors/Destructors */
	CEsmSound();
	//virtual ~CEsmSound() { Destroy(); }
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
		return _T("Sound");
	}

	/* Get class members */
	sounddata_t *GetSoundData() {
		return m_pData ? m_pData->GetSoundData() : NULL;
	}

	float GetVolume() {
		return m_pData ? ((float)GetSoundData()->Volume) / 255.0f : 0.0f;
	}

	int GetMinRange() {
		return m_pData ? GetSoundData()->MinRange : 0;
	}

	int GetMaxRange() {
		return m_pData ? GetSoundData()->MaxRange : 0;
	}

	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetVolume(const float Volume);
	void SetMinRange(const int Range);
	void SetMaxRange(const int Range);
	void SetName(const TCHAR *pName) {
		if (m_pName) {
			m_pName->SetName(pName);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
