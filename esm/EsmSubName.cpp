/*===========================================================================
 *
 * File:    EsmSubName.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmsubname.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmSubName.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubName Method - void Copy (pSubRecord);
 *
 *=========================================================================*/
void CEsmSubName::Copy(CEsmSubRecord *pSubRecord) {
	Destroy();
	m_Type.SetType(pSubRecord->GetType());
	m_RecordSize = pSubRecord->GetRecordSize();
	m_Name = ((CEsmSubName *)pSubRecord)->GetName();
}

/*===========================================================================
 *      End of Class Method CEsmSubName::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubName Method - CEsmSubRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmSubName::Create(void) {
	DEFINE_FUNCTION("CEsmSubName::Create()");
	CEsmSubRecord *pSubRecord;
	CreatePointer(pSubRecord, CEsmSubName);
	return (pSubRecord);
}


CEsmSubRecord *CEsmSubNameNull::Create(void) {
	DEFINE_FUNCTION("CEsmSubNameNull::Create()");
	CEsmSubRecord *pSubRecord;
	CreatePointer(pSubRecord, CEsmSubNameNull);
	return (pSubRecord);
}

/*===========================================================================
 *      End of Class Method CEsmSubName::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubName Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CEsmSubName::ReadData(CGenFile &File) {
	//DEFINE_FUNCTION("CEsmSubName::ReadData()");
	bool Result;
	m_Name.SetSize(m_RecordSize);
	Result = File.Read((TCHAR *)(const TCHAR*)m_Name, m_RecordSize);

	if (Result) {
		m_Name.UpdateLength();
	}

	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmSubName::Read()
 *=========================================================================*/
