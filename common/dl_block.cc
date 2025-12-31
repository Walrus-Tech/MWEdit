/*===========================================================================
 *
 * File:    DL_Block.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, April 03, 2001
 *
 * Implements the memory logging routines for debug builds.
 * If allocated memory blocks are stored in the block info structure
 * upon creation and removed upon deletion, the logging routines
 * can trace memory blocks that are deleted more than once or blocks that
 * are never freed.
 *
 * The code is primarily from "Writing Solid Code" by Steve Maguire.
 *
 * 4 September 2002
 *  - Changed from a linked-list to a resizable array of pointers to
 *    increase the speed when dealing with a large number of allocated
 *    pointers.
 *
 *=========================================================================*/
#if _DEBUG

#include "Common/dl_block.h"
#include "Common/dl_log.h"
#include <string.h>


DEFINE_FILE("DL_Block.cpp");

/* Allocated array of blocks */
static blockinfo_t **l_ppBlocks = NULL;
static int l_NumBlocks = 0;
static int l_AllocatedBlocks = 0;


/*===========================================================================
 *
 * Begin Pointer Comparison Macros
 *
 * The functions in this file must compare arbitrary pointers (ie, they
 * could point to anything), which is not always portable according to ANSI.
 * Thus, the following macros are used to define pointer comparisons to
 * allow the correct comparisons to be made across various platforms.
 * Ensure the comparisons are correct for your implemenation.
 *
 *=========================================================================*/
#define IsPtrLess(pLeft, pRight)      ((pLeft) <  (pRight))
#define IsPtrGreater(pLeft, pRight)   ((pLeft) >  (pRight))
#define IsPtrEqual(pLeft, pRight)     ((pLeft) == (pRight))
#define IsPtrLessEq(pLeft, pRight)    ((pLeft) <= (pRight))
#define IsPtrGreaterEq(pLeft, pRight) ((pLeft) >= (pRight))


/* Points to the start of a singly linked list of memory block
 * information structures */
//static blockinfo_t* pBIHead = NULL;


/*===========================================================================
 *
 * Function - void ResizeBlockArray (void);
 *
 * Local function to increase the size of the block array.  The current
 * block information is copied into the new block array.
 *
 *=========================================================================*/
void ResizeBlockArray() {
	DEFINE_FUNCTION("ResizeBlockArray()");
	blockinfo_t **ppNewArray;

	/* Determine the new size of the array */
	if (l_ppBlocks == NULL) {
		l_AllocatedBlocks = BLOCK_INITIAL_ARRAYSIZE;
	} else {
		ASSERT(l_AllocatedBlocks < INT_MAX);
		l_AllocatedBlocks *= BLOCK_RESIZEARRAY_FACTOR;
	}

	/* Allocate the new array */
	ppNewArray = new blockinfo_t *[l_AllocatedBlocks];
	ASSERT(ppNewArray != NULL);

	/* Copy existing blocks if required */
	if (l_ppBlocks != NULL) {
		memcpy(ppNewArray, l_ppBlocks, sizeof(blockinfo_t *) * l_NumBlocks);
		delete[] l_ppBlocks;
	}

	l_ppBlocks = ppNewArray;
}


/*===========================================================================
 *
 * Function - static blockinfo_t* GetBlockInfo (pBlock);
 *
 * A local function which attempts to return the block information structure
 * for the given memory block.  If the block does not exist, the function
 * will ASSERT.  The function always returns a valid block.
 *
 *=========================================================================*/
static blockinfo_t *GetBlockInfo(void *pBlock) {
	DEFINE_FUNCTION("GetBlockInfo()");
	int BlockIndex;
	byte *pStart;
	byte *pEnd;
	byte *pByteBlock = (byte *)pBlock;

	/* Look through the array for a match */
	for (BlockIndex = 0; BlockIndex < l_NumBlocks; BlockIndex++) {
		pStart = l_ppBlocks[BlockIndex]->pPointer;
		pEnd = pStart + l_ppBlocks[BlockIndex]->Size - 1;

		if (IsPtrGreaterEq(pByteBlock, pStart) && IsPtrLessEq(pByteBlock, pEnd)) {
			break;
		}
	}

	/* Ensure a valid block was found */
	ASSERT(BlockIndex < l_NumBlocks);
	return l_ppBlocks[BlockIndex];
}


