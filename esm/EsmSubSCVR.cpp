/*===========================================================================
 *
 * File:    EsmSubSCVR.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 * 18 October 2003
 *  - Added the Fine() virtual method.
 *
 *=========================================================================*/

/* Include Files */
#include "EsmSubSCVR.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmSubSCVR.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - void Copy (pSubRecord);
 *
 *=========================================================================*/
void CEsmSubSCVR::Copy(CEsmSubRecord* pSubRecord) {
	Destroy();
	m_Type.SetType(pSubRecord->GetType());
	m_RecordSize = pSubRecord->GetRecordSize();
	memcpy(&m_FuncData, ((CEsmSubSCVR *)pSubRecord)->GetInfoFuncData(), sizeof(infofuncdata_t));
	m_StringLength = strlen(m_FuncData.Name);
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - bool Find (FindData);
 *
 * Returns true if the given text existing in the sub-record data.  Default
 * implementation does a binary check of the sub-record data (not case
 * sensitive).  Stops searching on the first match.
 *
 *=========================================================================*/
bool CEsmSubSCVR::Find(esmfind_t &FindData) {
	int iResult;

	/* Ignore if data is invalid or too small */
	if (m_pData == NULL || GetRecordSize() < FindData.Length) {
		return (false);
	}

	/* Find the first occurence of the text in the name */
	iResult = memisearch((char *)GetName(), FindData.pText, GetNameLength(), FindData.Length, 0);

	if (iResult >= 0) {
		return (true);
	}

	/* No match */
	return (false);
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - bool IsUsed (pID);
 *
 *=========================================================================*/
bool CEsmSubSCVR::IsUsed(const TCHAR *pID) {
	return (StringCompare(GetName(), pID, false) == 0);
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::IsUsed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CEsmSubSCVR::ReadData(CGenFile &File) {
	//DEFINE_FUNCTION("CEsmSubSCVR::ReadData()");
	bool Result;
	Result = File.Read((char *)&m_FuncData, m_RecordSize);
	m_StringLength = m_RecordSize - MWESM_SCVR_BASESIZE;
	m_FuncData.Name[m_StringLength] = NULL_CHAR;
	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - void SetName (pString);
 *
 *=========================================================================*/
void CEsmSubSCVR::SetName(const TCHAR *pString) {
	if (pString == NULL) {
		m_StringLength = 0;
		m_FuncData.Name[0] = NULL_CHAR;
	} else {
		m_StringLength = strlen(pString);

		if (m_StringLength > MWESM_SCVR_IDSIZE) {
			m_StringLength = MWESM_SCVR_IDSIZE;
		}

		strncpy(m_FuncData.Name, pString, MWESM_SCVR_IDSIZE);
	}
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::SetName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmSubSCVR Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CEsmSubSCVR::WriteData(CGenFile &File) {
	//DEFINE_FUNCTION("CEsmSubSCVR::WriteData()");
	bool Result;
	m_RecordSize = MWESM_SCVR_BASESIZE + m_StringLength;
	Result = File.Write((char *)&m_FuncData, m_RecordSize);
	return (Result);
}

/*===========================================================================
 *      End of Class Method CEsmSubSCVR::WriteData()
 *=========================================================================*/
