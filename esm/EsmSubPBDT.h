/*===========================================================================
 *
 * File:    EsmsubPBDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBPBDT_H
#define __ESMSUBPBDT_H


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
	float Quality;
	long Uses;
} probedata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubPBDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubPBDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubPBDT();
	//virtual ~CEsmSubPBDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubPBDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(probedata_t));
		m_RecordSize = sizeof(probedata_t);
		memset(m_pData, 0, sizeof(probedata_t));
	}

	/* Get class methods */
	probedata_t *GetProbeData() {
		return (probedata_t *)m_pData;
	}

	float GetWeight() {
		return GetProbeData()->Weight;
	}

	float GetQuality() {
		return GetProbeData()->Quality;
	}

	long GetValue() {
		return GetProbeData()->Value;
	}

	long GetUses() {
		return GetProbeData()->Uses;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetProbeData()->Weight = Value;
	}

	void SetQuality(const float Value) {
		GetProbeData()->Quality = Value;
	}

	void SetValue(const long Value) {
		GetProbeData()->Value = Value;
	}

	void SetUses(const long Value) {
		GetProbeData()->Uses = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
