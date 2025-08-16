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


#include "EsmOptionsDef.h"


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


class CEsmScriptOptions;
CEsmScriptOptions *GetEsmOptScriptOptions();


#endif
