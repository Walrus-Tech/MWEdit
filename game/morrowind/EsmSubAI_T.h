/*===========================================================================
 *
 * File:    EsmsubAI_T.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAI_T_H
#define __ESMSUBAI_T_H


#include "esm/EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	float X;
	float Y;
	float Z;
	long Unknown;
} ai_tdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubAI_T Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAI_T : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubAI_T();
	//virtual ~CEsmSubAI_T() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAI_T);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ai_tdata_t));
		m_RecordSize = sizeof(ai_tdata_t);
		memset(m_pData, 0, sizeof(ai_tdata_t));
		GetAIData()->Unknown = 1;
	}

	/* Get class methods */
	ai_tdata_t *GetAIData() {
		return (ai_tdata_t *) m_pData;
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

	long GetUnknown() {
		return GetAIData()->Unknown;
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

	void SetUnknown(const long Value) {
		GetAIData()->Unknown = Value;
	}
};


#endif
