/*===========================================================================
 *
 * File:    Objarray.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, December 31, 2003
 *
 * Defines the template class TObjArray which defines a class to hold an
 * array of arbritrary type with the objects belonging to the array (they
 * are deleted/created automatically as required). Uses the TPtrArray
 * template class.
 *
 *=========================================================================*/
#ifndef __OBJARRAY_H
#define __OBJARRAY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "PtrArray.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class TObjArray Definition
 *
 * An array of objects that 'belong' to the array and are created and
 * deleted automatically.
 *
 *=========================================================================*/
template <class CObjType> class TObjArray {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	TPtrArray<CObjType> m_Array; /* Array of object pointers */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper function to delete all elements */
	void DeleteElements_Priv();


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	TObjArray(const int MaxSize = 0, const int GrowSize = -1);
	virtual ~TObjArray() {
		Destroy();
	}

	/* Delete the array */
	virtual void Destroy();
	void RemoveAll() {
		Destroy();
	}

	/* Add a new object */
	int Add(CObjType *pObject) {
		return m_Array.Add(pObject);
	}

	bool AddElement(CObjType *pObject) {
		return m_Array.AddElement(pObject);
	}

	int AddHead(CObjType *pObject) {
		return m_Array.AddHead(pObject);
	}

	void AddSort(CObjType *pObject) {
		m_Array.AddSort(pObject);
	}

	void AddSortFast(CObjType *pObject) {
		m_Array.AddSortFast(pObject);
	}

	CObjType *AddNew();

	/* Delete elements */
	void DeleteElement(CObjType *pObject);
	void DeleteElement(const int Index);
	void RemoveAt(const int Index) {
		DeleteElement(Index);
	}

	/* Find an element in the array */
	int FindElement(CObjType *pObject) {
		return m_Array.FindElement(pObject);
	}

	int FindFast(CObjType *pObject) {
		return m_Array.FindFast(pObject);
	}

	int FindInsertLoc(CObjType *pObject) {
		return m_Array.FindInsertLoc(pObject);
	}

	int FindFastFunc(PQSORT_CMPFUNC pCompareFunc, void *pObject2) {
		return m_Array.FindFastFunc(pCompareFunc, pObject2);
	}

	int FindBSearch(PQSORT_CMPFUNC_ORIG pCompareFunc, void *pObject2) {
		return m_Array.FindBSearch(pCompareFunc, pObject2);
	}

	/* Frees any extra allocated memory */
	void FreeExtra() {
		m_Array.FreeExtra();
	}

	/* Access elements */
	CObjType *GetAt(const int Index) {
		return m_Array.GetAt(Index);
	}

	bool GetElement(CObjType **ppObject, const int Index) const {
		return m_Array.GetElement(ppObject, Index);
	}

	/* Get class members */
	int GetNumElements() const {
		return m_Array.GetNumElements();
	}

	int GetMaxElements() const {
		return m_Array.GetMaxElements();
	}

	int GetUpperBound() const {
		return m_Array.GetUpperBound();
	}

	int GetGrowSize() const {
		return m_Array.GetGrowSize();
	}

	int GetSize() const {
		return m_Array.GetSize();
	}

	/* Ensures the given array index is valid */
	bool IsValidIndex(const int Index) const {
		return m_Array.IsValidIndex(Index);
	}

	/* Inserts an element after the given index */
	int Insert(CObjType *pObject, const int Index) {
		return m_Array.Insert(pObject, Index);
	}

	bool InsertAfter(const int Index, CObjType *pObject) {
		return m_Array.InsertAfter(Index, pObject);
	}

	bool InsertBefore(const int Index, CObjType *pObject) {
		return m_Array.InsertBefore(Index, pObject);
	}

	bool InsertAt(const int Index, CObjType *pObject) {
		return m_Array.InsertAt(Index, pObject);
	}

	/* Attempts to get the specified array element */
	CObjType *operator[](const int Index) const {
		return m_Array[Index];
	}

	/* Change the grow size */
	void SetGrowSize(const int GrowSize = -1) {
		m_Array.SetGrowSize(GrowSize);
	}

	void SetMaxElements(const int MaxSize);
	void SetSize(const int NewSize) {
		SetMaxElements(NewSize);
	}

	/* Set the user supplied compare function */
	void SetCompareFunc(PQSORT_CMPFUNC pFunction) {
		m_Array.SetCompareFunc(pFunction);
	}

	void SetCmpFuncData(const long lUserData) {
		m_Array.SetCompareFunc(lUserData);
	}

	/* Sorts the array using the current compare function */
	void Sort(const long lUserData) {
		m_Array.Sort(lUserData);
	}
};

