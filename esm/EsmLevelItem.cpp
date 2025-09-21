/*===========================================================================
 *
 * File:    EsmLevelItem.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

#include "EsmLevelItem.h"


DEFINE_FILE("EsmLevelItem.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmLevelItem::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_DATA,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_NNAM,
		CEsmSubByte::Create
	},
	{
		MWESM_SUBREC_INAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_INTV,
		CEsmSubShort::Create
	},
	{
		MWESM_SUBREC_INDX,
		CEsmSubLong::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmLevelItem Constructor
 *
 *=========================================================================*/
CEsmLevelItem::CEsmLevelItem() {
	//DEFINE_FUNCTION("CEsmLevelItem::CEsmLevelItem()");
	m_pID = NULL;
	m_pData = NULL;
	m_pNNam = NULL;
	m_pIndex = NULL;
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmLevelItem::Destroy() {
	//DEFINE_FUNCTION("CEsmLevelItem::Destroy()");
	m_pID = NULL;
	m_pData = NULL;
	m_pNNam = NULL;
	m_pIndex = NULL;
	CEsmRecord::Destroy();
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - void AddItem (pID, Value);
 *
 * Adds an item to the levelled list.
 *
 *=========================================================================*/
void CEsmLevelItem::AddItem(const TCHAR *pID, const int Value) {
	CEsmSubNameFix *pName;
	CEsmSubShort *pValue;

	/* Allocate the new subrecords */
	pName = (CEsmSubNameFix *)AllocateSubRecord(MWESM_SUBREC_INAM);
	pName->CreateNew();
	pValue = (CEsmSubShort *)AllocateSubRecord(MWESM_SUBREC_INTV);
	pValue->CreateNew();

	/* Set the values */
	pName->SetName(pID);
	pValue->SetValue((short)Value);

	/* Increase the size member */
	SetListSize(GetListSize() + 1);
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmLevelItem::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmLevelItem *pLevelItem;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_LEVI)) {
		return CEsmRecord::CompareFields(FieldID, pRecord);
	}

	pLevelItem = (CEsmLevelItem *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_ID:
			return StringCompare(GetID(), pLevelItem->GetID(), false);

		case ESM_FIELD_ALLPC:
			return (int)IsAllPC() - (int)pLevelItem->IsAllPC();

		case ESM_FIELD_CALCEACH:
			return (int)IsCalcEach() - (int)pLevelItem->IsCalcEach();

		case ESM_FIELD_LIST:
			return 0;

		case ESM_FIELD_CHANCENONE:
			return GetChanceNone() - pLevelItem->GetChanceNone();

		default:
			return CEsmRecord::CompareFields(FieldID, pRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmLevelItem::Create() {
	DEFINE_FUNCTION("CEsmLevelItem::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmLevelItem);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmLevelItem::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);

	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_DATA);
	AllocateSubRecord(MWESM_SUBREC_NNAM);
	AllocateSubRecord(MWESM_SUBREC_INDX);

	m_pIndex->CreateNew();
	m_pData->CreateNew();
	m_pNNam->CreateNew();
}


/*===========================================================================
 *
 * Class TCHAR* CEsmLevelItem Method - const TCHAR* GetItemListString (void);
 *
 * Uses a local static buffer to create a list of the current items
 * in the levelled list (up to 256 bytes).
 *
 *=========================================================================*/
const TCHAR *CEsmLevelItem::GetItemListString() {
	static TCHAR s_Buffer[256];
	TCHAR TempBuffer[32];
	CEsmSubNameFix *pNameSubRec;
	CEsmSubRecord *pLevelSubRec;
	int ArrayIndex;
	int BufferLength;
	int StringLength;
	pNameSubRec = (CEsmSubNameFix *)FindFirst(MWESM_SUBREC_INAM, ArrayIndex);
	s_Buffer[0] = NULL_CHAR;
	BufferLength = 0;

	while (pNameSubRec != NULL) {
		pLevelSubRec = GetSubRecord(ArrayIndex + 1);

		if (pLevelSubRec->IsType(MWESM_SUBREC_INTV)) {
			StringLength = TSTRLEN(pNameSubRec->GetName());

			if (StringLength + BufferLength > 255) {
				break;
			}

			TSTRCPY(s_Buffer + BufferLength, pNameSubRec->GetName());
			BufferLength += StringLength;
			snprintf(TempBuffer,
			         31,
			         _T(" (%d),   "),
			         (int)((CEsmSubShort *)pLevelSubRec)->GetValue());
			StringLength = TSTRLEN(TempBuffer);

			if (StringLength + BufferLength > 255) {
				break;
			}

			TSTRCPY(s_Buffer + BufferLength, TempBuffer);
			BufferLength += StringLength;
		}

		pNameSubRec = (CEsmSubNameFix *)FindNext(MWESM_SUBREC_INAM, ArrayIndex);
	}

	return s_Buffer;
}


/*===========================================================================
 *
 * Class TCHAR* CEsmLevelItem Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmLevelItem::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_ID:
			return GetID();

		case ESM_FIELD_ALLPC:
			return BOOLTOYESNO(IsAllPC());

		case ESM_FIELD_LIST:
			return GetItemListString();

		case ESM_FIELD_CHANCENONE:
			snprintf(s_Buffer, 31, _T("%d"), GetChanceNone());
			return s_Buffer;

		case ESM_FIELD_CALCEACH:
			return BOOLTOYESNO(IsCalcEach());

		default:
			return CEsmRecord::GetFieldString(FieldID);
	}
}


/*===========================================================================
 *
 * Class CEsmLevelItem Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmLevelItem::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_NAME)) {
		m_pID = (CEsmSubName *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_DATA)) {
		m_pData = (CEsmSubLong *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_NNAM)) {
		m_pNNam = (CEsmSubByte *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_INDX)) {
		m_pIndex = (CEsmSubLong *)pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}


/*===========================================================================
 *
 * Class CEsmLevelItem Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmLevelItem::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_ALLPC:
			SetAllPC(StringToBoolean(pString));
			return true;

		case ESM_FIELD_CHANCENONE:
			SetChanceNone(atoi(pString));
			return true;

		case ESM_FIELD_CALCEACH:
			SetCalcEach(StringToBoolean(pString));
			return true;
	}

	/* No matching field found */
	return CEsmRecord::SetFieldValue(FieldID, pString);
}
