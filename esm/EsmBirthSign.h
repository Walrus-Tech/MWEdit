/*===========================================================================
 *
 * File:    EsmBirthSign.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMBIRTHSIGN_H
#define __ESMBIRTHSIGN_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubNameFix.h"
#include "EsmSubName32.h"
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
 * Begin Class CEsmBirthSign Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmBirthSign : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pNameData;
	CEsmSubNameFix *m_pTextureData;
	CEsmSubName *m_pDescData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmBirthSign();
	//virtual ~CEsmBirthSign() { Destroy(); }
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
		return _T("Birth Sign");
	}

	/* Get class members */
	const TCHAR *GetName() {
		return m_pNameData ? m_pNameData->GetName() : _T("");
	}

	const TCHAR *GetDescription() {
		return m_pDescData ? m_pDescData->GetName() : _T("");
	}

	const TCHAR *GetTexture() {
		return m_pTextureData ? m_pTextureData->GetName() : _T("");
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

	void SetTexture(const TCHAR *pString) {
		if (m_pTextureData) {
			m_pTextureData->SetName(pString);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmBirthSign Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/
