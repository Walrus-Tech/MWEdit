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


#if _WIN32
	#include "io.h"
#endif

#include "Common/dl_file.h"


/* Used to indicate an invalid find handle */
#define NULL_FIND_HANDLE (-1l)

/* Platform specific defines */
#if _WIN32
	/* Define the base file block type */
	typedef struct _finddata_t fileblock_t;

	/* Redefine attribute values */
	#define FA_ARCH     _A_ARCH
	#define FA_DIREC    _A_SUBDIR
	#define FA_RDONLY   _A_RDONLY
	#define FA_HIDDEN   _A_HIDDEN
	#define FA_SYSTEM   _A_SYSTEM
	#define FA_NORMAL   _A_NORMAL
#endif


/*=========================================================================
 *
 * Class CFileBlock Definition
 *
 * A class to handle the different variations of the fileblock structure
 * under the various operating systems.
 *
 *=======================================================================*/
class CFileBlock {
  protected:
	fileblock_t BlockData;

  public:
	/* Class Constructor */
	CFileBlock() {
		Destroy();
	}

	/* Class Destructor */
	virtual void Destroy();

	/* Return various members of the file block data */
	fileblock_t &GetBlock() {
		return BlockData;
	}

	fileblock_t *GetBlockPtr() {
		return &BlockData;
	}

	/* Define the get methods depending on the platform */
#if _WIN32
	char *GetName() {
		return &BlockData.name[0];
	}

	int GetAttribute() const {
		return BlockData.attrib;
	}

	time_t GetCreationTime() const {
		return BlockData.time_create;
	}

	time_t GetAccessTime() const {
		return BlockData.time_access;
	}

	time_t GetWriteTime() const {
		return BlockData.time_write;
	}

	ulong GetSize() const {
		return BlockData.size;
	}
#endif
};


/*=========================================================================
 *
 * Begin Class CFindFile Definition
 *
 * Main class used for searching files under many operating systems.
 *
 *=======================================================================*/
class CFindFile {
  protected:
	long FindHandle;      /* Handle for the current find */
	CFileBlock FileBlock; /* Block for holding file info */


  public:
	/* Class Constructor */
	CFindFile();

	/* Class Destructors */
	~CFindFile() {
		Destroy();
	}

	void Destroy();

	/* Closes the file find */
	bool Close();

	/* Find the first occurence of a given file spec */
	bool FindFirst(const char *pFileSpec, const int Attributes = FA_NORMAL);

	/* Find the next occurence of the previous file spec */
	bool FindNext();

	/* Used to get information on a found file */
	char *GetName() {
		return FileBlock.GetName();
	}

	int GetAttribute() {
		return FileBlock.GetAttribute();
	}

	time_t GetCreationTime() {
		return FileBlock.GetCreationTime();
	}

	time_t GetAccessTime() {
		return FileBlock.GetAccessTime();
	}

	time_t GetWriteTime() {
		return FileBlock.GetWriteTime();
	}

	ulong GetSize() {
		return FileBlock.GetSize();
	}

	/* Check the type of the current file */
	bool IsDirectory() {
		return (FileBlock.GetAttribute() & FA_DIREC) == FA_DIREC;
	}

	bool IsSystem() {
		return (FileBlock.GetAttribute() & FA_SYSTEM) == FA_SYSTEM;
	}

	bool IsHidden() {
		return (FileBlock.GetAttribute() & FA_HIDDEN) == FA_HIDDEN;
	}

	bool IsReadOnly() {
		return (FileBlock.GetAttribute() & FA_RDONLY) == FA_RDONLY;
	}

	bool IsArchive() {
		return (FileBlock.GetAttribute() & FA_ARCH) == FA_ARCH;
	}
};


#endif
