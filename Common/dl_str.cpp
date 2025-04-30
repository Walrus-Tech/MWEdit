/*===========================================================================
 *
 * File:    DL_Str.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Saturday, May 05, 2001
 *
 * Comtains implementation of string related functions for Dave's Library
 * of common code.
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *  - Moved from regular char to TCHAR type to support wide characters
 *    under Windows. Successfully tested.
 *
 * 22 Jan 2003 (Dave Humphrey)
 *  - Added the IsStringPrint() function.
 *
 * 2 October 2003
 *  - Made the vsnprintf() function available under Borland.
 *
 * 4 January 2003
 *  - StringToBoolean() modified to convert Yes/No values.
 *
 *=========================================================================*/

/* Include Files */
#include "dl_str.h"
#include "dl_chr.h"
#include <ctype.h>


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
DEFINE_FILE("dl_str.cpp");
/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - size_t CountSubstrings (pSourceString, pSearchString);
 *
 * Counts the number of times pSearchString occurs in pSourceString.
 * ASSERTs if any input is invalid.  Supports finding of overlapping
 * search strings, for example, a count of strings "yy" in string "yyyyyy"
 * yields 5 (rather than just 3 if it didn't support overlapping strings).
 *
 *=========================================================================*/
size_t CountSubstrings(const TCHAR *pSourceString, const TCHAR *pSearchString) {
	DEFINE_FUNCTION("CountSubstrings()");
	size_t Count = 0;
	TCHAR *pFind;
	/* Ensure valid input */
	ASSERT(pSourceString != NULL && pSearchString != NULL);
	pFind = (TCHAR *)TSTRSTR(pSourceString, pSearchString);

	while (pFind != NULL) {
		Count++;
		pFind = TSTRSTR(pFind + 1, pSearchString);
	}

	return (Count);
}

/*===========================================================================
 *      End of Function CountSubstrings()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsStringFloat (pString);
 *
 * Returns TRUE if the string is composed only of whitespace and numbers
 * from 0 to 9 and one '.'.
 *
 *=========================================================================*/
bool IsStringFloat(const TCHAR *pString) {
	DEFINE_FUNCTION("IsStringFloat()");
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Parse string character by character */
	while (*pString != NULL_CHAR) {
		if (*pString == '.') {
			pString++;
			break;
		}

		if (!TISSPACE(*pString) && !TISDIGIT(*pString)) {
			return (false);
		}

		pString++;
	}

	while (*pString != NULL_CHAR) {
		if (!TISSPACE(*pString) && !TISDIGIT(*pString)) {
			return (false);
		}

		pString++;
	}

	return (true);
}

/*===========================================================================
 *      End of Function IsStringFloat()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsStringNumber (pString);
 *
 * Returns TRUE if the string is composed only of whitespace and numbers
 * from 0 to 9.
 *
 *=========================================================================*/
bool IsStringNumber(const TCHAR *pString) {
	DEFINE_FUNCTION("IsStringNumber()");
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Parse string character by character */
	while (*pString != NULL_CHAR) {
		if (!TISSPACE(*pString) && !TISDIGIT(*pString)) {
			return (false);
		}

		pString++;
	}

	return (true);
}

/*===========================================================================
 *      End of Function IsStringNumber()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsStringDigit (pString);
 *
 * Returns TRUE if the string is composed only of decimal numbers 0 to 9.
 *
 *=========================================================================*/
bool IsStringDigit(const TCHAR *pString) {
	DEFINE_FUNCTION("IsStringDigit()");
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Parse string character by character */
	while (*pString != NULL_CHAR) {
		if (!TISDIGIT(*pString)) {
			return (false);
		}

		pString++;
	}

	return (true);
}

/*===========================================================================
 *      End of Function IsStringDigit()
 *=========================================================================*/



/*===========================================================================
 *
 * Function - bool IsStringPrint (pString);
 *
 * Returns TRUE if the string is composed only of printable characters.
 *
 *=========================================================================*/
bool IsStringPrint(const TCHAR *pString) {
	DEFINE_FUNCTION("IsStringPrint()");
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Parse string character by character */
	while (*pString != NULL_CHAR) {
		if (!TISPRINT(*pString)) {
			return (false);
		}

		pString++;
	}

	return (true);
}

/*===========================================================================
 *      End of Function IsStringPrint()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* ltrim (TCHAR* pString);
 *
 * Strips all space characters from the left side of the given string,
 * returning a pointer to the first non-whitespace character.
 * Space characters include spaces, tabs and line feeds a defined by
 * the isspace() function.  ASSERTs if given invalid input.
 *
 *=========================================================================*/
TCHAR* ltrim(TCHAR *pString) {
	DEFINE_FUNCTION("ltrim()");
	size_t Index = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Ignore any spaces or TABs until end of string */
	while (pString[Index] != '\0' && TISSPACE(pString[Index])) {
		Index++;
	}

	/* Return pointer to the first non-whitespace TCHAR */
	return (pString + Index);
}

/*===========================================================================
 *      End of Function ltrim()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* rtrim (TCHAR* pString);
 *
 * Strips all space characters from the right side of the given string,
 * returning a pointer to the modified string.  Space characters include
 * spaces, tabs and line feeds a defined by the isspace() function.
 * ASSERTs if given invalid input.
 *
 *=========================================================================*/
TCHAR* rtrim(TCHAR *pString) {
	DEFINE_FUNCTION("rtrim()");
	size_t Index;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Start at the end of the string */
	Index = TSTRLEN(pString);

	while (Index != 0) {
		Index--;

		/* Terminate string and return if non-whitespace found */
		if (!TISSPACE(pString[Index])) {
			pString[Index + 1] = NULL_CHAR;
			return (pString);
		}
	}

	/* Return an empty string */
	*pString = NULL_CHAR;
	return (pString);
}

/*===========================================================================
 *      End of Function rtrim()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SeperateVarValue (ppVariable, ppValue, pString,
                        SeperatorChar = '=',
                    CommentChar   = '#');
 *
 * Takes the input string and attempts to seperate it into a variable/value
 * pair.  If the CommentChar is non-NULL, everything after the last comment
 * character in a line is ignored.  The string is then split into two
 * where the first SeperatorChar is found.  Whitespace is trimmed and the
 * results stored in ppVariable and ppValue.  Returns TRUE on success.
 * FALSE is returned if no variable/value pair was found (ppVariable then
 * points to the string with no comments and whitespace trimmed).
 * ASSERTs if given invalid input.
 *
 *=========================================================================*/
bool SeperateVarValue(TCHAR **ppVariable,
                      TCHAR **ppValue,
                      TCHAR *pString,
                      const TCHAR SeperatorChar,
                      const TCHAR CommentChar) {
	DEFINE_FUNCTION("SeperateVarValue()");
	TCHAR *pParse;
	/* Ensure valid input */
	ASSERT(ppVariable != NULL && ppValue != NULL && pString != NULL);
	ASSERT(SeperatorChar != NULL_CHAR);

	/* Remove any comments from string, if required */
	if (CommentChar != NULL_CHAR) {
		chrrtrunc(pString, CommentChar);
	}

	/* Look for the seperator TCHAR */
	*ppVariable = trim(pString);
	pParse = TSTRCHR(pString, SeperatorChar);

	if (pParse == NULL) {
		return (false);
	}

	*pParse = NULL_CHAR;
	/* Remove trailing spaces from variable */
	rtrim(*ppVariable);
	/* Remove leading spaces from the value */
	*ppValue = ltrim(pParse + 1);
	return (true);
}

/*===========================================================================
 *      End of Function SeperateVarValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SeperateVarValueQ (ppVariable, ppValue, pString,
                        SeperatorChar, CommentChar);
 *
 * Same as the SeperateVarValue() function but handles values that are
 * surrounded by double quotes ("").
 *
 *=========================================================================*/
bool SeperateVarValueQ(TCHAR **ppVariable,
                       TCHAR **ppValue,
                       TCHAR *pString,
                       const TCHAR SeperatorChar,
                       const TCHAR CommentChar) {
	DEFINE_FUNCTION("SeperateVarValueQ()");
	TCHAR *pParse;
	bool FoundSep;
	bool FoundQuote;
	/* Ensure valid input */
	ASSERT(ppVariable != NULL && ppValue != NULL && pString != NULL);
	ASSERT(SeperatorChar != NULL_CHAR);
	pParse = pString;
	FoundSep = false;
	FoundQuote = false;

	while (*pParse != NULL_CHAR) {
		if (*pParse == SeperatorChar && !FoundSep) {
			*pParse = NULL_CHAR;
			FoundSep = true;
			*ppVariable = trim(pString);
			*ppValue = pParse + 1;
		} else if (FoundSep && *pParse == '"') {
			if (FoundQuote) {
				*pParse = NULL_CHAR;
			} else {
				*ppValue = pParse + 1;
			}

			FoundQuote = !FoundQuote;
		} else if (!FoundQuote && *pParse == CommentChar) {
			*pParse = NULL_CHAR;
			break;
		}

		pParse++;
	}

	if (!FoundSep) {
		*ppVariable = trim(pString);
		*ppValue = NULL;
		return (false);
	} else {
		*ppValue = trim(*ppValue);
	}

	return (true);
}

/*===========================================================================
 *      End of Function SeperateVarValueQ()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool StringToBoolean (pString);
 *
 * Returns the bool equivalent of a string.  For use when it doesn't
 * matter if the string does not represent a bool string.
 *
 * See Also: StringToBoolean (bool&, TCHAR*);
 *
 *=========================================================================*/
bool StringToBoolean(const TCHAR *pString) {
	//DEFINE_FUNCTION("StringToBoolean(TCHAR*)");
	bool Flag = FALSE;
	StringToBoolean(Flag, pString);
	return (Flag);
}

/*===========================================================================
 *      End of Function StringToBoolean()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool StringToBoolean (Flag, pString);
 *
 * Atempts to convert a string to a bool TRUE/FALSE value, returning
 * the result in the Flag referenced variable.  Returns TRUE if the
 * string was successfully parsed to a bool, or FALSE otherwise.
 * ASSERTs if passed invalid input.
 *  1. Checks string against 'TRUE' or 'FALSE', case insensitive
 *  2. Checks string against 'YES'  or 'NO', case insensitive
 *  3. Checks for a zero/non-zero integral value.
 *  4. If conversion to a number failed, FALSE is returned.
 *
 * See Also: StringToBoolean (TCHAR*);
 *
 *=========================================================================*/
bool StringToBoolean(bool &Flag, const TCHAR *pString) {
	DEFINE_FUNCTION("StringToBoolean(bool&, TCHAR*)");
	TCHAR *pError;
	long Result;
	/* Make sure the string is valid */
	ASSERT(pString != NULL);

	/* See if the string contains explicit TRUE/FALSE strings */
	if (_stricmp(pString, _T("TRUE")) == 0 || _stricmp(pString, _T("YES")) == 0) {
		Flag = TRUE;
		return (true);
	} else if (_stricmp(pString, _T("FALSE")) == 0 || _stricmp(pString, _T("NO")) == 0) {
		Flag = FALSE;
		return (true);
	} else if (*pString == NULL_CHAR) { /* Special case for an empty string */
		return (false);
	}

	/* Convert the string to a number as a last resort */
	Result = TSTRTOL(pString, &pError, 0);

	if (*pError != NULL_CHAR) {
		return (false);
	}

	Flag = (bool)(Result == 0) ? false : true;
	return (false);
}

/*===========================================================================
 *      End of Function StringToBoolean()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool StringChanged (pString1, pString2, CaseSensitive);
 *
 * Smart string compare which returns TRUE if the two strings are different.
 * Handles NULL cases and case sensitivity.  Default is case insensitive.
 *
 *=========================================================================*/
bool StringChanged(const TCHAR *pString1, const TCHAR *pString2, const bool CaseSensitive) {
	//DEFINE_FUNCTION("StringChanged()");

	/* Check for NULL strings */
	if (pString1 == NULL && pString2 == NULL) {
		return (FALSE);
	}

	if (pString1 == NULL) {
		return (TRUE);
	}

	if (pString2 == NULL) {
		return (TRUE);
	}

	/* Compare the two valid strings depending on the case option */
	if (CaseSensitive) {
		if (TSTRCMP(pString1, pString2) == 0) {
			return (FALSE);
		}
	} else {
		if ( _stricmp(pString1, pString2) == 0) {
			return (FALSE);
		}
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Function StringChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int StringCompare (pString1, pString2, CaseSensitive);
 *
 * Smart string compare which returns as per strcmp().  Handles NULL cases
 * and case sensitivity.  Default is case insensitive.
 *
 *=========================================================================*/
int StringCompare(const TCHAR *pString1, const TCHAR *pString2, const bool CaseSensitive) {
	//DEFINE_FUNCTION("StringCompare()");

	/* Check for NULL strings */
	if (pString1 == NULL && pString2 == NULL) {
		return (0);
	}

	if (pString1 == NULL) {
		return (-pString2[0]);
	}

	if (pString2 == NULL) {
		return (pString1[0]);
	}

	/* Compare the two valid strings depending on the case option */
	if (CaseSensitive) {
		return TSTRCMP(pString1, pString2);
	} else {
		return _stricmp(pString1, pString2);
	}
}

/*===========================================================================
 *      End of Function StringChanged()
 *=========================================================================*/



/*=========================================================================
 *
 * Function - size_t strhgt (pString);
 *
 * Returns the number of lines in the string (seperated by a Line Feed).
 * ASSERTs if given invalid input.
 *
 *=======================================================================*/
size_t strhgt(const TCHAR *pString) {
	DEFINE_FUNCTION("strhgt()");
	size_t LineCount = 1;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	while (*pString != NULL_CHAR) {
		if (*pString == LF_CHAR) {
			LineCount++;
		}

		pString++;
	}

	return (LineCount);
}

/*=========================================================================
 *      End of Function strhgt()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* stristr (pString, pSearchString);
 *
 * Returns the first position of the given substring in the string, ignoring
 * case.  Returns NULL if the substring is not found in the string.  ASSERTs
 * if given invalid input.  Functions the same as the standard TSTRSTR()
 * function.
 *
 *=========================================================================*/
TCHAR* stristr(const TCHAR *pString, const TCHAR *pSearchString) {
	DEFINE_FUNCTION("stristr()");
	size_t StringIndex = 0;
	size_t SearchIndex = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL && pSearchString != NULL);

	/* Special case for an empty search string */
	if (*pSearchString == NULL_CHAR) {
		return (NULL);
	}

	/* The main search loop */
	while (pString[StringIndex] != NULL_CHAR) {
		if (TTOUPPER(pString[StringIndex]) == TTOUPPER(pSearchString[SearchIndex])) {
			SearchIndex++;

			if (pSearchString[SearchIndex] == NULL_CHAR) {
				return (((TCHAR *)pString) + StringIndex - SearchIndex + 1);
			}
		} else if (SearchIndex != 0) {
			StringIndex -= SearchIndex;
			SearchIndex = 0;
		}

		StringIndex++;
	}

	/* Nothing found... */
	return (NULL);
}

/*===========================================================================
 *      End of Function stristr()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - TCHAR *strnncpy (pDestString, pSourceString, MaxStringLegth);
 *
 * Just like the standard strncpy function but appends a NUL character
 * to the end of the destination if required.  Returns a pointer to the
 * destination string.  ASSERTs if given invalid input.
 *
 *=======================================================================*/
TCHAR* strnncpy(TCHAR *pDestString, const TCHAR *pSourceString, const size_t MaxStringLength) {
	DEFINE_FUNCTION("strnncpy()");
	size_t Index = 0;
	/* Ensure valid Input */
	ASSERT(pDestString != NULL);

	if (pSourceString == NULL) {
		pDestString[0] = NULL_CHAR;
		return (pDestString);
	}

	/* Start copying */
	while (Index < MaxStringLength && *pSourceString != NULL_CHAR) {
		pDestString[Index] = *pSourceString;
		++pSourceString;
		++Index;
	}

	/* Null terminate */
	pDestString[Index] = NULL_CHAR;
	return (pDestString);
}

/*=========================================================================
 *      End of Function strnncpy()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - int strlicmp (pString1, pString2);
 *
 * Compares the two strings, up to the end of the shortest string,
 * with case insensitivity.  ASSERTs if given invalid input.  Returns
 * same values as the TSTRCMP() function:
 *  < 0 : String1 is less than String2
 *  = 0 : String1 is the same as String2
 *  > 0 : String1 is greater than String2
 *
 *=======================================================================*/
int strlicmp(const TCHAR *pString1, const TCHAR *pString2) {
	DEFINE_FUNCTION("strlicmp()");
	int StringDifference;
	size_t Index = 0;
	/* Can't use NULL pointers */
	ASSERT(pString1 != NULL && pString2 != NULL);

	/* Compare the strings up to end of string */
	while (pString1[Index] != NULL_CHAR && pString2[Index] != NULL_CHAR) {
		StringDifference = TTOUPPER(pString1[Index]) - TTOUPPER(pString2[Index]);

		if (StringDifference != 0) {
			return (StringDifference);
		}

		Index++;
	}

	return (0);
}

/*=========================================================================
 *      End of Function strlicmp()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - size_t strlinelen (pString);
 *
 * Returns the number of characters up to the first Line Feed in the
 * string, or the end of the string if no CR is found.  ASSERTs if input
 * is invalid.
 *
 *=========================================================================*/
size_t strlinelen(const TCHAR *pString) {
	DEFINE_FUNCTION("strlinelen()");
	size_t Index = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Find end of string or first CR */
	while (pString[Index] != NULL_CHAR && pString[Index] != LF_CHAR) {
		Index++;
	}

	return (Index);
}

/*===========================================================================
 *      End of Function strlinelen()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - TCHAR *strlwr (string);
 *
 * Converts a string to lowercase.  Only used if not available in
 * the current system.  ASSERTs if given invalid input.
 *
 *=======================================================================*/
#if !defined(__TURBOC__) && !defined(_WIN32)

TCHAR* strlwr(TCHAR *pString) {
	DEFINE_FUNCTION("strlwr()");
	size_t Index = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	while (pString[Index] != NULL_CHAR) {
		pString[Index] = TTOUPPER(pString[Index]);
		Index++;
	}

	return (pString);
}

#endif
/*=========================================================================
 *      End of Function strlwr()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - size_t strmaxlinelen (pString);
 *
 * Finds and returns the length of the longest substring in the string
 * separated by Line Feeds.  ASSERTs if given invalid input.
 *
 *=======================================================================*/
size_t strmaxlinelen(const TCHAR *pString) {
	DEFINE_FUNCTION("strmaxlinelen()");
	size_t LineLength = 0;
	size_t MaxLineLength = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Find all lines in string */
	while (*pString != NULL_CHAR) {
		if (*pString == LF_CHAR) {
			if (LineLength > MaxLineLength) {
				MaxLineLength = LineLength;
			}

			LineLength = 0;
		} else {
			LineLength++;
		}

		pString++;
	}

	if (LineLength > MaxLineLength) {
		MaxLineLength = LineLength;
	}

	return (MaxLineLength);
}

/*=========================================================================
 *      End of Function strmaxlinelen()
 *=======================================================================*/


/*========================================================================
 *
 * Function - int strnicmp (pString1, pString2, MaxStringLength);
 *
 * Compares the two strings, up to the max length characters, and returns
 * a value based on their equality (with case insensitivity).
 *  < 0 : String1 is less than String2
 *  = 0 : String1 is the same as String2
 *  > 0 : String1 is greater than String2
 * ASSERTs if given invalid inputs. Is only used in systems where a
 * similar function is not available.
 *
 *=======================================================================*/
#if !defined(__TURBOC__) && !defined(_WIN32)

int strnicmp(const TCHAR *pString1, const TCHAR *pString2, const size_t MaxStringLength) {
	DEFINE_FUNCTION("strnicmp()");
	int StringDiff;
	size_t Index = 0;
	/* Ensure valid inputs */
	ASSERT(pString1 != NULL && pString2 != NULL);

	/* Compare the strings up to maxlen or end of string */
	while (pString1[Index] != NULL_CHAR &&
	       pString2[Index] != NULL_CHAR &&
	       Index < MaxStringLength) {
		StringDiff = TTOUPPER(pString1[Index]) - TTOUPPER(pString2[Index]);

		if (StringDiff != 0) {
			return (StringDiff);
		}

		Index++;
	}

	if (Index == MaxStringLength) {
		return (0);
	}

	return (TTOUPPER(pString1[Index]) - TTOUPPER(pString2[Index]));
}

#endif
/*=========================================================================
 *      End of Function strnicmp()
 *=======================================================================*/


/*=========================================================================
 *
 * Function - TCHAR* strproper (pString);
 *
 * Converts the specified string to proper case (first letter in each word
 * is capitalized).  Returns a pointer to the modified string.  ASSERTs
 * if given invalid input.  Whitespace is defined according to the
 * isspace() function.
 *
 *=======================================================================*/
TCHAR* strproper(TCHAR *pString) {
	DEFINE_FUNCTION("strproper()");
	TCHAR* pInitialString = pString;
	/* Make sure it is a valid string */
	ASSERT(pString != NULL);

	/* Find the next non-whitespace character */
	while (*pString != NULL_CHAR) {
		pString = ltrim(pString);
		*pString = (TCHAR)TTOUPPER(*pString);

		/* Find the next whitespace character */
		while (*pString != NULL_CHAR && !TISSPACE(*pString)) {
			pString++;
		}
	}

	/* Return the string pointer */
	return (pInitialString);
}

/*=========================================================================
 *      End of Function strproper()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* UnquoteString (pString);
 *
 * Removes quotes from the beginning/end of the string. The string is
 * modified. Returns the start to the unquoted string.
 *
 *=========================================================================*/
TCHAR* UnquoteString(TCHAR *pString) {
	TCHAR *pParse = pString;
	TCHAR *pStart = pString;
	bool FoundQuote = false;

	while (*pParse != NULL_CHAR) {
		if (*pParse == '"') {
			*pParse = NULL_CHAR;

			if (FoundQuote) {
				return (pStart);
			}

			FoundQuote = true;
			pStart = pParse + 1;
		}

		pParse++;
	}

	return (pString);
}

/*===========================================================================
 *      End of Function UnquoteString()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - TCHAR *strupr (string);
 *
 * Converts a string to uppercase.  Only used if not available in
 * the current system.  ASSERTs if given invalid input.
 *
 *=======================================================================*/
#if !defined(__TURBOC__) && !defined(_WIN32)

TCHAR* strupr(TCHAR *pString) {
	DEFINE_FUNCTION("strupr()");
	size_t Index = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	while (pString[Index] != NULL_CHAR) {
		pString[Index] = (TCHAR)TTOUPPER(pString[Index]);
		Index++;
	}

	return (pString);
}

#endif
/*=========================================================================
 *      End of Function strupr()
 *=======================================================================*/


/*===========================================================================
 *
 * Function - int snprintf (pBuffer, MaxLength, pFormat, ...);
 *
 * Similar to the sprintf() function which outputs a printf() formatted
 * list of arguments to a string buffer, but also limits the number of
 * bytes output to the buffer.  For systems that have no builtin version
 * of a snprintf() function, the function ASSERTs if more than MaxLength
 * characters have been output to the buffer.  Returns the number of
 * bytes output to the string, or negative value on error.
 *
 * See Also: vsnprintf()
 *
 *=========================================================================*/
//int snprintf (TCHAR* pBuffer, const size_t MaxLength, const TCHAR* pFormat, ...) {
// DEFINE_FUNCTION("vsnprintf()");
// va_list Args;
// int     Result;
//
//	/* Ensure valid input */
// ASSERT(pBuffer != NULL && pFormat != NULL);
//
// va_start(Args, pFormat);
// Result = vsnprintf (pBuffer, MaxLength, pFormat, Args);
// va_end(Args);
//
// return (Result);
// }
/*===========================================================================
 *      End of Function snprintf()
 *=========================================================================*/



/*===========================================================================
 *
 * Function - int vsnprintf (pBuffer, MaxLength, pFormat, Args);
 *
 * Similar to the function vsprintf() which outputs a variable list of
 * arguments to a string buffer, but outputs a maximum of MaxLength bytes
 * to the output buffer.  In systems that have no builtin vsnprintf()
 * type function, the function ASSERTs if more than MaxLength characters
 * are output to the buffer.  Returns the number of characters output
 * to the buffer, not including the terminating NULL character, or a
 * negative value on any error.
 *
 *=========================================================================*/
//int vsnprintf (TCHAR* pBuffer, const size_t MaxLength, const TCHAR* pFormat, va_list Args) {
// DEFINE_FUNCTION("vsnprintf()");
// int Result;
//
//	/* Ensure valid input */
// ASSERT(pBuffer != NULL && pFormat != NULL);
//
//	/* Windows has a builtin vsnprintf() type function */
// #if defined(_WIN32) && !defined(__BCPLUSPLUS__)
// Result = _vsntprintf(pBuffer, MaxLength, pFormat, Args);
// #else
// Result = vsprintf(pBuffer, pFormat, Args);
//    //ASSERT(Result >= 0 && ((size_t)Result) <= MaxLength);
//
// if (Result > 0 && (size_t)Result > MaxLength) {
// ErrorHandler.AddError(ERR_OVERFLOW, "Wrote %d bytes to a maximum buffer size of %u bytes!", Result, MaxLength);
// Result = -1;
// }
// #endif
//
// if (Result < 0) pBuffer[MaxLength] = NULL_CHAR;
// return (Result);
// }
/*===========================================================================
 *      End of Function vsnprintf()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 * Test routines for the functions in this module.  Only defined in
 * DEBUG builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)

/* Turn off compiler warning options */
#if defined(__BCPLUSPLUS__)
	#pragma warn -rch
	#pragma warn -ccc
#endif

/*===========================================================================
 *
 * Function - void Test_CountSubstrings (void);
 *
 * Tests the CountSubstrings() function
 *  1. Checks function with a regular search string
 *  2. Tests with a string containing overlapping search strings.
 *  3. Test empty string case
 *  4. Test nosubstrings case
 *
 *=========================================================================*/
void Test_CountSubstrings(void) {
	DEFINE_FUNCTION("Test_CountSubstrings()");
	TCHAR TestString[101];
	size_t Result;
	SystemLog.Printf(stdout, _T("============= Testing CountSubstrings() ===================="));
	/* Check function with a regular string */
	TSTRCPY(TestString, _T(".....11....11..11...11.11"));
	Result = CountSubstrings(TestString, _T("11"));
	ASSERT(Result == 5);
	/* Check function with string containing overlapping strings */
	TSTRCPY(TestString, _T("...1111....111111"));
	Result = CountSubstrings(TestString, _T("11"));
	ASSERT(Result == 8);
	/* Check function with a empty string */
	TSTRCPY(TestString, _T(""));
	Result = CountSubstrings(TestString, _T("11"));
	ASSERT(Result == 0);
	/* Check function with a string with no substrings*/
	TSTRCPY(TestString, _T(".....22....22..22...22.22"));
	Result = CountSubstrings(TestString, _T("11"));
	ASSERT(Result == 0);
}

/*===========================================================================
 *      End of Function Test_CountSubstrings()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_ltrim (void);
 *
 * Tests the ltrim() function.
 *  1. Test string with whitespace to remove
 *  2. Test string with no whitespace
 *  3. Test string with all whitespace
 *  4. Test empty string
 *
 *=========================================================================*/
void Test_ltrim(void) {
	DEFINE_FUNCTION("Test_ltrim()");
	TCHAR TestString[101];
	TCHAR *pTrimmed;
	SystemLog.Printf(stdout, _T("============= Testing ltrim() ===================="));
	/* Check with a regular string with whitespace */
	TSTRCPY(TestString, _T("  \t\t  123"));
	pTrimmed = ltrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("123")) == 0);
	/* Check with a regular string with no whitespace */
	TSTRCPY(TestString, _T("123"));
	pTrimmed = ltrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("123")) == 0);
	/* Check with a regular string with all whitespace */
	TSTRCPY(TestString, _T("  \t\t  "));
	pTrimmed = ltrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("")) == 0);
	/* Check with a emnpty string*/
	TSTRCPY(TestString, _T(""));
	pTrimmed = ltrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("")) == 0);
}

