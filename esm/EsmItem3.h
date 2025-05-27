/*===========================================================================
 *
 * File:    EsmItem3H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Base class for all records (4: ARMO, WEAP, CLOT) with:
 *  ID  }
 *  Name    } CEsmItem1
 *  Script  }
 *  Model   }
 *
 *  Icon    }
 *  Weight  } CEsmItem3
 *  Value   }
 *
 *  Enchant
 *  Enchant Pts
 *
 *=========================================================================*/
#ifndef __ESMITEM3H
#define __ESMITEM3H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Class type flag (bit field) */
#define MWESM_CLASSTYPE_ITEM3 8

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmItem3 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmItem3 : public CEsmItem2 {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pEnchant;     /* Reference to record fields */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmItem3();
	//virtual ~CEsmItem3() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Used to determine the type of derived classes */
	virtual int GetClassType(void) {
		return (CEsmItem2::GetClassType() | MWESM_CLASSTYPE_ITEM3);
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Get class members */
	const TCHAR *GetEnchant(void) const {
		return (m_pEnchant ? m_pEnchant->GetName() : _T(""));
	}

	virtual long GetEnchantPts(void) {
		return (0);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetEnchant(const TCHAR *pEnchant);
	virtual void SetEnchantPts(const long Points) { }

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmItem3 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
