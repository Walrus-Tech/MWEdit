/*===========================================================================
 *
 * File:    EsmClass.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCLASS_H
#define __ESMCLASS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubCLDT.h"
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
 * Begin Class CEsmClass Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmClass : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pName;
	CEsmSubCLDT *m_pData;
	CEsmSubName *m_pDescription;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmClass();
	//virtual ~CEsmClass() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Class");
	}

	/* Get class members */
	classdata_t *GetClassData(void) {
		return (m_pData ? m_pData->GetClassData() : NULL);
	}

	const TCHAR *GetName(void) {
		return (m_pName ? m_pName->GetName() : _T(""));
	}

	const TCHAR *GetDescription(void) {
		return (m_pDescription ? m_pDescription->GetName() : _T(""));
	}

	long GetFlags(void) {
		return (m_pData ? m_pData->GetFlags() : 0);
	}

	long GetAutoCalcFlags(void) {
		return (m_pData ? m_pData->GetAutoCalcFlags() : 0);
	}

	bool IsPlayable(void) {
		return (m_pData ? m_pData->IsPlayable() : false);
	}

	/* Get autocalc flags */
	bool IsAutoWeapon(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_WEAPONS) : false);
	}

	bool IsAutoArmor(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_ARMOR) : false);
	}

	bool IsAutoClothing(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_CLOTHING) : false);
	}

	bool IsAutoBook(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_BOOKS) : false);
	}

	bool IsAutoIngrediant(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_INGREDIANTS) : false);
	}

	bool IsAutoPick(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_PICKS) : false);
	}

	bool IsAutoProbe(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_PROBES) : false);
	}

	bool IsAutoLight(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_LIGHTS) : false);
	}

	bool IsAutoApparatus(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_APPARATUS) : false);
	}

	bool IsAutoRepair(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_REPAIR) : false);
	}

	bool IsAutoMisc(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_MISC) : false);
	}

	bool IsAutoSpell(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_SPELLS) : false);
	}

	bool IsAutoMagicItem(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_MAGICITEMS) : false);
	}

	bool IsAutoPotion(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_POTIONS) : false);
	}

	bool IsAutoTraining(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_TRAINING) : false);
	}

	bool IsAutoSpellMaking(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_SPELLMAKING) : false);
	}

	bool IsAutoEnchanting(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_ENCHANTING) : false);
	}

	bool IsAutoRepairItem(void) {
		return (m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_REPAIRITEM) : false);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pString) {
		if (m_pName) {
			m_pName->SetName(pString);
		}
	}

	void SetDescription(const TCHAR *pString) {
		if (m_pDescription) {
			m_pDescription->SetName(pString);
		}
	}

	void SetPlayable(const bool Flag) {
		if (m_pData) {
			m_pData->SetPlayable(Flag);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmClass Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/
