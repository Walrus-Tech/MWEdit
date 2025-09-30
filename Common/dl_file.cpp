/*===========================================================================
 *
 * File:    DL_File.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, May 07, 2001
 *
 * Implementation for file related routines for Dave's Library of common
 * code.
 *
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *  - Moved from regular char to TCHAR type to support wide characters
 *    under Windows. Successfully tested.
 *
 * 20 January 2003 (Dave Humphrey)
 *  - Added the MakePathEx() function.
 *
 * 18 September 2003
 *  - Added the ReadFileCB() function.
 *
 * 18 December 2003
 *  - Added the CompareFiles() function.
 *
 * 16 February 2004
 *  - Added the MakeSpaceLabel() function.
 *
 *=========================================================================*/
#include "dl_file.h"
#include <direct.h>
#include <errno.h>
//#include <limits.h>
//#include <sys\stat.h>
//#include <io.h>
#include <ctype.h>

#ifndef _MSC_VER
	#include <dir.h>
#endif

#if _WIN32
	#include <windows.h>
#endif


DEFINE_FILE("DL_File.h");


/*=========================================================================
 *
 * Function - bool ChangeDirectory (pPath);
 *
 * Returns TRUE if the specified path is a valid directory.  Does this
 * by attempting to change paths.  If successful the current path is
 * changed to the given directory.  Otherwise the current path is
 * unchanged and FALSE is returned.  ASSERTs on NULL input.  Is
 * currently valid in the following systems:
 *  WIN32 - Uses the _chdir() function
 *  MSDOS - Uses the chdir() function
 * ASSERTs if run under any other system.
 *
 *=======================================================================*/
bool ChangeDirectory(const TCHAR *pPath) {
	DEFINE_FUNCTION("ChangeDirectory()");
	int Result;
	/* Make sure the given path is valid */
	ASSERT(pPath != NULL);
	/* Call the correct function according to the current system */
#if _WIN32
	Result = _tchdir(pPath);
#else
	ASSERT(FALSE);
#endif

	if (Result != 0) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Directory '%s' is not valid!"),
		                      pPath);
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - TCHAR* ChangeExtension (pDestFilename, pSourceFilename,
 *                   pNewExtension, MaxStringLength);
 *
 * Copies the source filename to the destination, changing the file's
 * extension.  The destination filename will be, at most, MaxStringLength
 * bytes in length.  The new extension can include the leading '.'
 * TCHARacter or not.  A pointer to the destination string is returned.
 * The function ASSERTs if passed a bad pointer.
 *
 *=========================================================================*/
TCHAR *ChangeExtension(TCHAR *pDestFilename,
                       const TCHAR *pSourceFilename,
                       const TCHAR *pNewExtension,
                       const size_t MaxStringLength) {
	DEFINE_FUNCTION("ChangeExtension()");
	size_t DestLength;
	/* Ensure valid input */
	ASSERT(pDestFilename != NULL && pSourceFilename != NULL && pNewExtension != NULL);
	/* Create the new filename without an extension */
	strnncpy(pDestFilename, pSourceFilename, MaxStringLength);
	RemoveExtension(pDestFilename);
	DestLength = TSTRLEN(pDestFilename);

	/* Ensure the '.' extension TCHARacter is present */
	if (*pNewExtension != (TCHAR)'.' && DestLength < MaxStringLength) {
		chrcat(pDestFilename, (TCHAR)'.');
		DestLength++;
	}

	/* Add the new extension to the destination filename */
	TSTRNCAT(pDestFilename, pNewExtension, MaxStringLength - DestLength);
	return pDestFilename;
}


/*===========================================================================
 *
 * Function - bool CompareExtension (pFilename, pExtension);
 *
 * Compares the extension of the given filename with the given extension
 * and returns TRUE if they match (case insensitive). The '.' extension
 * TCHARacter is not included. ASSERTs if passed invalid string pointers.
 *
 *=========================================================================*/
bool CompareExtension(const TCHAR *pFilename, const TCHAR *pExtension) {
	DEFINE_FUNCTION("CompareExtension()");
	const TCHAR *pFileExt;
	int Result;
	/* Ensure valid input */
	ASSERT(pFilename != NULL && pExtension != NULL);
	/* Attempt to find the file's extension */
	pFileExt = FindExtension(pFilename);

	if (pFileExt != NULL) {
		Result = _stricmp(pFileExt, pExtension);

		if (Result == 0) {
			return TRUE;
		}
	}

	/* No extension found */
	return FALSE;
}


/*===========================================================================
 *
 * Function - bool CompareFiles (pFilename1, pFilename2);
 *
 * Compares two files, returning true only if the two are an exact match.
 * Performs a binary compare (case sensitive).
 *
 *=========================================================================*/
bool CompareFiles(const TCHAR *pFilename1, const TCHAR *pFilename2) {
	//DEFINE_FUNCTION("CompareFiles()");
	FILE *pFileHandle1;
	FILE *pFileHandle2;
	bool ReturnValue = true;

	/* Ignore invalid input */
	if (pFilename1 == NULL || pFilename2 == NULL) {
		return false;
	}

	/* Attempt to open both files for input */
	pFileHandle1 = TFOPEN(pFilename1, _T("rb"));

	if (pFileHandle1 == NULL) {
		return false;
	}

	pFileHandle2 = TFOPEN(pFilename2, _T("rb"));

	if (pFileHandle2 == NULL) {
		fclose(pFileHandle1);
		return false;
	}

	/* Compare each file, byte by byte */
	while (!feof(pFileHandle1) && !feof(pFileHandle2)) {
		if (fgetc(pFileHandle1) != fgetc(pFileHandle2)) {
			ReturnValue = false;
			break;
		}

		/* Abort on any error */
		if (ferror(pFileHandle1) != 0 || ferror(pFileHandle2) != 0) {
			ReturnValue = false;
			break;
		}
	}

	/* Ensure both files are the samesize */
	if (feof(pFileHandle1) != feof(pFileHandle2)) {
		ReturnValue = false;
	}

	fclose(pFileHandle1);
	fclose(pFileHandle2);
	return ReturnValue;
}


/*=========================================================================
 *
 * Function - bool CopyOneFile (pInputFile, pOutputFile);
 *
 * Copies the given input file to the output file.  Returns FALSE on any
 * error.  Overwrites the destination file if it exists.  ASSERTs if
 * given invalid file strings.  Changed the buffer from a stack variable
 * to a dynamic because of problems with 16-bit compiles under Borland.
 *
 *=======================================================================*/
