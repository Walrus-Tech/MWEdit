/*===========================================================================
 *
 * File:    EsmSoundGen.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSOUNDGEN_H
#define __ESMSOUNDGEN_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmRecord.h"
#include "EsmSubName.h"
#include "EsmSubNameFix.h"
#include "EsmSubLong.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* SoundGen types */
#define MWESM_SNDGEN_MIN          0
#define MWESM_SNDGEN_LEFTFOOT     0
#define MWESM_SNDGEN_RIGHTFOOT    1
#define MWESM_SNDGEN_SWIMLEFT     2
#define MWESM_SNDGEN_SWIMRIGHT    3
#define MWESM_SNDGEN_MOAN         4
#define MWESM_SNDGEN_ROAR         5
#define MWESM_SNDGEN_SCREAM       6
#define MWESM_SNDGEN_LAND         7
#define MWESM_SNDGEN_MAX          7

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
const TCHAR *GetESMSoundGenType(const int Type);
int GetESMSoundGenType(const TCHAR *pString);
/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSoundGen Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSoundGen : public CEsmRecord {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubLong *m_pTypeData;
	CEsmSubNameFix *m_pSoundName;
	CEsmSubNameFix *m_pCreatureName;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSoundGen();
	//virtual ~CEsmSoundGen() { Destroy(); }
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
		return _T("Sound Gen");
	}

	/* Get class members */
	const TCHAR *GetSound(void) {
		return (m_pSoundName ? m_pSoundName->GetName() : _T(""));
	}

	const TCHAR *GetCreature(void) {
		return (m_pCreatureName ? m_pCreatureName->GetName() : _T(""));
	}

	long GetSoundType(void) {
		return (m_pTypeData ? m_pTypeData->GetValue() : 0);
	}

	const TCHAR *GetTypeString(void) {
		return GetESMSoundGenType(GetSoundType());
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetSound(const TCHAR *pString) {
		if (m_pSoundName) {
			m_pSoundName->SetName(pString);
		}
	}

	void SetCreature(const TCHAR *pString);
	void SetSoundType(const int Type) {
		if (m_pTypeData) {
			m_pTypeData->SetValue(Type);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmSoundGen Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmBodyPart.H
 *=========================================================================*/
