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
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	long Uses;
	float Quality;
} repairdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubRIDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubRIDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubRIDT();
	//virtual ~CEsmSubRIDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubRIDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(repairdata_t));
		m_RecordSize = sizeof(repairdata_t);
		memset(m_pData, 0, sizeof(repairdata_t));
	}

	/* Get class members */
	repairdata_t *GetRepairData(void) {
		return ((repairdata_t *)m_pData);
	}

	float GetWeight(void) {
		return (GetRepairData()->Weight);
	}

	float GetQuality(void) {
		return (GetRepairData()->Quality);
	}

	long GetValue(void) {
		return (GetRepairData()->Value);
	}

	long GetUses(void) {
		return (GetRepairData()->Uses);
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

/*===========================================================================
 *      End of Class CEsmSubRIDT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubRIDT.H
 *=========================================================================*/
