/*===========================================================================
 *
 * File:    EsmGameSetting.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMGAMESETTING_H
#define __ESMGAMESETTING_H


#include "EsmRecord.h"
#include "EsmSubFloat.h"
#include "EsmSubLong.h"
#include "EsmSubName.h"


/* Global types */
#define MWESM_SETTING_INTEGER 1
#define MWESM_SETTING_FLOAT   2
#define MWESM_SETTING_STRING  3


/*===========================================================================
 *
 * Begin Class CEsmGameSetting Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmGameSetting : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubLong *m_pLongData;
	CEsmSubFloat *m_pFloatData;
	CEsmSubName *m_pStringData;


  public:
	/* Class Constructors/Destructors */
	CEsmGameSetting();
	//virtual ~CEsmGameSetting() { Destroy(); }
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
		return _T("Game Setting");
	}

	/* Get class members */
	const TCHAR *GetTypeString();
	int GetType();
	const TCHAR *GetValue();
	int GetType(const TCHAR *pString);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetValue(const TCHAR *pString);
	void SetGMSTType(const TCHAR *pString);

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
