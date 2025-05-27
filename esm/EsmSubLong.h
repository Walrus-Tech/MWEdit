/*===========================================================================
 *
 * File:    EsmSubLong.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBLONG_H
#define __ESMSUBLONG_H


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
 * Begin Class CEsmSubLong Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubLong : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	long m_Long;

	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	virtual bool ReadData(CGenFile &File) {
		return File.ReadLong(m_Long);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.WriteLong(m_Long);
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
		m_Long = ((CEsmSubLong *)pSubRecord)->GetValue();
	}


	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubLong);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		m_RecordSize = sizeof(long);
		m_Long = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return (false);
	}

	/* Get/set the long value directly */
	long GetValue(void) {
		return (m_Long);
	}

	void SetValue(const long Value) {
		m_Long = Value;
	}

	/* Set/check a bit field flag value */
	bool IsFlag(const long Flag) {
		return ((m_Long & Flag) != 0);
	}

	void SetFlag(const long Flag, const bool Set) {
		(Set ? SetFlag(Flag) : ClearFlag(Flag));
	}

	void SetFlag(const long Flag) {
		m_Long = (m_Long | Flag);
	}

	void ClearFlag(const long Flag) {
		m_Long = (m_Long & (~Flag));
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
