/*===========================================================================
 *
 * File:    EsmWeapon.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMWEAPON_H
#define __ESMWEAPON_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem3.h"
#include "EsmSubWPDT.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
const TCHAR *GetESMWeaponType(const int Type);
int GetESMWeaponType(const TCHAR *pString);
bool IsESMWeaponRange(const int Type);
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmWeapon Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmWeapon : public CEsmItem3 {
	DECLARE_SUBRECCREATE();


	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubWPDT *m_pWeaponData; /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmWeapon();
	//virtual ~CEsmWeapon() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Weapon");
	}

	/* Get class members */
	weapondata_t *GetWeaponData(void) {
		return (m_pWeaponData == NULL ? NULL : m_pWeaponData->GetWeaponData());
	}

	const TCHAR *GetWeaponType(void) {
		return GetESMWeaponType(GetWeaponTypeID());
	}

	int GetWeaponTypeID(void) {
		return (m_pWeaponData ? GetWeaponData()->Type : 0);
	}

	virtual float GetWeight(void) {
		return (m_pWeaponData ? GetWeaponData()->Weight : 0);
	}

	virtual long GetValue(void) {
		return (m_pWeaponData ? GetWeaponData()->Value : 0);
	}

	virtual long GetEnchantPts(void) {
		return (m_pWeaponData ? GetWeaponData()->EnchantPts : 0);
	}

	long GetFlags(void) {
		return (m_pWeaponData ? GetWeaponData()->Flags : 0);
	}

	int GetHealth(void) {
		return (m_pWeaponData ? GetWeaponData()->Health : 0);
	}

	float GetSpeed(void) {
		return (m_pWeaponData ? GetWeaponData()->Speed : 0);
	}

	float GetReach(void) {
		return (m_pWeaponData ? GetWeaponData()->Reach : 0);
	}

	int GetChopMin(void) {
		return (m_pWeaponData ? GetWeaponData()->ChopMin : 0);
	}

	int GetChopMax(void) {
		return (m_pWeaponData ? GetWeaponData()->ChopMax : 0);
	}

	int GetSlashMin(void) {
		return (m_pWeaponData ? GetWeaponData()->SlashMin : 0);
	}

	int GetSlashMax(void) {
		return (m_pWeaponData ? GetWeaponData()->SlashMax : 0);
	}

	int GetThrustMin(void) {
		return (m_pWeaponData ? GetWeaponData()->ThrustMin : 0);
	}

	int GetThrustMax(void) {
		return (m_pWeaponData ? GetWeaponData()->ThrustMax : 0);
	}

	bool IsIgnoreResist(void) {
		return (GetFlags() & MWESM_WEAPONFLAG_IGNORERESIST) != 0;
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (GetWeaponData() != NULL) {
			GetWeaponData()->Weight = Weight;
		}
	}

	virtual void SetValue(const long Value) {
		if (GetWeaponData() != NULL) {
			GetWeaponData()->Value = Value;
		}
	}

	virtual void SetEnchantPts(const long Points) {
		if (GetWeaponData() != NULL) {
			GetWeaponData()->EnchantPts = Points & 0xFFFF;
		}
	}

	void SetIgnoreResist(const bool Flag) {
		if (GetWeaponData() == NULL) {
			return;
		}

		if (Flag) {
			GetWeaponData()->Flags |= MWESM_WEAPONFLAG_IGNORERESIST;
		} else {
			GetWeaponData()->Flags &= ~MWESM_WEAPONFLAG_IGNORERESIST;
		}
	}

	void SetChopMin(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->ChopMin = Value;
		}
	}

	void SetChopMax(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->ChopMax = Value;
		}
	}

	void SetSlashMin(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->SlashMin = Value;
		}
	}

	void SetSlashMax(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->SlashMax = Value;
		}
	}

	void SetThrustMin(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->ThrustMin = Value;
		}
	}

	void SetThrustMax(const byte Value) {
		if (GetWeaponData()) {
			GetWeaponData()->ThrustMax = Value;
		}
	}

	void SetSpeed(const float Value) {
		if (GetWeaponData()) {
			GetWeaponData()->Speed = Value;
		}
	}

	void SetReach(const float Value) {
		if (GetWeaponData()) {
			GetWeaponData()->Reach = Value;
		}
	}

	void SetHealth(const int Value) {
		if (GetWeaponData()) {
			GetWeaponData()->Health = Value;
		}
	}

	void SetWeaponType(const int Type) {
		if (GetWeaponData() && Type >= MWESM_WEAPONTYPE_MIN && Type <= MWESM_WEAPONTYPE_MAX) {
			GetWeaponData()->Type = Type;
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmWeapon Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
