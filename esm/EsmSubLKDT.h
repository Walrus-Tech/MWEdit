/*===========================================================================
 *
 * File:    EsmsubLKDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBLKDT_H
#define __ESMSUBLKDT_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	float Quality;
	long Uses;
} lockdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubLKDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubLKDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubLKDT();
	//virtual ~CEsmSubLKDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubLKDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(lockdata_t));
		m_RecordSize = sizeof(lockdata_t);
		memset(m_pData, 0, sizeof(lockdata_t));
	}

	/* Get class members */
	lockdata_t *GetLockData() {
		return (lockdata_t *)m_pData;
	}

	float GetWeight() {
		return GetLockData()->Weight;
	}

	float GetQuality() {
		return GetLockData()->Quality;
	}

	long GetValue() {
		return GetLockData()->Value;
	}

	long GetUses() {
		return GetLockData()->Uses;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetLockData()->Weight = Value;
	}

	void SetQuality(const float Value) {
		GetLockData()->Quality = Value;
	}

	void SetValue(const long Value) {
		GetLockData()->Value = Value;
	}

	void SetUses(const long Value) {
		GetLockData()->Uses = Value;
	}
};


#endif
