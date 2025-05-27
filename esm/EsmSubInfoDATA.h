/*===========================================================================
 *
 * File:    EsmSubInfoDATA.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBINFODATA_H
#define __ESMSUBINFODATA_H


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

/* Gender types */
#define MWESM_INFOGENDER_NONE     -1
#define MWESM_INFOGENDER_MALE      0
#define MWESM_INFOGENDER_FEMALE    1

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
	long Unknown1;
	long Disposition;
	char Rank;
	char Gender;
	char PCRank;
	char Unknown2;
} infodata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubInfoDATA Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubInfoDATA : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubInfoDATA();
	//virtual ~CEsmSubInfoDATA() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubInfoDATA);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(infodata_t));
		m_RecordSize = sizeof(infodata_t);
		memset(m_pData, 0, sizeof(infodata_t));
		GetInfoData()->Rank = -1;
		GetInfoData()->PCRank = -1;
		GetInfoData()->Gender = (char) MWESM_INFOGENDER_NONE;
	}

	/* Get class members */
	infodata_t *GetInfoData(void) {
		return ((infodata_t *)m_pData);
	}

	long GetUnknown1(void) {
		return (GetInfoData()->Unknown1);
	}

	char GetUnknown2(void) {
		return (GetInfoData()->Unknown2);
	}

	long GetDisposition(void) {
		return (GetInfoData()->Disposition);
	}

	char GetRank(void) {
		return (GetInfoData()->Rank);
	}

	char GetPCRank(void) {
		return (GetInfoData()->PCRank);
	}

	char GetGender(void) {
		return (GetInfoData()->Gender);
	}

	bool IsFemale(void) {
		return (GetGender() == MWESM_INFOGENDER_FEMALE);
	}

	bool IsMale(void) {
		return (GetGender() == MWESM_INFOGENDER_MALE);
	}

	bool IsNoGender(void) {
		return (GetGender() == MWESM_INFOGENDER_NONE);
	}

	/* Set class members */
	void SetUnknown1(const long Value) {
		GetInfoData()->Unknown1 = Value;
	}

	void SetUnknown2(const char Value) {
		GetInfoData()->Unknown2 = Value;
	}

	void SetDisposition(const long Value) {
		GetInfoData()->Disposition = Value;
	}

	void SetRank(const char Value) {
		GetInfoData()->Rank = Value;
	}

	void SetPCRank(const char Value) {
		GetInfoData()->PCRank = Value;
	}

	void SetGender(const char Value) {
		GetInfoData()->Gender = Value;
	}

	void SetFemale(void) {
		SetGender(MWESM_INFOGENDER_FEMALE);
	}

	void SetMale(void) {
		SetGender(MWESM_INFOGENDER_MALE);
	}

	void SetNoGender(void) {
		SetGender(MWESM_INFOGENDER_NONE);
	}

};

/*===========================================================================
 *      End of Class CEsmSubAADT CEsmSubInfoDATA
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubDATA.H
 *=========================================================================*/
