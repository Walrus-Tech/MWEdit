/*===========================================================================
 *
 * File:    EsmsubNPCO.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNPCO_H
#define __ESMSUBNPCO_H


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
	long Count;
	TCHAR Item[MWESM_ID_MAXSIZE]; /* Might not be NULL terminated */
} npcodata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubNPCO Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubNPCO : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubNPCO();
	//virtual ~CEsmSubNPCO() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNPCO);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(npcodata_t));
		m_RecordSize = sizeof(npcodata_t);
		memset(m_pData, 0, sizeof(npcodata_t));
	}

	/* Get class methods */
	npcodata_t *GetData (void) {
		return (npcodata_t *) m_pData;
	}

	const TCHAR *GetItem (void) {
		return (GetData()->Item);
	}

	int GetCount (void) {
		return (GetData()->Count);
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed (const TCHAR* pID) {
		return (StringCompare(GetItem(), pID, false) == 0);
	}

	/* Set item data */
	void SetCount (const int Count) {
		GetData()->Count = Count;
	}

	void SetItem (const TCHAR* pString) {
		TSTRNCPY(GetData()->Item, pString, MWESM_ID_MAXSIZE);
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
