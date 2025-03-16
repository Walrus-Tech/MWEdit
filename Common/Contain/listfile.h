/*===========================================================================
 *
 * File:    ListFile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, March 29, 2001
 *
 * Defines the CListFile class for handling files contain a list of
 * items, one per line.
 *
 *=========================================================================*/
#ifndef __LISTFILE_H
#define __LISTFILE_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "dl_err.h"
#include "dl_file.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Defines
 *
 *=========================================================================*/

/* Default maximum line length */
#define LISTFILE_LINE_LENGTH 256

/*===========================================================================
 *      End of Defines
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CListFile Definition
 *
 * A class for handling a file which contains a list of items, line by line.
 * The line is read one line at a time, returning the results to the user
 * when requested, so there is no overhead for storing the entire list.
 *
 *=========================================================================*/
class CListFile {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	char *pCurrentLine;     /* Holds the text of the current line */
	size_t MaxLineLength;    /* Maximum characters allowed per line */
	FILE *pFileHandle;      /* Handle to the list file */
	boolean BufferValid;      /* Is the current line buffer valid */
	boolean IgnoreBlankLines; /* An option of ignoring empty lines in file */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CListFile(const size_t LineLength = LISTFILE_LINE_LENGTH);
	virtual ~CListFile();
	virtual void Destroy (void);

	/* Close an open list file */
	void Close (void);

	/* Get class members */
	char *GetCurrentLine (void) const;
	int GetMaxLineLength (void) const;
	boolean GetIgnoreBlankLines (void) const;

	/* Is the list file currently open or not? */
	boolean IsOpen (void) const;

	/* Determine if the current line buffer is valid */
	boolean IsValidLine (void) const;

	/* Open and starting parsing a list file */
	boolean Open (const char* pFilename);

	/* Input one line from the list file */
	boolean ReadNextLine (void);

	/* Set class members */
	void SetIgnoreBlankLines (const boolean Value);

};

/*===========================================================================
 *      End of Class CListFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CListFile Inline Methods
 *
 *=========================================================================*/

/* Return the current line string buffer */
inline char *CListFile::GetCurrentLine (void) const {
	return (pCurrentLine);
}

/* Return the current maximum line length */
inline int CListFile::GetMaxLineLength (void) const {
	return (MaxLineLength);
}

/* Get the ignore empty line option */
inline boolean CListFile::GetIgnoreBlankLines (void) const {
	return (IgnoreBlankLines);
}

/* Returns TRUE if the current file is open */
inline boolean CListFile::IsOpen (void) const {
	return ((pFileHandle == NULL) ? FALSE : TRUE);
}

/* Determine if the current line buffer is valid */
inline boolean CListFile::IsValidLine (void) const {
	return (BufferValid);
}

/* Set the ignore empty line option */
inline void CListFile::SetIgnoreBlankLines (const boolean Value) {
	IgnoreBlankLines = Value;
}

/*===========================================================================
 *      End of CListFile Inline Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Test Function Prototypes
 *
 *=========================================================================*/
#if defined(_DEBUG)
	void Test_ListFile (void);
#endif
/*===========================================================================
 *      End of Test Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File ListFile.H
 *=========================================================================*/
