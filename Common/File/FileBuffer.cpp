/*===========================================================================
 *
 * File:    Filebuffer.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, December 05, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "filebuffer.h"
#include "dl_file.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("FileBuffer.cpp");


/*===========================================================================
 *
 * Class CFileBuffer Constructor
 *
 *=========================================================================*/
CFileBuffer::CFileBuffer() {
	DEFINE_FUNCTION("CFileBuffer::CFileBuffer()");
	m_pFile = NULL;
	m_Attached = false;
	m_FileIndex = 0;
	m_BufferIndex = 0;
	/* Create the initial data buffer */
	CreateArrayPointer(m_pBuffer, char, FILEBUF_DEFAULT_BUFFER_SIZE);
	m_BufferSize = 0;
	m_MaxBufferSize = FILEBUF_DEFAULT_BUFFER_SIZE;
}


/*===========================================================================
 *
 * Class CFileBuffer Destructor
 *
 *=========================================================================*/
CFileBuffer::~CFileBuffer() {
	DEFINE_FUNCTION("CFileBuffer::~CFileBuffer()");
	Destroy();
	DestroyArrayPointer(m_pBuffer);
}


/*===========================================================================
 *
 * Class CFileBuffer Method - void Destroy (void);
 *
 *=========================================================================*/
void CFileBuffer::Destroy() {
	//DEFINE_FUNCTION("CFileBuffer::Destroy()");
	/* Ensure the file is properly closed */
	Close();
}


/*===========================================================================
 *
 * Class CFileBuffer Method - void Attach (pFile);
 *
 * Attaches an existing file handle to the file buffer. The current file
 * is closed.
 *
 *=========================================================================*/
void CFileBuffer::Attach(FILE *pFile) {
	/* Close the current file, if any */
	Close();
	m_Attached = true;
	m_pFile = pFile;
	m_FileIndex = ftell(m_pFile);
}


/*===========================================================================
 *
 * Class CFileBuffer Method - void Close (void);
 *
 * Closes any open file, or detachs it as needed.
 *
 *=========================================================================*/