/*===========================================================================
 *
 * Function - void CheckMemoryRefs (void);
 *
 * Checks the reference member of all memory block logs looking for blocks
 * that have not been referenced with NoteMemoryRef().  The function
 * ASSERTs if any unflagged block is found.  Use this function to check
 * for dangling pointers in your application.
 *
 *=========================================================================*/
void CheckMemoryRefs() {
	DEFINE_FUNCTION("CheckMemoryRefs()");
	int BlockIndex;
	blockinfo_t *pBlockInfo;

	for (BlockIndex = 0; BlockIndex < l_NumBlocks; BlockIndex++) {
		pBlockInfo = l_ppBlocks[BlockIndex];
		/* Simple check for the integrity of the block.  If this ASSERT
		 * fires it indicates that the blockinfo code has caused an
		 * error or its memory has been trashed. */
		ASSERT(pBlockInfo->pPointer != NULL && pBlockInfo->Size != 0);
		/* Ensure that the block has been referenced by a call to
		 * NoteMemoryRef(). If this ASSERT fires it indicates either
		 * a dangling pointer or that not all pointers have been
		 * accounted for. */
		ASSERT(pBlockInfo->Referenced);
	}
}


/*===========================================================================
 *
 * Function - void ClearMemoryRefs (void);
 *
 * Clears all the reference flags of the current memory block logs.
 * Use this function before NoteMemoryRefs() to check for dangling pointers
 * in your application.
 *
 *=========================================================================*/
void ClearMemoryRefs() {
	//DEFINE_FUNCTION("ClearMemoryRefs()");
	int BlockIndex;

	for (BlockIndex = 0; BlockIndex < l_NumBlocks; BlockIndex++) {
		l_ppBlocks[BlockIndex]->Referenced = FALSE;
	}
}


/*===========================================================================
 *
 * Function - boolean CreateBlockInfo (pNewBlock, NewSize);
 *
 * Creates a new memory block information structure for the given memory.
 * Returns TRUE on success or FALSE if the new block log could not be
 * created.  On failure the newly allocated block should be freed.
 *
 *=========================================================================*/
boolean CreateBlockInfo(void *pNewBlock, const size_t NewSize) {
	DEFINE_FUNCTION("CreateBlockInfo(void*, size_t)");
	blockinfo_t *pBlockInfo;
	/* Ensure valid input */
	ASSERT(pNewBlock != NULL && NewSize != 0);
	/* Create the memory log structure */
	pBlockInfo = new blockinfo_t;

	if (pBlockInfo == NULL) {
		return FALSE;
	}

	/* Initialize the new memory block */
	pBlockInfo->pPointer = (byte *)pNewBlock;
	pBlockInfo->Size = NewSize;
	pBlockInfo->Referenced = TRUE;
	pBlockInfo->pName = NULL;

	/* Resize blocks array if required */
	if (l_ppBlocks == NULL || l_NumBlocks >= l_AllocatedBlocks) {
		ResizeBlockArray();
	}

	/* Add the block info to the array */
	l_ppBlocks[l_NumBlocks] = pBlockInfo;
	l_NumBlocks++;
	return TRUE;
}


/*===========================================================================
 *
 * Function - boolean CreateBlockInfo (pNewBlock, NewSize, pName, pFunc);
 *
 * Creates a new memory block information structure for the given memory.
 * Returns TRUE on success or FALSE if the new block log could not be
 * created.  On failure the newly allocated block should be freed.
 * Accepts the given valid name string for thje pointer name.  ASSERTs if
 * the input pNname pointer is not valid.
 *
 *=========================================================================*/
boolean CreateBlockInfo(void *pNewBlock,
                        const size_t NewSize,
                        const TCHAR *pName,
                        const TCHAR *pFunc) {
	DEFINE_FUNCTION("CreateBlockInfo(void*, size_t, char*)");
	blockinfo_t *pBlockInfo;
	/* Ensure valid input */
	ASSERT(pNewBlock != NULL && NewSize != 0 && pName != NULL);
	/* Create the memory log structure */
	pBlockInfo = new blockinfo_t;

	if (pBlockInfo == NULL) {
		return FALSE;
	}

	/* Initialize the new memory block */
	pBlockInfo->pPointer = (byte *)pNewBlock;
	pBlockInfo->Size = NewSize;
	pBlockInfo->Referenced = TRUE;
	/* Attempt to create the name string */
	pBlockInfo->pName = new TCHAR[TSTRLEN(pName) +1];

	if (pBlockInfo->pName == NULL) {
		memset (pBlockInfo, (int)GARBAGE_CHAR, sizeof(blockinfo_t));
		delete pBlockInfo;
		return FALSE;
	}

	TSTRCPY(pBlockInfo->pName, pName);

	/* Attempt to create the function string if required */
	if (pFunc == NULL) {
		pBlockInfo->pFunc = NULL;
	} else {
		pBlockInfo->pFunc = new TCHAR[TSTRLEN(pFunc) +1];

		if (pBlockInfo->pFunc == NULL) {
			memset (pBlockInfo, (int)GARBAGE_CHAR, sizeof(blockinfo_t));
			delete pBlockInfo;
			return FALSE;
		}

		TSTRCPY(pBlockInfo->pFunc, pFunc);
	}

	/* Resize blocks array if required */
	if (l_ppBlocks == NULL || l_NumBlocks >= l_AllocatedBlocks) {
		ResizeBlockArray();
	}

	/* Add the block info to the array */
	l_ppBlocks[l_NumBlocks] = pBlockInfo;
	l_NumBlocks++;
	return TRUE;
}


