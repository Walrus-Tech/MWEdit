/*===========================================================================
 *
 * File:    GenFile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, May 17, 2001
 *
 * Contains the definition of the CGenFile class which contains the basic
 * file stream I/O handling.
 *
 *=========================================================================*/
#ifndef __GENFILE_H
#define __GENFILE_H

/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include <stdarg.h>
#include "dl_file.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type and Structure Definitions
 *
 *=========================================================================*/

/* Used to indicate a position in a file stream */
typedef long filepos_t;

/*===========================================================================
 *      End of Type and Structure Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CGenFile Definition
 *
 * Encapsulates basic file stream I/O operations, helping to reduce the
 * apparent complexity of source code.
 *
 *=========================================================================*/
class CGenFile {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	FILE *m_pFileHandle;      /* The file stream handle */
	bool m_Attached;     /* Indicates the stream should not be closed */
	long m_LineCount;        /* Used to track lines in file */


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors */
	CGenFile();
	CGenFile(FILE* pSourceHandle);
	CGenFile(const char* pFilename, const char* pMode);

	/* Class destructors */
	virtual ~CGenFile();
	virtual void Destroy (void);

	/* Attach to an existing file stream */
	void Attach (FILE* pFileHandle);
	void Detach (void);

	/* Clears the error flag of the stream */
	void ClearError (void);

	/* Close an opened file stream */
	virtual void Close (void);

	/* Creates a new temporary file */
	bool CreateTemp (void);

	/* Attempt to flush a file stream buffer */
	bool Flush (void);

	/* Return the file handle for object */
	FILE *GetHandle (void);

	/* Return the file size for the current file */
	long GetFileSize (void);
	bool GetFileSize (long &FileSize);

	/* Class status methods */
	bool IsOpen (void);
	bool IsEOF (void);
	bool IsError (void);

	/* Line count methods */
	long DecLineCount (void) {
		return (--m_LineCount);
	}

	long IncLineCount (void) {
		return (++m_LineCount);
	}

	void SetLineCount (const long Value) {
		m_LineCount = Value;
	}

	long GetLineCount (void) const {
		return (m_LineCount);
	}

	/* Attempt to open the given filename */
	virtual bool Open (const char* pFilename, const char* pMode);

	/* Output formatted string to file stream */
	bool Printf (const char* pString, ...);
	bool VPrintf (const char* pString, va_list Args);

	/* Attempt to read a section from the file */
	bool Read (char* pBuffer, size_t &BytesRead, const size_t NumBytes);
	bool Read (char* pBuffer, const size_t NumBytes);
	bool ReadEx (char* pBuffer, const size_t Size, const size_t Count);

	/* Read a line */
	int ReadLine (char* pBuffer = NULL, const size_t MaxStringLength = 0);

	/* Input a character from the file stream */
	bool ReadChar (char &Char);

	/* Read binary integers */
	bool ReadShort (short &Value);
	bool ReadInt (int &Value);
	bool ReadLong (long &Value);
	bool ReadFloat (float &Value);

	/* Move the file position to the file beginning */
	void Rewind (void);

	/* Move the current file position */
	bool Seek (const filepos_t Position, const int SeekType);

	/* Get the current file position */
	filepos_t Tell (void);
	bool Tell (filepos_t &Position);

	/* Attempt to write a section to the file */
	bool Write (const char* pBuffer, size_t &BytesWritten, const size_t NumBytes);
	bool Write (const char* pBuffer, const size_t NumBytes);
	bool WriteEx (const char* pBuffer, const size_t Size, const size_t Count);

	/* Output a character to the file */
	bool WriteChar (const char Char);

	/* Write binary integers */
	bool WriteShort (const short Value);
	bool WriteInt (const int Value);
	bool WriteLong (const long Value);
	bool WriteFloat (const float Value);

	/* FILE* type conversion operator */
	operator FILE* (void);

};

/*===========================================================================
 *      End of Class CGenFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CGenFile Inline Methods
 *
 *=========================================================================*/

/* Class constructors */
inline CGenFile::CGenFile() {
	m_pFileHandle = NULL;
	m_Attached = FALSE;
}

inline CGenFile::CGenFile(FILE* pSourceHandle) {
	m_pFileHandle = pSourceHandle;
	m_Attached = FALSE;
}

inline CGenFile::CGenFile(const char* pFilename, const char* pMode) {
	m_pFileHandle = NULL;
	m_Attached = FALSE;
	m_LineCount = 0;
	Open(pFilename, pMode);
}

/* Class destructor */
inline CGenFile::~CGenFile() {
	Destroy();
}

/* Class pseudo-destructor */
inline void CGenFile::Destroy (void) {
	Close();
}

/* Attach to an existing file stream */
inline void CGenFile::Attach (FILE* pFileHandle) {
	IASSERT(pFileHandle != NULL);
	Close();
	m_Attached = TRUE;
	m_pFileHandle = pFileHandle;
}

/* Unattached to an existing file stream */
inline void CGenFile::Detach (void) {
	if (m_Attached) {
		m_Attached = FALSE;
		m_pFileHandle = NULL;
	}
}

