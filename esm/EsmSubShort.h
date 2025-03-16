/*===========================================================================
 *
 * File:    EsmSubShort.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSHORT_H
#define __ESMSUBSHORT_H


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
 * Begin Class CEsmSubShort Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubShort : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	short m_Short;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	virtual bool ReadData (CGenFile& File) {
		return File.ReadShort(m_Short);
	}

	virtual bool WriteData (CGenFile& File) {
		return File.WriteShort(m_Short);
	}


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubFLAG();
	//virtual ~CEsmSubFLAG() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy (CEsmSubRecord* pSubRecord) {
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		m_Short = ((CEsmSubShort *) pSubRecord)->GetValue();
	}

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubShort);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(short));
		m_RecordSize = sizeof(short);
		m_Short = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find (esmfind_t &FindData) {
		return (false);
	}

	/* Get/set the long value directly */
	short GetValue (void) {
		return (m_Short);
	}

	void SetValue (const short Value) {
		m_Short = Value;
	}

	/* Set a bit field flag value */
	bool IsFlag (const short Flag) {
		return ((m_Short & Flag) != 0);
	}

	void SetFlag (const short Flag, const bool Set) {
		(Set ? SetFlag(Flag) : ClearFlag(Flag));
	}

	void SetFlag (const short Flag) {
		m_Short = (m_Short | Flag);
	}

	void ClearFlag (const short Flag) {
		m_Short = (m_Short & (~Flag));
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
