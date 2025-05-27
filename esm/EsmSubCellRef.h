/*===========================================================================
 *
 * File:    EsmSubCellRef.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBCELLREF_H
#define __ESMSUBCELLREF_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
#include "EsmSubPos6.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

#define MWESM_CELLREF_INDEXMASK 0x00FFFFFF
#define MWESM_CELLREF_MODFLAG   0x01000000

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
//#pragma pack(push, 1)

struct esmrecinfo_t;
class CEsmCell;

//#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubCellRef Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCellRef : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubRecArray m_SubRecArray;      /* Array of sub-records related to the reference */

	bool m_IsActive;
	esmrecinfo_t *m_pRecInfo;
	CEsmCell *m_pCell;        /* Parent cell */
	long m_UserData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Clears all sub-records in the array */
	void ClearSubRecArray(void);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSubCellRef();
	virtual ~CEsmSubCellRef() {
		Destroy();
	}

	virtual void Destroy(void);

	/* Add a new sub-record to the cell-reference array */
	void AddSubRec(CEsmSubRecord *pSubRec) {
		m_SubRecArray.Add(pSubRec);
	}

	/* Copy from another cellref sub-record */
	virtual void Copy(CEsmSubRecord *pSubRecord);

	/* Create a name object */
	static CEsmSubRecord *Create(void);

	/* Create a new sub-record */
	virtual void CreateNew(CEsmCell *pCell);

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData);

	/* Access sub-records */
	CEsmSubRecord *FindSubRecord(const TCHAR *pType);

	/* Get class members */
	int GetNumSubRecs(void) {
		return (m_SubRecArray.GetSize());
	}

	CEsmSubRecord *GetSubRec(const int Index) {
		return (m_SubRecArray.GetAt(Index));
	}

	CEsmCell *GetCell(void) {
		return (m_pCell);
	}

	esmrecinfo_t *GetRecInfo(void) {
		return (m_pRecInfo);
	}

	bool IsActive(void) {
		return (m_IsActive);
	}

	bool IsDeleted(void) {
		return (FindSubRecord(MWESM_SUBREC_DELE) != NULL);
	}

	long GetUserData(void) {
		return (m_UserData);
	}

	const TCHAR *GetFieldString(const int FieldID);
	int GetIndex(void);
	pos6data_t *GetLocation(void);

	/* Is the cell reference for the given object? */
	bool IsReference(const TCHAR *pID);

	/* Checks for an identical cell reference object */
	bool IsSame(CEsmSubCellRef *pCellRef);

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID);

	/* Set class members */
	void SetIsActive(const bool Flag) {
		m_IsActive = Flag;
	}

	void SetRecInfo(esmrecinfo_t *pRecInfo) {
		m_pRecInfo = pRecInfo;
	}

	void SetCell(CEsmCell *pCell) {
		m_pCell = pCell;
	}

	void SetUserData(const long Value) {
		m_UserData = Value;
	}

	void SetRefName(const TCHAR *pName);
	void SetIndex(const long Index, const byte Flag);
	void SetFRMRFlag(const byte Flag);
	void SetFRMRIndex(const long Index);
	void SetDelete(const bool Flag);

	/* Output the entire sub-record to the given location in the file */
	virtual bool Write(CGenFile &File);

};

/*===========================================================================
 *      End of Class CEsmSubCellRef Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
