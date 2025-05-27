/*===========================================================================
 *
 * File:    EsmsubIRDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBIRDT_H
#define __ESMSUBIRDTXH


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

/* Number of effects per ingrediant */
#define MWESM_INGRE_NUMEFFECTS 4

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
	long EffectID[MWESM_INGRE_NUMEFFECTS];
	long SkillID[MWESM_INGRE_NUMEFFECTS];
	long AttributeID[MWESM_INGRE_NUMEFFECTS];
} ingredata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubIRDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubIRDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubIRDT();
	//virtual ~CEsmSubIRDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubIRDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ingredata_t));
		m_RecordSize = sizeof(ingredata_t);
		memset(m_pData, 0, sizeof(ingredata_t));
		GetIngreData()->EffectID[0] = -1;
		GetIngreData()->EffectID[1] = -1;
		GetIngreData()->EffectID[2] = -1;
		GetIngreData()->EffectID[3] = -1;
		GetIngreData()->SkillID[0] = -1;
		GetIngreData()->SkillID[1] = -1;
		GetIngreData()->SkillID[2] = -1;
		GetIngreData()->SkillID[3] = -1;
		GetIngreData()->AttributeID[0] = -1;
		GetIngreData()->AttributeID[1] = -1;
		GetIngreData()->AttributeID[2] = -1;
		GetIngreData()->AttributeID[3] = -1;
	}

	/* Get class members */
	ingredata_t *GetIngreData(void) {
		return ((ingredata_t *)m_pData);
	}

	float GetWeight(void) {
		return (GetIngreData()->Weight);
	}

	long GetValue(void) {
		return (GetIngreData()->Value);
	}

	bool IsValidEffect(const int Index) {
		return (Index >= 0 && Index < MWESM_INGRE_NUMEFFECTS);
	}

	long GetEffectID(const int Index) {
		return (IsValidEffect(Index) ? GetIngreData()->EffectID[Index] : 0);
	}

	long GetSkillID(const int Index) {
		return (IsValidEffect(Index) ? GetIngreData()->SkillID[Index] : 0);
	}

	long GetAttributeID(const int Index) {
		return (IsValidEffect(Index) ? GetIngreData()->AttributeID[Index] : 0);
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID);

	/* Set class members */
	void SetWeight(const float Value) {
		GetIngreData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetIngreData()->Value = Value;
	}

	void SetEffectID(const int Index, const long Value) {
		if (IsValidEffect(Index)) {
			GetIngreData()->EffectID[Index] = Value;
		}
	}

	void SetSkillID(const int Index, const long Value) {
		if (IsValidEffect(Index)) {
			GetIngreData()->SkillID[Index] = Value;
		}
	}

	void SetAttributeID(const int Index, const long Value) {
		if (IsValidEffect(Index)) {
			GetIngreData()->AttributeID[Index] = Value;
		}
	}

};

/*===========================================================================
 *      End of Class CEsmSubIRDT Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class bool CEsmSubIRDT Method - inline IsUsed (pID) const;
 *
 *=========================================================================*/
inline bool CEsmSubIRDT::IsUsed(const TCHAR *pID) {
	bool Result;
	int Index;

	for (Index = 0; Index < MWESM_INGRE_NUMEFFECTS; Index++) {
		if (GetIngreData()->EffectID[Index] < 0) {
			continue;
		}

		Result = StringCompare(GetESMEffect(GetIngreData()->EffectID[Index]), pID, false) == 0;

		if (Result) {
			return (true);
		}
	}

	return (false);
}

/*===========================================================================
 *      End of Class Method bool CEsmSubIRDT::IsUsed()
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmSubIRDT.H
 *=========================================================================*/
