/*===========================================================================
 *
 * File:    EsmsubName32.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNAME32_H
#define __ESMSUBNAME32_H


#include "esm/EsmSubBase.h"
#include "Common/String/SString.h"


/*===========================================================================
 *
 * Begin Class CEsmSubName32 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubName32 : public CEsmSubRecord {
  protected:
	char m_NameData[33];


	/* Helper input methods */
	virtual bool ReadData(CGenFile &File) {
		if (m_RecordSize > 32) {
			ErrorHandler.AddError(ERR_BADINPUT,
			                      _T("Invalid CEsmSubName32 record size of '%d'!"),
			                      m_RecordSize);
			return false;
		}

		memset(m_NameData, 0, 33);
		return File.Read((TCHAR *)(const TCHAR *)m_NameData, m_RecordSize);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.Write((const TCHAR *)m_NameData, 32);
	}


  public:
	/* Class Constructors/Destructors */
	CEsmSubName32() {
		memset(m_NameData, 0, 33);
	}

	//virtual ~CEsmSubName32() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		Destroy();
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = 32;
		SetName(((CEsmSubName32 *)pSubRecord)->GetName());
	}


	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubName32);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		m_RecordSize = 32;
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
		return 32;
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return TSTRNICMP(m_NameData, pID, 32) == 0;
	}

	/* Set class methods */
	void SetName(const TCHAR *pName) {
		memset(m_NameData, 0, 33);
		strnncpy(m_NameData, pName, 32);
	}
};


#endif
