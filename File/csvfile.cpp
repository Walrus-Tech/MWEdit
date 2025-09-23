/*===========================================================================
 *
 * File:    CsvFile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, October 09, 2003
 *
 * Implements a simple CSV (Comma Seperated File) class, CCsvFile.
 *
 *=========================================================================*/
#include "csvFile.h"


DEFINE_FILE("CsvFile.cpp");


/*===========================================================================
 *
 * Class CCsvFile Constructor
 *
 *=========================================================================*/
CCsvFile::CCsvFile() : m_Rows(0) {
	//DEFINE_FUNCTION("CCsvFile::CCsvFile()");
	m_KeepQuotes = false;
}


/*===========================================================================
 *
 * Class CCsvFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CCsvFile::Destroy() {
	//DEFINE_FUNCTION("CCsvFile::Destroy()");
	m_Filename.Empty();
	ClearRows();
}


/*===========================================================================
 *
 * Class CCsvFile Method - CCsvRow* AddRow (void);
 *
 * Adds a new row to the end of the CSV file. Returns the new object or
 * NULL on any error.
 *
 *=========================================================================*/
CCsvRow *CCsvFile::AddRow() {
	DEFINE_FUNCTION("CCsvFile::AddRow()");
	CCsvRow *pRow;
	CreateClassPointer(pRow, CCsvRow, 0);
	m_Rows.Add(pRow);
	return pRow;
}


/*===========================================================================
 *
 * Class CCsvFile Method - void ClearRows (void);
 *
 * Deletes all defined row objects.
 *
 *=========================================================================*/
void CCsvFile::ClearRows() {
	DEFINE_FUNCTION("CCsvFile::ClearRows()");
	CCsvRow *pRow;
	int Index;

	for (Index = 0; Index < m_Rows.GetNumElements(); Index++) {
		pRow = m_Rows.GetAt(Index);
		DestroyPointer(pRow);
	}

	m_Rows.RemoveAll();
}


/*===========================================================================
 *
 * Class CCsvFile Method - int FindHeaderCol (pString);
 *
 * Looks for the given string in the header column, returning the 0-based
 * column index on success or -1 otherwise. Not case-sensitive.
 *
 *=========================================================================*/
int CCsvFile::FindHeaderCol(const TCHAR *pString) {
	CCsvRow *pRow;
	CSString *pColString;
	int ColIndex;
	/* Get the header row */
	pRow = GetRow(0);

	if (pRow == NULL) {
		return -1;
	}

	for (ColIndex = 0; ColIndex < pRow->GetNumElements(); ColIndex++) {
		pColString = pRow->GetAt(ColIndex);

		if (pColString == NULL) {
			continue;
		}

		if (pColString->CompareNoCase(pString) == 0) {
			return ColIndex;
		}
	}

	/* No match */
	return -1;
}


/*===========================================================================
 *
 * Class CCsvFile Method - const TCHAR* GetElement (Row, Col);
 *
 * Returns the text of the given CSV element (0-based) or NULL.
 *
 *=========================================================================*/
