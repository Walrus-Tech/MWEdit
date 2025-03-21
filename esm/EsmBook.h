/*===========================================================================
 *
 * File:    EsmBook.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMBOOK_H
#define __ESMBOOK_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem3.h"
#include "EsmSubBKDT.h"
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
 * Begin Class CEsmBook Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmBook : public CEsmItem3 {
	DECLARE_SUBRECCREATE();


	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubBKDT *m_pBookData;    /* Reference to subrecords */
	CEsmSubName *m_pText;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmBook();
	//virtual ~CEsmBook() { Destroy(); }
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
		return _T("Book");
	}

	/* Get class members */
	bookdata_t *GetBookData (void) {
		return (m_pBookData == NULL ? NULL : m_pBookData->GetBookData() );
	}

	const TCHAR *GetBookText (void) {
		return (m_pText ? m_pText->GetName() : _T(""));
	}

	virtual float GetWeight (void) {
		return (m_pBookData == NULL ? 0 : m_pBookData->GetWeight());
	}

	virtual long GetValue (void) {
		return (m_pBookData == NULL ? 0 : m_pBookData->GetValue());
	}

	virtual long GetEnchantPts (void) {
		return (m_pBookData == NULL ? 0 : m_pBookData->GetEnchantPts());
	}

	int GetSkillID (void) {
		return (m_pBookData == NULL ? -1 : m_pBookData->GetSkillID());
	}

	bool IsScroll (void) {
		return (m_pBookData == NULL ? false : m_pBookData->IsScroll());
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetScroll (const bool Flag) {
		if (m_pBookData) {
			m_pBookData->SetScroll(Flag);
		}
	}

	void SetSkillID (const int Skill) {
		if (m_pBookData) {
			m_pBookData->SetSkillID(Skill);
		}
	}

	void SetEnchantPts (const int Value) {
		if (m_pBookData) {
			m_pBookData->SetEnchantPts(Value);
		}
	}

	void SetWeight (const float Weight) {
		if (m_pBookData) {
			m_pBookData->SetWeight(Weight);
		}
	}

	void SetBookText (const TCHAR* pText) {
		if (m_pText) {
			m_pText->SetName(pText);
		}
	}

	virtual void SetValue (const long Value) {
		if (m_pBookData) {
			m_pBookData->SetValue(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmBook Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Convert an armor type to a string */
const TCHAR *GetESMArmorType (const int ArmorType);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
