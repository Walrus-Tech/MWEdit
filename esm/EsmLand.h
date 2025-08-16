/*===========================================================================
 *
 * File:    EsmLand.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 28, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMLAND_H
#define __ESMLAND_H


#include "EsmRecord.h"
#include "EsmSubLong.h"
#include "EsmSubLong64.h"


/* Default grid array size */
#define MWESM_LAND_VERTEXSIZE  65
#define MWESM_LAND_WNAMSIZE    9
#define MWESM_LAND_VTEXSIZE    16

/*  Default record data */
#define MWESM_LAND_DEFAULTDATA 9


#pragma pack(push, 1)

struct mwesm_vnmlpoint_t {
	char X;
	char Y;
	char Z;
};

/* Vertex normal data */
struct mwesm_vnmldata_t {
	mwesm_vnmlpoint_t Normals[MWESM_LAND_VERTEXSIZE][MWESM_LAND_VERTEXSIZE];
};

/* Vertex height data */
struct mwesm_vhgtdata_t {
	float Offset;
	byte Unknown1;
	char HeightData[MWESM_LAND_VERTEXSIZE][MWESM_LAND_VERTEXSIZE];
	short Unknown2;
};

/* WNAM data */
struct mwesm_wnamdata_t {
	char Data[MWESM_LAND_WNAMSIZE][MWESM_LAND_WNAMSIZE];
};

/* Vertex color data */
typedef mwesm_vnmldata_t mwesm_vclrdata_t;

/* Vertex texture data */
struct mwesm_vtexdata_t {
	short Textures[MWESM_LAND_VTEXSIZE][MWESM_LAND_VTEXSIZE];
};

#pragma pack(pop)


/*===========================================================================
 *
 * Begin Class CEsmLand Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmLand : public CEsmRecord {
	DECLARE_SUBRECCREATE();

  protected:
	CEsmSubLong64 *m_pLocation;
	CEsmSubLong *m_pData;
	CEsmSubRecord *m_pNormalData;
	CEsmSubRecord *m_pHeightData;
	CEsmSubRecord *m_pWNAMData;
	CEsmSubRecord *m_pColorData;
	CEsmSubRecord *m_pTextureData;


  public:
	/* Class Constructors/Destructors */
	CEsmLand();
	//virtual ~CEsmLand() { Destroy(); }
	virtual void Destroy();

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Return a new record object */
	static CEsmRecord *Create();

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Get class members */
	long GetCellX() const {
		return m_pLocation == NULL ? 0 : m_pLocation->GetValue1();
	}

	long GetCellY() const {
		return m_pLocation == NULL ? 0 : m_pLocation->GetValue2();
	}

	long GetData() const {
		return m_pData == NULL ? 0 : m_pData->GetValue();
	}

	/* Access the sub-record data */
	mwesm_vnmldata_t *GetNormalData() {
		return m_pNormalData == NULL ? NULL : (mwesm_vnmldata_t *)m_pNormalData->GetData();
	}

	mwesm_vhgtdata_t *GetHeightData() {
		return m_pHeightData == NULL ? NULL : (mwesm_vhgtdata_t *)m_pHeightData->GetData();
	}

	mwesm_wnamdata_t *GetWNAMData() {
		return m_pWNAMData == NULL ? NULL : (mwesm_wnamdata_t *)m_pWNAMData->GetData();
	}

	mwesm_vclrdata_t *GetColorData() {
		return m_pColorData == NULL ? NULL : (mwesm_vclrdata_t *)m_pColorData->GetData();
	}

	mwesm_vtexdata_t *GetTextureData() {
		return m_pTextureData == NULL ? NULL : (mwesm_vtexdata_t *)m_pTextureData->GetData();
	}

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType() {
		return _T("Land");
	}

	/* Check if the given record is the same as this one */
	virtual bool IsSame(CEsmRecord *pRecord);

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class members */
	void SetCellX(const long Value) {
		if (m_pLocation != NULL) {
			m_pLocation->SetValue1(Value);
		}
	}

	void SetCellY(const long Value) {
		if (m_pLocation != NULL) {
			m_pLocation->SetValue2(Value);
		}
	}

	void SetData(const long Value) {
		if (m_pData != NULL) {
			m_pData->SetValue(Value);
		}
	}
};


#endif
