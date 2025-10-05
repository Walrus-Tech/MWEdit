/*===========================================================================
 *
 * File:    DL_Err.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, April 24, 2001
 *
 * Contains the definitions for the CErrorHandler class, used for the
 * general handling of errors.
 *
 *=========================================================================*/
#ifndef __DL_ERR_H
#define __DL_ERR_H


#include "Common/dl_mem.h"


/* Maximum size of a message string for the error message strings */
#define MAX_ERROR_MESSAGESIZE   1024

/* Number of error incidents allowed at a time */
#define MAX_ERROR_INCIDENTS     50

/* Maximum number of errors to output to a notify list */
#define MAX_ERROR_NOTIFYLIST    10
#define ERROR_NOTIFYLIST_BUFFER 1024


/*===========================================================================
 *
 * Begin Custom Error Code Defines
 *
 *=========================================================================*/
#define ERR_NONE          ((errcode_t) 0)
#define ERR_MEM           ((errcode_t) 1)
#define ERR_OPENFILE      ((errcode_t) 2)
#define ERR_READFILE      ((errcode_t) 3)
#define ERR_WRITEFILE     ((errcode_t) 4)
#define ERR_OVERFLOW      ((errcode_t) 5)
#define ERR_BADINPUT      ((errcode_t) 6)
#define ERR_BADARRAYINDEX ((errcode_t) 7)
#define ERR_MAXINDEX      ((errcode_t) 8)
#define ERR_SYSTEM        ((errcode_t) 9)
#define ERR_TCGRAPH       ((errcode_t) 10) /* Only in TC-DOS */
#define ERR_WINDOWS       ((errcode_t) 11) /* Only under windows */
#define ERR_CUSTOM        ((errcode_t) 12)


/* Define type for error codes */
typedef long errcode_t;

/* Define the severity level of the custom error */
typedef enum {
	ERRLEVEL_UNKNOWN = -1,
	ERRLEVEL_INFO = 0,
	ERRLEVEL_WARNING = 1,
	ERRLEVEL_ERROR = 2,
	ERRLEVEL_CRITICAL = 3
} errlevel_t;

/* Type for a error handler notify function */
typedef int (ERR_NOTIFY_FUNCTION) (const TCHAR *pTitle, const TCHAR *pMsg);
typedef int (*PERR_NOTIFY_FUNCTION) (const TCHAR *pTitle, const TCHAR *pMsg);

/* Error hook callback function type */
typedef void (*PERROR_HOOKPROC) (void *pData, const TCHAR *pString, va_list Args);


/*===========================================================================
 *
 * Begin Custom Error Function Definition
 *
 * The following function type definition allows the expansion of the
 * error handler to support multiple systems of errors.  The functions
 * take an error code and return the associated error message.  The
 * functions should always return a valid string.
 *
 *=========================================================================*/
typedef const TCHAR *(ERR_CUSTOM_FUNCTION) (const errcode_t Code);
typedef const TCHAR *(*PERR_CUSTOM_FUNCTION) (const errcode_t Code);


/*===========================================================================
 *
 * Begin Class CErrorRecord Definition
 *
 * Defines one custom error definition for the CErrorHandler class.  Uses
 * a simple linked list structure.
 *
 *=========================================================================*/
class CErrorRecord {
  private:
	errcode_t Code;   /* The custom code for this error */
	TCHAR *pMessage;  /* the custom message string for the error */
	errlevel_t Level; /* The severity level for the custom error */

	/* The optional function for retrieving the error message for
	 * different system/platforms */
	PERR_CUSTOM_FUNCTION CustomErrFunction;

	/* Points to the next record in the linked list (or NULL if last element) */
	CErrorRecord *pNext;


  public:
	/* Class Constructors/Destructors */
	CErrorRecord();
	virtual ~CErrorRecord() {
		Destroy();
	}

	virtual void Destroy();

	/* Get class members */
	errcode_t GetCode() const {
		return Code;
	}

	errlevel_t GetLevel() const {
		return Level;
	}

