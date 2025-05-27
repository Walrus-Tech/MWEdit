/*===========================================================================
 *
 * File:    EsmContainer.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmContainer.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmContainer.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmContainer::s_SubRecCreate[] = {
	{
		MWESM_SUBREC_NAME,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_FNAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_MODL,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ITEX,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SCRI,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ENAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_CNDT,
		CEsmSubCNDT::Create
	},
	{
		MWESM_SUBREC_FLAG,
		CEsmSubLong::Create
	},
	{
		MWESM_SUBREC_NPCO,
		CEsmSubNPCO::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Constructor
 *
 *=========================================================================*/
CEsmContainer::CEsmContainer() {
	//DEFINE_FUNCTION("CEsmContainer::CEsmContainer()");
	m_pContData = NULL;
	m_pFlag = NULL;
}

/*===========================================================================
 *      End of Class CEsmContainer Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmContainer::Destroy(void) {
	//DEFINE_FUNCTION("CEsmContainer::Destroy()");
	m_pContData = NULL;
	m_pFlag = NULL;
	CEsmItem1::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmContainer::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmContainer::CompareFields(const int FieldID, CEsmRecord *pRecord) {
	CEsmContainer *pCont;

	/* Ensure the correct type */
	if (!pRecord->IsType(MWESM_REC_CONT)) {
		return CEsmItem1::CompareFields(FieldID, pRecord);
	}

	pCont = (CEsmContainer *)pRecord;

	switch (FieldID) {
		case ESM_FIELD_WEIGHT:
			return (int)(GetWeight() * 100 - pCont->GetWeight() * 100);

		case ESM_FIELD_ORGANIC:
			return (int)IsOrganic() - (int)pCont->IsOrganic();

		case ESM_FIELD_RESPAWN:
			return (int)IsRespawn() - (int)pCont->IsRespawn();

		case ESM_FIELD_ITEMLIST:
			return (0);

		default:
			return CEsmItem1::CompareFields(FieldID, pRecord);
	}
}

/*===========================================================================
 *      End of Class Method   DEFINE_FUNCTION("CEsmArmor::CompareFields()");::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmContainer::Create(void) {
	DEFINE_FUNCTION("CEsmContainer::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmContainer);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmContainer::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmContainer::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem1::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_CNDT);
	AllocateSubRecord(MWESM_SUBREC_FLAG);
	m_pContData->CreateNew();
	m_pFlag->CreateNew();
	m_pFlag->SetFlag(MWESM_CONTFLAG_DEFAULT);
}

/*===========================================================================
 *      End of Class Method CEsmContainer::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmContainer Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR *CEsmContainer::GetFieldString(const int FieldID) {
	static TCHAR s_Buffer[32];

	switch (FieldID) {
		case ESM_FIELD_WEIGHT:
			snprintf(s_Buffer, 31, _T("%.2f"), GetWeight());
			return (s_Buffer);

		case ESM_FIELD_ORGANIC:
			return (BOOLTOYESNO(IsOrganic()));

		case ESM_FIELD_RESPAWN:
			return (BOOLTOYESNO(IsRespawn()));

		case ESM_FIELD_ITEMLIST:
			return ("");

		default:
			return CEsmItem1::GetFieldString(FieldID);
	}
}

/*===========================================================================
 *      End of Class Method TCHAR* CEsmContainer::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmContainer::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_CNDT)) {
		m_pContData = (CEsmSubCNDT *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_FLAG)) {
		m_pFlag = (CEsmSubLong *)pSubRecord;
	} else {
		CEsmItem1::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmContainer::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmContainer Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmContainer::SetFieldValue(const int FieldID, const TCHAR *pString) {
	switch (FieldID) {
		case ESM_FIELD_WEIGHT:
			SetWeight((float)atof(pString));
			return (true);

		case ESM_FIELD_ORGANIC:
			SetOrganic(StringToBoolean(pString));
			return (true);

		case ESM_FIELD_RESPAWN:
			SetRespawn(StringToBoolean(pString));
			return (true);
	};

	/* No matching field found */
	return CEsmItem1::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmContainer::SetFieldValue()
 *=========================================================================*/
