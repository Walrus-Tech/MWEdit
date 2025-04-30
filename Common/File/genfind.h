/*===========================================================================
 *
 * File:    Genfind.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, June 06, 2001
 *
 * Implements a system portable class CFileFind used for iterating
 * through files in the current directory.
 *
 *=========================================================================*/
#ifndef __GENFIND_H
#define __GENFIND_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/

#if defined(__MSDOS__)
	#include "dos.h"
	#include "dir.h"
	#include "time.h"
	#include "io.h"
#elif defined (__BORLANDC__)
	#include "sys/types.h"
	//#include "sysutils.hpp"
	#include "io.h"
#elif defined(_WIN32)
	#include "io.h"
#endif

#include "dl_file.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*=========================================================================
 *
 * Begin Defines
 *
 *=======================================================================*/

/* Used to indicate an invalid find handle */
#define NULL_FIND_HANDLE (-1l)

/* Platform specific defines */
#if defined(_WIN32) && defined(__BORLANDC__)
	typedef WIN32_FIND_DATA fileblock_t;

	/* Redefine attribute values */
	#define FA_ARCH     FILE_ATTRIBUTE_ARCHIVE
	#define FA_DIREC    FILE_ATTRIBUTE_DIRECTORY
	#define FA_RDONLY   FILE_ATTRIBUTE_READONLY
	#define FA_HIDDEN   FILE_ATTRIBUTE_HIDDEN
	#define FA_SYSTEM   FILE_ATTRIBUTE_SYSTEM
	#define FA_NORMAL   FILE_ATTRIBUTE_NORMAL

#elif defined(_WIN32)

	/* Define the base file block type */
	typedef struct _finddata_t fileblock_t;

	/* Redefine attribute values */
	#define FA_ARCH     _A_ARCH
	#define FA_DIREC    _A_SUBDIR
	#define FA_RDONLY   _A_RDONLY
	#define FA_HIDDEN   _A_HIDDEN
	#define FA_SYSTEM   _A_SYSTEM
	#define FA_NORMAL   _A_NORMAL



#elif defined(__MSDOS__)

	/* Define the base file block type */
	typedef struct ffblk fileblock_t;
#endif

/*=========================================================================
 *      End of Defines
 *=======================================================================*/


/*=========================================================================
 *
 * Class CFileBlock Definition
 *
 * A class to handle the different variations of the fileblock structure
 * under the various operating systems.
 *
 *=======================================================================*/
class CFileBlock {

	/* Begin protected class members */
  protected:
	fileblock_t BlockData;

	/* Begin public class methods */
  public:

	/* Class Constructor */
	CFileBlock(void) {
		Destroy();
	}

	/* Class Destructor */
	virtual void Destroy(void);

	/* Return various members of the file block data */
	fileblock_t &GetBlock(void) {
		return (BlockData);
	}

	fileblock_t *GetBlockPtr(void) {
		return (&BlockData);
	}

	/* Define the get methods depending on the platform */
#if defined (_WIN32) && defined(__BORLANDC__)
	time_t ConvertFileTime(const FILETIME &FileTime) const;

	char *GetName(void) {
		return (&BlockData.cFileName[0]);
	}

	int GetAttribute(void) const {
		return (BlockData.dwFileAttributes);
	}

	time_t GetCreationTime(void) const {
		return (ConvertFileTime(BlockData.ftCreationTime));
	}

	time_t GetAccessTime(void) const {
		return (ConvertFileTime(BlockData.ftLastAccessTime ));
	}

	time_t GetWriteTime(void) const {
		return (ConvertFileTime(BlockData.ftLastWriteTime ));
	}

	ulong GetSize(void) const {
		return (BlockData.nFileSizeLow );
	}

#elif defined(_WIN32)
	char *GetName(void) {
		return (&BlockData.name[0]);
	}

	int GetAttribute(void) const {
		return (BlockData.attrib);
	}

	time_t GetCreationTime(void) const {
		return (BlockData.time_create);
	}

	time_t GetAccessTime(void) const {
		return (BlockData.time_access);
	}

	time_t GetWriteTime(void) const {
		return (BlockData.time_write);
	}

	ulong GetSize(void) const {
		return (BlockData.size);
	}

#elif defined(__MSDOS__)
	char *GetName(void) const {
		return (char *)(&BlockData.ff_name[0]);
	}

	int GetAttribute(void) const {
		return (BlockData.ff_attrib);
	}

	time_t GetCreationTime(void) const {
		return (-1l);
	}

	time_t GetAccessTime(void) const {
		return (-1l);
	}

	time_t GetWriteTime(void) const;
	ulong GetSize(void) const {
		return (BlockData.ff_fsize);
	}

#endif

};

/*=========================================================================
 *      End of Class CFileBlock Definition
 *=======================================================================*/



/*=========================================================================
 *
 * Begin Class CFindFile Definition
 *
 * Main class used for searching files under many operating systems.
 *
 *=======================================================================*/
class CFindFile {

	/* Begin protected class members */
  protected:
	long FindHandle;    /* Handle for the current find */
	CFileBlock FileBlock;     /* Block for holding file info */


	/* Begin public class methods */
  public:

	/* Class Constructor */
	CFindFile(void);

	/* Class Destructors */
	~CFindFile(void) {
		Destroy();
	}

	void Destroy(void);

	/* Closes the file find */
	bool Close(void);

	/* Find the first occurence of a given file spec */
	bool FindFirst(const char *pFileSpec, const int Attributes = FA_NORMAL);

	/* Find the next occurence of the previous file spec */
	bool FindNext(void);

	/* Used to get information on a found file */
	char *GetName(void) {
		return (FileBlock.GetName());
	}

	int GetAttribute(void) {
		return (FileBlock.GetAttribute());
	}

	time_t GetCreationTime(void) {
		return (FileBlock.GetCreationTime());
	}

	time_t GetAccessTime(void) {
		return (FileBlock.GetAccessTime());
	}

	time_t GetWriteTime(void) {
		return (FileBlock.GetWriteTime());
	}

	ulong GetSize(void) {
		return (FileBlock.GetSize());
	}

	/* Check the type of the current file */
	bool IsDirectory(void) {
		return (FileBlock.GetAttribute() & FA_DIREC) == FA_DIREC;
	}

	bool IsSystem(void) {
		return (FileBlock.GetAttribute() & FA_SYSTEM) == FA_SYSTEM;
	}

	bool IsHidden(void) {
		return (FileBlock.GetAttribute() & FA_HIDDEN) == FA_HIDDEN;
	}

	bool IsReadOnly(void) {
		return (FileBlock.GetAttribute() & FA_RDONLY) == FA_RDONLY;
	}

	bool IsArchive(void) {
		return (FileBlock.GetAttribute() & FA_ARCH) == FA_ARCH;
	}

};

/*=========================================================================
 *      End of Class CFindFile Definition
 *=======================================================================*/


#endif
/*===========================================================================
 *      End of File Genfind.H
 *=========================================================================*/
