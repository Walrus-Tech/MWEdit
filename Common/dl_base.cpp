/*===========================================================================
 *
 * File:    DL_Base.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Sunday, April 01, 2001
 *
 * Implements common functions for Dave's Library of common code.
 *
 *=========================================================================*/

/* Include Files */
#include "dl_base.h"
#include "dl_err.h"


/*===========================================================================
 *
 * Begin Local Variables
 *
 *=========================================================================*/
DEFINE_FILE("DL_Base.cpp");

/* The current path seperator character (usually '\\' or '/') */
TCHAR LocalePathChar = '\\';

/* Local variables used by the new qsort() algorithim */
long l_QSortUserData = 0;
PQSORT_CMPFUNC l_QSortCmpFunc = NULL;

/* Global variable used to eliminate errors from not using the
   DEFINE_FUNCTION() macro (for DEBUG builds only) */
#if defined(_DEBUG)
	TCHAR ThisFunction[] = _T("?");
#endif

/*===========================================================================
 *      End of Local Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void CustomAssert (pString, pFile, pFunction, Line);
 *
 * A custom assertion type function used by the ASSERT macro defined in
 * DL_BASE.H.  Accepts a message string, file name, function name, and
 * line number where the assertion occurred. Outputs message to stderr.
 * Exits program with abort().
 *
 *=========================================================================*/
void CustomAssert (const TCHAR* pString, const TCHAR* pFile,
                   const TCHAR* pFunction, const long Line) {
	//DEFINE_FUNCTION("CustomAssert()");
	/* TODO: Hack to ensure we reset to text mode under MSDOS in
	 * case we are in a graphics mode. */
#if defined(__MSDOS__)
	ASM {
		mov ax, 03h
		int 10h
	};
#endif

	/* Output message to log file */
	if (SystemLog.IsOpen()) {
		SystemLog.Printf (_T("ASSERTION FAILED: '%s'"), pString);
		SystemLog.Printf (_T("     File: '%s'"), pFile);
		SystemLog.Printf (_T("     Func: '%s'"), pFunction);
		SystemLog.Printf (_T("     Line: %ld"), Line);
	}

	/* Display a message box under Borland */
#if defined(__BCPLUSPLUS__) || defined(_WIN32)
	ErrorHandler.Printf (_T("Application Assert!"),
	                     _T("ASSERTION FAILED: '%s'\r\n\tFile: '%s'\r\n\tFunc: '%s'\r\n\tLine: %ld\r\nAborting Program!"),
	                     pString, pFile, pFunction, Line);
#else
	fprintf (stderr, _T("ASSERTION FAILED: '%s'\r\n"), pString);
	fprintf (stderr, _T("\tFile: '%s'\r\n"), pFile);
	fprintf (stderr, _T("\tFunc: '%s'\r\n"), pFunction);
	fprintf (stderr, _T("\tLine: %ld\r\n"), Line);
	fflush(stderr);
#endif
	/* Abort program */
#if defined(_WIN32_WCE)
	exit(0);
#else
	abort();
#endif
}

/*===========================================================================
 *      End of Function CustomAssert()
 *=========================================================================*/



#if defined(__TURBOC__) && !defined(__BCPLUSPLUS__)
/*===========================================================================
 *
 * Function - void throw (pString);
 *
 * A custom throw function only used when the system has no exception
 * handling capability.  Calls the ErrorHandler.Exit() function to abort
 * the program.
 *
 *=========================================================================*/
void throw (const TCHAR* pString) {
	ErrorHandler.Exit(pString);
}

/*===========================================================================
 *      End of Function throw()
 *=========================================================================*/
#endif

#if !defined(_WIN32_WCE)
/*===========================================================================
 *
 * Function - void qsort (pBase, NumElements, ElementWidth, pCmpFunc, lUserData);
 *
 * Same as the standard qsort() algorithm except it takes an extended
 * UserData parameter which is passed onto the user supplied compare
 * function.  This allows one compare function to sort a variety of
 * ways depending on the lUserData parameter.  Uses the standard qsort()
 * algorithim and local variables.
 *
 *=========================================================================*/
void qsort (void* pBase, size_t NumElements, size_t ElementWidth,
            PQSORT_CMPFUNC pCmpFunc, long lUserData) {
	DEFINE_FUNCTION("qsort()");
	/* Ensure valid input */
	ASSERT(pCmpFunc != NULL);
	/* Save the extended parameters to local variables */
	l_QSortCmpFunc = pCmpFunc;
	l_QSortUserData = lUserData;
	/* Call the standard qsort() algorithm with our inline compare function */
	qsort(pBase, NumElements, ElementWidth, l_QSortCompare);
}

/*===========================================================================
 *      End of Function qsort()
 *=========================================================================*/
#endif