bool CopyOneFile(const TCHAR *pInputFile, const TCHAR *pOutputFile) {
	DEFINE_FUNCTION("CopyOneFile()");
	FILE *pInputHandle = NULL;
	FILE *pOutputHandle = NULL;
	byte *Buffer;
	size_t ReadSize;
	size_t WriteSize;
	bool ReturnValue = TRUE;
	/* Ensure valid input */
	ASSERT(pInputFile != NULL && pOutputFile != NULL);
	/* Attempt to open input file */
	pInputHandle = OpenFile(pInputFile, _T("rb"));

	if (pInputHandle == NULL) {
		return FALSE;
	}

	/* Attempt to open output file */
	pOutputHandle = OpenFile(pOutputFile, _T("wb"));

	if (pOutputHandle == NULL) {
		fclose(pInputHandle);
		return FALSE;
	}

	/* Allocate the transfer buffer */
	Buffer = (byte *)CreateString(COPYFILE_BUFFERSIZE);

	/* Read and write file in sections until finished */
	do {
		/* Input data from source file and output to destination */
		ReadSize = fread(Buffer, 1, COPYFILE_BUFFERSIZE, pInputHandle);
		WriteSize = fwrite(Buffer, 1, ReadSize, pOutputHandle);

		/* Ensure both the input and output was successful */
		if (WriteSize != ReadSize || ferror(pInputHandle) || ferror(pOutputHandle)) {
			ErrorHandler.AddError(ERR_SYSTEM,
			                      (errcode_t)errno,
			                      _T("Failed to copy file '%s' to '%s'!"),
			                      pInputFile,
			                      pOutputFile);
			ReturnValue = FALSE;
			break;
		}
	} while (ReadSize == COPYFILE_BUFFERSIZE);

	/* Close files */
	DestroyPointer(Buffer);
	fclose(pInputHandle);
	fclose(pOutputHandle);
	return ReturnValue;
}


/*=========================================================================
 *
 * Function - TCHAR* CreatePath (pNewPath, pString, MaxStringLength);
 *
 * Creates a path from the given string.  Copies up to MaxStringLength
 * bytes into the destination string and ensures that the given path ends
 * in the current LocalePathTCHAR TCHARacter.  ASSERTs on invalid input.
 * Returns a pointer to the new string.
 *
 *=======================================================================*/
TCHAR *CreatePath(TCHAR *pNewPath, const TCHAR *pString, const size_t MaxStringLength) {
	DEFINE_FUNCTION("CreatePath()");
	/* Ensure all input is valid */
	ASSERT(pNewPath != NULL && pString != NULL);
	/* Copy the given string into the new path */
	strnncpy(pNewPath, pString, MaxStringLength);

	/* Ensure the path ends with a path TCHARacter */
	if ((size_t)TSTRLEN(pNewPath) < MaxStringLength) {
		TerminatePath(pNewPath);
	}

	return pNewPath;
}


/*===========================================================================
 *
 * Function - bool DelOneFile (pFilename);
 *
 * Delete a single file, returns false on any error.
 *
 *=========================================================================*/
bool DelOneFile(const TCHAR *pFilename) {
	DEFINE_FUNCTION("DelOneFile()");
#if _WIN32
	BOOL Result;
	Result = DeleteFile(pFilename);

	if (!Result) {
		ErrorHandler.AddError(ERR_WINDOWS, _T("Failed to delete file '%s'!"), pFilename);
		return false;
	}

	return true;
#else
	ASSERT(false);
	return false;
#endif
}


/*=========================================================================
 *
 * Function - TCHAR* ExtractFilename (pFilename, pPath, MaxStringLength);
 *
 * Copies just the filename from the given path into the given file string
 * (up to MaxStringLength bytes).  ASSERTs if passed a bad pointer.  Returns
 * a pointer to the file string.
 *
 *=======================================================================*/
TCHAR *ExtractFilename(TCHAR *pFilename, const TCHAR *pPath, const size_t MaxStringLength) {
	DEFINE_FUNCTION("ExtractFilename()");
	/* Ensure valid input */
	ASSERT(pFilename != NULL && pPath != NULL);
	/* Find the start of the filename in the path string */
	pPath = FindFilename(pPath);

	/* Check to ensure a filename was found in the path */
	if (pPath == NULL) {
		*pFilename = NULL_CHAR;
	} else {
		strnncpy(pFilename, pPath, MaxStringLength);
	}

	return pFilename;
}


/*=========================================================================
 *
 * Function - TCHAR* ExtractPath (pPath, pString, MaxStringLength);
 *
 * Copies just the path from the given string and copies into the
 * specified path (at most MaxStringLength bytes).  Returns a pointer
 * to the new path string.  Ensures the path ends in the current
 * LocalePathTCHAR TCHARacter.  ASSERTs if passed a bad pointer.
 * Assumes the string has the format:
 *  drive:\\path1\\path2\\filename
 *  drive:\\filename
 *  drive:filename
 * Both the drive and filename are optional.
 *
 *=======================================================================*/
TCHAR *ExtractPath(TCHAR *pPath, const TCHAR *pString, const size_t MaxStringLength) {
	DEFINE_FUNCTION("ExtractPath()");
	TCHAR *pFilePtr;
	/* Ensure all the input is valid */
	ASSERT(pPath != NULL && pString != NULL);
	/* Copy the string into the new path */
	strnncpy(pPath, pString, MaxStringLength);
	/* Remove any filename from the new path string, if any */
	pFilePtr = (TCHAR *)FindFilename(pPath);
	*pFilePtr = NULL_CHAR;

	/* Ensure the path terminates properly, if possible */
	if ((size_t)TSTRLEN(pPath) < MaxStringLength) {
		TerminatePath(pPath);
	}

	return pPath;
}


/*=========================================================================
 *
 * Function - bool FileExists (pFilename);
 *
 * Returns TRUE if the specified file exists and can be opened for
 * reading.  ASSERTs if passed a bad pointer.
 *
 *=======================================================================*/
