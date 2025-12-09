/*===========================================================================
 *
 * File:    Esmsubaadt.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBALDT_H
#define __ESMSUBALDT_H


#include "esm/EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	long AutoCalc;
} alchemydata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubALDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubALDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubALDT() {}
	//virtual ~CEsmSubALDT() { Destroy(); }
	//virtual void Destroy (void) { }

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubALDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(alchemydata_t));
		m_RecordSize = sizeof(alchemydata_t);
		memset(m_pData, 0, sizeof(alchemydata_t));
	}

	/* Get class members */
	alchemydata_t *GetAlchemyData() {
		return (alchemydata_t *)m_pData;
	}

	float GetWeight() {
		return GetAlchemyData()->Weight;
	}

	long GetValue() {
		return GetAlchemyData()->Value;
	}

	bool IsAutoCalc() {
		return GetAlchemyData()->AutoCalc != 0;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetAlchemyData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetAlchemyData()->Value = Value;
	}

	void SetAutoCalc(const bool Flag) {
		GetAlchemyData()->AutoCalc = Flag ? 1 : 0;
	}
};


#endif