void CFileBuffer::Close() {
	/* Detach the handle if we don't own it */
	if (m_Attached) {
		m_pFile = NULL;
		m_Attached = false;
	} else if (m_pFile != NULL) { /* Close the file if it is open */
		fclose(m_pFile);
		m_pFile = NULL;
	}

	m_BufferSize = 0;
	m_FileIndex = 0;
	m_BufferIndex = 0;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool GetData_Priv (Size);
 *
 * Ensures that at least hte given amount of data is available in the file
 * buffer. Reads more in if required. Returns false if the requested amount
 * is not available. Protected class method.
 *
 * Only call from the GetData() method.
 *
 *=========================================================================*/
bool CFileBuffer::GetData_Priv(const int Size) {
	int ReadSize;
	int Result;

	/* Ignore invalid input */
	if (Size <= 0) {
		return true;
	}

	/* Too much data for one read? */
	if (Size > m_MaxBufferSize) {
		ErrorHandler.AddError(ERR_MAXINDEX,
		                      _T("Cannot request for more than the file buffer size!"));
		return false;
	}

	/* Is the file handle valid? */
	if (m_pFile == NULL) {
		ErrorHandler.AddError(ERR_MAXINDEX, _T("File buffer not currently open!"));
		return false;
	} else if (feof(m_pFile)) {
		ErrorHandler.AddError(ERR_MAXINDEX, _T("End-of-file reached in file buffer!"));
		return false;
	}

	/* Shift data in preparation for a read */
	memmove(m_pBuffer, m_pBuffer + m_BufferIndex, m_BufferSize - m_BufferIndex);
	ReadSize = m_BufferIndex + (m_MaxBufferSize - m_BufferSize);
	m_BufferSize -= m_BufferIndex;
	m_BufferIndex = 0;
	m_FileIndex = ftell(m_pFile) - m_BufferSize;

	/* Attempt to read the data  */
	Result = fread(m_pBuffer + m_BufferSize, 1, ReadSize, m_pFile);
	m_BufferSize += Result;

	/* Have we read enough data? */
	if (Size > m_BufferSize) {
		ErrorHandler.AddError(ERR_BADINPUT, _T("Not enough data in file for requested amount!"));
		return false;
	}

	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool Open (pFilename, pMode);
 *
 * Opens a file for buffered input. Returns false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::Open(const TCHAR *pFilename, const TCHAR *pMode) {
	bool Result;
	/* Close the current file, if any */
	Close();
	/* Attempt to open the file in the given mode */
	Result = OpenFile(&m_pFile, pFilename, pMode);

	if (!Result) {
		return false;
	}

	m_FileIndex = 0;
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool Read (pData, Size);
 *
 * Read a set amount of data from the buffer. Returns false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::Read(char *pData, const int Size) {
	bool Result;
	/* Ensure the requested amount of data can be provided */
	Result = GetData(Size);

	if (!Result) {
		return false;
	}

	/* Copy the data */
	memcpy(pData, m_pBuffer + m_BufferIndex, Size);
	m_BufferIndex += Size;
	m_FileIndex += Size;
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool ReadChar (InputChar);
 *
 * Input a character from the buffer, returning false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::ReadChar(char &InputChar) {
	bool Result;
	/* Ensure there's enough required data */
	Result = GetData(1);

	if (!Result) {
		return false;
	}

	/* Get the character, modify file pointers */
	InputChar = m_pBuffer[m_BufferIndex];
	m_BufferIndex++;
	m_FileIndex++;
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool ReadData (pData, Size);
 *
 * Read a set amount of data from the buffer. Use when the amount of data
 * to be read exceeds the buffer size. Returns false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::ReadData(char *pData, const int Size) {
	bool Result;
	int ReadSize = 0;
	int CopySize;

	/* Read data until the requested amount is available */
	while (ReadSize < Size) {
		/* Copy the current data in the buffer */
		CopySize = m_BufferSize - m_BufferIndex;

		if (CopySize + ReadSize > Size) {
			CopySize = Size - ReadSize;
		}

		memcpy(pData + ReadSize, m_pBuffer + m_BufferIndex, CopySize);
		ReadSize += CopySize;
		m_BufferIndex += CopySize;
		m_FileIndex += CopySize;
		/* Read in more data */
		Result = GetData(m_BufferIndex);

		if (!Result) {
			return false;
		}
	}

	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool ReadInt (InputValue);
 *
 * Input an integer from the buffer, returning false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::ReadInt(int &InputValue) {
	bool Result;
	/* Ensure there's enough required data */
	Result = GetData(sizeof(int));

	if (!Result) {
		return false;
	}

	/* Get the value, modify file pointers */
	InputValue = *(int *)(m_pBuffer + m_BufferIndex);
	m_BufferIndex += sizeof(int);
	m_FileIndex += sizeof(int);
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool ReadLong (InputValue);
 *
 * Input a long integer from the buffer, returning false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::ReadLong(long &InputValue) {
	bool Result;
	/* Ensure there's enough required data */
	Result = GetData(sizeof(long));

	if (!Result) {
		return false;
	}

	/* Get the value, modify file pointers */
	InputValue = *(long *)(m_pBuffer + m_BufferIndex);
	m_BufferIndex += sizeof(long);
	m_FileIndex += sizeof(long);
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - bool ReadShort (InputValue);
 *
 * Input a short integer from the buffer, returning false on any error.
 *
 *=========================================================================*/
bool CFileBuffer::ReadShort(short &InputValue) {
	bool Result;
	/* Ensure there's enough required data */
	Result = GetData(sizeof(short));

	if (!Result) {
		return false;
	}

	/* Get the value, modify file pointers */
	InputValue = *(short *)(m_pBuffer + m_BufferIndex);
	m_BufferIndex += sizeof(short);
	m_FileIndex += sizeof(short);
	return true;
}


/*===========================================================================
 *
 * Class CFileBuffer Method - void SetBufferSize (Size);
 *
 * Sets the size of the data buffer. Zero or negative sizes are ignored.
 * Any currently buffered data maybe truncated if the size is smaller than
 * the current buffer size.
 *
 *=========================================================================*/
void CFileBuffer::SetBufferSize(const int Size) {
	DEFINE_FUNCTION("CFileBuffer::SetBufferSize()");
	char *pNewBuffer;
	int NewBufferSize;

	/* Ignore invalid input */
	if (Size <= 0) {
		return;
	}

	/* Create the new buffer */
	CreateArrayPointer(pNewBuffer, char, Size);

	/* Copy any current data into the new buffer */
	if (Size < m_BufferSize) {
		memcpy(pNewBuffer, m_pBuffer, Size);
		NewBufferSize = Size;
	} else {
		memcpy(pNewBuffer, m_pBuffer, m_BufferSize);
		NewBufferSize = m_BufferSize;
	}

	/* Destroy the old buffer data */
	DestroyArrayPointer(m_pBuffer);
	m_pBuffer = pNewBuffer;
	m_MaxBufferSize = Size;
	m_BufferSize = NewBufferSize;
}
