/*===========================================================================
 *
 * File:    EsmIngrediant.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMINGREDIANT_H
#define __ESMINGREDIANT_H


#include "EsmItem2.h"
#include "EsmSubENAM.h"
#include "EsmSubIRDT.h"


#define MWESM_INGRE_NUMENCHANTS 4


/*===========================================================================
 *
 * Begin Class CEsmIngrediant Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmIngrediant : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubIRDT *m_pIngreData; /* Reference to subrecords */


  public:
	/* Class Constructors/Destructors */
	CEsmIngrediant();
	//virtual ~CEsmIngrediant() { Destroy(); }
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
		return _T("Ingrediant");
	}

	/* Get class members */
	ingredata_t *GetIngreData() {
		return m_pIngreData ? m_pIngreData->GetIngreData() : NULL;
	}

	virtual float GetWeight() {
		return m_pIngreData ? m_pIngreData->GetWeight() : 0;
	}

	virtual long GetValue() {
		return m_pIngreData ? m_pIngreData->GetValue() : 0;
	}

	/* Access the effect/skill/attribute IDs */
	long GetEffectID(const int Index) {
		return m_pIngreData ? m_pIngreData->GetEffectID(Index) : -1;
	}

	long GetSkillID(const int Index) {
		return m_pIngreData ? m_pIngreData->GetSkillID(Index) : -1;
	}

	long GetAttributeID(const int Index) {
		return m_pIngreData ? m_pIngreData->GetAttributeID(Index) : -1;
	}

	bool IsValidEffect(const int Index) {
		return m_pIngreData ? m_pIngreData->IsValidEffect(Index) : false;
	}

	const TCHAR *GetEffect(const int Index) {
		return GetESMEffect(GetEffectID(Index));
	}

	const TCHAR *GetSkill (const int Index) {
		return GetESMSkill(GetEffectID(Index));
	}

	const TCHAR *GetAttribute(const int Index) {
		return GetESMAttribute(GetEffectID(Index));
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (m_pIngreData != NULL) {
			m_pIngreData->SetWeight(Weight);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pIngreData != NULL) {
			m_pIngreData->SetValue(Value);
		}
	}

	void SetEffect(const int Index, const int Value) {
		if (m_pIngreData != NULL) {
			m_pIngreData->SetEffectID(Index, Value);
		}
	}

	void SetSkill(const int Index, const int Value) {
		if (m_pIngreData != NULL) {
			m_pIngreData->SetSkillID(Index, Value);
		}
	}

	void SetAttribute(const int Index, const int Value) {
		if (m_pIngreData != NULL) {
			m_pIngreData->SetAttributeID(Index, Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
