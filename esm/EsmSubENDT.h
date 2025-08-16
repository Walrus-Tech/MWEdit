/*===========================================================================
 *
 * File:    EsmsubENDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBENDT_H
#define __ESMSUBENDT_H


#include "EsmSubBase.h"


/* Enchant types */
#define MWESM_ENCHTYPE_MIN            0
#define MWESM_ENCHTYPE_CASTONCE       0
#define MWESM_ENCHTYPE_CASTUSED       1
#define MWESM_ENCHTYPE_CASTSTRIKES    2
#define MWESM_ENCHTYPE_CONSTANT       3
#define MWESM_ENCHTYPE_MAX            3


#pragma pack(push, 1)

typedef struct {
	long Type;
	long EnchantCost;
	long Charge;
	long AutoCalc;
} enchantdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubENDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubENDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubENDT();
	//virtual ~CEsmSubENDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubENDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(enchantdata_t));
		m_RecordSize = sizeof(enchantdata_t);
		memset(m_pData, 0, sizeof(enchantdata_t));
		GetEnchantData()->AutoCalc = 1;
	}

	/* Get class members */
	enchantdata_t *GetEnchantData() {
		return (enchantdata_t *)m_pData;
	}

	long GetEnchantType() {
		return GetEnchantData()->Type;
	}

	long GetEnchantCost() {
		return GetEnchantData()->EnchantCost;
	}

	long GetCharge() {
		return GetEnchantData()->Charge;
	}

	bool IsAutoCalc() {
		return GetEnchantData()->AutoCalc != 0;
	}

	/* Set class members */
	void SetEnchantType(const long Value) {
		if (Value >= MWESM_ENCHTYPE_MIN && Value <= MWESM_ENCHTYPE_MAX) {
			GetEnchantData()->Type = Value;
		}
	}

	void SetEnchantCost(const long Value) {
		GetEnchantData()->EnchantCost = Value;
	}

	void SetCharge(const long Value) {
		GetEnchantData()->Charge = Value;
	}

	void SetAutoCalc(const bool Flag) {
		GetEnchantData()->AutoCalc = Flag ? 1 : 0;
	}
};


#endif
