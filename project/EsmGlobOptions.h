/*===========================================================================
 *
 * File:    Esmgloboptions.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 7, 2003
 *
 * Defines the functions for accessing the various MWEdit options.
 *

 *=========================================================================*/

#ifndef __ESMGLOBOPTIONS_H
#define __ESMGLOBOPTIONS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/

#include "EsmOptionsDef.h"

/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

bool GetEsmOptNoScriptFormat();
bool GetEsmOptBackupSaves();
bool GetEsmOptNoScriptPrompt();
bool GetEsmOptAllowExtFuncs();
bool GetEsmOptUseExtraFile();
bool GetEsmOptStrictIDs();
bool GetEsmOptInitialIndentLevel();
bool GetEsmOptIndentCommentsMore();
bool GetEsmOptAllowBloodmoon();
bool GetEsmOptAllowTribunal();

int GetEsmOptScriptWarnLevel();
int GetEsmOptScriptFormatType();

const TCHAR *GetEsmOptDefaultAuthor();
const TCHAR *GetEsmOptExtraFile();
const TCHAR *GetEsmOptScriptIndentString();

/* Forward definition */

class CEsmScriptOptions;
CEsmScriptOptions *GetEsmOptScriptOptions();

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif

/*===========================================================================
 *      End of File Esmgloboptions.H
 *=========================================================================*/