	CErrorRecord *GetNext() const {
		return pNext;
	}

	const TCHAR *GetMsg(const errcode_t SubCode = ERR_NONE) const;

	/* Is this record the last in the linked list? */
	boolean IsLast() {
		if (pNext == NULL) {
			return TRUE;
		} else {
			return FALSE;
		}
	}

	/* Set class members */
	void SetCode(const errcode_t NewCode) {
		Code = NewCode;
	}

	void SetLevel(const errlevel_t NewLevel) {
		Level = NewLevel;
	}

	void SetNext(CErrorRecord *pNewNext) {
		pNext = pNewNext;
	}

	void SetMsg(const TCHAR *pString) {
		ReplaceString(&pMessage, pString);
	}

	void SetFunction(PERR_CUSTOM_FUNCTION NewFunction) {
		CustomErrFunction = NewFunction;
	}
};


/*===========================================================================
 *
 * Begin Class CErrorDatabase Definition
 *
 * Maintains a singly linked list of CErrorRecord objects containing
 * information on custom errors.  Can also be modified to handle any
 * system or platform specific errors.
 *
 *=========================================================================*/
class CErrorDatabase {
  private:
	CErrorRecord *pHead;        /* Start of the singly linked list */
	boolean AddedDefaultErrors; /* Have the default custom errors been loaded? */
	int NumErrors;              /* Number of custom errors in list */


  public:
	/* Class Constructors/Destructors */
	CErrorDatabase();
	virtual ~CErrorDatabase() {
		Destroy();
	}

	virtual void Destroy();

	/* Add a new custom error to the head of the linked list */
	void Add(const errcode_t Code,
	         const TCHAR *pMessage,
	         const errlevel_t Level = ERRLEVEL_ERROR);

	/* Add a custom error function */
	void AddCustomError(const errcode_t Code, PERR_CUSTOM_FUNCTION ErrFunction);

	/* Deletes the entire singly linked list of custom errors */
	void ClearErrors();

	/* Attempt to find a specific custom error record in the linked list */
	CErrorRecord *Find(const errcode_t Code);

	/* Get class members */
	int GetNumErrors() {
		return NumErrors;
	}

	/* Add the default custom errors to the database */
	void InitDefaultErrors();
};


/*===========================================================================
 *
 * Begin Class CErrorIncident Definition
 *
 * Records one occurence of an error for later retrieval.  Uses a simple
 * singly linked list structure.
 *
 *=========================================================================*/
class CErrorIncident {
  private:
	errcode_t Code;        /* The custom error code */
	errcode_t SubCode;
	TCHAR *pMessage;       /* The optional error message */
	CErrorIncident *pNext; /* Pointer to the next record in linked list */


  public:
	/* Class Constructors/Destructors */
	CErrorIncident();
	virtual ~CErrorIncident() {
		Destroy();
	}

	virtual void Destroy();

	/* Get class members */
	errcode_t GetCode() const {
		return Code;
	}

	errcode_t GetSubCode() const {
		return SubCode;
	}

	TCHAR *GetMsg() const {
		return pMessage;
	}

	CErrorIncident *GetNext() const {
		return pNext;
	}

	/* Set class members */
	void SetCode(const errcode_t NewCode) {
		Code = NewCode;
	}

	void SetSubCode(const errcode_t NewCode) {
		SubCode = NewCode;
	}

	void SetNext(CErrorIncident *pNewNext) {
		pNext = pNewNext;
	}

	void SetMsg(const TCHAR* pString) {
		ReplaceString(&pMessage, pString);
	}

	void SetMsg(const TCHAR *pString, va_list Args);
};


/*===========================================================================
 *
 * Begin Class CErrorHandler Definition
 *
 * Handles the recording and display of the errors for the application.
 *
 *=========================================================================*/
class CErrorHandler {
  private:
	CErrorIncident *pIncidentHead;    /* The current errors recorded */
	int NumErrors;

	CErrorDatabase &refErrorDatabase; /* The referenced database object */

