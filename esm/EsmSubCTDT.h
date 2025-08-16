/*===========================================================================
 *
 * File:    EsmsubCTDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBCTDT_H
#define __ESMSUBCTDT_H


#include "EsmSubBase.h"


/* Armor types */
#define MWESM_CLOTHTYPE_MIN   0
#define MWESM_CLOTHTYPE_PANTS 0
#define MWESM_CLOTHTYPE_MAX   9


#pragma pack(push, 1)

typedef struct {
	long Type;
	float Weight;
	ushort Value;
	short EnchantPts;
} clothdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubCTDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCTDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubCTDT();
	//virtual ~CEsmSubCTDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCTDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(clothdata_t));
		m_RecordSize = sizeof(clothdata_t);
		memset(m_pData, 0, sizeof(clothdata_t));
	}

	/* Get class members */
	clothdata_t *GetClothData() {
		return (clothdata_t *)m_pData;
	}

	int GetClothType() {
		return GetClothData()->Type;
	}

	ushort GetValue() {
		return GetClothData()->Value;
	}

	float GetWeight() {
		return GetClothData()->Weight;
	}

	short GetEnchantPts() {
		return GetClothData()->EnchantPts;
	}

	/* Set class members */
	void SetClothType(const int Type) {
		if (Type >= MWESM_CLOTHTYPE_MIN && Type <= MWESM_CLOTHTYPE_MAX) {
			GetClothData()->Type = Type;
		}
	}

	void SetValue(const ushort Value) {
		GetClothData()->Value = Value;
	}

	void SetWeight(const float Value) {
		GetClothData()->Weight = Value;
	}

	void SetEnchantPts(const short Value) {
		GetClothData()->EnchantPts = Value;
	}
};


#endif