/*===========================================================================
 *      End of Function Test_ltrim()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_rtrim (void);
 *
 * Tests the rtrim() function.
 *  1. Test string with whitespace to remove
 *  2. Test string with no whitespace
 *  3. Test string with all whitespace
 *  4. Test empty string
 *
 *=========================================================================*/
void Test_rtrim(void) {
	DEFINE_FUNCTION("Test_rtrim()");
	TCHAR TestString[101];
	TCHAR *pTrimmed;
	SystemLog.Printf(stdout, _T("============= Testing rtrim() ===================="));
	/* Check with a regular string with whitespace */
	TSTRCPY(TestString, _T("123  \t\t  "));
	pTrimmed = rtrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("123")) == 0);
	/* Check with a regular string with no whitespace */
	TSTRCPY(TestString, _T("123"));
	pTrimmed = rtrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("123")) == 0);
	/* Check with a regular string with all whitespace */
	TSTRCPY(TestString, _T("  \t\t  "));
	pTrimmed = rtrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("")) == 0);
	/* Check with a empty string*/
	TSTRCPY(TestString, _T(""));
	pTrimmed = rtrim(TestString);
	ASSERT(TSTRCMP(pTrimmed, _T("")) == 0);
}

/*===========================================================================
 *      End of Function Test_rtrim()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_SeperateVarValue (void);
 *
 * Tests the SeperateVarValue() function.
 *  1. Tests for a variety of regular strings with Var, Value, and Comment
 *     using default characters.
 *  2. Test using specific characters for seperation/comment
 *  3. Test with NULL comment character
 *  4. Test with string with no seperator character
 *
 *=========================================================================*/
