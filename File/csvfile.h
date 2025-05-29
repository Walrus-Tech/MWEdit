/*===========================================================================
 *
 * File:    CsvFile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, October 09, 2003
 *
 * Defines a simple CSV (Comma Seperated File) class, CCsvFile.
 *
 *=========================================================================*/
#ifndef __CSVFILE_H
#define __CSVFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "file/genfile.h"
#include "contain/temarray.h"
#include "contain/ptrarray.h"
#include "string/sstring.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* CSV file characters */
#define CSVFILE_COLCHAR   ','
#define CSVFILE_ROWCHAR1  '\r'
#define CSVFILE_ROWCHAR2  '\n'
#define CSVFILE_QUOTECHAR '"'

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Array of string objects */
typedef TTemplateArray<CSString> CCsvRow;

/* Array of CSV row points */
typedef TPtrArray<CCsvRow> CCsvRowArray;

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CCsvFile Definition
 *
 * For handling a simple CSV type data file.
 *
 *=========================================================================*/
class CCsvFile {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	CCsvRowArray m_Rows; /* CSV file rows */
	CSString m_Filename; /* The last known filename */

	bool m_KeepQuotes; /* Keep or parse quote files */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CCsvFile();
	virtual ~CCsvFile() {
		Destroy();
	}

	virtual void Destroy(void);

	/* Adds a row to the end of the csv file */
	CCsvRow *AddRow(void);

	/* Delete all row objects */
	void ClearRows(void);

	/* Find a specific column index */
	int FindHeaderCol(const TCHAR *pString);

	/* Access a CSV element text */
	const TCHAR *GetElement(const int Row, const int Col);
	CCsvRow *GetRow(const int Row) {
		return (IsValidRow(Row) ? m_Rows.GetAt(Row) : NULL);
	}

	/* Get class members */
	int GetNumLines(void) const {
		return (m_Rows.GetNumElements());
	}

	const TCHAR *GetFilename(void) const {
		return (m_Filename);
	}

	/* Is the element indices valid? */
	bool IsValidElement(const int Row, const int Col);
	bool IsValidRow(const int Row) {
		return (m_Rows.IsValidIndex(Row));
	}

	/* Check for missing/empty cells */
	bool IsMissingCells(void);
	bool IsRowMissingCells(const int RowIndex);

	/* Attempt to load a new CSV file */
	bool Load(const TCHAR *pFilename);

	/* Parse a CSV text buffer */
	bool ParseText(const TCHAR *pBuffer, const int Size);

	/* Attempt to save the CSV file */
	bool Save(const TCHAR *pFilename);

	/* Set a specific string */
	CSString *SetString(const int Row, const int Col, const TCHAR *pString);

	/* Set class members */
	void SetKeepQuotes(const bool Flag) {
		m_KeepQuotes = Flag;
	}

};

/*===========================================================================
 *      End of Class CCsvFile Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File CsvFile.H
 *=========================================================================*/
