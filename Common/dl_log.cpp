/*===========================================================================
 *
 * File:    DL_Log.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, April 02, 2001
 *
 * Implements the CLogFile class for handling output to a simple log file
 * for debugging purposes.  Note that this module should not use the
 * ErrorHandler for noting errors as the CErrorHandler class uses the
 * CLogFile class, causing possible infinite loops.
 *
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *  - Moved from regular char to TCHAR type to support wide characters
 *    under Windows. Successfully tested.
 *
 *=========================================================================*/

/* Include Files */
#include "dl_log.h"
#include "dl_mem.h"
#if !defined(_WIN32_WCE)
	#include <time.h>
#endif


/*===========================================================================
 *
 * Begin Global Variables
 *
 *=========================================================================*/

/* The main log file for debugging output */
CLogFile SystemLog;

/*===========================================================================
 *      End of Global Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Variables
 *
 *=========================================================================*/
DEFINE_FILE("DL_log.cpp");
/*===========================================================================
 *      End of Local Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Constructor (Default)
 *
 *=========================================================================*/
CLogFile::CLogFile(void) {
	TabLevel = 0;
	pLogFileHandle = NULL;
	pHookProc = NULL;
}

/*===========================================================================
 *      End of Class CLogFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Constructor - CLogFile (pFilename, AppendFile);
 *
 * Attempts to open the given filename as the current logfile.  Accepts
 * input as per the Open() class method.
 *
 *=========================================================================*/
CLogFile::CLogFile(const TCHAR *pFilename, const logmode_t AppendFile) {
	/* Initialize the class members */
	TabLevel = 0;
	pLogFileHandle = NULL;
	pHookProc = NULL;
	/* Attempt to open log file */
	Open(pFilename, AppendFile);
}

/*===========================================================================
 *      End of Class CLogFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool Close (void);
 *
 * Closes the log file, if currently open.  Returns TRUE on success or FALSE
 * if no log file is currently open.
 *
 *=========================================================================*/
