/*===========================================================================
 *
 * File:    EsmLockPick.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMLOCKPICK_H
#define __ESMLOCKPICK_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
#include "EsmSubLKDT.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmLockPick Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmLockPick : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubLKDT *m_pLockData; /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmLockPick();
	//virtual ~CEsmLockPick() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Lock Pick");
	}

	/* Get class members */
	lockdata_t *GetLockData() {
		return m_pLockData ? m_pLockData->GetLockData() : NULL;
	}

	virtual float GetWeight() {
		return m_pLockData ? m_pLockData->GetWeight() : 0;
	}

	virtual long GetValue() {
		return m_pLockData ? m_pLockData->GetValue() : 0;
	}

	float GetQuality() {
		return m_pLockData ? m_pLockData->GetQuality() : 0;
	}

	long GetUses() {
		return m_pLockData ? m_pLockData->GetUses() : 0;
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (m_pLockData) {
			m_pLockData->SetWeight(Weight);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pLockData) {
			m_pLockData->SetValue(Value);
		}
	}

	void SetUses(const long Value) {
		if (m_pLockData) {
			m_pLockData->SetUses(Value);
		}
	}

	void SetQuality(const float Value) {
		if (m_pLockData) {
			m_pLockData->SetQuality(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmArmor Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
