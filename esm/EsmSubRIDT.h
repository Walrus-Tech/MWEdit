/*===========================================================================
 *
 * File:    EsmsubRIDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBRIDT_H
#define __ESMSUBRIDT_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	long Uses;
	float Quality;
} repairdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubRIDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubRIDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubRIDT();
	//virtual ~CEsmSubRIDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubRIDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(repairdata_t));
		m_RecordSize = sizeof(repairdata_t);
		memset(m_pData, 0, sizeof(repairdata_t));
	}

	/* Get class members */
	repairdata_t *GetRepairData() {
		return (repairdata_t *)m_pData;
	}

	float GetWeight() {
		return GetRepairData()->Weight;
	}

	float GetQuality() {
		return GetRepairData()->Quality;
	}

	long GetValue() {
		return GetRepairData()->Value;
	}

	long GetUses() {
		return GetRepairData()->Uses;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetRepairData()->Weight = Value;
	}

	void SetQuality(const float Value) {
		GetRepairData()->Quality = Value;
	}

	void SetValue(const long Value) {
		GetRepairData()->Value = Value;
	}

	void SetUses(const long Value) {
		GetRepairData()->Uses = Value;
	}
};


#endif
