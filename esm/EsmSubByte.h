/*===========================================================================
 *
 * File:    EsmSubByte.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBBYTE_H
#define __ESMSUBBYTE_H


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
 * Begin Class CEsmSubByte Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubByte : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	char m_Byte;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	virtual bool ReadData(CGenFile &File) {
		return File.ReadChar(m_Byte);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.WriteChar(m_Byte);
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
		m_Byte = ((CEsmSubByte *)pSubRecord)->GetValue();
	}

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubByte);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		m_Byte = 0;
		m_RecordSize = sizeof(byte);
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return false;
	}

	/* Get/set the long value directly */
	byte GetValue() {
		return m_Byte;
	}

	void SetValue(const byte Value) {
		m_Byte = Value;
	}

	/* Set a bit field flag value */
	bool IsFlag(const byte Flag) {
		return (m_Byte & Flag) != 0;
	}

	void SetFlag(const byte Flag, const bool Set) {
		Set ? SetFlag(Flag) : ClearFlag(Flag);
	}

	void SetFlag(const byte Flag) {
		m_Byte = (m_Byte | Flag);
	}

	void ClearFlag(const byte Flag) {
		m_Byte = (m_Byte & (~Flag));
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
