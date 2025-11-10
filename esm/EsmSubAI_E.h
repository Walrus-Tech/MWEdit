/*===========================================================================
 *
 * File:    EsmsubAI_E.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAI_E_H
#define __ESMSUBAI_E_H


#include <float.h>

#include "esm/EsmSubBase.h"



#pragma pack(push, 1)

typedef struct {
	float X;
	float Y;
	float Z;
	short Duration;
	char ID[32];
	short Unknown;
} ai_edata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubAI_E Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAI_E : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubAI_E();
	//virtual ~CEsmSubAI_E() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAI_E);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ai_edata_t));
		m_RecordSize = sizeof(ai_edata_t);
		memset(m_pData, 0, sizeof(ai_edata_t));
		GetAIData()->X = FLT_MAX;
		GetAIData()->Y = FLT_MAX;
		GetAIData()->Z = FLT_MAX;
		GetAIData()->Unknown = 1;
	}

	/* Get class methods */
	ai_edata_t *GetAIData() {
		return (ai_edata_t *)m_pData;
	}

	float GetXPos() {
		return GetAIData()->X;
	}

	float GetYPos() {
		return GetAIData()->Y;
	}

	float GetZPos() {
		return GetAIData()->Z;
	}

	short GetDuration() {
		return GetAIData()->Duration;
	}

	short GetUnknown() {
		return GetAIData()->Unknown;
	}

	const TCHAR *GetID() {
		return GetAIData()->ID;
	}

	/* Set class members */
	void SetXPos(const float Value) {
		GetAIData()->X = Value;
	}

	void SetYPos(const float Value) {
		GetAIData()->Y = Value;
	}

	void SetZPos(const float Value) {
		GetAIData()->Z = Value;
	}

	void SetDuration(const short Value) {
		GetAIData()->Duration = Value;
	}

	void SetUnknown(const short Value) {
		GetAIData()->Unknown = Value;
	}

	void SetID(const TCHAR *pString) {
		TSTRNCPY(GetAIData()->ID, pString, 32);
	}
};


#endif
