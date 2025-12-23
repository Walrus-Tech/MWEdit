/*===========================================================================
 *
 * File:    ConApp.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, December 06, 2000
 *
 * Contains the implementation for the CConsoleApp class providing a
 * base class for simple console applications.
 *
 * Steps to using CConsoleApp for your program:
 *
 *  1. Derive a class from CConsoleApp such as
 *      class CMyApp : public CConsoleApp {
 *  2. Add a global object of your class to your source code and
 *     the standard macro to create the main() routine.
 *      CMyApp theApp;
 *      STANDARD_CONSOLEAPP_MAIN(theApp);
 *  3. Create an array of strings that you wish to display for the
 *     program's help and set the ppHelpText class member to the
 *     first string in the array.  Don't forget to NULL terminate
 *     the array.
 *      char* pMyHelp[] = {
 *          "This is my simple console application",
 *          "",
 *          "\tUsage:   MyApp /?",
 *          NULL };
 *  4. Override the virtual methods ParseCommand() and ParseParameter()
 *     if you wish to handle any command line arguments passed to the
 *     program.  Remember to call the base class method if you wish to
 *     retain some of its capabilities.
 *  5. Override StartApp() to contain whatever it is your program does.
 *     Consider this just a different main() function.
 *
 * 18 September 2003
 *  - Replaced the 'boolean' type with 'bool'.
 *
 *=========================================================================*/
#include "Common/conapp.h"
#include <conio.h>
#include <ctype.h>


DEFINE_FILE("ConApp.cpp");

/* A pointer to the one and only console application object */
CConsoleApp *pTheConsoleApp = NULL;


/*===========================================================================
 *
 * Class CConsoleApp Constructor
 *
 *=========================================================================*/
