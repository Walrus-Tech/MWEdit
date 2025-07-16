/*===========================================================================
 *
 * File:    EsmsubSCVR.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBSCVR_H
#define __ESMSUBSCVR_H


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

/* Base size without the optional string */
#define MWESM_SCVR_BASESIZE           5
#define MWESM_SCVR_IDSIZE             63

/* Index values */
#define MWESM_SCVR_INDEX0             ((byte)'0')
#define MWESM_SCVR_INDEX1             ((byte)'1')
#define MWESM_SCVR_INDEX2             ((byte)'2')
#define MWESM_SCVR_INDEX3             ((byte)'3')
#define MWESM_SCVR_INDEX4             ((byte)'4')
#define MWESM_SCVR_INDEX5             ((byte)'5')

/* Function type */
#define MWESM_SCVRFUNC_NONE           ((byte)'0')
#define MWESM_SCVRFUNC_FUNCTION       ((byte)'1')
#define MWESM_SCVRFUNC_GLOBAL         ((byte)'2')
#define MWESM_SCVRFUNC_LOCAL          ((byte)'3')
#define MWESM_SCVRFUNC_JOURNAL        ((byte)'4')
#define MWESM_SCVRFUNC_ITEM           ((byte)'5')
#define MWESM_SCVRFUNC_DEAD           ((byte)'6')
#define MWESM_SCVRFUNC_NOTID          ((byte)'7')
#define MWESM_SCVRFUNC_NOTFACTION     ((byte)'8')
#define MWESM_SCVRFUNC_NOTCLASS       ((byte)'9')
#define MWESM_SCVRFUNC_NOTRACE        ((byte)'A')
#define MWESM_SCVRFUNC_NOTCELL        ((byte)'B')
#define MWESM_SCVRFUNC_NOTLOCAL       ((byte)'C')

/* Function type codes */
#define MWESM_SCVRFUNCCODE_VARIABLE   (*(short *)"sX")
#define MWESM_SCVRFUNCCODE_JOURNAL    (*(short *)"JX")
#define MWESM_SCVRFUNCCODE_ITEM       (*(short *)"IX")
#define MWESM_SCVRFUNCCODE_DEAD       (*(short *)"DX")
#define MWESM_SCVRFUNCCODE_NOTID      (*(short *)"XX")
#define MWESM_SCVRFUNCCODE_NOTFACTION (*(short *)"FX")
#define MWESM_SCVRFUNCCODE_NOTCLASS   (*(short *)"CX")
#define MWESM_SCVRFUNCCODE_NOTRACE    (*(short *)"RX")
#define MWESM_SCVRFUNCCODE_NOTCELL    (*(short *)"LX")

/* Compare operators */
#define MWESM_SCVROP_EQUALS           ((byte)'0')
#define MWESM_SCVROP_NOEQUALS         ((byte)'1')
#define MWESM_SCVROP_GREATER          ((byte)'2')
#define MWESM_SCVROP_GREATEREQUALS    ((byte)'3')
#define MWESM_SCVROP_LESSER           ((byte)'4')
#define MWESM_SCVROP_LESSEREQUALS     ((byte)'5')

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
	byte Index;
	byte Type;
	short Function;
	byte CompareOp;
	char Name[MWESM_SCVR_IDSIZE + 1]; /* Optional */
} infofuncdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubSCVR Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubSCVR : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	infofuncdata_t m_FuncData;
	int m_StringLength;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input methods */
	virtual bool ReadData(CGenFile &File);
	virtual bool WriteData(CGenFile &File);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmSubSCVR() {
		m_StringLength = 0;
	}

	//virtual ~CEsmSubSCVR() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubSCVR);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(infofuncdata_t));
		m_RecordSize = sizeof(infofuncdata_t);
		memset(m_pData, 0, sizeof(infofuncdata_t));
		m_StringLength = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData);

	/* Get class methods */
	infofuncdata_t *GetInfoFuncData() {
		return &m_FuncData;
	}

	const TCHAR *GetName() {
		return m_FuncData.Name;
	}

	int GetNameLength() {
		return m_StringLength;
	}

	virtual long GetRecordSize() const {
		return MWESM_SCVR_BASESIZE + m_StringLength;
	}

	byte GetFuncIndex() {
		return GetInfoFuncData()->Index;
	}

	byte GetFuncType() {
		return GetInfoFuncData()->Type;
	}

	short GetFunction() {
		return GetInfoFuncData()->Function;
	}

	byte GetCompareOp() {
		return GetInfoFuncData()->CompareOp;
	}

	const char *GetFuncName() {
		return GetInfoFuncData()->Name;
	}

	/* Checks if the sub-record uses the given ID */
	virtual bool IsUsed(const TCHAR *pID);

	/* Set class methods */
	void SetName(const TCHAR *pString);
	void SetFuncName(const TCHAR *pString) {
		TSTRNCPY(GetInfoFuncData()->Name, pString, MWESM_SCVR_IDSIZE + 1);
	}

	void SetFuncIndex(const byte Value) {
		GetInfoFuncData()->Index = Value;
	}

	void SetFuncType(const byte Value) {
		GetInfoFuncData()->Type = Value;
	}

	void SetFunction(const short Value) {
		GetInfoFuncData()->Function = Value;
	}

	void SetCompareOp(const byte Value) {
		GetInfoFuncData()->CompareOp = Value;
	}
};

/*===========================================================================
 *      End of Class CEsmSubAADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubINDX.H
 *=========================================================================*/
