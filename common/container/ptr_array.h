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

#include <cstddef>

#include "Common/dl_base.h"


/* Macro for iterating through an array */
#if !ITERATE_ARRAY
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
#if _DEBUG
	bool AssertValid();
#endif  // _DEBUG

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


#if _DEBUG
	void Test_StressPtrArray(const std::size_t NumTests = 100);
	void Test_PtrArray();
#endif  // _DEBUG


#endif  // __PTRARRAY_H
