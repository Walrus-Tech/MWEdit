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
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubFloat Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubFloat : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	float m_Float;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	virtual bool ReadData(CGenFile &File) {
		return File.ReadFloat(m_Float);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.WriteFloat(m_Float);
	}


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubFLAG();
	//virtual ~CEsmSubFLAG() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		m_Float = ((CEsmSubFloat *) pSubRecord)->GetValue();
	}

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubFloat);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		m_Float = 0;
		m_RecordSize = sizeof(float);
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return (false);
	}

	/* Get/set the long value directly */
	float GetValue(void) {
		return (m_Float);
	}

	void SetValue(const float Value) {
		m_Float = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
