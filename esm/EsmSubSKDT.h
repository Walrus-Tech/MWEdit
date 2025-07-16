/*===========================================================================
 *
 * File:    EsmsubSKDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSKDT_H
#define __ESMSUBSKDT_H


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
	long Attribute;
	long Specialization;
	float UseValue1;
	float UseValue2;
	float UseValue3;
	float UseValue4;
} skilldata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubSKDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSKDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubSKDT();
	//virtual ~CEsmSubSKDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSKDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(skilldata_t));
		m_RecordSize = sizeof(skilldata_t);
		memset(m_pData, 0, sizeof(skilldata_t));

		GetSkillData()->UseValue1 = 1.0f;
		GetSkillData()->UseValue2 = 1.0f;
		GetSkillData()->UseValue3 = 1.0f;
		GetSkillData()->UseValue4 = 1.0f;
	}

	/* Get class members */
	skilldata_t *GetSkillData() {
		return (skilldata_t *)m_pData;
	}

	long GetAttributeID() {
		return GetSkillData()->Attribute;
	}

	long GetSpecialization() {
		return GetSkillData()->Specialization;
	}

	float GetUseValue1() {
		return GetSkillData()->UseValue1;
	}

	float GetUseValue2() {
		return GetSkillData()->UseValue2;
	}

	float GetUseValue3() {
		return GetSkillData()->UseValue3;
	}

	float GetUseValue4() {
		return GetSkillData()->UseValue4;
	}

	/* Set class members */
	void SetAttributeID(const long Value) {
		GetSkillData()->Attribute = Value;
	}

	void SetSpecialization(const long Value) {
		GetSkillData()->Specialization = Value;
	}

	void SetUseValue1(const float Value) {
		GetSkillData()->UseValue1 = Value;
	}

	void SetUseValue2(const float Value) {
		GetSkillData()->UseValue2 = Value;
	}

	void SetUseValue3(const float Value) {
		GetSkillData()->UseValue3 = Value;
	}

	void SetUseValue4(const float Value) {
		GetSkillData()->UseValue4 = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
