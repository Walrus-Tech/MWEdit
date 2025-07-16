/*===========================================================================
 *
 * File:    EsmMagicEffect.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmMagicEffect.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmMagicEffect.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmMagicEffect::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_INDX,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_MEDT,
		CEsmSubMEDT::Create
	},
	{
		MWESM_SUBREC_ITEX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_PTEX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CVFX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_BVFX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_HVFX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_AVFX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CSND,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_BSND,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_HSND,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ASND,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DESC,
		CEsmSubName::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Constructor
 *
 *=========================================================================*/
CEsmMagicEffect::CEsmMagicEffect() {
	//DEFINE_FUNCTION("CEsmMagicEffect::CEsmMagicEffect()");
	m_pIndexData = NULL;
	m_pEffectData = NULL;
	m_pIcon = NULL;
	m_pParticle = NULL;
	m_pDescription = NULL;
	m_pCastSound = NULL;
	m_pHitSound = NULL;
	m_pAreaSound = NULL;
	m_pBoltSound = NULL;
	m_pCastVisual = NULL;
	m_pHitVisual = NULL;
	m_pAreaVisual = NULL;
	m_pBoltVisual = NULL;
}

/*===========================================================================
 *      End of Class CEsmMagicEffect Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmMagicEffect::Destroy() {
	//DEFINE_FUNCTION("CEsmMagicEffect::Destroy()");
	m_pIndexData = NULL;
	m_pEffectData = NULL;
	m_pIcon = NULL;
	m_pParticle = NULL;
	m_pDescription = NULL;
	m_pCastSound = NULL;
	m_pHitSound = NULL;
	m_pAreaSound = NULL;
	m_pBoltSound = NULL;
	m_pCastVisual = NULL;
	m_pHitVisual = NULL;
	m_pAreaVisual = NULL;
	m_pBoltVisual = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmMagicEffect::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmMagicEffect *pEffect;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_MGEF)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pEffect = (CEsmMagicEffect *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_SCHOOL:
			return StringCompare(GetSchool(), pEffect->GetSchool(), false);

		case ESM_FIELD_ID:
			return StringCompare(GetEffect(), pEffect->GetEffect(), false);

		case ESM_FIELD_COST:
			return (int)(GetBaseCost() * 100 - pEffect->GetBaseCost() * 100);

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmMagicEffect::Create() {
	DEFINE_FUNCTION("CEsmMagicEffect::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmMagicEffect);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmMagicEffect::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);

	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_INDX);
	AllocateSubRecord(MWESM_SUBREC_MEDT);
	AllocateSubRecord(MWESM_SUBREC_ITEX);
	AllocateSubRecord(MWESM_SUBREC_PTEX);
	AllocateSubRecord(MWESM_SUBREC_CVFX);
	AllocateSubRecord(MWESM_SUBREC_AVFX);
	AllocateSubRecord(MWESM_SUBREC_BVFX);
	AllocateSubRecord(MWESM_SUBREC_HVFX);
	AllocateSubRecord(MWESM_SUBREC_DESC);

	m_pEffectData->CreateNew();
	m_pIndexData->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - float GetAlchemyCost (Duration, Magnitude);
 *
 * Returns the computed spell cost for the alchemy enchantment of the
 * given duration and magnitude.  Returns -1 on any error.
 *
 *=========================================================================*/
