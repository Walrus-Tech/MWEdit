/*===========================================================================
 *
 * File:    PtrArray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Implements the TPtrArray template for handling a simple array
 * of typed pointers which do not belong to the array.
 *
 *=========================================================================*/

/* Include Files */
#include "Common/Contain/PtrArray.h"

#include <cstddef>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>

#include "Common/dl_base.h"
#include "Common/dl_err.h"
#include "Common/dl_mem.h"

#if _DEBUG
#include <cstdio>
#include <ctime>

#include "Common/dl_block.h"
#include "Common/dl_log.h"
#endif  //_DEBUG


DEFINE_FILE("PrtArray.cpp");


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 *=========================================================================*/
#if _DEBUG
/* Test structure used for testing */
typedef struct {
	int Number;
	char Message[32];
	long lNumber;
} testdata_t;

/* Test type definitions */
typedef TPtrArray<testdata_t> CTestDataArray;
typedef TPtrArray<char> CPCharArray;
#endif  // _DEBUG


/*===========================================================================
 *
 * Class TPtrArray Constructor - TPtrArray (MaxSize);
 *
 * Attempts to create an array with the given maximum number of elements.
 * ASSERTs if given invalid input.
 *
 *=========================================================================*/
template <class TArrayPtr> TPtrArray<TArrayPtr>::TPtrArray(const int MaxSize,
                                                           const int GrowSize) {
	DEFINE_FUNCTION("TPtrArray::TPtrArray()");
	/* Ensure valid input */
	IASSERT(MaxSize <= INT_MAX / sizeof(TArrayPtr *));

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
 * Class TPtrArray Destructor
 *
 *=========================================================================*/
template <class TArrayPtr> TPtrArray<TArrayPtr>::~TPtrArray() {
	//DEFINE_FUNCTION("TPtrArray::~TPtrArray()");
	Destroy();
	/* Unallocate the array */
	DestroyArrayPointer(m_ppArray);
}


/*===========================================================================
 *
 * Class TPtrArray Method - void Destroy (void);
 *
 * Clears the array contents.  Does not delete the pointers.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TPtrArray<TArrayPtr>::Destroy() {
	//DEFINE_FUNCTION("TPtrArray::Destroy()");
	m_NumElements = 0;
}


/*===========================================================================
 *
 * Class TPtrArray Method - bool AddElement (pNewElement);
 *
 * Attempts to add a new element to the end of the array.  The input
 * element must be valid.  Returns FALSE on any error.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TPtrArray<TArrayPtr>::AddElement(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TPtrArray::AddElement()");
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);

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

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::Add(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TPtrArray::Add()");
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);

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
	return m_NumElements - 1;
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::AddHead(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TPtrArray::AddHead()");
	return InsertBefore(0, pNewElement);
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::Insert(TArrayPtr *pNewElement, const int Index) {
	int InsertCounter;

	/* Resize array if required */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	if (Index < 0) {
		for (InsertCounter = m_NumElements; InsertCounter > 0; InsertCounter--) {
			m_ppArray[InsertCounter] = m_ppArray[InsertCounter - 1];
		}

		m_ppArray[0] = pNewElement;
		m_NumElements++;
		return 0;
	} else if (Index >= m_NumElements) {
		return Add(pNewElement);
	} else {
		for (InsertCounter = m_NumElements; InsertCounter > Index; InsertCounter--) {
			m_ppArray[InsertCounter] = m_ppArray[InsertCounter - 1];
		}

		m_ppArray[Index + 1] = pNewElement;
		m_NumElements++;
	}

	return Index;
}


/*===========================================================================
 *
 * Class TPtrArray Method - bool AddSort (pNewElement);
 *
 * Attempts to add a new element to a sorted array.  The input
 * element must be valid.  Returns FALSE on any error.  Assumes that the
 * template class TArrayPtr has a defined < operator. If the array has
 * reached the maximum size, the lowest element is removed.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TPtrArray<TArrayPtr>::AddSort(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TPtrArray::AddSort()");
	int LoopCounter;
	int InsertCounter;
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);

	/* Check if we have to resize the array */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Find the position to insert the new element */
	if (m_pCmpFunc != NULL) {
		for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
			if (m_pCmpFunc((void *)m_ppArray[LoopCounter],
			               (void *)pNewElement,
			               m_CmpFuncData) > 0) {
				break;
			}
		}
	} else {
		LoopCounter = m_NumElements;
	}

	/* Shift elements after insertion point */
	for (InsertCounter = m_NumElements; InsertCounter > LoopCounter; InsertCounter--) {
		m_ppArray[InsertCounter] = m_ppArray[InsertCounter - 1];
	}

	/* Insert the new element to array */
	m_ppArray[LoopCounter] = pNewElement;
	m_NumElements++;
	return;
}

