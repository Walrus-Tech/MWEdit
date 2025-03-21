/*===========================================================================
 *
 * File:    NameList.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, May 29, 2001
 *
 * Routines for simple handling of name-value lists.
 *
 *=========================================================================*/
#ifndef __NAMELIST_H
#define __NAMELIST_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "dl_err.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Associate a short string with a long integer value */
typedef struct {
	long lValue;
	const TCHAR *pName;
} valuenames_t;

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Find a value associated with a name */
bool FindNameValue (long &lValue, const valuenames_t* pValueArray, const TCHAR* pName);
long FindNameValue (const valuenames_t* pValueArray, const TCHAR* pName);

/* Find a name associated with a value */
const TCHAR *FindValueName (const valuenames_t* pValueArray, const long lValue);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Namelist.H
 *=========================================================================*/
