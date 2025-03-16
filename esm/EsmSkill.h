/*===========================================================================
 *
 * File:    EsmSkill.h
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSKILL_H
#define __ESMSKILL_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubLong.h"
#include "EsmSubSKDT.h"
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
 * Begin Class CEsmSkill Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSkill : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubLong *m_pIndexData;
	CEsmSubSKDT *m_pSkillData;
	CEsmSubName *m_pDescData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSkill();
	//virtual ~CEsmSkill() { Destroy(); }
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
		return _T("Skill");
	}

	/* Get class members */
	skilldata_t *GetSkillData (void) {
		return (m_pSkillData ? m_pSkillData->GetSkillData() : NULL);
	}

	int GetSkillID (void) {
		return (m_pIndexData ? m_pIndexData->GetValue() : -1);
	}

	const TCHAR *GetName (void) {
		return (m_pIndexData ? GetESMSkill(m_pIndexData->GetValue()) : _T(""));
	}

	const TCHAR *GetType (void) {
		return (m_pSkillData ? GetESMClassSpec(GetSkillData()->Specialization) : _T(""));
	}

	const TCHAR *GetAttribute (void) {
		return (m_pSkillData ? GetESMAttribute(GetSkillData()->Attribute) : _T(""));
	}

	const TCHAR *GetDescription (void) {
		return (m_pDescData ? m_pDescData->GetName() : _T(""));
	}

	virtual bool IsSame (CEsmRecord* pRecord);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetDescription (const TCHAR* pString) {
		if (m_pDescData) {
			m_pDescData->SetName(pString);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmSkill Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/

