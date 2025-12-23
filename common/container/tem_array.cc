/*===========================================================================
 *
 * File:    TemArray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Implements the TTemplateArray template for handling a simple array
 * of typed pointers.
 *
 *=========================================================================*/
#include "Common/Contain/temarray.h"

#include <cstddef>
#include <climits>
#include <cstring>

#include "Common/dl_base.h"
#include "Common/dl_block.h"
#include "Common/dl_err.h"
#include "Common/dl_mem.h"

#if _DEBUG
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Common/dl_log.h"
#endif  // _DEBUG

DEFINE_FILE("TemArray.cpp");

#if _DEBUG
/* Test structure used for testing */
typedef struct {
	int Number;
	char Message[32];
	long lNumber;
} testdata_t;

/* Test type definitions */
typedef TTemplateArray<testdata_t> CTestDataArray;
typedef TTemplateArray<char> CPCharArray;
#endif  // _DEBUG

/*===========================================================================
 *
 * Class TTemplateArray Constructor - TTemplateArray (MaxSize);
 *
 * Attempts to create an array with the given maximum number of elements.
 * ASSERTs if given invalid input.
 *
 *=========================================================================*/
template <class TArrayPtr> TTemplateArray<TArrayPtr>::TTemplateArray(const int MaxSize,
                                                                     const int GrowSize) {
	DEFINE_FUNCTION("TTemplateArray::TTemplateArray()");
	/* Ensure valid input */
	IASSERT(MaxSize <= UINT_MAX / sizeof(TArrayPtr *));

	if (MaxSize > 0) {
		CreateArrayPointer(m_ppArray, TArrayPtr *, MaxSize);
	} else {
		m_ppArray = NULL;
	}

	m_MaxElements = MaxSize;
	m_NumElements = 0;
	m_CmpFuncData = 0;
	m_GrowSize = GrowSize;
	m_pCmpFunc = NULL;
}


/*===========================================================================
 *
 * Class TTemplateArray Destructor
 *
 *=========================================================================*/
template <class TArrayPtr> TTemplateArray<TArrayPtr>::~TTemplateArray() {
	//DEFINE_FUNCTION("TTemplateArray::~CGenArray()");
	/* Delete all the valid pointers in array */
	Destroy();
	/* Unallocate the array */
	DestroyArrayPointer(m_ppArray);
}


/*===========================================================================
 *
 * Class TTemplateArray Method - void Destroy (void);
 *
 * Deletes all the valid pointers currently in the array.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TTemplateArray<TArrayPtr>::Destroy() {
	//DEFINE_FUNCTION("TTemplateArray::Destroy()");
	int LoopCounter;

	/* Ensure a valid array */
	//IASSERT(m_ppArray != NULL);

	/* Delete all the valid elements in array */
	for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
		IASSERT(m_ppArray[LoopCounter] != NULL);
		DestroyPointer(m_ppArray[LoopCounter]);
	}

	m_NumElements = 0;
}


/*===========================================================================
 *
 * Class TTemplateArray Method - bool AddElement (pNewElement);
 *
 * Attempts to add a new element to the end of the array.  The input
 * element must be valid.  Returns false on any error.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TTemplateArray<TArrayPtr>::AddElement(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TTemplateArray::AddElement()");
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);
	IASSERT(IsValidPointer(pNewElement));

	/* Check if we have to resize the array */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Ensure array can hold one more element */
	if (m_NumElements >= m_MaxElements) {
		ErrorHandler.AddError(ERR_MAXINDEX,
		                      "A maximum of %u array elements has been reached!",
		                      m_MaxElements);
		return false;
	}

	/* Add element to array */
	m_ppArray[m_NumElements] = pNewElement;
	m_NumElements++;
	return true;
}