const TCHAR *CCsvFile::GetElement(const int Row, const int Col) {
	if (!IsValidElement(Row, Col)) {
		return NULL;
	}

	return (const TCHAR *)*((m_Rows.GetAt(Row))->GetAt(Col));
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool IsMissingCells (void);
 *
 * Returns true if there are any missing or empty cells in the file.
 *
 *=========================================================================*/
bool CCsvFile::IsMissingCells() {
	int RowIndex;
	bool Result;

	/* Check all rows */
	for (RowIndex = 0; RowIndex < m_Rows.GetNumElements(); RowIndex++) {
		Result = IsRowMissingCells(RowIndex);

		if (Result) {
			return true;
		}
	}

	/* No missing/empty cells found */
	return false;
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool IsRowMissingCells (RowIndex);
 *
 * Returns true if the given row has any missing or empty cells.
 *
 *=========================================================================*/
bool CCsvFile::IsRowMissingCells(const int RowIndex) {
	CCsvRow *pRow;
	CSString *pColString;
	int ColIndex;
	pRow = GetRow(RowIndex);

	if (pRow == NULL) {
		return true;
	}

	/* Check all columns in the row */
	for (ColIndex = 0; ColIndex < pRow->GetNumElements(); ColIndex++) {
		pColString = pRow->GetAt(ColIndex);

		if (pColString == NULL) {
			return true;
		}

		if (pColString->IsEmpty()) {
			return true;
		}
	}

	return false;
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool IsValidElement (Row, Col);
 *
 * Returns true if the given CSV element coordinates are valid (0-based).
 *
 *=========================================================================*/
bool CCsvFile::IsValidElement(const int Row, const int Col) {
	if (!m_Rows.IsValidIndex(Row)) {
		return false;
	}

	CCsvRow *pRow = m_Rows.GetAt(Row);

	if (pRow == NULL) {
		return false;
	}

	if (!pRow->IsValidIndex(Col)) {
		return false;
	}

	if (pRow->GetAt(Col) == NULL) {
		return false;
	}

	return true;
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool Load (pFilename);
 *
 * Attempt to load and parse the given CSV file, returning false on
 * any error. The current contents are destroyed.
 *
 *=========================================================================*/
bool CCsvFile::Load(const TCHAR *pFilename) {
	CGenFile File;
	CSString Buffer;
	bool Result;
	int FileSize;
	/* Clear the current contents */
	Destroy();
	/* Attempt to openb the given file for input */
	Result = File.Open(pFilename, "rb");

	if (!Result) {
		return false;
	}

	m_Filename = pFilename;
	FileSize = File.GetFileSize();
	Buffer.SetSize(FileSize);
	/* Read the file text */
	Result = File.Read((TCHAR *)(const TCHAR *)Buffer, FileSize);

	if (!Result) {
		return false;
	}

	/* Parse the file text */
	Result = ParseText(Buffer, FileSize);
	return true;
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool ParseText (pBuffer, BufferSize);
 *
 * Protected class method to parse a text buffer into the CSV row/column
 * components. Returns false on any error.
 *
 *=========================================================================*/
bool CCsvFile::ParseText(const TCHAR *pBuffer, const int BufferSize) {
	DEFINE_FUNCTION("CCsvFile::ParseText()");
	const TCHAR *pParse;
	const TCHAR *pQuoteStart;
	const TCHAR *pRowStart;
	const TCHAR *pColStart;

	CSString QuoteBuffer;
	CSString CellBuffer;
	CSString *pNewString;
	CCsvRow *pRow;

	bool InQuote;
	bool HasQuote;
	bool EndCell;
	bool EndRow;
	int Index;

	/* Initialize the loop variables */
	pParse = pBuffer;
	pQuoteStart = NULL;
	pRowStart = pBuffer;
	pColStart = pBuffer;
	InQuote = false;
	HasQuote = false;
	EndCell = false;
	EndRow = false;
	Index = 0;
	/* Create the first row */
	pRow = AddRow();

	/* Parse the entire buffer string */
	while (Index <= BufferSize) {
		switch (*pParse) {
			case CSVFILE_COLCHAR:
				if (!InQuote) {
					EndCell = true;
				}

				break;

			case NULL_CHAR:
				if (pParse[-1] == CSVFILE_ROWCHAR1) {
					break;
				}

				if (pParse[-1] == CSVFILE_ROWCHAR2) {
					break;
				}

			case CSVFILE_ROWCHAR2:
				EndCell = true;
				EndRow = true;

				if (InQuote) {
					HasQuote = true;
					QuoteBuffer.Copy(pQuoteStart + 1, (int)(pParse - pQuoteStart - 1));
					InQuote = false;
				}

				break;

			case CSVFILE_QUOTECHAR:
				if (!m_KeepQuotes) {
					if (InQuote) {
						HasQuote = true;
						QuoteBuffer.Copy(pQuoteStart + 1, (int)(pParse - pQuoteStart - 1));
					} else {
						QuoteBuffer.Empty();
						pQuoteStart = pParse;
					}

					InQuote = !InQuote;
					break;
				}
		};

		/* Finish a cell parse */
		if (EndCell) {
			CreatePointer(pNewString, CSString);
			pRow->Add(pNewString);

			if (HasQuote) {
				*pNewString = QuoteBuffer;
			} else if (pParse != pColStart) {
				pNewString->Copy(pColStart, (int)(pParse - pColStart));
				pNewString->Trim();
			}

			HasQuote = false;
			EndCell = false;
			pColStart = pParse + 1;
		}

		/* End of a row */
		if (EndRow) {
			pRow = AddRow();

			if (pParse[1] == CSVFILE_ROWCHAR1) {
				pParse++;
				Index++;
			}

			pRowStart = pParse + 1;
			pColStart = pRowStart;
			EndRow = false;
		}

		Index++;
		pParse++;
	}

	/* Delete the last row if it is empty */
	if (pRow->GetNumElements() == 0) {
		m_Rows.DeleteElement(m_Rows.GetNumElements() - 1);
		DestroyPointer(pRow);
	}

	return true;
}


/*===========================================================================
 *
 * Class CCsvFile Method - bool Save (pFilename);
 *
 * Attempts to save the csv file to the given filename. Returns false on
 * any error.
 *
 *=========================================================================*/
bool CCsvFile::Save(const TCHAR *pFilename) {
	CGenFile File;
	CCsvRow *pRow;
	CSString *pString;
	int RowIndex;
	int ColIndex;
	bool Result;
	/* Attempt to open the file for output */
	Result = File.Open(pFilename, "wb");

	if (!Result) {
		return false;
	}

	m_Filename = pFilename;

	for (RowIndex = 0; RowIndex < m_Rows.GetNumElements(); RowIndex++) {
		pRow = m_Rows.GetAt(RowIndex);

		if (pRow == NULL || pRow->GetNumElements() == 0) {
			continue;
		}

		for (ColIndex = 0; ColIndex < pRow->GetNumElements(); ColIndex++) {
			pString = pRow->GetAt(ColIndex);
			Result = true;

			if (ColIndex > 0) {
				Result = File.Printf(_T(","));
			}

			if (pString != NULL) {
				Result = File.Printf(_T("\"%s\""), *pString);
			}

			if (!Result) {
				return false;
			}
		}

		File.Printf(_T("\n"));
	}

	return true;
}


/*===========================================================================
 *
 * Class CCsvFile Method - CSString* SetString (Row, Col, pString);
 *
 * Sets the given string. Returns the new string on NULL on any error.
 *
 *=========================================================================*/
CSString *CCsvFile::SetString(const int Row, const int Col, const TCHAR *pString) {
	DEFINE_FUNCTION("CCsvFile::SetString()");
	CCsvRow *pRow;
	CSString *pNewString;

	/* Ignore invalid input */
	if (Row < 0 || Col < 0) {
		return NULL;
	}

	pRow = GetRow(Row);

	/* Create the row if required */
	if (pRow == NULL) {
		while (m_Rows.GetNumElements() <= Row) {
			pRow = AddRow();
		}
	}

	/* Create the column if required */
	pNewString = pRow->GetAt(Col);

	if (pNewString == NULL) {
		while (pRow->GetNumElements() <= Col) {
			CreatePointer(pNewString, CSString);
			pRow->Add(pNewString);
		}
	}

	/* Set the string value */
	(*pNewString) = pString;
	return pNewString;
}
