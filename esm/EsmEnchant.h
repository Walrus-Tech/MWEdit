/*===========================================================================
 *
 * File:    EsmEnchant.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMENCHANT_H
#define __ESMENCHANT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubENDT.h"
#include "EsmSubENAM.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Number of effects allowed per enchantment */
#define MWESM_ENCHANT_NUMENCHANTS 8

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
const TCHAR *GetESMEnchantType (const int Type);
int GetESMEnchantType (const TCHAR* pString);
bool GetESMEnchantType (int &OutType, const TCHAR* pString);
const TCHAR *GetESMEnchantRangeType (const int Type);
int GetESMEnchantRangeType (const TCHAR* pString);
bool GetESMEnchantRangeType (int &OutType, const TCHAR* pString);
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmEnchant Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmEnchant : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubENDT *m_pEnchantData;     /* Reference to sub-records */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmEnchant();
	//virtual ~CEsmEnchant() { Destroy(); }
	virtual void Destroy (void);

	/* Compare two fields of the record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("Enchant");
	}

	/* Get class members */
	const TCHAR *GetEnchantType (void) {
		return (GetESMEnchantType(GetEnchantTypeID()));
	}

	int GetEnchantTypeID (void) {
		return (m_pEnchantData ? m_pEnchantData->GetEnchantType() : 0);
	}

	enchantdata_t *GetEnchantData (void) {
		return (m_pEnchantData ? m_pEnchantData->GetEnchantData() : NULL);
	}

	long GetEnchantCost (void) {
		return (m_pEnchantData ? m_pEnchantData->GetEnchantCost() : 0);
	}

	long GetCharge (void) {
		return (m_pEnchantData ? m_pEnchantData->GetCharge() : 0);
	}

	bool IsAutoCalc (void) {
		return (m_pEnchantData ? m_pEnchantData->IsAutoCalc() : false);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetEnchantType (const int Type) {
		if (m_pEnchantData) {
			m_pEnchantData->SetEnchantType(Type);
		}
	}

	void SetAutoCalc (const bool Flag) {
		if (m_pEnchantData) {
			m_pEnchantData->SetAutoCalc(Flag);
		}
	}

	void SetEnchantCost (const int Value) {
		if (m_pEnchantData) {
			m_pEnchantData->SetEnchantCost(Value);
		}
	}

	void SetCharge (const int Value) {
		if (m_pEnchantData) {
			m_pEnchantData->SetCharge(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);

};

/*===========================================================================
 *      End of Class CEsmEnchant Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/