/*===========================================================================
 *
 * Class TTemplateArray Method - bool AddSort (pNewElement);
 *
 * Attempts to add a new element to a sorted array.  The input
 * element must be valid.  Returns false on any error.  Assumes that the
 * template class TArrayPtr has a defined < operator. If the array has
 * reached the maximum size, the lowest element is removed.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TTemplateArray<TArrayPtr>::AddSort(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TTemplateArray::AddSort()");
	int LoopCounter;
	int InsertCounter;
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);
	IASSERT(IsValidPointer(pNewElement));

	/* Check if we have to resize the array */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Find the position to insert the new element */
	if (m_pCmpFunc != NULL) {
		for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
			if (m_pCmpFunc((void *)(m_ppArray + LoopCounter),
			               (void *)(&pNewElement),
			               m_CmpFuncData) > 0) {
				break;
			}
		}
	} else {
		LoopCounter = m_NumElements;
// for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
		// if (*(m_ppArray[LoopCounter]) < *pNewElement) break;
// }
	}

	/* Remove the last element, if required */
	if (m_NumElements >= m_MaxElements) {
		/* Ignore new element if it doesn't 'fit' in array */
		if (LoopCounter == m_NumElements) {
			return false;
		}

		DestroyPointer(m_ppArray[m_NumElements - 1]);
		m_NumElements--;
	}

	/* Shift elements after insertion point */
	for (InsertCounter = m_NumElements; InsertCounter > LoopCounter; InsertCounter--) {
		m_ppArray[InsertCounter] = m_ppArray[InsertCounter - 1];
	}

	/* Insert the new element to array */
	m_ppArray[LoopCounter] = pNewElement;
	m_NumElements++;
	return true;
}


#if _DEBUG
/*===========================================================================
 *
 * Class TTemplateArray Method - bool AssertValid (void);
 *
 * Tests the contents of the array to ensure they are valid.  Exists
 * in debug builds only.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TTemplateArray<TArrayPtr>::AssertValid() {
	DEFINE_FUNCTION("TTemplateArray::AssertValid()");
	int LoopCounter;
	/* Ensure valid input */
	ASSERT(m_NumElements <= m_MaxElements);

	if (m_ppArray == NULL) {
		ASSERT(m_NumElements == 0);
		ASSERT(m_MaxElements == 0);
	} else {
		ASSERT(m_MaxElements > 0);

		for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
			ASSERT(IsValidPointer(m_ppArray[LoopCounter]));
		}
	}

	return true;
}

#endif  // _DEBUG


/*===========================================================================
 *
 * Class TTemplateArray Method - bool DeleteElement (Index, Delete);
 *
 * Attempts to remove the given array element from the array.  Returns
 * false if the array index is invalid or on any other error (ASSERTs
 * in DEBUG builds).
 *
 *=========================================================================*/
template <class TArrayPtr>
void TTemplateArray<TArrayPtr>::DeleteElement(const int Index, const bool Delete) {
	//DEFINE_FUNCTION("TTemplateArray::DeleteElement()");
	int LoopCounter;
	/* Ensure the index is valid */
	IASSERT(IsValidIndex(Index));

	/* Delete the element */
	if (Delete) {
		DestroyPointer(m_ppArray[Index]);
	}

	/* Shift the array to compensate for the removed element */
	for (LoopCounter = Index; LoopCounter < m_NumElements; LoopCounter++) {
		m_ppArray[LoopCounter] = m_ppArray[LoopCounter + 1];
	}

	m_NumElements--;
	return;
}


/*===========================================================================
 *
 * Class TTemplateArray Method - bool GetElement (ppElement, Index);
 *
 * Attempts to retrieve the specified array element.  Returns false if the
 * given Index is not valid (asserts in debug builds).
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TTemplateArray<TArrayPtr>::GetElement(TArrayPtr **ppElement, const int Index) const {
	//DEFINE_FUNCTION("TTemplateArray::GetElement()");

	/* Ensure the index is valid */
	if (IsValidIndex(Index)) {
		*ppElement = m_ppArray[Index];
		return true;
	}

	/* Assert in debug builds */
	ABORT("TTemplateArray::GetElement() - Invalid array index received!");
	/* Return NULL in release builds */
	*ppElement = NULL;
	return false;
}


