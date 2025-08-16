/*===========================================================================
 *
 * File:    EsmsubAMBI.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAMBI_H
#define __ESMSUBAMBI_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	long AmbientColor;
	long SunlightColor;
	long FogColor;
	float FogDensity;
} ambidata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubAMBI Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAMBI : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubAMBI() {}
	//virtual ~CEsmSubAMBI() { Destroy(); }
	//virtual void Destroy (void) { }

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAMBI);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(ambidata_t));
		m_RecordSize = sizeof(ambidata_t);
		memset(m_pData, 0, sizeof(ambidata_t));
	}

	/* Get class methods */
	ambidata_t *GetAMBIData() {
		return (ambidata_t *)m_pData;
	}
};


#endif
