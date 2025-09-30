/*===========================================================================
 *
 * File:    Genfind.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, June 06, 2001
 *
 * Implements the CFileFind class
 *
 *=========================================================================*/
#if _WIN32
	#include "io.h"
#endif

#include "file\genfind.h"


DEFINE_FILE("GenFind.cpp");


/*=========================================================================
 *
 * Class CFileBlock Destructor
 *
 *=======================================================================*/
void CFileBlock::Destroy() {
	//DEFINE_FUNCTION("CFileBlock::Destroy");
	/* Clear all elements to 0 initially depending on platform */
#if _WIN32
	BlockData.attrib = FA_NORMAL;
	BlockData.name[0] = NULL_CHAR;
	BlockData.time_create = -1;
	BlockData.time_access = -1;
	BlockData.time_write = -1;
	BlockData.size = 0;
#endif
}


/*=========================================================================
 *
 * Class CFindFile Constructor
 *
 *=======================================================================*/
CFindFile::CFindFile() {
	FindHandle = NULL_FIND_HANDLE;
}


/*=========================================================================
 *
 * Class CFindFile Destructor
 *
 *=======================================================================*/
void CFindFile::Destroy() {
	/* Ensure the find handle is closed */
	Close();
	FindHandle = NULL_FIND_HANDLE;
	FileBlock.Destroy();
}


/*=========================================================================
 *
 * Class CFindFile Method - bool Close (void);
 *
 * Closes a file find.  Returns TRUE on success or FALSE on error.
 * Must be called once a find is finished and before another search is
 * started.
 *
 *=======================================================================*/
bool CFindFile::Close() {
	//DEFINE_FUNCTION("CFindFile::Close()");

	/* Make sure the filehandle is currently valid */
	if (FindHandle == NULL_FIND_HANDLE) {
		return FALSE;
	}

	/* For Windows, Visual C++ */
#if _WIN32
	int Result;
	/* Call the Visual C++ function */
	Result = _findclose(FindHandle);
	FindHandle = NULL_FIND_HANDLE;
	return (Result != 0) ? FALSE : TRUE;
	/* Undefined system in use */
#else
	return FALSE;
#endif
}


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
	/* For Windows, Visual C++ */
#if _WIN32
	/* Call the Visual C++ function */
	FindHandle = _findfirst((char *)pFilespec, FileBlock.GetBlockPtr());
	return (FindHandle == -1) ? FALSE : TRUE;
	/* Undefined system in use */
#else
	return FALSE;
#endif
}


/*===========================================================================
 *
 * Class CFindFile Method - bool FindNext (void);
 *
 * Finds the next file after a call to FindFirst(). Returns FALSE
 * on any error or TRUE on success.
 *
 *=========================================================================*/
bool CFindFile::FindNext() {
	//DEFINE_FUNCTION("CFindFile::FindNext()");
	int Result;

	/* Make sure the current find handle is valid */
	if (FindHandle == NULL_FIND_HANDLE) {
		return FALSE;
	}

	/* For Windows, Visual C++ */
#if _WIN32
	/* Call the Visual C++ function */
	Result = _findnext(FindHandle, FileBlock.GetBlockPtr());
	return (Result == -1) ? FALSE : TRUE;
	/* Undefined system in use */
#else
	return FALSE;
#endif
}