/*===========================================================================
 *
 * Class TTemplateArray Method - void ResizeArray (GrowArray);
 *
 * Shrinks or grows the array depending on the input flag.  If growing the
 * array the max array size is increased by the grow size.  The default
 * grow size of -1 (or less than) indicates that the optimal grow size be
 * used.  If shrinking the array, the array maxsize is reduced to to
 * current number of defined elements in the array.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TTemplateArray<TArrayPtr>::ResizeArray(const bool GrowArray) {
	DEFINE_FUNCTION("TTemplateArray::ResizeArray()");
	int NewSize;
	TArrayPtr **ppNewArray = NULL;
	byte **ppOldArray;

	/* Compute the new array size */
	if (GrowArray) {
		if (m_GrowSize < 0) {
			int GrowSize = m_MaxElements / 2;

			if (GrowSize < 4) {
				GrowSize = 4;
			} else if (GrowSize > 1024) {
				GrowSize = 1024;
			}

			NewSize = m_MaxElements + GrowSize;
		} else {
			NewSize = m_MaxElements + m_GrowSize;
		}
	} else {
		NewSize = m_NumElements;
	}

	/* Do nothing if array size has not changed */
	if (NewSize == m_MaxElements) {
		return;
	}

	/* Ensure a valid size */
	IASSERT(NewSize <= UINT_MAX / sizeof(TArrayPtr *));

	if (NewSize != 0) {
		/* Attempt to allocate space for the new array */
		CreateArrayPointer(ppNewArray, TArrayPtr *, NewSize);
		/* Copy pointers into new array */
		std::memcpy(ppNewArray, m_ppArray, sizeof(TArrayPtr *)*m_NumElements);
	}

	/* Set the resized array */
	ppOldArray = (byte **)m_ppArray;
	m_ppArray = ppNewArray;
	m_MaxElements = NewSize;
	/* Delete the old array (but not the objects!) */
	DestroyArrayPointer(ppOldArray);
}


/*===========================================================================
 *
 * Class TTemplateArray Method - void Sort (lUserData);
 *
 * Sorts the array using the current compare function.  Uses the standard
 * qsort algorithm and the specified user data value.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TTemplateArray<TArrayPtr>::Sort(const long lUserData) {
	m_CmpFuncData = lUserData;

	/* Ignore if no compare function defined */
	if (m_pCmpFunc == NULL) {
		return;
	}

	/* Run the extended qsort() routine on the array */
	// TODO: Namespace qsort in common
	qsort((void *)m_ppArray, m_NumElements, sizeof(TArrayPtr *), m_pCmpFunc, m_CmpFuncData);
}


/*===========================================================================
 *
 * Class TTemplateArray Method - void* operator[] (Index);
 *
 * Attempts to return the specified array element.  Returns NULL if the
 * index is invalid (asserts in debug builds).
 *
 *=========================================================================*/
template <class TArrayPtr>
inline TArrayPtr *TTemplateArray<TArrayPtr>::operator[](const int Index) const {
	//DEFINE_FUNCTION("TTemplateArray::operator[]()");

	/* Ensure the index is valid */
	if (IsValidIndex(Index)) {
		return m_ppArray[Index];
	}

	/* Assert in debug builds */
	ABORT("TTemplateArray::operator[]() - Invalid array index received!");
	return NULL;
}

#if _DEBUG
/*===========================================================================
 *
 * Function - void Test_StressTemplateArray (NumTests);
 *
 * Runs a stress test of the TTemplateArray class a number of times,
 * attempting to 'force' an error of some sort.  For each tests, a
 * random number of random sized strings are added to two char* arrays.
 *
 *=========================================================================*/
