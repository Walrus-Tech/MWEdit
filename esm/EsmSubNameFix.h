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


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
#include "EsmSubName.h"
#include "string/SString.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/

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

	/*---------- Begin Proected Class Members ---------------------*/
  protected:
	CSString m_Name;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData(CGenFile &File) {
		m_Name.SetSize(m_RecordSize);
		bool Result = File.Read((TCHAR *)(const TCHAR *)m_Name, m_RecordSize);
		m_Name.UpdateLength();
		return (Result);
	}

	virtual bool WriteData(CGenFile &File) {
		if (GetRecordSize() <= 0) {
			return (true);
		}

		return File.Write((const TCHAR *)m_Name, GetRecordSize());
	}


	/*---------- Begin Public Class Methods -----------------------*/
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
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubNameFix);
		return (pSubRecord);
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return (m_Name.FindI(FindData.pText));
	}

	/* Get class methods */
	const TCHAR *GetName(void) const {
		return (m_Name);
	}

	virtual long GetRecordSize(void) const {
		return ((m_Name.GetLength() >= MWESM_ID_MAXSIZE - 1) ? MWESM_ID_MAXSIZE :
		        (m_Name.GetLength() + 1));
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID) {
		return (m_Name.CompareNoCase(pID) == 0);
	}

	/* Set class methods */
	void SetName(const TCHAR *pName) {
		m_Name = pName;
		m_RecordSize = m_Name.GetLength();
	}

};

/*===========================================================================
 *      End of Class CEsmSubNameFix Definition
 *=========================================================================*/
#endif

#endif
/*===========================================================================
 *      End of File EsmSubNameFix.H
 *=========================================================================*/
