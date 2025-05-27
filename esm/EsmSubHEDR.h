/*===========================================================================
 *
 * File:    EsmSubHEDR.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBHEDR_H
#define __ESMSUBHEDR_H


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
 * Begin Definitions
 *
 *=========================================================================*/

/* Header string sizes */
#define MWESM_HEDR_AUTHORSIZE 32
#define MWESM_HEDR_DESCSIZE   256

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	float Version;
	long Unknown1;
	char Author[MWESM_HEDR_AUTHORSIZE];
	char Description[MWESM_HEDR_DESCSIZE];
	long NumRecords;
} headerdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubHEDR Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubHEDR : public CEsmSubRecord {

	/*---------- Begin Proected Class Members ---------------------*/
  protected:
	headerdata_t m_Data;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData(CGenFile &File) {
		return File.Read((char *)&m_Data, m_RecordSize);
	}

	virtual bool WriteData(CGenFile &File) {
		return File.Write((char *)&m_Data, m_RecordSize);
	}


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubHEDR();
	//virtual ~CEsmSubHEDR() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();
		m_Data = *((CEsmSubHEDR *)pSubRecord)->GetHeaderData();
	}

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubHEDR);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		m_RecordSize = sizeof(headerdata_t);
		memset(&m_Data, 0, sizeof(headerdata_t));
		m_Data.Version = 1.0;
		m_Data.NumRecords = 1;
	}

	/* Get class members */
	headerdata_t *GetHeaderData(void) {
		return (&m_Data);
	}

	float GetVersion(void) {
		return (GetHeaderData()->Version);
	}

	long GetUnknown(void) {
		return (GetHeaderData()->Unknown1);
	}

	const char *GetAuthor(void) {
		return (GetHeaderData()->Author);
	}

	const char *GetDescription(void) {
		return (GetHeaderData()->Description);
	}

	long GetNumRecords(void) {
		return (GetHeaderData()->NumRecords);
	}

	/* Set class members */
	void SetVersion(const float Value) {
		GetHeaderData()->Version = Value;
	}

	void SetNumRecords(const long Value) {
		GetHeaderData()->NumRecords = Value;
	}

	void SetUnknown(const long Value) {
		GetHeaderData()->Unknown1 = Value;
	}

	void SetAuthor(const TCHAR *pValue) {
		TSTRNCPY(GetHeaderData()->Author, pValue, MWESM_HEDR_AUTHORSIZE);
	}

	void SetDescription(const TCHAR *pValue) {
		TSTRNCPY(GetHeaderData()->Description, pValue, MWESM_HEDR_DESCSIZE);
	}

};

/*===========================================================================
 *      End of Class CEsmSubHEDR Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmsubname.H
 *=========================================================================*/
