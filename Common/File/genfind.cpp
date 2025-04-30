/*===========================================================================
 *
 * File:    Genfind.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, June 06, 2001
 *
 * Implements the CFileFind class
 *
 *=========================================================================*/

/* Include Files */
#if defined(__MSDOS__)
	#include "dos.h"
	#include "dir.h"
	#include "time.h"
	#include "io.h"
#elif defined(_WIN32)
	#include "io.h"
#endif

#if defined(_WIN32) && defined(__BORLANDC__)
	#include <windows.h>
	#include <time.h>
#endif

#include "file\genfind.h"

/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
DEFINE_FILE("GenFind.cpp");
/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*=========================================================================
 *
 * Class CFileBlock Destructor
 *
 *=======================================================================*/
void CFileBlock::Destroy(void) {
	//DEFINE_FUNCTION("CFileBlock::Destroy");
	/* Clear all elements to 0 initially depending on platform */
#if defined(_WIN32) && defined(__BORLANDC__)
	BlockData.dwFileAttributes = FA_NORMAL;
	BlockData.cFileName[0] = NULL_CHAR;
	BlockData.nFileSizeLow = 0;
#elif defined(_WIN32)
	BlockData.attrib = FA_NORMAL;
	BlockData.name[0] = NULL_CHAR;
	BlockData.time_create = -1;
	BlockData.time_access = -1;
	BlockData.time_write = -1;
	BlockData.size = 0;
#elif defined(__MSDOS__)
	BlockData.ff_attrib = FA_NORMAL;
	BlockData.ff_name[0] = NULL_CHAR;
	BlockData.ff_ftime = 0;
	BlockData.ff_fsize = 0;
	BlockData.ff_fdate = 0;
#endif
}

/*=========================================================================
 *      End of Class CFileBlock Destructor
 *=======================================================================*/


#if defined(_WIN32) && defined(__BORLANDC__)
/*===========================================================================
 *
 * Class CFileBlock Method - time_t ConvertFileTime (const FILETIME& FileTime);
 *
 * Helper function to convert from file time to a time_t value.
 *
 *=========================================================================*/
time_t CFileBlock::ConvertFileTime(const FILETIME &FileTime) const {
	DEFINE_FUNCTION("CFileBlock::ConvertFileTime()");
	BOOL Result;
	SYSTEMTIME SysTime;
	FILETIME LocalTime;
	struct tm TimePtr;
	Result = FileTimeToLocalFileTime(&FileTime, &LocalTime);

	if (Result) {
		Result = FileTimeToSystemTime(&LocalTime, &SysTime);
	}

	if (!Result) {
		return (time_t)(0);
	}

	/* Convert ftime to a tm time, hopefully */
	TimePtr.tm_sec = SysTime.wSecond;
	TimePtr.tm_min = SysTime.wMinute;
	TimePtr.tm_hour = SysTime.wHour;
	TimePtr.tm_mday = SysTime.wDay;
	TimePtr.tm_mon = SysTime.wMonth;
	TimePtr.tm_year = SysTime.wYear;
	TimePtr.tm_wday = SysTime.wDayOfWeek;
	TimePtr.tm_yday = 0;
	TimePtr.tm_isdst = 0;
	return mktime(&TimePtr);
}

/*===========================================================================
 *      End of Class Method CFileBlock::ConvertFileTime()
 *=========================================================================*/
#endif


#if defined(__MSDOS__)
/*===========================================================================
 *
 * Class CFileBlock Method - time_t GetWriteTime (void)
 *
 * MSDOS method which converts the file block's ftime time and data data
 * into a time_t value.
 *
 *=========================================================================*/
time_t CFileBlock::GetWriteTime(void) const {
	//DEFINE_FUNCTION("CFileBlock::GetWriteTime()");
	struct ftime FileTime;
	struct tm TimeM;
	ulong Value;
	/* Create a long value and assign the ftime to it */
	Value = (BlockData.ff_ftime & 0xFFFF) + ((BlockData.ff_fdate << 16) & 0xFFFF000ul);
	FileTime = *((ftime *)&Value);
	/* Convert ftime to a tm time, hopefully */
	TimeM.tm_sec = (FileTime.ft_tsec / 2);
	TimeM.tm_min = FileTime.ft_min;
	TimeM.tm_hour = FileTime.ft_hour;
	TimeM.tm_mday = FileTime.ft_day;
	TimeM.tm_mon = FileTime.ft_month;
	TimeM.tm_year = FileTime.ft_year + 80;
	TimeM.tm_wday = 0;
	TimeM.tm_yday = 0;
	TimeM.tm_isdst = 0;
	/* Convert the tm time to a time_t value */
	return mktime(&TimeM);
}

/*===========================================================================
 *      End of Class Method CFileBlock::GetWriteTime()
 *=========================================================================*/
#endif


/*=========================================================================
 *
 * Class CFindFile Constructor
 *
 *=======================================================================*/
