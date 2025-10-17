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


#include "esm/EsmRecord.h"
#include "esm/EsmSubName.h"
#include "esm/EsmSubCLDT.h"


/*===========================================================================
 *
 * Begin Class CEsmClass Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmClass : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pName;
	CEsmSubCLDT *m_pData;
	CEsmSubName *m_pDescription;


  public:
	/* Class Constructors/Destructors */
	CEsmClass();
	//virtual ~CEsmClass() { Destroy(); }
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
		return _T("Class");
	}

	/* Get class members */
	classdata_t *GetClassData() {
		return m_pData ? m_pData->GetClassData() : NULL;
	}

	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	const TCHAR *GetDescription() {
		return m_pDescription ? m_pDescription->GetName() : _T("");
	}

	long GetFlags() {
		return m_pData ? m_pData->GetFlags() : 0;
	}

	long GetAutoCalcFlags() {
		return m_pData ? m_pData->GetAutoCalcFlags() : 0;
	}

	bool IsPlayable() {
		return m_pData ? m_pData->IsPlayable() : false;
	}

	/* Get autocalc flags */
	bool IsAutoWeapon() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_WEAPONS) : false;
	}

	bool IsAutoArmor() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_ARMOR) : false;
	}

	bool IsAutoClothing() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_CLOTHING) : false;
	}

	bool IsAutoBook() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_BOOKS) : false;
	}

	bool IsAutoIngrediant() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_INGREDIANTS) : false;
	}

	bool IsAutoPick() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_PICKS) : false;
	}

	bool IsAutoProbe() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_PROBES) : false;
	}

	bool IsAutoLight() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_LIGHTS) : false;
	}

	bool IsAutoApparatus() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_APPARATUS) : false;
	}

	bool IsAutoRepair() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_REPAIR) : false;
	}

	bool IsAutoMisc() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_MISC) : false;
	}

	bool IsAutoSpell() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_SPELLS) : false;
	}

	bool IsAutoMagicItem() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_MAGICITEMS) : false;
	}

	bool IsAutoPotion() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_POTIONS) : false;
	}

	bool IsAutoTraining() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_TRAINING) : false;
	}

	bool IsAutoSpellMaking() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_SPELLMAKING) : false;
	}

	bool IsAutoEnchanting() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_ENCHANTING) : false;
	}

	bool IsAutoRepairItem() {
		return m_pData ? m_pData->IsAutoCalcFlag(MWESM_CLASSAUTO_REPAIRITEM) : false;
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


#endif
