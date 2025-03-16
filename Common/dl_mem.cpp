/*===========================================================================
 *
 * File:    DL_Mem.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Sunday, April 01, 2001
 *
 * Implements memory specific routines for Dave's Library of common code.
 *
 * Version History
 * -------------------------------------------------------------------------
 * 21 January 2003
 *  - CreateString(TCHAR*) now accepts NULL input (returns NULL).
 *
 *=========================================================================*/

/* Include Files */
#include "dl_mem.h"
#include <string.h>

#if !defined(_WIN32_WCE)
	#include <time.h>

	#if defined(_MSC_VER)
		//#include <alloc.h>
	#endif
#endif

#if defined(__BCPLUSPLUS__)
	#include "alloc.h"
	#include "malloc.h"
#endif

#include <ctype.h>

#if defined(_WIN32)
	#include <windows.h>
#endif


/*===========================================================================
 *
 * Begin Local Variables
 *
 *=========================================================================*/
DEFINE_FILE("DL_Mem.h");
/*===========================================================================
 *      End of Local Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void* AllocateMemory (const size_t Size);
 *
 * For use when you always want a valid block of new memory returned.
 * Attempts to allocate the given number of bytes (0 is an invalid size)
 * and return the pointer to the new block of memory.  On allocation
 * error the function throws an exception.
 *
 *=========================================================================*/
void *AllocateMemory (const size_t Size) {
	DEFINE_FUNCTION("AllocateMemory(size_t)");
	void *pNewObject;
	/* Ensure valid input */
	ASSERT(Size != 0);
	/* Attempt to allocate memory */
	CreateArrayPointer(pNewObject, TCHAR, Size);
	/* Initialize memory in debug mode */
#if defined(_DEBUG)
	memset(pNewObject, GARBAGE_CHAR, Size * sizeof(TCHAR));
#endif
	return (pNewObject);
}

/*===========================================================================
 *      End of Function AllocateMemory()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - TCHAR* CreateString (pString);
 *
 * For use when you always want a valid new string created.
 * Attempts to allocate a new string and copies the contents of the given
 * string into it.  Throws an exception on allocation error and outputs
 * error message. Assumes the input string is valid (asserts if it isn't).
 *
 *=======================================================================*/
TCHAR *CreateString (const TCHAR* pString) {
	DEFINE_FUNCTION("CreateString(TCHAR*)");
	TCHAR* pNewString;
	size_t NewSize;

	/* Ensure valid input */
	if (pString == NULL) {
		return (NULL);
	}

	/* Get the length of the new string and allocate it */
	NewSize = TSTRLEN(pString) + 1;
	CreateArrayPointer(pNewString, TCHAR, NewSize);
	/* Copy the string to the new location */
	TSTRCPY(pNewString, pString);
	return (pNewString);
}

/*=========================================================================
 *      End of Function CreateString()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - TCHAR* CreateString (StringSize);
 *
 * For use when you always want a valid new string created.
 * Same as CreateString() above but creates a string pointer of
 * the given length (plus one for the terminating NULL).  String is
 * initially set to the empty string.
 *
 *=======================================================================*/
TCHAR *CreateString (const size_t StringSize) {
	DEFINE_FUNCTION("CreateString(size_t)");
	TCHAR* pNewString;
	/* Allocate the new string pointer */
	CreateArrayPointer(pNewString, TCHAR, StringSize + 1);
	*pNewString = NULL_CHAR;
	pNewString[StringSize] = NULL_CHAR;
	return (pNewString);
}

/*=========================================================================
 *      End of Function CreateString()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - bool CreateString (ppNewString, pSourceString);
 *
 * Attempts to create a new string from the input string, returning the
 * result in the ppNewString pointer.  Returns TRUE on success or FALSE
 * on any error (source string is NULL).  Throws an exception if the
 * string could not be allocated.
 *
 *=========================================================================*/
