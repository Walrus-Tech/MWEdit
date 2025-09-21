/*===========================================================================
 *
 * File:    Esmsubbase.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "esmsubbase.h"


DEFINE_FILE("EsmSubBase.cpp");


/*===========================================================================
 *
 * Class CEsmSubRecord Constructor
 *
 *=========================================================================*/
CEsmSubRecord::CEsmSubRecord() {
	//DEFINE_FUNCTION("CEsmSubRecord::CEsmSubRecord()");
	SetType(_T("????"));
	m_RecordSize = 0;
	m_pData = NULL;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmSubRecord::Destroy() {
	DEFINE_FUNCTION("CEsmSubRecord::Destroy()");
	DestroyArrayPointer(m_pData);
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - void Copy (pSubRecord);
 *
 *=========================================================================*/
void CEsmSubRecord::Copy(CEsmSubRecord *pSubRecord) {
	DEFINE_FUNCTION("CEsmSubRecord::Copy()");
	Destroy();
	m_Type.SetType(pSubRecord->m_Type);
	m_RecordSize = pSubRecord->m_RecordSize;

	if (pSubRecord->m_pData != NULL) {
		CreateArrayPointer(m_pData, byte, m_RecordSize);
		memcpy(m_pData, pSubRecord->m_pData, m_RecordSize);
	}
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - void CopyData (pData, Size);
 *
 *=========================================================================*/
void CEsmSubRecord::CopyData(char *pData, const int Size) {
	DEFINE_FUNCTION("CEsmSubRecord::CopyData()");
	/* Delete the current data */
	DestroyArrayPointer(m_pData);
	m_RecordSize = 0;

	if (pData == NULL || Size <= 0) {
		return;
	}

	CreateArrayPointer(m_pData, byte, Size);
	memcpy(m_pData, pData, Size);
	m_RecordSize = Size;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - CEsmSubRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmSubRecord *CEsmSubRecord::Create() {
	DEFINE_FUNCTION("CEsmSubRecord::Create()");
	CEsmSubRecord *pSubRecord;
	CreatePointer(pSubRecord, CEsmSubRecord);
	return pSubRecord;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool Find (FindData);
 *
 * Returns true if the given text existing in the sub-record data.  Default
 * implementation does a binary check of the sub-record data (not case
 * sensitive).  Stops searching on the first match.
 *
 *=========================================================================*/
bool CEsmSubRecord::Find(esmfind_t &FindData) {
	int iResult;

	/* Ignore if data is invalid or too small */
	if (m_pData == NULL || GetRecordSize() < FindData.Length) {
		return false;
	}

	/* Find the first occurence of the text in the raw data */
	iResult = memisearch((char *)m_pData, FindData.pText, GetRecordSize(), FindData.Length, 0);

	if (iResult >= 0) {
		return true;
	}

	/* No match */
	return false;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool Read (File);
 *
 * Starts reading the sub-record at the current position in the file (after
 * the sub-record type).  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmSubRecord::Read(CGenFile &File) {
	bool Result;
	/* Delete the current record information, if any */
	Destroy();
	/* Input the record data on success */
	Result = ReadData(File);
	return Result;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool ReadData (File);
 *
 * Virtual protected method that inputs the sub-record data from the file
 * (after the sub-record size).  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmSubRecord::ReadData(CGenFile &File) {
	DEFINE_FUNCTION("CEsmSubRecord::ReadData()");
	bool Result;

	if (m_RecordSize <= 0) {
		return true;
	}

	/* Create the data pointer */
	CreateArrayPointer(m_pData, byte, m_RecordSize);
	Result = File.Read((char *)m_pData, m_RecordSize);
	return Result;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool Write (File);
 *
 * Outputs the entire record to the given file. Returns false on any error.
 *
 *=========================================================================*/
bool CEsmSubRecord::Write(CGenFile &File) {
	bool Result;
	Result = WriteHeader (File);
	Result &= WriteData (File);
	return Result;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool WriteData (File);
 *
 * Protected virtual method that outputs the record data.  The base class
 * method only outputs the record if is is an unknown type.  Returns false
 * on any error.
 *
 *=========================================================================*/
bool CEsmSubRecord::WriteData(CGenFile &File) {
	bool Result;

	/* Don't output anything if we don't have any data */
	if (m_pData == NULL) {
		Result = File.Seek(m_RecordSize, SEEK_CUR);
	} else {
		Result = File.Write((char *)m_pData, m_RecordSize);
	}

	return Result;
}


/*===========================================================================
 *
 * Class CEsmSubRecord Method - bool WriteHeader (File);
 *
 * Protected virtual method that outputs the sub-record header to the current
 * position in the file.  Returns false on any error.
 *
 *=========================================================================*/
bool CEsmSubRecord::WriteHeader(CGenFile &File) {
	bool Result;
	Result = File.Write(m_Type.pType, MWESM_TYPE_SIZE);
	Result &= File.WriteLong(GetRecordSize());
	return Result;
}
