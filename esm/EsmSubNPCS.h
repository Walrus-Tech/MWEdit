/*===========================================================================
 *
 * File:    EsmsubNPCS.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNPCS_H
#define __ESMSUBNPCS_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	TCHAR Item[MWESM_ID_MAXSIZE]; /* Might not be NULL terminated */
} npcsdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubNPCS Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubNPCS : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubNPCS();
	//virtual ~CEsmSubNPCS() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNPCS);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(npcsdata_t));
		m_RecordSize = sizeof(npcsdata_t);
		memset(m_pData, 0, sizeof(npcsdata_t));
	}

	/* Get class methods */
	npcsdata_t *GetData() {
		return (npcsdata_t *)m_pData;
	}

	const TCHAR *GetName() {
		return GetData()->Item;
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return StringCompare(GetName(), pID, false) == 0;
	}

	/* Set class methods */
	void SetName(const TCHAR *pString) {
		TSTRNCPY(GetData()->Item, pString, MWESM_ID_MAXSIZE);
	}
};


#endif
