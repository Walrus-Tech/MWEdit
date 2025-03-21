/*===========================================================================
 *
 * File:    EsmDialogue.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMDIALOGUE_H
#define __ESMDIALOGUE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubNameFix.h"
#include "EsmSubByte.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Dialogue types */
#define MWESM_DIALTYPE_MIN        0
#define MWESM_DIALTYPE_TOPIC      0
#define MWESM_DIALTYPE_VOICE      1
#define MWESM_DIALTYPE_GREETING   2
#define MWESM_DIALTYPE_PERSUASION 3
#define MWESM_DIALTYPE_JOURNAL    4
#define MWESM_DIALTYPE_MAX        4

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
const TCHAR *GetESMDialogType (const int Type);
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmDialogue Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmDialogue : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubRecord *m_pData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmDialogue();
	//virtual ~CEsmDialogue() { Destroy(); }
	virtual void Destroy (void);

	/* Compare two fields of the record */
	virtual int CompareFields (const int FieldID, CEsmRecord* pRecord);

	/* Return a new record object */
	static CEsmRecord *Create (void);

	/* Create a new, empty, record */
	virtual void CreateNew (CEsmFile* pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString (const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType (void);

	/* Get class members */
	const TCHAR *GetDialogType (void) {
		return (GetESMDialogType(GetDialogTypeID()));
	}

	int GetDialogTypeID (void) {
		return (m_pData ? (int) * (m_pData->GetData()) : 0);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord (CEsmSubRecord* pSubRecord);

	/* Set class members */
	void SetDialogType (const int Type) {
		if (m_pData) {
			*(m_pData->GetData()) = (byte) Type;
		}
	}

};

/*===========================================================================
 *      End of Class CEsmDialogue Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmDialogue.H
 *=========================================================================*/
