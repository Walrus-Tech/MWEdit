/*===========================================================================
 *
 * File:    EsmsubCLDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBCLDT_H
#define __ESMSUBCLDT_H


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

/* Class data flags */
#define MWESM_CLASSFLAG_PLAYABLE  1

/* Class Auto-calc Flags */
#define MWESM_CLASSAUTO_WEAPONS       0x00001
#define MWESM_CLASSAUTO_ARMOR         0x00002
#define MWESM_CLASSAUTO_CLOTHING      0x00004
#define MWESM_CLASSAUTO_BOOKS         0x00008
#define MWESM_CLASSAUTO_INGREDIANTS   0x00010
#define MWESM_CLASSAUTO_PICKS         0x00020
#define MWESM_CLASSAUTO_PROBES        0x00040
#define MWESM_CLASSAUTO_LIGHTS        0x00080
#define MWESM_CLASSAUTO_APPARATUS     0x00100
#define MWESM_CLASSAUTO_REPAIR        0x00200
#define MWESM_CLASSAUTO_MISC          0x00400
#define MWESM_CLASSAUTO_SPELLS        0x00800
#define MWESM_CLASSAUTO_MAGICITEMS    0x01000
#define MWESM_CLASSAUTO_POTIONS       0x02000
#define MWESM_CLASSAUTO_TRAINING      0x04000
#define MWESM_CLASSAUTO_SPELLMAKING   0x08000
#define MWESM_CLASSAUTO_ENCHANTING    0x10000
#define MWESM_CLASSAUTO_REPAIRITEM    0x20000

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
	long AttributeID1;
	long AttributeID2;
	long Specialization;
	long MinorID1;
	long MajorID1;
	long MinorID2;
	long MajorID2;
	long MinorID3;
	long MajorID3;
	long MinorID4;
	long MajorID4;
	long MinorID5;
	long MajorID5;
	long Flags;
	long AutoCalcFlags;
} classdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubCLDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCLDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubCLDT();
	//virtual ~CEsmSubCLDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCLDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(classdata_t));
		m_RecordSize = sizeof(classdata_t);
		memset(m_pData, 0, sizeof(classdata_t));
		GetClassData()->MinorID1 = 0;
		GetClassData()->MinorID2 = 1;
		GetClassData()->MinorID3 = 2;
		GetClassData()->MinorID4 = 3;
		GetClassData()->MinorID5 = 4;
		GetClassData()->MajorID1 = 5;
		GetClassData()->MajorID2 = 6;
		GetClassData()->MajorID3 = 7;
		GetClassData()->MajorID4 = 8;
		GetClassData()->MajorID5 = 9;
		GetClassData()->AttributeID1 = 0;
		GetClassData()->AttributeID2 = 1;
	}

	/* Get class members */
	classdata_t *GetClassData(void) {
		return ((classdata_t *)m_pData);
	}

	long GetAttribute1(void) {
		return (GetClassData()->AttributeID1);
	}

	long GetAttribute2(void) {
		return (GetClassData()->AttributeID2);
	}

	long GetSpecialization(void) {
		return (GetClassData()->Specialization);
	}

	long GetFlags(void) {
		return (GetClassData()->Flags);
	}

	long GetAutoCalcFlags(void) {
		return (GetClassData()->AutoCalcFlags);
	}

	bool IsPlayable(void) {
		return ((GetFlags() & MWESM_CLASSFLAG_PLAYABLE) != 0);
	}

	bool IsAutoCalcFlag(const long Flag) {
		return ((GetAutoCalcFlags() & Flag) != 0);
	}

	/* Get major skills */
	long GetMajorSkill(const int Index) {
		switch (Index) {
			case 0:
				return (GetClassData()->MajorID1);

			case 1:
				return (GetClassData()->MajorID2);

			case 2:
				return (GetClassData()->MajorID3);

			case 3:
				return (GetClassData()->MajorID4);

			default:
				return (0);
		}
	}

	/* Get minor skills */
	long GetMinorSkill(const int Index) {
		switch (Index) {
			case 0:
				return (GetClassData()->MinorID1);

			case 1:
				return (GetClassData()->MinorID2);

			case 2:
				return (GetClassData()->MinorID3);

			case 3:
				return (GetClassData()->MinorID4);

			default:
				return (0);
		}
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetClassData()->Flags |= Flag;
		} else {
			GetClassData()->Flags &= ~Flag;
		}
	}

	void SetAutoCalcFlag(const long Flag, const bool Set) {
		if (Set) {
			GetClassData()->AutoCalcFlags |= Flag;
		} else {
			GetClassData()->AutoCalcFlags &= ~Flag;
		}
	}

	/* Set class members */
	void SetAttribute1(const long Value) {
		GetClassData()->AttributeID1 = Value;
	}

	void SetAttribute2(const long Value) {
		GetClassData()->AttributeID2 = Value;
	}

	void SetSpecialization(const long Value) {
		GetClassData()->Specialization = Value;
	}

	void SetPlayable(const bool Flag) {
		SetFlag(MWESM_CLASSFLAG_PLAYABLE, Flag);
	}

	/* Set major skills */
	void SetMajorSkill(const int Index, const long Value) {
		switch (Index) {
			case 0:
				GetClassData()->MajorID1 = Value;
				break;

			case 1:
				GetClassData()->MajorID2 = Value;
				break;

			case 2:
				GetClassData()->MajorID3 = Value;
				break;

			case 3:
				GetClassData()->MajorID4 = Value;
				break;
		}
	}

	/* Set minor skills */
	void SetMinorSkill(const int Index, const long Value) {
		switch (Index) {
			case 0:
				GetClassData()->MinorID1 = Value;
				break;

			case 1:
				GetClassData()->MinorID2 = Value;
				break;

			case 2:
				GetClassData()->MinorID3 = Value;
				break;

			case 3:
				GetClassData()->MinorID4 = Value;
				break;
		}
	}
};

/*===========================================================================
 *      End of Class CEsmSubCLDT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
