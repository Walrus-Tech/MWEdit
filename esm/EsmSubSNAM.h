/*===========================================================================
 *
 * File:    EsmSbSNAM.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSNAM_H
#define __ESMSUBSNAM_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	char Name[MWESM_ID_MAXSIZE];
	byte Chance;
} snamdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubSNAM Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSNAM : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubSNAM();
	//virtual ~CEsmSubSNAM() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSNAM);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(snamdata_t));
		m_RecordSize = sizeof(snamdata_t);
		memset(m_pData, 0, sizeof(snamdata_t));
	}

	/* Get class methods */
	snamdata_t *GetSNAMData() {
		return (snamdata_t *)m_pData;
	}

	const TCHAR *GetName() {
		return GetSNAMData()->Name;
	}

	byte GetChance() {
		return GetSNAMData()->Chance;
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return StringCompare(GetName(), pID, false) == 0;
	}

	/* Set class members */
	void SetName(const TCHAR *pString) {
		TSTRNCPY(GetSNAMData()->Name, pString, MWESM_ID_MAXSIZE);
	}

	void SetChance(const byte Chance) {
		GetSNAMData()->Chance = Chance;
	}
};


#endif
