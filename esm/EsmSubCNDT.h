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
	float Weight;
} contdata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubCNDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCNDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubCNDT();
	//virtual ~CEsmSubCNDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create (void) {
		CEsmSubRecord* pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCNDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew (void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(contdata_t));
		m_RecordSize = sizeof(contdata_t);
		memset(m_pData, 0, sizeof(contdata_t));
	}

	/* Get class members */
	contdata_t *GetContData (void) {
		return ((contdata_t *) m_pData);
	}

	float GetWeight (void) {
		return (GetContData()->Weight);
	}

	/* Set class members */
	void SetWeight (const float Value) {
		GetContData()->Weight = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubCNDT Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Esmsubaodt.H
 *=========================================================================*/
