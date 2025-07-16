/*===========================================================================
 *
 * File:    EsmScript.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSCRIPT_H
#define __ESMSCRIPT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubSCHD.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Max script text size */
#define ESM_SCRIPT_MAXTEXT 32768

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmScript Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmScript : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubSCHD *m_pScriptHeader;
	CEsmSubRecord *m_pScriptVars;
	CEsmSubRecord *m_pScriptData;
	CEsmSubName *m_pScriptText;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmScript();
	//virtual ~CEsmScript() { Destroy(); }
	virtual void Destroy();

	/* Clear any of the compiled data information */
	void ClearCompileData();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Export a script to a text file */
	bool ExportScript(const TCHAR *pPath);

	/* Find a local variable info */
	short FindLocalVar(const TCHAR *pLocalVar, char &VarType);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Script");
	}

	/* Get class members */
	virtual const TCHAR *GetID() {
		return m_pScriptHeader ? m_pScriptHeader->GetName() : _T("");
	}

	virtual void SetID(const TCHAR *pString) {
		if (m_pScriptHeader) {
			m_pScriptHeader->SetName(pString);
		}
	}

	CEsmSubSCHD *GetScriptHeader() {
		return m_pScriptHeader;
	}

	CEsmSubRecord *GetScriptVars() {
		return m_pScriptVars;
	}

	CEsmSubRecord *GetScriptData() {
		return m_pScriptData;
	}

	const TCHAR *GetScriptText() {
		return m_pScriptText ? m_pScriptText->GetName() : _T("");
	}

	int GetScriptSize() {
		return m_pScriptText ? m_pScriptText->GetRecordSize() : 0;
	}

	/* Checks if another record is used in this record */
	virtual bool IsUsed(const TCHAR *pID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetScriptText(const TCHAR *pName) {
		if (m_pScriptText) {
			m_pScriptText->SetName(pName);
		}
	}
};

/*===========================================================================
 *      End of Class CEsmScript Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmScript.H
 *=========================================================================*/
