/*===========================================================================
 *
 * File:    EsmsubSCHD.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSCHD_H
#define __ESMSUBSCHD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	char Name[MWESM_ID_MAXSIZE];
	long NumShorts;
	long NumLongs;
	long NumFloats;
	long ScriptDataSize;
	long LocalVarSize;
} scriptheaddata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubSCHD Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSCHD : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubSCHD();
	//virtual ~CEsmSubSCHD() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSCHD);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(scriptheaddata_t));
		m_RecordSize = sizeof(scriptheaddata_t);
		memset(m_pData, 0, sizeof(scriptheaddata_t));
	}

	/* Get class members */
	scriptheaddata_t *GetScriptHeadData(void) {
		return ((scriptheaddata_t *)m_pData);
	}

	const TCHAR *GetName(void) {
		return (GetScriptHeadData()->Name);
	}

	long GetNumShorts(void) {
		return (GetScriptHeadData()->NumShorts);
	}

	long GetNumLongs(void) {
		return (GetScriptHeadData()->NumLongs);
	}

	long GetNumFloats(void) {
		return (GetScriptHeadData()->NumFloats);
	}

	long GetScriptDataSize(void) {
		return (GetScriptHeadData()->ScriptDataSize);
	}

	long GetLocalVarSize(void) {
		return (GetScriptHeadData()->LocalVarSize);
	}

	/* Set class members */
	void SetName(const TCHAR *pString) {
		TSTRNCPY(GetScriptHeadData()->Name, pString, MWESM_ID_MAXSIZE);
	}

	void SetNumShorts(const long Value) {
		GetScriptHeadData()->NumShorts = Value;
	}

	void SetNumLongs(const long Value) {
		GetScriptHeadData()->NumLongs = Value;
	}

	void SetNumFloats(const long Value) {
		GetScriptHeadData()->NumFloats = Value;
	}

	void SetScriptDataSize(const long Value) {
		GetScriptHeadData()->ScriptDataSize = Value;
	}

	void SetLocalVarSize(const long Value) {
		GetScriptHeadData()->LocalVarSize = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
