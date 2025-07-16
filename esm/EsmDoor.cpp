/*===========================================================================
 *
 * File:    EsmDoor.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmDoor.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmDoor.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


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
 *      End of Sub-Record Create Array
 *=========================================================================*/


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
 *      End of Class CEsmDoor Constructor
 *=========================================================================*/


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
 *      End of Class Method CEsmDoor::Destroy()
 *=========================================================================*/


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
 *      End of Class Method CEsmDoor::Create()
 *=========================================================================*/


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
 *      End of Class Method CEsmDoor::CreateNew()
 *=========================================================================*/


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

/*===========================================================================
 *      End of Class Event CEsmDoor::OnAddSubRecord()
 *=========================================================================*/
