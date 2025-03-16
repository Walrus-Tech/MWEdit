/*===========================================================================
 *
 * File:    Objarray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, December 31, 2003
 *
 * Contains test procedures for the TObjArray template.
 *
 *=========================================================================*/

/* Include Files */
#include "objarray.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("ObjArray.cpp");

/* Sample fixed string structure */
struct fixedstring {
	char String[64];
};

/* Test arrays */
TObjArray<long> m_LongArray;
TObjArray<fixedstring> m_StringArray;

/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/
