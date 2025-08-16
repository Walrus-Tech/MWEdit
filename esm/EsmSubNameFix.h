/*===========================================================================
 *
 * File:    EsmsubNameFix.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNAMEFIX_H
#define __ESMSUBNAMEFIX_H


#include "EsmSubBase.h"
#include "EsmSubName.h"
#include "string/SString.h"


typedef CEsmSubName CEsmSubNameFix;

#if FALSE

/*===========================================================================
 *
 * Begin Class CEsmSubNameFix Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubNameFix : public CEsmSubRecord {
  protected:
	CSString m_Name;


	/* Helper input methods */
	virtual bool ReadData(CGenFile &File) {
		m_Name.SetSize(m_RecordSize);
		bool Result = File.Read((TCHAR *)(const TCHAR *)m_Name, m_RecordSize);
		m_Name.UpdateLength();
		return Result;
	}

	virtual bool WriteData(CGenFile &File) {
		if (GetRecordSize() <= 0) {
			return true;
		}

		return File.Write((const TCHAR *)m_Name, GetRecordSize());
	}


  public:
	/* Class Constructors/Destructors */
	//CEsmSubNameFix() { m_MaxSize = MWESM_ID_MAXSIZE; }
	//virtual ~CEsmSubNameFix() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		Destroy();
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		m_Name = ((CEsmSubNameFix *)pSubRecord)->GetName();
	}


	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNameFix);
		return pSubRecord;
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return m_Name.FindI(FindData.pText);
	}

	/* Get class methods */
	const TCHAR *GetName() const {
		return m_Name;
	}

	virtual long GetRecordSize() const {
		return (m_Name.GetLength() >= MWESM_ID_MAXSIZE - 1) ? MWESM_ID_MAXSIZE :
		       (m_Name.GetLength() + 1);
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return m_Name.CompareNoCase(pID) == 0;
	}

	/* Set class methods */
	void SetName(const TCHAR *pName) {
		m_Name = pName;
		m_RecordSize = m_Name.GetLength();
	}
};


#endif

#endif
