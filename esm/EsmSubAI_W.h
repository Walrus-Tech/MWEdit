/*===========================================================================
 *
 * File:    EsmsubAI_W.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAI_W_H
#define __ESMSUBAI_W_H


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
#define MWESM_AIW_NUMIDLES 8
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
	short Distance;
	short Duration;
	byte TimeOfDay;
	byte Idle[MWESM_AIW_NUMIDLES];
	byte Unknown;
} ai_wdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubAI_W Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAI_W : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubAI_W();
	//virtual ~CEsmSubAI_W() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAI_W);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ai_wdata_t));
		m_RecordSize = sizeof(ai_wdata_t);
		memset(m_pData, 0, sizeof(ai_wdata_t));
		GetAIData()->Unknown = 1;
	}

	/* Get class members */
	ai_wdata_t *GetAIData() {
		return (ai_wdata_t *)m_pData;
	}

	short GetDistance() {
		return GetAIData()->Distance;
	}

	short GetDuration() {
		return GetAIData()->Duration;
	}

	byte GetTimeOfDay() {
		return GetAIData()->TimeOfDay;
	}

	byte GetUnknown() {
		return GetAIData()->Unknown;
	}

	byte GetIdle(const int Index) {
		return IsValidIndex(Index) ? GetAIData()->Idle[Index] : 0;
	}

	bool IsValidIndex(const int Index) {
		return Index >= 0 && Index < MWESM_AIW_NUMIDLES;
	}

	/* Set class members */
	void SetDistance(const short Value) {
		GetAIData()->Distance = Value;
	}

	void SetDuration(const short Value) {
		GetAIData()->Duration = Value;
	}

	void SetTimeOfDay(const byte Value) {
		GetAIData()->TimeOfDay = Value;
	}

	void SetUnknown(const byte Value) {
		GetAIData()->Unknown = Value;
	}

	void SetIdle(const int Index, const byte Value) {
		if (IsValidIndex(Index)) {
			GetAIData()->Idle[Index] = Value;
		}
	}
};

/*===========================================================================
 *      End of Class CEsmSubAI_W Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubAI_A.H
 *=========================================================================*/