bool FileExists(const TCHAR *pFilename) {
	DEFINE_FUNCTION("FileExists()");
	FILE *pFileHandle;
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	/* Test for empty string (prevents _wfopen() from asserting in UNICODE debug builds */
	if (pFilename[0] == NULL_CHAR) {
		return false;
	}

	/* Attempt to open file for reading */
	pFileHandle = TFOPEN(pFilename, _T("r"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* File was opened and therefore exists, close and return success */
	fclose(pFileHandle);
	return TRUE;
}


/*===========================================================================
 *
 * Function - const TCHAR* FindExtension (pFilename);
 *
 * Returns a pointer to the first character in the file extension, just
 * after the '.' character.  Returns NULL if the file has no extension.
 * ASSERTs if given an invalid string pointer.  Searches for the first
 * '.' character from the end of the string before a path seperator
 * character (LocalePathTCHAR) or a ':'.
 *
 *=========================================================================*/
const TCHAR *FindExtension(const TCHAR *pFilename) {
	DEFINE_FUNCTION("FindExtension()");
	size_t StringIndex;
	/* Ensure valid input */
	ASSERT(pFilename != NULL);
	/* Find the end of the filename */
	StringIndex = TSTRLEN(pFilename);

	/* Find the last '.' TCHARacter before the path/drive starts */
	while (pFilename[StringIndex] != LocalePathChar
	       && pFilename[StringIndex] != (TCHAR)':'
	       && StringIndex != 0) {
		StringIndex--;

		/* Check for the extension marker TCHARaacter */
		if (pFilename[StringIndex] == (TCHAR)'.') {
			return pFilename + StringIndex + 1;
		}
	}

	/* No extension found */
	return NULL;
}


/*=========================================================================
 *
 * Function - const TCHAR* FindFilename (pPath);
 *
 * Returns a pointer to the first character in the filename in the given
 * complete path.  ASSERTs if given an invalid pointer.  Returns an
 * empty string if the given path contains no filename.  Uses the current
 * LocalePathChar and the drive character ':'.
 *
 *=======================================================================*/
const TCHAR *FindFilename(const TCHAR *pPath) {
	DEFINE_FUNCTION("FindFilename()");
	size_t StringIndex;
	/* Ensure the input is valid */
	ASSERT(pPath != NULL);
	/* Start at the end of the given path */
	StringIndex = TSTRLEN(pPath);

	while (StringIndex != 0) {
		StringIndex--;

		if (pPath[StringIndex] == LocalePathChar ||
		    pPath[StringIndex] == (TCHAR)':') {
			StringIndex++;
			break;
		}
	}

	return pPath + StringIndex;
}


/*===========================================================================
 *
 * Function - TCHAR* GetDirString (TCHAR* pString, const int MaxLength);
 *
 * Copies  the current directory into the given string, which is returned.
 * Up to MaxLength characters will be copied into the string.
 *
 *=========================================================================*/
TCHAR *GetDirString(TCHAR *pString, const int MaxLength) {
	DEFINE_FUNCTION("GetDirString()");
	/* Ensure valid input */
	ASSERT(pString != NULL && MaxLength > 0);
#if _WIN32
	_tgetcwd(pString, MaxLength - 1);
#else
	getcwd(pString, MaxLength - 1);
#endif
	TerminatePath(pString);
	return pString;
}


/*===========================================================================
 *
 * Function - long GetFileSize (pFilename);
 *
 * Returns the size of the give filename.  Returns 0 on any error and
 * sets the appropiate error code. ASSERTs if given a bad file string pointer.
 *
 *=========================================================================*/
long GetFileSize(const TCHAR *pFilename) {
	//DEFINE_FUNCTION("GetFileSize(TCHAR*)");
	long FileSize;
	bool Result;
	Result = GetFileSize(FileSize, pFilename);

	if (!Result) {
		return 0;
	}

	return FileSize;
}


/*===========================================================================
 *
 * Function - long GetFileSize (pFileHandle);
 *
 * Returns the size of the give file stream.  Returns 0 on any error and
 * sets the appropiate error code. ASSERTs if given a bad file stream pointer.
 * The current file position remains unchanged.
 *
 *=========================================================================*/
long GetFileSize(FILE *pFileHandle) {
	//DEFINE_FUNCTION("GetFileSize(FILE*)");
	long FileSize;
	bool Result;
	Result = GetFileSize(FileSize, pFileHandle);

	if (!Result) {
		return 0;
	}

	return FileSize;
}


/*===========================================================================
 *
 * Function - bool GetFileSize (FileSize, pFilename);
 *
 * Attempts to retrieve the size in bytes of the given filename. Returns
 * FALSE on any error (setting the appropiate error), or TRUE on success.
 * ASSERTs if given an invalid file string pointer.
 *
 *=========================================================================*/
bool GetFileSize(long &FileSize, const TCHAR *pFilename) {
	DEFINE_FUNCTION("GetFileSize(long&, TCHAR*)");
	FILE *pFileHandle;
	bool Result;
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	/* Attempt to open file for binary input */
	/* Test for empty string (prevents _wfopen() from asserting in UNICODE debug builds */
	if (pFilename[0] != NULL_CHAR) {
		pFileHandle = TFOPEN(pFilename, _T("rb"));
	} else {
		pFileHandle = NULL;
	}

	if (pFileHandle == NULL) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not open the file '%s'!"),
		                      pFilename);
		return FALSE;
	}

	Result = GetFileSize(FileSize, pFileHandle);
	fclose(pFileHandle);
	return Result;
}


/*===========================================================================
 *
 * Function - bool GetFileSize (FileSize, pFileHandle);
 *
 * Attempts to retrieve the number of bytes in the given valid file
 * stream.  The file position of the stream is unchanged.   Returns
 * TRUE on success, or FALSE on any error, setting the appropiate error.
 * ASSERTs if given an  invalid stream pointer.  Files opened in text mode
 * may not report the file size correctly.
 *
 *=========================================================================*/
bool GetFileSize(long &FileSize, FILE *pFileHandle) {
	DEFINE_FUNCTION("GetFileSize(long&, FILE*)");
	long PrevFilePos;
	int Result;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Save the current file position */
	PrevFilePos = ftell(pFileHandle);

	if (PrevFilePos < 0) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not retrieve current position in file!"));
		return FALSE;
	}

	/* Attempt to move to the end of the file */
	Result = fseek(pFileHandle, 0, SEEK_END);

	if (Result < 0) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not move file position to end of file!"));
		return FALSE;
	}

	/* Get the size of the file in bytes */
	FileSize = ftell(pFileHandle);

	if (FileSize < 0) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not retrieve current position in file!"));
		return FALSE;
	}

	Result = fseek(pFileHandle, PrevFilePos, SEEK_SET);

	if (Result < 0) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not move file position to previous location!"));
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - bool HasExtension (pFilename);
 *
 * Returns TRUE if the given filename has an extension.  ASSERTs if given
 * an invalid string pointer.
 *
 *=========================================================================*/
