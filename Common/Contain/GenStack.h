/*===========================================================================
 *
 * File:    Genstack.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 21, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __GENSTACK_H
#define __GENSTACK_H


/* Default stack size */
#define GENSTACK_DEFAULT_SIZE 32


/*===========================================================================
 *
 * Begin Class CGenStack Definition
 *
 * Holds a stack of void* pointers.  The pointers are not deleted when
 * they are removed.
 *
 *=========================================================================*/
class CGenStack {
  protected:
	void **m_ppStack;   /* Pointer to array of void pointers */
	int m_NumElements;  /* Number of elements on the stack */
	int m_NumAllocated; /* Size of allocated array */

	/* Changes the size of the array */
	bool AllocSize(const int Size);


  public:
	/* Class Constructors/Destructors */
	CGenStack(const int Size = GENSTACK_DEFAULT_SIZE);
	virtual ~CGenStack();

	/* Get class members */
	int GetSize() const {
		return m_NumElements;
	}

	bool IsEmpty() const {
		return m_NumElements == 0;
	}

	/* Stack access */
	void *Peek();
	void *Pop();
	void *GetAt(const int Index);
	void Push(void *pData);

	/* Remove all elements from the stack */
	void RemoveAll();

	/* Changes the size of the stack */
	bool SetSize(const int Size);
};


#endif  // __GENSTACK_H
