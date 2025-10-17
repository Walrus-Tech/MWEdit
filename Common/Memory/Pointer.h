/*===========================================================================
 *
 * File:    Pointer.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, May 08, 2001
 *
 * Contains the definition for a simple smart pointer template class
 * CSPointer.
 *
 *=========================================================================*/
#ifndef __POINTER_H
#define __POINTER_H


#include "Common/dl_base.h"
#include "Common/dl_mem.h"


/*===========================================================================
 *
 * Begin Class CSPointer Definition
 *
 * A simple smart pointer template class which supports auto deletion
 * of pointers but not reference counting.
 *
 *=========================================================================*/
template <class TPtr> class CSPointer {
  private:
	TPtr *m_pPointer;   /* The pointer to the template class object */
	boolean AutoDelete; /* Determines whether pointer is deleted when destructed */


  public:
	/* Class Constructor */
	CSPointer(TPtr *pNewPtr) : m_pPointer(pNewPtr) {
		AutoDelete = TRUE;
	}

	CSPointer() {
		m_pPointer = NULL;
		AutoDelete = TRUE;
	}

	/* Class Destructors */
	virtual ~CSPointer() {
		Destroy();
	}

	virtual void Destroy() {
		if (AutoDelete) {
			DestroyPointer(m_pPointer);
		} else {
			m_pPointer = NULL;
		}
	}

	/* Copy the object pointer, but don't delete it */
	CSPointer &Clone(TPtr *pSourcePtr) {
		Destroy();
		m_pPointer = pSourcePtr;
		AutoDelete = FALSE;
		return *this;
	}

	CSPointer &Clone(TPtr &Source) {
		Destroy();
		m_pPointer = &Source;
		AutoDelete = FALSE;
		return *this;
	}

	/* Access the class object pointer */
	virtual TPtr *Get() {
		return m_pPointer;
	}

	operator TPtr *() {
		return m_pPointer;
	}

	TPtr &operator *() {
		return *m_pPointer;
	}

	TPtr *operator ->() {
		return m_pPointer;
	}

	CSPointer &operator =(CSPointer<TPtr> &pSourcePtr) {
		return Clone((TPtr *)pSourcePtr);
	}

	CSPointer &operator =(TPtr *pSourcePtr) {
		Destroy();
		m_pPointer = pSourcePtr;
		AutoDelete = TRUE;
		return *this;
	}
};

typedef CSPointer<char> spchar_t;
typedef CSPointer<byte> spbyte_t;
typedef CSPointer<int> spint_t;
typedef CSPointer<uint> spuint_t;
typedef CSPointer<long> splong_t;
typedef CSPointer<ulong> spulong_t;


#endif