float CEsmMagicEffect::GetAlchemyCost(const int Duration, const int Magnitude) {
	const esmeffectdata_t *pEffectData;
	float Cost;
	float BaseCost;
	/* Get the basic effect data */
	pEffectData = GetESMEffectData(GetEffectID());

	if (pEffectData == NULL) {
		return -1;
	}

	BaseCost = GetBaseCost();

	/* Compute cost based on the effect flags */
	if (pEffectData->HasDuration() && pEffectData->HasMagnitude()) {
		Cost = (float)(BaseCost / 10.0 + BaseCost * Duration * Magnitude / 5.0);
	} else if (pEffectData->HasDuration()) {
		Cost = (float)(BaseCost / 10.0 + BaseCost * Duration / 5.0);
	} else if (pEffectData->HasMagnitude()) {
		Cost = (float)(BaseCost / 10.0 + BaseCost * Magnitude / 5.0);
	} else {
		Cost = (float)(BaseCost / 10.0 + BaseCost / 5.0);
	}

	return Cost;
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::GetAlchemyCost()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - float GetEnchantCost (EffectData);
 *
 * Computes the spell cost for the given enchant data.
 *
 *=========================================================================*/
float CEsmMagicEffect::GetEnchantCost(enchanteffect_t &EffectData) {
	const esmeffectdata_t *pEffectData;
	float Cost;
	float BaseCost;
	/* Get the basic effect data */
	pEffectData = GetESMEffectData(GetEffectID());

	if (pEffectData == NULL) {
		return -1;
	}

	BaseCost = GetBaseCost();

	/* Compute cost based on the effect flags */
	if (pEffectData->HasDuration() && pEffectData->HasMagnitude()) {
		Cost = (float)(BaseCost * EffectData.Duration
		               * ((float)EffectData.MagMax
		               +  (float)EffectData.MagMin) / 40.0);
	} else if (pEffectData->HasDuration()) {
		Cost = (float)(BaseCost * EffectData.Duration / 20.0);
	} else if (pEffectData->HasMagnitude()) {
		Cost = (float)(BaseCost * ((float)EffectData.MagMax + (float)EffectData.MagMin) / 40.0);
	} else {
		Cost = (float)(BaseCost / 20.0);
	}

	/* Add in the area effect */
	if (EffectData.RangeType != MWESM_ENCHANTRANGE_SELF) {
		Cost += (float)(BaseCost * EffectData.Area / 40.0);
	}

	/* Add in the target type effect */
	if (EffectData.RangeType == MWESM_ENCHANTRANGE_TARGET) {
		Cost *= 1.5f;
	}

	return Cost;
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::GetEnchantCost()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmMagicEffect Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmMagicEffect::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_SCHOOL:
			return GetSchool();

		case ESM_FIELD_ID:
			return GetEffect();

		case ESM_FIELD_COST:
			snprintf(s_Buffer, 31, _T("%.2f"), GetBaseCost());
			return s_Buffer;

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmMagicEffect::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Method - bool IsSame (pRecord);
 *
 *=========================================================================*/
bool CEsmMagicEffect::IsSame(CEsmRecord *pRecord) {
	/* Check type first */
	if (!pRecord->IsType(MWESM_REC_MGEF)) {
		return false;
	}

	CEsmMagicEffect *pEffect = (CEsmMagicEffect *)pRecord;

	if (m_pIndexData == NULL) {
		return false;
	}

	return pEffect->IsEffect(m_pIndexData->GetValue());
}

/*===========================================================================
 *      End of Class Method CEsmMagicEffect::IsSame()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmMagicEffect Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmMagicEffect::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_MEDT)) {
		m_pEffectData = (CEsmSubMEDT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_INDX)) {
		m_pIndexData = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_ITEX)) {
		m_pIcon = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_PTEX)) {
		m_pParticle = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DESC)) {
		m_pDescription = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CVFX)) {
		m_pCastVisual = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_BVFX)) {
		m_pBoltVisual = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_AVFX)) {
		m_pAreaVisual = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_HVFX)) {
		m_pHitVisual = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_CSND)) {
		m_pCastSound = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_BSND)) {
		m_pBoltSound = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_ASND)) {
		m_pAreaSound = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_HSND)) {
		m_pHitSound = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmMagicEffect::CEsmMagicEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Set Methods
 *
 *=========================================================================*/
void CEsmMagicEffect::SetIcon(const TCHAR *pString) {
	if (m_pIcon == NULL) {
		AllocateSubRecord(MWESM_SUBREC_ITEX);
	}

	m_pIcon->SetName(pString);
}

void CEsmMagicEffect::SetParticle(const TCHAR *pString) {
	if (m_pParticle == NULL) {
		AllocateSubRecord(MWESM_SUBREC_PTEX);
	}

	m_pParticle->SetName(pString);
}

void CEsmMagicEffect::SetDescription(const TCHAR *pString) {
	if (m_pDescription == NULL) {
		AllocateSubRecord(MWESM_SUBREC_DESC);
	}

	m_pDescription->SetName(pString);
}

void CEsmMagicEffect::SetCastSound(const TCHAR *pString) {
	if (m_pCastSound == NULL) {
		AllocateSubRecord(MWESM_SUBREC_CSND);
	}

	m_pCastSound->SetName(pString);
}

void CEsmMagicEffect::SetBoltSound(const TCHAR *pString) {
	if (m_pBoltSound == NULL) {
		AllocateSubRecord(MWESM_SUBREC_BSND);
	}

	m_pBoltSound->SetName(pString);
}

void CEsmMagicEffect::SetAreaSound(const TCHAR *pString) {
	if (m_pAreaSound == NULL) {
		AllocateSubRecord(MWESM_SUBREC_ASND);
	}

	m_pAreaSound->SetName(pString);
}

void CEsmMagicEffect::SetHitSound(const TCHAR *pString) {
	if (m_pHitSound == NULL) {
		AllocateSubRecord(MWESM_SUBREC_HSND);
	}

	m_pHitSound->SetName(pString);
}

void CEsmMagicEffect::SetCastVisual(const TCHAR *pString) {
	if (m_pCastVisual == NULL) {
		AllocateSubRecord(MWESM_SUBREC_CVFX);
	}

	m_pCastVisual->SetName(pString);
}

void CEsmMagicEffect::SetBoltVisual(const TCHAR *pString) {
	if (m_pBoltVisual == NULL) {
		AllocateSubRecord(MWESM_SUBREC_BVFX);
	}

	m_pBoltVisual->SetName(pString);
}

void CEsmMagicEffect::SetAreaVisual(const TCHAR *pString) {
	if (m_pAreaVisual == NULL) {
		AllocateSubRecord(MWESM_SUBREC_AVFX);
	}

	m_pAreaVisual->SetName(pString);
}

void CEsmMagicEffect::SetHitVisual(const TCHAR *pString) {
	if (m_pHitVisual == NULL) {
		AllocateSubRecord(MWESM_SUBREC_HVFX);
	}

	m_pHitVisual->SetName(pString);
}

/*===========================================================================
 *      End of Set Methods
 *=========================================================================*/
