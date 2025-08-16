/*===========================================================================
 *
 * File:    EsmsubLHDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBLHDT_H
#define __ESMSUBLHDT_H


#include "EsmSubBase.h"


/* Light flags */
#define MWESM_LIGHTFLAG_DYNAMIC       0x0001
#define MWESM_LIGHTFLAG_CANCARRY      0x0002
#define MWESM_LIGHTFLAG_NEGATIVE      0x0004
#define MWESM_LIGHTFLAG_FLICKER       0x0008
#define MWESM_LIGHTFLAG_ISFIRE        0x0010
#define MWESM_LIGHTFLAG_DEFAULTOFF    0x0020
#define MWESM_LIGHTFLAG_FLICKERSLOW   0x0040
#define MWESM_LIGHTFLAG_PULSE         0x0080
#define MWESM_LIGHTFLAG_PULSESLOW     0x0100
#define MWESM_LIGHTFLAG_FLICKERALL    0x01C8


#pragma pack(push, 1)

typedef struct {
	float Weight;
	long Value;
	long Time;
	long Radius;
	union {
		struct {
			byte Red;
			byte Green;
			byte Blue;
			byte Null;
		};

		long ColorRef;
	};

	long Flags;
} lightdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubLHDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubLHDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubLHDT();
	//virtual ~CEsmSubLHDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubLHDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(lightdata_t));
		m_RecordSize = sizeof(lightdata_t);
		memset(m_pData, 0, sizeof(lightdata_t));

		GetLightData()->Red = 192;
		GetLightData()->Green = 128;
		GetLightData()->Blue = 64;
	}

	/* Get class members */
	lightdata_t *GetLightData() {
		return (lightdata_t *)m_pData;
	}

	float GetWeight() {
		return GetLightData()->Weight;
	}

	long GetValue() {
		return GetLightData()->Value;
	}

	long GetTime() {
		return GetLightData()->Time;
	}

	long GetRadius() {
		return GetLightData()->Radius;
	}

	long GetColorRef() {
		return GetLightData()->ColorRef;
	}

	byte GetColorRed() {
		return GetLightData()->Red;
	}

	byte GetColorGreen() {
		return GetLightData()->Green;
	}

	byte GetColorBlue() {
		return GetLightData()->Blue;
	}

	long GetFlags() {
		return GetLightData()->Flags;
	}

	bool IsDynamic() {
		return (GetFlags() & MWESM_LIGHTFLAG_DYNAMIC) != 0;
	}

	bool IsCanCarry() {
		return (GetFlags() & MWESM_LIGHTFLAG_CANCARRY) != 0;
	}

	bool IsNegative() {
		return (GetFlags() & MWESM_LIGHTFLAG_NEGATIVE) != 0;
	}

	bool IsFlicker() {
		return (GetFlags() & MWESM_LIGHTFLAG_FLICKER) != 0;
	}

	bool IsFire() {
		return (GetFlags() & MWESM_LIGHTFLAG_ISFIRE) != 0;
	}

	bool IsDefaultOff() {
		return (GetFlags() & MWESM_LIGHTFLAG_DEFAULTOFF) != 0;
	}

	bool IsFlickerSlow() {
		return (GetFlags() & MWESM_LIGHTFLAG_FLICKERSLOW) != 0;
	}

	bool IsPulse() {
		return (GetFlags() & MWESM_LIGHTFLAG_PULSE) != 0;
	}

	bool IsPulseSlow() {
		return (GetFlags() & MWESM_LIGHTFLAG_PULSESLOW) != 0;
	}

	bool IsFlickerAll() {
		return (GetFlags() & MWESM_LIGHTFLAG_FLICKERALL) != 0;
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetLightData()->Flags |= Flag;
		} else {
			GetLightData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetLightData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetLightData()->Value = Value;
	}

	void SetTime(const long Value) {
		GetLightData()->Time = Value;
	}

	void SetRadius(const long Value) {
		GetLightData()->Radius = Value;
	}

	void SetColorRef(const long Value) {
		GetLightData()->ColorRef = Value;
	}

	void SetColorRed(const byte Value) {
		GetLightData()->Red = Value;
	}

	void SetColorGreen(const byte Value) {
		GetLightData()->Green = Value;
	}

	void SetColorBlue(const byte Value) {
		GetLightData()->Blue = Value;
	}

	void SetColor(const byte R, const byte G, const byte B) {
		GetLightData()->Red = R;
		GetLightData()->Green = G;
		GetLightData()->Blue = B;
	}

	void SetDynamic(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_DYNAMIC, Flag);
	}

	void SetCanCarry(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_CANCARRY, Flag);
	}

	void SetNegative(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_NEGATIVE, Flag);
	}

	void SetFlicker(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_FLICKER, Flag);
	}

	void SetFire(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_ISFIRE, Flag);
	}

	void SetDefaultOff(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_DEFAULTOFF, Flag);
	}

	void SetFlickerSlow(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_FLICKERSLOW, Flag);
	}

	void SetPulse(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_PULSE, Flag);
	}

	void SetPulseSlow(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_PULSESLOW, Flag);
	}

	void SetFlickerAll(const bool Flag) {
		SetFlag(MWESM_LIGHTFLAG_FLICKERALL, Flag);
	}
};


#endif
