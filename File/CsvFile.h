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


#include "Common/File/GenFile.h"
#include "Common/Contain/temarray.h"
#include "Common/Contain/PtrArray.h"
#include "Common/String/SString.h"


/* CSV file characters */
#define CSVFILE_COLCHAR   ','
#define CSVFILE_ROWCHAR1  '\r'
#define CSVFILE_ROWCHAR2  '\n'
#define CSVFILE_QUOTECHAR '"'


/* Array of string objects */
typedef TTemplateArray<CSString> CCsvRow;

/* Array of CSV row points */
typedef TPtrArray<CCsvRow> CCsvRowArray;


/*===========================================================================
 *
 * Begin Class CCsvFile Definition
 *
 * For handling a simple CSV type data file.
 *
 *=========================================================================*/
class CCsvFile {
  private:
	CCsvRowArray m_Rows; /* CSV file rows */
	CSString m_Filename; /* The last known filename */

	bool m_KeepQuotes;   /* Keep or parse quote files */


  public:
	/* Class Constructors/Destructors */
	CCsvFile();
	virtual ~CCsvFile() {
		Destroy();
	}

	virtual void Destroy();

	/* Adds a row to the end of the csv file */
	CCsvRow *AddRow();

	/* Delete all row objects */
	void ClearRows();

	/* Find a specific column index */
	int FindHeaderCol(const TCHAR *pString);

	/* Access a CSV element text */
	const TCHAR *GetElement(const int Row, const int Col);
	CCsvRow *GetRow(const int Row) {
		return IsValidRow(Row) ? m_Rows.GetAt(Row) : NULL;
	}

	/* Get class members */
	int GetNumLines() const {
		return m_Rows.GetNumElements();
	}

	const TCHAR *GetFilename() const {
		return m_Filename;
	}

	/* Is the element indices valid? */
	bool IsValidElement(const int Row, const int Col);
	bool IsValidRow(const int Row) {
		return m_Rows.IsValidIndex(Row);
	}

	/* Check for missing/empty cells */
	bool IsMissingCells();
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


#endif