/* Clears the error flag of the file stream */
inline void CGenFile::ClearError (void) {
	IASSERT(m_pFileHandle != NULL);
	clearerr(m_pFileHandle);
}

/* Close the file stream, if it is open */
inline void CGenFile::Close (void) {
	if (IsOpen()) {
		if (!m_Attached) {
			fclose(m_pFileHandle);
		}

		m_pFileHandle = NULL;
	}

	m_Attached = FALSE;
}

/* Creates a new temporary file for output */
inline bool CGenFile::CreateTemp (void) {
	Close();
	m_pFileHandle = tmpfile();

	if (m_pFileHandle == NULL) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to create temporary file!");
		return (FALSE);
	}

	return (TRUE);
}

inline bool CGenFile::Flush (void) {
	IASSERT(IsOpen());

	if (fflush(m_pFileHandle) != 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to flush file stream!");
		return (FALSE);
	}

	return (TRUE);
}

/* Return the file handle for object */
inline FILE *CGenFile::GetHandle (void) {
	return (m_pFileHandle);
}

/* Return the file size */
inline long CGenFile::GetFileSize (void) {
	IASSERT(IsOpen());
	return ::GetFileSize(m_pFileHandle);
}

/* Retrieve the file size with error status */
inline bool CGenFile::GetFileSize (long &FileSize) {
	IASSERT(IsOpen());
	return ::GetFileSize(FileSize, m_pFileHandle);
}

/* Returns TRUE if the EOF has been reached */
inline bool CGenFile::IsEOF (void) {
	if (!IsOpen() || feof(m_pFileHandle)) {
		return (TRUE);
	}

	return (FALSE);
}

/* Returns TRUE if the file stream has an error */
inline bool CGenFile::IsError (void) {
	if (!IsOpen() || ferror(m_pFileHandle)) {
		return (TRUE);
	}

	return (FALSE);
}

/* Returns TRUE if the file stream is currently open */
inline bool CGenFile::IsOpen (void) {
	return (bool) ((m_pFileHandle == NULL) ? FALSE : TRUE);
}

/* Open a file as with the fopen() function */
inline bool CGenFile::Open (const char* pFilename, const char* pMode) {
	Close();
	m_LineCount = 0;
	return OpenFile(&m_pFileHandle, pFilename, pMode);
}

/* Output a formatted string to file */
inline bool CGenFile::Printf (const char* pString, ...) {
	va_list Args;
	bool Result;
	IASSERT(pString != NULL);
	va_start(Args, pString);
	Result = VPrintf(pString, Args);
	va_end(Args);
	return (Result);
}

/* Output a formatted string to file using a variable argument list */
inline bool CGenFile::VPrintf (const char* pString, va_list Args) {
	IASSERT(pString != NULL);

	/* Ensure file is open for output */
	if (!IsOpen()) {
		ErrorHandler.AddError(ERR_WRITEFILE, "File is not open!");
		return (FALSE);
	}

	/* Output formatted string to file */
	if (vfprintf(m_pFileHandle, pString, Args) < 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Error outputting a formatted string to file!");
		return (FALSE);
	}

	return (Flush());
}

/* Read a section from the file */
inline bool CGenFile::Read (char* pBuffer, size_t &BytesRead, const size_t NumBytes) {
	IASSERT(pBuffer != NULL && IsOpen());
	/* Attempt to read buffer */
	BytesRead = fread(pBuffer, 1, NumBytes, m_pFileHandle);

	if (BytesRead != NumBytes) {
		ErrorHandler.AddError(ERR_SYSTEM, errno,
		                      "Failed to read section from file, only %u of %u bytes received!", BytesRead, NumBytes);
		return (FALSE);
	}

	return (TRUE);
}

/* Read a section from the file */
inline bool CGenFile::Read (char* pBuffer, const size_t NumBytes) {
	size_t BytesRead;
	return Read(pBuffer, BytesRead, NumBytes);
}

/* Read a section from the file */
inline bool CGenFile::ReadEx (char* pBuffer, const size_t Size, const size_t Count) {
	ulong NumBytes = (ulong) Size * (ulong)Count;
	size_t BytesRead;

	/* Ensure valid input size */
	if (NumBytes >= (ulong) UINT_MAX) {
		ErrorHandler.AddError(ERR_OVERFLOW, "Exceeded the maximum input size of %ud bytes!", UINT_MAX);
		return (FALSE);
	}

	return Read(pBuffer, BytesRead, (size_t)NumBytes);
}

/* Read a character from the file */
inline bool CGenFile::ReadChar (char &InputChar) {
	IASSERT(IsOpen());
	int Input;
	/* Attempt to read character */
	Input = fgetc(m_pFileHandle);

	if (Input < 0) {
		InputChar = NULL_CHAR;
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to read character from file!");
		return (FALSE);
	}

	InputChar = (char) Input;
	return (TRUE);
}

