/*===========================================================================
 *
 * File:    EsmsubBKDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBBKDT_H
#define __ESMSUBBKDT_H


#include "esm/EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	long Scroll;
	long SkillID;
	long EnchantPts;
} bookdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubBKDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubBKDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubBKDT();
	//virtual ~CEsmSubBKDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubBKDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(bookdata_t));
		m_RecordSize = sizeof(bookdata_t);
		memset(m_pData, 0, sizeof(bookdata_t));
		GetBookData()->SkillID = -1;
	}

	/* Get class members */
	bookdata_t *GetBookData() {
		return (bookdata_t *)m_pData;
	}

	float GetWeight() {
		return GetBookData()->Weight;
	}

	long GetValue() {
		return GetBookData()->Value;
	}

	long GetEnchantPts() {
		return GetBookData()->EnchantPts;
	}

	long GetSkillID() {
		return GetBookData()->SkillID;
	}

	bool IsScroll() {
		return GetBookData()->Scroll != 0;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetBookData()->Weight = Value;
	}

	void SetEnchantPts(const long Value) {
		GetBookData()->EnchantPts = Value;
	}

	void SetValue(const long Value) {
		GetBookData()->Value = Value;
	}

	void SetSkillID(const long Value) {
		GetBookData()->SkillID = Value;
	}

	void SetScroll(const bool Flag) {
		GetBookData()->Scroll = Flag ? 1 : 0;
	}
};


#endif
