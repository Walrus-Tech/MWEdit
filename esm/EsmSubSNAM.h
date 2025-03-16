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
	char Name[MWESM_ID_MAXSIZE];
	byte Chance;
} snamdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubSNAM Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSNAM : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubSNAM();
	//virtual ~CEsmSubSNAM() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSNAM);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(snamdata_t));
		m_RecordSize = sizeof(snamdata_t);
		memset(m_pData, 0, sizeof(snamdata_t));
	}

	/* Get class methods */
	snamdata_t *GetSNAMData (void) {
		return ((snamdata_t *) m_pData);
	}

	const TCHAR *GetName (void) {
		return (GetSNAMData()->Name);
	}

	byte GetChance (void) {
		return (GetSNAMData()->Chance);
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed (const TCHAR* pID) {
		return (StringCompare(GetName(), pID, false) == 0);
	}

	/* Set class members */
	void SetName (const TCHAR* pString) {
		TSTRNCPY(GetSNAMData()->Name, pString, MWESM_ID_MAXSIZE);
	}

	void SetChance (const byte Chance) {
		GetSNAMData()->Chance = Chance;
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