bool CreateString (TCHAR** ppNewString, const TCHAR* pSourceString) {
	DEFINE_FUNCTION("CreateString(TCHAR**, TCHAR*)");
	/* Ensure valid input */
	ASSERT(ppNewString != NULL);

	/* Special case for a NULL input string */
	if (pSourceString == NULL) {
		*ppNewString = NULL;
		return (FALSE);
	}

	/* Create the new string */
	*ppNewString = CreateString(pSourceString);
	return (TRUE);
}

/*===========================================================================
 *      End of Function CreateString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CreateString (ppNewString, StringSize);
 *
 * Attempts to create a new string from the given size, returning the
 * result in the ppNewString pointer.  Returns TRUE on success or FALSE
 * on any error (source string is NULL).  Throws an exception if the
 * string could not be allocated.
 *
 *=========================================================================*/
bool CreateString (TCHAR** ppNewString, const size_t StringSize) {
	DEFINE_FUNCTION("CreateString(TCHAR**, size_t)");
	/* Ensure valid input */
	ASSERT(ppNewString != NULL);
	/* Create the new string */
	*ppNewString = CreateString(StringSize);
	return (TRUE);
}

/*===========================================================================
 *      End of Function CreateString()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - bool GetFreeMemory (Memory);
 *
 * Returns the number of bytes available for allocation.
 * Returns FALSE on any error (if the amount of memory could not
 * be retrieved).
 *
 *=======================================================================*/
bool GetFreeMemory (long &Memory) {
	DEFINE_FUNCTION("GetFreeMemory()");
	/*---------- Borland 16 bit ---------------------------------------------*/
#if defined (__BCPLUSPLUS__)
	Memory = 0;
	return (TRUE);
	/*---------- DOS real mode implementation -------------------------------*/
#elif defined (__MSDOS__)
	Memory = farcoreleft();
	return (TRUE);
	/*---------- Windows implementation -------------------------------------*/
#elif defined(_WIN32)
	MEMORYSTATUS Status;
	GlobalMemoryStatus(&Status);
	Memory = (long) Status.dwAvailVirtual;
	return (TRUE);
	/*---------- Any unknown system implementation --------------------------*/
#else
	ASSERT(FALSE);
	return (FALSE);
#endif
}

/*=========================================================================
 *      End of Function GetFreeMemory()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - bool GetTotalMemory (Memory)
 *
 * Returns the total amount of memory on the system in bytes.
 * On error the function returns FALSE.
 *
 *=======================================================================*/
bool GetTotalMemory (long &Memory) {
	DEFINE_FUNCTION("GetTotalMemory()");
	/*---------- Borland 16 bit ---------------------------------------------*/
#if defined (__BCPLUSPLUS__)
	Memory = 0;
	return (TRUE);
	/*---------- DOS real mode implementation -------------------------------*/
#elif defined(__TURBOC__)
	struct heapinfo HeapInfo;
	long MemorySize = 0l;

	/* Make sure the heap is not corrupt */
	if (heapcheck() != _HEAPOK) {
		return (FALSE);
	}

	GetFreeMemory(MemorySize);
	/* Walk through the heap counting used and free blocks */
	HeapInfo.ptr = NULL;

	while (heapwalk(&HeapInfo) == _HEAPOK) {
		if (HeapInfo.in_use) {
			MemorySize += HeapInfo.size;
		}
	}

	return (TRUE);
	/*---------- Windows implementation -------------------------------------*/
#elif defined(_WIN32)
	MEMORYSTATUS Status;
	GlobalMemoryStatus(&Status);
	Memory = (long) Status.dwAvailVirtual;
	return (TRUE);
	/*---------- Any unknown system implementation --------------------------*/
#else
	ASSERT(FALSE);
	return (FALSE);
#endif
}

/*=========================================================================
 *      End of Function GetTotalMemory()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - bool GetUsedMemory (Memory);
 *
 * Returns the amount of allocated memory in bytes.  On error the function
 * returns FALSE.
 *
 *=======================================================================*/
