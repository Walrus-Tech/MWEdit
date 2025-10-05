/*===========================================================================
 *
 * File:    Esmgloboptions.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 7, 2003
 *
 * Implements the global functions for accessing and returning the
 * various MWEdit options.
 *
 *=========================================================================*/
#include "project/StdAfx.h"
#include "project/EsmGlobOptions.h"
#include "project/EsmOptions.h"
#include "project/MWEdit.h"


DEFINE_FILE("EsmGlobOptions.cpp");


/*===========================================================================
 *
 * Function - bool GetEsmOptAllowBloodmoon (void);
 *
 *=========================================================================*/
bool GetEsmOptAllowBloodmoon() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetAllowBloodmoon();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptAllowTribunal (void);
 *
 *=========================================================================*/
bool GetEsmOptAllowTribunal() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetAllowTribunal();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptNoScriptFormat (void);
 *
 * Returns the current no-script-format options flag.
 *
 *=========================================================================*/
bool GetEsmOptNoScriptFormat() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetNoScriptFormat();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptBackupSaves (void);
 *
 *=========================================================================*/
bool GetEsmOptBackupSaves() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetBackupSaves();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptStrictIDs (void);
 *
 *=========================================================================*/
bool GetEsmOptStrictIDs() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetStrictIDs();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptInitialIndentLevel (void);
 *
 *=========================================================================*/
bool GetEsmOptInitialIndentLevel() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetInitialIndentLevel();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptIndentCommentsMore (void);
 *
 *=========================================================================*/
bool GetEsmOptIndentCommentsMore() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetIndentCommentsMore();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptNoScriptPrompt (void);
 *
 *=========================================================================*/
bool GetEsmOptNoScriptPrompt() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetNoScriptPrompt();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptUseExtraFile (void);
 *
 *=========================================================================*/
bool GetEsmOptUseExtraFile() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetUseExtraFile();
}


/*===========================================================================
 *
 * Function - bool GetEsmOptAllowExtFuncs (void);
 *
 *=========================================================================*/
bool GetEsmOptAllowExtFuncs() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetAllowExtFuncs();
}


/*===========================================================================
 *
 * Function - int GetEsmOptScriptWarnLevel (void);
 *
 * Returns the current script compiler message level setting.
 *
 *=========================================================================*/
int GetEsmOptScriptWarnLevel() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetScriptWarnLevel();
}


/*===========================================================================
 *
 * Function - int GetEsmOptScriptFormatType (void);
 *
 * Return the current type of the script format.
 *
 *=========================================================================*/
int GetEsmOptScriptFormatType() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetFormatType();
}


/*===========================================================================
 *
 * Function - CEsmScriptOptions* GetEsmOptScriptOptions (void);
 *
 * Gets the current script options object.
 *
 *=========================================================================*/
CEsmScriptOptions *GetEsmOptScriptOptions() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetScriptOptions();
}


/*===========================================================================
 *
 * Function - const TCHAR* GetEsmOptDefaultAuthor (void);
 *
 * Returns the default author string from the application options.
 *
 *=========================================================================*/
const TCHAR *GetEsmOptDefaultAuthor() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetAuthorName();
}


/*===========================================================================
 *
 * Function - const TCHAR* GetEsmOptExtraFile (void);
 *
 *=========================================================================*/
const TCHAR *GetEsmOptExtraFile() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetExtraFile();
}


/*===========================================================================
 *
 * Function - const TCHAR* GetEsmOptScriptIndentString (void);
 *
 *=========================================================================*/
const TCHAR *GetEsmOptScriptIndentString() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	return pApp->GetOptions()->GetScriptIndentString();
}