/*===========================================================================
 *
 * Function - void FreeBlockInfo (void* pBlock)
 *
 * Attempts to remove the block info for the given memory.  The function
 * will ASSERT if given an invalid memory block.
 *
 *=========================================================================*/
void FreeBlockInfo(void *pBlock) {
	DEFINE_FUNCTION("FreeBlockInfo()");
	int BlockIndex;
	blockinfo_t *pBlockInfo = NULL;
	byte *pByteBlock = (byte *)pBlock;
	/* Ensure valid input */
	ASSERT(pBlock != NULL);

	/* Search the block linked list for a match, from head to tail */
	for (BlockIndex = 0; BlockIndex < l_NumBlocks; BlockIndex++) {
		pBlockInfo = l_ppBlocks[BlockIndex];

		/* Check for a block match */
		if (IsPtrEqual(pBlockInfo->pPointer, pByteBlock)) {
			memmove(l_ppBlocks + BlockIndex,
			        l_ppBlocks + BlockIndex + 1,
			        sizeof(blockinfo_t *) * (l_NumBlocks - BlockIndex));
			l_NumBlocks--;
			break;
		}
	}

	/* Ensure a valid block was found to be deleted */
	ASSERT(pBlockInfo != NULL);
	//ASSERT(BlockIndex < l_NumBlocks);

	/* Delete the pointer name, if any */
	if (pBlockInfo->pName != NULL) {
		memset(pBlockInfo->pName,
		       (int)GARBAGE_CHAR,
		       (TSTRLEN(pBlockInfo->pName) + 1) * sizeof(TCHAR));
		delete[] pBlockInfo->pName;
	}

	/* Delete the function name, if any */
	if (pBlockInfo->pFunc != NULL) {
		memset(pBlockInfo->pFunc,
		       (int)GARBAGE_CHAR,
		       (TSTRLEN(pBlockInfo->pFunc) + 1) * sizeof(TCHAR));
		delete[] pBlockInfo->pFunc;
	}

	/* Clear the blockinfo structure and delete */
	memset(pBlockInfo, (int)GARBAGE_CHAR, sizeof(blockinfo_t));
	delete pBlockInfo;
}


/*===========================================================================
 *
 * Function - size_t GetNumBlocks (void);
 *
 * Returns the total number of allocated blocks.
 *
 *=========================================================================*/
size_t GetNumBlocks() {
	//DEFINE_FUNCTION("GetNumBlocks()");
	return l_NumBlocks;
}


/*===========================================================================
 *
 * Function - boolean IsValidPointer (pBlock, MinSize);
 *
 * Ensures that the given block is a valid memory block and that it is
 * at least MinSize bytes in size (from the given pointer to the
 * end of the block).  The passed block does not have to be the very start
 * of an allocated block, but can be anywhere in the block.
 *
 * The function will ASSERT if the block pointer or size is invalid, and
 * never actually returns NULL.  The value returned is to allow the
 * function to be used in an ASSERT statement easily, such as
 *      ASSERT(IsValidPointer(pSomeObject, size));
  *
 *=========================================================================*/
boolean IsValidPointer(void *pBlock, const size_t MinSize) {
	DEFINE_FUNCTION("IsValidPointer(void*, size_t)");
	blockinfo_t *pBlockInfo;
	byte *pByteBlock = (byte *)pBlock;
	/* Ensure valid input */
	ASSERT(pBlock != NULL && MinSize != 0);
	pBlockInfo = GetBlockInfo(pBlock);
	/* Ensure that the block size is valid */
	ASSERT(IsPtrLessEq(pByteBlock + MinSize, pBlockInfo->pPointer + pBlockInfo->Size));
	return TRUE;
}


