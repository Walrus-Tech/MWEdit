/*===========================================================================
 *
 * File:    EsmApparatus.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMAPPARATUS_H
#define __ESMAPPARATUS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
#include "EsmSubAADT.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Convert an apparatus type to a string */
const TCHAR *GetESMAppaType(const int AppaType);
int GetESMAppaType(const TCHAR *pString);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmApparatus Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmApparatus : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubAADT *m_pAppaData; /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmApparatus();
	//virtual ~CEsmApparatus() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Apparatus");
	}

	/* Get class members */
	appadata_t *GetAppaData() {
		return m_pAppaData == NULL ? NULL : m_pAppaData->GetAppaData();
	}

	int GetAppaTypeID() {
		return m_pAppaData == NULL ? -1 : m_pAppaData->GetAppaType();
	}

	const TCHAR *GetAppaType() {
		return GetESMAppaType(GetAppaTypeID());
	}

	virtual float GetWeight() {
		return m_pAppaData == NULL ? 0 : GetAppaData()->Weight;
	}

	virtual long GetValue() {
		return m_pAppaData == NULL ? 0 : GetAppaData()->Value;
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (m_pAppaData != NULL) {
			m_pAppaData->SetWeight(Weight);
		}
	}

	virtual void SetValue(const long Value) {
		if (m_pAppaData != NULL) {
			m_pAppaData->SetValue(Value);
		}
	}

	void SetQuality(const float Quality) {
		if (m_pAppaData != NULL) {
			m_pAppaData->SetQuality(Quality);
		}
	}

	void SetAppaType(const long Type) {
		if (m_pAppaData != NULL) {
			m_pAppaData->SetAppaType(Type);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};

/*===========================================================================
 *      End of Class CEsmArmor Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
