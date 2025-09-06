/*===========================================================================
 *
 * File:    PtrArray.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Defines a simple template array of pointers class, TPtrArray. A
 * pointer array contains pointer to typed objects that do not belong
 * to the array.  The objects are not deleted when the array is deleted.
 *
 *=========================================================================*/
#ifndef __PTRARRAY_H
#define __PTRARRAY_H


#include "dl_base.h"
#include "dl_mem.h"
#include "dl_err.h"
#include <limits.h>
#include <memory.h>
#include "math.h"


/* Macro for iterating through an array */
#if !defined(ITERATE_ARRAY)
	#define ITERATE_ARRAY(Array, Index, pRecord) for (Index = 0; Index < Array.GetNumElements(), pRecord = Array.GetAt(Index); Index++)
#endif

/*===========================================================================
 *
 * Begin Class TPtrArray Definition
 *
 * Simple template class for handling an array of typed pointers.  The
 * objects pointed to belong to the array and are deleted when the array
 * is deleted.
 *
 *=========================================================================*/
template <class TArrayPtr> class TPtrArray {
  private:
	TArrayPtr **m_ppArray;     /* Contains the array of pointers to objects */
	int m_MaxElements;         /* Maximum size of array */
	int m_NumElements;         /* Current number of elements in array */
	int m_GrowSize;            /* Amount to grow array when limit reached */

	PQSORT_CMPFUNC m_pCmpFunc; /* Pointer to a user supplied compare function */
	long m_CmpFuncData;        /* User supplied data for the compare function */


  protected:
	/* Changes the max-size of the array */
	void ResizeArray(const bool GrowArray);
	void ResizeArray(const int NewSize);


  public:
	/* Class Constructors/Destructors */
	TPtrArray(const int MaxSize = 0, const int GrowSize = -1);
	virtual ~TPtrArray();
	virtual void Destroy();

	void RemoveAll() {
		Destroy();
	}

	/* Tests the contents to ensure they are valid */
#if defined(_DEBUG)
	bool AssertValid();
#endif

	/* Attempts to add a new object to the end of the array */
	bool AddElement(TArrayPtr *pNewElement);
	int Add(TArrayPtr *pNewElement);
	int AddHead(TArrayPtr *pNewElement);
	void AddSort(TArrayPtr *pNewElement);
	void AddSortFast(TArrayPtr *pNewElement);
	int Insert(TArrayPtr *pNewElement, const int Index);

	/* Attempts to delete an element from the array */
	void DeleteElement(const int Index);
	void DeleteElement(TArrayPtr *pElement);

	void RemoveAt(const int Index) {
		DeleteElement(Index);
	}

	/* Find an element in the array */
	int FindElement(TArrayPtr *pElement);
	int FindFast(TArrayPtr *pElement);
	int FindFastFunc(PQSORT_CMPFUNC pCompareFunc, void *pElement2);
	int FindInsertLoc(TArrayPtr *pElement);
	int FindBSearch(PQSORT_CMPFUNC_ORIG pCompareFunc, void *pElement2);

	/* Frees any extra allocated memory */
	void FreeExtra() {
		ResizeArray(false);
	}

	/* Get the array size */
	int GetMaxElements() const {
		return m_MaxElements;
	}

	int GetNumElements() const {
		return m_NumElements;
	}

	int GetGrowSize() const {
		return m_GrowSize;
	}

	int GetSize() const {
		return m_NumElements;
	}

	int GetUpperBound() const {
		return m_NumElements - 1;
	}

	/* Attempt to retrieve an array element */
	bool GetElement(TArrayPtr **ppElement, const int Index) const;
	TArrayPtr *GetAt(const int Index);

	/* Inserts an element after the given index */
	bool InsertAfter(const int Index, TArrayPtr *pElement);
	bool InsertBefore(const int Index, TArrayPtr *pElement);
	bool InsertAt(const int Index, TArrayPtr *pElement) {
		return InsertBefore(Index, pElement);
	}

	/* Ensures the given array index is valid */
	bool IsValidIndex(const int Index) const {
		return (Index >= 0 && Index < m_NumElements) ? true : false;
	}

	/* Attempts to get the specified array element */
	TArrayPtr *operator[](const int Index) const;

	/* Change the grow size */
	void SetGrowSize(const int GrowSize = -1) {
		m_GrowSize = GrowSize;
	}

	void SetMaxElements(const int MaxSize) {
		ResizeArray(MaxSize);
	}

	void SetSize(const int NewSize) {
		SetMaxElements(NewSize);
	}

	/* Set the user supplied compare function */
	void SetCompareFunc(PQSORT_CMPFUNC pFunction) {
		m_pCmpFunc = pFunction;
	}

	void SetCmpFuncData(const long lUserData) {
		m_CmpFuncData = lUserData;
	}

	/* Sorts the array using the current compare function */
	void Sort(const long lUserData);
};


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
			               (void * )pNewElement,
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


#if defined(_DEBUG)
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

#endif


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
	int CompIndex = (int)ceil((EndIndex - StartIndex) / 2.0f);
	int Result;

	while (EndIndex - StartIndex > 1) {
		Result = m_pCmpFunc(m_ppArray[CompIndex], pElement, m_CmpFuncData);

		if (Result == 0) {
			return (CompIndex);
		} else if (Result > 0) {
			EndIndex = CompIndex;
			CompIndex = StartIndex + (int)ceil((EndIndex - StartIndex) / 2.0f);
		} else {
			StartIndex = CompIndex;
			CompIndex = StartIndex + (int)ceil((EndIndex - StartIndex) / 2.0f);
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
	int CompIndex = (int)ceil((EndIndex - StartIndex) / 2.0f);
	int Result;

	while (EndIndex - StartIndex > 1) {
		Result = pCompareFunc(m_ppArray[CompIndex], pElement2, m_CmpFuncData);

		if (Result == 0) {
			return CompIndex;
		} else if (Result > 0) {
			EndIndex = CompIndex;
			CompIndex = StartIndex + (int)ceil((EndIndex - StartIndex) / 2.0f);
		} else {
			StartIndex = CompIndex;
			CompIndex = StartIndex + (int)ceil((EndIndex - StartIndex) / 2.0f);
		}
	}

	Result = pCompareFunc(m_ppArray[StartIndex], pElement2, m_CmpFuncData);

	if (Result == 0) {
		return (StartIndex);
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
	pResult = (TArrayPtr **)bsearch(pElement,
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
		memcpy(ppNewArray, m_ppArray, sizeof(TArrayPtr *)*m_NumElements);
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
		memcpy(ppNewArray, m_ppArray, sizeof(TArrayPtr *)*m_NumElements);
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


#if defined(_DEBUG)
	void Test_StressPtrArray(const int NumTests = 100);
	void Test_PtrArray();
#endif


#endif
