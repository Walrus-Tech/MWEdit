/*===========================================================================
 *
 * File:    EsmTES3.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 *
 *=========================================================================*/
#ifndef __ESMTES3_H
#define __ESMTES3_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubHEDR.h"
#include "EsmSubName.h"
#include "EsmSubLong64.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmTES3 Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmTES3 : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubHEDR *m_pHeader; /* Reference to record fields */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmTES3();
	//virtual ~CEsmArmor() { Destroy(); }
	virtual void Destroy();

	/* Adds a master sub-record */
	void AddMaster(const TCHAR *pFilename, const long FileSize);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get class members */
	headerdata_t *GetHeaderData() {
		return m_pHeader ? m_pHeader->GetHeaderData() : NULL;
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);
};

/*===========================================================================
 *      End of Class CEsmTES3 Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Esmarmor.H
 *=========================================================================*/
