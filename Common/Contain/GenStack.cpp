/*===========================================================================
 *
 * File:    Genstack.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 21, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "genstack.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("GenStack.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Constructor
 *
 *=========================================================================*/
CGenStack::CGenStack(const int Size) {
	DEFINE_FUNCTION("CGenStack::CGenStack()");
	int NewSize = (Size <= 0) ? GENSTACK_DEFAULT_SIZE : Size;
	/* Allocate the initial stack data */
	CreateArrayPointer(m_ppStack, void *, NewSize);
	m_NumElements = 0;
	m_NumAllocated = NewSize;
}

/*===========================================================================
 *      End of Class CGenStack Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Destructor
 *
 *=========================================================================*/
CGenStack::~CGenStack() {
	DEFINE_FUNCTION("CGenStack::~CGenStack()");
	/* Delete the array */
	RemoveAll();
	/* Delete the array pointer */
	DestroyArrayPointer(m_ppStack);
}

/*===========================================================================
 *      End of Class CGenStack Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - bool AllocSize (Size);
 *
 * Attempt to change the size of the stack to the given value.  Returns
 * false on any invalid size, including a size that would truncate elements.
 * Protected class method.
 *
 *=========================================================================*/
bool CGenStack::AllocSize(const int Size) {
	DEFINE_FUNCTION("CGenStack::AllocSize()");
	void **ppNewData;

	/* Check for valid input */
	if (Size <= 0) {
		ErrorHandler.AddError(ERR_BADINPUT, _T("Invalid stack size to %d!"), Size);
		return false;
	}
	/* Ensure we don't truncate existing stack elements */
	else if (m_NumElements > Size) {
		ErrorHandler.AddError(ERR_BADINPUT,
		                      _T("Cannot set the stack size to %d, %d elements would be lost!"),
		                      Size, m_NumElements - Size);
		return false;
	}

	/* Allocate the new stack data */
	CreateArrayPointer(ppNewData, void*, Size);

	/* Copy the old stack data */
	if (m_NumElements != 0) {
		memcpy(ppNewData, m_ppStack, sizeof(void *)*m_NumElements);
	}

	/* Delete the old stack and set to the new */
	DestroyArrayPointer(m_ppStack);
	m_ppStack = ppNewData;
	m_NumAllocated = Size;
	return true;
}

/*===========================================================================
 *      End of Class Method CGenStack::AllocSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - void* GetAt (Index);
 *
 * Access elements from the top of the stack. Returns NULL if index is
 * not valid.
 *
 *=========================================================================*/
void *CGenStack::GetAt(const int Index) {
	if (Index >= m_NumElements || Index < 0) {
		return NULL;
	}

	return m_ppStack[m_NumElements - 1 - Index];
}

/*===========================================================================
 *      End of Class Method CGenStack::GetAt()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - void* Peek (void);
 *
 * Returns the top item in the stack, but does not remove it.  Returns NULL
 * if no item is available.
 *
 *=========================================================================*/
void *CGenStack::Peek() {
	if (m_NumElements == 0) {
		return NULL;
	}

	return m_ppStack[m_NumElements - 1];
}

/*===========================================================================
 *      End of Class Method CGenStack::Peek()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - void* Pop (void);
 *
 * Removes and returns the top item on the stack, or NULL if the stack
 * uis empty.
 *
 *=========================================================================*/
void *CGenStack::Pop() {
	if (m_NumElements == 0) {
		return NULL;
	}

	m_NumElements--;
	return m_ppStack[m_NumElements];
}

/*===========================================================================
 *      End of Class Method CGenStack::Pop()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - void Push (void* pData);
 *
 * Adds the given item to the top of the stack.  Grows the array if
 * required.
 *
 *=========================================================================*/
void CGenStack::Push(void *pData) {
	DEFINE_FUNCTION("");

	/* Grow array as required */
	if (m_NumElements == m_NumAllocated) {
		AllocSize(m_NumElements * 2);
	}

	m_ppStack[m_NumElements] = pData;
	m_NumElements++;
}

/*===========================================================================
 *      End of Class Method CGenStack::Push()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - void RemoveAll (void);
 *
 * Remove all pointers from the stack.
 *
 *=========================================================================*/
void CGenStack::RemoveAll() {
	m_NumElements = 0;
}

/*===========================================================================
 *      End of Class Method CGenStack::RemoveAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CGenStack Method - bool SetSize (Size);
 *
 * Changes the size of the stack. Returns false on any error or if the
 * given size is too small such that it truncates existing elements.
 *
 *=========================================================================*/
bool CGenStack::SetSize(const int Size) {
	return AllocSize(Size);
}

/*===========================================================================
 *      End of Class Method CGenStack::SetSize()
 *=========================================================================*/