void Test_SeperateVarValue(void) {
	DEFINE_FUNCTION("Test_SeperateVarValue()");
	TCHAR TestString[101];
	bool Result;
	TCHAR *pVar;
	TCHAR *pVal;
	SystemLog.Printf(stdout, _T("============= Testing SeperateVarValue() ===================="));
	/* Test a regular string using function default characters */
	TSTRCPY(TestString, _T("  Variable   =  Value    # Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString);
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("Value")) == 0);
	/* Test a regular string using function default characters, no whitespace */
	TSTRCPY(TestString, _T("Variable=Value#Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString);
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("Value")) == 0);
	/* Test a string with multiple characters */
	TSTRCPY(TestString, _T(" Variable === Value ###Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString);
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("== Value ##")) == 0);
	/* Test a regular string using specific seperator character */
	TSTRCPY(TestString, _T("  Variable  *  Value     # Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString, '*');
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("Value")) == 0);
	/* Test a regular string using specific characters */
	TSTRCPY(TestString, _T("  Variable  *  Value     { Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString, '*', '{');
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("Value")) == 0);
	/* Test a regular string with NULL comment character */
	TSTRCPY(TestString, _T("  Variable  =  Value#Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString, '=', NULL_CHAR);
	ASSERT(Result);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
	ASSERT(TSTRCMP(pVal, _T("Value#Comment")) == 0);
	/* Test a regular string with no seperator character */
	TSTRCPY(TestString, _T("  Variable # Comment"));
	Result = SeperateVarValue(&pVar, &pVal, TestString);
	ASSERT(Result == false);
	ASSERT(TSTRCMP(pVar, _T("Variable")) == 0);
}

/*===========================================================================
 *      End of Function Test_SeperateVarValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_StringToBoolean (void);
 *
 * Tests the StringToBoolean() function.
 *  1. Tests strings of 'TRUE' and 'FALSE'
 *  2. Tests strings with positive/negative decimal numbers
 *  3. Tests with octal and hexadecimal numbers
 *  4. Tests with invalid bool strings
 *
 *=========================================================================*/
void Test_StringToBoolean(void) {
	DEFINE_FUNCTION("Test_StringToBoolean()");
	TCHAR TestString[101];
	bool Flag;
	bool Result;
	SystemLog.Printf(stdout, _T("============= Testing StringToBoolean() ===================="));
	/* Test the 'TRUE' string */
	TSTRCPY(TestString, _T("True"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test the 'FALSE' string */
	TSTRCPY(TestString, _T("FaLsE"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == false);
	/* Test the '0' decimal string */
	TSTRCPY(TestString, _T("0"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == false);
	/* Test the '1' decimal string */
	TSTRCPY(TestString, _T("1"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test the '-1' decimal string */
	TSTRCPY(TestString, _T("-1"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test the '103' decimal string */
	TSTRCPY(TestString, _T("103"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test an octal string */
	TSTRCPY(TestString, _T("05"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test a hexadecimal string */
	TSTRCPY(TestString, _T("0xf5"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result);
	ASSERT(Flag == true);
	/* Test with empty string */
	TSTRCPY(TestString, _T(""));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result == false);
	/* Test with invalid string */
	TSTRCPY(TestString, _T("asd9p8adsf"));
	Result = StringToBoolean(Flag, TestString);
	ASSERT(Result == false);
}

/*===========================================================================
 *      End of Function Test_StringToBoolean()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_StringChanged (void);
 *
 * Tests the StringChanged() function
 *  1. Tests all possible NULL cases.
 *  2. Check TRUE and FALSE regular cases with default case sensitivity.
 *  3. Check TRUE and FALSE regular cases with case sensitivity.
 *  4. Check TRUE and FALSE regular cases without case sensitivity.
 *  5. Check empty string cases
 *
 *=========================================================================*/
void Test_StringChanged(void) {
	DEFINE_FUNCTION("Test_StringChanged()");
	bool Result;
	SystemLog.Printf(stdout, _T("============= Testing StringChanged() ===================="));
	/* Check double-NULL case */
	Result = StringChanged(NULL, NULL);
	ASSERT(Result == FALSE);
	/* Check single-NULL case #1 */
	Result = StringChanged(NULL, _T("asd"));
	ASSERT(Result == TRUE);
	/* Check single-NULL case #2 */
	Result = StringChanged(_T("asd"), NULL);
	ASSERT(Result == TRUE);
	/* Check FALSE regular case with default case sensitivity */
	Result = StringChanged(_T("asd"), _T("ASD"));
	ASSERT(Result == FALSE);
	/* Check TRUE regular case with default case sensitivity */
	Result = StringChanged(_T("111"), _T("ASD"));
	ASSERT(Result == TRUE);
	/* Check FALSE regular case with case sensitivity */
	Result = StringChanged(_T("asd"), _T("asd"), TRUE);
	ASSERT(Result == FALSE);
	/* Check TRUE regular case with case sensitivity */
	Result = StringChanged(_T("ASD"), _T("asd"), TRUE);
	ASSERT(Result == TRUE);
	/* Check TRUE regular case with case sensitivity */
	Result = StringChanged(_T("111"), _T("ASD"), TRUE);
	ASSERT(Result == TRUE);
	/* Check FALSE regular case without case sensitivity */
	Result = StringChanged(_T("asd"), _T("asd"), FALSE);
	ASSERT(Result == FALSE);
	/* Check FALSE regular case without case sensitivity */
	Result = StringChanged(_T("ASD"), _T("asd"), FALSE);
	ASSERT(Result == FALSE);
	/* Check TRUE regular case without case sensitivity */
	Result = StringChanged(_T("111"), _T("ASD"), FALSE);
	ASSERT(Result == TRUE);
	/* Check empty string case */
	Result = StringChanged(_T("111"), _T(""));
	ASSERT(Result == TRUE);
	/* Check empty string case */
	Result = StringChanged(_T(""), _T(""));
	ASSERT(Result == FALSE);
}

/*===========================================================================
 *      End of Function Test_StringChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_IsStringNumber (void);
 *
 * Tests the IsStringNumber() function
 *  1. Checks several typical positive/negative cases
 *  2. Checks empty string case.
 *
 *=========================================================================*/
void Test_IsStringNumber(void) {
	DEFINE_FUNCTION("Test_IsStringNumber()");
	SystemLog.Printf(stdout, _T("============= Testing IsStringNumber() ===================="));
	/* Check several typical positive cases */
	ASSERT(IsStringNumber(_T("  123  ")) == TRUE);
	ASSERT(IsStringNumber(_T("16285")) == TRUE);
	ASSERT(IsStringNumber(_T("\t1 2 3 4 5 6 7 8 9 0 ")) == TRUE);
	/* Check several typical negative cases */
	ASSERT(IsStringNumber(_T("123.6")) == FALSE);
	ASSERT(IsStringNumber(_T("0xC5")) == FALSE);
	/* Check the empty string case */
	ASSERT(IsStringNumber(_T("")) == TRUE);
}

/*===========================================================================
 *      End of Function Test_IsStringNumber()
 *========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strhgt (void);
 *
 * Tests the strhgt() function
 *  1. Test with typical strings
 *  2. Test with empty string
  *
 *=========================================================================*/
void Test_strhgt(void) {
	DEFINE_FUNCTION("Test_strhgt()");
	SystemLog.Printf(stdout, _T("============= Testing strhgt() ===================="));
	/* Test several typical strings */
	ASSERT(strhgt(_T("Test String")) == 1);
	ASSERT(strhgt(_T("Test\nString")) == 2);
	ASSERT(strhgt(_T("\nTest\nString")) == 3);
	ASSERT(strhgt(_T("\n\nTest\nString")) == 4);
	ASSERT(strhgt(_T("Test\nString\n")) == 3);
	ASSERT(strhgt(_T("Test\nStri\nng")) == 3);
	/* Test with empty string */
	ASSERT(strhgt(_T("")) == 1);
	ASSERT(strhgt(_T("\n")) == 2);
	ASSERT(strhgt(_T("\n\n")) == 3);
}

/*===========================================================================
 *      End of Function Test_strhgt()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_stristr (void);
 *
 * Tests the stristr() function
 *  1. Test several typical positive/negative cases
 *  2. Check case insensitivity
 *  3. Check overlapping string case
 *  4. Check empty string cases
  *
 *=========================================================================*/
void Test_stristr(void) {
	DEFINE_FUNCTION("Test_stristr()");
	TCHAR *pStr;
	SystemLog.Printf(stdout, _T("============= Testing stristr() ===================="));
	/* Check several typical positive cases */
	pStr = stristr(_T("0123456789"), _T("45"));
	ASSERT(TSTRCMP(pStr, _T("456789")) == 0);
	pStr = stristr(_T("0123456789"), _T("01"));
	ASSERT(TSTRCMP(pStr, _T("0123456789")) == 0);
	pStr = stristr(_T("0123456789"), _T("789"));
	ASSERT(TSTRCMP(pStr, _T("789")) == 0);
	/* Check several typical negative cases */
	pStr = stristr(_T("0123456789"), _T("ab"));
	ASSERT(pStr == NULL);
	/* Check case insensitivity */
	pStr = stristr(_T("aBcDeFG"), _T("DEF"));
	ASSERT( _stricmp(pStr, _T("defg")) == 0);
	/* Check overlapping string case */
	pStr = stristr(_T("1111111234"), _T("11112"));
	ASSERT( _stricmp(pStr, _T("1111234")) == 0);
	/* Check empty string cases */
	pStr = stristr(_T(""), _T("111"));
	ASSERT(pStr == NULL);
}

/*===========================================================================
 *      End of Function Test_stristr()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strlicmp (void);
 *
 * Test the strlicmp() function
 *  1. Test with typical equality cases.
 *  2. Test several less-than cases
 *  3. Test several greater-than cases
 *  4, Check empty string cases
 *
 *=========================================================================*/
void Test_strlicmp(void) {
	DEFINE_FUNCTION("Test_strlicmp()");
	SystemLog.Printf(stdout, _T("============= Testing strlicmp() ===================="));
	/* Check several equal cases */
	ASSERT(strlicmp(_T("123"), _T("123")) == 0);
	ASSERT(strlicmp(_T("AsD"), _T("asd")) == 0);
	ASSERT(strlicmp(_T("123"), _T("1234567")) == 0);
	ASSERT(strlicmp(_T("1234567"), _T("123")) == 0);
	/* Check several less-than cases */
	ASSERT(strlicmp(_T("123"), _T("234")) < 0);
	ASSERT(strlicmp(_T("123"), _T("124")) < 0);
	/* Check several greater-than cases */
	ASSERT(strlicmp(_T("234"), _T("123")) > 0);
	ASSERT(strlicmp(_T("124"), _T("123")) > 0);
	/* Check empty string cases */
	ASSERT(strlicmp(_T("123"), _T("")) == 0);
	ASSERT(strlicmp(_T(""), _T("124")) == 0);
	ASSERT(strlicmp(_T(""), _T("")) == 0);
}

/*===========================================================================
 *      End of Function Test_strlicmp()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strlinelen (void);
 *
 * Tests the strlinelen() function
 *  1. Checks function with regular string with CR in middle/start/end
 *  2. Tests with string containing no CR
 *  3. Tests with empty string
 *  4. Tests with string with multiple CRs
 *
 *=========================================================================*/
void Test_strlinelen(void) {
	DEFINE_FUNCTION("Test_strlinelen()");
	TCHAR TestString[101];
	size_t Result;
	SystemLog.Printf(stdout, _T("============= Testing strlinelen() ===================="));
	/* Check with a regular string with CR in middle */
	TSTRCPY(TestString, _T("123456\n890"));
	Result = strlinelen(TestString);
	ASSERT(Result == 6);
	/* Check with a regular string with CR at end */
	TSTRCPY(TestString, _T("123456789\n"));
	Result = strlinelen(TestString);
	ASSERT(Result == 9);
	/* Check with a regular string with CR at start*/
	TSTRCPY(TestString, _T("\n234567890"));
	Result = strlinelen(TestString);
	ASSERT(Result == 0);
	/* Check with a regular string with no CR */
	TSTRCPY(TestString, _T("1234567890"));
	Result = strlinelen(TestString);
	ASSERT(Result == 10);
	ASSERT(Result == TSTRLEN(TestString));
	/* Check with a empty string  */
	TSTRCPY(TestString, _T(""));
	Result = strlinelen(TestString);
	ASSERT(Result == 0);
	/* Check with a regular string with multiple CRs */
	TSTRCPY(TestString, _T("12\n4\n6\n890"));
	Result = strlinelen(TestString);
	ASSERT(Result == 2);
}

/*===========================================================================
 *      End of Function Test_strlinelen()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strmaxlinelen (void);
 *
 * Tests the strmaxlinelen() function.
 *  1. Tests with typical strings
 *  2. Test with empty string
 *
 *=========================================================================*/
void Test_strmaxlinelen(void) {
	DEFINE_FUNCTION("Test_strmaxlinelen()");
	SystemLog.Printf(stdout, _T("============= Testing strmaxlinelen() ===================="));
	/* Test several typical strings */
	ASSERT(strmaxlinelen(_T("1234567890")) == 10);
	ASSERT(strmaxlinelen(_T("1\n234567890")) == 9);
	ASSERT(strmaxlinelen(_T("12345678\n90")) == 8);
	ASSERT(strmaxlinelen(_T("12\n34\n56\n78\n90")) == 2);
	ASSERT(strmaxlinelen(_T("123\n4567\n890")) == 4);
	ASSERT(strmaxlinelen(_T("\n\n\n")) == 0);
	ASSERT(strmaxlinelen(_T("\n1\n\n")) == 1);
	/* Test empty string */
	ASSERT(strmaxlinelen(_T("")) == 0);
}

/*===========================================================================
 *      End of Function Test_strmaxlinelen()
 *=========================================================================*/



/*===========================================================================
 *
 * Function - void Test_strnicmp (void);
 *
 * Tests the strnicmp() function
 *  1. Test with typical equal strings
 *  2. Test with typical less than strings
 *  3. Test with typical greater than strings
 *  4. Test with empty strings
 *
 *=========================================================================*/
void Test_strnicmp(void) {
	DEFINE_FUNCTION("Test_strnicmp()");
	SystemLog.Printf(stdout, _T("============= Testing strnicmp() ===================="));
#if !defined(__TURBOC__) && !defined(_WIN32)
	/* Test several equal strings */
	ASSERT(strnicmp(_T("123"), _T("123"), 5) == 0);
	ASSERT(strnicmp(_T("123"), _T("123"), 2) == 0);
	ASSERT(strnicmp(_T("abcdef123"), _T("ABCDEF"), 4) == 0);
	/* Test several less than strings */
	ASSERT(strnicmp(_T("123"), _T("234"), 5) < 0);
	ASSERT(strnicmp(_T("123"), _T("234"), 2) < 0);
	/* Test several greater than strings */
	ASSERT(strnicmp(_T("234"), _T("123"), 5) > 0);
	ASSERT(strnicmp(_T("234"), _T("123"), 2) > 0);
	/* Test several empty strings */
	ASSERT(strnicmp(_T("123"), _T(""), 5) > 0);
	ASSERT(strnicmp(_T(""), _T("234"), 2) < 0);
	ASSERT(strnicmp(_T(""), _T(""), 2) == 0);
#endif
}

/*===========================================================================
 *      End of Function Test_strnicmp()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strnncpy (void);
 *
 * Tests the strnncpy() function.
 *  1. Test with regular strings
 *  2. Test with short strings to ensure strings are NULL terminated
 *  3. Test with empty string
 *
 *=========================================================================*/
void Test_strnncpy(void) {
	DEFINE_FUNCTION("Test_strnncpy()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("============= Testing strnncpy() ===================="));
	/* Test a regular string copy */
	strnncpy(TestString, _T("123456789"), 50);
	ASSERT(TSTRCMP(TestString, _T("123456789")) == 0);
	/* Test a short string copy */
	strnncpy(TestString, _T("123456789"), 5);
	ASSERT(TSTRCMP(TestString, _T("12345")) == 0);
	/* Test an empty string copy */
	strnncpy(TestString, _T(""), 50);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}

/*===========================================================================
 *      End of Function Test_strnncpy()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strproper (void);
 *
 * Tests the string proper function.
 *  1. Test with several typical strings
 *  2. Test with empty string
 *  3. Test with string without whitespace
 *
 *=========================================================================*/
void Test_strproper(void) {
	DEFINE_FUNCTION("Test_strproper()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("============= Testing strproper() ===================="));
	/* Check several typical strings */
	TSTRCPY(TestString, _T("this is\ta  test"));
	ASSERT(TSTRCMP(strproper(TestString), _T("This Is\tA  Test")) == 0);
	TSTRCPY(TestString, _T("   test\nnew line  "));
	ASSERT(TSTRCMP(strproper(TestString), _T("   Test\nNew Line  ")) == 0);
	/* Check an empty string */
	TSTRCPY(TestString, _T(""));
	ASSERT(TSTRCMP(strproper(TestString), _T("")) == 0);
	/* Check a string without whitespace */
	TSTRCPY(TestString, _T("thisisastring"));
	ASSERT(TSTRCMP(strproper(TestString), _T("Thisisastring")) == 0);
}

/*===========================================================================
 *      End of Function Test_strproper()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_strupr (void);
 *
 * Tests the strupr()/strlwr() functions.
 *  1. Test strlwr() with typical strings
 *  2. Test strupr() with typical strings
 *
 *=========================================================================*/
void Test_strupr(void) {
	DEFINE_FUNCTION("Test_strupr()");
	SystemLog.Printf(stdout, _T("============= Testing strlwr()/strupr() ===================="));
#if !defined(__TURBOC__) && !defined(_WIN32)
	TCHAR TestString[101];
	/* Test strlwr() with typical strings */
	TSTRCPY(TestString, _T("ABCD 123 abcd"));
	ASSERT(TSTRCMP(strlwr(TestString), _T("abcd 123 abcd")) == 0);
	TSTRCPY(TestString, _T(""));
	ASSERT(TSTRCMP(strlwr(TestString), _T("")) == 0);
	/* Test strupr() with typical strings */
	TSTRCPY(TestString, _T("ABCD 123 abcd"));
	ASSERT(TSTRCMP(strupr(TestString), _T("ABCD 123 ABCD")) == 0);
	TSTRCPY(TestString, _T(""));
	ASSERT(TSTRCMP(strupr(TestString), _T("")) == 0);
#endif
}

/*===========================================================================
 *      End of Function Test_strupr()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_vsnprintf (void);
 *
 * Tests the vsnprintf() as well as the snprintf() functions.  Note that
 * the snprintf() function is based on the vsnprintf() function,
 *  1. Test a plain string and ensure correct output
 *  2. Test outputting more than allowed string length
 *
 *=========================================================================*/
void Test_vsnprintf(void) {
	DEFINE_FUNCTION("Test_vsnprintf()");
	TCHAR TestString[] = _T("This is a test string...\n\r 1010 kkasdlkj");
	TCHAR OutputString[1024];
	TCHAR *pShortString;
	int Result;
	SystemLog.Printf(stdout, _T("============= Testing vsnprintf() ===================="));
	ASSERT(DebugHeapCheckMemory());
	/* Check basic function of snprintf() (and thus vsnprintf()) */
	Result = snprintf(OutputString, 1000, _T("%s"), TestString);
	ASSERT(Result > 0);
	ASSERT(Result == (int)TSTRLEN(TestString));
	ASSERT(TSTRCMP(OutputString, TestString) == 0);
	Result = snprintf(OutputString, 1000, TestString);
	ASSERT(Result > 0);
	ASSERT(Result == (int)TSTRLEN(TestString));
	ASSERT(TSTRCMP(OutputString, TestString) == 0);
	Result = snprintf(OutputString, 1000, _T("This %s, 101 = %d"), _T("is a test"), 101);
	ASSERT(Result > 0);
	SystemLog.Printf(stdout, _T("snprintf() Output: %s"), OutputString);
	/* Check outputting more than allowed characters */
	Result = snprintf(OutputString, 5, _T("Testing maximum 5 characters"));
	ASSERT(Result < 0);
	SystemLog.Printf(stdout, _T("snprintf(5) Output 1: %s"), OutputString);
	pShortString = CreateString(6);
	Result = snprintf(pShortString, 5, _T("Testing max 5 characters"));
	ASSERT(Result < 0);
	SystemLog.Printf(stdout, _T("snprintf(5) Output 2: %s"), pShortString);
	/* Check memory if nessecary */
	ASSERT(DebugHeapCheckMemory());
	DestroyPointer(pShortString);
}

/*===========================================================================
 *      End of Function Test_vsnprintf()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_DLStr (void);
 *
 * Tests all the functions in this module.
 *  1. Tests the vsnprintf() and snprintf() functions
 *  2. Tests the CountSubstrings() function
 *  3. Tests the ltrim() and rtrim() functions
 *  4. Tests the strlinelen() function
 *  5. Tests the SeperateVarValue() function
 *  6. Tests the StringToBoolean() function
 *  7. Tests the StringChanged() function
 *  8. Tests the IsStringNumber() function
 *  9. Tests the stristr() function
 *  10.Tests the strlicmp() function
 *  11. Tests the strproper() function
 *  12. Tests the strhgt() function
 *  13. Tests the strmaxlinelen() function
 *  14. Tests the strupr()/strlwr() functions
 *  15. Tests the strnicmp() function
 *
 *=========================================================================*/
void Test_DLStr(void) {
	//DEFINE_FUNCTION("Test_DLStr()");
	Test_vsnprintf();
	Test_CountSubstrings();
	Test_ltrim();
	Test_rtrim();
	Test_strlinelen();
	Test_SeperateVarValue();
	Test_StringToBoolean();
	Test_StringChanged();
	Test_IsStringNumber();
	Test_stristr();
	Test_strlicmp();
	Test_strnncpy();
	Test_strproper();
	Test_strhgt();
	Test_strmaxlinelen();
	Test_strupr();
	Test_strnicmp();
}

/*===========================================================================
 *      End of Function Test_DLStr()
 *=========================================================================*/

/* Restore compiler warning options */
#if defined(__BCPLUSPLUS__)
	#pragma warn .rch
	#pragma warn .ccc
#endif

#endif
/*===========================================================================
 *      End of Module Test Routines
 *=========================================================================*/
