/*===========================================================================
 *
 * File:    Esmstartscript.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 13, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSTARTSCRIPT_H
#define __ESMSTARTSCRIPT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubLong.h"
#include "EsmSubName32.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmStartScript Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmStartScript : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pName;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmStartScript();
	//virtual ~CEsmStartScript() { Destroy(); }
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
		return _T("Start Script");
	}

	/* Get class members */
	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pString) {
		if (m_pName) {
			m_pName->SetName(pString);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmStartScript Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmstartscript.H
 *=========================================================================*/