bool GetUsedMemory (long &Memory) {
	//DEFINE_FUNCTION("GetUserMemory()");
	long MemoryFree = 0;
	long MemoryTotal;
	bool Result;
	/* Get the total/free memory on the system, ensuring they are valid */
	Result = GetTotalMemory(MemoryTotal);

	if (Result) {
		Result = GetFreeMemory(MemoryFree);
	}

	if (!Result) {
		return (FALSE);
	}

	/* Compute the difference in memory */
	Memory = MemoryTotal - MemoryFree;
	return (TRUE);
}

/*=========================================================================
 *      End of Function GetUsedMemory()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - int GetHeapStatus (void);
 *
 * Checks and returns the validity of the heap.  Return values include
 *  HEAP_OK     - Heap is ok.
 *      HEAP_EMPTY  - Heap doesn't exist or not initialized..
 *  HEAP_CORRUPT    - Heap is corrupt.
 *  HEAP_NOTDEFINED - No defined heap status function on current system.
 *
 * Not all values are defined in all systems.
 *
 *=======================================================================*/
int GetHeapStatus (void) {
	DEFINE_FUNCTION("GetHeapStatus()");
	/*---------- Borland 16 bit ---------------------------------------------*/
#if defined (__BCPLUSPLUS__)
	return (HEAP_NOTDEFINED);
	/*---------- DOS real mode implementation -------------------------------*/
#elif defined(__MSDOS__)
	return (heapcheck());
	/*---------- Windows implementation -------------------------------------*/
#elif defined(_WIN32)
#if defined(_DEBUG)

	if (_CrtCheckMemory()) {
		return (HEAP_OK);
	}

	return (HEAP_CORRUPT);
#else
	return (HEAP_NOTDEFINED);
#endif
	/*---------- Any unknown system implementation --------------------------*/
#else
	ASSERT(FALSE);
	return (HEAP_NOTDEFINED);
#endif
}

/*=========================================================================
 *      End of Function GetHeapStatus()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - TCHAR* GetHeapStatusString (void);
 *
 * Returns a string based on the status of the heap.  Always returns a
 * valid string, never NULL.
 *
 *=======================================================================*/
const TCHAR *GetHeapStatusString (void) {
	switch (GetHeapStatus()) {
		case HEAP_OK:
			return (_T("Ok"));

		case HEAP_CORRUPT:
			return (_T("Corrupt"));

		case HEAP_EMPTY:
			return (_T("Empty or not Initialized" ));

		case HEAP_NOTDEFINED:
			return (_T("Status Not Defined in Current System"));

		default:
			return (_T("Error, Invalid Heap Status"));
	}
}

/*=========================================================================
 *      End of Function GetHeapStatusString()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - void* memsearch (pBuffer, pSearchBuffer, BufferLength,
                   SearchLength, StartIndex);
 *
 * Searches for the search bytes in given string using a 'binary' search
 * using the given lengths.  Starts searching in the target memory at
 * the given index.  Returns a pointer to the position of the search bytes
 * in the target bytes.  ASSERTs if given invalid input.
 *
 *=======================================================================*/
TCHAR *memsearch (const TCHAR* pBuffer, const TCHAR* pSearchBuffer,
                  const size_t BufferLength, const size_t SearchLength,
                  const size_t StartIndex) {
	DEFINE_FUNCTION("memsearch()");
	size_t BufferIndex;       /* Loop counters */
	size_t SearchIndex;
	/* Ensure valid input */
	ASSERT(pBuffer != NULL && pSearchBuffer != NULL);

	/* Ensure string lengths allow a possible match */
	if (BufferLength < StartIndex ||
	    SearchLength == 0 ||
	    SearchLength > BufferLength - StartIndex) {
		return (NULL);
	}

	BufferIndex = StartIndex;
	SearchIndex = 0;

	/* The main search loop */
	while (BufferIndex < BufferLength) {
		if (pBuffer[BufferIndex] == pSearchBuffer[SearchIndex]) {
			SearchIndex++;

			if (SearchIndex >= SearchLength) {
				return (TCHAR*)(pBuffer + BufferIndex - SearchLength + 1);
			}
		} else if (SearchIndex != 0) {
			BufferIndex -= SearchIndex;
			SearchIndex = 0;
		}

		BufferIndex++;
	}

	/* Nothing found... */
	return (NULL);
}

