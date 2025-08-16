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


#include "EsmSubBase.h"


#define MWESM_CELLFLAG_INTERIOR       0x01
#define MWESM_CELLFLAG_HASWATER       0x02
#define MWESM_CELLFLAG_SLEEPILLEGAL   0x04
#define MWESM_CELLFLAG_LIKEEXTERIOR   0x80


#pragma pack(push, 1)

typedef struct {
	long Flags;
	long GridX;
	long GridY;
} celldata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubCellDATA Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCellDATA : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubCellDATA();
	//virtual ~CEsmSubCellDATA() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCellDATA);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(celldata_t));
		m_RecordSize = sizeof(celldata_t);
		memset(m_pData, 0, sizeof(celldata_t));
	}

	/* Get class methods */
	celldata_t *GetCellData() {
		return (celldata_t *)m_pData;
	}

	long GetGridX() {
		return GetCellData()->GridX;
	}

	long GetGridY() {
		return GetCellData()->GridY;
	}

	long GetFlags() {
		return GetCellData()->Flags;
	}

	bool IsInterior() {
		return (GetFlags() & MWESM_CELLFLAG_INTERIOR) != 0;
	}

	bool HasWater() {
		return (GetFlags() & MWESM_CELLFLAG_HASWATER) != 0;
	}

	bool IsSleepIllegal() {
		return (GetFlags() & MWESM_CELLFLAG_SLEEPILLEGAL) != 0;
	}

	bool IsLikeExterior() {
		return (GetFlags() & MWESM_CELLFLAG_LIKEEXTERIOR) != 0;
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


#endif
