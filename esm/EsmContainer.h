/*===========================================================================
 *
 * File:    EsmContainer.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCONTAINER_H
#define __ESMCONTAINER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem1.h"
#include "EsmSubCNDT.h"
#include "EsmSubLong.h"
#include "EsmSubNPCO.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Flag bit fields */
#define MWESM_CONTFLAG_DEFAULT 8  /* Not sure what '8' is */
#define MWESM_CONTFLAG_ORGANIC 1
#define MWESM_CONTFLAG_RESPAWN 2

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmContainer Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmContainer : public CEsmItem1 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubCNDT *m_pContData;
	CEsmSubLong *m_pFlag;



	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmContainer();
	//virtual ~CEsmContainer() { Destroy(); }
	virtual void Destroy(void);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("Container");
	}

	/* Get class members */
	contdata_t *GetContData(void) {
		return (m_pContData == NULL ? NULL : m_pContData->GetContData());
	}

	float GetWeight(void) {
		return (m_pContData == NULL ? 0 : m_pContData->GetWeight());
	}

	bool IsOrganic(void) {
		return (m_pFlag == NULL ? false : m_pFlag->IsFlag(MWESM_CONTFLAG_ORGANIC));
	}

	bool IsRespawn(void) {
		return (m_pFlag == NULL ? false : m_pFlag->IsFlag(MWESM_CONTFLAG_RESPAWN));
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetWeight(const float Value) {
		if (m_pContData) {
			m_pContData->SetWeight(Value);
		}
	}

	void SetOrganic(const bool Flag) {
		if (m_pFlag) {
			m_pFlag->SetFlag(MWESM_CONTFLAG_ORGANIC, Flag);
		}
	}

	void SetRespawn(const bool Flag) {
		if (m_pFlag) {
			m_pFlag->SetFlag(MWESM_CONTFLAG_RESPAWN, Flag);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmContainer Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmActivator.H
 *=========================================================================*/