/*=========================================================================
 *      End of Function memsearch()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - int  memisearch (pBuffer, pSearchBuffer, BufferLength,
                SearchLength, StartIndex);
 *
 * Searches for the search bytes in given string using a 'binary' search
 * using the given lengths.  Starts searching in the target memory at
 * the given index.  Returns the 0-based index to the position of the search bytes
 * in the target bytes.  ASSERTs if given invalid input. Case insensitive.
 *
 *=======================================================================*/
int memisearch (const TCHAR* pBuffer, const TCHAR* pSearchBuffer,
                const size_t BufferLength, const size_t SearchLength,
                const size_t StartIndex) {
	DEFINE_FUNCTION("memisearch()");
	size_t BufferIndex;       /* Loop counters */
	size_t SearchIndex;
	/* Ensure valid input */
	ASSERT(pBuffer != NULL && pSearchBuffer != NULL);

	/* Ensure string lengths allow a possible match */
	if (BufferLength < StartIndex ||
	    SearchLength == 0 ||
	    SearchLength > BufferLength - StartIndex) {
		return (-1);
	}

	BufferIndex = StartIndex;
	SearchIndex = 0;

	/* The main search loop */
	while (BufferIndex < BufferLength) {
		if (tolower(pBuffer[BufferIndex]) == tolower(pSearchBuffer[SearchIndex])) {
			SearchIndex++;

			if (SearchIndex >= SearchLength) {
				return (BufferIndex - SearchLength + 1);
			}
		} else if (SearchIndex != 0) {
			BufferIndex -= SearchIndex;
			SearchIndex = 0;
		}

		BufferIndex++;
	}

	/* Nothing found... */
	return (-1);
}

/*=========================================================================
 *      End of Function memisearch()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - bool ReplaceString (ppNewString, pSourceString);
 *
 * Same as CreateString(TCHAR**, TCHAR*) except that the destrination string
 * is deleted if it is non-NULL.  Returns TRUE on success or FALSE
 * on any error (source string is NULL).  Throws an exception if the
 * string could not be allocated.  Ignores if the input and output
 * strings point to the same object.
 *
 *=========================================================================*/
bool ReplaceString (TCHAR** ppNewString, const TCHAR* pSourceString) {
	DEFINE_FUNCTION("ReplaceString(TCHAR**, TCHAR*)");
	/* Ensure valid input */
	ASSERT(ppNewString != NULL);

	/* Check for NULL inputs */
	if (*ppNewString == NULL && pSourceString == NULL) {
		return (FALSE);
	}

	/* Check for same input/output objects */
	if (*ppNewString == pSourceString) {
		return (TRUE);
	}

	/* Delete the destination string if required */
	DestroyPointer(*ppNewString);
	/* Attempt to allocate the new stirng */
	return CreateString(ppNewString, pSourceString);
}

/*===========================================================================
 *      End of Function ReplaceString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ReplaceString (ppNewString, Length);
 *
 * Same as CreateString(TCHAR**, size_t) except that the destrination string
 * is deleted if it is non-NULL.  Returns TRUE on success or FALSE
 * on any error (source string is NULL).  Throws an exception if the
 * string could not be allocated.
 *
 *=========================================================================*/
bool ReplaceString (TCHAR** ppNewString, const size_t Length) {
	DEFINE_FUNCTION("ReplaceString(TCHAR**, size_t)");
	/* Ensure valid input */
	ASSERT(ppNewString != NULL);
	/* Delete the destination string if required */
	DestroyPointer(*ppNewString);
	/* Attempt to allocate the new stirng */
	return CreateString(ppNewString, Length);
}

