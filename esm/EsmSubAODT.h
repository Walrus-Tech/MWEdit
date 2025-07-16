/*===========================================================================
 *
 * File:    Esmsubaodt.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAODT_H
#define __ESMSUBAODT_H


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

/* Armor types */
#define MWESM_ARMORTYPE_MIN       0
#define MWESM_ARMORTYPE_HELMET    0
#define MWESM_ARMORTYPE_CUIRASS   1
#define MWESM_ARMORTYPE_LPAULDRON 2
#define MWESM_ARMORTYPE_RPAULDRON 3
#define MWESM_ARMORTYPE_GREAVES   4
#define MWESM_ARMORTYPE_BOOTS     5
#define MWESM_ARMORTYPE_LGAUNTLET 6
#define MWESM_ARMORTYPE_RGAUNTLET 7
#define MWESM_ARMORTYPE_SHIELD    8
#define MWESM_ARMORTYPE_LBRACER   9
#define MWESM_ARMORTYPE_RBRACER   10
#define MWESM_ARMORTYPE_MAX       10

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
	long Type;
	float Weight;
	long Value;
	long Health;
	long EnchantPts;
	long Rating;
} armordata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubAODT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAODT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubAODT();
	//virtual ~CEsmSubAODT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAODT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(armordata_t));
		m_RecordSize = sizeof(armordata_t);
		memset(m_pData, 0, sizeof(armordata_t));
	}

	/* Get class members */
	armordata_t *GetArmorData() {
		return (armordata_t *)m_pData;
	}

	long GetArmorType() {
		return GetArmorData()->Type;
	}

	float GetWeight() {
		return GetArmorData()->Weight;
	}

	long GetHealth() {
		return GetArmorData()->Health;
	}

	long GetValue() {
		return GetArmorData()->Value;
	}

	long GetEnchantPts() {
		return GetArmorData()->EnchantPts;
	}

	long GetRating() {
		return GetArmorData()->Rating;
	}

	/* Set class members */
	void SetArmorType(const int Type) {
		if (Type >= MWESM_ARMORTYPE_MIN && Type <= MWESM_ARMORTYPE_MAX) {
			GetArmorData()->Type = Type;
		}
	}

	void SetWeight(const float Value) {
		GetArmorData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetArmorData()->Value = Value;
	}

	void SetHealth(const long Value) {
		GetArmorData()->Health = Value;
	}

	void SetEnchantPts(const long Value) {
		GetArmorData()->EnchantPts = Value;
	}

	void SetRating(const long Value) {
		GetArmorData()->Rating = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAODT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
