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


#include "EsmItem3.h"
#include "EsmSubBKDT.h"


/*===========================================================================
 *
 * Begin Class CEsmBook Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmBook : public CEsmItem3 {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubBKDT *m_pBookData; /* Reference to subrecords */
	CEsmSubName *m_pText;


  public:
	/* Class Constructors/Destructors */
	CEsmBook();
	//virtual ~CEsmBook() { Destroy(); }
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
		return _T("Book");
	}

	/* Get class members */
	bookdata_t *GetBookData() {
		return m_pBookData == NULL ? NULL : m_pBookData->GetBookData();
	}

	const TCHAR *GetBookText() {
		return m_pText ? m_pText->GetName() : _T("");
	}

	virtual float GetWeight() {
		return m_pBookData == NULL ? 0 : m_pBookData->GetWeight();
	}

	virtual long GetValue() {
		return m_pBookData == NULL ? 0 : m_pBookData->GetValue();
	}

	virtual long GetEnchantPts() {
		return m_pBookData == NULL ? 0 : m_pBookData->GetEnchantPts();
	}

	int GetSkillID() {
		return m_pBookData == NULL ? -1 : m_pBookData->GetSkillID();
	}

	bool IsScroll() {
		return m_pBookData == NULL ? false : m_pBookData->IsScroll();
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetScroll(const bool Flag) {
		if (m_pBookData) {
			m_pBookData->SetScroll(Flag);
		}
	}

	void SetSkillID(const int Skill) {
		if (m_pBookData) {
			m_pBookData->SetSkillID(Skill);
		}
	}

	void SetEnchantPts(const int Value) {
		if (m_pBookData) {
			m_pBookData->SetEnchantPts(Value);
		}
	}

	void SetWeight(const float Weight) {
		if (m_pBookData) {
			m_pBookData->SetWeight(Weight);
		}
	}

	void SetBookText(const TCHAR *pText) {
		if (m_pText) {
			m_pText->SetName(pText);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pBookData) {
			m_pBookData->SetValue(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


/* Convert an armor type to a string */
const TCHAR *GetESMArmorType(const int ArmorType);


#endif
