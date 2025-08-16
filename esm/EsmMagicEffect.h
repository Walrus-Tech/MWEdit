/*===========================================================================
 *
 * File:    EsmMagicEffect.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMMAGICEFFECT_H
#define __ESMMAGICEFFECT_H


#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubLong.h"
#include "EsmSubShort.h"
#include "EsmSubByte.h"
#include "EsmSubMEDT.h"
#include "EsmSubENAM.h"


/*===========================================================================
 *
 * Begin Class CEsmMagicEffect Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmMagicEffect : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubLong *m_pIndexData;
	CEsmSubMEDT *m_pEffectData;
	CEsmSubNameFix *m_pIcon;
	CEsmSubNameFix *m_pParticle;
	CEsmSubName *m_pDescription;
	CEsmSubNameFix *m_pCastSound;
	CEsmSubNameFix *m_pHitSound;
	CEsmSubNameFix *m_pAreaSound;
	CEsmSubNameFix *m_pBoltSound;
	CEsmSubNameFix *m_pCastVisual;
	CEsmSubNameFix *m_pHitVisual;
	CEsmSubNameFix *m_pAreaVisual;
	CEsmSubNameFix *m_pBoltVisual;


  public:
	/* Class Constructors/Destructors */
	CEsmMagicEffect();
	//virtual ~CEsmMagicEffect() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Compute the cost of spells, etc... */
	float GetAlchemyCost(const int Duration, const int Magnitude);
	float GetEnchantCost(enchanteffect_t &EffectData);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Magic Effect");
	}

	/* Get class members */
	bool IsEffect(const int EffectID) {
		return m_pIndexData ? m_pIndexData->GetValue() == EffectID : false;
	}

	const TCHAR *GetEffect() {
		return GetESMEffect(GetEffectID());
	}

	const TCHAR *GetName() {
		return GetEffect();
	}

	const TCHAR *GetSchool() {
		return GetESMSpellSchool(GetSchoolID());
	}

	const TCHAR *GetIcon() {
		return m_pIcon ? m_pIcon->GetName() : _T("");
	}

	const TCHAR *GetParticle() {
		return m_pParticle ? m_pParticle->GetName() : _T("");
	}

	const TCHAR *GetDescription() {
		return m_pDescription ? m_pDescription->GetName() : _T("");
	}

	const TCHAR *GetCastSound() {
		return m_pCastSound ? m_pCastSound->GetName() : _T("");
	}

	const TCHAR *GetBoltSound() {
		return m_pBoltSound ? m_pBoltSound->GetName() : _T("");
	}

	const TCHAR *GetAreaSound() {
		return m_pAreaSound ? m_pAreaSound->GetName() : _T("");
	}

	const TCHAR *GetHitSound() {
		return m_pHitSound ? m_pHitSound->GetName() : _T("");
	}

	const TCHAR *GetCastVisual() {
		return m_pCastVisual ? m_pCastVisual->GetName() : _T("");
	}

	const TCHAR *GetBoltVisual() {
		return m_pBoltVisual ? m_pBoltVisual->GetName() : _T("");
	}

	const TCHAR *GetAreaVisual() {
		return m_pAreaVisual ? m_pAreaVisual->GetName() : _T("");
	}

	const TCHAR *GetHitVisual() {
		return m_pHitVisual ? m_pHitVisual->GetName() : _T("");
	}

	int GetEffectID() {
		return m_pIndexData ? m_pIndexData->GetValue() : -1;
	}

	float GetBaseCost() {
		return m_pEffectData ? m_pEffectData->GetBaseCost() : 0;
	}

	int GetSchoolID() {
		return m_pEffectData ? m_pEffectData->GetSpellSchool() : -1;
	}

	int GetRed() {
		return m_pEffectData ? m_pEffectData->GetRed() : 0;
	}

	int GetGreen() {
		return m_pEffectData ? m_pEffectData->GetGreen() : 0;
	}

	int GetBlue() {
		return m_pEffectData ? m_pEffectData->GetBlue() : 0;
	}

	float GetSpeed() {
		return m_pEffectData ? m_pEffectData->GetSpeedX() : 0.0f;
	}

	float GetSize() {
		return m_pEffectData ? m_pEffectData->GetSizeX() : 0.0f;
	}

	float GetMaxSize() {
		return m_pEffectData ? m_pEffectData->GetSizeCap() : 0.0f;
	}

	long GetFlags() {
		return m_pEffectData ? m_pEffectData->GetFlags() : 0;
	}

	bool IsSpellMaking() {
		return m_pEffectData ? m_pEffectData->IsSpellMaking() : false;
	}

	bool IsEnchanting() {
		return m_pEffectData ? m_pEffectData->IsEnchanting() : false;
	}

	bool IsNegative() {
		return m_pEffectData ? m_pEffectData->IsNegative() : false;
	}

	/* Get the effect data */
	magiceffectdata_t *GetMagicEffectData() {
		return m_pEffectData ? m_pEffectData->GetEffectData() : NULL;
	}

	/* Check for identical records */
	virtual bool IsSame(CEsmRecord *pRecord);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetIcon(const TCHAR *pString);
	void SetParticle(const TCHAR *pString);
	void SetDescription(const TCHAR *pString);
	void SetCastSound(const TCHAR *pString);
	void SetBoltSound(const TCHAR *pString);
	void SetAreaSound(const TCHAR *pString);
	void SetHitSound(const TCHAR *pString);
	void SetCastVisual(const TCHAR *pString);
	void SetBoltVisual(const TCHAR *pString);
	void SetAreaVisual(const TCHAR *pString);
	void SetHitVisual(const TCHAR *pString);
	void SetEnchanting(const bool Flag) {
		if (m_pEffectData) {
			m_pEffectData->SetEnchanting(Flag);
		}
	}

	void SetSpellMaking(const bool Flag) {
		if (m_pEffectData) {
			m_pEffectData->SetSpellMaking(Flag);
		}
	}

	void SetNegative(const bool Flag) {
		if (m_pEffectData) {
			m_pEffectData->SetNegative(Flag);
		}
	}

	void SetSchool(const int Value) {
		if (m_pEffectData) {
			m_pEffectData->SetSpellSchool(Value);
		}
	}

	void SetRed(const byte Value) {
		if (m_pEffectData) {
			m_pEffectData->SetRed(Value);
		}
	}

	void SetGreen(const byte Value) {
		if (m_pEffectData) {
			m_pEffectData->SetGreen(Value);
		}
	}

	void SetBlue(const byte Value) {
		if (m_pEffectData) {
			m_pEffectData->SetBlue(Value);
		}
	}

	void SetSize(const float Value) {
		if (m_pEffectData) {
			m_pEffectData->SetSizeX(Value);
		}
	}

	void SetBaseCost(const float Value) {
		if (m_pEffectData) {
			m_pEffectData->SetBaseCost(Value);
		}
	}

	void SetMaxSize(const float Value) {
		if (m_pEffectData) {
			m_pEffectData->SetSizeCap(Value);
		}
	}

	void SetSpeed(const float Value) {
		if (m_pEffectData) {
			m_pEffectData->SetSpeedX(Value);
		}
	}
};


#endif
