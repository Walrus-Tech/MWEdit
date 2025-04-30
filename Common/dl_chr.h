/*===========================================================================
 *
 * File:    DL_Chr.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Sunday, May 06, 2001
 *
 * Contains definitions for TCHARacter related functions of Dave's Library
 * of common code.
 *
 *=========================================================================*/
#ifndef __DL_CHR_H
#define __DL_CHR_H

/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_mem.h"
#include "dl_err.h"
#include "dl_log.h"
#include <string.h>

#if defined(_WIN32)
	#include "tchar.h"
#endif

/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Insert a TCHARacter somewhere in a string */
void chradd(TCHAR *pString, const size_t TCHARIndex, const TCHAR NewTCHAR);

/* Add a TCHARacter to the end of a string */
void chrcat(TCHAR *pString, const TCHAR NewTCHAR);

/* Count the number of TCHARacters in the string */
int chrcount(const TCHAR *pString, const TCHAR TCHAR);

/* Delete a TCHARacter from a string */
void chrdel(TCHAR *pString, const size_t TCHARIndex);

/* Delete the last TCHARacter from the string */
void chrdellast(TCHAR *pString);

/* Reverse search for last punctuation TCHARacter in string */
boolean chrrpunc(size_t &TCHARIndex, const TCHAR *pString);

/* Divide string into substrings seperated by token TCHARacter */
TCHAR *chrtok(TCHAR *pString, const TCHAR TokenTCHAR);

/* Truncate a string at first/last occurence of TCHARacter */
TCHAR *chrtrunc(TCHAR *pString, const TCHAR TruncateTCHAR);
TCHAR *chrrtrunc(TCHAR *pString, const TCHAR TruncateTCHAR);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Testing Routine Prototypes
 *
 * Prototypes for test functions of module.  Only available in DEBUG builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)
	void Test_chradd(void);
	void Test_chrcat(void);
	void Test_chrdel(void);
	void Test_chrdellast(void);
	void Test_chrtok(void);
	void Test_chrrpunc(void);
	void Test_chrtrunc(void);
	void Test_chrrtrunc(void);
	void Test_DLChr(void);
#endif
/*===========================================================================
 *      End of Testing Routine Prototypes
 *=========================================================================*/

#endif
/*===========================================================================
 *      End of File DL_Chr.H
 *=========================================================================*/
