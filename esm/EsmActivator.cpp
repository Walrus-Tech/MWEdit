/*===========================================================================
 *
 * File:    EsmActivator.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "EsmActivator.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmActivator.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmActivator::s_SubRecCreate[] = {
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
		NULL,
		CEsmSubRecord::Create
	} /* Must be last record */
};
/*===========================================================================
 *      End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmActivator Constructor
 *
 *=========================================================================*/
CEsmActivator::CEsmActivator() {
	//DEFINE_FUNCTION("CEsmActivator::CEsmActivator()");
}

/*===========================================================================
 *      End of Class CEsmActivator Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmActivator Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmActivator::Destroy() {
	//DEFINE_FUNCTION("CEsmActivator::Destroy()");
	CEsmItem1::Destroy();
}

/*===========================================================================
 *      End of Class Method CEsmActivator::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmActivator Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord *CEsmActivator::Create() {
	DEFINE_FUNCTION("CEsmActivator::Create()");
	CEsmRecord *pRecord;
	CreatePointer(pRecord, CEsmActivator);
	return pRecord;
}

/*===========================================================================
 *      End of Class Method CEsmActivator::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmActivator Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmActivator::SetFieldValue(const int FieldID, const TCHAR *pString) {
	return CEsmItem1::SetFieldValue(FieldID, pString);
}

/*===========================================================================
 *      End of Class Method CEsmActivator::SetFieldValue()
 *=========================================================================*/