/*===========================================================================
 *      End of Class TObjArray Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObjArray Constructor - TObjArray (MaxSize);
 *
 * Attempts to create an array with the given maximum number of elements.
 * ASSERTs if given invalid input.
 *
 *=========================================================================*/
template <class CObjType> TObjArray<CObjType>::TObjArray(const int MaxSize, const int GrowSize) :
	m_Array(MaxSize, GrowSize) {
	//DEFINE_FUNCTION("TObjArray::TObjArray()");
}

/*===========================================================================
 *      End of Class TObjArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Template TObjArray Method - void Destroy (void);
 *
 *=========================================================================*/
template <class CObjType>
void TObjArray<CObjType>::Destroy() {
	//DEFINE_FUNCTION("TObjArray::Destroy()");
	DeleteElements_Priv();
}

/*===========================================================================
 *      End of Class Method TObjArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObjArray Method - CObjType* AddNew (void);
 *
 * Creates and adds a new object to the array. The new object is returned.
 *
 *=========================================================================*/
template <class CObjType>
CObjType *TObjArray<CObjType>::AddNew() {
	DEFINE_FUNCTION("CObjType::AddNew()");
	CObjType *pNewObject;
	/* Allocate the new object and add it to the end of the array */
	CreatePointer(pNewObject, CObjType);
	m_Array.Add(pNewObject);
	return pNewObject;
}

/*===========================================================================
 *      End of Class Method TObjArray::Add()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObjArray Method - void DeleteElement (pString);
 *
 * Attempts to delete the given element from the array. Ignores invalid input.
 *
 *=========================================================================*/
template <class CObjType>
void TObjArray<CObjType>::DeleteElement(CObjType *pObject) {
	int Index;
	/* Attempt to find the element in the array */
	Index = m_Array.FindElement(pObject);

	if (Index < 0) {
		return;
	}

	DeleteElement(Index);
}

/*===========================================================================
 *      End of Class Method TObjArray::DeleteElement()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObjArray Method - void DeleteElement (Index);
 *
 * Deletes an element given its array index. Ignores invalid input.
 *
 *=========================================================================*/
template <class CObjType>
void TObjArray<CObjType>::DeleteElement(const int Index) {
	DEFINE_FUNCTION("TObjArray::DeleteElement()");
	CObjType *pObject;
	/* Get element and ensure it is valid */
	pObject = m_Array.GetAt(Index);

	if (pObject == NULL) {
		return;
	}

	/* Delete element from array */
	m_Array.DeleteElement(Index);
	/* Delete element */
	DestroyPointer(pObject);
}

/*===========================================================================
 *      End of Class Method TObjArray::DeleteElement()
 *=========================================================================*/


/*===========================================================================
 *
 * Template TObjArray Method - void DeleteElements_Priv (void);
 *
 * Protected class method that deletes all elements currently in the array.
 *
 *=========================================================================*/
template <class CObjType>
void TObjArray<CObjType>::DeleteElements_Priv() {
	DEFINE_FUNCTION("TObjArray::DeleteElements_Priv()");
	CObjType *pObject;
	int Index;

	/* Delete each element in the array one-by-one */
	for (Index = 0; Index < m_Array.GetNumElements(); Index++) {
		pObject = m_Array.GetAt(Index);
		DestroyPointer(pObject);
	}

	/* Clear the array itself */
	m_Array.Destroy();
}

/*===========================================================================
 *      End of Class Method TObjArray::DeleteElements_Priv()
 *=========================================================================*/


/*===========================================================================
 *
 * Template TObjArray Method - void SetMaxElements (MaxSize);
 *
 * Changes the maximum size of the array. Deletes objects if required.
 *
 *=========================================================================*/
template <class CObjType>
void TObjArray<CObjType>::SetMaxElements(const int MaxSize) {
	//DEFINE_FUNCTION("TObjArray::SetMaxElements()");
	CObjType *pObject;
	int Index;

	/* Delete any truncated elements in the array one-by-one */
	for (Index = MaxSize; Index < m_Array.GetNumElements(); Index++) {
		pObject = m_Array.GetAt(Index);
		DestroyPointer(pObject);
	}

	/* Change the array size */
	m_Array.Resize(MaxSize);
}

/*===========================================================================
 *      End of Class Method TObjArray::SetMaxElements()
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Objarray.H
 *=========================================================================*/
