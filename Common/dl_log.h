/*===========================================================================
 *
 * File:    DL_Log.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, April 02, 2001
 *
 * Defines the CLogFile class for handling output to a simple log file for
 * debugging purposes.
 *
 *=========================================================================*/
#ifndef __DL_LOG_H
#define __DL_LOG_H


#include "dl_base.h"
#include <stdarg.h>


#define DL_LOG_NAME    _T("DL_Log.cpp")
#define DL_LOG_VERSION _T("0.01d")
#define DL_LOG_AUTHOR  _T("Dave Humphrey (uesp@m0use.net)")
#define DL_LOG_DATE    _T("2 April 2001")


/* Number of tab levels allowed in a log file */
#define LOGFILE_MAX_TABS 20


/* Logfile hook callback function type */
typedef void (*PLOGFILE_HOOKPROC) (const TCHAR *pString, va_list Args);
typedef void (LOGFILE_HOOKPROC) (const TCHAR *pString, va_list Args);

/* Parameters for the log file Open() method */
typedef enum {
	LOG_OPEN = 0,
	LOG_APPEND = 1
} logmode_t;


/*===========================================================================
 *
 * Class CLogFile Definition
 *
 * This class is used for handling log file operations used to output
 * various debugging information while the application is running.
 *
 *=========================================================================*/
class CLogFile {
  private:
	FILE *pLogFileHandle;        /* The pointer to the log file steam */
	int TabLevel;                /* Number of tabs to pad output with */
	PLOGFILE_HOOKPROC pHookProc; /* The optional hook function */


  protected:
	/* Outputs the current time to the log file */
	bool OutputCurrentTime();

	/* Outputs any tabs required by the current TabLevel */
	bool OutputTabs();


  public:
	/* Class Constructor and Destructor */
	CLogFile();
	CLogFile(const TCHAR *pFilename, const logmode_t AppendFile = LOG_OPEN);
	virtual ~CLogFile() {
		Close();
	}

	/* Closes the log file if it's currently open */
	bool Close();

	/* Access the file handle */
	FILE *GetFileHandle() {
		return pLogFileHandle;
	}

	/* Same as the Printf() method except it only works in debug builds.
	 * For release builds the function is nothing (to save a call). */
#if _DEBUG
	void DebugPrintf(const TCHAR *pString, ...);
#else
	void DebugPrintf(const TCHAR *, ...) { }
#endif

	/* Increase or decrease the current tab level of log file */
	void DecrementTabs();
	void IncrementTabs();

	/* Returns the open status of the log file */
	bool IsOpen() {
		return (bool)((pLogFileHandle == NULL) ? FALSE : TRUE);
	}

	/* Attempt to open a log file for output */
	bool Open(const TCHAR *pFilename, const logmode_t AppendFile = LOG_OPEN);

	/* Output the current date/time to the log file */
	bool OutputDate();

	/* Prints the current memory status to the log file */
	void OutputMemoryStatus();

	/* Output a log entry */
	bool Printf(const TCHAR *pString, ...);

	/* Output a log entry to logfile and another stream */
	bool Printf(FILE *pFileHandle, const TCHAR *pString, ...);

	/* Output a line to the log file */
	bool PrintLine(const TCHAR *pString, va_list Args);

	/* Change the hook procedure */
	void SetHookProc(PLOGFILE_HOOKPROC pProc = NULL) {
		pHookProc = pProc;
	}

	/* Change the current tab level */
	void SetTabLevel(const int NewTabLevel = 0);
};


/*===========================================================================
 *
 * Begin Test Function Prototypes
 *
 * Prototypes for functions to test module.  Available only in DEBUG builds.
 *
 *=========================================================================*/
#if _DEBUG
	void Test_LogFile();
#endif


/* The primary log file */
extern CLogFile SystemLog;


#endif
