/*===========================================================================
 *
 * File:    Esmcsvdefs.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  October 13, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCSVDEFS_H
#define __ESMCSVDEFS_H


#include "File/CsvFile.h"
#include "esm/EsmDefs.h"


/* Holds extended CSV import/export column information */
typedef struct {
	int FieldID;
	long UserData;
} esmcsvcol_t;

/* Holds information for importing/exporting a record type */
typedef struct {
	const TCHAR *pEsmRecType;
	const TCHAR *pRecordName;
	int *pColArray;
	esmcsvcol_t *pExColArray;
} esmcsvrecinfo_t;


/* Convert an input CSV item type to a regular item type string */

const TCHAR *GetEsmCsvRecordType(const TCHAR *pString);
const TCHAR *GetEsmCsvRecordString(const TCHAR *pString);
int *GetEsmCsvColArray(const TCHAR *pType);
esmcsvcol_t *GetEsmCsvExColArray(const TCHAR *pType);


#endif
