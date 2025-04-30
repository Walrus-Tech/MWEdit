/*===========================================================================
 *
 * File:    DL_Str.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Saturday, May 05, 2001
 *
 * Contains string related definitions for Dave's Library of common code.
 *
 *=========================================================================*/
#ifndef __DL_STR_H
#define __DL_STR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_mem.h"
#include "dl_err.h"
#include "dl_log.h"
#include <string.h>
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Defines
 *
 *=========================================================================*/

/* Convert a bool value to a string */
#define BooleanToString(Flag) ((Flag) ? _T("True") : _T("False"))
#define BOOLTOYESNO(Flag)     ((Flag) ? _T("Yes") : _T("No"))

/* Shortcut to trimming whitespace from a string */
#define trim(String) ltrim(rtrim(String))

#if defined(_WIN32_WCE)
	#define stricmp(String1, String2) _stricmp((String1), (String2))
#endif

/*===========================================================================
 *      End of Defines
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Returns the number of substrings in the given string */
size_t CountSubstrings(const TCHAR *pSourceString, const TCHAR *pSearchString);

/* Is... type functions for strings */
bool IsStringNumber(const TCHAR *pString);
bool IsStringDigit(const TCHAR *pString);
bool IsStringPrint(const TCHAR *pString);
bool IsStringFloat(const TCHAR *pString);

/* Strip whitespace from left/right side of string */
TCHAR* ltrim(TCHAR *pString);
TCHAR* rtrim(TCHAR *pString);

/* A strlen() function which can handle NULL strings */
size_t SafeStrLen(const TCHAR *pString);

/* Seperate a string in a variable/value pair */
bool SeperateVarValue(TCHAR **ppVariable,
                      TCHAR** ppValue,
                      TCHAR *pString,
                      const TCHAR SeperatorTCHAR = _T('='),
                      const TCHAR CommentTCHAR = _T('#'));
bool SeperateVarValueQ(TCHAR **ppVariable,
                       TCHAR **ppValue,
                       TCHAR *pString,
                       const TCHAR SeperatorTCHAR = _T('='),
                       const TCHAR CommentTCHAR = _T('#'));

/* A smart string compare function which supports NULL cases and case sensitivity */
bool StringChanged(const TCHAR *pString1, const TCHAR *pString2, const bool CaseSensitive = FALSE);
int StringCompare(const TCHAR *pString1, const TCHAR *pString2, const bool CaseSensitive = FALSE);

/* Convert a string to a bool value */
bool StringToBoolean(bool &Flag, const TCHAR *pString);
bool StringToBoolean(const TCHAR *pString);

/* Counts the number of lines in string, seperated by a CR */
size_t strhgt(const TCHAR *pString);

/* Find a substring in a string with case insensitivity */
TCHAR* stristr(const TCHAR *pString, const TCHAR *pSubString);

/* Compares two strings up to the length of the shortest, case insensitive */
int strlicmp(const TCHAR *pString1, const TCHAR *pString2);

/* Return number of TCHARacters to first CR or end of string */
size_t strlinelen(const TCHAR *pString);

/* Returns the maximum line length of lines seperated by CR */
size_t strmaxlinelen(const TCHAR *pString);

/* Copies a maximum number of TCHARacter ensuring string is NULL terminated */
TCHAR* strnncpy(TCHAR *pDestString, const TCHAR *pSourceString, const size_t MaxStringLength);

/* Output printf() formatted message to a string buffer */
int snprintf(TCHAR *pBuffer, const size_t MaxLength, const TCHAR *pFormat, ...);

/* Removes quotes from the string */
TCHAR* UnquoteString(TCHAR *pString);

/* String argument formatter with length checking */
int vsnprintf(TCHAR *pBuffer, const size_t MaxLength, const TCHAR *pFormat, va_list Args);


/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Inline String Functions
 *
 *=========================================================================*/

/* A strlen() function which can handle NULL strings */
inline size_t SafeStrLen(const TCHAR *pString) {
	return ((pString == NULL) ? 0 : TSTRLEN(pString));
}

/*===========================================================================
 *      End of Inline String Functions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Standard Replacement Function Prototypes
 *
 * These functions are only used in systems where they are not
 * otherwise available.
 *
 *=========================================================================*/
#if !defined(__TURBOC__) && !defined(_WIN32)

	/* Standard uppercase/lowercase conversion functions */
	TCHAR* strlwr(TCHAR *pString);
	TCHAR* strupr(TCHAR *pString);

	/* Compare a portion of a string with case insensitivity */
	int strnicmp(const TCHAR *pString1, const TCHAR *pString2, const size_t MaxStringLength);

#endif
/*===========================================================================
 *      End of Standard Replacement Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Testing Routine Prototypes
 *
 * Prototypes for test functions of module.  Only available in DEBUG builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)
	void Test_vsnprintf(void);
	void Test_CountSubstrings(void);
	void Test_ltrim(void);
	void Test_rtrim(void);
	void Test_strlinelen(void);
	void Test_SeperateVarValue(void);
	void Test_StringToBoolean(void);
	void Test_StringChanged(void);
	void Test_IsStringNumber(void);
	void Test_stristr(void);
	void Test_strlicmp(void);
	void Test_strnncpy(void);
	void Test_strproper(void);
	void Test_strhgt(void);
	void Test_strmaxlinelen(void);
	void Test_strupr(void);
	void Test_strnicmp(void);
	void Test_DLStr(void);
#endif
/*===========================================================================
 *      End of Testing Routine Prototypes
 *=========================================================================*/




#endif
/*===========================================================================
 *      End of File Dl_str.H
 *=========================================================================*/
