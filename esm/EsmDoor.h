/*===========================================================================
 *
 * File:    EsmDoore.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMDOOR_H
#define __ESMDOOR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem1.h"
#include "EsmSubName.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmDoor Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmDoor : public CEsmItem1 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pOpenSound;
	CEsmSubNameFix *m_pCloseSound;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmDoor();
	//virtual ~CEsmDoor() { Destroy(); }
	virtual void Destroy (void);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void) {
		return _T("Door");
	}

	/* Get class members */
	const TCHAR *GetCloseSound (void) {
		return (m_pCloseSound ? m_pCloseSound->GetName() : _T(""));
	}

	const TCHAR *GetOpenSound (void) {
		return (m_pOpenSound ? m_pOpenSound->GetName() : _T(""));
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetCloseSound (const TCHAR* pSound) {
		if (m_pOpenSound) {
			m_pOpenSound->SetName(pSound);
		}
	}

	void SetOpenSound (const TCHAR* pSound) {
		if (m_pCloseSound) {
			m_pCloseSound->SetName(pSound);
		}
	}

};

/*===========================================================================
 *      End of Class CEsmDoor Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmDoor.H
 *=========================================================================*/
