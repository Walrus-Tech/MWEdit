/*===========================================================================
 *
 * File:    EsmsubMCDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBMCDT_H
#define __ESMSUBMCDT_H


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
	long Unknown;
} miscdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubMCDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubMCDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubMCDT();
	//virtual ~CEsmSubMCDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubMCDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(miscdata_t));
		m_RecordSize = sizeof(miscdata_t);
		memset(m_pData, 0, sizeof(miscdata_t));
	}

	/* Get class members */
	miscdata_t *GetMiscData() {
		return (miscdata_t *)m_pData;
	}

	float GetWeight() {
		return GetMiscData()->Weight;
	}

	long GetValue() {
		return GetMiscData()->Value;
	}

	long GetUnknown() {
		return GetMiscData()->Unknown;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetMiscData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetMiscData()->Value = Value;
	}

	void SetUnknown(const long Value) {
		GetMiscData()->Unknown = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
