/*===========================================================================
 *
 * File:    EsmsubMEDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBMEDT_H
#define __ESMSUBMEDT_H


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

/* Magic effect flags */
#define MWESM_EFFECTFLAG_SPELLMAKING 0x0200
#define MWESM_EFFECTFLAG_ENCHANTING  0x0400
#define MWESM_EFFECTFLAG_NEGATIVE    0x0800

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
	long SpellSchool;
	float BaseCost;
	long Flags;
	long Red;
	long Green;
	long Blue;
	float SpeedX;
	float SizeX;
	float SizeCap;
} magiceffectdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubMEDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubMEDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubMEDT();
	//virtual ~CEsmSubMEDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubMEDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(magiceffectdata_t));
		m_RecordSize = sizeof(magiceffectdata_t);
		memset(m_pData, 0, sizeof(magiceffectdata_t));
		GetEffectData()->Red = 128;
		GetEffectData()->Blue = 128;
		GetEffectData()->Green = 128;
		GetEffectData()->SizeX = 1.0;
		GetEffectData()->SpeedX = 1.0;
		GetEffectData()->SizeCap = 1.0;
		GetEffectData()->BaseCost = 1.0;
	}

	/* Get class members */
	magiceffectdata_t *GetEffectData(void) {
		return ((magiceffectdata_t *)m_pData);
	}

	long GetSpellSchool(void) {
		return (GetEffectData()->SpellSchool);
	}

	float GetBaseCost(void) {
		return (GetEffectData()->BaseCost);
	}

	long GetFlags(void) {
		return (GetEffectData()->Flags);
	}

	long GetRed(void) {
		return (GetEffectData()->Red);
	}

	long GetGreen(void) {
		return (GetEffectData()->Green);
	}

	long GetBlue(void) {
		return (GetEffectData()->Blue);
	}

	float GetSpeedX(void) {
		return (GetEffectData()->SpeedX);
	}

	float GetSizeX(void) {
		return (GetEffectData()->SizeX);
	}

	float GetSizeCap(void) {
		return (GetEffectData()->SizeCap);
	}

	bool IsSpellMaking(void) {
		return ((GetFlags() & MWESM_EFFECTFLAG_SPELLMAKING) != 0);
	}

	bool IsEnchanting(void) {
		return ((GetFlags() & MWESM_EFFECTFLAG_ENCHANTING) != 0);
	}

	bool IsNegative(void) {
		return ((GetFlags() & MWESM_EFFECTFLAG_NEGATIVE) != 0);
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetEffectData()->Flags |= Flag;
		} else {
			GetEffectData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetSpellSchool(const long Value) {
		GetEffectData()->SpellSchool = Value;
	}

	void SetBaseCost(const float Value) {
		GetEffectData()->BaseCost = Value;
	}

	void SetSpeedX(const float Value) {
		GetEffectData()->SpeedX = Value;
	}

	void SetSizeX(const float Value) {
		GetEffectData()->SizeX = Value;
	}

	void SetSizeCap(const float Value) {
		GetEffectData()->SizeCap = Value;
	}

	void SetRed(const byte Value) {
		GetEffectData()->Red = (long)(ulong)Value;
	}

	void SetGreen(const byte Value) {
		GetEffectData()->Green = (long)(ulong)Value;
	}

	void SetBlue(const byte Value) {
		GetEffectData()->Blue = (long)(ulong)Value;
	}

	void SetColor(const byte R, const byte G, const byte B) {
		SetRed(R);
		SetGreen(G);
		SetBlue(B);
	}

	void SetSpellMaking(const bool Flag) {
		SetFlag(MWESM_EFFECTFLAG_SPELLMAKING, Flag);
	}

	void SetEnchanting(const bool Flag) {
		SetFlag(MWESM_EFFECTFLAG_ENCHANTING, Flag);
	}

	void SetNegative(const bool Flag) {
		SetFlag(MWESM_EFFECTFLAG_NEGATIVE, Flag);
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
