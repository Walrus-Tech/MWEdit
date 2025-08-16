/*===========================================================================
 *
 * File:    EsmBodyPart.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMBODYPART_H
#define __ESMBODYPART_H


#include "EsmRecord.h"
#include "EsmSubBYDT.h"
#include "EsmSubName.h"


const TCHAR *GetESMBodyPart(const int Part);
const TCHAR *GetESMBodyPartType(const int PartType);
int GetESMBodyPart(const TCHAR *pString);
int GetESMBodyPartType(const TCHAR *pString);


/*===========================================================================
 *
 * Begin Class CEsmBodyPart Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmBodyPart : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubNameFix *m_pName; /* Reference to sub-records */
	CEsmSubNameFix *m_pModel;
	CEsmSubBYDT *m_pBodyData;


  public:
	/* Class Constructors/Destructors */
	CEsmBodyPart();
	//virtual ~CEsmBodyPart() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Body Part");
	}

	/* Get class members */
	bodypartdata_t *GetBodyData() {
		return m_pBodyData == NULL ? NULL : m_pBodyData->GetBodyData();
	}

	int GetBodyPartID() {
		return m_pBodyData == NULL ? -1 : m_pBodyData->GetPart();
	}

	int GetBodyTypeID() {
		return m_pBodyData == NULL ? -1 : m_pBodyData->GetPartType();
	}

	const TCHAR *GetBodyPart() {
		return GetESMBodyPart(GetBodyPartID());
	}

	const TCHAR *GetBodyPartType() {
		return GetESMBodyPartType(GetBodyTypeID());
	}

	const TCHAR *GetName() {
		return m_pName ? m_pName->GetName() : _T("");
	}

	const TCHAR *GetModel() {
		return m_pModel ? m_pModel->GetName() : _T("");
	}

	bool IsFemale() {
		return m_pBodyData == NULL ? false : m_pBodyData->IsFemale();
	}

	bool IsVampire() {
		return m_pBodyData == NULL ? false : m_pBodyData->IsVampire();
	}

	/* Get the playable state, but only if the part is the hair or head */
	bool IsPlayable() {
		if (GetBodyPartID() > MWESM_PART_HAIR) {
			return false;
		}

		return m_pBodyData->IsPlayable();
	}

	/* Return the race if the part type is skin, or empty string otherwise */
	const TCHAR *GetRace() {
		if (GetBodyTypeID() != MWESM_PARTTYPE_SKIN || m_pName == NULL) {
			return _T("");
		}

		return m_pName->GetName();
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class memebers */
	void SetModel(const TCHAR *pModel) {
		if (m_pModel) {
			m_pModel->SetName(pModel);
		}
	}

	void SetRace(const TCHAR *pRace) {
		if (m_pName) {
			m_pName->SetName(pRace);
		}
	}

	void SetFemale(const bool Flag) {
		if (m_pBodyData) {
			m_pBodyData->SetFemale(Flag);
		}
	}

	void SetPlayable(const bool Flag) {
		if (m_pBodyData) {
			m_pBodyData->SetPlayable(Flag);
		}
	}

	void SetBodyPart(const int Type) {
		if (m_pBodyData) {
			m_pBodyData->SetPart(Type);
		}
	}

	void SetBodyPartType(const int Type) {
		if (m_pBodyData) {
			m_pBodyData->SetPartType(Type);
		}
	}

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);
};


#endif