bool CLogFile::Close(void) {
	//DEFINE_FUNCTION("CLogFile::Close()");
	int Result;

	/* Is the log file currently open? */
	if (!IsOpen()) {
		return (FALSE);
	}

	/* Output status messages to log file */
	Printf(_T("Closing Log File..."));
	OutputMemoryStatus();
	/* Close log file and reset parameters */
	Result = fclose(pLogFileHandle);
	pLogFileHandle = NULL;
	TabLevel = 0;

	if (Result < 0) {
		return (FALSE);
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CLogFile::Close()
 *=========================================================================*/


#if defined(_DEBUG)
/*===========================================================================
 *
 * Class CLogFile Method - void DebugPrintf (const TCHAR* pString, ...);
 *
 * Outputs a printf() formatted message to the log file but only in
 * debug builds.  Compiles to a NULL inline function for release builds.
 * Otherwise is identical to the Printf() method.
 *
 *=========================================================================*/
void CLogFile::DebugPrintf(const TCHAR *pString, ...) {
	DEFINE_FUNCTION("CLogFile::DebugPrintf()");
	va_list Args;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Ensure the log file is currently open */
	if (!IsOpen()) {
		return;
	}

	/* Print the line to the file */
	va_start(Args, pString);
	(pString, Args);
	va_end(Args);
}

/*===========================================================================
 *      End of Class Method CLogFile::DebugPrintf()
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Class CLogFile Method - void DecrementTabs (void)
 *
 * Decreases the current tab level by one if possible.  The tab level
 * indicates how many tags preceed each line output to the log file,
 * allowing simple formatting of the output for easier viewing.
 *
 * See also:    CLogFile::IncrementTabs();
 *      CLogFile::SetTabLevel(NewTabLevel);
 *
 *=========================================================================*/
void CLogFile::DecrementTabs(void) {
	if (TabLevel > 0) {
		TabLevel--;
	}
}

/*===========================================================================
 *      End of Class Method CLogFile::DecrementTabs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - void IncrementTabs (void)
 *
 * Increases the current tab level by one if possible.  The tab level
 * indicates how many tags preceed each line output to the log file,
 * allowing simple formatting of the output for easier viewing.
 *
 * See also:    CLogFile::DecrementTags();
 *      CLogFile::SetTabLevel(NewTabLevel);
 *
 *=========================================================================*/
void CLogFile::IncrementTabs(void) {
	if (TabLevel < LOGFILE_MAX_TABS) {
		TabLevel++;
	}
}

/*===========================================================================
 *      End of Class Method CLogFile::IncrementTabs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool Open (pFilename, AppendFile);
 *
 * Attempts to create a log file using the given filename.  Any current
 * log file is closed.  If the AppendFile flag is LOG_APPEND (the default
 * is LOG_OPEN) and the log file currently exists, log entries will be
 * appended to the end of the file.  If AppendFile is FALSE, the log
 * file will be overwritten if it exists (the default).  Returns TRUE
 * if the log file was successfully opened.
 *
 *=========================================================================*/
bool CLogFile::Open(const TCHAR *pFilename, const logmode_t AppendFile) {
	DEFINE_FUNCTION("CLogFile::Open()");
	bool Result;
	/* Check for valid input */
	ASSERT(pFilename != NULL);
	ASSERT(*pFilename != NULL_CHAR);

	/* Ensure the current log file is closed */
	if (IsOpen()) {
		Result = Close();

		if (!Result) {
			return (FALSE);
		}
	}

	/* Attempt to open file for output, depending on the append flag */
	pLogFileHandle = TFOPEN(pFilename, AppendFile ? _T("at") : _T("wt"));

	if (pLogFileHandle == NULL) {
		return (FALSE);
	}

	/* Output the filename and full date to log file */
	Result = Printf(_T("==================== Opened Logfile %s ================"), pFilename);

	if (!Result) {
		return (FALSE);
	}

	return (OutputDate());
}

/*===========================================================================
 *      End of Class Method CLogFile::Open()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool OutputDate (void);
 *
 * Outputs the full date and time to the log file.  Returns FALSE on any
 * error.
 *
 *=========================================================================*/
bool CLogFile::OutputDate(void) {
	//DEFINE_FUNCTION("CLogFile::OutputDate()");
	TCHAR DateString[33] = _T("");
	struct tm *pCurrentTime;
	time_t Today;

	/* Ensure the log file is currently open */
	if (!IsOpen()) {
		return (FALSE);
	}

	/* Get the current Date and convert it to local time */
	time(&Today);
	pCurrentTime = localtime(&Today);

	if (pCurrentTime == NULL) {
		return (FALSE);
	}

	/* Output the date line to the file */
	TSTRFTIME(DateString, 32, _T("%A, %d of %B, %Y"), pCurrentTime);
	return (Printf(_T("The current date is %s."), DateString));
}

/*===========================================================================
 *      End of Class Method CLogFile::OutputDate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool OutputCurrentTime (void)
 *
 * This protected class method outputs the current time to the log file
 * in the format:  "HH:MM:SS - "
 * Assumes that the log file is currently open and valid.
 *
 *=========================================================================*/
bool CLogFile::OutputCurrentTime(void) {
	DEFINE_FUNCTION("CLogFile::OutputCurrentTime()()");
	TCHAR TimeString[17] = _T("");
	int Result;
	time_t CurrentTime;
	struct tm *pToday;
	/* Ensure a valid log file handle */
	ASSERT(pLogFileHandle != NULL);
	/* Get the current local time and ensure its valid */
	time(&CurrentTime);
	pToday = localtime(&CurrentTime);

	if (pToday == NULL) {
		return (FALSE);
	}

	/* Output the formatted time to log file */
	TSTRFTIME(TimeString, 16, _T("%H:%M:%S"), pToday);
	Result = TFPRINTF(pLogFileHandle, _T("%s (%ld) - "), TimeString, clock());

	if (Result < 0) {
		return (FALSE);
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CLogFile::OutputCurrentTime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - void OutputMemoryStatus (void);
 *
 * Outputs the current memory status to the log file.
 *
 *=========================================================================*/
void CLogFile::OutputMemoryStatus(void) {
	//DEFINE_FUNCTION("CLogFile::OutputMemoryStatus()");
	bool MemResult;
	long UsedMemory = 0;
	long FreeMemory = 0;
	long TotalMemory = 0;
	/* Attempt to retrieve current memory usage */
	MemResult = GetUsedMemory(UsedMemory);

	if (MemResult) {
		MemResult = GetFreeMemory(FreeMemory);
	}

	if (MemResult) {
		MemResult = GetTotalMemory(TotalMemory);
	}

	if (MemResult) {
		Printf(_T("Used/Free/Total Memory: %lu/%lu/%lu bytes"), UsedMemory, FreeMemory, TotalMemory);
	} else {
		Printf(_T("Error attempting to retrieve memory usage!"));
	}

	/* Output heap information */
#if defined(_DEBUG)
	DebugPrintf(_T("DebugHeapCheckMemory() returns %s"),
	            DebugHeapCheckMemory() ? _T("TRUE") : _T("FALSE"));
#endif
	Printf(_T("Heap Status: %s"), GetHeapStatusString());
	/* Output custom heap information */
#if defined(_DEBUG)
	OutputBlockInfo();
#endif
}

/*===========================================================================
 *      End of Class Method CLogFile::OutputMemoryStatus()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool OutputTabs (void);
 *
 * This protected class method outputs all the tabs required by the
 * current TabLevel to the log file.  Assumes that the log file is currently
 * open and valid.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool CLogFile::OutputTabs(void) {
	DEFINE_FUNCTION("CLogFile::OutputTabs()");
	int LoopCounter;
	int Result;
	/* Ensure a valid log file handle */
	ASSERT(pLogFileHandle != NULL);

	/* Output the tabs, if any */
	for (LoopCounter = 0; LoopCounter < TabLevel; LoopCounter++) {
		Result = TFPUTC((TCHAR)'\t', pLogFileHandle);

		if (Result == EOF) {
			return (FALSE);
		}
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CLogFile::OutputTabs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool Printf (pString, ...);
 *
 * Outputs a log file entry in the usual printf() format.  Returns TRUE
 * on success, or FALSE on any error.
 *
 *=========================================================================*/
bool CLogFile::Printf(const TCHAR *pString, ...) {
	DEFINE_FUNCTION("CLogFile::Printf(TCHAR*)");
	va_list Args;
	bool Result;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Ensure the log file is currently open */
	if (!IsOpen()) {
		return (FALSE);
	}

	/* Print the line to the file */
	va_start(Args, pString);
	Result = PrintLine(pString, Args);
	va_end(Args);
	return (Result);
}

/*===========================================================================
 *      End of Class Method CLogFile::Printf()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CLogFile Method - bool Printf (pFileHandle, pString, ...);
 *
 * Outputs a log file entry in the usual printf() format to the log file as well
 * as the given file stream.  Returns TRUE on success, or FALSE on any error.
 * Ignores the file stream if its NULL.  Outputs to the input stream
 * even if the log file is closed.
 *
 *=========================================================================*/
bool CLogFile::Printf(FILE *pFileHandle, const TCHAR *pString, ...) {
	DEFINE_FUNCTION("CLogFile::Printf(FILE*, TCHAR*)");
	int Result;
	int LoopCounter;
	va_list Args;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	va_start(Args, pString);

	/* Output line header to log file if open */
	if (IsOpen()) {
		Result = PrintLine(pString, Args);

		if (!Result) {
			va_end (Args);
			return (FALSE);
		}
	}

	/* Output result to file stream if required */
	if (pFileHandle != NULL) {
		/* Output the tabs, if any */
		for (LoopCounter = 0; LoopCounter < TabLevel; LoopCounter++) {
			Result = TFPUTC((TCHAR)'\t', pFileHandle);

			if (Result == EOF) {
				return (FALSE);
			}
		}

		Result = TVFPRINTF(pFileHandle, pString, Args);
		va_end(Args);

		if (Result < 0) {
			return (FALSE);
		}

		/* Terminate line with a line feed character */
		Result = TFPRINTF(pFileHandle, _T("\n"));

		if (Result < 0) {
			return (FALSE);
		}

		/* Flush output stream */
		Result = fflush (pFileHandle);

		if (Result == EOF) {
			return (FALSE);
		}
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CLogFile::Printf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - bool PrintLine (pString, Args);
 *
 * Outputs a line to the log file using the format string and variable
 * arguments.  Returns FALSE on any error.  Assumes that the log file
 * is currently open.  Protected class method.
 *
 *=========================================================================*/
bool CLogFile::PrintLine(const TCHAR *pString, va_list Args) {
	DEFINE_FUNCTION("CLogFile::PrintLine()");
	int Result;
	ASSERT(pString != NULL);
	ASSERT(pLogFileHandle != NULL);
	/* Get the current time and write to file as the line header */
	Result = OutputCurrentTime();

	if (!Result) {
		return (FALSE);
	}

	/* Output the tabs, if any */
	Result = OutputTabs();

	if (!Result) {
		return (FALSE);
	}

	/* Print the variable argument list to the file */
	Result = TVFPRINTF(pLogFileHandle, pString, Args);

	if (Result < 0) {
		return (FALSE);
	}

	/* Output to the optional hook procedure */
	if (pHookProc != NULL) {
		pHookProc(pString, Args);
	}

	/* A linefeed to terminate the current line */
	Result = TFPRINTF(pLogFileHandle, _T("\n"));

	if (Result < 0) {
		return (FALSE);
	}

	/* Flush the file stream to make sure the written characters are written
	 * to the file. This is in case the program crashes and isn't closed. If
	 * this did happen without the following line, any buffered log file
	 * data might not be output. */
	Result = fflush(pLogFileHandle);

	if (Result == EOF) {
		return (FALSE);
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CLogFile::PrintLine()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CLogFile Method - void SetTabLevel (NewTabLevel);
 *
 * Sets the current tab level to the given value, if valid.  The tab level
 * indicates how many tags preceed each line output to the log file,
 * allowing simple formatting of the output for easier viewing.  Valid
 * input is from 0 (no tabs) to LOGFILE_MAX_TABS.
 *
 * See also:    CLogFile::IncrementTags();
 *      CLogFile::DecrementTags();
 *
 *=========================================================================*/
void CLogFile::SetTabLevel(const int NewTabLevel) {
	/* Ensure a valid input */
	if (NewTabLevel < 0 || NewTabLevel > LOGFILE_MAX_TABS) {
		return;
	}

	TabLevel = NewTabLevel;
}

/*===========================================================================
 *      End of Class Method CLogFile::SetTabLevel()
 *=========================================================================*/



/*===========================================================================
 *
 * Begin Module Test Routines
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
 * Function - void Test_LogHook (pString, Args);
 *
 * Tests the callback functionality of the CLogFile class.
 *
 *=========================================================================*/
void Test_LogHook(const TCHAR *pString, va_list Args) {
	//DEFINE_FUNCTION("Test_LogHook()");
	TPRINTF(_T("Test_LogHook called...\n"));
	TVPRINTF(pString, Args);
	TPRINTF(_T("\n"));
}

/*===========================================================================
 *      End of Function void Test_LogHook()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_LogFile (void);
 *
 * Tests the CLogFile class.  Only defined in debug builds.
 *  - Checks constructors
 *  - Standard open method
 *  - Appending log files
 *  - Open an invalid file (empty string and NULL)
 *  - Open a log file without closing the current one.
 *  - Tab level increments and decrements
 *  - SetTabLevel() method with random values (-100 to 100)
 *  - Checks the hook procedure
 *  - Test split output to file stream
 *  - Tests DebugPrintf() method.
 *
 *=========================================================================*/
void Test_LogFile(void) {
	DEFINE_FUNCTION("Test_LogFile()");
	CLogFile TestLog1(_T("test1.log"));       /* Check constructors */
	CLogFile TestLog2;
	CLogFile TestLog3;
	int LoopCounter;
	int TabLevel;
	/* Check standard open method */
	TestLog2.Open(_T("test2.log"));
	/* Test appending logs */
	TestLog3.Open(_T("test3.log"), LOG_OPEN);
	TestLog3.Printf(_T("Test1"));
	TestLog3.Close();
	TestLog3.Open(_T("test3.log"), LOG_APPEND);
	TestLog3.Printf(_T("Append Test1"));
	/* Attempt to open an invalid file (both should ASSERT) */
	//TestLog2.Open("");
	//TestLog2.Open(NULL);
	/* Open file without closing the current log */
	TestLog1.Open(_T("test1a.log"));

	/* Check tab level incrementation */
	for (LoopCounter = 0; LoopCounter < 100; LoopCounter++) {
		TestLog1.IncrementTabs();
		TestLog1.Printf (_T("TabLevel = %d"), LoopCounter);
	}

	/* Check tab level decrementation */
	for (LoopCounter = 0; LoopCounter < 110; LoopCounter++) {
		TestLog1.DecrementTabs();
		TestLog1.Printf (_T("TabLevel = %d"), LoopCounter);
	}

	/* Check random tab levels with SetTabLevel() method */
	for (LoopCounter = 0; LoopCounter < 100; LoopCounter++) {
		TabLevel = (int) ((float)rand() * 201 / RAND_MAX) - 100;
		TestLog1.SetTabLevel(TabLevel);
		TestLog1.Printf (_T("SetTabLevel = %d"), TabLevel);
	}

	/* Reset the tab level for the log */
	TestLog1.SetTabLevel();
	/* Check the hook procedures */
	TestLog1.SetHookProc(Test_LogHook);
	TestLog1.Printf(_T("Testing hook proc..."));
	TestLog1.SetHookProc();
	TestLog1.Printf(_T("Removed hook proc..."));
	/* Test splitting output to file stream */
	TestLog1.Printf(TestLog2.GetFileHandle(), _T("Testing split output to file stream..."));
	TestLog1.Printf(stdout, _T("Testing split output to stdout..."));
	/* Test debug output */
	TestLog1.DebugPrintf(_T("Testing debug print...%d, %s"), 1001, _T("adedr"));
	ASSERT(DebugHeapCheckMemory());
}

/*===========================================================================
 *      End of Function Test_LogFile()
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