/* Read one line from the file */
inline int CGenFile::ReadLine (char* pBuffer, const size_t MaxStringLength) {
	IASSERT(IsOpen());
	return (::ReadLine(m_pFileHandle, pBuffer, MaxStringLength));
}

/* Read binary short integer (16 bit) */
inline bool CGenFile::ReadShort (short &Value) {
	return Read((char*)&Value, sizeof(short));
}

/* Read binary integer (size depends on system) */
inline bool CGenFile::ReadInt (int &Value) {
	return Read((char*)&Value, sizeof(int));
}

/* Read binary long integer (32 bit) */
inline bool CGenFile::ReadLong (long &Value) {
	return Read((char*)&Value, sizeof(long));
}

/* Read binary float (32 bit) */
inline bool CGenFile::ReadFloat (float &Value) {
	return Read((char*)&Value, sizeof(float));
}


/* Move to the fiel beginning and clear the stream errors */
inline void CGenFile::Rewind (void) {
	IASSERT(IsOpen());
	rewind(m_pFileHandle);
}

/* Move the current file position as per fseek() */
inline bool CGenFile::Seek (const filepos_t Position, const int SeekType) {
	IASSERT(IsOpen());

	if (fseek(m_pFileHandle, Position, SeekType) != 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to change the current file position!");
		return (FALSE);
	}

	return (TRUE);
}

/* Retrieve the current file position as per ftell() */
inline bool CGenFile::Tell (filepos_t &Position) {
	IASSERT(IsOpen());
	Position = ftell(m_pFileHandle);

	if (Position < 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to retrieve the current file position!");
		return (FALSE);
	}

	return (TRUE);
}

/* Retrieve the current file position as per ftell() */
inline filepos_t CGenFile::Tell (void) {
	filepos_t Position;
	Tell(Position);
	return (Position);
}

/* Write a section to the file */
inline bool CGenFile::Write (const char* pBuffer, size_t &BytesWritten, const size_t NumBytes) {
	IASSERT(pBuffer != NULL && IsOpen());
	/* Attempt to read buffer */
	BytesWritten = fwrite(pBuffer, 1, NumBytes, m_pFileHandle);

	if (BytesWritten != NumBytes) {
		ErrorHandler.AddError(ERR_SYSTEM, errno,
		                      "Failed to write section to file, only %u of %u bytes output!", BytesWritten, NumBytes);
		return (FALSE);
	}

	return (TRUE);
}

/* Write a section to the file */
inline bool CGenFile::Write (const char* pBuffer, const size_t NumBytes) {
	size_t BytesWritten;
	return Write(pBuffer, BytesWritten, NumBytes);
}

/* Write a section to the file */
inline bool CGenFile::WriteEx (const char* pBuffer, const size_t Size, const size_t Count) {
	ulong NumBytes = (ulong) Size * (ulong)Count;
	size_t BytesWritten;

	/* Ensure valid input size */
	if (NumBytes >= (ulong) UINT_MAX) {
		ErrorHandler.AddError(ERR_OVERFLOW, "Exceeded the maximum output size of %ud bytes!", UINT_MAX);
		return (FALSE);
	}

	return Write(pBuffer, BytesWritten, (size_t)NumBytes);
}

/* Write a character to the file */
inline bool CGenFile::WriteChar (const char Char) {
	IASSERT(IsOpen());

	/* Attempt to write character */
	if ( fputc((int) Char, m_pFileHandle) < 0 ) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Failed to write character to file!");
		return (FALSE);
	}

	return (TRUE);
}

/* Write binary short integer (16 bit) */
inline bool CGenFile::WriteShort (const short Value) {
	short TempValue = Value;
	return Write((char*)&TempValue, sizeof(short));
}

/* Write binary integer (size depends on system) */
inline bool CGenFile::WriteInt (const int Value) {
	int TempValue = Value;
	return Write((char*)&TempValue, sizeof(int));
}

/* Write binary long integer (32 bit) */
inline bool CGenFile::WriteLong (const long Value) {
	long TempValue = Value;
	return Write((char*)&TempValue, sizeof(long));
}

/* Write binary float (32 bit) */
inline bool CGenFile::WriteFloat (const float Value) {
	float TempValue = Value;
	return Write((char*)&TempValue, sizeof(float));
}

/* Class FILE* type conversion operator */
inline CGenFile::operator FILE* (void) {
	return (m_pFileHandle);
}

/*===========================================================================
 *      End of Class CGenFile Inline Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Test Routine Prototypes
 *
 *=========================================================================*/
#if defined(_DEBUG)
	#define TEST_GENFILE_SEEKFILESIZE 10000
	#define TEST_GENFILE_RWNUMSIZE  1000

	void Test_RWGenFile (const size_t NumTests = 100);
	void Test_RWCharGenFile (const size_t NumTests = 20);
	void Test_GenFileRWNumbers (const size_t NumTests = 1000);
	void Test_GenFileSeekTell (const size_t NumTests = 1000);
	void Test_GenFilePrint (void);
	void Test_GenFile (void);
#endif
/*===========================================================================
 *      End of Test Routine Prototypes
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Genfile.H
 *=========================================================================*/
