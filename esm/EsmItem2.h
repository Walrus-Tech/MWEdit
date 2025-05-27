/*===========================================================================
 *
 * File:    EsmItem2.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Base class for all records (9) with:
 *  ID  }
 *  Name    } CEsmItem1
 *  Script  }
 *  Model   }
 *  Icon
 *  Weight
 *  Value
 *
 *=========================================================================*/
#ifndef __ESMITEM2_H
#define __ESMITEM2_H


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
 * Begin Definitions
 *
 *=========================================================================*/

/* Class type flag (bit field) */
#define MWESM_CLASSTYPE_ITEM2 4

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmItem2 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmItem2 : public CEsmItem1 {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNameFix *m_pIcon;        /* Reference to record fields */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmItem2();
	//virtual ~CEsmItem2() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Used to determine the type of derived classes */
	virtual int GetClassType(void) {
		return (CEsmItem1::GetClassType() | MWESM_CLASSTYPE_ITEM2);
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Get class members */
	const TCHAR *GetIcon(void) const {
		return (m_pIcon ? m_pIcon->GetName() : _T(""));
	}

	virtual float GetWeight(void) {
		return (0);
	}

	virtual long GetValue(void) {
		return (0);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetIcon(const TCHAR *pIcon);
	virtual void SetWeight(const float Weight) { }

	virtual void SetValue(const long Value) { }

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmItem2 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