CConsoleApp::CConsoleApp() {
	//DEFINE_FUNCTION("CConsoleApp::CConsoleApp()");
	/* Add the custom class errors only once */
	static bool InitErrors = AddClassErrors();
	/* Initialize the program command line arguments */
	NumArguments = 0;
	pArguments = NULL;
	pOutputStream = stdout;
	/* Initialize the program information */
	pProgramName = NULL;
	pAppName = CreateString(DL_BASE_NAME);
	pAppDate = CreateString(DL_BASE_DATE);
	pAppAuthor = CreateString(DL_BASE_AUTHOR);
	ppHelpText = NULL;
	/* Create the compiled-on date */
	pCompiledDate = CreateString(__DL_TIMESTAMP__);
	/* Set the initial version information */
	MajorVersion = 0;
	MinorVersion = 0;
	ReleaseType = RELEASE_UNKNOWN;
	BuildNumber = -1;
	/* Set the command parsing options */
	DoParseCommands = TRUE;
	DoParseParameters = TRUE;
	DoFlagParsing = TRUE;
	/* Set the various display options */
	DisplayTitle = TRUE;
	DoOpenLog = TRUE;
	/* Set the initial paging options */
	OutputLineCount = 0;
	DoPaging = TRUE;
	LinesPerPage = 23;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - void Destroy (void)
 *
 * Destroys or resets any class members.
 *
 *=========================================================================*/
void CConsoleApp::Destroy() {
	//DEFINE_FUNCTION("CConsoleApp::Destroy()");
	int LoopCounter;

	/* Delete the arguments array */
	for (LoopCounter = 0; LoopCounter < NumArguments; LoopCounter++) {
		DestroyArrayPointer(pArguments[LoopCounter]);
	}

	DestroyArrayPointer(pArguments);
	/* Delete any allocated strings */
	DestroyArrayPointer(pProgramName);
	DestroyArrayPointer(pAppName);
	DestroyArrayPointer(pAppDate);
	DestroyArrayPointer(pAppAuthor);
	DestroyArrayPointer(pCompiledDate);
	NumArguments = 0;
	OutputLineCount = 0;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool AddClassErrors (void)
 *
 * Static function which registers the custom errors for the class.
 *
 *=========================================================================*/
bool CConsoleApp::AddClassErrors() {
	//DEFINE_FUNCTION("CConsoleApp::AddClassErrors()");
	ErrorDatabase.Add(ERRCONAPP_NOHELP, "No help text was defined!", ERRLEVEL_WARNING);
	ErrorDatabase.Add(ERRCONAPP_BADLINESPERPAGE, "Bad lines per page value specified!");
	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - void AbortProgram (void)
 *
 * Aborts the program and outputs the error message in the ErrorHandler
 * object.  Method does not return.
 *
 *=========================================================================*/
void CConsoleApp::AbortProgram() {
	//DEFINE_FUNCTION("CConsoleApp::AbortProgram()");
	fprintf(pOutputStream, "   Program Error...Aborting!\n");
	fprintf(pOutputStream, "\t%s\n\n", ErrorHandler.GetLastErrorMsg());
	/* Exit program with failure code */
	exit(EXIT_FAILURE);
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool OpenLog (void)
 *
 * Opens a log file with the same name as the program with a LOG extension
 * for any debug builds.
 *
 *=========================================================================*/
bool CConsoleApp::OpenLog() {
	//DEFINE_FUNCTION("CConsoleApp::OpenLog()");
#if _DEBUG
	char LogFilename[_MAX_FNAME + 5] = "temp.log";
	/* Create a file with the new extension and attempt to open log */
	ChangeExtension(LogFilename, pProgramName, ".log", _MAX_FNAME + 4);
	return SystemLog.Open(LogFilename);
#else
	return TRUE;
#endif
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool OutputHelp (void)
 *
 * Output the application's help text.
 *
 *=========================================================================*/
bool CConsoleApp::OutputHelp() {
	//DEFINE_FUNCTION( "CConsoleApp::OutputHelp()");
	bool Result = TRUE;
	int LoopCounter = 0;

	/* Output title if not already output */
	if (!DisplayTitle) {
		Result = OutputTitle();
	}

	/* Ignore if no help text array defined */
	if (ppHelpText == NULL) {
		if (Result) {
			Result = PrintLine("\tNo help defined!");
		}

		ErrorHandler.AddError(ERRCONAPP_NOHELP);
		return Result;
	}

	/* Output the help text */
	while (ppHelpText[LoopCounter] != NULL) {
		Result = PrintLine(ppHelpText[LoopCounter]);

		if (!Result) {
			return FALSE;
		}

		LoopCounter++;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool OutputTitle (void)
 *
 * Outputs the standard application title to the current output stream.
 * Returns FALSE on any output error.
 *
 *=========================================================================*/
bool CConsoleApp::OutputTitle() {
	DEFINE_FUNCTION("CConsoleApp::OutputTitle()");
	int Result = 0;
	/* Ensure valid input */
	ASSERT(pOutputStream != NULL);

	/* Output the program name if present */
	if (pAppName) {
		Result = fprintf(pOutputStream, "%s ", pAppName);
	}

	/* Output the application version */
	if (Result >= 0) {
		Result = (OutputVersion() == TRUE) ? 0 : - 1;

		if (Result >= 0) {
			Result = fprintf(pOutputStream, ", ");
		}
	}

	/* Output application date, author name, and line feed */
	if (pAppDate && Result >= 0) {
		Result = fprintf(pOutputStream, "%s, ", pAppDate);
	}

	if (pAppAuthor && Result >= 0) {
		Result = fprintf(pOutputStream, "by %s", pAppAuthor);
	}

	if (Result >= 0) {
		Result = fprintf(pOutputStream, "\n");
	}

	/* Check for an error condition */
	if (Result < 0 || ferror(pOutputStream)) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Error writing to the output file stream!");
		return FALSE;
	}

	/* Increase the number of lines output and return success */
	OutputLineCount++;
	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool OutputVersion (void)
 *
 * Outputs the version information to the current output stream.
 *
 *=========================================================================*/
bool CConsoleApp::OutputVersion() {
	DEFINE_FUNCTION("CConsoleApp::OutputVersion()");
	int Result;
	/* Ensure a valid output stream handle */
	ASSERT(pOutputStream != NULL);
	Result = fprintf(pOutputStream,
	                 "v%0d.%0d%c",
	                 MajorVersion,
	                 MinorVersion,
	                 ReleaseTypeToChar(ReleaseType));

	if (Result >= 0 && ReleaseType != RELEASE_FINAL && BuildNumber >= 0) {
		Result = fprintf(pOutputStream, "(build %d)", BuildNumber);
	}

	/* Check for an error condition */
	if (Result < 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Error writing to the output file stream!");
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool ParseAllParameters (void)
 *
 * Parses each of the command line parameters.  Returns FALSE on any error.
 * Protected class method.
 *
 *=========================================================================*/
bool CConsoleApp::ParseAllParameters() {
	//DEFINE_FUNCTION("CConsoleApp::ParseAllParameters()");
	cmdparse_t Result;
	int LoopCounter;

	for (LoopCounter = 0; LoopCounter < NumArguments; LoopCounter++) {
		Result = ParseOneParameter(pArguments[LoopCounter]);

		if (Result == CMDPARSE_FAILED) {
			return FALSE;
		}
	}

	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - cmdparse_t ParseCommand (char* pCommand, const bool Flag)
 *
 * Parses the given command parameter string with the given flag.  Returns
 * CMDPARSE_FAILED on error, CMDPARSE_SUCCESS on success, and CMDPARSE_NOTPARSED
 * if the command was not parsed.
 *
 *=========================================================================*/
cmdparse_t CConsoleApp::ParseCommand(char *pCommand, const bool Flag) {
	//DEFINE_FUNCTION("CConsoleApp::ParseCommand()");
	switch (tolower(*pCommand)) {
		/* Standard help display, do not return but exit program */
		case '?':
		case 'h':
			OutputHelp();
			exit(EXIT_SUCCESS);

		/* Paging options */
		case 'p':
			return ParsePagingCommand(pCommand + 1, Flag);

		/* Unknown command option */
		default:
			return CMDPARSE_NOTPARSED;
	}
}


/*===========================================================================
 *
 * Class CConsoleApp Method - cmdparse_t ParseOneParameter (char* pString)
 *
 * Parses the given parameter string depending on the parsing options. Checks
 * to see if it is a command string and calls the ParseCommand() method if
 * required. Returns CMDPARSE_FAILED on any error, CMDPARSE_NOTPARSED if the
 * parameter could not be parsed for any reason and CMDPARSE_SUCCESS on
 * success.  Protected class method.
 *
 *=========================================================================*/
cmdparse_t CConsoleApp::ParseOneParameter(char *pString) {
	DEFINE_FUNCTION("CConsoleApp::ParseOneParameter()");
	bool CommandFlag = TRUE;
	int StringSize;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	pString = trim(pString);

	/* See if it can be parsed as a command first */
	if (DoParseCommands && (*pString == '/' || *pString == '-')) {
		pString++;

		/* Check for an initial -/+ flag */
		if (*pString == '-') {
			CommandFlag = FALSE;
			pString++;
		} else if (*pString == '+') {
			CommandFlag = TRUE;
			pString++;
		}

		StringSize = strlen(pString);

		/* Check for a terminating -/+ flag */
		if (pString[StringSize - 1] == '-') {
			CommandFlag = FALSE;
		} else if (pString[StringSize - 1] == '+') {
			CommandFlag = TRUE;
		}

		/* Parse the command parameter */
		return ParseCommand(pString, CommandFlag);
	}

	/* Default to parsing it as a regular parameter */
	return ParseParameter(pString);
}


/*===========================================================================
 *
 * Class CConsoleApp Method - cmdparse_t ParsePagingCommand (pString, Flag);
 *
 * Parses a paging option command string and returns CMDPARSE_SUCCESS or
 * CMDPARSE_FAILED on any error.
 *
 *=========================================================================*/
cmdparse_t CConsoleApp::ParsePagingCommand(char *pString, const bool Flag) {
	//DEFINE_FUNCTION("CConsoleApp::ParsePagingCommand()");

	/* Do we want to turn off paging? */
	if (!Flag) {
		DoPaging = FALSE;
		return CMDPARSE_SUCCESS;
	}

	/* Parse the number of lines per page from the string */
	LinesPerPage = atoi(pString);

	/* Ensure a valid number */
	if (LinesPerPage < 1) {
		DoPaging = FALSE;
		ErrorHandler.AddError(ERRCONAPP_BADLINESPERPAGE,
		                      "\tInvalid lines per page value specified (%d)!",
		                      LinesPerPage);
		return CMDPARSE_FAILED;
	}

	DoPaging = TRUE;
	return CMDPARSE_SUCCESS;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - cmdparse_t ParseParameter (pString)
 *
 * Parses the given parameter string.  Returns CMDPARSE_FAILED on any error,
 * CMDPARSE_NOTPARSED if the parameter could not be parsed for any reason
 * and CMDPARSE_SUCCESS on success.  Protected class method.
 *
 *=========================================================================*/
cmdparse_t CConsoleApp::ParseParameter(char */*pString*/ ) {
	//DEFINE_FUNCTION("CConsoleApp::ParseParameter()");
	/* Default to not parsing the parameter */
	return CMDPARSE_NOTPARSED;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - bool PrintLine (const char* pString, ...)
 *
 * Outputs one line to the current output file stream.  Supports paging
 * as per the values of the current LinesPerPage and DoPaging members.
 * Returns FALSE on any error.
 *
 *=========================================================================*/
bool CConsoleApp::PrintLine(const char *pString, ...) {
	//DEFINE_FUNCTION("CConsoleApp::PrintLine()");
	int Result = 0;
	va_list Args;

	/* Output the variable list of arguments */
	if (pString != NULL) {
		va_start(Args, pString);
		Result = vfprintf(pOutputStream, pString, Args);
		va_end(Args);
	}

	/* Output the line feed character */
	if (Result >= 0) {
		Result = fputs("\n", pOutputStream);
	}

	OutputLineCount++;

	/* Check for a paging condition */
	if (DoPaging && (OutputLineCount % LinesPerPage) == 0) {
		Result = fprintf(pOutputStream, "Press any key to continue...\n");
		int InputChar = getch();

		//getch();
		if (Result >= 0) {
			Result = fprintf(pOutputStream, "\n");
		}

		if (InputChar == ESC_CHAR) {
			ErrorHandler.AddError(ERR_BADINPUT, "Action aborted by used!");
			AbortProgram();
		}
	}

	/* Check for an error */
	if (Result < 0 || ferror(pOutputStream)) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, "Error writing to the output file stream!");
		return FALSE;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Class CConsoleApp Method - int StartConsoleApp (ArgCount, pArgs[])
 *
 * Entry point for the console app class.
 *
 *=========================================================================*/
int CConsoleApp::StartConsoleApp(const int ArgCount, char *pArgs[]) {
	DEFINE_FUNCTION("CConsoleApp::StartConsoleApp()");
	int LoopCounter;
	bool Result = TRUE;
	/* Set the global pointer to the console application */
	pTheConsoleApp = this;
	/* Allocate the program name */
	pProgramName = CreateString(pArgs[0]);
	NumArguments = ArgCount - 1;

	/* Allocate the arguments array */
	if (NumArguments > 0) {
		CreateArrayPointer(pArguments, char *, NumArguments);
	}

	/* Create the argument strings */
	for (LoopCounter = 0; LoopCounter < NumArguments; LoopCounter++) {
		pArguments[LoopCounter] = CreateString(pArgs[LoopCounter + 1]);
	}

	/* Create the standard log file */
	if (DoOpenLog) {
		Result = OpenLog();
	}

	/* Output the program title if required */
	if (Result && DisplayTitle) {
		Result = OutputTitle();
	}

	/* Parse any command line parameters if required */
	if (Result && DoParseParameters) {
		Result = ParseAllParameters();
	}

	if (!Result) {
		return EXIT_FAILURE;
	}

	/* Call the user's overridden method */
	return StartApp();
}


/*===========================================================================
 *
 * Function - CConsoleApp* GetConsoleApp (void)
 *
 * Returns the global console application object.
 *
 *=========================================================================*/
CConsoleApp *GetConsoleApp() {
	DEFINE_FUNCTION("GetConsoleApp()");
	ASSERT(pTheConsoleApp != NULL);
	return pTheConsoleApp;
}


/*===========================================================================
 *
 * Function - char ReleaseTypeToChar (ReleaseType);
 *
 * Converts a release type to a character for output.
 *
 *=========================================================================*/
char ReleaseTypeToChar(const release_t ReleaseType) {
	//DEFINE_FUNCTION("ReleaseTypeToChar()");
	switch (ReleaseType) {
		case RELEASE_UNKNOWN:
			return '?';

		case RELEASE_DEBUG:
			return 'd';

		case RELEASE_ALPHA:
			return 'a';

		case RELEASE_BETA:
			return 'b';

		case RELEASE_FINAL:
			return ' ';

		default:
			return '?';
	}
}
