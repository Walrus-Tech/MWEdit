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


#include "EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	byte Volume;
	byte MinRange;
	byte MaxRange;
} sounddata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubDATA Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubDATA : public CEsmSubRecord {
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


#endif
