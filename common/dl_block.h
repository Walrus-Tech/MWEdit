/*===========================================================================
 *
 * File:    DL_Block.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, April 03, 2001
 *
 * Contains the definition for memory block logging routines for debug
 * builds.  If allocated memory blocks are stored in the block info
 * structure upon creation and removed upon deletion, the logging routines
 * can trace memory blocks that are deleted more than once or blocks that
 * are never freed.
 *
 * The code is primarily from "Writing Solid Code" by Steve Maguire.
 *
 *=========================================================================*/
#if _DEBUG
#ifndef __DL_BLOCK_H
#define __DL_BLOCK_H


#include "Common/dl_base.h"


#define BLOCK_INITIAL_ARRAYSIZE  256
#define BLOCK_RESIZEARRAY_FACTOR 2


/*===========================================================================
 *
 * Begin Block Info Structure
 *
 * One element of the block info singly linked list.
 *
 *=========================================================================*/
typedef struct BLOCKINFO {
	//struct BLOCKINFO* pNext;    /* Pointer to the next block info structure */
	byte *pPointer;     /* Pointer to the start of block */
	TCHAR *pName;       /* The name of the pointer (optional) */
	TCHAR *pFunc;       /* Calling function name, optional */
	size_t Size;        /* Size of the memory block */
	boolean Referenced; /* Used to track dangling pointers */
} blockinfo_t;


/* Check for dangling, unreferenced pointers */
void CheckMemoryRefs();

/* Reset all the referenced flags of blocks */
void ClearMemoryRefs();

/* Create a new block info node */
boolean CreateBlockInfo(void *pNewBlock, const size_t NewSize);
boolean CreateBlockInfo(void *pNewBlock,
                        const size_t NewSize,
                        const TCHAR *pName,
                        const TCHAR *pFunc);

/* Delete a block info node */
void FreeBlockInfo(void *pBlock);

/* Return the current number of allocated blocks */
size_t GetNumBlocks();

/* Checks for the given memory block in the current block list */
boolean IsValidPointer(void *pBlock, const size_t MinSize);
boolean IsValidPointer(void *pBlock);

/* Flag the referenced member of the block */
void NoteMemoryRef(void *pBlock);

/* Outputs all the block information to the system log file */
void OutputBlockInfo();

/* Retrieve the size of a block */
size_t SizeOfBlock(void *pBlock);

/* Update a block node information */
void UpdateBlockInfo(void *pOldBlock, void *pNewBlock, const size_t NewSize);


#endif
#endif /* End of if defined(_DEBUG) */
