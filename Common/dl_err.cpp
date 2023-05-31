/*===========================================================================
 *
 * File:	DL_Err.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	Tuesday, April 24, 2001
 *
 * Class CErrorDatabase and CErrorHandler for handling custom errors
 * in an application.  The database class supports any system/platform
 * specific errors meaning that you only need to worry about handling
 * errors with the global objects ErrorHandler and ErrorDatabase. For
 * instance, if you were making a Windows, DirectDraw, COM application,
 * you would normally have to worry about the system, Windows, DirectDraw
 * and the COM specific errors, in addition to your own (thats 5 different
 * error systems).  All these methods can be 'hidden' by the error handling
 * classes, making your code better looking.
 *
 * TODO: The ErrorHandler records error incidents in a singly linked list.
 *	Initially, the list simply grew until the program ended, but in
 *	some cases this caused problems (1000's of errors  being saved).
 *	Now, up to MAX_ERROR_INCIDENTS are recorded. Once this limit
 *	is reached, the incidents are deleted except for the current
 *	one.  Better methods could be used if so required.
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *	- Moved from regular char to TCHAR type to support wide characters
 *	  under Windows. Successfully tested.
 *
 * 25 June 2003
 *	- Added the NotifyListCode() and NotifyListType() methods.
 *
 * 18 September 2003
 *	- Modified NotifyList() to output the error description from the
 *	  database if it is available.
 *
 *=========================================================================*/

	/* Include Files */
#include "dl_err.h"
#include "dl_str.h"

#if !defined(_WIN32_WCE)
  #include <errno.h>

  	/* Include TC graphic error messages */
  #if defined(_TCGRAPHERRORS)
    #include <graphics.h>
  #endif
#endif

	/* Include Windows error messages/functions */
#if defined(_WIN32) || defined(__BCPLUSPLUS__)
  #include "windows.h"
#endif




/*===========================================================================
 *
 * Begin Local Variables
 *
 *=========================================================================*/
  DEFINE_FILE("DL_Err.h");
/*===========================================================================
 *		End of Local Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Global Variables
 *
 *=========================================================================*/
  CErrorDatabase ErrorDatabase;
  CErrorHandler  ErrorHandler(ErrorDatabase);
/*===========================================================================
 *		End of Global Variables
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorRecord Constructor
 *
 *=========================================================================*/
CErrorRecord::CErrorRecord (void) {
  pMessage = NULL;
  CustomErrFunction = NULL;
  Code = ERR_NONE;
  Level = ERRLEVEL_UNKNOWN;
  pNext = NULL;
 }
/*===========================================================================
 *		End of Class CErrorRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorRecord Method - void Destroy (void);
 *
 * Deletes the contents of the object.
 *
 *=========================================================================*/
void CErrorRecord::Destroy (void) {
  DEFINE_FUNCTION("CErrorRecord::Destroy()");

  DestroyPointer(pMessage);

  Code = ERR_NONE;
  Level = ERRLEVEL_UNKNOWN;
  CustomErrFunction = NULL;

	/* Assumed the linked list structure is maintained by the parent */
  pNext = NULL;
 }
/*===========================================================================
 *		End of Class Method CErrorRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorRecord Method - TCHAR* GetMsg (SubCode) const;
 *
 * Attempts to retrieve the message for the error.  If the custom error
 * function is non-NULL, the message is returned from that function using
 * the given error SubCode. Otherwise, the current message string of the
 * object is returned.
 *
 *=========================================================================*/
const TCHAR* CErrorRecord::GetMsg (const errcode_t SubCode) const {
  //DEFINE_FUNCTION("CErrorRecord::GetMsg()");

	/* Return the current message string for a regular error */
  if (CustomErrFunction == NULL) return (pMessage);

	/* Call the custom error function with the error's subcode */
  return CustomErrFunction(SubCode);
 }
/*===========================================================================
 *		End of Class Method CErrorRecord::GetMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Constructor
 *
 *=========================================================================*/
CErrorDatabase::CErrorDatabase (void) {
  pHead = NULL;
  AddedDefaultErrors = FALSE;
  NumErrors = 0;

  InitDefaultErrors();
 }
/*===========================================================================
 *		End of Class CErrorDatabase Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - void Destroy (void);
 *
 * Deletes the current contents of the object.
 *
 *=========================================================================*/