/*===========================================================================
 *      End of Function ReplaceString()
 *=========================================================================*/


#if defined(__TURBOC__) && !defined(__BCPLUSPLUS__)
/*===========================================================================
 *
 * Function - void _DosMemDumpHeap (void);
 *
 * Dumps the heap blocks to the SystemLog under TurboC.
 *
 *=========================================================================*/
void _DosMemDumpHeap (void) {
	struct heapinfo HeapInfo;
	long MemorySize = 0l;
	long UnusedSize = 0l;
	long Index = 1l;
	SystemLog.Printf (_T("Outputting DOS heap block information..."));

	/* Make sure the heap is not corrupt */
	if (heapcheck() != _HEAPOK) {
		SystemLog.Printf (_T("\t\tHeap is corrupt, cannot output block information!"));
		return;
	}

	/* Walk through the heap counting used and free blocks */
	HeapInfo.ptr = NULL;

	while (heapwalk(&HeapInfo) == _HEAPOK) {
		if (HeapInfo.in_use) {
			MemorySize += HeapInfo.size;
		} else {
			UnusedSize += HeapInfo.size;
		}

		SystemLog.Printf (_T("\t\t%3ld) %p: %8ld bytes,  Used=%1d "), Index, HeapInfo.ptr, HeapInfo.size,
		                  HeapInfo.in_use);
		Index++;
	}

	SystemLog.Printf (_T("\tOutput %ld bytes of used and %ld bytes of unused heap blocks."), MemorySize,
	                  UnusedSize);
	/* Chain to our custom block handler in debug builds */
#if defined(_DEBUG)
	OutputBlockInfo();
#endif
	return;
}

/*===========================================================================
 *      End of Function _DosMemDumpHeap()
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Begin File Test Routines (Debug Builds Only)
 *
 *=========================================================================*/
#if defined(_DEBUG)


#define CREATESTRING1_BUFFERSIZE 11000

/* Turn off compiler warning options */
#if defined(__BCPLUSPLUS__)
	#pragma warn -rch
	#pragma warn -ccc
#endif

/*===========================================================================
 *
 * Test the CreateString (TCHAR*) function
 *
 * 1. Tests the allocation of set strings.
 * 2. Tests the allocation of random sized strings (from 1 to 10000 bytes).
 *
 *=========================================================================*/
void Test_CreateString1 (void) {
	DEFINE_FUNCTION("Test_CreateString1()");
	TCHAR* Buffer;
	TCHAR* pTestStrings[4] = { _T(""), _T("\0"), _T("testing"), _T("asdadasd") };
	TCHAR* pTestPtr;
	int LoopCounter;
	size_t RandomSize;
	/* Test the set string allocation */
	SystemLog.Printf (stderr,
	                  _T("========== Testing CreateString(TCHAR*) with set strings =========="));
	/* Allocate because large stack strings mess up in Borland 16-bit */
	Buffer = CreateString(CREATESTRING1_BUFFERSIZE);

	for (LoopCounter = 0; LoopCounter < 4; LoopCounter++) {
		pTestPtr = CreateString(pTestStrings[LoopCounter]);
		/* Ensure the string was properly allocated */
		ASSERT(pTestPtr != NULL);
		ASSERT(TSTRCMP(pTestStrings[LoopCounter], pTestPtr) == 0);
		ASSERT(IsValidPointer(pTestPtr, TSTRLEN(pTestStrings[LoopCounter]) + 1));
		/* Delete the test string */
		DestroyPointer(pTestPtr);
		SystemLog.Printf (stderr, _T("\t\tSuccessfully allocated string '%s'."), pTestStrings[LoopCounter]);
	}

	/* Test the random string allocation */
	SystemLog.Printf (stderr,
	                  _T("========== Testing CreateString(TCHAR*) with random length strings =========="));
	srand( (unsigned)time( NULL ) );
	memset(Buffer, (TCHAR)'a', CREATESTRING1_BUFFERSIZE * sizeof(TCHAR));

	for (LoopCounter = 0; LoopCounter < 1000; LoopCounter++) {
		RandomSize = (size_t) ((float)rand() * 10000 / RAND_MAX);
		Buffer[RandomSize] = NULL_CHAR;
		pTestPtr = CreateString(Buffer);
		/* Ensure the string was properly allocated */
		ASSERT(pTestPtr != NULL);
		ASSERT(TSTRCMP(pTestPtr, Buffer) == 0);
		ASSERT(IsValidPointer(pTestPtr, RandomSize + 1));
		/* Delete the test string */
		DestroyPointer(pTestPtr);
		SystemLog.Printf (stderr, _T("\t\t%7d) Successfully allocated string of length %u bytes."),
		                  LoopCounter, RandomSize);
		Buffer[RandomSize] = (TCHAR)'a';
	}

	ASSERT(DebugHeapCheckMemory());
	DestroyPointer(Buffer);
}

