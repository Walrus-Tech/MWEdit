/*===========================================================================
 *
 * File:    DL_Mem.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Sunday, April 01, 2001
 *
 * Contains memory related definitions for Dave's Library of common code.

 *=========================================================================*/
#ifndef __DL_MEM_H
#define __DL_MEM_H


/*===========================================================================
 *
 * Begin Include Files
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_log.h"
#include "dl_block.h"

#if defined(__TURBOC__)
	#if !defined(_WIN32_WCE)
		//#include <alloc.h>
	#endif
#endif
/*===========================================================================
 *      End of Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin File Identification
 *
 *=========================================================================*/
#define DL_MEM_NAME    _T("DL_Mem.cpp")
#define DL_MEM_VERSION _T("0.01d")
#define DL_MEM_AUTHOR  _T("Dave Humphrey (uesp@m0use.net)")
#define DL_MEM_DATE    _T("1 April 2001")
/*===========================================================================
 *      End of File Identification
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Pointer Creation Definitions
 *
 * Macros for the creation of general pointers.  Ensures the allocation
 * was successfull and, on error, displays an error message and exits
 * the program.  On error the program outputs an error message and
 * throws an exception.  Debug versions update the memory logging info
 * and output more explicit error messages.
 *
 *=========================================================================*/
#if defined(_DEBUG)

/* Macro for creating a general pointer */
#define CreatePointer(pObject, Type) { \
		(pObject) = new Type; \
		\
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(Type), _T(#pObject), ThisFunction)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes in file %s, function %s, line #%d!"), sizeof(Type), ThisFile, ThisFunction, __LINE__); \
			throw (_T("Out of Memory!")); \
		} }

#define CreatePointerL(pObject, Type) { \
		(pObject) = new Type; \
		\
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(Type), _T(#pObject), NULL)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes (file '%s', line #%d)!"), sizeof(Type), __FILE__, __LINE__); \
			throw (_T("Out of Memory!")); \
		} }

/* Macro for creating a general class pointer with arguments*/
#define CreateClassPointer(pObject, Type, Args) { \
		(pObject) = new Type(Args); \
		\
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(Type), _T(#pObject), ThisFunction)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes in file %s, function %s, line #%d!"), sizeof(Type), ThisFile, ThisFunction, __LINE__); \
			throw (_T("Out of Memory!")); \
		} }


/* Macro for creating a general array pointer array  */
#define CreateArrayPointer(pObject, Type, Number) { \
		(pObject) = new Type[Number]; \
		\
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(Type)*Number, _T(#pObject), ThisFunction)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes (%u[%u]) in file %s, function %s, line #%d!"), sizeof(Type)*Number, sizeof(Type), Number, ThisFile, ThisFunction, __LINE__); \
			throw (_T("Out of Memory!")); \
		} }

#define CreateArrayPointerL(pObject, Type, Number) { \
		(pObject) = new Type[Number]; \
		\
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(Type)*Number, _T(#pObject), NULL)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes (%u[%u]) in file %s, function %s, line #%d!"), sizeof(Type)*Number, sizeof(Type), Number, __FILE__, "", __LINE__); \
			throw (_T("Out of Memory!")); \
		} }


/* Macro for validating a pointer already created but not yet added
     * to the block array and not yet ensured it was created successfully.
     * This is used for class allocations that take many arguments in their
     * constructors and thus can't be easily used with the CreatePointer()
     * type macros above. */
#define ValidateNewPointer(pObject) { \
		if ((pObject) != NULL) { \
			if (!CreateBlockInfo((pObject), sizeof(*(pObject)), _T(#pObject), ThisFunction)) { \
				delete pObject; \
				pObject = NULL; \
			} \
		} \
		\
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes in file %s, function %s, line #%d!"), sizeof(*pObject), ThisFile, ThisFunction, __LINE__); \
			throw (_T("Out of Memory!")); \
		} }

/* Release build pointer creation macros */
#else


/* Macro for creating a general pointer */
#define CreatePointer(pObject, Type) { \
		(pObject) = new Type; \
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes!"), sizeof(Type)); \
			throw (_T("Out of Memory!")); \
		} }

#define CreatePointerL(pObject, Type) CreatePointer(pObject, Type)

/* Macro for creating a class pointer with arguments*/
#define CreateClassPointer(pObject, Type, Args) { \
		(pObject) = new Type(Args); \
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes!"), sizeof(Type)); \
			throw (_T("Out of Memory!")); \
		} }


/* Macro for creating a general array pointer array  */
#define CreateArrayPointer(pObject, Type, Number) { \
		(pObject) = new Type[Number]; \
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes!"), sizeof(Type)*Number); \
			throw (_T("Out of Memory!")); \
		} }

#define CreateArrayPointerL(pObject, Type, Number) CreateArrayPointer(pObject, Type, Number)

/* Validate a prexisting pointer (see debug version for more info) */
#define ValidateNewPointer(pObject) { \
		if ((pObject) == NULL) { \
			SystemLog.Printf(stderr, _T("Failed to allocate %u bytes!"), sizeof(*(pObject)) ); \
			throw (_T("Out of Memory!")); \
		} }

#endif
/*===========================================================================
 *      End of Pointer Creation Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Pointer Deletion Definitions
 *
 * Macros for deleting or releasing pointers.  The macros ensure the
 * pointer being deleting is non-NULL.  The pointers are set to NULL
 * after being freed.  Debug versions update the memory block information
 * and output error to log file if a NULL pointer was deleted.
 *
 *=========================================================================*/
#if defined(_DEBUG)

