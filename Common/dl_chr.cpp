/*===========================================================================
 *
 * File:    DL_Chr.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Sunday, May 06, 2001
 *
 * Implementation of character related functions for Dave's Library of
 * common code.
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *  - Moved from regular char to TCHAR type to support wide characters
 *    under Windows. Successfully tested.
 *
 *=========================================================================*/

#include "dl_chr.h"
#include <ctype.h>


DEFINE_FILE("DL_Chr.h");


/*===========================================================================
 *
 * Function - void chradd (pString, CharIndex, NewChar);
 *
 * Attempts to insert the specified character into the string at the
 * given position CharIndex.  First character in string is at position 0.
 * Assumes the string is long enough to add another character.  ASSERTs
 * if any invalid input is received.
 *
 *=========================================================================*/
void chradd(TCHAR *pString, const size_t CharIndex, const TCHAR NewChar) {
	DEFINE_FUNCTION("chradd()");
	TCHAR *pInsertPosition;
	size_t StringLength;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	StringLength = TSTRLEN(pString);
	ASSERT(CharIndex <= StringLength);
	/* Shift the characters after insert position right by one */
	pInsertPosition = pString + CharIndex;
	memmove (pInsertPosition + 1, pInsertPosition, (StringLength - CharIndex + 1) * sizeof(TCHAR));
	/* Add the new character to the string */
	*pInsertPosition = NewChar;
}


/*===========================================================================
 *
 * Function - void chrcat (TCHAR* pString, const TCHAR NewChar);
 *
 * Attempts to add a character to the end of the given string.  Assumes
 * that the string is long enough to add another character.  ASSERTs if
 * any bad input is received.
 *
 *=========================================================================*/
void chrcat(TCHAR *pString, const TCHAR NewChar) {
	DEFINE_FUNCTION("chrcat()");
	TCHAR *pInsertPosition;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Find the end of the string */
	pInsertPosition = pString + TSTRLEN(pString);
	/* Add the character to end of string, making sure we NULL terminate */
	pInsertPosition[1] = NULL_CHAR;
	pInsertPosition[0] = NewChar;
}


/*===========================================================================
 *
 * Function - int chrcount (pString, Char);
 *
 * Counts the number of characters in the given string.  ASSERTs if given
 * invalid input.
 *
 *=========================================================================*/
int chrcount(const TCHAR *pString, const TCHAR Char) {
	DEFINE_FUNCTION("chrcount()");
	int Count = 0;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	while (*pString != NULL_CHAR) {
		if (*pString == Char) {
			Count++;
		}

		pString++;
	}

	return Count;
}


/*===========================================================================
 *
 * Function - void chrdel (pString, CharIndex);
 *
 * Attempts to delete the character at the given position from the string.
 * Position 0 is the first character in the string.  ASSERTs on any bad
 * input.
 *
 *=========================================================================*/
void chrdel(TCHAR *pString, const size_t CharIndex) {
	DEFINE_FUNCTION("chrdel()");
	TCHAR *pDeletePosition;
	size_t StringLength;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	StringLength = TSTRLEN(pString);
	ASSERT(CharIndex <= StringLength);
	/* Shift the characters left of the deletion position by one */
	pDeletePosition = pString + CharIndex;
	memmove (pDeletePosition, pDeletePosition + 1, (StringLength - CharIndex) * sizeof(TCHAR));
}


/*===========================================================================
 *
 * Function - void chrdellast (pString);
 *
 * Deletes the last character from the string. ASSERTs on bad input.
 *
 *=========================================================================*/
void chrdellast(TCHAR *pString) {
	DEFINE_FUNCTION("chrdellast()");
	size_t StringLength;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Find last character in string, and ensure at least one exists */
	StringLength = TSTRLEN(pString);

	/* Delete the last character in the string, if any */
	if (StringLength > 0) {
		pString[StringLength - 1] = NULL_CHAR;
	}
}


/*===========================================================================
 *
 * Function - boolean chrrpunc (CharIndex, pString);
 *
 * Looks for the first punctuation character from the end of the string.
 * Saves the character index if one is found (0 is the first character
 * in the string) and returns TRUE.  Returns FALSE if no matching character
 * was found.  ASSERTs on bad input.
 *
 *=========================================================================*/
boolean chrrpunc(size_t &CharIndex, const TCHAR *pString) {
	DEFINE_FUNCTION("chrrpunc()");
	size_t StringPosition;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Start at the end of the string */
	StringPosition = TSTRLEN(pString);

	/* Look for a punctuating character until start of string is reached */
	while (StringPosition != 0) {
		StringPosition--;

		if (ispunct(pString[StringPosition])) {
			CharIndex = StringPosition;
			return TRUE;
		}
	}

	/* character not found in string */
	return FALSE;
}


