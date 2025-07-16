/*===========================================================================
 *
 * File:    EsmItem1.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Base class for all records (4: ACTI, ) with:
 *  ID
 *  Name
 *  Script
 *  Model
 *
 *=========================================================================*/
#ifndef __ESMITEM1_H
#define __ESMITEM1_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Class type flag (bit field) */
#define MWESM_CLASSTYPE_ITEM1 2

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmItem1 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmItem1 : public CEsmRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pModel; /* Reference to record fields */
	CEsmSubNameFix *m_pName;
	CEsmSubNameFix *m_pScript;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmItem1();
	//virtual ~CEsmArmor() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Used to determine the type of derived classes */
	virtual int GetClassType() {
		return CEsmRecord::GetClassType() | MWESM_CLASSTYPE_ITEM1;
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Get class members */
	const TCHAR *GetName() const {
		return m_pName ? m_pName->GetName() : _T("");
	}

	const TCHAR *GetModel() const {
		return m_pModel ? m_pModel->GetName() : _T("");
	}

	const TCHAR *GetScript() const {
		return m_pScript ? m_pScript->GetName() : _T("");
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pName) {
		if (m_pName) {
			m_pName->SetName(pName);
		}
	}

	void SetModel(const TCHAR *pName) {
		if (m_pModel) {
			m_pModel->SetName(pName);
		}
	}

	void SetScript(const TCHAR *pName);

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmItem1 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