template <class TArrayPtr>
void TPtrArray<TArrayPtr>::AddSortFast(TArrayPtr *pNewElement) {
	//DEFINE_FUNCTION("TPtrArray::AddSortFast()");
	int LoopCounter;
	int InsertCounter;
	/* Ensure valid input */
	IASSERT(pNewElement != NULL);

	/* Check if we have to resize the array */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Find the position to insert the new element */
	if (m_pCmpFunc != NULL) {
		LoopCounter = FindInsertLoc(pNewElement);
		//for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
		//if (m_pCmpFunc((void*)m_ppArray[LoopCounter], (void*)pNewElement, m_CmpFuncData) > 0) break;
		//}
	} else {
		LoopCounter = m_NumElements;
	}

	/* Shift elements after insertion point */
	for (InsertCounter = m_NumElements; InsertCounter > LoopCounter; InsertCounter--) {
		m_ppArray[InsertCounter] = m_ppArray[InsertCounter - 1];
	}

	/* Insert the new element to array */
	m_ppArray[LoopCounter] = pNewElement;
	m_NumElements++;
	return;
}


#if _DEBUG
/*===========================================================================
 *
 * Class TPtrArray Method - bool AssertValid (void);
 *
 * Tests the contents of the array to ensure they are valid.  Exists
 * in debug builds only.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TPtrArray<TArrayPtr>::AssertValid() {
	DEFINE_FUNCTION("TPtrArray::AssertValid()");
	int LoopCounter;
	/* Ensure valid input */
	ASSERT(m_NumElements <= m_MaxElements);

	if (m_ppArray == NULL) {
		ASSERT(m_NumElements == 0);
		ASSERT(m_MaxElements == 0);
	} else {
		ASSERT(m_MaxElements > 0);

		for (LoopCounter = 0; LoopCounter < m_NumElements; LoopCounter++) {
			ASSERT(m_ppArray[LoopCounter] != NULL);
		}
	}

	return true;
}

#endif  // _DEBUG


/*===========================================================================
 *
 * Class TPtrArray Method - bool DeleteElement (Index);
 *
 * Attempts to remove the given array element from the array.  Returns
 * FALSE if the array index is invalid or on any other error (ASSERTs
 * in DEBUG builds).  Does not unallocate the element.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TPtrArray<TArrayPtr>::DeleteElement(const int Index) {
	//DEFINE_FUNCTION("TPtrArray::DeleteElement()");
	int LoopCounter;
	/* Ensure the index is valid */
	IASSERT(IsValidIndex(Index));

	/* Shift the array to compensate for the removed element */
	for (LoopCounter = Index; LoopCounter < m_NumElements; LoopCounter++) {
		m_ppArray[LoopCounter] = m_ppArray[LoopCounter + 1];
	}

	m_NumElements--;
	return;
}

template <class TArrayPtr>
void TPtrArray<TArrayPtr>::DeleteElement(TArrayPtr *pElement) {
	//DEFINE_FUNCTION("TPtrArray::DeleteElement()");
	int Index = FindElement(pElement);

	if (Index >= 0) {
		DeleteElement(Index);
	}
}


/*===========================================================================
 *
 * Class TTemplateArray Method - int FindElement (pElement);
 *
 *=========================================================================*/