void CErrorDatabase::Destroy (void) {
  //DEFINE_FUNCTION("CErrorDatabase::Destroy()");

	/* Delete the singly linked list */
  ClearErrors();
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - void Add (Code, pMessage, Level);
 *
 * Attempts to add the given custom error definition to the singly
 * linked list.  The error Level is optional and defaults to ERRLEVEL_ERROR.
 * On any error, an exception is thrown (no memory to allocate).
 *
 *=========================================================================*/
void CErrorDatabase::Add (const errcode_t Code, const TCHAR* pMessage, const errlevel_t Level) {
  DEFINE_FUNCTION("CErrorDatabase::Add()");
  CErrorRecord* pNewRecord;

	/* Ensure valid input */
  ASSERT(pMessage != NULL);

	/* Attempt to allocate the new record */
  CreatePointer(pNewRecord, CErrorRecord);

	/* Attempt to initialize the new record */
  pNewRecord->SetCode(Code);
  pNewRecord->SetLevel(Level);
  pNewRecord->SetMsg(pMessage);

	/* Add the new error to the head of the linked list */
  pNewRecord->SetNext(pHead);
  pHead = pNewRecord;
  NumErrors++;
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::Add()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - void AddCustomError (Code, ErrFunction);
 *
 * Adds a custom error function with the given error code to the database.
 * Throws an exception if memory could not be allocated.
 *
 *=========================================================================*/
void CErrorDatabase::AddCustomError (const errcode_t Code, PERR_CUSTOM_FUNCTION ErrFunction) {
  DEFINE_FUNCTION("CErrorDatabase::AddCustomError()");
  CErrorRecord* pNewRecord;

	/* Ensure valid input */
  ASSERT(ErrFunction != NULL);

	/* Attempt to allocate the new record */
  CreatePointer(pNewRecord, CErrorRecord);

	/* Attempt to initialize the new record */
  pNewRecord->SetCode(Code);
  pNewRecord->SetFunction(ErrFunction);

	/* Add the new error to the head of the linked list */
  pNewRecord->SetNext(pHead);
  pHead = pNewRecord;
  NumErrors++;
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::AddCustomError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - void ClearErrors (void);
 *
 * Deletes the entire singly linked list.
 *
 *=========================================================================*/
void CErrorDatabase::ClearErrors (void) {
  DEFINE_FUNCTION("CErrorDatabase::ClearErrors()");
  CErrorRecord* pListPtr;

	/* Delete all items in the singly linked list */
  while (pHead != NULL) {
    pListPtr = pHead->GetNext();
    DestroyPointer(pHead);
    pHead = pListPtr;
   }

  AddedDefaultErrors = FALSE;
  NumErrors = 0;
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::ClearErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - CErrorRecord* Find (Code);
 *
 * Attempt to find the custom error record with the given error code. 
 * Returns NULL if the given record could not be found.
 *
 *=========================================================================*/
CErrorRecord* CErrorDatabase::Find (const errcode_t Code) {
  DEFINE_FUNCTION("CErrorDatabase::Find()");
  CErrorRecord* pSearchPtr;

	/* Search the entire linked list */
  for (pSearchPtr = pHead; pSearchPtr != NULL; pSearchPtr = pSearchPtr->GetNext()) {
    if (pSearchPtr->GetCode() == Code) return (pSearchPtr);
   }

	/* No record was found */
  SystemLog.DebugPrintf(_T("%s - Failed to find error record with code %ld!"), ThisFunction, Code);
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorDatabase Method - void InitDefaultErrors (void);
 *
 * Adds the default custom errors the the database.  Will not add the
 * errors if they were previously added.
 *
 *=========================================================================*/
void CErrorDatabase::InitDefaultErrors (void) {
  //DEFINE_FUNCTION("CErrorDatabase::InitDefaultErrors()");

	/* Ignore if the default errors have already been added */
  if (AddedDefaultErrors) return;

	/* Add the regular custom errors */
  Add (ERR_NONE,	 _T("No error generated."),			ERRLEVEL_INFO);
  Add (ERR_MEM,		 _T("Failed to allocate memory!"),		ERRLEVEL_CRITICAL);
  Add (ERR_OPENFILE,	 _T("Failed to open file!"),			ERRLEVEL_ERROR);
  Add (ERR_READFILE,	 _T("Failed to read from file!"),		ERRLEVEL_ERROR);
  Add (ERR_WRITEFILE,	 _T("Failed to write to file!"),		ERRLEVEL_ERROR);
  Add (ERR_BADARRAYINDEX,_T("Index exceeds array limits!"),		ERRLEVEL_WARNING);
  Add (ERR_MAXINDEX,	 _T("Array has reached it's maximum size!"),	ERRLEVEL_WARNING);
  Add (ERR_BADINPUT,     _T("Invalid input was received!"),		ERRLEVEL_WARNING);
  Add (ERR_OVERFLOW,	 _T("Received input that would result in an overflow!"), ERRLEVEL_ERROR);
  Add (ERR_CUSTOM,       _T("Custom application error!"),		ERRLEVEL_ERROR);

	/* Add the system error messages */
  AddCustomError (ERR_SYSTEM, SystemErrorFunction);

	/* Add the graphic error messages under DOS if required */
  #if defined(_TCGRAPHERRORS)
    AddCustomError(ERR_TCGRAPH, TCGraphErrorFunction);
  #endif

  	/* Add the windows error messages under Windows if required */
  #if defined(_WIN32) || defined(__BCPLUSPLUS__)
    AddCustomError(ERR_WINDOWS, WindowsErrorFunction);
  #endif

  AddedDefaultErrors = TRUE;
 }
/*===========================================================================
 *		End of Class Method CErrorDatabase::InitDefaultErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorIncident Constructor
 *
 *=========================================================================*/
CErrorIncident::CErrorIncident (void) {
  pNext = NULL;
  pMessage = NULL;
  Code = ERR_NONE;
  SubCode = ERR_NONE;
 }
/*===========================================================================
 *		End of Class CErrorIncident Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorIncident Method - void Destroy (void);
 *
 * Clears the contents of the object.
 *
 *=========================================================================*/
void CErrorIncident::Destroy (void) {
  DEFINE_FUNCTION("CErrorIncident::Destroy()");

  DestroyPointer(pMessage);
  Code = ERR_NONE;
  SubCode = ERR_NONE;

	/* Assumes that the linked list structure is maintained by the parent */
  pNext = NULL;
 }
/*===========================================================================
 *		End of Class Method CErrorIncident::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorIncident Method - void SetMsg (pString, Args);
 *
 * Sets the incident message string using a variable list of arguments,
 * as in the vprintf() type functions.  Messages are limited to a 
 * size of MAX_ERROR_MESSAGESIZE bytes.
 *
 *=========================================================================*/
void CErrorIncident::SetMsg (const TCHAR* pString, va_list Args) {
  DEFINE_FUNCTION("CErrorIncident::SetMsg(TCHAR*, va_list)");
  TCHAR MessageBuffer[MAX_ERROR_MESSAGESIZE*2];
  int   Result;

	/* Attempt to create the message string */
  Result = vsnprintf(MessageBuffer, MAX_ERROR_MESSAGESIZE, pString, Args);

	/* Only set message if the message was successfully created */
  if (Result >= 0) ReplaceString(&pMessage, MessageBuffer);
 }
/*===========================================================================
 *		End of Class Method CErrorIncident::SetMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Constructor
 *
 *=========================================================================*/
CErrorHandler::CErrorHandler (CErrorDatabase& ErrDB) : refErrorDatabase(ErrDB) {
  pIncidentHead = NULL;
  NumErrors     = 0;
  pNotifyFunc   = NULL;
  pHookFunc     = NULL;
  m_LastErrorCount = 0;
 }
/*===========================================================================
 *		End of Class CErrorHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Destroy (void);
 *
 * Clears the contents of the object.
 *
 *=========================================================================*/
void CErrorHandler::Destroy (void) {
  //DEFINE_FUNCTION("CErrorHandler::Destroy()");

	/* Delete the current errors */
  ClearErrors();

  pNotifyFunc = NULL;
  pHookFunc   = NULL;
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void AddError (Code, pString, ...);
 *
 * Adds the given error code and optional message to the top of the error
 * list.  Throws an exception on a memory allocation error.  Accepts message
 * input as per the printf() type functions.  Message string should be 
 * limited to MAX_ERROR_MESSAGESIZE characters in size.  Does not ensure
 * that the message is correctly written.  
 *
 *=========================================================================*/
void CErrorHandler::AddError (const errcode_t Code, const TCHAR* pString, ...) {
  //DEFINE_FUNCTION("CErrorHandler::AddError(errcode_t, TCHAR*, ...)");
  va_list Args;

  va_start(Args, pString);

#if defined(_WIN32)
  AddErrorV(Code, GetLastError(), pString, Args);
#else
  AddErrorV(Code, ERR_NONE, pString, Args);
#endif

  va_end(Args);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::AddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void AddError (Code, SubCode, pString, ...);
 *
 * Adds the given error code and optional message to the top of the error
 * list.  Throws an exception on a memory allocation error.  Accepts message
 * input as per the printf() type functions.  Message string should be 
 * limited to MAX_ERROR_MESSAGESIZE characters in size.  Does not ensure
 * that the message is correctly written.  
 *
 *=========================================================================*/
void CErrorHandler::AddError (const errcode_t Code, const errcode_t SubCode, const TCHAR* pString, ...) {
  //DEFINE_FUNCTION("CErrorHandler::AddError(errcode_t, errcode_t, TCHAR*, ...)");
  va_list Args;

  va_start(Args, pString);
  AddErrorV(Code, SubCode, pString, Args);
  va_end(Args);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::AddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void AddErrorV (Code, SubCode, pString, Args);
 *
 * Adds the given error code and optional message to the top of the error
 * list.  Throws an exception on a memory allocation error.  Accepts message
 * input as per the vprintf() type functions.  Message string should be 
 * limited to MAX_ERROR_MESSAGESIZE characters in size.  Does not ensure
 * that the message is correctly written.  
 *
 *=========================================================================*/
void CErrorHandler::AddErrorV (const errcode_t Code, const errcode_t SubCode, const TCHAR* pString, va_list Args) {
  DEFINE_FUNCTION("CErrorHandler::AddErrorV(errcode_t, errcode_t, TCHAR*, va_list)");
  CErrorIncident* pNewIncident;

	/* Ensure we don't exceed the maximum error limit */
  if (NumErrors >= MAX_ERROR_INCIDENTS) {
    SystemLog.Printf(_T("Clearing %u error incidents..."), NumErrors);
    ClearErrors();
   }

	/* Attempt to allocate a new incident object */
  CreatePointer(pNewIncident, CErrorIncident);

	/* Initialize the new error incident */
  pNewIncident->SetCode(Code);
  pNewIncident->SetSubCode(SubCode);
  if (pString != NULL) pNewIncident->SetMsg(pString, Args);

	/* Add error to head of incident list */
  pNewIncident->SetNext(pIncidentHead);
  pIncidentHead = pNewIncident;
  NumErrors++;
  m_LastErrorCount++;

	/* Call the user's hook function if required */
  if (pHookFunc != NULL) pHookFunc(pHookData, pString, Args);

	/* Output the error information to the log file */
  OutputLastErrorToLog();
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::AddErrorV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void ClearErrors (void);
 *
 * Deletes all the errors currently in the linked list.
 *
 *=========================================================================*/
void CErrorHandler::ClearErrors (void) {
  DEFINE_FUNCTION("CErrorHandler::ClearErrors()");
  CErrorIncident* pListPtr;

	/* Delete all elements in the singly linked list */
  while (pIncidentHead != NULL) {
    pListPtr = pIncidentHead->GetNext();
    DestroyPointer(pIncidentHead);
    pIncidentHead = pListPtr;
   }

  NumErrors = 0;
  m_LastErrorCount = 0;
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::ClearErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Exit (pTitle);
 *
 * Displays the last error message using the Notify() method and then
 * aborts the program using exit() (end with cleanup code).
 *
 *=========================================================================*/
void CErrorHandler::Exit (const TCHAR* pTitle) {
  DEFINE_FUNCTION("CErrorHandler::Exit()");

	/* Display the error message to user */
  Notify(pTitle);

	/* End program calling cleanup code first */
  exit(EXIT_FAILURE);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Exit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void _Exit (pTitle);
 *
 * Displays the last error message using the Notify() method and then
 * aborts the program using _exit() (end without cleanup code).
 *
 *=========================================================================*/
void CErrorHandler::_Exit (const TCHAR* pTitle) {
  DEFINE_FUNCTION("CErrorHandler::_Exit()");

	/* Display the error message to user */
  Notify(pTitle);

	/* End program immediately without calling any cleanup code */
  _exit(EXIT_FAILURE);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::_Exit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - CErrorIncident* GetError (Index);
 *
 * Attempts to return the specified error from the linked list.  ASSERTs
 * if the given index is invalid.  The specified error record is not
 * removed from the incident list (unlike the PopError() method).
 *
 *=========================================================================*/
CErrorIncident* CErrorHandler::GetError (const int Index) {
  DEFINE_FUNCTION("CErrorHandler::GetError()");
  CErrorIncident* pListPtr;
  int		  ListCounter;

	/* Ensure the input index is valid */
  ASSERT(Index >= 0);
  ASSERT(Index < NumErrors);

	/* Move to the specified element in the list */
  for (pListPtr  = pIncidentHead,	ListCounter = 0;
       pListPtr != NULL		&&	ListCounter < Index; 
       pListPtr  = pListPtr->GetNext(),	ListCounter++) {
   }

	/* Ensure a valid list element was found */
  ASSERT(pListPtr != NULL);
  return (pListPtr);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::GetError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - TCHAR* GetLastErrorMsg (void);
 *
 * Returns the error message of the most recent incident.  If no incidents
 * have been recorded, returns a standard 'no errors' type string.  If the
 * incident's message is NULL, it attempts to return the database 
 * message for that error.  Always returns a valid string, never NULL.
 *
 *=========================================================================*/
const TCHAR* CErrorHandler::GetLastErrorMsg (void) {
  //DEFINE_FUNCTION("CErrorHandler::GetLastErrorMsg()");

	/* Ensure there is at least one incident recorded in list */
  if (NumErrors == 0) return (_T("No recorded errors."));

	/* Check for a valid incident message */
  if (pIncidentHead->GetMsg() != NULL) return (pIncidentHead->GetMsg());

	/* Return the message from the error database */
  return (GetLastErrorDBMsg());
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::GetLastErrorMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - TCHAR* GetLastDBErrorMsg (void);
 *
 * Returns the database error message of the most recent incident.  If 
 * no incidents have been recorded, returns a standard 'no errors' type 
 * string.  Always returns a valid string, never NULL.
 *
 *=========================================================================*/
const TCHAR* CErrorHandler::GetLastErrorDBMsg (void) {
  //DEFINE_FUNCTION("CErrorHandler::GetLastDBErrorMsg()");
  CErrorRecord* pErrRecord;

	/* Ensure there is at least one incident recorded in list */
  if (NumErrors == 0) return (_T("No recorded errors."));

	/* Attempt to retrieve database message for error */
  pErrRecord = refErrorDatabase.Find(pIncidentHead->GetCode());
  if (pErrRecord != NULL) return (pErrRecord->GetMsg(pIncidentHead->GetSubCode()));

	/* No error message available for the incident! */
  SystemLog.Printf(_T("No message available for error %ld/%ld"), pIncidentHead->GetCode(), pIncidentHead->GetSubCode());
  return (_T("No message available for the error!"));
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::GetLastDBErrorMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Notify (pTitle);
 *
 * Notifies the user of the most recent error.  Uses the Printf() method
 * to output results depending on the current compiled system.
 * Nothing happens if there are no current errors in the list.
 *
 *=========================================================================*/
void CErrorHandler::Notify (const TCHAR* pTitle) {
  //DEFINE_FUNCTION("CErrorHandler::Notify()");
  CErrorRecord* pErrorRecord;

	/* Ignore if there are no errors to output */
  if (pIncidentHead == NULL) return;

	/* Attempt to find the error record in the database of custom errors */
  pErrorRecord = refErrorDatabase.Find(pIncidentHead->GetCode());

  if (pErrorRecord == NULL) {
    Printf(pTitle, _T("Unknown error code %ld!\n\r%s\n\r"), pIncidentHead->GetCode(),
						   pIncidentHead->GetMsg());
   }
  else {
    Printf(pTitle, _T("%s\r\n%s\r\n"), pErrorRecord->GetMsg(pIncidentHead->GetSubCode()),
			       pIncidentHead->GetMsg());
   }

 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Notify()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Notify (pMsg, pTitle);
 *
 * Same as the Notify() function but outputs the given user message 
 * instead of the recorded error message.
 *
 *=========================================================================*/
void CErrorHandler::Notify (const TCHAR* pMsg, const TCHAR* pTitle) {
  CErrorRecord* pErrorRecord;

	/* Ignore if there are no errors to output */
  if (pIncidentHead == NULL) return;

	/* Attempt to find the error record in the database of custom errors */
  pErrorRecord = refErrorDatabase.Find(pIncidentHead->GetCode());

  if (pErrorRecord == NULL) {
    Printf(pTitle, _T("Unknown error code %ld!\n\r%s\n\r"), pIncidentHead->GetCode(),
						   pIncidentHead->GetMsg());
   }
  else if (pMsg != NULL) {
    Printf(pTitle, _T("%s\r\n%s\r\n"), pMsg,
			       pIncidentHead->GetMsg());
   }
  else {
    Printf(pTitle, _T("%s\r\n%s\r\n"), pErrorRecord->GetMsg(pIncidentHead->GetSubCode()),
			       pIncidentHead->GetMsg());
   }

 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Notify()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void NotifyList (pMsg, pTitle);
 *
 * Same as the Notify() function but outputs the given user message 
 * instead of the recorded error message.  Outputs all the errors
 * recorded by the m_LastErrorCount member.  Outputs 10 errors at most.
 *
 *=========================================================================*/
void CErrorHandler::NotifyList (const TCHAR* pMsg, const TCHAR* pTitle) {
  CErrorIncident* pError;
  CErrorRecord*   pErrorRecord;
  TCHAR		  ErrorBuffer[MAX_ERROR_MESSAGESIZE+1];
  int		  OutputErrors;
  int		  Length;

	/* Ignore if there are no errors to output */
  if (pIncidentHead == NULL) return;
  
	/* Print the error message description */
  Length = snprintf(ErrorBuffer, MAX_ERROR_MESSAGESIZE, _T("%s\n\r\n\r"), pMsg);
  OutputErrors = 0;
  pError = pIncidentHead;

	/* Output all required errors */
  while (pError != NULL && OutputErrors < MAX_ERROR_NOTIFYLIST && OutputErrors < m_LastErrorCount) {
    pErrorRecord = refErrorDatabase.Find(pError->GetCode());

    if (pErrorRecord == NULL) {
      Length += snprintf(ErrorBuffer+Length, MAX_ERROR_MESSAGESIZE-Length, _T("      %d) %s\n\r"), OutputErrors+1,	
				pError->GetMsg());
     }
    else {
      Length += snprintf(ErrorBuffer+Length, MAX_ERROR_MESSAGESIZE-Length, _T("      %d) %s\n\r\t%s\n\r"), OutputErrors+1,	
				pError->GetMsg(), pErrorRecord->GetMsg(pError->GetSubCode()));
     }

    pError = pError->GetNext();
    OutputErrors++;
   }
  
	/* Output the message */
  Printf(pTitle, ErrorBuffer, NULL);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::NotifyList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void NotifyListCode (ErrCode, pMsg, pTitle);
 *
 * Same as the Notify() function but outputs the given user message 
 * instead of the recorded error message.  Outputs all the errors
 * recorded by the m_LastErrorCount member that have the given error code.
 * Outputs 10 errors at most.
 *
 *=========================================================================*/
void CErrorHandler::NotifyListCode (const int ErrCode, const TCHAR* pMsg, const TCHAR* pTitle) {
  CErrorIncident* pError;
  CErrorRecord*   pErrorRecord;
  TCHAR		  ErrorBuffer[MAX_ERROR_MESSAGESIZE+1];
  int		  OutputErrors;
  int		  Length;

	/* Ignore if there are no errors to output */
  if (pIncidentHead == NULL) return;
  
	/* Print the error message description */
  Length = snprintf(ErrorBuffer, MAX_ERROR_MESSAGESIZE, _T("%s\n\r"), pMsg);
  OutputErrors = 0;
  pError = pIncidentHead;

	/* Output all required errors */
  while (pError != NULL && OutputErrors < MAX_ERROR_NOTIFYLIST && OutputErrors < m_LastErrorCount) {
    pErrorRecord = refErrorDatabase.Find(pError->GetCode());

		/* Ignore all errors that don't have the given error code */
    if (pError->GetCode() != ErrCode) {
      pError = pError->GetNext();
      continue;
     }

    Length += snprintf(ErrorBuffer+Length, MAX_ERROR_MESSAGESIZE-Length, _T("      %d) %s\n\r"), OutputErrors+1,	
				pError->GetMsg());
     
    pError = pError->GetNext();
    OutputErrors++;
   }
  
	/* Output the message if required */
  if (OutputErrors > 0) Printf(pTitle, ErrorBuffer, NULL);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::NotifyListCode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void NotifyListType (ErrType, pMsg, pTitle);
 *
 * Same as the Notify() function but outputs the given user message 
 * instead of the recorded error message.  Outputs all the errors
 * recorded by the m_LastErrorCount member that have at least the
 * given error level type. Outputs 10 errors at most.
 *
 *=========================================================================*/
void CErrorHandler::NotifyListType (const int ErrType, const TCHAR* pMsg, const TCHAR* pTitle) {
  CErrorIncident* pError;
  CErrorRecord*   pErrorRecord;
  TCHAR		  ErrorBuffer[MAX_ERROR_MESSAGESIZE+1];
  int		  OutputErrors;
  int		  Length;

	/* Ignore if there are no errors to output */
  if (pIncidentHead == NULL) return;
  
	/* Print the error message description */
  Length = snprintf(ErrorBuffer, MAX_ERROR_MESSAGESIZE, _T("%s\n\r"), pMsg);
  OutputErrors = 0;
  pError = pIncidentHead;

	/* Output all required errors */
  while (pError != NULL && OutputErrors < MAX_ERROR_NOTIFYLIST && OutputErrors < m_LastErrorCount) {
    pErrorRecord = refErrorDatabase.Find(pError->GetCode());

		/* Ignore all errors that don't have a valid error level */
    if (pErrorRecord != NULL && pErrorRecord->GetLevel() < ErrType) {
      pError = pError->GetNext();
      continue;
     }

    Length += snprintf(ErrorBuffer+Length, MAX_ERROR_MESSAGESIZE-Length, _T("      %d) %s\n\r"), OutputErrors+1,	
				pError->GetMsg());

    pError = pError->GetNext();
    OutputErrors++;
   }
  
	/* Output the message if required */
  if (OutputErrors > 0) Printf(pTitle, ErrorBuffer, NULL);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::NotifyListType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void OutputLastErrorToLog (void);
 *
 * Protectd class method which outputs the topmost error incident to the
 * SystemLog.
 *
 *=========================================================================*/
void CErrorHandler::OutputLastErrorToLog (void) {
  //DEFINE_FUNCTION("CErrorHandler::OutputLastErrorToLog()");
  CErrorRecord* pErrorRecord;

	/* Ensure there is a valid error in the list */
  if (pIncidentHead == NULL) return;

	/* Attempt to get the database entry for the error */
  pErrorRecord = refErrorDatabase.Find(pIncidentHead->GetCode());

  SystemLog.Printf (_T("Error (%ld / %ld): %s"), pIncidentHead->GetCode(), pIncidentHead->GetSubCode(),
		    (pErrorRecord == NULL) ? _T("No database entry for error found!") : pErrorRecord->GetMsg(pIncidentHead->GetSubCode()) );
  SystemLog.Printf (_T("\t\t User Message: %s"), pIncidentHead->GetMsg());
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::OutputLastErrorToLog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - CErrorIncident* PopError (void);
 *
 * Returns the most recently added error incident in the list, removing
 * it from the incident list.  Returns NULL if no errors currently exist.
 *
 * See Also: GetError(int), PeekError()
 *
 *=========================================================================*/
CErrorIncident* CErrorHandler::PopError (void) {
  //DEFINE_FUNCTION("CErrorHandler::PopError()");
  CErrorIncident* pLastError;

	/* Check if there are any errors left to return */
  if (pIncidentHead == NULL) return (NULL);

	/* Remove the head from the singly linked list */
  pLastError = pIncidentHead;
  pIncidentHead = pLastError->GetNext();
  NumErrors--;

  return (pLastError);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::PopError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - CErrorIncident* PeekError (void);
 *
 * Returns the most recently added error incident in the list.
 * Returns NULL if no errors currently exist.
 *
 * See Also: GetError(int), PopError()
 *
 *=========================================================================*/
CErrorIncident* CErrorHandler::PeekError (void) {
  //DEFINE_FUNCTION("CErrorHandler::PopError()");

	/* Check if there are any errors left to return */
  if (pIncidentHead == NULL) return (NULL);
  return (pIncidentHead);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::PeekError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Printf (pTitle, pString, ...);
 *
 * Accepts input as the printf() function, outputting the given error message
 * to whatever the current system supports.  Uses the variable argument version
 * of the Printf() method.  Does not check to ensure the message was 
 * successfully output.
 *
 *=========================================================================*/
void CErrorHandler::Printf (const TCHAR* pTitle, const TCHAR* pString, ...) {
  DEFINE_FUNCTION("CErrorHandler::Printf(TCHAR*, TCHAR*, ...)");
  va_list Args;

	/* Ensure valid input */
  ASSERT(pString != NULL);

	/* Use the variable argument version of Printf() */
  va_start(Args, pString);
  Printf(pTitle, pString, Args);
  va_end(Args);
 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Printf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CErrorHandler Method - void Printf (pTitle, pString, Args);
 *
 * Outputs an error message to the user depending on the current system.
 * Accepts a variable argument list (va_list).  If a custom output function
 * is installed, the error message is redirected to it.  Otherwise the
 * error is output depending on the system. Current supported systems
 * include:
 *	WIN32 -	Message dialog is displayed (not in console applications).
 *	DEFAULT - Message is output to stderr
 * Does not check to ensure message is correctly output.
 *
 * See Also:  Printf (TCHAR*, TCHAR*, ...);
 *
 *=========================================================================*/
void CErrorHandler::Printf (const TCHAR* pTitle, const TCHAR* pString, va_list Args) {
  DEFINE_FUNCTION("CErrorHandler::Printf(TCHAR*, TCHAR*, va_list)");
  TCHAR MsgBuffer[MAX_ERROR_MESSAGESIZE+1];

	/* Ensure valid input */
  ASSERT(pString != NULL && pTitle != NULL);

	/* Use the custom notify function if supplied with one */
  if (pNotifyFunc != NULL) {
    vsnprintf(MsgBuffer, MAX_ERROR_MESSAGESIZE, pString, Args);
    pNotifyFunc(pTitle, MsgBuffer);
    return;
   }


 /*---------- Begin Win32 Specific Code ----------------------------*/
#if (defined(_WIN32) || defined(__BCPLUSPLUS__)) && !defined(_CONSOLE)
  
	/* Output the variable argument list to the temporary string */
  vsnprintf(MsgBuffer, MAX_ERROR_MESSAGESIZE, pString, Args);

	/* Display a standard error message box */
  MessageBox(NULL, MsgBuffer, pTitle, MB_OK | MB_ICONHAND | MB_TASKMODAL);


  /*---------- Begin Default Code (Output to stderr) ----------------*/
#else

	/* Output the variable argument list to the stderr stream */
  fprintf (stderr, _T("%s\n"), pTitle);
  fprintf (stderr, _T("\t"));
  vfprintf (stderr, pString, Args);
  fprintf (stderr, _T("\n"));
  fflush(stderr);
  
#endif

 }
/*===========================================================================
 *		End of Class Method CErrorHandler::Printf()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* SystemErrorFunction (Code);
 *
 * Returns the error message associated with the given system error code.
 * Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR* SystemErrorFunction (const errcode_t Code) {
  DEFINE_FUNCTION("SystemErrorFunction()");
  TCHAR* pErrMessage;

#if defined(_WIN32_WCE)  
  return (_T("No system errors in WinCE!"));
#else

	/* Check to ensure that it is a valid system error code */
  if (Code < 0 || ((int) Code) >= _sys_nerr)
    return (_T("Invalid system error code!"));

	/* Retrieve the error message from the system, ensuring its valid */
#if defined(_UNICODE)
  static TCHAR l_BufferMsg[256];

	/* Convert ASCII message to unicode */
  mbstowcs(l_BufferMsg, sys_errlist[(int)Code], 255);

  pErrMessage = l_BufferMsg;
#else
  pErrMessage = sys_errlist[(int)Code];
#endif
  ASSERT(pErrMessage != NULL);

  //SystemLog.Printf ("SystemErrorFunction(%s)", pErrMessage);
  return (pErrMessage);
#endif
 }
/*===========================================================================
 *		End of Function SystemErrorFunction()
 *=========================================================================*/


#if defined(_TCGRAPHERRORS)
/*===========================================================================
 *
 * Function - TCHAR* TCGraphErrorFunction (Code);
 *
 * Returns the error message associated with the given graphics error code
 * under TurboC for DOS. Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR* TCGraphErrorFunction (const errcode_t Code) {
  //DEFINE_FUNCTION("TCGraphErrorFunction()");
  TCHAR* pErrMessage;

	/* Retrieve the error message from the library */
  pErrMessage = grapherrormsg((int)Code);

	/* Ensure the message is valid */
  if (pErrMessage == NULL) return (_T("Invalid graphics error code!"));
  return (pErrMessage);
 }
/*===========================================================================
 *		End of Function TCGraphErrorFunction()
 *=========================================================================*/
#endif


#if defined(_WIN32) || defined(__BCPLUSPLUS__)
/*===========================================================================
*
 * Function - TCHAR* WindowsErrorFunction (Code);
 *
 * Returns the error message associated with the given windows error code
 * as returned by GetLastError(). Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR* WindowsErrorFunction (const errcode_t Code) {
  //DEFINE_FUNCTION("WindowsErrorFunction()");
  static TCHAR ErrMessage[512] = _T("");
  DWORD Result;

	/* Format message string */
#if defined(__BCPLUSPLUS__)
  Result = sprintf (ErrMessage, _T("Windows 16-bit error code = %ld (0x%04X)"), Code, Code);

#else
  Result = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, (DWORD) Code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		&ErrMessage[0], 511, NULL);
#endif

	/* Ensure the message is valid */
  if (Result == 0) return (_T("Error creating Windows error message!"));
  return (ErrMessage);
 }
/*===========================================================================
 *		End of Function WindowsErrorFunction()
 *=========================================================================*/
#endif



/*===========================================================================
 *
 * Begin Module Test Routines
 *
 * Debug builds only test routines for this module.
 *
 *=========================================================================*/
#if defined(_DEBUG)

	/* Turn off several warnings associated with the test code */
#if defined(__BCPLUSPLUS__)
  #pragma warn -rch
  #pragma warn -ccc
#endif

/*===========================================================================
 *
 * Function - TCHAR* Test_CustomErrorFunc (const errcode_t Code);
 *
 * Test for the custom error function.  Returns test error messages 
 * depending on the value of the input error code.  Always returns
 * a valid string.
 *
 *=========================================================================*/
TCHAR* Test_CustomErrorFunc (const errcode_t Code) {
  //DEFINE_FUNCTION("Test_CustomErrorFunc()");

  switch (Code) {
    case TEST_ERR1: return (_T("Test Error 1"));
    case TEST_ERR2: return (_T("Test Error 2"));
    case TEST_ERR3: return (_T("Test Error 3"));
    case TEST_ERR4: return (_T("Test Error 4"));
    default:	    return (_T("Unknown Test Error Code"));
   }
 }
/*===========================================================================
 *		End of Function Test_CustomErrorFunc()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_AddError (void);
 *
 * Tests the Add() method of the CErrorDatabase class.
 *	1. Add errors with/without default error level.
 *	2. Addition of duplicate error codes
 *	3. Indirectly tests the Find() method.
 * Function ASSERTs on any error. Results are output to the SystemLog.
 *
 *=========================================================================*/
void Test_AddError (void) {
  DEFINE_FUNCTION("Test_AddError()");
  CErrorRecord* pFindRecord;

  SystemLog.Printf (stdout, _T("================ Test_AddError() ==================="));

	/* Test the addition of errors to the database */
  ErrorDatabase.Add(TEST_ERR1, _T("Test error code 1 message"));
  ErrorDatabase.Add(TEST_ERR2, _T("Test error code 2 message"), ERRLEVEL_WARNING);

	/* Check to ensure TEST_ERR1 was correctly stored */
  pFindRecord = ErrorDatabase.Find(TEST_ERR1);
  ASSERT(pFindRecord != NULL);
  ASSERT(pFindRecord->GetCode() == TEST_ERR1);
  SystemLog.Printf (_T("TEST_ERR1 = '%s'"), pFindRecord->GetMsg());

  	/* Check to ensure TEST_ERR2 was correctly stored */
  pFindRecord = ErrorDatabase.Find(TEST_ERR2);
  ASSERT(pFindRecord != NULL);
  ASSERT(pFindRecord->GetCode() == TEST_ERR2);
  ASSERT(pFindRecord->GetLevel() == ERRLEVEL_WARNING);
  SystemLog.Printf (_T("TEST_ERR2 = '%s'"), pFindRecord->GetMsg());

	/* Attempt to add a duplicate error code */
  ErrorDatabase.Add(TEST_ERR2, _T("Test error code 2a message"), ERRLEVEL_CRITICAL);
  pFindRecord = ErrorDatabase.Find(TEST_ERR2);
  ASSERT(pFindRecord != NULL);
  SystemLog.Printf (_T("TEST_ERR2a = '%s'"), pFindRecord->GetMsg());
 }
/*===========================================================================
 *		End of Function Test_AddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_AddCustomError (void);
 *
 * Tests the addition of a custom error to the database.
 *	1. Add the error and ensure it was correctly added.
 *	2. Test the retrieval of various valid/invalid error sub-codes.
 *	3. Indirectly tests the Find() method.
 *
 *=========================================================================*/
void Test_AddCustomError (void) {
  DEFINE_FUNCTION("Test_AddCustomError()");
  CErrorRecord* pFindRecord;

  SystemLog.Printf (stdout, _T("================ Test_AddCustomError() ==================="));

	/* Add the custom error */
  ErrorDatabase.AddCustomError(TEST_ERR3, Test_CustomErrorFunc);
  pFindRecord = ErrorDatabase.Find(TEST_ERR3);
  ASSERT(pFindRecord != NULL);

	/* Test the retrieval of various custom error messages */
  SystemLog.Printf (_T("CustomError(ERR_NONE) = '%s'"), pFindRecord->GetMsg(ERR_NONE));
  SystemLog.Printf (_T("CustomError(TEST_ERR1) = '%s'"), pFindRecord->GetMsg(TEST_ERR1));
  SystemLog.Printf (_T("CustomError(TEST_ERR4) = '%s'"), pFindRecord->GetMsg(TEST_ERR4));
  
 }
/*===========================================================================
 *		End of Function Test_AddCustomError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_DefaultErrors (void);
 *
 * Tests the default errors in the CErrorDatabase class.
 *	1. Checks and outputs each default error message.
 *	2. Clears database and reinitializes default errors.
 *	3. Attempts to re-add default errors without clearing database.
 *	4. Indirectly tests the Find() and GetNumErrors() methods.
 * Function ASSERTs on any error.  Results are output to the SystemLog.
 *
 *=========================================================================*/
void Test_DefaultErrors (void) {
  DEFINE_FUNCTION("Test_DefaultErrors()");
  CErrorRecord* pFindRecord;
  signed int	ErrorCounter;

	/* Default errors to test, ERR_NONE must be last in array */
  errcode_t DefaultErrors[] = { ERR_MEM, ERR_OPENFILE, ERR_READFILE, ERR_WRITEFILE,
			        ERR_OVERFLOW, ERR_BADINPUT, ERR_BADARRAYINDEX, ERR_MAXINDEX,
			        ERR_SYSTEM, ERR_NONE };

  SystemLog.Printf (stdout, _T("================ Test_DefaultErrors() ==================="));

	/* Test all error codes in the DefaultErrors[] array */
  ErrorCounter = -1;

  do {
    ErrorCounter++;

    pFindRecord = ErrorDatabase.Find(DefaultErrors[ErrorCounter]);
    ASSERT(pFindRecord != NULL);
    SystemLog.Printf (_T("%2d) DefaultError(%2ld) = '%s'"), ErrorCounter, DefaultErrors[ErrorCounter], pFindRecord->GetMsg());

  } while (DefaultErrors[ErrorCounter] != ERR_NONE);

	/* Clear errors and retinitialize */
  ErrorCounter = ErrorDatabase.GetNumErrors();
  ErrorDatabase.ClearErrors();
  ASSERT(ErrorDatabase.GetNumErrors() == 0);
  ErrorDatabase.InitDefaultErrors();
  ASSERT(ErrorDatabase.GetNumErrors() == ErrorCounter);

	/* Attempt to re-add the default errors to database */
  ErrorDatabase.InitDefaultErrors();
  ASSERT(ErrorDatabase.GetNumErrors() == ErrorCounter);

 }
/*===========================================================================
 *		End of Function Test_DefaultErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_GetLastErrorMsg (void);
 *
 * Tests the CErrorHandler::GetLastErrorMsg() and GetLastErrorDBMsg() methods.
 *	1. Test with valid incidents/errors
 *	2. Test with invalid error codes
 *	3. Test with invalid incidents
 *
 *=========================================================================*/
void Test_GetLastErrorMsg (void) {
  //DEFINE_FUNCTION("Test_GetLastErrorMsg()");

  SystemLog.Printf (stdout, _T("================ Testing GetLastErrorMsg() ==================="));

	/* Test with valid incidents/errors */
  ErrorHandler.AddError(ERR_OPENFILE, _T("Test incident error message, %s, %d"), _T("test string"), 10101);
  SystemLog.Printf(_T("\t***Good Code with Msg = %s"), ErrorHandler.GetLastErrorMsg());
  ErrorHandler.AddError(ERR_SYSTEM, ENOENT, _T("Test incident system error message, %s, %d"), _T("test string"), 10101);
  SystemLog.Printf(_T("\t***System Code With Msg = %s"), ErrorHandler.GetLastErrorMsg());
  ErrorHandler.AddError(ERR_SYSTEM, ENOENT, NULL);
  SystemLog.Printf(_T("\t***System Code no Msg = %s"), ErrorHandler.GetLastErrorMsg());

	/* Test with invalid error codes */
  ErrorHandler.AddError(1414, 111, _T("Test invalid incident error message, %s, %d"), _T("test string"), 10101);
  SystemLog.Printf(_T("\t***Bad Code with Msg = %s"), ErrorHandler.GetLastErrorMsg());

	/* Test with invalid error incidents */
  ErrorHandler.ClearErrors();
  SystemLog.Printf(_T("\t***No Errors = %s"), ErrorHandler.GetLastErrorMsg());
  ErrorHandler.AddError(ERR_MEM, (TCHAR*)NULL);
  SystemLog.Printf(_T("\t***Good Code, No Msg = %s"), ErrorHandler.GetLastErrorMsg());
  ErrorHandler.AddError(123, (TCHAR*)NULL);
  SystemLog.Printf(_T("\t***Bad Code, No Msg = %s"), ErrorHandler.GetLastErrorMsg());
 }
/*===========================================================================
 *		End of Function Test_GetLastErrorMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_HandlerAddError (void);
 *
 * Tests the addition of errors to the ErrorHandler list.
 *	1. Tests the AddError() methods with a variety of inputs.
 *
 *
 *=========================================================================*/
void Test_HandlerAddError (void) {
  //DEFINE_FUNCTION("Test_HandlerAddError()");

  SystemLog.Printf (stdout, _T("================ Test_HandlerAddError() ==================="));

	/* Test the standard AddError() method */
  ErrorHandler.AddError(ERR_MEM,	_T("Testing...Failed to allocate memory"));
  ErrorHandler.AddError(ERR_BADINPUT,	_T("Testing ERR_BADINPUT (%s), 101 = %d"), _T("ERR_BADINPUT"), 101);
  ErrorHandler.AddError(ERR_NONE,	_T("Testing ERR_NONE"));
  ErrorHandler.AddError(TEST_ERR1,	_T("Testing TEST_ERR1"));
  ErrorHandler.AddError(TEST_ERR3,	_T("Testing TEST_ERR3 with no subcode"));
  ErrorHandler.AddError(TEST_ERR5,	_T("Testing invalid error code TEST_ERR5"));
  ErrorHandler.AddError(ERR_MEM, NULL);
  ErrorHandler.AddError(ERR_MEM, (TCHAR*)NULL);

	/* Test the sub-code AddError() method */
  ErrorHandler.AddError(ERR_MEM,   ERR_MEM,   _T("Testing ERR_MEM subcode version"));
  ErrorHandler.AddError(ERR_NONE,  ERR_NONE,  _T("Testing ERR_NONE subcode version, %s, %d"), _T("ERR_NONE"), 101);
  ErrorHandler.AddError(TEST_ERR5, TEST_ERR5, _T("Testing invalid error code TEST_ERR5 with subcode TEST_ERR5"));
  ErrorHandler.AddError(TEST_ERR3, TEST_ERR1, _T("Testing TEST_ERR3 with subcode TEST_ERR1"));
  ErrorHandler.AddError(TEST_ERR3, TEST_ERR1, _T("Testing TEST_ERR3 with subcode TEST_ERR1 (%s, %d)"), _T("TEST_ERR1"), 101);
  ErrorHandler.AddError(TEST_ERR3, TEST_ERR3, _T("Testing TEST_ERR3 with subcode TEST_ERR3"));
  ErrorHandler.AddError(TEST_ERR3, TEST_ERR5, _T("Testing TEST_ERR3 with subcode TEST_ERR5"));
  ErrorHandler.AddError(ERR_SYSTEM, EACCES,   _T("Testing ERR_SYSTEM with subcode EACCES"));
  ErrorHandler.AddError(ERR_MEM,   ERR_MEM, NULL);
  ErrorHandler.AddError(ERR_MEM,   ERR_MEM, NULL);
 }
/*===========================================================================
 *		End of Function Test_HandlerAddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_HandlerNotify (void);
 *
 * Tests the Notify() method of the CErrorHandler class.
 *	1. Call Notify() for the current errors in the incident list.
 *	2. Tests the PopError() method to remove errors from handler.
 *
 *=========================================================================*/
void Test_HandlerNotify (void) {
  DEFINE_FUNCTION("Test_HandlerNotify()");
  CErrorIncident* pErrorIncident;

	/* Test the Notify() method with a given title */
  ErrorHandler.Notify(_T("Test Title"));

	/* Output all errors in the incident list */
  while (ErrorHandler.GetNumErrors() > 0) {
    ErrorHandler.Notify();

		/* Delete the error from the handler */
    pErrorIncident = ErrorHandler.PopError(); 
    ASSERT(pErrorIncident != NULL);
    DestroyPointer(pErrorIncident);
   }

 }
/*===========================================================================
 *		End of Function Test_HandlerNotify()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_SystemErrors (void);
 *
 * Tests the custom error system codes.
 *	1. Ensures the system error exists in the database.
 *	2. Checks default message output
 *	3. Tests each system error codes, outputting message to SystemLog
 *	4. Check a number of invalid system error codes
 *
 *=========================================================================*/
void Test_SystemErrors (void) {
  DEFINE_FUNCTION("Test_SystemErrors()");
  CErrorRecord* pSystemError;
  int	        LoopCounter;

  SystemLog.Printf (stdout, _T("================ Test_SystemErrors() ==================="));

	/* Attempt to retrieve the system error record */
  pSystemError = ErrorDatabase.Find(ERR_SYSTEM);
  ASSERT(pSystemError != NULL);

	/* Output default error message output */
  SystemLog.Printf (_T("Default System Error Message = '%s'"), pSystemError->GetMsg());

	/* Output message for each valid system error */
  for (LoopCounter = 0; LoopCounter < _sys_nerr; LoopCounter++) {
    SystemLog.Printf (_T("%2d) System Error = '%s'"), LoopCounter, pSystemError->GetMsg(LoopCounter));
    ASSERT(pSystemError->GetMsg(LoopCounter) != NULL);
   }

	/* Output a few invalid system error codes */
  SystemLog.Printf (_T("System Error( 105) = '%s'"), pSystemError->GetMsg(105));
  SystemLog.Printf (_T("System Error(1111) = '%s'"), pSystemError->GetMsg(1111));
 }
/*===========================================================================
 *		End of Function Test_SystemErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_Allocation (void);
 *
 * Continually allocates and deletes errors and incidents to ensure reliability
 * in the long term.
 *
 *=========================================================================*/
void Test_Allocation (void) {
  DEFINE_FUNCTION("Test_Allocation()");
  TCHAR MsgBuffer[101];
  int  LoopCounter;
  int  ErrorCounter;
  int  NumAllocations;

  SystemLog.Printf (stdout, _T("================ Start of Test_Allocation() ============"));

	/* Reset the current incident and database lists */
  ErrorHandler.ClearErrors();
  ErrorDatabase.ClearErrors();

	/* Number of test loops */
  for (LoopCounter = 0; LoopCounter < 1000; LoopCounter++) {
    NumAllocations = (int) ((float)rand() * 10000 / RAND_MAX);
    SystemLog.Printf (stdout, _T("================ Starting Test %d With %d Allocations ============"), LoopCounter, NumAllocations);
    TFPRINTF (stderr, _T("Test %d (%d)..."), LoopCounter, NumAllocations);
    	
    for (ErrorCounter = 0; ErrorCounter < NumAllocations; ErrorCounter++) {
      snprintf (MsgBuffer, 101, _T("Error message %d of %d "), ErrorCounter, NumAllocations);
      ErrorDatabase.Add(ErrorCounter, MsgBuffer);
      ErrorHandler.AddError(ErrorCounter, _T("Testing error code %d of %d"), ErrorCounter, NumAllocations);
     }

		/* Reset the incident and database lists */
    SystemLog.Printf (stdout, _T("================ Clearing %d Allocated Errors ============"), NumAllocations);
    ErrorHandler.ClearErrors();
    ErrorDatabase.ClearErrors();
    OutputBlockInfo();

		/* Ensure the debug heap is still error free */
    ASSERT(DebugHeapCheckMemory());

    TFPRINTF (stderr, _T("%u blocks remained after deletion.\n"), GetNumBlocks());
   }

  SystemLog.Printf (stdout, _T("================ End of Test_Allocation() ============"));
 }
/*===========================================================================
 *		End of Function Test_Allocation()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_DLErr (void);
 *
 * Main test routine for the module.
 *	1. Tests the default error codes in the error database
 *	2. Tests the custom system error codes
 *	3. Tests the addition of regular errors to the database.
 *	4. Tests the addition of custom errors to the database
 *	5. Tests additition of errors to the ErrorHandler object.
 *	6, Tests the Notify()/PopError() methods of the ErrorHandler object.
 *	7. Clears all errors/incidents and outputs allocated blocks.
 *	8. Tests reliability of repeated number of allocations/deletions
 *	9. Tests the GetLastErrorMsg() and GetLastErrorDBMsg() methods
 *
 *=========================================================================*/
void Test_DLErr (void) {
  DEFINE_FUNCTION("Test_DLErr()");

  ASSERT(DebugHeapCheckMemory());
  SystemLog.Printf (stdout, _T("================ Test_DLErr() ==================="));
  
  Test_DefaultErrors();
  Test_SystemErrors();
  Test_AddError();
  Test_AddCustomError();
  Test_HandlerAddError();
  Test_GetLastErrorMsg();
  //Test_HandlerNotify();
  //ErrorHandler.Exit("Exiting Application");

  ASSERT(DebugHeapCheckMemory());

  SystemLog.Printf(stdout, _T("========== Output Current Allocated Blocks =========="));
  OutputBlockInfo();
  SystemLog.Printf(stdout, _T("========== Deleting Error Incidents and Database =========="));
  ErrorHandler.ClearErrors();
  ErrorDatabase.ClearErrors();
  OutputBlockInfo();
  ASSERT(DebugHeapCheckMemory());

  SystemLog.Printf (stdout, _T("================ End of Test_DLErr() ==================="));

  //Test_Allocation();
 }
/*===========================================================================
 *		End of Function Test_DLErr()
 *=========================================================================*/

	/* Restore compiler warning options */
#if defined(__BCPLUSPLUS__)
  #pragma warn .rch
  #pragma warn .ccc
#endif  

#endif
/*===========================================================================
 *		End of Module Test Routines
 *=========================================================================*/
