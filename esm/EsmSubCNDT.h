/*===========================================================================
 *
 * File:    EsmsubCNDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBCNDT_H
#define __ESMSUBCNDT_H


#pragma pack(push, 1)

typedef struct {
	float Weight;
} contdata_t;

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmSubCNDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCNDT : public CEsmSubRecord {
  public:
	/* Class Constructors/Destructors */
	//CEsmSubCNDT();
	//virtual ~CEsmSubCNDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCNDT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(contdata_t));
		m_RecordSize = sizeof(contdata_t);
		memset(m_pData, 0, sizeof(contdata_t));
	}

	/* Get class members */
	contdata_t *GetContData() {
		return (contdata_t *)m_pData;
	}

	float GetWeight() {
		return GetContData()->Weight;
	}

	/* Set class members */
	void SetWeight(const float Value) {
		GetContData()->Weight = Value;
	}
};


#endif
