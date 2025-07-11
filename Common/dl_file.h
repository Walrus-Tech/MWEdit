/*===========================================================================
 *
 * File:    DL_File.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, May 07, 2001
 *
 * Contains file releated definitions for Dave's Library of common code.
 *
 *=========================================================================*/
#ifndef __DL_FILE_H
#define __DL_FILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_mem.h"
#include "dl_log.h"
#include "dl_err.h"
#include "dl_chr.h"
#include "dl_str.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Size of input/output buffer for the CopyFile() function */
#if defined(__BCPLUSPLUS__)
	#define COPYFILE_BUFFERSIZE 1024u
#elif defined(__TURBOC__)
	#define COPYFILE_BUFFERSIZE 60000u
#else
	#define COPYFILE_BUFFERSIZE 60000u
#endif

/* Number of bytes read at a time for the ReadFileCB() function */
#define READFILECB_NUMBYTES     32000

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin ReadFile()/WriteFile() Mode Definitions
 *
 *=========================================================================*/
#define FILE_BINARY FALSE
#define FILE_TEXT   TRUE
/*===========================================================================
 *      End of ReadFile()/WriteFile() Mode Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin ReadLine() Return Type Definitions
 *
 *=========================================================================*/
#define READLINE_ERROR (-1)
#define READLINE_OK    (0)
#define READLINE_MSL   (1)
#define READLINE_EOF   (2)
/*===========================================================================
*      End of ReadLine() Return Type Definition
*=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* ReadFileCB callback function type */
typedef int (*READFILE_CALLBACK) (const long FileSize, const long BytesRead, void *pUserData);

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Attempt to change directory to the given path */
bool ChangeDirectory(const TCHAR *pPath);

/* Copy filename to a new string, changing it's extensions */
TCHAR *ChangeExtension(TCHAR *pDestFilename,
                       const TCHAR *pSourceFilename,
                       const TCHAR *pNewExtension,
                       const size_t MaxStringLength);

/* Compare the extension with the given filename's extension */
bool CompareExtension(const TCHAR *pFilename, const TCHAR *pExtension);

/* Copy from the source to the destination file */
bool CopyOneFile(const TCHAR *pInputFile, const TCHAR *pOutputFile);

/* Create a properly terminated path string */
TCHAR *CreatePath(TCHAR *pNewPath, const TCHAR *pString, const size_t MaxStringLength);

/* Delete a file */
bool DelOneFile(const TCHAR *pFilename);

/* Copy the filename from a path to a string */
TCHAR *ExtractFilename(TCHAR *pFilename, const TCHAR *pPath, const size_t MaxStringLength);

/* Copy the path from a given string */
TCHAR *ExtractPath(TCHAR *pPath, const TCHAR *pString, const size_t MaxStringLength);

/* Checks to see if a file is available for reading */
bool FileExists(const TCHAR *pFilename);

/* Return a pointer to the extension in a path */
const TCHAR *FindExtension(const TCHAR *pFilename);

/* Return a pointer to the filename in a path */
const TCHAR *FindFilename(const TCHAR *pPath);

/* Retrieve the size of a file in bytes */
long GetFileSize(const TCHAR *pFilename);
long GetFileSize(FILE *pFileHandle);
bool GetFileSize(long &FileSize, const TCHAR *pFilename);
bool GetFileSize(long &FileSize, FILE *pFileHandle);

/* Return the current directory */
TCHAR *GetDirString(TCHAR *pString, const int MaxLength);

/* Returns TRUE if the given file has any extension */
bool HasExtension(const TCHAR *pFilename);

/* Returns TRUE if the given filename contains a path */
bool HasPath(const TCHAR *pFilename);

/* Returns TRUE if the given path is valid but does not change current path */
bool IsDirectory(const TCHAR *pPath);

/* Determines if a file can be written to */
bool IsFileWriteable(const TCHAR *pFilename);

/* Returns TRUE if the given filename contains wildcard TCHARacters */
bool IsWildCard(const TCHAR *pFilename);

/* Makes multiple levels of directories */
bool MakePathEx(const TCHAR *pPath);

