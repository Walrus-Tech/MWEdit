/*===========================================================================
 *
 * File:    TemArray.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Defines a simple template array class, TTemplateArray.
 *
 *=========================================================================*/
#ifndef __TEMARRAY_H
#define __TEMARRAY_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_mem.h"
#include "dl_err.h"
#include <limits.h>
#include <memory.h>
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Macro for iterating through an array */
#if !defined(ITERATE_ARRAY)
	#define ITERATE_ARRAY(Array, Index, pRecord) for (Index = 0; Index < Array.GetNumElements(), pRecord = Array.GetAt(Index); Index++)
#endif


/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class TTemplateArray Definition
 *
 * Simple template class for handling an array of typed pointers.  The
 * objects pointed to belong to the array and are deleted when the array
 * is deleted.
 *
 *=========================================================================*/
template <class TArrayPtr>
class TTemplateArray {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	TArrayPtr **m_ppArray; /* Contains the array of pointers to objects */
	int m_MaxElements; /* Maximum size of array */
	int m_NumElements; /* Current number of elements in array */
	int m_GrowSize;    /* Amount to grow array when limit reached */

	PQSORT_CMPFUNC m_pCmpFunc;    /* Pointer to a user supplied compare function */
	long m_CmpFuncData; /* User supplied data for the compare function */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Changes the max-size of the array */
	void ResizeArray(const bool GrowArray);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	TTemplateArray(const int MaxSize = 0, const int GrowSize = -1);
	virtual ~TTemplateArray();
	virtual void Destroy(void);

	/* Tests the contents to ensure they are valid */
#if defined(_DEBUG)
	bool AssertValid(void);
#endif

	/* Attempts to add a new object to the end of the array */
	bool Add(TArrayPtr *pNewElement) {
		return AddElement(pNewElement);
	}

	bool AddElement(TArrayPtr *pNewElement);
	bool AddSort(TArrayPtr *pNewElement);

	/* Attempts to delete an element from the array */
	void DeleteElement(const int Index, const bool Delete = true);

	/* Frees any extra allocated memory */
	void FreeExtra(void) {
		ResizeArray(false);
	}

	/* Get the array size */
	int GetMaxElements(void) const {
		return (m_MaxElements);
	}

	int GetNumElements(void) const {
		return (m_NumElements);
	}

	int GetGrowSize(void) const {
		return (m_GrowSize);
	}

	/* Attempt to retrieve an array element */
	bool GetElement(TArrayPtr **ppElement, const int Index) const;
	TArrayPtr *GetAt(const int Index) {
		return IsValidIndex(Index) ? m_ppArray[Index] : NULL;
	}

	/* Ensures the given array index is valid */
	bool IsValidIndex(const int Index) const {
		return ((Index >= 0 && Index < m_NumElements) ? true : false);
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
 *      End of Class TTemplateArray Definition
 *=========================================================================*/


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
 *      End of Class TTemplateArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class TTemplateArray Destructor
 *
 *=========================================================================*/
template <class TArrayPtr> TTemplateArray<TArrayPtr>::~TTemplateArray(void) {
	//DEFINE_FUNCTION("TTemplateArray::~CGenArray()");
	/* Delete all the valid pointers in array */
	Destroy();
	/* Unallocate the array */
	DestroyArrayPointer(m_ppArray);
}

/*===========================================================================
 *      End of Class TTemplateArray Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class TTemplateArray Method - void Destroy (void);
 *
 * Deletes all the valid pointers currently in the array.
 *
 *=========================================================================*/
template <class TArrayPtr>
void TTemplateArray<TArrayPtr>::Destroy(void) {
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
 *      End of Class Method TTemplateArray::Destroy()
 *=========================================================================*/


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
		ErrorHandler.AddError(ERR_MAXINDEX, "A maximum of %u array elements has been reached!",
		                      m_MaxElements);
		return (false);
	}

	/* Add element to array */
	m_ppArray[m_NumElements] = pNewElement;
	m_NumElements++;
	return (true);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::AddElement()
 *=========================================================================*/


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
			if (m_pCmpFunc((void *)(m_ppArray + LoopCounter), (void *)(&pNewElement), m_CmpFuncData) > 0) {
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
			return (false);
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
	return (true);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::AddSort()
 *=========================================================================*/


#if defined(_DEBUG)
/*===========================================================================
 *
 * Class TTemplateArray Method - bool AssertValid (void);
 *
 * Tests the contents of the array to ensure they are valid.  Exists
 * in debug builds only.
 *
 *=========================================================================*/
template <class TArrayPtr>
bool TTemplateArray<TArrayPtr>::AssertValid(void) {
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

	return (true);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::AssertValid()
 *=========================================================================*/
#endif


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
 *      End of Class Method TTemplateArray::DeleteElement()
 *=========================================================================*/


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
		return (true);
	}

	/* Assert in debug builds */
	ABORT("TTemplateArray::GetElement() - Invalid array index received!");
	/* Return NULL in release builds */
	*ppElement = NULL;
	return (false);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::GetElement()
 *=========================================================================*/


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
		memcpy(ppNewArray, m_ppArray, sizeof(TArrayPtr *)*m_NumElements);
	}

	/* Set the resized array */
	ppOldArray = (byte **) m_ppArray;
	m_ppArray = ppNewArray;
	m_MaxElements = NewSize;
	/* Delete the old array (but not the objects!) */
	DestroyArrayPointer(ppOldArray);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::ResizeArray()
 *=========================================================================*/


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
	qsort((void *)m_ppArray, m_NumElements, sizeof(TArrayPtr *), m_pCmpFunc, m_CmpFuncData);
}

/*===========================================================================
 *      End of Class Method TTemplateArray<TArrayPtr>::Sort()
 *=========================================================================*/


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
		return (m_ppArray[Index]);
	}

	/* Assert in debug builds */
	ABORT("TTemplateArray::operator[]() - Invalid array index received!");
	return (NULL);
}

/*===========================================================================
 *      End of Class Method TTemplateArray::operator[]()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Module Test Function Prototypes
 *
 *=========================================================================*/
#if defined(_DEBUG)
	void Test_StressTemplateArray(const int NumTests = 100);
	void Test_TemplateArray(void);
#endif
/*===========================================================================
 *      End of Module Test Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File TemArray.H
 *=========================================================================*/
