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
	float Weight;
	long Value;
	float Quality;
	long Uses;
} lockdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubLKDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubLKDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
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

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