/*===========================================================================
 *
 * Function - TCHAR* chrtok (pString, TokenChar);
 *
 * Seperates the given string into substrings divided by the given token
 * character, as strtok().  Returns NULL when no substrings are
 * left.  Uses an internal static variable which prevents use of nesting
 * chrtok() calls.  ASSERTs on invalid input.  The TokenTCHAR cannot be
 * the terminating NULL character.
 *
 * Unlike strtok(), chrtok() ignores multiple occurences of the TokenTCHAR,
 * for example, the TestString "11x22x33xxx44"
 *  strtok(TestString, "x") = "11", "22", "33", "44"
 *  chrtok(TestString, 'x') = "11", "22", "33", "", "", "44"
 * The use is otherwise identical to strok().
 *
 *=========================================================================*/
TCHAR *chrtok(TCHAR *pString, const TCHAR TokenChar) {
	DEFINE_FUNCTION("chrtok()");
	static TCHAR *pParse = NULL;
	TCHAR *pSearchChar;
	TCHAR *pResult;
	/* Ensure valid input */
	ASSERT(TokenChar != NULL_CHAR);

	/* Check for end of parsed token string */
	if (pString == NULL && pParse == NULL) {
		return NULL;
	}

	/* Start parsing a new string */
	if (pString != NULL) {
		pParse = pString;
	}

	/* Search for the next substring */
	pSearchChar = TSTRCHR(pParse, TokenChar);

	/* No more substrings */
	if (pSearchChar == NULL) {
		pResult = pParse;
		pParse = NULL;
		return pResult;
	}

	/* Terminate substring */
	*pSearchChar = NULL_CHAR;
	pResult = pParse;
	pParse = pSearchChar + 1;
	return pResult;
}


/*===========================================================================
 *
 * Function - TCHAR* chrtrunc (pString, TruncateChar);
 *
 * Truncates the character at the first occurence of the given character.
 * Returns the string.  ASSERTs if given invalid input.
 *
 *=========================================================================*/
TCHAR *chrtrunc(TCHAR *pString, const TCHAR TruncateChar) {
	DEFINE_FUNCTION("chrtrunc()");
	TCHAR *pFindChar;
	/* Ensure valid input */
	ASSERT(pString != NULL && TruncateChar != NULL_CHAR);
	/* Attempt to find the first truncation character */
	pFindChar = TSTRCHR(pString, TruncateChar);

	if (pFindChar != NULL) {
		*pFindChar = NULL_CHAR;
	}

	return pString;
}


/*===========================================================================
 *
 * Function - TCHAR* chrrtrunc (pString, TruncateChar);
 *
 * Truncates the character at the last occurence of the given character.
 * Returns the string.  ASSERTs if given invalid input.
 *
 *=========================================================================*/
TCHAR *chrrtrunc(TCHAR *pString, const TCHAR TruncateChar) {
	DEFINE_FUNCTION("chrrtrunc()");
	TCHAR *pFindChar;
	/* Ensure valid input */
	ASSERT(pString != NULL && TruncateChar != NULL_CHAR);
	/* Attempt to find the last truncation character */
	pFindChar = TSTRRCHR(pString, TruncateChar);

	if (pFindChar != NULL) {
		*pFindChar = NULL_CHAR;
	}

	return pString;
}


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 * Test routines for the functions in this module.  Only defined in
 * DEBUG builds.
 *
 *=========================================================================*/
#if defined(_DEBUG)


/*===========================================================================
 *
 * Function - void Test_chradd (void);
 *
 * Tests the chradd() function.
 *  1. Ensures characters are correctly inserted in middle of string
 *  2. Check adding characters at start of string
 *  3. Check adding characters at end of string
 *
 *=========================================================================*/
