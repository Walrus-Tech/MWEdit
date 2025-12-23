/*===========================================================================
 *
 * File:    NameList.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, May 29, 2001
 *
 * Implements routines related to manipulating simple name-value associative
 * lists.
 *
 *=========================================================================*/
#include "Common/Utility/namelist.h"
#include <string.h>


DEFINE_FILE("NameList.cpp");


/*===========================================================================
 *
 * Function - bool FindNameValue (lValue, pValueArray, , pName);
 *
 * Attempts to find the value associated with the given name.  Returns
 * FALSE if the name could not be found. Accepts NULL strings. The
 * input array must end with an empty name string.  String compare is
 * case insensitive.
 *
 *=========================================================================*/
bool FindNameValue(long &lValue, const valuenames_t *pValueArray, const TCHAR *pName) {
	DEFINE_FUNCTION("FindNameValue()")
	int Index;
	/* Ensure valid array */
	ASSERT(pValueArray != NULL);

	/* Ignore NULL input */
	if (pName == NULL) {
		ErrorHandler.AddError(ERR_BADINPUT, "Value name string was not specified!");
		return false;
	}

	/* Search array until an empty string or null is found */
	Index = 0;

	while (pValueArray[Index].pName != NULL && pValueArray[Index].pName[0] != NULL_CHAR) {
		if (_stricmp(pValueArray[Index].pName, pName) == 0) {
			lValue = pValueArray[Index].lValue;
			return true;
		}

		Index++;
	}

	/* No match found */
	ErrorHandler.AddError(ERR_BADINPUT, "Value for the string '%s' was not found!", pName);
	return FALSE;
}


/*===========================================================================
 *
 * Function - long FindNameValue (pValueArray, pName);
 *
 * Attempts to find the value associated with the given name.  Returns
 * the value if found, or the last value in the array. String compare is
 * case insensitive.
 *
 *=========================================================================*/
long FindNameValue(const valuenames_t *pValueArray, const TCHAR *pName) {
	DEFINE_FUNCTION("FindNameValue()")
	int Index;
	/* Ensure valid input */
	ASSERT(pValueArray != NULL);

	/* Ignore NULL input */
	if (pName == NULL) {
		ErrorHandler.AddError(ERR_BADINPUT, "Value name string was not specified!");
		return false;
	}

	/* Search array until an empty string or null is found */
	Index = 0;

	while (pValueArray[Index].pName != NULL && pValueArray[Index].pName[0] != NULL_CHAR) {
		if (_stricmp(pValueArray[Index].pName, pName) == 0) {
			return pValueArray[Index].lValue;
		}

		Index++;
	}

	/* No match found */
	return pValueArray[Index].lValue;
}


/*===========================================================================
 *
 * Function - const TCHAR* FindValueName (pValueArray, lValue);
 *
 * Attempts to find the name associated with the given value.  Returns
 * the string if found, or an empty string.
 *
 *=========================================================================*/
const TCHAR *FindValueName(const valuenames_t *pValueArray, const long lValue) {
	DEFINE_FUNCTION("FindValueName()")
	int Index;
	/* Ensure valid input */
	ASSERT(pValueArray != NULL);
	/* Search array until an empty string or null is found */
	Index = 0;

	while (pValueArray[Index].pName != NULL && pValueArray[Index].pName[0] != NULL_CHAR) {
		if (pValueArray[Index].lValue == lValue) {
			return pValueArray[Index].pName;
		}

		Index++;
	}

	/* No match found */
	return _T("");
}