/*===========================================================================
 *      End of testing the CreateString(TCHAR*) function
 *=========================================================================*/


/*===========================================================================
 *
 * Test the CreateString(size_t) function
 *
 * 1. Tests the allocation of strings of set sizes.
 * 2. Tests the allocation of random sized strings (from 1 to
 *    TEST_MAXSTRING_SIZE bytes).
 *
 *=========================================================================*/
void Test_CreateString2 (void) {
	DEFINE_FUNCTION("Test_CreateString2()");
	size_t TestSizes[4] = { 10, 1, 2, 200 };
	size_t RandomSize;
	int LoopCounter;
	TCHAR* pTestPtr;
	/* Test the allocation of set sized strings */
	SystemLog.Printf(stderr,
	                 _T("========== Testing CreateString(size_t) with set sized strings =========="));

	for (LoopCounter = 0; LoopCounter < 4; LoopCounter++) {
		pTestPtr = CreateString(TestSizes[LoopCounter]);
		/* Ensure the string was properly allocated */
		ASSERT(pTestPtr != NULL);
		ASSERT(IsValidPointer(pTestPtr, TestSizes[LoopCounter] + 1));
		DestroyPointer(pTestPtr);
		SystemLog.Printf (stderr, _T("\t\tSuccessfully allocated string of %u bytes."),
		                  TestSizes[LoopCounter]);
	}

	/* Test the allocation of randomly sized strings */
	SystemLog.Printf (stderr,
	                  _T("========== Testing CreateString(size_t) with randomly sized strings =========="));
	srand( (unsigned)time( NULL ) );

	for (LoopCounter = 0; LoopCounter < 1000; LoopCounter++) {
		RandomSize = (size_t) ((float)((size_t)rand()) * TEST_MAXSTRING_SIZE / RAND_MAX);
		pTestPtr = CreateString(RandomSize);
		/* Ensure the string was properly allocated */
		ASSERT(pTestPtr != NULL);
		ASSERT(IsValidPointer(pTestPtr, RandomSize + 1));
		DestroyPointer(pTestPtr);
		SystemLog.Printf (stderr, _T("\t\t%7d) Successfully allocated string of %u bytes."),
		                  LoopCounter + 1, RandomSize);
	}

	ASSERT(DebugHeapCheckMemory());
}

/*===========================================================================
 *      End of testing the CreateString(size_t) function
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_CreateString3 (void);
 *
 * Tests the CreateString(TCHAR**, TCHAR*) function.  Since this function
 * is based on the CreateString(TCHAR*) function, some tests can be skipped.
 *  1. Tests for NULL source string
 *  2. Check allocation of set strings
 *
 *=========================================================================*/
