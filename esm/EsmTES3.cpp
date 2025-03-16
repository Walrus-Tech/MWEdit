/*===========================================================================
 *
 * File:    EsmTES3.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "esmTES3.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmTES3.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmTES3::s_SubRecCreate[] = {
	{ MWESM_SUBREC_HEDR, CEsmSubHEDR::Create },
	{ MWESM_SUBREC_MAST, CEsmSubName::Create },
	{ MWESM_SUBREC_DATA, CEsmSubLong64::Create },
	{ NULL, CEsmSubRecord::Create } /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Constructor
 *
 *=========================================================================*/
CEsmTES3::CEsmTES3 () {
	//DEFINE_FUNCTION("CEsmTES3::CEsmTES3()");
	m_pHeader = NULL;
}

/*===========================================================================
 *      End of Class CEsmTES3 Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmTES3::Destroy (void) {
	//DEFINE_FUNCTION("CEsmTES3::Destroy()");
	/* Clear the references */
	m_pHeader = NULL;
	/* Call the base class method */
	CEsmRecord::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmTES3::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Method - void AddMaster (pFilename, FileSize);
 *
 *=========================================================================*/
void CEsmTES3::AddMaster(const TCHAR* pFilename, const long FileSize) {
	CEsmSubName* pName;
	CEsmSubLong64* pSize;
	pName = (CEsmSubName *) AllocateSubRecord(MWESM_SUBREC_MAST);
	pSize = (CEsmSubLong64 *) AllocateSubRecord(MWESM_SUBREC_DATA);
	pName->CreateNew();
	pSize->CreateNew();
	pName->SetName(pFilename);
	pSize->SetValue1(FileSize);
}

/*===========================================================================
 *      End of Class Method CEsmTES3::AddMaster()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmTES3::Create (void) {
	DEFINE_FUNCTION("CEsmTES3::Create()");
	CEsmRecord* pRecord;
	CreatePointer(pRecord, CEsmTES3);
	return (pRecord);
}

/*===========================================================================
 *      End of Class Method CEsmTES3::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmTES3::CreateNew (CEsmFile* pFile) {
	/* Call the base class record first */
	CEsmRecord::CreateNew(pFile);
	/* Create the item sub-records */
	AllocateSubRecord(MWESM_SUBREC_HEDR);
	m_pHeader->CreateNew();
}

/*===========================================================================
 *      End of Class Method CEsmTES3::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmTES3 Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmTES3::OnAddSubRecord (CEsmSubRecord* pSubRecord) {
	if (pSubRecord->IsType(MWESM_SUBREC_HEDR)) {
		m_pHeader = (CEsmSubHEDR *) pSubRecord;
	} else {
		CEsmRecord::OnAddSubRecord(pSubRecord);
	}
}

/*===========================================================================
 *      End of Class Event CEsmTES3::OnAddSubRecord()
 *=========================================================================*/