bool HasExtension(const TCHAR *pFilename) {
	DEFINE_FUNCTION("HasExtension()");
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	if (FindExtension(pFilename) == NULL) {
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - bool HasPath (pFilename);
 *
 * Returns TRUE if the given filename contains a path.  ASSERTs if given an
 * invalid string pointer. Uses the current LocalePathTCHAR TCHARacter and the
 * drive TCHARacter ':'.
 *
 *=========================================================================*/
bool HasPath(const TCHAR *pFilename) {
	DEFINE_FUNCTION("HasPath()");
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	/* Look for any drive/path TCHARacters in filename */
	while (*pFilename != NULL_CHAR) {
		if (*pFilename == LocalePathChar || *pFilename == ':') {
			return TRUE;
		}

		pFilename++;
	}

	return FALSE;
}


/*=========================================================================
 *
 * Function - bool IsDirectory (pPath);
 *
 * Returns TRUE if the specified path is a valid but does not change
 * change the current directory.  ASSERTs if the input path pointer is
 * invalid.  Sets the appropiate error on failure.
 *
 *=======================================================================*/
bool IsDirectory(const TCHAR *pPath) {
	DEFINE_FUNCTION("IsDirectory()");
	TCHAR InitialPath[_MAX_PATH + 1];
	TCHAR *pResult;
	bool Result;
	/* Ensure valid input */
	ASSERT(pPath != NULL);
	/* Save the initial directory */
#if _WIN32
	pResult = _tgetcwd(InitialPath, _MAX_PATH);
#else
	pResult = getcwd(InitialPath, _MAX_PATH);
#endif

	if (pResult == NULL) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Failed to retrieve the current directory!"));
		return FALSE;
	}

	/* Attempt to change directories */
	Result = ChangeDirectory(pPath);

	if (!Result) {
		return FALSE;
	}

	/* Restore the initial path and return success */
	ChangeDirectory(InitialPath);
	return TRUE;
}


/*========================================================================
 *
 * Function - bool IsFileWriteable (pFilename);
 *
 * Returns TRUE if the given file can be written to.  ASSERTs if
 * input string is invalid.
 *
 *======================================================================*/
bool IsFileWriteable(const TCHAR *pFilename) {
	DEFINE_FUNCTION("IsFileWriteable()");
	FILE *pFileHandle;
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	/* Test for empty string (prevents _wfopen() from asserting in UNICODE debug builds */
	if (pFilename[0] == NULL_CHAR) {
		return FALSE;
	}

	/* Attempt to open the file for appending */
	pFileHandle = TFOPEN (pFilename, _T("ab"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* Close the now open file and return success */
	fclose (pFileHandle);
	return TRUE;
}


/*=========================================================================
 *
 * Function - bool IsWildCard (pFilename);
 *
 * Returns TRUE if the given string has any '*' or '?' wildcard
 * TCHARacters in it.  ASSERTs if the given string is invalid.
 *
 *=======================================================================*/
bool IsWildCard(const TCHAR *pFilename) {
	DEFINE_FUNCTION("IsWildCard()");
	/* Ensure valid input */
	ASSERT(pFilename != NULL);

	/* Search entire string for a wildcard TCHARacter */
	while (*pFilename != NULL_CHAR) {
		if (*pFilename == (TCHAR)'*' || *pFilename == (TCHAR)'?') {
			return TRUE;
		}

		pFilename++;
	}

	/* No wildcard TCHARacters found */
	return FALSE;
}


/*===========================================================================
 *
 * Function - TCHAR* MakeSpaceLabel (Buffer, BufferSize, Value);
 *
 * Makes a convienient space label of the given value in bytes in the given
 * string buffer.
 *
 *=========================================================================*/
TCHAR *MakeSpaceLabel(TCHAR *Buffer, const int BufferSize, const double Value) {
	//DEFINE_FUNCTION("MakeSpaceLabel()");
	if ((int)Value == 0) {
		snprintf(Buffer, BufferSize, _T("0 b"));
	} else if (Value < 0.0) {
		snprintf(Buffer, BufferSize, _T("? b"));
	} else if (Value <= 1500.0) {
		snprintf(Buffer, BufferSize, _T("%d b"), (int)Value);
	} else if (Value <= 1500000.0) {
		snprintf(Buffer, BufferSize, _T("%.1f kb"), Value / 1000.0);
	} else if (Value <= 1500000000.0) {
		snprintf(Buffer, BufferSize, _T("%.1f Mb"), Value / 1000000.0);
	} else {
		snprintf(Buffer, BufferSize, _T("%.1f Gb"), Value / 1000000000.0);
	}

	return Buffer;
}


/*===========================================================================
 *
 * Function - bool MakePathEx (pPath);
 *
 * Creates multiple levels of paths. Returns false on any error.
 *
 *=========================================================================*/
bool MakePathEx(const TCHAR *pPath) {
	TCHAR TempPath[_MAX_PATH + 1];
	TCHAR TempDrive[8] = _T("c:\\");
	TCHAR InitialPath[_MAX_PATH + 1];
	TCHAR *pParse;
	bool Result;
	int iResult;

	/* Ignore invalid input */
	if (pPath == NULL) {
		return false;
	}

	strnncpy(TempPath, pPath, _MAX_PATH);
	/* Save the initial directory */
	GetDirString(InitialPath, _MAX_PATH);
	pParse = TSTRTOK(TempPath, _T("\\"));

	while (pParse != NULL && *pParse != NULL_CHAR) {
		/* Does the given directory/drive exist? */
		if (pParse[1] == ':') {
			TempDrive[0] = pParse[0];
			Result = ChangeDirectory(TempDrive);
		} else {
			Result = ChangeDirectory(pParse);
		}

		/* Attempt to make the given directory */
		if (!Result) {
			iResult = _tmkdir(pParse);

			if (iResult < 0) {
				ErrorHandler.AddError(ERR_OPENFILE,
				                      _T("Failed to create the directory '%s'!"),
				                      pParse);
				return false;
			}

			Result = ChangeDirectory(pParse);

			if (!Result) {
				return false;
			}
		}

		pParse = TSTRTOK(NULL, _T("\\"));
	}

	/* Restore the initial path and return success */
	ChangeDirectory(InitialPath);
	return true;
}


/*===========================================================================
 *
 * Function - FILE* OpenFile (pFilename, pMode);
 *
 * Wrapper function for opening a file with fopen().  Records error and
 * SystemLog information automatically.  Returns NULL on any error.
 * ASSERTs if the filename or mode string is invalid.
 *
 *=========================================================================*/
const TCHAR *l_GetFileMode(const TCHAR *pMode) {
	switch (pMode[0]) {
		case 'r':
			return _T("reading");

		case 'w':
			return _T("writing");

		case 'a':
			return _T("read/write");

		default:
			return _T("unknown");
	}
}

FILE *OpenFile (const TCHAR *pFilename, const TCHAR *pMode) {
	DEFINE_FUNCTION("OpenFile(TCHAR*, TCHAR*)");
	FILE *pFileHandle = NULL;
	/* Ensure valid input */
	ASSERT(pFilename != NULL && pMode != NULL);

	/* Attempt to open file in desired mode */
	if (*pFilename != NULL_CHAR && *pMode != NULL_CHAR) {
		pFileHandle = TFOPEN(pFilename, pMode);
	}

	/* Check for error conditions and output status */
	if (pFileHandle == NULL) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Failed to open the file '%s' (mode was '%s')!"),
		                      pFilename,
		                      l_GetFileMode(pMode));
	} else {
		SystemLog.Printf(_T("Opened file '%s' in mode '%s'..."), pFilename, l_GetFileMode(pMode));
	}

	return pFileHandle;
}


/*===========================================================================
 *
 * Function - bool OpenFile (ppFileHandle, pFilename, pMode);
 *
 * Attempts to open a file using fopen().  Returns TRUE on success, and
 * FALSE on error, setting the appropiate error.  ASSERTs if any input
 * string pointer is invalid.
 *
 *=========================================================================*/
bool OpenFile(FILE **ppFileHandle, const TCHAR *pFilename, const TCHAR *pMode) {
	DEFINE_FUNCTION("OpenFile(FILE**, TCHAR*, TCHAR*)");
	/* Ensure valid input */
	ASSERT(ppFileHandle != NULL);
	*ppFileHandle = OpenFile(pFilename, pMode);

	if (*ppFileHandle == NULL) {
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - bool ReadFile (ppBuffer, BytesRead, pFilename, TextMode);
 *
 * Attempts to read the entire file into a new string buffer.
 * On any error FALSE is returned and the appropiate error code set.
 * On success, the ppBuffer points to the newly allocated string
 * containing the file data, and BytesRead is the size of the string.
 * ASSERTs if tanyhe input is invalid.  Ensure that any valid
 * returned pointer is at one point unallocated with delete.  If the
 * TextMode flag is TRUE (FILE_TEXT), the file is read in text mode.
 * If FALSE (FILE_BINARY), the file is read in binary mode.  Note that
 * on some systems, the two modes are identical.
 *
 *=========================================================================*/
bool ReadFile(byte **ppBuffer, size_t &BytesRead, const TCHAR *pFilename, const bool TextMode) {
	DEFINE_FUNCTION("ReadFile()");
	FILE *pFileHandle;
	long FileSize;
	size_t BufferSize;
	bool Result;
	bool ReturnValue = TRUE;
	/* Ensure valid input */
	ASSERT(pFilename != NULL && ppBuffer != NULL);
	BytesRead = 0;
	*ppBuffer = NULL;
	/* Attempt to open the file for input */
	pFileHandle = OpenFile(pFilename, TextMode ? _T("rt") : _T("rb"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* Attempt to get the file size in bytes */
	Result = GetFileSize(FileSize, pFileHandle);
	BufferSize = (size_t)FileSize;

	/* If an error occured getting the file size, do nothing */
	if (!Result) {
		ReturnValue = FALSE;
	}
	/* For systems with long/int having different bit sizes */
	else if (FileSize != (long)BufferSize) {
		ErrorHandler.AddError(ERR_MEM,
		                      _T("Cannot read the file '%s' as it's size exceeds the maximum allocation size!"),
		                      pFilename);
		ReturnValue = FALSE;
	}
	/* Allocate input buffer and read data from file */
	else {
		CreateArrayPointer(*ppBuffer, byte, BufferSize + 1);
		BytesRead = fread(*ppBuffer, 1, BufferSize, pFileHandle);
		(*ppBuffer)[BufferSize] = NULL_CHAR;

		/* Ensure the input was entirely successfull */
		if (ferror(pFileHandle)) {
			ErrorHandler.AddError(ERR_SYSTEM,
			                      (errcode_t)errno,
			                      _T("Could not read the entire file '%s' (%u of %u bytes read)!"),
			                      pFilename,
			                      BytesRead,
			                      BufferSize);
			DestroyPointer(*ppBuffer);
			ReturnValue = FALSE;
		}
	}

	fclose(pFileHandle);
	return ReturnValue;
}


/*===========================================================================
 *
 * Function - bool ReadFileCB (ppBuffer, BytesRead, pFilename, CallBackFunc, pUserData);
 *
 * Same as the ReadFile() function but reads the files in increments, calling
 * the given callback function to update the user on the read progress.
 * File is read in BINARY mode.
 *
 *=========================================================================*/
bool ReadFileCB(byte **ppBuffer,
                size_t &BytesRead,
                const TCHAR *pFilename,
                READFILE_CALLBACK CallBackFunc,
                void *pUserData) {
	DEFINE_FUNCTION("ReadFileCB()");
	FILE *pFileHandle;
	byte *pCurrentPos;
	long FileSize;
	long TotalBytes;
	size_t BufferSize;
	bool Result;
	bool ReturnValue = TRUE;
	int CBResult;

	/* Ensure valid input */
	ASSERT(pFilename != NULL && ppBuffer != NULL);
	BytesRead = 0;
	*ppBuffer = NULL;
	/* Attempt to open the file for input */
	pFileHandle = OpenFile(pFilename, _T("rb"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* Attempt to get the file size in bytes */
	Result = GetFileSize(FileSize, pFileHandle);
	BufferSize = (size_t)FileSize;

	/* If an error occured getting the file size, do nothing */
	if (!Result) {
		fclose(pFileHandle);
		return false;
	}

	/* For systems with long/int having different bit sizes */
	if (FileSize != (long)BufferSize) {
		ErrorHandler.AddError(ERR_MEM,
		                      _T("Cannot read the file '%s' as it's size exceeds the maximum allocation size!"),
		                      pFilename);
		fclose(pFileHandle);
		return false;
	}

	/* Allocate input buffer */
	CreateArrayPointer(*ppBuffer, byte, BufferSize + 1);
	pCurrentPos = *ppBuffer;
	TotalBytes = 0;

	/* Input file by chunks */
	while (!feof(pFileHandle)) {
		if (READFILECB_NUMBYTES > FileSize - TotalBytes) {
			BytesRead = fread(pCurrentPos, 1, FileSize - TotalBytes, pFileHandle);
		} else {
			BytesRead = fread(pCurrentPos, 1, READFILECB_NUMBYTES, pFileHandle);
		}

		pCurrentPos += BytesRead;
		TotalBytes += BytesRead;

		/* Update the callback function */
		if (CallBackFunc != NULL) {
			CBResult = CallBackFunc(FileSize, TotalBytes, pUserData);

			if (CBResult < 0) {
				ErrorHandler.AddError(ERR_SYSTEM,
				                      (errcode_t)errno,
				                      _T("ReadFileCB() callback function returned abort code!"));
				ReturnValue = FALSE;
				break;
			}
		}

		if (BytesRead != READFILECB_NUMBYTES) {
			break;
		}
	}

	/* NULL terminate in case of a text file */
	(*ppBuffer)[BufferSize] = NULL_CHAR;

	/* Ensure the input was entirely successfull */
	if (ferror(pFileHandle)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Could not read the entire file '%s' (%u of %u bytes read)!"),
		                      pFilename,
		                      BytesRead,
		                      BufferSize);
		DestroyPointer(*ppBuffer);
		ReturnValue = FALSE;
	}

	BytesRead = TotalBytes;
	fclose(pFileHandle);
	return ReturnValue;
}


/*===========================================================================
 *
 * Function - bool ReadFileBuffer (ppBuffer, BytesRead, pFilename, MaxSize, TextMode);
 *
 * Attempts to read the entire, or part of, a file into an existing string
 * buffer. On any error FALSE is returned and the appropiate error code set.
 * On success, at most MaxSize bytes of the file is read into the ppBuffer,
 * BytesRead is the number of bytes read. ASSERTs if tanyhe input is invalid.
 * If the TextMode flag is TRUE (FILE_TEXT), the file is read in text mode.
 * If FALSE (FILE_BINARY), the file is read in binary mode.  Note that
 * on some systems, the two modes are identical.  The buffer should be
 * at least one byte bigger in text mode to allow for the '\0' terminating
 * byte.
 *
 *=========================================================================*/
bool ReadFileBuffer(byte **ppBuffer,
                    size_t &BytesRead,
                    const TCHAR *pFilename,
                    const size_t MaxInputSize,
                    const bool TextMode) {
	DEFINE_FUNCTION("ReadFileBuffer()");
	FILE *pFileHandle;
	long FileSize;
	size_t BufferSize;
	bool Result;
	bool ReturnValue = TRUE;

	/* Ensure valid input */
	ASSERT(pFilename != NULL && ppBuffer != NULL && *ppBuffer != NULL);
	BytesRead = 0;
	/* Attempt to open the file for input */
	pFileHandle = OpenFile(pFilename, TextMode ? _T("rt") : _T("rb"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* Attempt to get the file size in bytes */
	Result = GetFileSize(FileSize, pFileHandle);
	BufferSize = (size_t)FileSize;

	/* If an error occured getting the file size, do nothing */
	if (!Result) {
		ReturnValue = FALSE;
	}
	/* For systems with long/int having different bit sizes */
	else if (FileSize != (long)BufferSize) {
		ErrorHandler.AddError(ERR_MEM,
		                      _T("Cannot read the file '%s' as it's size exceeds the maximum allocation size!"),
		                      pFilename);
		ReturnValue = FALSE;
	}
	/* Read data from file */
	else {
		if (BufferSize > MaxInputSize) {
			BufferSize = MaxInputSize;
		}

		BytesRead = fread(*ppBuffer, 1, BufferSize, pFileHandle);

		/* Ensure the input was entirely successfull */
		if (ferror(pFileHandle)) {
			ErrorHandler.AddError(ERR_SYSTEM,
			                      (errcode_t)errno,
			                      _T("Could not read the file '%s' (%u of %u bytes read)!"),
			                      pFilename,
			                      BytesRead,
			                      BufferSize);
			ReturnValue = FALSE;
		}

		/* NULL terminate if in text mode */
		if (TextMode) {
			if (BufferSize >= MaxInputSize) {
				(*ppBuffer)[MaxInputSize - 1] = NULL_CHAR;
			} else {
				(*ppBuffer)[BufferSize] = NULL_CHAR;
			}
		}
	}

	fclose(pFileHandle);
	return ReturnValue;
}


/*=========================================================================
 *
 * Function - int ReadLine (pFileHandle, pString, MaxStringLength);
 *
 * Reads up to MaxStringLength characters or to the first Linefeed
 * from the given file into the given string.  If string is NULL,
 * characters are merely read and not stored in string.  Returns:
 *  READLINE_OK    : Success
 *  READLINE_MSL   : If the maximum string length was reached
 *  READLINE_EOF   : End-of-file was reached
 *  READLINE_ERROR : An error was encountered. Sets the appropiate error.
 * ASSERTs if the input file handle is invalid.  The CR character is not
 * included at the end of the string.  MaxStringLength must be greater
 * than 0.
 *
 *=======================================================================*/
int ReadLine(FILE *pFileHandle, TCHAR *pString, const size_t MaxStringLength) {
	DEFINE_FUNCTION("ReadLine()");
	int ReturnValue = READLINE_OK;
	int InputChar;
	size_t StringLength = 0;
	/* Ignore any invalid file handle input */
	ASSERT(pFileHandle != NULL);

	/* Check if at the eof already */
	if (feof(pFileHandle)) {
		ErrorHandler.AddError(ERR_READFILE,
		                      _T("Could not read line, already at the end of the file!"));
		return READLINE_ERROR;
	}

	/* Main input loop (infinite) */
	do {
		/* Read in next character from file */
		InputChar = fgetc(pFileHandle);

		/* Check for EOF or Error conditions */
		if (InputChar == EOF) {
			if (!feof(pFileHandle)) {
				ErrorHandler.AddError(ERR_SYSTEM,
				                      (errcode_t)errno,
				                      _T("Failed to read line from file!"));
				ReturnValue = READLINE_ERROR;
			} else {
				ReturnValue = READLINE_EOF;
			}

			break;
		} else if (InputChar == LF_CHAR) { /* Check for end of line */
			break;
		} else if (pString != NULL) { /* Add character to string buffer */
			pString[StringLength] = (TCHAR)InputChar;
			StringLength++;

			/* Ensure string buffer does not exceed its maximum length */
			if (StringLength >= MaxStringLength) {
				ErrorHandler.AddError (ERR_MAXINDEX,
				                       _T("ReadLine() - Maximum string length %u reached!"),
				                       MaxStringLength);
				ReturnValue = READLINE_MSL;
				break;
			}
		}
	} while (TRUE); /* Loop is exited using break */

	/* Ensure the string is NULL terminated */
	if (pString != NULL) {
		pString[StringLength] = NULL_CHAR;
	}

	return ReturnValue;
}


/*=========================================================================
 *
 * Function - bool read_int (pFileHandle, Value);
 *
 * Reads an integer from the specified file. Returns FALSE on any error
 * and sets the appropiate code in ErrorHandler. The size of an integer
 * depends on the platform compiled under. In DOS it is usually 16 bit,
 * in Windows it is 32 bit, etc...  ASSERTs if the input handle is invalid.
 *
 *=======================================================================*/
bool read_int(FILE *pFileHandle, int &Value) {
	DEFINE_FUNCTION("read_int()");
	size_t InputSize;
	/* Make sure the file handle is valid */
	ASSERT(pFileHandle != NULL);
	/* Read in the integer value */
	InputSize = fread(&Value, 1, sizeof(int), pFileHandle);

	/* Check for any read error */
	if (InputSize != sizeof(int)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error reading binary integer value (read only %u of %u bytes)!"),
		                      InputSize,
		                      sizeof(int));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - bool read_long (pFileHandle, Value);
 *
 * Reads a long integer from the specified file. Returns FALSE on any error
 * and sets the appropiate code in ErrorHandler. The size of a long may
 * depend on the platform compiled under, though it is usually 32 bits.
 * ASSERTs if the input handle is invalid.
 *
 *=======================================================================*/
bool read_long(FILE *pFileHandle, long &Value) {
	DEFINE_FUNCTION("read_long()");
	size_t InputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Read the value */
	InputSize = fread (&Value, 1, sizeof(long), pFileHandle);

	/* Ensure the value was correctly read */
	if (InputSize != sizeof(long)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error reading binary long integer value (read only %u of %u bytes)!"),
		                      InputSize,
		                      sizeof(long));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - bool read_short (pFileHandle, Value);
 *
 * Reads a short integer from the specified file. Returns FALSE on any error
 * and sets the appropiate code in ErrorHandler. The size of a short may
 * depend on the platform compiled under, though it is usually 16 bits.
 * ASSERTs if the input handle is invalid.
 *
 *=======================================================================*/
bool read_short(FILE *pFileHandle, short &Value) {
	DEFINE_FUNCTION("read_short()");
	size_t InputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Read in the integer value */
	InputSize = fread(&Value, 1, sizeof(short), pFileHandle);

	/* Check for any read error */
	if (InputSize != sizeof(short)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error reading binary short integer value (read only %u of %u bytes)!"),
		                      InputSize,
		                      sizeof(short));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - long read_motlong (pFileHandle, Value);
 *
 * Reads a long integer from the specified file using the Motorola byte
 * order (as opposed to the usual Intel byte order).  Returns FALSE on
 * any error and sets the appropiate code with ErrorHandler.  A long integer
 * is usually 32 bit but may depend on the platform compiled under.
 *
 *=======================================================================*/
bool read_motlong(FILE *pFileHandle, long &Value) {
	DEFINE_FUNCTION("read_motlong()");
	unsigned char InputData[sizeof(long)];
	size_t InputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Read in the integer value */
	InputSize = fread(&InputData, 1, sizeof(long), pFileHandle);

	/* Check for any read error */
	if (InputSize != sizeof(long)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error reading binary motorola long value (read only %u of %u bytes)!"),
		                      InputSize,
		                      sizeof(long));
		return FALSE;
	}

	/* Compute the proper long integer value */
	Value = (long)(((unsigned long)InputData[3]) + (((unsigned long)InputData[2]) << 8)
	               + (((unsigned long)InputData[1]) << 16)
	               + (((unsigned long)InputData[0]) << 24));
	return TRUE;
}


/*===========================================================================
 *
 * Function - TCHAR* RemoveExtension (pFilename);
 *
 * Removes the extension from the given filename. Returns a pointer to
 * the modified file string.  ASSERTs if passed a bad pointer.
 *
 *=========================================================================*/
TCHAR *RemoveExtension(TCHAR *pFilename) {
	//DEFINE_FUNCTION("RemoveExtension()");
	TCHAR *pExtPtr;
	/* Attempt to find the start of the file extension */
	pExtPtr = (TCHAR *)FindExtension(pFilename);

	/* Terminate the file string at the '.' character */
	if (pExtPtr != NULL) {
		pExtPtr[-1] = NULL_CHAR;
	}

	return pFilename;
}


/*===========================================================================
 *
 * Function - TCHAR* TerminatePath (TCHAR* pPath);
 *
 * Ensures the given path string terminates in the current LocalPathChar
 * character.  Returns a pointer to the given string.  ASSERTs if the
 * input string is invalid.  Assumes that the string has been allocated
 * to allow an additional TCHARacter to be added to it.
 *
 *=========================================================================*/
TCHAR *TerminatePath(TCHAR *pPath) {
	DEFINE_FUNCTION("TerminatePath()");
	size_t PathLength;
	/* Ensure the input path is valid */
	ASSERT(pPath != NULL);
	PathLength = TSTRLEN(pPath);

	/* Ensure the string ends in the current path character */
	if (PathLength != 0 && pPath[PathLength - 1] != LocalePathChar) {
		pPath[PathLength] = LocalePathChar;
		pPath[PathLength + 1] = NULL_CHAR;
	}

	return pPath;
}


/*===========================================================================
 *
 * Function - bool WildcardCompare (pFilename, pFilter);
 *
 * Description
 *
 *=========================================================================*/
bool WildcardCompare(const TCHAR *pFilename, const TCHAR *pFilter) {
	while (*pFilename != NULL_CHAR && *pFilter != NULL_CHAR) {
		switch (*pFilter) {
			case '*': {
				bool Result;

				do {
					Result = WildcardCompare(pFilename, pFilter + 1);

					if (Result) {
						return true;
					}

					pFilename++;
				} while (*pFilename != NULL_CHAR && *pFilter != NULL_CHAR);

				/* Special case for * matching no characters */
				if (*pFilename == NULL_CHAR && pFilter[1] == NULL_CHAR) {
					return true;
				}
			}

			case '?':
				pFilename++;
				pFilter++;
				break;

			default:
				if (toupper(*pFilename) != toupper(*pFilter)) {
					return false;
				}

				pFilename++;
				pFilter++;
				break;
		}
	}

	return *pFilename == *pFilter;
}


/*===========================================================================
 *
 * Function - bool WriteFile (pBuffer, Size, pFilename, TextMode);
 *
 * Outputs Size bytes from the string pBuffer to the given filename.
 * Returns TRUE on success or FALSE on any error, setting the appropiate
 * error with ErrorHandler. If TextMode is TRUE (FILE_TEXT), the file
 * is created in text mode, if FALSE (FILE_BINARY), the file is created
 * in binary mode, the default.  ASSERTs if passed any invalid pointers.
 * The file is overwritten if it currently exists.
 *
 *=========================================================================*/
bool WriteFile(const byte *pBuffer,
               const size_t Size,
               const TCHAR *pFilename,
               const bool TextMode) {
	DEFINE_FUNCTION("WriteFile()");
	FILE *pFileHandle;
	size_t OutputBytes;
	bool ReturnValue = TRUE;
	/* Ensure valid input */
	ASSERT(pBuffer != NULL && pFilename != NULL);
	/* Attempt to open file for output */
	pFileHandle = OpenFile(pFilename, TextMode ? _T("wt") : _T("wb"));

	if (pFileHandle == NULL) {
		return FALSE;
	}

	/* Attempt to output string buffer to file */
	OutputBytes = fwrite(pBuffer, 1, Size, pFileHandle);

	if (ferror(pFileHandle)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Failed to write to the file '%s' (only %u of %u bytes output)!"),
		                      pFilename,
		                      OutputBytes,
		                      Size);
		ReturnValue = FALSE;
	}

	fclose(pFileHandle);
	return ReturnValue;
}


/*=========================================================================
 *
 * Function - bool write_short (pFileHandle, OutputValue);
 *
 * Writes a short integer to a file. Returns FALSE on any error.
 * The size of a short integer may depend on the system compiled in,
 * but usually it is 16 bits.  ASSERTs if passed an invalid file
 * handle.
 *
 *=======================================================================*/
bool write_short(FILE *pFileHandle, const short OutputValue) {
	DEFINE_FUNCTION("write_short()");
	size_t OutputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Output the data */
	OutputSize = fwrite(&OutputValue, 1, sizeof(short), pFileHandle);

	/* Ensure the data was properly output */
	if (OutputSize != sizeof(short)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error writing binary short integer to file (%u of %u bytes output)!"),
		                      OutputSize,
		                      sizeof(short));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - bool write_int (pFileHandle, OutputValue);
 *
 * Writes an  integer to a file. Returns FALSE on any error and sets the
 * appropiate error with ErrorHandler. The size of an integer depends
 * on the system compiled under, though usually it is 16 of 32 bits.
 * ASSERTs if given an invalid file handle.
 *
 *=======================================================================*/
bool write_int(FILE *pFileHandle, const int OutputValue) {
	DEFINE_FUNCTION("write_int()");
	size_t OutputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Output the data */
	OutputSize = fwrite(&OutputValue, 1, sizeof(int), pFileHandle);

	/* Ensure the data was properly output */
	if (OutputSize != sizeof(int)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error writing binary integer to file (%u of %u bytes output)!"),
		                      OutputSize,
		                      sizeof(int));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - bool write_long (pFileHandle, OutputValue);
 *
 * Writes a long integer to a file. Returns FALSE on any error, setting
 * the appropiate error code with the ErrorHandler.  ASSERTs if given
 * an invalid file handle.  Long integers are usually 32 bits in size,
 * but may depend on the system compiled under.
 *
 *=======================================================================*/
bool write_long(FILE *pFileHandle, const long OutputValue) {
	DEFINE_FUNCTION("write_long()");
	size_t OutputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);
	/* Output the data */
	OutputSize = fwrite(&OutputValue, 1, sizeof(long), pFileHandle);

	/* Ensure the data was properly output */
	if (OutputSize != sizeof(long)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error writing binary long integer to file (%u of %u bytes output)!"),
		                      OutputSize,
		                      sizeof(long));
		return FALSE;
	}

	return TRUE;
}


/*=========================================================================
 *
 * Function - bool write_motlong (pFileHandle, OutputValue);
 *
 * Writes a long integer to a file using the Motorola byte order (as
 * opposed to the usual Intel byte order). Returns FALSE on any error
 * and sets the appropiate error code with the ErrorHandler.  ASSERTs
 * if given an invalid file handle.  Long integers are usually 32 bits
 * in size, but may depend on the system compiled under.
 *
 *=======================================================================*/
bool write_motlong(FILE *pFileHandle, const long OutputValue) {
	DEFINE_FUNCTION("write_motlong()");
	unsigned char OutputData[sizeof(long)];
	size_t OutputSize;
	/* Ensure valid input */
	ASSERT(pFileHandle != NULL);

	/* Create the output buffer */
	OutputData[0] = (unsigned char)((OutputValue >> 24) & 0xFF);
	OutputData[1] = (unsigned char)((OutputValue >> 16) & 0xFF);
	OutputData[2] = (unsigned char)((OutputValue >> 8) & 0xFF);
	OutputData[3] = (unsigned char)(OutputValue & 0xFF);
	/* Output the data */
	OutputSize = fwrite(OutputData, 1, sizeof(long), pFileHandle);

	/* Ensure the data was properly output */
	if (OutputSize != sizeof(long)) {
		ErrorHandler.AddError(ERR_SYSTEM,
		                      (errcode_t)errno,
		                      _T("Error writing binary motorola long integer to file (%u of %u bytes output)!"),
		                      OutputSize,
		                      sizeof(long));
		return FALSE;
	}

	return TRUE;
}
