/*===========================================================================
 *
 * File:    EsmSubFRMR.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBFRMR_H
#define __ESMSUBFRMR_H


#include "esm/EsmSubBase.h"


#pragma pack(push, 1)

typedef struct {
	int Index : 24;
	int Flag : 8;
} frmrdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubFRMR Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubFRMR : public CEsmSubRecord {
  protected:
	frmrdata_t m_Data;


	virtual bool ReadData(CGenFile &File) {
		return File.Read((char *)&m_Data, sizeof(frmrdata_t));
	}

	virtual bool WriteData(CGenFile &File) {
		return File.Write((char *)&m_Data, sizeof(frmrdata_t));
	}


  public:
	/* Class Constructors/Destructors */
	//CEsmSubFRMR();
	//virtual ~CEsmSubFRMR() { Destroy(); }
	//virtual void Destroy (void);

	/* Copy from another name record */
	virtual void Copy(CEsmSubRecord *pSubRecord) {
		m_Type.SetType(pSubRecord->GetType());
		m_RecordSize = pSubRecord->GetRecordSize();

		if (pSubRecord->IsType(MWESM_SUBREC_FRMR)) {
			m_Data.Index = ((CEsmSubFRMR *)pSubRecord)->GetIndex();
			m_Data.Flag = ((CEsmSubFRMR *)pSubRecord)->GetFlag();
		} else {
			m_Data.Index = 0;
			m_Data.Flag = 0;
		}
	}


	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubFRMR);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		m_RecordSize = sizeof(frmrdata_t);
		m_Data.Index = 0;
		m_Data.Flag = 0;
	}

	/* Finds text in the sub-record */
	virtual bool Find(esmfind_t &FindData) {
		return false;
	}

	/* Get/set the long value directly */
	long GetValue() {
		return (*(long *)&m_Data);
	}

	long GetIndex() {
		return m_Data.Index;
	}

	byte GetFlag() {
		return m_Data.Flag;
	}

	void SetValue(const long Value) {
		*(long *)&m_Data = Value;
	}

	void SetIndex(const long Index) {
		m_Data.Index = Index & 0x00FFFFFF;
	}

	void SetFlag(const byte Flag) {
		m_Data.Flag = Flag;
	}
};


#endif
