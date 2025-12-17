/*===========================================================================
 *
 * File:    EsmLight.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMLIGHT_H
#define __ESMLIGHT_H


#include "esm/EsmItem2.h"
#include "esm/EsmSubLHDT.h"


const TCHAR *GetESMLightFlicker(const int Flags);


/*===========================================================================
 *
 * Begin Class CEsmLight Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmLight : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubLHDT *m_pLightData;   /* Reference to subrecords */
	CEsmSubNameFix *m_pSound;


  public:
	/* Class Constructors/Destructors */
	CEsmLight();
	//virtual ~CEsmLight() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Light");
	}

	/* Get class members */
	lightdata_t *GetLightData(void) {
		return (m_pLightData == NULL ? NULL : m_pLightData->GetLightData());
	}

	const TCHAR *GetSound(void) {
		return (m_pSound ? m_pSound->GetName() : _T(""));
	}

	virtual float GetWeight(void) {
		return (m_pLightData ? m_pLightData->GetWeight() : 0);
	}

	virtual long GetValue(void) {
		return (m_pLightData ? m_pLightData->GetValue() : 0);
	}

	long GetTime(void) {
		return (m_pLightData ? m_pLightData->GetTime() : 0);
	}

	long GetRadius(void) {
		return (m_pLightData ? m_pLightData->GetRadius() : 0);
	}

	long GetColor(void) {
		return (m_pLightData ? m_pLightData->GetColorRef() : 0);
	}

	long GetFlags(void) {
		return (m_pLightData ? m_pLightData->GetFlags() : 0);
	}

	byte GetRed(void) {
		return (m_pLightData ? m_pLightData->GetColorRed() : 0);
	}

	byte GetGreen(void) {
		return (m_pLightData ? m_pLightData->GetColorGreen() : 0);
	}

	byte GetBlue(void) {
		return (m_pLightData ? m_pLightData->GetColorBlue() : 0);
	}

	bool IsDynamic(void) {
		return (m_pLightData ? m_pLightData->IsDynamic() : false);
	}

	bool IsCanCarry(void) {
		return (m_pLightData ? m_pLightData->IsCanCarry() : false);
	}

	bool IsNegative(void) {
		return (m_pLightData ? m_pLightData->IsNegative() : false);
	}

	bool IsFlicker(void) {
		return (m_pLightData ? m_pLightData->IsFlicker() : false);
	}

	bool IsFire(void) {
		return (m_pLightData ? m_pLightData->IsFire() : false);
	}

	bool IsDefaultOff(void) {
		return (m_pLightData ? m_pLightData->IsDefaultOff() : false);
	}

	bool IsFlickerSlow(void) {
		return (m_pLightData ? m_pLightData->IsFlickerSlow() : false);
	}

	bool IsPulse(void) {
		return (m_pLightData ? m_pLightData->IsPulse() : false);
	}

	bool IsPulseSlow(void) {
		return (m_pLightData ? m_pLightData->IsPulseSlow() : false);
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetIcon(const TCHAR *pString);
	void SetName(const TCHAR *pString);
	void SetSound(const TCHAR *pString);
	void SetRadius(const long Value) {
		if (m_pLightData) {
			m_pLightData->SetRadius(Value);
		}
	}

	void SetTime(const long Value) {
		if (m_pLightData) {
			m_pLightData->SetTime(Value);
		}
	}

	void SetRed(const byte Value) {
		if (m_pLightData) {
			m_pLightData->SetColorRed(Value);
		}
	}

	void SetBlue(const byte Value) {
		if (m_pLightData) {
			m_pLightData->SetColorBlue(Value);
		}
	}

	void SetGreen(const byte Value) {
		if (m_pLightData) {
			m_pLightData->SetColorGreen(Value);
		}
	}

	void SetColor(const byte R, const byte G, const byte B) {
		if (m_pLightData) {
			m_pLightData->SetColor(R, G, B);
		}
	}

	void SetDynamic(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetDynamic(Flag);
		}
	}

	void SetCanCarry(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetCanCarry(Flag);
		}
	}

	void SetNegative(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetNegative(Flag);
		}
	}

	void SetFlicker(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetFlicker(Flag);
		}
	}

	void SetFire(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetFire(Flag);
		}
	}

	void SetDefaultOff(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetDefaultOff(Flag);
		}
	}

	void SetFlickerSlow(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetFlickerSlow(Flag);
		}
	}

	void SetPulse(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetPulse(Flag);
		}
	}

	void SetPulseSlow(const bool Flag) {
		if (m_pLightData) {
			m_pLightData->SetPulseSlow(Flag);
		}
	}

	virtual void SetWeight(const float Weight) {
		if (m_pLightData) {
			m_pLightData->SetWeight(Weight);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pLightData) {
			m_pLightData->SetValue(Value);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};


#endif
