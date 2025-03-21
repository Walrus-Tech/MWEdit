/*===========================================================================
 *
 * File:    EsmSubLong64.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBLONG64_H
#define __ESMSUBLONG64_H


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
 * Begin Class CEsmSubLong64 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubLong64 : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	long m_Long1;
	long m_Long2;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	virtual bool ReadData (CGenFile& File) {
		return File.ReadLong(m_Long1) & File.ReadLong(m_Long2);
	}

	virtual bool WriteData (CGenFile& File) {
		return File.WriteLong(m_Long1) & File.WriteLong(m_Long2);
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
		m_Long1 = ((CEsmSubLong64 *) pSubRecord)->GetValue1();
		m_Long2 = ((CEsmSubLong64 *) pSubRecord)->GetValue2();
	}


	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubLong64);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		m_RecordSize = sizeof(long) * 2;
		m_Long1 = 0;
		m_Long2 = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find (esmfind_t &FindData) {
		return (false);
	}

	/* Get/set the long value directly */
	long GetValue1 (void) {
		return (m_Long1);
	}

	long GetValue2 (void) {
		return (m_Long2);
	}

	void SetValue1 (const long Value) {
		m_Long1 = Value;
	}

	void SetValue2 (const long Value) {
		m_Long2 = Value;
	}


};

/*===========================================================================
 *      End of Class CEsmSubLong64 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmSubLong64.H
 *=========================================================================*/
