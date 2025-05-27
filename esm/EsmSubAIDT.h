/*===========================================================================
 *
 * File:    EsmsubAIDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBAIDT_H
#define __ESMSUBAIDT_H


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

/* AI data flag values */
#define MWESM_AIFLAG_WEAPON       0x00001
#define MWESM_AIFLAG_ARMOR        0x00002
#define MWESM_AIFLAG_CLOTHING     0x00004
#define MWESM_AIFLAG_BOOK         0x00008
#define MWESM_AIFLAG_INGREDIANT   0x00010
#define MWESM_AIFLAG_PICK         0x00020
#define MWESM_AIFLAG_PROBE        0x00040
#define MWESM_AIFLAG_LIGHT        0x00080
#define MWESM_AIFLAG_APPARATUS    0x00100
#define MWESM_AIFLAG_REPAIR       0x00200
#define MWESM_AIFLAG_MISC         0x00400
#define MWESM_AIFLAG_SPELL        0x00800
#define MWESM_AIFLAG_MAGICITEM    0x01000
#define MWESM_AIFLAG_POTION       0x02000
#define MWESM_AIFLAG_TRAINING     0x04000
#define MWESM_AIFLAG_SPELLMAKING  0x08000
#define MWESM_AIFLAG_ENCHANTING   0x10000
#define MWESM_AIFLAG_REPAIRITEM   0x20000

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
	byte Hello;
	byte Unknown1;
	byte Fight;
	byte Flee;
	byte Alarm;
	byte Unknown2;
	byte Unknown3;
	byte Unknown4;
	long Flags;
} aidata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubAIDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubAIDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubAIDT();
	//virtual ~CEsmSubAIDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubAIDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(aidata_t));
		m_RecordSize = sizeof(aidata_t);
		memset(m_pData, 0, sizeof(aidata_t));
	}

	/* Get class members */
	aidata_t *GetAIData(void) {
		return ((aidata_t *)m_pData);
	}

	byte GetHello(void) {
		return (GetAIData()->Hello);
	}

	byte GetFlee(void) {
		return (GetAIData()->Flee);
	}

	byte GetFight(void) {
		return (GetAIData()->Fight);
	}

	byte GetAlarm(void) {
		return (GetAIData()->Alarm);
	}

	long GetFlags(void) {
		return (GetAIData()->Flags);
	}

	bool IsFlag(const long Flag) {
		return ((GetFlags() & Flag) != 0);
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetAIData()->Flags |= Flag;
		} else {
			GetAIData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetHello(const byte Value) {
		GetAIData()->Hello = Value;
	}

	void SetFlee(const byte Value) {
		GetAIData()->Flee = Value;
	}

	void SetFight(const byte Value) {
		GetAIData()->Fight = Value;
	}

	void SetAlarm(const byte Value) {
		GetAIData()->Alarm = Value;
	}

	void SetFlags(const long Value) {
		GetAIData()->Flags = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubAIDT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubAIDT.H
 *=========================================================================*/
