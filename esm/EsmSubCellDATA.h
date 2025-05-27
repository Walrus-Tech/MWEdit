/*===========================================================================
 *
 * File:    EsmSubCellDATA.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBCELLDATA_H
#define __ESMSUBCELLDATA_H


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
#define MWESM_CELLFLAG_INTERIOR       0x01
#define MWESM_CELLFLAG_HASWATER       0x02
#define MWESM_CELLFLAG_SLEEPILLEGAL   0x04
#define MWESM_CELLFLAG_LIKEEXTERIOR   0x80
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
	long Flags;
	long GridX;
	long GridY;
} celldata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubCellDATA Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCellDATA : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubCellDATA();
	//virtual ~CEsmSubCellDATA() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCellDATA);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(celldata_t));
		m_RecordSize = sizeof(celldata_t);
		memset(m_pData, 0, sizeof(celldata_t));
	}

	/* Get class methods */
	celldata_t *GetCellData(void) {
		return ((celldata_t *)m_pData);
	}

	long GetGridX(void) {
		return (GetCellData()->GridX);
	}

	long GetGridY(void) {
		return (GetCellData()->GridY);
	}

	long GetFlags(void) {
		return (GetCellData()->Flags);
	}

	bool IsInterior(void) {
		return ((GetFlags() & MWESM_CELLFLAG_INTERIOR) != 0);
	}

	bool HasWater(void) {
		return ((GetFlags() & MWESM_CELLFLAG_HASWATER) != 0);
	}

	bool IsSleepIllegal(void) {
		return ((GetFlags() & MWESM_CELLFLAG_SLEEPILLEGAL) != 0);
	}

	bool IsLikeExterior(void) {
		return ((GetFlags() & MWESM_CELLFLAG_LIKEEXTERIOR) != 0);
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetCellData()->Flags |= Flag;
		} else {
			GetCellData()->Flags &= ~Flag;
		}
	}

	/* Set class methods */
	void SetGridX(const long Value) {
		GetCellData()->GridX = Value;
	}

	void SetGridY(const long Value) {
		GetCellData()->GridY = Value;
	}

	void SetInterior(const bool Flag) {
		SetFlag(MWESM_CELLFLAG_INTERIOR, Flag);
	}

	void SetHasWater(const bool Flag) {
		SetFlag(MWESM_CELLFLAG_HASWATER, Flag);
	}

	void SetSleepIllegal(const bool Flag) {
		SetFlag(MWESM_CELLFLAG_SLEEPILLEGAL, Flag);
	}

	void SetLikeExterior(const bool Flag) {
		SetFlag(MWESM_CELLFLAG_LIKEEXTERIOR, Flag);
	}

};

/*===========================================================================
 *      End of Class CEsmSubCellDATA Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
