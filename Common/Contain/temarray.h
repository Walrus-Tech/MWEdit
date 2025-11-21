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

#include <cstddef>

#include "Common/dl_base.h"

/* Macro for iterating through an array */
#ifndef ITERATE_ARRAY
	#define ITERATE_ARRAY(Array, Index, pRecord) for (Index = 0; Index < Array.GetNumElements(), pRecord = Array.GetAt(Index); Index++)
#endif


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


  public:
	/* Class Constructors/Destructors */
	TTemplateArray(const int MaxSize = 0, const int GrowSize = -1);
	virtual ~TTemplateArray();
	virtual void Destroy();

	/* Tests the contents to ensure they are valid */
#if _DEBUG
	bool AssertValid();
#endif  // _DEBUG

	/* Attempts to add a new object to the end of the array */
	bool Add(TArrayPtr *pNewElement) {
		return AddElement(pNewElement);
	}

	bool AddElement(TArrayPtr *pNewElement);
	bool AddSort(TArrayPtr *pNewElement);

	/* Attempts to delete an element from the array */
	void DeleteElement(const int Index, const bool Delete = true);

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

	/* Attempt to retrieve an array element */
	bool GetElement(TArrayPtr **ppElement, const int Index) const;
	TArrayPtr *GetAt(const int Index) {
		return IsValidIndex(Index) ? m_ppArray[Index] : NULL;
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
	void Test_StressTemplateArray(const std::size_t NumTests = 100);
	void Test_TemplateArray();
#endif  // _DEBUG


#endif  // __TEMARRAY_H
