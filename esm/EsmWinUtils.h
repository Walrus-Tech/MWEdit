/*===========================================================================
*
* File:    Esmwinutils.H
* Author:  Dave Humphrey (uesp@m0use.net)
* Created On:  May 27, 2003
*
* Description
*
*=========================================================================*/
#ifndef __ESMWINUTILS_H
#define __ESMWINUTILS_H


#include "esm/EsmFile.h"


/* Morrowind registries */
#define MWESM_REG_INSTALLPATH _T("SOFTWARE\\Bethesda Softworks\\Morrowind\\Installed Path")
#define MWESM_REG_PATH        _T("SOFTWARE\\Bethesda Softworks\\Morrowind")


/* Path functions */
const TCHAR *GetMWDataPath();
void SetMWDataPath(const TCHAR *pString);

/* Attempt to update the Morrowind paths from ther registry */
void FindMWRegistryPath();


#endif
