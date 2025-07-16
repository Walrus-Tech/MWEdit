/*===========================================================================
 *
 * File:    EsmActivator.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMACTIVATOR_H
#define __ESMACTIVATOR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem1.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmActivator Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmActivator : public CEsmItem1 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:

	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmActivator();
	//virtual ~CEsmActivator() { Destroy(); }
	virtual void Destroy();
	/* Return a new record object */
	static CEsmRecord *Create();
	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Activator");
	}
	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmActivator Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmActivator.H
 *=========================================================================*/
