/*===========================================================================
 *
 * File:    EsmsubENDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBENDT_H
#define __ESMSUBENDT_H


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

/* Enchant types */
#define MWESM_ENCHTYPE_MIN            0
#define MWESM_ENCHTYPE_CASTONCE       0
#define MWESM_ENCHTYPE_CASTUSED       1
#define MWESM_ENCHTYPE_CASTSTRIKES    2
#define MWESM_ENCHTYPE_CONSTANT       3
#define MWESM_ENCHTYPE_MAX            3

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
	long Type;
	long EnchantCost;
	long Charge;
	long AutoCalc;
} enchantdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubENDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubENDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubENDT();
	//virtual ~CEsmSubENDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubENDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(enchantdata_t));
		m_RecordSize = sizeof(enchantdata_t);
		memset(m_pData, 0, sizeof(enchantdata_t));
		GetEnchantData()->AutoCalc = 1;
	}

	/* Get class members */
	enchantdata_t *GetEnchantData(void) {
		return (enchantdata_t *)m_pData;
	}

	long GetEnchantType(void) {
		return (GetEnchantData()->Type);
	}

	long GetEnchantCost(void) {
		return (GetEnchantData()->EnchantCost);
	}

	long GetCharge(void) {
		return (GetEnchantData()->Charge);
	}

	bool IsAutoCalc(void) {
		return (GetEnchantData()->AutoCalc != 0);
	}

	/* Set class members */
	void SetEnchantType(const long Value) {
		if (Value >= MWESM_ENCHTYPE_MIN && Value <= MWESM_ENCHTYPE_MAX) {
			GetEnchantData()->Type = Value;
		}
	}

	void SetEnchantCost(const long Value) {
		GetEnchantData()->EnchantCost = Value;
	}

	void SetCharge(const long Value) {
		GetEnchantData()->Charge = Value;
	}

	void SetAutoCalc(const bool Flag) {
		GetEnchantData()->AutoCalc = Flag ? 1 : 0;
	}

};

/*===========================================================================
 *      End of Class CEsmSubENDT Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File EsmsubENDT.H
 *=========================================================================*/
