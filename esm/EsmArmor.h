/*===========================================================================
 *
 * File:    Esmarmor.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMARMOR_H
#define __ESMARMOR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem3.h"
#include "EsmSubAODT.h"
#include "EsmSubByte.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Number of body part definitions allowed in an armor record */
#define MWESM_ARMOR_MAXBODYPARTS 7

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmArmor Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmArmor : public CEsmItem3 {
	DECLARE_SUBRECCREATE();


	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubAODT *m_pArmorData; /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmArmor();
	//virtual ~CEsmArmor() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Armor");
	}

	/* Get class members */
	armordata_t *GetArmorData() {
		return m_pArmorData == NULL ? NULL : m_pArmorData->GetArmorData();
	}

	const TCHAR *GetArmorType();
	int GetArmorTypeID() {
		return m_pArmorData == NULL ? -1 : m_pArmorData->GetArmorType();
	}

	virtual float GetWeight() {
		return m_pArmorData == NULL ? 0 : m_pArmorData->GetWeight();
	}

	virtual long GetValue() {
		return m_pArmorData == NULL ? 0 : m_pArmorData->GetValue();
	}

	virtual long GetEnchantPts() {
		return m_pArmorData == NULL ? 0 : m_pArmorData->GetEnchantPts();
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetWeight(Weight);
		}
	}

	virtual void SetEnchantPts(const long Points) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetEnchantPts(Points);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetValue(Value);
		}
	}

	void SetArmorType(const int Type) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetArmorType(Type);
		}
	}

	void SetArmorRating(const int Rating) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetRating(Rating);
		}
	}

	void SetArmorHealth(const int Health) {
		if (m_pArmorData != NULL) {
			m_pArmorData->SetHealth(Health);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmArmor Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Convert an armor type to a string */
const TCHAR *GetESMArmorType(const int ArmorType);
int GetESMArmorType(const TCHAR *pString);
bool GetESMArmorType(int &OutIndex, const TCHAR *pString);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
