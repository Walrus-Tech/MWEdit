/*===========================================================================
 *
 * File:    EsmRepair.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMREPAIR_H
#define __ESMREPAIR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem2.h"
#include "EsmSubRIDT.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmRepair Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmRepair : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubRIDT *m_pRepairData;  /* Reference to subrecords */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmRepair();
	//virtual ~CEsmRepair() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Repair");
	}

	/* Get class members */
	repairdata_t *GetRepairData(void) {
		return (m_pRepairData ? m_pRepairData->GetRepairData() : NULL);
	}

	virtual float GetWeight(void) {
		return (m_pRepairData ? GetRepairData()->Weight : 0);
	}

	virtual long GetValue(void) {
		return (m_pRepairData ? GetRepairData()->Value : 0);
	}

	float GetQuality(void) {
		return (m_pRepairData ? GetRepairData()->Quality : 0);
	}

	long GetUses(void) {
		return (m_pRepairData ? GetRepairData()->Uses : 0);
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	virtual void SetWeight(const float Weight) {
		if (GetRepairData() != NULL) {
			GetRepairData()->Weight = Weight;
		}
	}

	virtual void SetValue(const long Value) {
		if (GetRepairData() != NULL) {
			GetRepairData()->Value = Value;
		}
	}

	void SetUses(const int Value) {
		if (GetRepairData()) {
			GetRepairData()->Uses = Value;
		}
	}

	void SetQuality(const float Value) {
		if (GetRepairData()) {
			GetRepairData()->Quality = Value;
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
 *      End of File EsmProbe.H
 *=========================================================================*/