template <class TArrayPtr>
int TPtrArray<TArrayPtr>::FindElement(TArrayPtr *pElement) {
	int Index;

	for (Index = 0; Index < m_NumElements; Index++) {
		if (m_ppArray[Index] == pElement) {
			return Index;
		}
	}

	return -1;
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::FindFast(TArrayPtr *pElement) {
	if (m_pCmpFunc == NULL || m_ppArray == NULL || m_NumElements == 0) {
		return FindElement(pElement);
	}

	int StartIndex = 0;
	int EndIndex = GetSize() - 1;
	int CompIndex = (int)std::ceil((EndIndex - StartIndex) / 2.0f);
	int Result;

	while (EndIndex - StartIndex > 1) {
		Result = m_pCmpFunc(m_ppArray[CompIndex], pElement, m_CmpFuncData);

		if (Result == 0) {
			return CompIndex;
		} else if (Result > 0) {
			EndIndex = CompIndex;
			CompIndex = StartIndex + (int)std::ceil((EndIndex - StartIndex) / 2.0f);
		} else {
			StartIndex = CompIndex;
			CompIndex = StartIndex + (int)std::ceil((EndIndex - StartIndex) / 2.0f);
		}
	}

	Result = m_pCmpFunc(m_ppArray[StartIndex], pElement, m_CmpFuncData);

	if (Result == 0) {
		return StartIndex;
	}

	Result = m_pCmpFunc(m_ppArray[EndIndex], pElement, m_CmpFuncData);

	if (Result == 0) {
		return EndIndex;
	}

	return -1;
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::FindFastFunc(PQSORT_CMPFUNC pCompareFunc, void *pElement2) {
	if (pCompareFunc == NULL || m_ppArray == NULL || m_NumElements == 0) {
		return -1;
	}

	int StartIndex = 0;
	int EndIndex = GetSize() - 1;
	int CompIndex = (int)std::ceil((EndIndex - StartIndex) / 2.0f);
	int Result;

	while (EndIndex - StartIndex > 1) {
		Result = pCompareFunc(m_ppArray[CompIndex], pElement2, m_CmpFuncData);

		if (Result == 0) {
			return CompIndex;
		} else if (Result > 0) {
			EndIndex = CompIndex;
			CompIndex = StartIndex + (int)std::ceil((EndIndex - StartIndex) / 2.0f);
		} else {
			StartIndex = CompIndex;
			CompIndex = StartIndex + (int)std::ceil((EndIndex - StartIndex) / 2.0f);
		}
	}

	Result = pCompareFunc(m_ppArray[StartIndex], pElement2, m_CmpFuncData);

	if (Result == 0) {
		return StartIndex;
	}

	Result = pCompareFunc(m_ppArray[EndIndex], pElement2, m_CmpFuncData);

	if (Result == 0) {
		return EndIndex;
	}

	return -1;
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::FindInsertLoc(TArrayPtr *pElement) {
	if (m_pCmpFunc == NULL || m_ppArray == NULL) {
		return FindElement(pElement);
	}

	int StartIndex = 0;
	int EndIndex = GetSize() - 1;
	int CompIndex = (EndIndex - StartIndex) / 2;
	int Result;

	if (GetSize() == 0) {
		return 0;
	}

	while (EndIndex - StartIndex > 1) {
		Result = m_pCmpFunc(m_ppArray[CompIndex], pElement, m_CmpFuncData);

		if (Result == 0) {
			return CompIndex;
		} else if (Result > 0) {
			EndIndex = CompIndex;
			CompIndex = StartIndex + (EndIndex - StartIndex) / 2;
		} else {
			StartIndex = CompIndex;
			CompIndex = StartIndex + (EndIndex - StartIndex) / 2;
		}
	}

	Result = m_pCmpFunc(m_ppArray[StartIndex], pElement, m_CmpFuncData);

	if (Result >= 0) {
		return StartIndex;
	}

	Result = m_pCmpFunc(m_ppArray[EndIndex], pElement, m_CmpFuncData);

	if (Result >= 0) {
		return EndIndex;
	}

	return EndIndex + 1;
}

template <class TArrayPtr>
int TPtrArray<TArrayPtr>::FindBSearch(PQSORT_CMPFUNC_ORIG pCompareFunc, void *pElement) {
	TArrayPtr **pResult;
	pResult = (TArrayPtr **)std::bsearch(pElement,
	                                     (void *)m_ppArray,
	                                     m_NumElements,
	                                     sizeof(TArrayPtr *),
	                                     pCompareFunc);

	if (pResult == NULL) {
		return -1;
	}

	return pResult - m_ppArray;
}


/*===========================================================================
 *
 * Class TTemplateArray Method - bool GetElement (ppElement, Index);
 *
 * Attempts to retrieve the specified array element.  Returns FALSE if the
 * given Index is not valid (asserts in debug builds).
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TPtrArray<TArrayPtr>::GetElement(TArrayPtr **ppElement, const int Index) const {
	//DEFINE_FUNCTION("TTemplateArray::GetElement()");

	/* Ensure the index is valid */
	if (IsValidIndex(Index)) {
		*ppElement = m_ppArray[Index];
		return true;
	}

	/* Assert in debug builds */
	//ABORT("TPtrArray::GetElement() - Invalid array index received!");
	/* Return NULL in release builds */
	*ppElement = NULL;
	return false;
}

template <class TArrayPtr>
TArrayPtr *TPtrArray<TArrayPtr>::GetAt(const int Index) {
	//DEFINE_FUNCTION("TTemplateArray::GetAt()");
	TArrayPtr *pObject;
	bool Result;
	Result = GetElement(&pObject, Index);

	if (Result) {
		return pObject;
	}

	return NULL;
}


/*===========================================================================
 *
 * Class TPtrArray Method - bool InsertAfter (Index, pElement);
 *
 * Inserts the given element after the specified Index.  If the Index is
 * not valid, the element is inserted at the end of the array.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TPtrArray<TArrayPtr>::InsertAfter(const int Index, TArrayPtr *pElement) {
	int LoopIndex;

	/* Ensure the index is valid */
	if (Index >= m_NumElements) {
		return AddElement(pElement);
	}

	/* Resize array if required */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Shift elements to make room for new element */
	for (LoopIndex = m_NumElements; LoopIndex > Index + 1; LoopIndex--) {
		m_ppArray[LoopIndex] = m_ppArray[LoopIndex - 1];
	}

	/* Insert the new element into the array */
	m_NumElements++;
	m_ppArray[Index + 1] = pElement;
	return true;
}

template <class TArrayPtr>
bool TPtrArray<TArrayPtr>::InsertBefore(const int Index, TArrayPtr *pElement) {
	int LoopIndex;

	/* Ensure the index is valid */
	if (Index > m_NumElements) {
		return AddElement(pElement);
	}

	/* Resize array if required */
	if (m_NumElements >= m_MaxElements) {
		ResizeArray(true);
	}

	/* Shift elements to make room for new element */
	for (LoopIndex = m_NumElements; LoopIndex > Index; LoopIndex--) {
		m_ppArray[LoopIndex] = m_ppArray[LoopIndex - 1];
	}

	/* Insert the new element into the array */
	m_NumElements++;
	m_ppArray[Index] = pElement;
	return true;
}


/*===========================================================================
 *
 * Class TPtrArray Method - void ResizeArray (GrowArray);
 *
 * Shrinks or grows the array depending on the input flag.  If growing the
 * array the max array size is increased by the grow size.  The default
 * grow size of -1 (or less than) indicates that the optimal grow size be
 * used.  If shrinking the array, the array maxsize is reduced to to
 * current number of defined elements in the array.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TPtrArray<TArrayPtr>::ResizeArray(const bool GrowArray) {
	DEFINE_FUNCTION("TPtrArray::ResizeArray()");
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

template <class TArrayPtr>
void TPtrArray<TArrayPtr>::ResizeArray(const int NewSize) {
	DEFINE_FUNCTION("TPtrArray::ResizeArray()");
	TArrayPtr **ppNewArray = NULL;
	byte **ppOldArray;

	/* Do nothing if array size has not changed */
	if (NewSize <= m_MaxElements) {
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
 * Class TPtrArray Method - void Sort (lUserData);
 *
 * Sorts the array using the current compare function.  Uses the standard
 * qsort algorithm and the specified user data value.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TPtrArray<TArrayPtr>::Sort(const long lUserData) {
	m_CmpFuncData = lUserData;

	/* Ignore if no compare function defined */
	if (m_pCmpFunc == NULL) {
		return;
	}

	/* Run the extended qsort() routine on the array */
	// TODO: Add qsort to common namespace to differentiate from std::qsort
	qsort((void *)m_ppArray, m_NumElements, sizeof(TArrayPtr *), m_pCmpFunc, m_CmpFuncData);
}


/*===========================================================================
 *
 * Class TPtrArray Method - void* operator[] (Index);
 *
 * Attempts to return the specified array element.  Returns NULL if the
 * index is invalid (asserts in debug builds).
 *
 *=========================================================================*/
template <class TArrayPtr>
inline TArrayPtr *TPtrArray<TArrayPtr>::operator[](const int Index) const {
	//DEFINE_FUNCTION("TPtrArray::operator[]()");

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
 * Function - void Test_StressPtrArray (NumTests);
 *
 * Runs a stress test of the TPtrArray class a number of times,
 * attempting to 'force' an error of some sort.  For each tests, a
 * random number of random sized strings are added to two char* arrays.
 *
 *=========================================================================*/
void Test_StressPtrArray(const std::size_t NumTests) {
	DEFINE_FUNCTION("Test_StressPtrArray()");
	CPCharArray StringArray1(100);
	std::size_t LoopCounter;
	std::size_t LoopCounter1;
	std::size_t NumAllocs;
	std::size_t TestSize;
	char *pBuffer;
	SystemLog.Printf(std::stdout,
	                 "================ Stressing the TPtrArray Class ====================");
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
		TestSize = (std::size_t)((float)std::rand() * 24000 / RAND_MAX);
		pBuffer = CreateString(TestSize);

		/* Add random sized strings */
		for (LoopCounter1 = 0; LoopCounter1 < NumAllocs; LoopCounter1++) {
			StringArray1.AddElement(pBuffer);
			StringArray2.AddElement(pBuffer);

			/* Run the DeleteElement() method */
			if ((std::rand() % 4) == 0) {
				StringArray1.DeleteElement((int)((float)std::rand() * (StringArray1.GetNumElements() - 1) / RAND_MAX));
				StringArray2.DeleteElement((int)((float)std::rand() * (StringArray2.GetNumElements() - 1) / RAND_MAX));
			}
			/* Run the FreeExtra() method */
			else if ((std::rand() % 10) == 0) {
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
		DestroyArrayPointer(pBuffer);
		OutputBlockInfo();
	}
}


/*===========================================================================
 *
 * Function - void Test_PtrArray (void);
 *
 * Tests the TPtrArray class.
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
void Test_PtrArray() {
	DEFINE_FUNCTION("Test_PtrArray()");
	long TestInt;
	long *pTestInt;
	char TestString[] = "Test String #1";
	char *pTestPtr;
	testdata_t TestData;
	testdata_t *pTestData;
	SystemLog.Printf(std::stdout,
	                 "================ Testing the TPtrArray Class ====================");

	/* Test construction of sample templates */
	TPtrArray<long> IntArray(100);
	TPtrArray<char> StringArray2(2, 0);
	TPtrArray<char> StringArray(2, 0);
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
	TestInt = 12345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	TestInt = 22345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	TestInt = 32345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == FALSE);
	TestData.Number = 123;
	TestData.lNumber = 222222l;
	std::strcpy(TestData.Message, "Test Message");
	ASSERT(TestDataArray.AddElement(&TestData) == TRUE);

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
	ASSERT(*pTestInt == 32345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 1) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 2) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(StringArray.GetElement(&pTestPtr, 0) == TRUE);
	ASSERT(std::strcmp(pTestPtr, TestString) == 0);
	ASSERT(StringArray.GetElement(&pTestPtr, 1) == TRUE);
	ASSERT(std::strcmp(pTestPtr, TestString) == 0);
	ASSERT(TestDataArray.GetElement(&pTestData, 0) == TRUE);
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(std::strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the [] operator */
	ASSERT(*IntArray[0] == 32345678l);
	ASSERT(*IntArray[1] == 32345678l);
	ASSERT(*IntArray[2] == 32345678l);
	ASSERT(std::strcmp(StringArray[0], TestString) == 0);
	ASSERT(std::strcmp(StringArray[1], TestString) == 0);
	pTestData = TestDataArray[0];
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(std::strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the DeleteElement() method */
	IntArray.DeleteElement(1);
	ASSERT(IntArray.GetNumElements() == 2);
	ASSERT(*IntArray[0] == 32345678l);
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
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == FALSE);
	StringArray2.SetGrowSize(1);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.GetMaxElements() == 3);
	ASSERT(StringArray2.GetNumElements() == 3);
	StringArray2.SetGrowSize(-1);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);

	/* Test the FreeExtra() method */
	ASSERT(StringArray2.GetMaxElements() > StringArray2.GetNumElements());
	StringArray2.FreeExtra();
	ASSERT(StringArray2.GetMaxElements() == StringArray2.GetNumElements());
	ASSERT(std::strcmp(StringArray2[0], TestString) == 0);
	ASSERT(std::strcmp(StringArray2[1], TestString) == 0);
	ASSERT(std::strcmp(StringArray2[2], TestString) == 0);
	ASSERT(std::strcmp(StringArray2[3], TestString) == 0);
	StringArray2.AssertValid();
	StringArray2.Destroy();
}


#endif  //_DEBUG
