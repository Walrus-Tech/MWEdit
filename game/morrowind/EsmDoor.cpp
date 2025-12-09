/*===========================================================================
 *
 * File:    EsmDoor.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "esm/EsmDoor.h"


DEFINE_FILE("EsmDoor.cpp");


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmDoor::s_SubRecCreate[] = {
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
		MWESM_SUBREC_SCRI,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_ANAM,
		CEsmSubNameFix::Create
	},
	{
		MWESM_SUBREC_SNAM,
		CEsmSubNameFix::Create
	},
	{
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};


/*===========================================================================
 *
 * Class CEsmDoor Constructor
 *
 *=========================================================================*/
CEsmDoor::CEsmDoor() {
	//DEFINE_FUNCTION("CEsmDoor::CEsmDoor()");
	m_pCloseSound = NULL;
	m_pOpenSound = NULL;
}


/*===========================================================================
 *
 * Class CEsmDoor Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmDoor::Destroy() {
	//DEFINE_FUNCTION("CEsmDoor::Destroy()");
	m_pCloseSound = NULL;
	m_pOpenSound = NULL;
	CEsmItem1::Destroy();
}


/*===========================================================================
 *
 * Class CEsmDoor Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmDoor::Create() {
	DEFINE_FUNCTION("CEsmDoor::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmDoor);
	return pRecord;
}


/*===========================================================================
 *
 * Class CEsmDoor Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmDoor::CreateNew(CEsmFile *pFile) {
	/* Call the base class record first */
	CEsmItem1::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_SNAM);
	AllocateSubRecord(MWESM_SUBREC_ANAM);
}


/*===========================================================================
 *
 * Class CEsmDoor Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmDoor::OnAddSubRecord(CEsmSubRecord *pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_SNAM)) {
		m_pOpenSound = (CEsmSubNameFix *)pSubRecord;
	} else if (pSubRecord->IsType(MWESM_SUBREC_ANAM)) {
		m_pCloseSound = (CEsmSubNameFix *)pSubRecord;
	} else {
		CEsmItem1::OnAddSubRecord(pSubRecord);
	}
}
