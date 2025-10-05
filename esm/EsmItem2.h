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


#include "esm/EsmItem1.h"


/* Class type flag (bit field) */
#define MWESM_CLASSTYPE_ITEM2 4


/*===========================================================================
 *
 * Begin Class CEsmItem2 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmItem2 : public CEsmItem1 {
  protected:
	CEsmSubNameFix *m_pIcon; /* Reference to record fields */


  public:
	/* Class Constructors/Destructors */
	CEsmItem2();
	//virtual ~CEsmItem2() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Used to determine the type of derived classes */
	virtual int GetClassType() {
		return CEsmItem1::GetClassType() | MWESM_CLASSTYPE_ITEM2;
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Get class members */
	const TCHAR *GetIcon() const {
		return m_pIcon ? m_pIcon->GetName() : _T("");
	}

	virtual float GetWeight() {
		return 0;
	}

	virtual long GetValue() {
		return 0;
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


#endif