	PERR_NOTIFY_FUNCTION pNotifyFunc; /* The optional notify function supplied by user */
	PERROR_HOOKPROC pHookFunc;        /* Optional users hook function */
	void *pHookData;

	int m_LastErrorCount;             /* Used to keep track of errors since last reset */


  protected:
	/* Outputs the most recent error to the SystemLog */
	void OutputLastErrorToLog();


  public:
	/* Class Constructors/Destructors */
	CErrorHandler(CErrorDatabase &ErrDB);
	virtual ~CErrorHandler() {
		Destroy();
	}

	virtual void Destroy ();

	/* Add an error to the top of the list */
	void AddError(const errcode_t Code, const TCHAR *pString = NULL, ...);
	void AddError(const errcode_t Code, const errcode_t SubCode, const TCHAR *pString, ...);
	void AddErrorV(const errcode_t Code,
	               const errcode_t SubCode,
	               const TCHAR *pString,
	               va_list Args);

	/* Delete all errors in the list */
	void ClearErrors();

	/* Clears the error count for tracking errors */
	void ClearErrorCount() {
		m_LastErrorCount = 0;
	}

	/* Display error message and abort program */
	void Exit(const TCHAR *pTitle = _T("Application Error"));
	void _Exit(const TCHAR *pTitle = _T("Application Error"));

	/* Get a specific error from the current list */
	CErrorIncident *GetError(const int Index = 0);

	/* Gets the error message of the most recent error incident */
	const TCHAR *GetLastErrorMsg();
	const TCHAR *GetLastErrorDBMsg();

	/* Get class members */
	int GetNumErrors() {
		return NumErrors;
	}

	int GetErrorCount() {
		return m_LastErrorCount;
	}

	/* Notifies the user of the most recent error */
	void Notify(const TCHAR *pTitle = _T("Application Error"));
	void Notify(const TCHAR *pMsg, const TCHAR *pTitle);
	void NotifyList(const TCHAR *pMsg, const TCHAR *pTitle);
	void NotifyListCode(const int ErrCode, const TCHAR *pMsg, const TCHAR *pTitle);
	void NotifyListType(const int ErrType, const TCHAR *pMsg, const TCHAR *pTitle);

	/* Retrieve the most recent error incident */
	CErrorIncident *PopError();
	CErrorIncident *PeekError();

	/* Standard error message output function */
	void Printf(const TCHAR *pTitle, const TCHAR *pString, ...);
	void Printf(const TCHAR *pTitle, const TCHAR *pString, va_list Args);

	/* Change the user notify function */
	void SetNotifyFunc(PERR_NOTIFY_FUNCTION NewFunc) {
		pNotifyFunc = NewFunc;
	}

	void SetHookFunc(PERROR_HOOKPROC NewFunc, void *pData) {
		pHookFunc = NewFunc;
		pHookData = pData;
	}
};


extern CErrorHandler ErrorHandler;
extern CErrorDatabase ErrorDatabase;


/* Returns the system error message associated with the error code */
const TCHAR *SystemErrorFunction(const errcode_t Code);
const TCHAR *TCGraphErrorFunction(const errcode_t Code);

#if _WIN32
	const TCHAR *WindowsErrorFunction(const errcode_t Code);
#endif


/*===========================================================================
 *
 * Begin Test Routine Definitions
 *
 * Function prototypes and definitions for the module test routines, only
 * available in DEBUG builds.
 *
 *=========================================================================*/

/* Custom error codes for testing error handler */
#define TEST_ERR1 100
#define TEST_ERR2 101
#define TEST_ERR3 102
#define TEST_ERR4 103
#define TEST_ERR5 105

/* Test routines for the module */
void Test_DefaultErrors();
void Test_SystemErrors();
void Test_AddError();
void Test_AddCustomError();
void Test_HandlerAddError();
void Test_HandlerNotify();
void Test_DLErr();
const TCHAR *Test_CustomErrFunc(const errcode_t Code);


#endif