void Test_CreateString3 (void) {
	DEFINE_FUNCTION("Test_CreateString3()");
	TCHAR* pStrings[4] = { _T("asldkja;lkdj;asd"), _T("123785"), _T(""), _T("o[ijopiap98dfp9hsadfp98ashf9as8fh") };
	TCHAR* pTestString1 = NULL;
	int LoopCounter;
	SystemLog.Printf(stdout,
	                 _T("================ Testing CreateString(TCHAR**, TCHAR*) ==================="));
	/* Test case of NULL source string */
	ASSERT(CreateString(&pTestString1, (TCHAR*)NULL) == FALSE);
	ASSERT(pTestString1 == NULL);

	/* Check the allocation of set strings */
	for (LoopCounter = 0; LoopCounter < 4; LoopCounter++) {
		ASSERT(CreateString(&pTestString1, pStrings[LoopCounter]) == TRUE);
		ASSERT(TSTRCMP(pTestString1, pStrings[LoopCounter]) == 0);
		DestroyPointer(pTestString1);
	}

	ASSERT(DebugHeapCheckMemory());
}

/*===========================================================================
 *      End of Function Test_CreateString3()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_memsearch (void);
 *
 * Tests the memsearch() and memisearch() functions.
 *  1. Tests for typical buffers
 *  2. Tests search buffer longer than buffer
 *  3. Tests empty buffers
 *  4. Tests overlapping data buffers
 *
 *=========================================================================*/
void Test_memsearch (void) {
	DEFINE_FUNCTION("Test_memsearch()");
	TCHAR TestBuffer[101] = _T("Test buffer 1234567890");
	TCHAR TestSearch[18] = _T("uff");
	TCHAR* pResult;
	int iResult;
	SystemLog.Printf(stdout,
	                 _T("================ Testing memsearch()/memisearch() ==================="));
	/* Test typical buffers */
	pResult = memsearch(TestBuffer, TestSearch, 20, 3, 0);
	ASSERT(TSTRNCMP(pResult, _T("uffer"), 5) == 0);
	iResult = memisearch(TestBuffer, TestSearch, 20, 3, 0);
	ASSERT(TSTRNCMP(TestBuffer + iResult, _T("uffer"), 5) == 0);
	pResult = memsearch(TestBuffer, _T("aaa"), 20, 3, 0);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, _T("aaa"), 20, 3, 0);
	ASSERT(iResult == -1);
	/* Test typical buffers with start index */
	pResult = memsearch(TestBuffer, TestSearch, 20, 3, 4);
	ASSERT(TSTRNCMP(pResult, _T("uffer"), 5) == 0);
	iResult = memisearch(TestBuffer, TestSearch, 20, 3, 4);
	ASSERT(TSTRNCMP(TestBuffer + iResult, _T("uffer"), 5) == 0);
	pResult = memsearch(TestBuffer, TestSearch, 20, 3, 14);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, TestSearch, 20, 3, 14);
	ASSERT(iResult == -1);
	/* Test typical buffers with case differences */
	TSTRCPY(TestSearch, _T("UfF"));
	pResult = memsearch(TestBuffer, TestSearch, 20, 3, 0);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, TestSearch, 20, 3, 0);
	ASSERT(TSTRNICMP(TestBuffer + iResult, _T("uffer"), 5) == 0);
	/* Test search buffer longer than main buffer */
	pResult = memsearch(TestBuffer, TestSearch, 3, 20, 0);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, TestSearch, 3, 20, 0);
	ASSERT(iResult == -1);
	/* Test empty buffers */
	pResult = memsearch(TestBuffer, TestSearch, 20, 0, 0);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, TestSearch, 20, 0, 0);
	ASSERT(iResult == -1);
	pResult = memsearch(TestBuffer, TestSearch, 0, 10, 0);
	ASSERT(pResult == NULL);
	iResult = memisearch(TestBuffer, TestSearch, 0, 10, 0);
	ASSERT(iResult == -1);
}

/*===========================================================================
 *      End of Function Test_memsearch()
 *=========================================================================*/



