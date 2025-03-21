/*===========================================================================
 *
 * File:    EsmsubAI_F.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAI_F_H
#define __ESMSUBAI_F_H


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
	float X;
	float Y;
	float Z;
	short Duration;
	char ID[32];
	short Unknown;
} ai_fdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubAI_F Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAI_F : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubAI_F();
	//virtual ~CEsmSubAI_F() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAI_F);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ai_fdata_t));
		m_RecordSize = sizeof(ai_fdata_t);
		memset(m_pData, 0, sizeof(ai_fdata_t));
	}

	/* Get class methods */
	ai_fdata_t *GetAIData (void) {
		return ((ai_fdata_t *) m_pData);
	}

	float GetXPos (void) {
		return (GetAIData()->X);
	}

	float GetYPos (void) {
		return (GetAIData()->Y);
	}

	float GetZPos (void) {
		return (GetAIData()->Z);
	}

	short GetDuration (void) {
		return (GetAIData()->Duration);
	}

	short GetUnknown (void) {
		return (GetAIData()->Unknown);
	}

	const TCHAR *GetID (void) {
		return (GetAIData()->ID);
	}

	/* Set class members */
	void SetXPos (const float Value) {
		GetAIData()->X = Value;
	}

	void SetYPos (const float Value) {
		GetAIData()->Y = Value;
	}

	void SetZPos (const float Value) {
		GetAIData()->Z = Value;
	}

	void SetDuration (const short Value) {
		GetAIData()->Duration = Value;
	}

	void SetUnknown (const short Value) {
		GetAIData()->Unknown = Value;
	}

	void SetID (const TCHAR* pString) {
		TSTRNCPY(GetAIData()->ID, pString, 32);
	}

};

/*===========================================================================
 *      End of Class CEsmSubAI_F Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubAI_A.H
 *=========================================================================*/
