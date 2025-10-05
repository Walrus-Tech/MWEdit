/*===========================================================================
 *
 * File:    Ssarray.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, December 18, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SSARRAY_H
#define __SSARRAY_H


#include "Common/String/SString.h"
#include "Common/Contain/PtrArray.h"


/* Local private string array definition */
typedef TPtrArray<CSString> CSSArrayPriv;


/*===========================================================================
 *
 * Begin Class CSStringArray Definition
 *
 * Description
 *
 *=========================================================================*/
class CSStringArray {
  private:
	CSSArrayPriv m_Strings;


  protected:
	/* Helper function to delete all elements */
	void DeleteStrings();


  public:
	/* Class Constructors/Destructors */
	CSStringArray();
	virtual ~CSStringArray() {
		Destroy();
	}

	virtual void Destroy();
	void RemoveAll() {
		Destroy();
	}

	/* Add a new string object */
	CSString *Add(const TCHAR *pString);

	/* Remove elements */
	void DeleteElement(CSString *pString);
	void DeleteElement(const int Index);

	/* Access elements */
	CSString *GetAt(const int Index) {
		return m_Strings.GetAt(Index);
	}

	/* Get class members */
	int GetNumElements() const {
		return m_Strings.GetNumElements();
	}

	bool IsValidIndex(const int Index) const {
		return m_Strings.IsValidIndex(Index);
	}
};


#endif