CFindFile::CFindFile(void) {
	FindHandle = NULL_FIND_HANDLE;
}

/*=========================================================================
 *      End of Class CFindFile Constructor
 *=======================================================================*/


/*=========================================================================
 *
 * Class CFindFile Destructor
 *
 *=======================================================================*/
void CFindFile::Destroy(void) {
	/* Ensure the find handle is closed */
	Close();
	FindHandle = NULL_FIND_HANDLE;
	FileBlock.Destroy();
}

/*=========================================================================
 *      End of Class CFindFile Destructor
 *=======================================================================*/


/*=========================================================================
 *
 * Class CFindFile Method - bool Close (void);
 *
 * Closes a file find.  Returns TRUE on success or FALSE on error.
 * Must be called once a find is finished and before another search is
 * started.
 *
 *=======================================================================*/
bool CFindFile::Close(void) {
	//DEFINE_FUNCTION("CFindFile::Close()");

	/* Make sure the filehandle is currently valid */
	if (FindHandle == NULL_FIND_HANDLE) {
		return (FALSE);
	}

	/* For MSDOS, TurboC */
#if defined(__MSDOS__)
	FindHandle = NULL_FIND_HANDLE;
	return (TRUE);
	/* Windows, Borland C++ */
#elif defined(_WIN32) && defined(__BORLANDC__)
	FindClose((HANDLE)FindHandle);
	return (true);
	/* For Windows, Visual C++ */
#elif defined(_WIN32)
	int Result;
	/* Call the Visual C++ function */
	Result = _findclose (FindHandle);
	FindHandle = NULL_FIND_HANDLE;
	return ((Result != 0) ? FALSE : TRUE);
	/* Undefined system in use */
#else
	return (FALSE);
#endif
}

/*=========================================================================
 *      End of Class Method CFindFile::Close()
 *=======================================================================*/


/*===========================================================================
 *
 * Class CFindFile Method - bool FindFirst (pFileSpec, Attribute);
 *
 * Finds the first occurence of the given file spec and attribute.
 * Returns FALSE on any error.
 *
 *=========================================================================*/
bool CFindFile::FindFirst(const char *pFilespec, const int Attribute) {
	DEFINE_FUNCTION("CFindFile::FindFirst()");
	/* Ensure valid input */
	ASSERT(pFilespec != NULL);
	/* Close the previous find, if any */
	Close();
	/* For MSDOS, TurboC */
#if defined(__MSDOS__)
	int Result;
	/* Just call the standard DOS findfirst function */
	Result = findfirst(pFilespec, FileBlock.GetBlockPtr(), Attribute);
	FindHandle = 0;
	return ((Result != 0) ? FALSE : TRUE);
	/* For Windows, Borland C++ */
#elif defined(_WIN32) && defined(__BORLANDC__)
	FileBlock.GetBlock().dwFileAttributes = Attribute;
	strnncpy(FileBlock.GetBlock().cFileName, pFilespec, _MAX_PATH);
	FindHandle = (long)FindFirstFile(pFilespec, &FileBlock);
	return ((FindHandle == (long)INVALID_HANDLE_VALUE) ? FALSE : TRUE);
	/* For Windows, Visual C++ */
#elif defined(_WIN32)
	/* Call the Visual C++ function */
	FindHandle = _findfirst((char *)pFilespec, FileBlock.GetBlockPtr());
	return ((FindHandle == -1) ? FALSE : TRUE);
	/* Undefined system in use */
#else
	return (FALSE);
#endif
}

/*===========================================================================
 *      End of Class Method CFindFile::FindFirst()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CFindFile Method - bool FindNext (void);
 *
 * Finds the next file after a call to FindFirst(). Returns FALSE
 * on any error or TRUE on success.
 *
 *=========================================================================*/
bool CFindFile::FindNext(void) {
	//DEFINE_FUNCTION("CFindFile::FindNext()");
	int Result;

	/* Make sure the current find handle is valid */
	if (FindHandle == NULL_FIND_HANDLE) {
		return (FALSE);
	}

	/* For MSDOS, TurboC */
#if defined(__MSDOS__)
	/* Just call the standard DOS findnext function */
	Result = findnext (FileBlock.GetBlockPtr());
	return ((Result != 0) ? FALSE : TRUE);
	/* For Windows, Borland C++ */
#elif defined(_WIN32) && defined(__BORLANDC__)
	Result = FindNextFile((HANDLE)FindHandle, &FileBlock);
	return (Result == TRUE);
	/* For Windows, Visual C++ */
#elif defined(_WIN32)
	/* Call the Visual C++ function */
	Result = _findnext(FindHandle, FileBlock.GetBlockPtr());
	return ((Result == -1) ? FALSE : TRUE);
	/* Undefined system in use */
#else
	return (FALSE);
#endif
}

/*===========================================================================
 *      End of Class Method CFindFile::FindNext()
 *=========================================================================*/
