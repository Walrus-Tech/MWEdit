/*===========================================================================
 *
 * File:    Esmsubbase.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBBASE_H
#define __ESMSUBBASE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "file/GenFile.h"
#include "EsmDefs.h"
#include "contain/PtrArray.h"
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

/* The record and sub-record type */
union esmrectype_t {
	TCHAR pType[MWESM_TYPE_SIZE];
	long lType;

	esmrectype_t () {
		lType = 0;
	}

	operator dword(void) const {
		return lType;
	}

	bool IsType (const esmrectype_t NewType) const {
		return (NewType.lType == lType);
	}

	bool IsType (const TCHAR* pNewType) const {
		return (*(const long*)pNewType == lType);
	}

	bool IsType (const long lNewType) const {
		return (lNewType == lType);
	}

	void SetType (const esmrectype_t NewType) {
		lType = NewType.lType;
	}

	void SetType (const TCHAR* pNewType) {
		lType = *(const long *)pNewType;
	}

	void SetType (const long lNewType) {
		lType = lNewType;
	}
};

inline bool operator == (const esmrectype_t &Type1, const esmrectype_t &Type2) {
	return Type1.lType == Type2.lType;
}

/* Find text structure */
struct esmfind_t {
	const TCHAR *pText;      /* The text we want to find */
	int Length;     /* Size of text */
};

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubRecord Definition
 *
 * Base class for all the sub-records in the ESM/ESP file.
 *
 *=========================================================================*/
class CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	esmrectype_t m_Type;         /* Type of sub-record */
	long m_RecordSize;       /* Size of the record when output */
	byte *m_pData;        /* The record data for an unknown type */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData (CGenFile& File);   /* Override in base classes */

	/* Helper output methods */
	virtual bool WriteData (CGenFile& File);    /* Override in base classes */
	virtual bool WriteHeader (CGenFile& File);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSubRecord();
	virtual ~CEsmSubRecord() {
		Destroy();
	}

	virtual void Destroy (void);

	/* Copies the values from the given subrecord */
	virtual void Copy (CEsmSubRecord* pSubRecord);

	/* Copies the given data into the subrecord */
	virtual void CopyData (char* pData, const int Size);

	/* Return a new sub-record object */
	static CEsmSubRecord *Create (void);

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		Destroy();
	}

	virtual void CreateNew (const int Size) {
		Destroy();
		CreateArrayPointerL(m_pData, byte, Size);
		m_RecordSize = Size;
		memset(m_pData, 0, Size);
	}

	/* Finds text in the sub-record */
	virtual bool Find (esmfind_t &FindData);

	/* Get class members */
	const TCHAR *GetType (void) const {
		return (m_Type.pType);
	}

	virtual long GetRecordSize (void) const {
		return (m_RecordSize);
	}

	byte *GetData (void) {
		return (m_pData);
	}

	/* Type comparison */
	bool IsType (const TCHAR* pType) const {
		return (m_Type.IsType(pType));
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed (const TCHAR* pID) {
		return (false);
	}

	/* Read a record from the current position in the file */
	virtual bool Read (CGenFile& File);

	/* Set class members */
	void SetRecordSize (const long Size) {
		m_RecordSize = Size;
	}

	void SetType (const TCHAR* pType) {
		m_Type.SetType(pType);
	}

	/* Output the entire sub-record to the given location in the file */
	virtual bool Write (CGenFile& File);


};

/*===========================================================================
 *      End of Class CEsmSubRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Pointer to a class method to create a sub-record object */
typedef CEsmSubRecord *(*ESMSUBREC_CREATEFUNC) (void);

/* Structure to hold information on sub-records */
typedef struct esmsubreccreate {
	const TCHAR *Type;
	ESMSUBREC_CREATEFUNC CreateMethod;

	/* Simple compare function */
	bool IsType (const TCHAR* pType) const {
		return (TSTRNICMP(Type, pType, MWESM_TYPE_SIZE) == 0);
	}
} esmsubreccreate_t;

/* Array of sub-record pointers */
typedef TPtrArray<CEsmSubRecord> CEsmSubRecArray;

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubbase.H
 *=========================================================================*/
