/*===========================================================================
 *
 * File:    EsmMisc.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMMISC_H
#define __ESMMISC_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
#include "EsmSubMCDT.h"
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
 * Begin Class CEsmMisc Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmMisc : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubMCDT *m_pMiscData; /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmMisc();
	//virtual ~CEsmMisc() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Misc");
	}

	/* Get class members */
	miscdata_t *GetMiscData() {
		return m_pMiscData ? m_pMiscData->GetMiscData() : NULL;
	}

	virtual float GetWeight() {
		return m_pMiscData ? m_pMiscData->GetWeight() : 0;
	}

	virtual long GetValue() {
		return m_pMiscData ? m_pMiscData->GetValue() : 0;
	}

	long GetUnknown() {
		return m_pMiscData ? m_pMiscData->GetUnknown() : 0;
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (m_pMiscData != NULL) {
			m_pMiscData->SetWeight(Weight);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pMiscData != NULL) {
			m_pMiscData->SetValue(Value);
		}
	}
};

/*===========================================================================
 *      End of Class CEsmArmor Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmMisc.H
 *=========================================================================*/