void Test_StressTemplateArray(const std::size_t NumTests) {
	DEFINE_FUNCTION("Test_StressTemplateArray()");
	CPCharArray StringArray1(100);
	std::size_t LoopCounter;
	std::size_t LoopCounter1;
	std::size_t NumAllocs;
	std::size_t TestSize;
	SystemLog.Printf(std::stdout,
	                 "================ Stressing the TTemplateArray Class ====================");
	std::srand((std::size_t)std::time(NULL));
	ErrorHandler.ClearErrors();
	ErrorDatabase.ClearErrors();
	OutputBlockInfo();

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		/* Create a random sized array */
		TestSize = (std::size_t)((float)std::rand() * 100000l / RAND_MAX) + 1;
		CPCharArray StringArray2(TestSize, 0);
		NumAllocs = (std::size_t)((float)std::rand() * 1100 / RAND_MAX) + 1;
		SystemLog.Printf(std::stdout,
		                 "\t%u) Adding %u random sized strings...",
		                 LoopCounter,
		                 NumAllocs);

		/* Add random sized strings */
		for (LoopCounter1 = 0; LoopCounter1 < NumAllocs; LoopCounter1++) {
			TestSize = (std::size_t)((float)std::rand() * 24000 / RAND_MAX);
			StringArray1.AddElement(CreateString(TestSize));
			StringArray2.AddElement(CreateString(TestSize));

			/* Run the DeleteElement() method */
			if ((rand() % 4) == 0) {
				StringArray1.DeleteElement((int)((float)std::rand() * (StringArray1.GetNumElements() - 1) / RAND_MAX));
				StringArray2.DeleteElement((int)((float)std::rand() * (StringArray2.GetNumElements() - 1) / RAND_MAX));
			} else if ((std::rand() % 10) == 0) { /* Run the FreeExtra() method */
				StringArray1.FreeExtra();
			}
		}

		/* Delete allocated memory */
		StringArray2.AssertValid();
		StringArray1.AssertValid();
		StringArray2.Destroy();
		StringArray1.Destroy();
		ErrorHandler.ClearErrors();
		ASSERT(DebugHeapCheckMemory());
		OutputBlockInfo();
	}
}


/*===========================================================================
 *
 * Function - void Test_TemplateArray (void);
 *
 * Tests the TTemplateArray class.
 *  1. Tests construction with typical sample templates
 *  2. Test the GetMaxElements() and GetNumElements() methods
 *  3. Test the AddElement() method
 *  4. Test the GetElement() method
 *  5. Test the [] operator
 *  6. Test the DeleteElement() method
 *  7. Test th Destroy() method
 *  8. Test the IsValidIndex() method
 *  9. Test the class destructor
 *  10. Test the SetGrowSize() method
 *  11. Test the FreeExtra() method

 *
 *=========================================================================*/