void Test_chradd() {
	DEFINE_FUNCTION("Test_chradd()");
	TCHAR TestString[101] = _T("123456789");
	SystemLog.Printf(stdout, _T("============= Testing chradd() ===================="));
	/* Add a character in the middle of the string */
	chradd(TestString, 4, '4');
	ASSERT(TSTRCMP(TestString, _T("1234456789")) == 0);
	/* Add a character at the start of the string */
	chradd(TestString, 0, '0');
	ASSERT(TSTRCMP(TestString, _T("01234456789")) == 0);
	/* Add a character at the end of the string */
	chradd(TestString, 11, '0');
	ASSERT(TSTRCMP(TestString, _T("012344567890")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_chrcat (void);
 *
 * Test the chrcat() function.
 *  1. Tests adding a character to a regular string.
 *  2. Tests adding a character to an empty string.
 *
 *=========================================================================*/
void Test_chrcat() {
	DEFINE_FUNCTION("Test_chrcat()");
	TCHAR TestString[101] = _T("123456789");
	SystemLog.Printf(stdout, _T("============= Testing chrcat() ===================="));
	/* Test adding character to regular string */
	chrcat(TestString, '0');
	ASSERT(TSTRCMP(TestString, _T("1234567890")) == 0);
	/* Test adding character to empty string */
	TestString[0] = NULL_CHAR;
	chrcat(TestString, '0');
	ASSERT(TSTRCMP(TestString, _T("0")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_chrdel (void);
 *
 * Tests the chrdel() function
 *  1. Deletes characters from middle of regular string.
 *  2. Delete characters from start/end of string
 *  3. Test empty string deletion
 *
 *=========================================================================*/
void Test_chrdel() {
	DEFINE_FUNCTION("Test_chrdel()");
	TCHAR TestString[101] = _T("123456789");
	SystemLog.Printf(stdout, _T("============= Testing chrdel() ===================="));
	/* Delete characters from middle of string */
	chrdel(TestString, 4);
	ASSERT(TSTRCMP(TestString, _T("12346789")) == 0);
	/* Delete characters from end of string */
	chrdel(TestString, 7);
	ASSERT(TSTRCMP(TestString, _T("1234678")) == 0);
	/* Delete characters from start of string */
	chrdel(TestString, 0);
	ASSERT(TSTRCMP(TestString, _T("234678")) == 0);
	/* Delete character from empty string */
	TestString[0] = NULL_CHAR;
	chrdel(TestString, 0);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_chrdellast (void);
 *
 * Tests the chrdellast() function.
 *  1. Delete the last character from a regular string
 *  2. Delete character from empty string.
 *
 *=========================================================================*/
void Test_chrdellast() {
	DEFINE_FUNCTION("Test_chrdellast()");
	TCHAR TestString[101] = _T("123456789");
	SystemLog.Printf(stdout, _T("============= Testing chrdellast() ===================="));
	/* Delete characters from regular of string */
	chrdellast(TestString);
	ASSERT(TSTRCMP(TestString, _T("12345678")) == 0);
	/* Delete character from empty string */
	TestString[0] = NULL_CHAR;
	chrdellast(TestString);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_chrtok (void);
 *
 * Tests the chrtok() function.
 *  1. Test a regular string, comparing results with strtok()
 *  2. Check the function enhanced cabapility.
 *
 *=========================================================================*/
void Test_chrtok() {
	DEFINE_FUNCTION("Test_chrtok()");
	TCHAR TestString1[] = _T("111x222x333x444x555");
	TCHAR TestString2[] = _T("111x222x333x444x555");
	TCHAR *pChrPtr;
	TCHAR *pStrPtr;
	SystemLog.Printf(stdout, _T("============= Testing chrtok() ===================="));
	/* Compare chrtok() results with strtok() for a normal string */
	pChrPtr = chrtok(TestString1, 'x');
	pStrPtr = TSTRTOK(TestString2, _T("x"));

	while (pChrPtr != NULL && pStrPtr != NULL) {
		SystemLog.Printf (_T("\t chrtok() / strtok() = %s / %s"), pChrPtr, pStrPtr);
		ASSERT(TSTRCMP(pChrPtr, pStrPtr) == 0);
		pChrPtr = chrtok(NULL, 'x');
		pStrPtr = TSTRTOK(NULL, _T("x"));
	}

	ASSERT(pChrPtr == NULL && pStrPtr == NULL);
	/* Test the enhanced feature of chrtok() */
	TSTRCPY (TestString1, _T("111x222xx333xx"));
	pChrPtr = chrtok(TestString1, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("111")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("222")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("333")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(TSTRCMP(pChrPtr, _T("")) == 0);
	pChrPtr = chrtok(NULL, 'x');
	ASSERT(pChrPtr == NULL);
}


/*===========================================================================
 *
 * Function - void Test_chrrpunc (void);
 *
 * Tests the chrrpunc() function.
 *  1. Ensures the function finds a punctuation in middle/start/end of string
 *  2. Check multiple punctuation case
 *  3. Check case where string contains no punctuation
 *  4. Check empty string case.
 *
 *=========================================================================*/
void Test_chrrpunc() {
	DEFINE_FUNCTION("Test_chrrpunc()");
	TCHAR TestString[101] = _T("0123=5678");
	boolean Result;
	size_t TCHARIndex;
	SystemLog.Printf(stdout, _T("============= Testing chrrpunc() ===================="));

	/* Test for punctuation in middle of string */
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result);
	ASSERT(TCHARIndex == 4);

	/* Test for punctuation at end of string */
	TSTRCPY (TestString, _T("012345678."));
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result);
	ASSERT(TCHARIndex == 9);

	/* Test for punctuation at start of string */
	TSTRCPY (TestString, _T(".123456789"));
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result);
	ASSERT(TCHARIndex == 0);

	/* Test for multiple punctuations in of string */
	TSTRCPY (TestString, _T("01234.67.0"));
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result);
	ASSERT(TCHARIndex == 8);

	/* Test for no punctuation in string */
	TSTRCPY (TestString, _T("0123456789"));
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result == FALSE);

	/* Test empty string case */
	TSTRCPY (TestString, _T(""));
	Result = chrrpunc(TCHARIndex, TestString);
	ASSERT(Result == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_chrtrunc (void);
 *
 * Tests the chrtrunc() function.
 *  1. Test function with regular string with truncation character in
 *     middle/start/end of string
 *  2. Check with no truncation character in string
 *  3. Test with empty string
 *
 *=========================================================================*/
void Test_chrtrunc() {
	DEFINE_FUNCTION("Test_chrtrunc()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("============= Testing chrtrunc() ===================="));

	/* Check with truncation character in middle of string */
	TSTRCPY(TestString, _T("123456789"));
	chrtrunc(TestString, '5');
	ASSERT(TSTRCMP(TestString, _T("1234")) == 0);

	/* Check with truncation character at end of string */
	TSTRCPY(TestString, _T("123456789"));
	chrtrunc(TestString, '9');
	ASSERT(TSTRCMP(TestString, _T("12345678")) == 0);

	/* Check with truncation character at start of string */
	TSTRCPY(TestString, _T("123456789"));
	chrtrunc(TestString, '1');
	ASSERT(TSTRCMP(TestString, _T("")) == 0);

	/* Check with no truncation character in string */
	TSTRCPY(TestString, _T("123456789"));
	chrtrunc(TestString, 'a');
	ASSERT(TSTRCMP(TestString, _T("123456789")) == 0);

	/* Check with empty string */
	TSTRCPY(TestString, _T(""));
	chrtrunc(TestString, '5');
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_chrtrunc (void);
 *
 * Tests the chrrtrunc() function.
 *  1. Test function with regular string with truncation character in
 *     middle/start/end of string
 *  2. Check with no truncation character in string
 *  3. Test with empty string
 *
 *=========================================================================*/
void Test_chrrtrunc() {
	DEFINE_FUNCTION("Test_chrrtrunc()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("============= Testing chrrtrunc() ===================="));

	/* Check with truncation character in middle of string */
	TSTRCPY(TestString, _T("123456789"));
	chrrtrunc(TestString, '5');
	ASSERT(TSTRCMP(TestString, _T("1234")) == 0);

	/* Check with truncation character at end of string */
	TSTRCPY(TestString, _T("123456789"));
	chrrtrunc(TestString, '9');
	ASSERT(TSTRCMP(TestString, _T("12345678")) == 0);

	/* Check with truncation character at start of string */
	TSTRCPY(TestString, _T("123456789"));
	chrrtrunc(TestString, '1');
	ASSERT(TSTRCMP(TestString, _T("")) == 0);

	/* Check with no truncation character in string */
	TSTRCPY(TestString, _T("123456789"));
	chrrtrunc(TestString, 'a');
	ASSERT(TSTRCMP(TestString, _T("123456789")) == 0);

	/* Check with empty string */
	TSTRCPY(TestString, _T(""));
	chrrtrunc(TestString, '5');
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_DLChr (void);
 *
 * Tests all the functions in this module.
 *  1. Tests the chradd() function
 *  2. Tests the chrcat() function
 *  3. Tests the chrdel() and chrdellast() functions
 *  4. Tests the chrtok() function
 *  5. Tests the chrrpunc() function
 *  6. Tests the chrtrunc() and chrrtrunc() functions
 *
 *=========================================================================*/
void Test_DLChr() {
	//DEFINE_FUNCTION("Test_DLChr()");
	Test_chradd();
	Test_chrcat();
	Test_chrdel();
	Test_chrdellast();
	Test_chrtok();
	Test_chrrpunc();
	Test_chrtrunc();
	Test_chrrtrunc();
}


#endif
