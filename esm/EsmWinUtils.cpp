/*===========================================================================
 *
 * File:    Esmwinutils.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  May 27, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "stdafx.h"
#include "esmwinutils.h"
#include "WinUtil.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("EsmWinUtils.cpp");

CString l_MWDataPath = _T(""); /* Absolute path to the Morrowind data files */

/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void FindMWRegistryPath (void);
 *
 * Attempts to find the Morrowind Data Files path from the registry
 *
 *=========================================================================*/
void FindMWRegistryPath(void) {
	//l_MWDataPath = AfxGetApp()->GetProfileString(MWESM_REG_PATH, _T(""), NULL);
	BYTE Buffer[_MAX_PATH + 8];
	DWORD BufferSize = _MAX_PATH + 7;
	DWORD Type;
	HKEY hKey;
	long Result;
	Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MWESM_REG_PATH, 0, KEY_QUERY_VALUE, &hKey);

	if (Result != ERROR_SUCCESS) {
		return;
	}

	Result = RegQueryValueEx(hKey, _T("Installed Path"), NULL, &Type, Buffer, &BufferSize);
	RegCloseKey(hKey);

	if (Result != ERROR_SUCCESS) {
		return;
	}

	l_MWDataPath = Buffer;
	TerminatePathString(l_MWDataPath);
	l_MWDataPath += _T("Data Files\\");
}

/*===========================================================================
 *      End of Function FindMWRegistryPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetMWDataPath (void);
 *
 * Return the Morrowind Data File path.
 *
 *=========================================================================*/
const TCHAR *GetMWDataPath(void) {
	//return _T("e:\\Morrowind\\Data Files\\");
	return (l_MWDataPath);
}

void SetMWDataPath(const TCHAR *pString) {
	l_MWDataPath = pString;
}

/*===========================================================================
 *      End of Function TCHAR* GetMWDataPath()
 *=========================================================================*/
