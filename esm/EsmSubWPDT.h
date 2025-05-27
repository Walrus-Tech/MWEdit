/*===========================================================================
 *
 * File:    EsmsubWPDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBWPDT_H
#define __ESMSUBWPDT_H


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

/* Armor types */
#define MWESM_WEAPONTYPE_MIN          0
#define MWESM_WEAPONTYPE_SHORT        0
#define MWESM_WEAPONTYPE_LONG         1
#define MWESM_WEAPONTYPE_LONG2HAND    2
#define MWESM_WEAPONTYPE_BLUNT        3
#define MWESM_WEAPONTYPE_BLUNT2CLOSE  4
#define MWESM_WEAPONTYPE_BLUNT2WIDE   5
#define MWESM_WEAPONTYPE_SPEAR        6
#define MWESM_WEAPONTYPE_AXE          7
#define MWESM_WEAPONTYPE_AXE2HAND     8
#define MWESM_WEAPONTYPE_BOW          9
#define MWESM_WEAPONTYPE_CROSSBOW    10
#define MWESM_WEAPONTYPE_THROWN      11
#define MWESM_WEAPONTYPE_ARROW       12
#define MWESM_WEAPONTYPE_BOLT        13
#define MWESM_WEAPONTYPE_MAX         13

/* Weapon flags */
#define MWESM_WEAPONFLAG_IGNORERESIST 1

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
	short Type;
	short Health;
	float Speed;
	float Reach;
	short EnchantPts;
	byte ChopMin;
	byte ChopMax;
	byte SlashMin;
	byte SlashMax;
	byte ThrustMin;
	byte ThrustMax;
	long Flags;
} weapondata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubWPDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubWPDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubWPDT();
	//virtual ~CEsmSubWPDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubWPDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(weapondata_t));
		m_RecordSize = sizeof(weapondata_t);
		memset(m_pData, 0, sizeof(weapondata_t));
	}

	/* Get class members */
	weapondata_t *GetWeaponData(void) {
		return ((weapondata_t *)m_pData);
	}

	float GetWeight(void) {
		return (GetWeaponData()->Weight);
	}

	long GetValue(void) {
		return (GetWeaponData()->Value);
	}

	short GetWeaponType(void) {
		return (GetWeaponData()->Type);
	}

	short GetEnchantPts(void) {
		return (GetWeaponData()->EnchantPts);
	}

	short GetHealth(void) {
		return (GetWeaponData()->Health);
	}

	float GetSpeed(void) {
		return (GetWeaponData()->Speed);
	}

	float GetReach(void) {
		return (GetWeaponData()->Reach);
	}

	long GetFlags(void) {
		return (GetWeaponData()->Flags);
	}

	byte GetChopMin(void) {
		return (GetWeaponData()->ChopMin);
	}

	byte GetChopMax(void) {
		return (GetWeaponData()->ChopMax);
	}

	byte GetSlashMin(void) {
		return (GetWeaponData()->SlashMin);
	}

	byte GetSlashMax(void) {
		return (GetWeaponData()->SlashMax);
	}

	byte GetThrustMin(void) {
		return (GetWeaponData()->ThrustMin);
	}

	byte GetThrustMax(void) {
		return (GetWeaponData()->ThrustMax);
	}

	bool IsIgnoreResist(void) {
		return ((GetFlags() & MWESM_WEAPONFLAG_IGNORERESIST) != 0);
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetWeaponData()->Flags |= Flag;
		} else {
			GetWeaponData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetWeaponType(const short Value) {
		if (Value >= MWESM_WEAPONTYPE_MIN && Value <= MWESM_WEAPONTYPE_MAX) {
			GetWeaponData()->Type = Value;
		}
	}

	void SetWeight(const float Value) {
		GetWeaponData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetWeaponData()->Value = Value;
	}

	void SetEnchantPts(const short Value) {
		GetWeaponData()->EnchantPts = Value;
	}

	void SetHealth(const short Value) {
		GetWeaponData()->Health = Value;
	}

	void SetSpeed(const float Value) {
		GetWeaponData()->Speed = Value;
	}

	void SetReach(const float Value) {
		GetWeaponData()->Reach = Value;
	}

	void SetChopMin(const byte Value) {
		GetWeaponData()->ChopMin = Value;
	}

	void SetChopMax(const byte Value) {
		GetWeaponData()->ChopMax = Value;
	}

	void SetSlashMin(const byte Value) {
		GetWeaponData()->SlashMin = Value;
	}

	void SetSlashMax(const byte Value) {
		GetWeaponData()->SlashMax = Value;
	}

	void SetThrustMin(const byte Value) {
		GetWeaponData()->ThrustMin = Value;
	}

	void SetThrustMax(const byte Value) {
		GetWeaponData()->ThrustMax = Value;
	}

	void SetIgnoreResist(const bool Value) {
		SetFlag(MWESM_WEAPONFLAG_IGNORERESIST, Value);
	}

};

/*===========================================================================
 *      End of Class CEsmSubWPDT Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Esmsubwpdt.H
 *=========================================================================*/
