/*===========================================================================
 *
 * File:    EsmAlchemy.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMALCHEMY_H
#define __ESMALCHEMY_H


#include "esm/EsmItem2.h"
#include "esm/EsmSubENAM.h"
#include "esm/EsmSubALDT.h"


/* Number of enchantments allowed per alchemy object */
#define MWESM_ALCHEMY_NUMENCHANTS 8


/*===========================================================================
 *
 * Begin Class CEsmAlchemy Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmAlchemy : public CEsmItem2 {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubALDT *m_pAlchemyData; /* Reference to subrecords */

  public:
	/* Class Constructors/Destructors */
	CEsmAlchemy();
	//virtual ~CEsmAlchemy() { Destroy(); }
	virtual void Destroy();
	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);
	/* Return a new record object */
	static CEsmRecord *Create();
	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);
	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);
	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Alchemy");
	}
	/* Get class members */
	alchemydata_t *GetAlchemyData() {
		return m_pAlchemyData == NULL ? NULL : m_pAlchemyData->GetAlchemyData();
	}
	virtual float GetWeight() {
		return m_pAlchemyData == NULL ? 0 : m_pAlchemyData->GetWeight();
	}
	virtual long GetValue() {
		return m_pAlchemyData == NULL ? 0 : m_pAlchemyData->GetValue();
	}
	bool IsAutoCalc() {
		return m_pAlchemyData ? m_pAlchemyData->IsAutoCalc() : false;
	}
	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);
	/* Set class members */
	virtual void SetIcon(const TCHAR *pIcon);
	void SetAutoCalc(const bool Flag) {
		if (m_pAlchemyData) {
			m_pAlchemyData->SetAutoCalc(Flag);
		}
	}
	virtual void SetWeight(const float Weight) {
		if (m_pAlchemyData) {
			m_pAlchemyData->SetWeight(Weight);
		}
	}
	virtual void SetValue(const long Value) {
		if (m_pAlchemyData) {
			m_pAlchemyData->SetValue(Value);
		}
	}
	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


/* Convert an armor type to a string */
const TCHAR *GetESMArmorType(const int ArmorType);


#endif