/*===========================================================================
 *
 * Function - void Test_ReplaceString (void);
 *
 * Tests the ReplaceString(TCHAR**, TCHAR*) function.  Is based on the
 * CreateString(TCHAR**, TCHAR*) function which eliminates some tests.
 *  1. Tests empty/NULL destination strings
 *  2. Check allocation of set strings
 *
 *=========================================================================*/
void Test_ReplaceString (void) {
	DEFINE_FUNCTION("Test_ReplaceString()");
	TCHAR* pStrings[4] = { _T("asldkja;lkdj;asd"), _T("123385"), _T(""), _T("o[ijopiap98dfp9hsadfp98ashf9as8fh") };
	TCHAR* pTestString1;
	int LoopCounter;
	SystemLog.Printf(stdout, _T("================ Testing ReplaceString() ==================="));
	/* Allocate temp string */
	pTestString1 = CreateString(_T("aadkjsdoijsadfhsdpofihdpfaioh"));
	/* Attempt to reallocate string */
	ASSERT(ReplaceString(&pTestString1, _T("1113233")) == TRUE);
	/* Test allocation of NULL source string with non-NULL destination */
	ASSERT(ReplaceString(&pTestString1, (TCHAR*)NULL) == FALSE);
	ASSERT(pTestString1 == NULL);
	/* Test allocation of NULL source string with NULL destination */
	ASSERT(ReplaceString(&pTestString1, (TCHAR*)NULL) == FALSE);
	ASSERT(pTestString1 == NULL);

	/* Check the allocation of set strings */
	for (LoopCounter = 0; LoopCounter < 4; LoopCounter++) {
		ASSERT(CreateString(&pTestString1, pStrings[LoopCounter]) == TRUE);
		ASSERT(TSTRCMP(pTestString1, pStrings[LoopCounter]) == 0);
		DestroyPointer(pTestString1);
	}

	ASSERT(DebugHeapCheckMemory());
}

/*===========================================================================
 *      End of Function Test_ReplaceString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function  - void Test_DL_Mem (void);
 *
 * Runs the test routines for this file.
 *  - Tests the CreateString(TCHAR*) function
 *  - Tests the CreateString(size_t) function
 *  - Tests the CreateString(TCHAR**, TCHAR*) function
 *  - Tests the ReplaceString(TCHAR**, TCHAR*) function
 *  - Runs the GetFreeMemory(), GetUsedMemory() and GetTotalMemory() functions,
 *    Outtputing results to log file, ASSERTing if any function returns an error.
 *  - Runs the GetHeapStatus() and GetHeapStatusString() functions, outputting
 *    their results to the log file.
 *  - Tests the memsearch() and memisearch() functions
 *
 *=========================================================================*/
void Test_DL_Mem (void) {
	DEFINE_FUNCTION("Test_DL_Mem()");
	long Memory;
	Test_CreateString1();
	Test_CreateString2();
	Test_CreateString3();
	Test_ReplaceString();
	Test_memsearch();
	ASSERT(GetFreeMemory(Memory) == TRUE);
	SystemLog.Printf(_T("\tGetFreeMemory() returned %ld"), Memory);
	ASSERT(GetUsedMemory(Memory) == TRUE);
	SystemLog.Printf(_T("\tGetUsedMemory() returned %ld"), Memory);
	ASSERT(GetTotalMemory(Memory) == TRUE);
	SystemLog.Printf(_T("\tGetTotalMemory() returned %ld"), Memory);
	SystemLog.Printf(_T("\tGetHeapStatus() returned %ld"), GetHeapStatus());
	SystemLog.Printf(_T("\tGetHeapStatusString() returned '%s'"), GetHeapStatusString());
}

/*===========================================================================
 *      End of Function Test_DL_Mem()
 *=========================================================================*/

/* Restore compiler warning options */
#if defined(__BCPLUSPLUS__)
	#pragma warn .rch
	#pragma warn .ccc
#endif

#endif
/*===========================================================================
 *      End of File Test Routines (Debug Builds Only)
 *=========================================================================*/
