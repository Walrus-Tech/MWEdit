/*===========================================================================
 *
 * File:    Xmlfile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "xmlfile.h"
#include <windows.h>


DEFINE_FILE("XmlFile.cpp");


/*===========================================================================
 *
 * Function - int l_ReadCallBack (FileSize, BytesRead, pUserData);
 *
 *=========================================================================*/
int l_ReadCallBack(const long FileSize, const long BytesRead, void *pUserData) {
	return ((CXmlFile *)pUserData)->OnReadCallback(FileSize, BytesRead);
}


/*===========================================================================
 *
 * Class CXmlFile Constructor
 *
 *=========================================================================*/
CXmlFile::CXmlFile() {
	//DEFINE_FUNCTION("CXmlFile::CXmlFile()");
	m_RootElement.SetIsRoot(true);
	m_LineCount = 0;
	m_CallBackFunc = NULL;
	memset(&m_CallBackInfo, 0, sizeof(m_CallBackInfo));
}


/*===========================================================================
 *
 * Class CXmlFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CXmlFile::Destroy() {
	//DEFINE_FUNCTION("CXmlFile::Destroy()");
	m_RootElement.Destroy();
	m_File.Destroy();
	m_LineCount = 0;
}


/*===========================================================================
 *
 * Class CXmlFile Event - int OnReadCallback (FileSize, BytesRead);
 *
 *=========================================================================*/
int CXmlFile::OnReadCallback(const long FileSize, const long BytesRead) {
	m_CallBackInfo.FileSize = FileSize;
	m_CallBackInfo.BytesParsed = BytesRead;

	if (FileSize == 0) {
		m_CallBackInfo.PercentDone = 0;
	} else {
		m_CallBackInfo.PercentDone = (float)BytesRead * 50.0f / (float)FileSize;
	}

	if (m_CallBackFunc != NULL) {
		return m_CallBackFunc(&m_CallBackInfo);
	}

	return 0;
}


/*===========================================================================
 *
 * Class CXmlFile Method - bool Read (pFilename);
 *
 * Attempt to input and parse the given XML file by reading the entire
 * file into a buffer and parsing it.  Returns false on any error.
 *
 *=========================================================================*/
bool CXmlFile::Read(const TCHAR *pFilename) {
	TCHAR *pFileBuffer;
	size_t BytesRead;
	int FilePos;
	int CBResult;
	bool Result;
	/* Delete the current contents */
	Destroy();

	/* Update the callback information */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.BytesParsed = 0;
		m_CallBackInfo.EventCode = XMLFILE_CBCODE_READSTART;
		m_CallBackInfo.FileSize = 0;
		m_CallBackInfo.LineCount = 0;
		m_CallBackInfo.pCurrentElem = NULL;
		m_CallBackInfo.pMessage = pFilename;
		m_CallBackInfo.PercentDone = 0;
		CBResult = m_CallBackFunc(&m_CallBackInfo);

		if (CBResult < 0) {
			return false;
		}
	}

	/* Attempt to input file all at once */
	Result = ReadFileCB((byte **)&pFileBuffer, BytesRead, pFilename, l_ReadCallBack, this);

	//Result = ReadFile((byte**)&pFileBuffer, BytesRead, pFilename, false);
	if (!Result) {
		return false;
	}

	m_Filename = pFilename;

	/* Update the callback information */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.EventCode = XMLFILE_CBCODE_READDONE;
		m_CallBackInfo.FileSize = BytesRead;
		CBResult = m_CallBackFunc(&m_CallBackInfo);

		if (CBResult < 0) {
			return false;
		}
	}

	/* Start parsing the buffer */
	FilePos = 0;
	Result = m_RootElement.Read(pFileBuffer, FilePos, BytesRead, m_LineCount);

	if (FilePos != (int)BytesRead) {
		//ErrorHandler.AddError(ERR_READFILE, _T("Possible under read of XML file (%d bytes)!"), BytesRead - FilePos);
	}

	/* Update the callback information */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.EventCode = XMLFILE_CBCODE_PARSEDONE;
		m_CallBackInfo.BytesParsed = FilePos;
		m_CallBackInfo.PercentDone = 100.0f;
		m_CallBackInfo.LineCount = m_LineCount;
		CBResult = m_CallBackFunc(&m_CallBackInfo);

		if (CBResult < 0) {
			return false;
		}
	}

	DestroyArrayPointer(pFileBuffer);
	return Result;
}


/*===========================================================================
 *
 * Class CXmlFile Method - bool Write (pFilename);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlFile::Write(const TCHAR *pFilename) {
	bool Result;
	int CBResult;

	/* Update the callback information */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.BytesParsed = 0;
		m_CallBackInfo.EventCode = XMLFILE_CBCODE_WRITESTART;
		m_CallBackInfo.FileSize = 0;
		m_CallBackInfo.LineCount = 0;
		m_CallBackInfo.pCurrentElem = NULL;
		m_CallBackInfo.pMessage = pFilename;
		m_CallBackInfo.PercentDone = 0;
		CBResult = m_CallBackFunc(&m_CallBackInfo);

		if (CBResult < 0) {
			return false;
		}
	}

	Result = m_File.Open(pFilename, "wb");
	m_Filename = pFilename;

	if (Result) {
		Result = m_RootElement.Write(m_File);
	}

	/* Update the callback information */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.EventCode = XMLFILE_CBCODE_WRITEDONE;
		m_CallBackInfo.BytesParsed = m_File.Tell();
		m_CallBackInfo.PercentDone = 100.0f;
		CBResult = m_CallBackFunc(&m_CallBackInfo);

		if (CBResult < 0) {
			return false;
		}
	}

	m_File.Close();
	return Result;
}