/*===========================================================================
 *
 * Function - boolean IsValidPointer (pBlock);
 *
 * Same as IsValidPointer(void*, size_t) except that it just checks if
 * the given pointer is valid without requiring a minimum size.
 *
 * The function will ASSERT if the block pointer or size is invalid, and
 * never actually returns NULL.  The value returned is to allow the
 * function to be used in an ASSERT statement easily, such as
 *      ASSERT(IsValidPointer(pSomeObject));
  *
 *=========================================================================*/
boolean IsValidPointer(void *pBlock) {
	DEFINE_FUNCTION("IsValidPointer(void*)");
	blockinfo_t *pBlockInfo;
	/* Ensure valid input */
	ASSERT(pBlock != NULL);
	/* Attempt to get the block info */
	pBlockInfo = GetBlockInfo(pBlock);

	if (pBlockInfo == NULL) {
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - void NoteMemoryRef (pBlock);
 *
 * Sets the reference flag for the log associated with the given memory
 * block.  The function ASSERTs if the given block is not valid.  Note that
 * the input block does not have to be the start of the allocated block,
 * but anywhere within the block.
 *
 *=========================================================================*/
void NoteMemoryRef(void *pBlock) {
	//DEFINE_FUNCTION("NoteMemoryRef()");
	blockinfo_t *pBlockInfo;
	pBlockInfo = GetBlockInfo(pBlock);
	pBlockInfo->Referenced = TRUE;
}


/*===========================================================================
 *
 * Function - void OutputBlockInfo (void);
 *
 * Outputs the current block information to the system log file.
 *
 *=========================================================================*/
void OutputBlockInfo() {
	//DEFINE_FUNCTION("OutputBlockInfo()");
	blockinfo_t *pBlockInfo;
	int BlockIndex;
	long Index = 1;
	long MemorySize = 0l;
	SystemLog.Printf(_T("Outputting custom allocation blocks..."));

	for (BlockIndex = 0; BlockIndex < l_NumBlocks; BlockIndex++, Index++) {
		pBlockInfo = l_ppBlocks[BlockIndex];
		MemorySize += pBlockInfo->Size;
		SystemLog.Printf(_T("\t\t%3ld) %p (%s, Func %s, %8u bytes), %s."),
		                 Index,
		                 pBlockInfo->pPointer,
		                 pBlockInfo->pName == NULL ? _T("NULL") : pBlockInfo->pName,
		                 pBlockInfo->pFunc == NULL ? _T("NULL") : pBlockInfo->pFunc,
		                 pBlockInfo->Size,
		                 pBlockInfo->Referenced ? _T("is Referenced") : _T("NOT Referenced"));
	}

	SystemLog.Printf(_T("\tOutput %ld bytes in %ld blocks..."), MemorySize, Index - 1);
}


/*===========================================================================
 *
 * Function - size_t SizeOfBlock (pBlock);
 *
 * Attempts to get the allocated size of the given block.  The function
 * will ASSERT if the passed pointer is invalid.
 *
 *=========================================================================*/
size_t SizeOfBlock(void *pBlock) {
	DEFINE_FUNCTION("SizeOfBlock()");
	blockinfo_t *pBlockInfo;
	pBlockInfo = GetBlockInfo(pBlock);
	ASSERT((byte *)pBlock == pBlockInfo->pPointer);
	return pBlockInfo->Size;
}


/*===========================================================================
 *
 * Function - void UpdateBlockInfo (pOldBlock, pNewBlock, NewSize);
 *
 * Attempts to update a log structure for a memory block.  If any of the
 * input parameters are invalid, the function will ASSERT.
 *
 *=========================================================================*/
void UpdateBlockInfo(void *pOldBlock, void *pNewBlock, const size_t NewSize) {
	DEFINE_FUNCTION("UpdateBlockInfo()");
	blockinfo_t *pBlockInfo;
	/* Ensure valid input */
	ASSERT(pNewBlock != NULL && NewSize != 0);
	/* Attempt to retrieve the block information */
	pBlockInfo = GetBlockInfo(pOldBlock);
	ASSERT((byte *)pOldBlock == pBlockInfo->pPointer);
	/* Update the log information */
	pBlockInfo->pPointer = (byte *)pNewBlock;
	pBlockInfo->Size = NewSize;
}


#endif /* End of if defined(_DEBUG) */
