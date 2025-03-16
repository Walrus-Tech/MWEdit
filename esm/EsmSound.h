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


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubNameFix.h"
#include "EsmSubDATA.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSound Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSound : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubDATA *m_pData;    /* Reference to sub-records */
	CEsmSubName *m_pName;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSound();
	//virtual ~CEsmSound() { Destroy(); }
	virtual void Destroy (void);

	/* Compare two fields of the record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("Sound");
	}

	/* Get class members */
	sounddata_t *GetSoundData (void) {
		return (m_pData ? m_pData->GetSoundData() : NULL);
	}

	float GetVolume (void) {
		return (m_pData ? ((float)GetSoundData()->Volume) / 255.0f : 0.0f);
	}

	int GetMinRange (void) {
		return (m_pData ? GetSoundData()->MinRange : 0);
	}

	int GetMaxRange (void) {
		return (m_pData ? GetSoundData()->MaxRange : 0);
	}

	const TCHAR *GetName (void) {
		return (m_pName ? m_pName->GetName() : _T(""));
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetVolume (const float Volume);
	void SetMinRange (const int Range);
	void SetMaxRange (const int Range);
	void SetName (const TCHAR* pName) {
		if (m_pName) {
			m_pName->SetName(pName);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmSound Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/
