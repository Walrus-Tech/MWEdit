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


#include "esm/EsmItem1.h"
#include "esm/EsmSubName.h"


/*===========================================================================
 *
 * Begin Class CEsmDoor Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmDoor : public CEsmItem1 {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pOpenSound;
	CEsmSubNameFix *m_pCloseSound;


  public:
	/* Class Constructors/Destructors */
	CEsmDoor();
	//virtual ~CEsmDoor() { Destroy(); }
	virtual void Destroy();

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Door");
	}

	/* Get class members */
	const TCHAR *GetCloseSound() {
		return m_pCloseSound ? m_pCloseSound->GetName() : _T("");
	}

	const TCHAR *GetOpenSound() {
		return m_pOpenSound ? m_pOpenSound->GetName() : _T("");
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetCloseSound(const TCHAR *pSound) {
		if (m_pOpenSound) {
			m_pOpenSound->SetName(pSound);
		}
	}

	void SetOpenSound(const TCHAR *pSound) {
		if (m_pCloseSound) {
			m_pCloseSound->SetName(pSound);
		}
	}
};


#endif
