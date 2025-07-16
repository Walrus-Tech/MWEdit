/*===========================================================================
 *
 * File:    Esmsubname.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBNAME_H
#define __ESMSUBNAME_H


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
 * Begin Class CEsmSubName Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubName : public CEsmSubRecord {

	/*---------- Begin Proected Class Members ---------------------*/
  protected:
	CSString m_Name;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData(CGenFile &File);
	virtual bool WriteData(CGenFile &File) {
		if (GetRecordSize() <= 0) {
			return true;
		}

		return File.Write((const TCHAR *)m_Name, GetRecordSize());
	}


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubName();
	//virtual ~CEsmSubName() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord);

	/* Create a name object */
	static CEsmSubRecord *Create();

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return m_Name.FindI(FindData.pText) >= 0;
	}

	/* Get class methods */
	const TCHAR *GetName() const {
		return m_Name;
	}

	virtual long GetRecordSize() const {
		if (m_Name.GetLength() == 32) {
			return 32;
		}

		return m_Name.GetLength() + 1;
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


/* Force null termination */
class CEsmSubNameNull : public CEsmSubName {
  public:

	/* Create a name object */
	static CEsmSubRecord *Create();

	/* Get record length */
	virtual long GetRecordSize() const {
		return m_Name.GetLength() + 1;
	}
};

/*===========================================================================
 *      End of Class CEsmSubName Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubname.H
 *=========================================================================*/
