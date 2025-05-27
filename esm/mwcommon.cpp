/*===========================================================================
 *
 * File:    Mwcommon.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  December 29, 2003
 *
 * Contains common functions for Morrowind related projects.
 *
 *=========================================================================*/

/* Include Files */
#include "stdafx.h"
#include "mwcommon.h"
#include "windows/WinUtil.h"
#include "dl_file.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
DEFINE_FILE("MWCommon.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetMWInstallPath (void);
 *
 * Returns the absolute path of the Morrowind installation as stored in
 * the Windows registry. Returns an empty string if the expected keys
 * were not found.
 *
 *=========================================================================*/
const TCHAR *GetMWInstallPath(void) {
	static TCHAR Buffer[_MAX_PATH + 8];
	DWORD BufferSize = _MAX_PATH + 7;
	DWORD Type;
	HKEY hKey;
	long Result;
	Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MWESM_REG_PATH, 0, KEY_QUERY_VALUE, &hKey);

	if (Result != ERROR_SUCCESS) {
		return _T("");
	}

	Result = RegQueryValueEx(hKey, _T("Installed Path"), NULL, &Type, (BYTE *)Buffer, &BufferSize);
	RegCloseKey(hKey);

	if (Result != ERROR_SUCCESS) {
		return _T("");
	}

	TerminatePath(Buffer);
	return (Buffer);
}

/*===========================================================================
 *      End of Function TCHAR* GetMWInstallPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetMWDataFilePath (void);
 *
 * Returns the absolute path of the Morrowind "Data Files" game path as
 * stored in the Windows registry. Returns an empty string if the
 * expected keys were not found.
 *
 *=========================================================================*/
const TCHAR *GetMWDataFilePath(void) {
	static TCHAR Buffer[_MAX_PATH + 24];
	TSTRCPY(Buffer, GetMWInstallPath());

	if (Buffer[0] == NULL_CHAR) {
		return _T("");
	}

	TSTRCAT(Buffer, _T("Data Files\\"));
	return (Buffer);
}

/*===========================================================================
 *      End of Function TCHAR* GetMWDataFilePath()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetMWTexturesPath (void);
 *
 * Returns the absolute path of the Morrowind "Data Files\Textures" game
 * path as stored in the Windows registry. Returns an empty string if the
 * expected keys were not found.
 *
 *=========================================================================*/
const TCHAR *GetMWTexturesPath(void) {
	static TCHAR Buffer[_MAX_PATH + 32];
	TSTRCPY(Buffer, GetMWInstallPath());

	if (Buffer[0] == NULL_CHAR) {
		return _T("");
	}

	TSTRCAT(Buffer, _T("Data Files\\Textures\\"));
	return (Buffer);
}

/*===========================================================================
 *      End of Function TCHAR* GetMWTexturesPath()
 *=========================================================================*/
