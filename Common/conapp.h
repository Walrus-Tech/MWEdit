/*===========================================================================
 *
 * File:    ConApp.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, December 06, 2000
 *
 * Defines the class CConsoleApp, used as a base class for simple
 * console (or command line) programs.
 *
 *=========================================================================*/
#ifndef __CONAPP_H
#define __CONAPP_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_err.h"
#include "dl_str.h"
#include "dl_file.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Defines
 *
 *=========================================================================*/

/* Defines a standard main routine */
#define STANDARD_CONSOLEAPP_MAIN(AppName) int main (int ArgCount, char* pArgs[]) { \
		return AppName.StartConsoleApp(ArgCount, &pArgs[0]); }

/* Custom class errors */
#define ERRCONAPP_NOHELP      2001
#define ERRCONAPP_BADLINESPERPAGE 2002

/*===========================================================================
 *      End of Defines
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Structure and Type Definitions
 *
 *=========================================================================*/

/* Used to determine the type of release */
typedef enum {
	RELEASE_UNKNOWN,
	RELEASE_DEBUG,
	RELEASE_ALPHA,
	RELEASE_BETA,
	RELEASE_FINAL
} release_t;

/* Return values for command line parameter parsing */
typedef enum {
	CMDPARSE_FAILED = -1,
	CMDPARSE_NOTPARSED = 0,
	CMDPARSE_SUCCESS = 1
} cmdparse_t;

/*===========================================================================
 *      End of Structure and Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CConsoleApp Definition
 *
 * Defines a base class from which applications can derive from to get
 * simple support for a console application.
 *
 *=========================================================================*/
class CConsoleApp {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	FILE *pOutputStream;      /* Destination of output */
	int NumArguments;       /* The program arguments data */
	char **pArguments;     /* Pointer to array of arguments */
	char *pProgramName;       /* Program name as given by argv[0] */

	char *pAppName;       /* Program information */
	char *pAppDate;
	char *pAppAuthor;
	char *pCompiledDate;

	int MajorVersion;       /* Versioning information */
	int MinorVersion;
	release_t ReleaseType;
	int BuildNumber;

	bool DoParseCommands;    /* Command line argument options */
	bool DoParseParameters;
	bool DoFlagParsing;

	bool DisplayTitle;       /* Display optioms */
	bool DoOpenLog;

	bool DoPaging;       /* Paging options */
	int LinesPerPage;
	int OutputLineCount;

	char **ppHelpText;     /* Help text for the application */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Registers any custom class errors */
	static bool AddClassErrors (void);

	/* Parses all the command line parameters */
	virtual bool ParseAllParameters (void);

	/* Parse the given command string */
	virtual cmdparse_t ParseCommand (char* pCommand, const bool Flag = TRUE);
	virtual cmdparse_t ParsePagingCommand (char* pString, const bool Flag);

	/* Parse the given parameter string */
	virtual cmdparse_t ParseOneParameter (char* pString);
	virtual cmdparse_t ParseParameter (char* pString);

	/* Main override for derived classes */
	virtual int StartApp (void);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CConsoleApp();
	virtual ~CConsoleApp() {
		Destroy();
	}

	virtual void Destroy (void);

	/* Aborts the program outputting an error message */
	virtual void AbortProgram (void);

	/* Get class members */
	virtual char *GetAppName (void);
// virtual char*     GetAppDate      (void);
// virtual char*     GetAppAuthor    (void);
// virtual char*     GetCompiledDate (void);
// virtual int       GetMajorVersion (void);
// virtual int       GetMinorVersion (void);
// virtual int     GetBuildNumber  (void);
// virtual release_t GetBuildType    (void);

	/* Opens the standard log file for debug builds */
	virtual bool OpenLog (void);

	/* Outputs the help screen for the program */
	virtual bool OutputHelp (void);

	/* Outputs a title information to the current output stream */
	virtual bool OutputTitle (void);
	virtual bool OutputVersion (void);

	/* Outputs a line printf() style to the desired output stream */
	virtual bool PrintLine (const char* pString = NULL, ...);

	/* Set class members */
	virtual void SetVersion (const int Major, const int Minor, const release_t Type);
	virtual void SetMajorVersion (const int Major);
	virtual void SetMinorVersion (const int Minor);
	virtual void SetReleaseType (const release_t Type);
	virtual void SetBuildNumber (const int Value);
	virtual void SetAppName (const char* pString);
	virtual void SetAppDate (const char* pString);
	virtual void SetAppAuthor (const char* pString);
	virtual void SetCompiledDate (const char* pString);
	virtual void SetHelpText (char** pText);
	virtual void SetDoPaging (const bool Flag);
	virtual void SetDoOpenLog (const bool Flag);

	/* Entry point for the class from main() */
	virtual int StartConsoleApp (const int ArgC, char* Argv[]);

};

/*===========================================================================
 *      End of Class CConsoleApp Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CConsoleApp Inline Methods
 *
 *=========================================================================*/

/* Get class members */
inline char *CConsoleApp::GetAppName (void) {
	return (pAppName);
}

/* Main protected override for derived classes */
inline int CConsoleApp::StartApp (void) {
	return (EXIT_SUCCESS);
}

/* Set the application version information */
inline void CConsoleApp::SetVersion (const int Major, const int Minor, const release_t Type) {
	MajorVersion = Major;
	MinorVersion = Minor;
	ReleaseType = Type;
}

/* Set the version members of application */
inline void CConsoleApp::SetMajorVersion (const int Major) {
	MajorVersion = Major;
}

inline void CConsoleApp::SetMinorVersion (const int Minor) {
	MinorVersion = Minor;
}

inline void CConsoleApp::SetReleaseType (const release_t Type) {
	ReleaseType = Type;
}

inline void CConsoleApp::SetBuildNumber (const int Value) {
	BuildNumber = Value;
}

/* Change the program identification strings */
inline void CConsoleApp::SetAppName (const char* pString) {
	ReplaceString(&pAppName, pString);
}

inline void CConsoleApp::SetAppDate (const char* pString) {
	ReplaceString(&pAppDate, pString);
}

inline void CConsoleApp::SetCompiledDate (const char* pString) {
	ReplaceString(&pCompiledDate, pString);
}

inline void CConsoleApp::SetAppAuthor (const char* pString) {
	ReplaceString(&pAppAuthor, pString);
}

inline void CConsoleApp::SetHelpText (char** ppText) {
	ppHelpText = ppText;
}

/* Set paging options */
inline void CConsoleApp::SetDoPaging (const bool Flag) {
	if (DoPaging != Flag) {
		OutputLineCount = 0;
	}

	DoPaging = Flag;
}

/* Set log options */
inline void CConsoleApp::SetDoOpenLog (const bool Flag) {
	DoOpenLog = Flag;
}

/*===========================================================================
 *      End of Class CConsoleApp Inline Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/* Return the current console application object */
CConsoleApp *GetConsoleApp (void);

/* Converts a release type to a printable output character */
char ReleaseTypeToChar (const release_t ReleaseType);

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File ConApp.H
 *=========================================================================*/
