/*===========================================================================
 *
 * File:    EsmSubDATA.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBDATA_H
#define __ESMSUBDATA_H


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
	byte Volume;
	byte MinRange;
	byte MaxRange;
} sounddata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubDATA Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubDATA : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubDATA();
	//virtual ~CEsmSubDATA() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubDATA);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(sounddata_t));
		m_RecordSize = sizeof(sounddata_t);
		memset(m_pData, 0, sizeof(sounddata_t));
	}

	/* Get class members */
	sounddata_t *GetSoundData() {
		return (sounddata_t *)m_pData;
	}

	byte GetVolume() {
		return GetSoundData()->Volume;
	}

	byte GetMinRange() {
		return GetSoundData()->MinRange;
	}

	byte GetMaxRange() {
		return GetSoundData()->MaxRange;
	}

	/* Set class members */
	void SetVolume(const byte Value) {
		GetSoundData()->Volume = Value;
	}

	void SetMinRange(const byte Value) {
		GetSoundData()->MinRange = Value;
	}

	void SetMaxRange(const byte Value) {
		GetSoundData()->MaxRange = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT CEsmSubDATA
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubDATA.H
 *=========================================================================*/
