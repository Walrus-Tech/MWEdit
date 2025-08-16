/*===========================================================================
 *
 * File:    EsmRegion.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMREGION_H
#define __ESMREGION_H


#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubWEAT.h"
#include "EsmSubNameFix.h"
#include "EsmSubLong.h"
#include "EsmSubSNAM.h"


/*===========================================================================
 *
 * Begin Class CEsmRegion Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmRegion : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pNameData;
	CEsmSubWEAT *m_pWeatherData;
	CEsmSubNameFix *m_pCreatureData;
	CEsmSubLong *m_pColorData;


  public:
	/* Class Constructors/Destructors */
	CEsmRegion();
	//virtual ~CEsmRegion() { Destroy(); }
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
		return _T("Region");
	}

	/* Get class members */
	weatherdata_t *GetWeatherData() {
		return m_pWeatherData ? m_pWeatherData->GetWeatherData() : NULL;
	}

	const TCHAR *GetName() {
		return m_pNameData ? m_pNameData->GetName() : _T("");
	}

	const TCHAR *GetCreature() {
		return m_pCreatureData ? m_pCreatureData->GetName() : _T("");
	}

	long GetColor() {
		return m_pColorData ? m_pColorData->GetValue() : 0;
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetName(const TCHAR *pString) {
		if (m_pNameData) {
			m_pNameData->SetName(pString);
		}
	}

	void SetCreature(const TCHAR *pString);
	void SetColor(const long Color) {
		if (m_pColorData) {
			m_pColorData->SetValue(Color);
		}
	}
};


#endif