/* Macro for destroying a pointer */
#define DestroyPointer(pObject) { \
		if ((pObject) != NULL) { \
			FreeBlockInfo(pObject); \
			delete pObject; \
			(pObject) = NULL; } \
		else { \
			/*SystemLog.Printf(_T("Attempted NULL pointer deletion! (%s in function %s, line %d, %s)"), ThisFile, ThisFunction, __LINE__, #pObject); */ \
		} }

/* Macro for destroying an array pointer */
#define DestroyArrayPointer(pObject) { \
		if ((pObject) != NULL) { \
			FreeBlockInfo(pObject); \
			delete[] pObject; \
			(pObject) = NULL; } \
		else { \
			/*SystemLog.Printf(_T("Attempted NULL array pointer deletion! (%s in function %s, line %d, %s)"), ThisFile, ThisFunction, __LINE__, #pObject); */ \
		} }

/* Release a handle type object (mostly for Win32 COM) */
#if !defined(RELEASE)
#define RELEASE(pObject) { \
		if ((pObject) != NULL) { \
			(pObject)->Release(); \
			(pObject) = NULL; } \
		else { \
			SystemLog.Printf(_T("Attempted NULL pointer release! (%s in function %s, line %d, %s)"), ThisFile, ThisFunction, __LINE__, #pObject); \
		} }
#endif


/* Release build definitions */
#else

/* Macro for destroying a pointer */
#define DestroyPointer(pObject) { \
		if ((pObject) != NULL) { \
			delete pObject; \
			(pObject) = NULL; } }

/* Macro for destroying an array pointer */
#define DestroyArrayPointer(pObject) { \
		if ((pObject) != NULL) { \
			delete[] pObject; \
			(pObject) = NULL; } }

/* Release a handle type object (mostly for Win32 COM) */
#if !defined(RELEASE)
#define RELEASE(pObject) { \
		if ((pObject) != NULL) { \
			(pObject)->Release(); \
			(pObject) = NULL; } }
#endif

#endif
/*===========================================================================
 *      End of Pointer Deletion Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Heap Status Values
 *
 * Return values for the GetHeapStatus() function.  Values map onto the
 * appropiate definition depending on the current system.
 *
 *=========================================================================*/
#if defined(__BCPLUSPLUS__)
	#define HEAP_OK   (_HEAPOK)
	#define HEAP_CORRUPT  (-5)
	#define HEAP_EMPTY    (_HEAPEMPTY)
#elif defined(_WIN32)
	#define HEAP_OK   (1)
	#define HEAP_CORRUPT  (0)
	#define HEAP_EMPTY    (-9)
#elif defined(__MSDOS__) &&  defined(__BCPLUSPLUS__)
	#define HEAP_OK   (_HEAPOK)
	#define HEAP_CORRUPT  (_HEAPCORRUPT)
	#define HEAP_EMPTY    (_HEAPEMPTY)
#else
	#define HEAP_OK   (1)
	#define HEAP_CORRUPT  (0)
	#define HEAP_EMPTY    (-9)
#endif

/* Common values */
#define HEAP_NOTDEFINED  (-10)
/*===========================================================================
 *      End of Heap Status Values
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Allocate a block of memory */
void *AllocateMemory(const size_t Size);

/* Attempts to allocate and initialize a string pointer */
TCHAR *CreateString(const TCHAR *pString);
//wchar_t* CreateStringW (const wchar_t*  pString);
TCHAR *CreateString(const size_t Length);

/* Attempt to create a new string from the given string */
bool CreateString(TCHAR **pNewString, const TCHAR *pSourceString);
bool CreateString(TCHAR **pNewString, const size_t StringSize);

/* Memory status routines */
bool GetTotalMemory(long &Memory);
bool GetFreeMemory(long &Memory);
bool GetUsedMemory(long &Memory);
int GetHeapStatus(void);
const TCHAR *GetHeapStatusString(void);

/* Search binary memory buffer for a sub-buffer */
TCHAR *memsearch(const TCHAR *pBuffer,
                 const TCHAR *pSearchBuffer,
                 const size_t BufferLength,
                 const size_t SearchLength,
                 const size_t StartIndex);

/* Search binary memory buffer for a sub-buffer, case insensitive */
int memisearch(const TCHAR *pBuffer,
               const TCHAR *pSearchBuffer,
               const size_t BufferLength,
               const size_t SearchLength,
               const size_t StartIndex);

/* Deletes the current string and allocates a new string */
bool ReplaceString(TCHAR **pNewString, const TCHAR *pSourceString);
bool ReplaceString(TCHAR **pNewString, const size_t Length);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Debug Heap Definitions
 *
 * Function prototypes and definitions for manipulating the debug heap.
 * Functions compile to nothing in release builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)

	#if defined(_MSDOS)
		#define DebugHeapCheckMemory() true

		/* Output all objects on the heap to the SystemLog */
		void _DosMemDumpHeap(void);

	#elif defined(_WIN32)
		#define DebugHeapCheckMemory() (_CrtDumpMemoryLeaks() == TRUE)
	#endif

#endif
/*===========================================================================
 *      End of Debug Heap Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Test Routine Prototypes
 *
 * Test function prototypes for this module, available only in DEBUG builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)

	#if defined(__TURBOC__) || defined(__BCPLUSPLUS__)
		#define TEST_MAXSTRING_SIZE 64000u
	#else
		#define TEST_MAXSTRING_SIZE 100000u
	#endif

	void Test_DL_Mem(void);
	void Test_CreateString1(void);
	void Test_CreateString2(void);
	void Test_CreateString3(void);
	void Test_memsearch(void);
	void Test_ReplaceString(void);
#endif
/*===========================================================================
 *      End of Test Routine Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File DL_Mem.H
 *=========================================================================*/
