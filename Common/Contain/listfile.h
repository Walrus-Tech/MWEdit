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


#include "Common/dl_err.h"
#include "Common/dl_file.h"

/* Default maximum line length */
#define LISTFILE_LINE_LENGTH 256


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
  private:
	char *pCurrentLine;       /* Holds the text of the current line */
	size_t MaxLineLength;     /* Maximum characters allowed per line */
	FILE *pFileHandle;        /* Handle to the list file */
	boolean BufferValid;      /* Is the current line buffer valid */
	boolean IgnoreBlankLines; /* An option of ignoring empty lines in file */


  public:
	/* Class Constructors/Destructors */
	CListFile(const size_t LineLength = LISTFILE_LINE_LENGTH);
	virtual ~CListFile();
	virtual void Destroy();

	/* Close an open list file */
	void Close();

	/* Get class members */
	char *GetCurrentLine() const;
	int GetMaxLineLength() const;
	boolean GetIgnoreBlankLines() const;

	/* Is the list file currently open or not? */
	boolean IsOpen() const;

	/* Determine if the current line buffer is valid */
	boolean IsValidLine() const;

	/* Open and starting parsing a list file */
	boolean Open(const char *pFilename);

	/* Input one line from the list file */
	boolean ReadNextLine();

	/* Set class members */
	void SetIgnoreBlankLines(const boolean Value);
};

/* Return the current line string buffer */
inline char *CListFile::GetCurrentLine() const {
	return pCurrentLine;
}

/* Return the current maximum line length */
inline int CListFile::GetMaxLineLength() const {
	return MaxLineLength;
}

/* Get the ignore empty line option */
inline boolean CListFile::GetIgnoreBlankLines() const {
	return IgnoreBlankLines;
}

/* Returns TRUE if the current file is open */
inline boolean CListFile::IsOpen() const {
	return (pFileHandle == NULL) ? FALSE : TRUE;
}

/* Determine if the current line buffer is valid */
inline boolean CListFile::IsValidLine() const {
	return BufferValid;
}

/* Set the ignore empty line option */
inline void CListFile::SetIgnoreBlankLines(const boolean Value) {
	IgnoreBlankLines = Value;
}

#if _DEBUG
	void Test_ListFile();
#endif


#endif
