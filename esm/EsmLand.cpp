/*===========================================================================
 *
 * File:    EsmLand.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 28, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmLand.h"

/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmLand.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmLand::s_SubRecCreate[] = {
	{ MWESM_SUBREC_INTV, CEsmSubLong64::Create },
	{ MWESM_SUBREC_DATA, CEsmSubLong::Create },
	{ MWESM_SUBREC_VNML, CEsmSubRecord::Create },
	{ MWESM_SUBREC_VHGT, CEsmSubRecord::Create },
	{ MWESM_SUBREC_WNAM, CEsmSubRecord::Create },
	{ MWESM_SUBREC_VCLR, CEsmSubRecord::Create },
	{ MWESM_SUBREC_VTEX, CEsmSubRecord::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Constructor
 *
 *=========================================================================*/
CEsmLand::CEsmLand () {
	//DEFINE_FUNCTION("CEsmLand::CEsmLand()");
	m_pData = NULL;
	m_pLocation = NULL;
	m_pNormalData = NULL;
	m_pHeightData = NULL;
	m_pWNAMData = NULL;
	m_pColorData = NULL;
	m_pTextureData = NULL;
}

/*===========================================================================
 *      End of Class CEsmLand Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmLand::Destroy (void) {
	//DEFINE_FUNCTION("CEsmLand::Destroy()");
	m_pData = NULL;
	m_pLocation = NULL;
	m_pNormalData = NULL;
	m_pHeightData = NULL;
	m_pWNAMData = NULL;
	m_pColorData = NULL;
	m_pTextureData = NULL;
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmLand::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmLand::CompareFields (const int FieldID, CEsmRecord* pRecord) {
	CEsmLand* pLand;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_LAND)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pLand = (CEsmLand *) pRecord;

	switch (FieldID) {
		case ESM_FIELD_DATA:
			return (GetData() - pLand->GetData());

		case ESM_FIELD_CELLX:
			return (GetCellX() - pLand->GetCellX());

		case ESM_FIELD_CELLY:
			return (GetCellY() - pLand->GetCellY());

		case ESM_FIELD_CELL:
		case ESM_FIELD_GRID:
			return (GetCellX() * 100 - pLand->GetCellX() * 100 + GetCellY() - pLand->GetCellY());

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method CEsmLand::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmLand::Create (void) {
	DEFINE_FUNCTION("CEsmLand::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmLand);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmLand::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmLand::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the required sub-records */
	AllocateSubRecord(MWESM_SUBREC_INTV);
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_VNML);
	AllocateSubRecord(MWESM_SUBREC_VHGT);
	AllocateSubRecord(MWESM_SUBREC_WNAM);
	/* Initialize the new sub-records */
	m_pLocation->CreateNew();
	m_pData->CreateNew();
	m_pNormalData->CreateNew(sizeof(mwesm_vnmldata_t));
	m_pHeightData->CreateNew(sizeof(mwesm_vhgtdata_t));
	m_pWNAMData->CreateNew(sizeof(mwesm_wnamdata_t));
	/* Set the default data for some fields */
	SetCellX(0);
	SetCellY(0);
	SetData(MWESM_LAND_DEFAULTDATA);
	GetHeightData()->Offset = -256.0f;
	GetHeightData()->Unknown1 = 0;
	GetHeightData()->Unknown2 = 0;
}

/*===========================================================================
 *      End of Class Method CEsmLand::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmLand Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmLand::GetFieldString (const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_CELLX:
			snprintf (s_Buffer, 31, _T("%ld"), GetCellX());
			return s_Buffer;

		case ESM_FIELD_CELLY:
			snprintf (s_Buffer, 31, _T("%ld"), GetCellY());
			return s_Buffer;

		case ESM_FIELD_CELL:
		case ESM_FIELD_GRID:
			snprintf (s_Buffer, 31, _T("%ld, %ld"), GetCellX(), GetCellY());
			return s_Buffer;

		case ESM_FIELD_DATA:
			snprintf (s_Buffer, 31, _T("%ld"), GetData());
			return s_Buffer;

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmLand::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Method - bool IsSame (pRecord);
 *
 * Checks if the input record is the same LAND as the current record.
 * The grid/cell location is checked.
 *
 *=========================================================================*/
bool CEsmLand::IsSame (CEsmRecord* pRecord) {
	/* Check types */
	if (!pRecord->IsType(MWESM_REC_LAND)) {
		return (false);
	}

	CEsmLand* pLand = (CEsmLand *) pRecord;

	/* Check the grid location otherwise */
	if (GetCellX() == pLand->GetCellX() && GetCellY() == pLand->GetCellY()) {
		return (true);
	}

	return (false);
}

/*===========================================================================
 *      End of Class Method CEsmLand::IsSame()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmLand Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmLand::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = (CEsmSubLong *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_INTV)) {
		m_pLocation = (CEsmSubLong64 *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_VNML)) {
		m_pNormalData = (CEsmSubRecord *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_VHGT)) {
		m_pHeightData = (CEsmSubRecord *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_WNAM)) {
		m_pWNAMData = (CEsmSubRecord *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_VCLR)) {
		m_pColorData = (CEsmSubRecord *) pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_VTEX)) {
		m_pTextureData = (CEsmSubRecord *) pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmLand::OnAddSubRecord()
 *=========================================================================*/


