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


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "SString.h"
#include "PtrArray.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Local private string array definition */
typedef TPtrArray<CSString> CSSArrayPriv;
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSStringArray Definition
 *
 * Description
 *
 *=========================================================================*/
class CSStringArray {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	CSSArrayPriv m_Strings;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper function to delete all elements */
	void DeleteStrings(void);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CSStringArray();
	virtual ~CSStringArray() {
		Destroy();
	}

	virtual void Destroy(void);
	void RemoveAll(void) {
		Destroy();
	}

	/* Add a new string object */
	CSString *Add(const TCHAR *pString);

	/* Remove elements */
	void DeleteElement(CSString *pString);
	void DeleteElement(const int Index);

	/* Access elements */
	CSString *GetAt(const int Index) {
		return (m_Strings.GetAt(Index));
	}

	/* Get class members */
	int GetNumElements(void) const {
		return (m_Strings.GetNumElements());
	}

	bool IsValidIndex(const int Index) const {
		return (m_Strings.IsValidIndex(Index));
	}

};

/*===========================================================================
 *      End of Class CSStringArray Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Ssarray.H
 *=========================================================================*/
