/*===========================================================================
 *
 * File:    EsmsubName512.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNAME512_H
#define __ESMSUBNAME512_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
#include "string/SString.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubName512 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubName512 : public CEsmSubRecord {

	/*---------- Begin Proected Class Members ---------------------*/
  protected:
	char m_NameData[513];


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData(CGenFile &File) {
		if (m_RecordSize > 512) {
			ErrorHandler.AddError(ERR_BADINPUT,
			                      _T("Invalid CEsmSubName512 record size of '%d'!"),
			                      m_RecordSize);
			return false;
		}

		memset(m_NameData, 0, 513);
		return File.Read((TCHAR *)(const TCHAR *)m_NameData, m_RecordSize);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.Write((const TCHAR *)m_NameData, m_RecordSize);
	}


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSubName512() {
		memset(m_NameData, 0, 513);
	}

	//virtual ~CEsmSubName512() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		Destroy();
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		SetName(((CEsmSubName512 *)pSubRecord)->GetName());
	}

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubName512);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		m_RecordSize = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return stristr(m_NameData, FindData.pText) != NULL;
	}

	/* Get class methods */
	const TCHAR *GetName() const {
		return &m_NameData[0];
	}

	virtual long GetRecordSize() const {
		return m_RecordSize;
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return TSTRNICMP(m_NameData, pID, 512) == 0;
	}

	/* Set class methods */
	void SetName(const TCHAR *pName) {
		memset(m_NameData, 0, 513);
		TSTRNCPY(m_NameData, pName, 512);
		m_RecordSize = TSTRLEN(m_NameData);
	}
};

/*===========================================================================
 *      End of Class CEsmSubName512 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmSubNameFix.H
 *=========================================================================*/
