/*===========================================================================
 *
 * File:    EsmSubFloat.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBFLOAT_H
#define __ESMSUBFLOAT_H


#include "EsmSubBase.h"


#pragma pack(push, 1)

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubFloat Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubFloat : public CEsmSubRecord {
  protected:
	float m_Float;


	virtual bool ReadData(CGenFile &File) {
		return File.ReadFloat(m_Float);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.WriteFloat(m_Float);
	}


  public:
	/* Class Constructors/Destructors */
	//CEsmSubFLAG();
	//virtual ~CEsmSubFLAG() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		m_Float = ((CEsmSubFloat *)pSubRecord)->GetValue();
	}

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubFloat);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		m_Float = 0;
		m_RecordSize = sizeof(float);
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return false;
	}

	/* Get/set the long value directly */
	float GetValue() {
		return m_Float;
	}

	void SetValue(const float Value) {
		m_Float = Value;
	}
};


#endif
