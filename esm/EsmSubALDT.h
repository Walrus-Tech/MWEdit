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
	long AutoCalc;
} alchemydata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubALDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubALDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubALDT() {}
	//virtual ~CEsmSubALDT() { Destroy(); }
	//virtual void Destroy (void) { }

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubALDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(alchemydata_t));
		m_RecordSize = sizeof(alchemydata_t);
		memset(m_pData, 0, sizeof(alchemydata_t));
	}

	/* Get class members */
	alchemydata_t *GetAlchemyData(void) {
		return ((alchemydata_t *)m_pData);
	}

	float GetWeight(void) {
		return (GetAlchemyData()->Weight);
	}

	long GetValue(void) {
		return (GetAlchemyData()->Value);
	}

	bool IsAutoCalc(void) {
		return (GetAlchemyData()->AutoCalc != 0);
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

/*===========================================================================
 *      End of Class CEsmSubALDT Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Esmsubaldt.H
 *=========================================================================*/
