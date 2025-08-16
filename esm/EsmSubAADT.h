/*===========================================================================
 *
 * File:    Esmsubaadt.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAADT_H
#define __ESMSUBAADT_H


#include "EsmSubBase.h"


#define MWESM_APPATYPE_MIN        0
#define MWESM_APPATYPE_MORTAR     0
#define MWESM_APPATYPE_ALBEMIC    1
#define MWESM_APPATYPE_CALCINATOR 2
#define MWESM_APPATYPE_RETORT     3
#define MWESM_APPATYPE_MAX        3


#pragma pack(push, 1)

typedef struct {
	long Type;
	float Quality;
	float Weight;
	long Value;
} appadata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubAADT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAADT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubAADT();
	//virtual ~CEsmSubAADT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAADT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(appadata_t));
		m_RecordSize = sizeof(appadata_t);
		memset(m_pData, 0, sizeof(appadata_t));
	}

	/* Get class methods */
	appadata_t *GetAppaData() {
		return (appadata_t *)m_pData;
	}

	long GetAppaType() {
		return GetAppaData()->Type;
	}

	float GetQuality() {
		return GetAppaData()->Quality;
	}

	float GetWeight() {
		return GetAppaData()->Weight;
	}

	long GetValue() {
		return GetAppaData()->Value;
	}

	/* Set class members */
	void SetAppaType(const long Type) {
		if (Type >= MWESM_APPATYPE_MIN && Type <= MWESM_APPATYPE_MAX) {
			GetAppaData()->Type = Type;
		}
	}

	void SetQuality(const float Value) {
		GetAppaData()->Quality = Value;
	}

	void SetWeight(const float Value) {
		GetAppaData()->Weight = Value;
	}

	void SetValue(const long Value) {
		GetAppaData()->Value = Value;
	}
};


#endif