void Test_TemplateArray() {
	DEFINE_FUNCTION("Test_TemplateArray()");
	long *pTestInt;
	char *pTestPtr;
	testdata_t *pTestData;
	SystemLog.Printf(std::stdout,
	                 "================ Testing the TTemplateArray Class ====================");

	/* Test construction of sample templates */
	TTemplateArray<long> IntArray(100);
	TTemplateArray<char> StringArray2(2, 0);
	TTemplateArray<char> StringArray(2, 0);
	CTestDataArray TestDataArray(1, 10);

	/* Test the GetMaxElements() method */
	ASSERT(IntArray.GetMaxElements() == 100);
	ASSERT(StringArray.GetMaxElements() == 2);
	ASSERT(TestDataArray.GetMaxElements() == 1);

	/* Test the GetNumElements() methods */
	ASSERT(IntArray.GetNumElements() == 0);
	ASSERT(StringArray.GetNumElements() == 0);
	ASSERT(TestDataArray.GetNumElements() == 0);

	/* Test the AddElement() method */
	CreatePointer(pTestInt, (long)(12345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	CreatePointer(pTestInt, (long)(22345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	CreatePointer(pTestInt, (long)(32345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	ASSERT(StringArray.AddElement(CreateString("Test String #1")) == TRUE);
	ASSERT(StringArray.AddElement(CreateString("Test String #2")) == TRUE);
	pTestPtr = CreateString("Invalid element String");
	ASSERT(StringArray.AddElement(pTestPtr) == FALSE);
	DestroyArrayPointer(pTestPtr);
	CreatePointer(pTestData, testdata_t);
	pTestData->Number = 123;
	pTestData->lNumber = 222222l;
	std::strcpy(pTestData->Message, "Test Message");
	ASSERT(TestDataArray.AddElement(pTestData) == TRUE);

	/* Test the GetNumElements() methods */
	ASSERT(IntArray.GetNumElements() == 3);
	ASSERT(StringArray.GetNumElements() == 2);
	ASSERT(TestDataArray.GetNumElements() == 1);

	/* Test the IsValidIndex() method */
	ASSERT(IntArray.IsValidIndex(0) == TRUE);
	ASSERT(IntArray.IsValidIndex(1) == TRUE);
	ASSERT(IntArray.IsValidIndex(2) == TRUE);
	ASSERT(IntArray.IsValidIndex(3) == FALSE);
	ASSERT(IntArray.IsValidIndex(-1) == FALSE);

	/* Test the GetElement() method */
	ASSERT(IntArray.GetElement(&pTestInt, 0) == TRUE);
	ASSERT(*pTestInt == 12345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 1) == TRUE);
	ASSERT(*pTestInt == 22345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 2) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(StringArray.GetElement(&pTestPtr, 0) == TRUE);
	ASSERT(std::strcmp(pTestPtr, "Test String #1") == 0);
	ASSERT(StringArray.GetElement(&pTestPtr, 1) == TRUE);
	ASSERT(std::strcmp(pTestPtr, "Test String #2") == 0);
	ASSERT(TestDataArray.GetElement(&pTestData, 0) == TRUE);
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(std::strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the [] operator */
	ASSERT(*IntArray[0] == 12345678l);
	ASSERT(*IntArray[1] == 22345678l);
	ASSERT(*IntArray[2] == 32345678l);
	ASSERT(std::strcmp(StringArray[0], "Test String #1") == 0);
	ASSERT(std::strcmp(StringArray[1], "Test String #2") == 0);
	pTestData = TestDataArray[0];
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(std::strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the DeleteElement() method */
	IntArray.DeleteElement(1);
	ASSERT(IntArray.GetNumElements() == 2);
	ASSERT(*IntArray[0] == 12345678l);
	ASSERT(*IntArray[1] == 32345678l);
	IntArray.DeleteElement(0);
	ASSERT(IntArray.GetNumElements() == 1);
	ASSERT(*IntArray[0] == 32345678l);
	IntArray.DeleteElement(0);
	ASSERT(IntArray.GetNumElements() == 0);

	/* Test the Destroy() method */
	StringArray.Destroy();
	ASSERT(StringArray.GetNumElements() == 0);

	/* Test the IsValidIndex() method again */
	ASSERT(IntArray.IsValidIndex(0) == FALSE);
	ASSERT(StringArray.IsValidIndex(0) == FALSE);

	/* Test the SetGrowSize() method */
	ASSERT(StringArray2.AddElement(CreateString("Test String #1")) == TRUE);
	ASSERT(StringArray2.AddElement(CreateString("Test String #2")) == TRUE);
	pTestPtr = CreateString("Invalid element String");
	ASSERT(StringArray2.AddElement(pTestPtr) == FALSE);
	StringArray2.SetGrowSize(1);
	ASSERT(StringArray2.AddElement(pTestPtr) == TRUE);
	ASSERT(StringArray2.GetMaxElements() == 3);
	ASSERT(StringArray2.GetNumElements() == 3);
	StringArray2.SetGrowSize(-1);
	ASSERT(StringArray2.AddElement(CreateString("Test String #4")) == TRUE);
	ASSERT(StringArray2.AddElement(CreateString("Test String #5")) == TRUE);

	/* Test the FreeExtra() method */
	ASSERT(StringArray2.GetMaxElements() > StringArray2.GetNumElements());
	StringArray2.FreeExtra();
	ASSERT(StringArray2.GetMaxElements() == StringArray2.GetNumElements());
	ASSERT(std::strcmp(StringArray2[0], "Test String #1") == 0);
	ASSERT(std::strcmp(StringArray2[1], "Test String #2") == 0);
	ASSERT(std::strcmp(StringArray2[2], "Invalid element String") == 0);
	ASSERT(std::strcmp(StringArray2[3], "Test String #4") == 0);
	ASSERT(IsValidPointer(StringArray2[0]));
	ASSERT(IsValidPointer(StringArray2[1]));
	ASSERT(IsValidPointer(StringArray2[2]));
	ASSERT(IsValidPointer(StringArray2[3]));
	StringArray2.AssertValid();
	StringArray2.Destroy();
}

#endif  // _DEBUG
