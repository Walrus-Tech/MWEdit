/*===========================================================================
 *
 * File:    Esmrecord.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMRECORD_H
#define __ESMRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
#include "EsmSubName.h"
#include "EsmSubLong.h"
#include "EsmSubNameFix.h"
#include "contain/dl_map.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Offset of the recordsize from the end of the record header */
#define MWESM_RECSIZE_OFFSET 12

/* Record flag bit fields */
#define MWESM_REC_BLOCKED 0x2000
#define MWESM_REC_PERSIST 0x0400

/* Class type flag (bit field) */
#define MWESM_CLASSTYPE_BASE 1

/* Static array for creating the record's subrecords */
#define DECLARE_SUBRECCREATE() private: \
	static const esmsubreccreate_t s_SubRecCreate[]; \
	virtual const esmsubreccreate_t* GetSubRecCreate (void) const { return (s_SubRecCreate); }

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmRecord Definition
 *
 * Base class for the main records in the ESM/ESP files.
 *
 *=========================================================================*/
class CEsmFile;

class CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmFile *m_pFile;        /* File parent */
	CEsmRecord *m_pPrevRecord;      /* Previous record in another file */

	esmrectype_t m_Type;         /* Type of record */
	long m_Header1;      /* Header data (unknown) */
	long m_Flags;
	long m_RecordSize;       /* Record size, used for input/output */
	long m_RefCount;

	long m_UserData;     /* Custom user data */

	CEsmSubRecArray m_SubRecords;       /* Array of sub-record pointers */

	CEsmSubLong *m_pDelete;      /* Reference to delete subrecord */
	CEsmSubName *m_pID;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData (CGenFile& File);
	virtual bool ReadHeader (CGenFile& File);

	/* Helper output methods */
	virtual bool WriteHeader (CGenFile& File);
	virtual bool WriteData (CGenFile& File);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmRecord();
	virtual ~CEsmRecord() {
		Destroy();
	}

	virtual void Destroy (void);

	/* Copy the contents from the given record */
	virtual void AddSubRecord (CEsmSubRecord* pSubRecord) {
		m_SubRecords.Add(pSubRecord);
	}

	virtual CEsmSubRecord *AllocNewSubRecord (const TCHAR* pType, const long RecordSize = 0);
	CEsmSubRecord *AllocateSubRecord (const TCHAR* pType, const long RecordSize = 0);
	virtual void Copy (CEsmRecord* pRecord);
	static CEsmRecord *Create (void);
	CEsmSubRecord *CreateCopy (CEsmSubRecord* pSubRecord);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Compare a specific field of the two record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Undeletes or deletes the record */
	virtual void DeleteToggle (void);

	/* Delete all sub-records of the given type */
	virtual int DeleteSubRecords (const TCHAR* pType);
	virtual void DeleteSubRecord (CEsmSubRecord* pSubRec) {
		m_SubRecords.DeleteElement(pSubRec);
	}

	/* Returns true if the record contains the given text */
	virtual bool Find (esmfind_t &FindData);

	/* Used to determine the type of derived classes */
	virtual int GetClassType (void) {
		return (MWESM_CLASSTYPE_BASE);
	}

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("?");
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Access particular records */
	CEsmSubRecord *FindFirst (const TCHAR* pType, int &ArrayIndex) {
		ArrayIndex = -1;
		return FindNext(pType, ArrayIndex);
	}

	CEsmSubRecord *FindNext (const TCHAR* pType, int &ArrayIndex);
	CEsmSubRecord *GetSubRecord (const int Index) {
		return (m_SubRecords.GetAt(Index));
	}

	int GetNumSubRecords (void) {
		return (m_SubRecords.GetSize());
	}

	/* Get class members */
	const TCHAR *GetType (void) {
		return (m_Type.pType);
	}

	esmrectype_t &GetRawType (void) {
		return (m_Type);
	}

	bool IsBlocked (void) {
		return ((m_Flags & MWESM_REC_BLOCKED) != 0);
	}

	bool IsPersist (void) {
		return ((m_Flags & MWESM_REC_PERSIST) != 0);
	}

	bool IsDeleted (void) {
		return (m_pDelete != NULL);
	}

	long GetRefCount (void) {
		return (m_RefCount);
	}

	CEsmFile *GetFile (void) {
		return (m_pFile);
	}

	CEsmRecord *GetPrevRecord (void) {
		return (m_pPrevRecord);
	}

	long GetUserData (void) {
		return (m_UserData);
	}

	/* Access the object's ID as a string */
	virtual const TCHAR *GetID (void) {
		return (m_pID ? m_pID->GetName() : _T(""));
	}

	virtual void SetID (const TCHAR* pString) {
		if (m_pID) {
			m_pID->SetName(pString);
		}
	}

	/* Are the records describing the same item */
	virtual bool IsSame (CEsmRecord* pRecord);
	virtual bool IsID (const TCHAR* pID) {
		return (StringCompare(GetID(), pID, false) == 0);
	}

	/* Checks if another record is used in this record */
	virtual bool IsUsed (const TCHAR* pID);

	/* Type comparison */
	bool IsType (const TCHAR* pType) const {
		return m_Type.IsType(pType);
	}

	/* So derived classes can detect an add event */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Input a record from the file */
	bool Read (CGenFile& File);

	/* Remove and delete the given sub-record */
	bool RemoveSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetFile (CEsmFile* pFile) {
		m_pFile = pFile;
	}

	void SetPrevRecord (CEsmRecord* pRecord) {
		m_pPrevRecord = pRecord;
	}

	void SetType (const TCHAR* pType) {
		m_Type.SetType(pType);
	}

	void SetUserData (const long Value) {
		m_UserData = Value;
	}

	void SetBlocked (const bool Flag) {
		m_Flags = (Flag ? m_Flags | (MWESM_REC_BLOCKED) : (m_Flags & (~MWESM_REC_BLOCKED)));
	}

	void SetPersist (const bool Flag) {
		m_Flags = (Flag ? m_Flags | (MWESM_REC_PERSIST) : (m_Flags & (~MWESM_REC_PERSIST)));
	}

	void AddReference (void) {
		m_RefCount++;
	}

	void DelReference (void) {
		m_RefCount--;
	}

	void SetDelete (const bool Flag);

	/* Set a certain field of the record */
	virtual bool SetFieldValue (const int FieldID, const TCHAR* pString);


	/* Output the record to the given file */
	bool Write (CGenFile& File);

};

/*===========================================================================
 *      End of Class CEsmRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Pointer to a class method to create a record object */
typedef CEsmRecord *(*ESMREC_CREATEFUNC) (void);

/* Structure to hold information on records */
typedef struct esmreccreate {
	const TCHAR *Type;
	ESMREC_CREATEFUNC CreateMethod;

	/* Simple compare function */
	bool IsType (const TCHAR* pType) const {
		return (TSTRNICMP(Type, pType, MWESM_TYPE_SIZE) == 0);
	}
} esmreccreate_t;

/* Sort function for the pointer array */
int _cdecl EsmRecordSort (const void* pElem1, const void* pElem2, const long lUserData);

/* Simple map of records by ID */
typedef TGenRefMap<CSString, CEsmRecord *, const char *> CEsmRecordRefMap;

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmrecord.H
 *=========================================================================*/
