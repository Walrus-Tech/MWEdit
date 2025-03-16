/*===========================================================================
 *
 * File:    EsmsubENAM.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBENAM_H
#define __ESMSUBENAM_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

#define MWESM_ALCH_MAXENCHANTS 8

/* Range types */
#define MWESM_ENCHANTRANGE_MIN    0
#define MWESM_ENCHANTRANGE_SELF   0
#define MWESM_ENCHANTRANGE_TOUCH  1
#define MWESM_ENCHANTRANGE_TARGET 2
#define MWESM_ENCHANTRANGE_MAX    2

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	short EffectID;
	byte SkillID;
	byte AttributeID;
	long RangeType;
	long Area;
	long Duration;
	long MagMin;
	long MagMax;
} enchanteffect_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubENAM Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubENAM : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubENAM();
	//virtual ~CEsmSubENAM() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubENAM);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(enchanteffect_t));
		m_RecordSize = sizeof(enchanteffect_t);
		memset(m_pData, 0, sizeof(enchanteffect_t));
		GetEnchantData()->EffectID = -1;
		GetEnchantData()->SkillID = -1;
		GetEnchantData()->AttributeID = -1;
	}

	/* Get class methods */
	enchanteffect_t *GetEnchantData (void) {
		return (enchanteffect_t *) m_pData;
	}

	short GetEffectID (void) {
		return (GetEnchantData()->EffectID);
	}

	byte GetSkillID (void) {
		return (GetEnchantData()->SkillID);
	}

	byte GetAttributeID (void) {
		return (GetEnchantData()->AttributeID);
	}

	long GetRangeType (void) {
		return (GetEnchantData()->RangeType);
	}

	long GetArea (void) {
		return (GetEnchantData()->Area);
	}

	long GetDuration (void) {
		return (GetEnchantData()->Duration);
	}

	long GetMagMin (void) {
		return (GetEnchantData()->MagMin);
	}

	long GetMagMax (void) {
		return (GetEnchantData()->MagMax);
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed (const TCHAR* pID) {
		return (StringCompare(GetESMEffect(GetEnchantData()->EffectID), pID, false) == 0);
	}

	/* Set class members */
	void SetEffectID (const int Value) {
		GetEnchantData()->EffectID = Value;
	}

	void SetSkillID (const byte Value) {
		GetEnchantData()->SkillID = Value;
	}

	void SetAttributeID (const byte Value) {
		GetEnchantData()->AttributeID = Value;
	}

	void SetRangeType (const long Value) {
		if (Value >= MWESM_ENCHANTRANGE_MIN && Value <= MWESM_ENCHANTRANGE_MAX) {
			GetEnchantData()->RangeType = Value;
		}
	}

	void SetArea (const long Value) {
		GetEnchantData()->Area = Value;
	}

	void SetDuration (const long Value) {
		GetEnchantData()->Duration = Value;
	}

	void SetMagMin (const long Value) {
		GetEnchantData()->MagMin = Value;
	}

	void SetMagMax (const long Value) {
		GetEnchantData()->MagMax = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubENAM Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