/* Create a convienient drive space string */
TCHAR *MakeSpaceLabel(TCHAR *Buffer, const int BufferSize, const double Value);

/* Opens a file with fopen(), recording log and error information */
FILE *OpenFile(const TCHAR *pFilename, const TCHAR *pMode);
bool OpenFile(FILE **ppFileHandle, const TCHAR *pFilename, const TCHAR *pMode);

/* Attempt to read in entire file to a newly allocated pointer */
bool ReadFile(byte **pBuffer,
              size_t &BytesRead,
              const TCHAR *pFilename,
              const bool TextMode = FILE_BINARY);
bool ReadFileCB(byte **pBuffer,
                size_t &BytesRead,
                const TCHAR *pFilename,
                READFILE_CALLBACK CallBackFunc,
                void *pUserData);

/* Read all/part of a file to an existing buffer */
bool ReadFileBuffer(byte **ppBuffer,
                    size_t &BytesRead,
                    const TCHAR *pFilename,
                    const size_t MaxInputSize,
                    const bool TextMode = FILE_BINARY);

/* Reads one line from the given file stream */
int ReadLine(FILE *pFileHandle, TCHAR *pString = NULL, const size_t MaxStringLength = 1);

/* Read integers from a file stream */
bool read_int(FILE *pFileHandle, int &Value);
bool read_long(FILE *pFileHandle, long &Value);
bool read_short(FILE *pFileHandle, short &Value);
bool read_motlong(FILE *pFileHandle, long &Value);

/* Removes any filename extension from the string */
TCHAR *RemoveExtension(TCHAR *pFilename);

/* Ensure the path string ends in the current path TCHARacter */
TCHAR *TerminatePath(TCHAR *pPath);

/* Output a data buffer to a file */
bool WriteFile(const byte *pBuffer,
               const size_t Size,
               const TCHAR *pFilename,
               const bool TextMode = FILE_BINARY);

/* Write integers to a file stream */
bool write_short(FILE *pFileHandle, const short OutputValue);
bool write_int(FILE *pFileHandle, const int OutputValue);
bool write_long(FILE *pFileHandle, const long OutputValue);
bool write_motlong(FILE *pFileHandle, const long OutputValue);

/* Compare a filename against a wildcard filter */
bool WildcardCompare(const TCHAR *pFilename, const TCHAR *pFilter);


/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Test Function Prototypes
 *
 * Prototypes for routines to test this module. Available only in DEBUG
 * builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)

	/* Maximum file size to use for Test_RWFile() */
	#if defined(__TURBOC__)
		#define TEST_RWFILE_MAXFILESIZE 65000u
	#else
		#define TEST_RWFILE_MAXFILESIZE 100000
	#endif

	/* Helper function to create a random file of a given size */
	void Test_CreateRandomFile(const TCHAR *pFilename,
	                           const size_t Size,
	                           const bool TextMode = FILE_BINARY);

	/* Helper function to compare two files */
	bool Test_CompareFiles(const TCHAR *pFilename1, const TCHAR *pFilename2);

	/* Test routines */
	void Test_ChangeExtension();
	void Test_ChangeDirectory();
	void Test_CompareExtension();
	void Test_CopyFile();
	void Test_CreatePath();
	void Test_ExtractFilename();
	void Test_ExtractPath();
	void Test_FileExists();
	void Test_GetFileSize();
	void Test_HasExtension();
	void Test_HasPath();
	void Test_IsDirectory();
	void Test_IsFileWriteable();
	void Test_IsWildCard();
	void Test_ReadFile();
	void Test_ReadFileBuffer();
	void Test_read_int();
	void Test_read_long();
	void Test_read_motlong();
	void Test_read_short();
	void Test_ReadLine();
	void Text_RemoveExtension();
	void Test_RWFile(const size_t NumTests = 100);
	void Test_RWNumbers(const size_t NumTests = 1000);
	void Test_TerminatePath();
	void Test_WriteFile();
	void Test_DL_File();

#endif
/*===========================================================================
 *      End of Test Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File DL_File.H
 *=========================================================================*/
