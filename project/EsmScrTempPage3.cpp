/*===========================================================================
 *
 * File:    Esmscrtemppage3.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  October 8, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "project/StdAfx.h"
#include "project/MWEdit.h"
#include "project/EsmScrTempPage3.h"
#include "project/EsmScrTempView.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEsmScrTempPage3, CPropertyPage);
DEFINE_FILE("EsmScrTempPage2.cpp");


/*===========================================================================
 *
 * Begin Class CEsmScrTempPage3 Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CEsmScrTempPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CEsmScrTempPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Constructor
 *
 *=========================================================================*/
CEsmScrTempPage3::CEsmScrTempPage3() : CPropertyPage(CEsmScrTempPage3::IDD) {
	//{{AFX_DATA_INIT(CEsmScrTempPage3)
	//}}AFX_DATA_INIT
	m_pParentView = NULL;
	m_NumColumns = 0;
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Destructor
 *
 *=========================================================================*/
CEsmScrTempPage3::~CEsmScrTempPage3() {
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Method - bool AddCsvColumns (pCsvFile);
 *
 * Adds the columns to the list control for displaying the given CSV
 * file. Returns false on any error.
 *
 *=========================================================================*/
bool CEsmScrTempPage3::AddCsvColumns(CCsvFile *pCsvFile) {
	CCsvRow *pRow;
	CSString *pString;
	int Index;
	/* Get the header row */
	pRow = pCsvFile->GetRow(0);

	if (pRow == NULL) {
		ErrorHandler.AddError(ERR_BADINPUT, _T("CSV file has no defined header row!"));
		return false;
	}

	/* Insert the index column */
	m_CsvList.InsertColumn(0, _T(""), LVCFMT_CENTER, 25, 0);

	/* Add all columns in the header row */
	for (Index = 0; Index < pRow->GetNumElements(); Index++) {
		pString = pRow->GetAt(Index);

		if (pString == NULL) {
			m_CsvList.InsertColumn(Index + 1,
			                       _T("?"),
			                       LVCFMT_CENTER,
			                       ESMSCRTEMP_CSVLIST_COLWIDTH,
			                       Index + 1);
		} else {
			m_CsvList.InsertColumn(Index + 1,
			                       *pString,
			                       LVCFMT_CENTER,
			                       ESMSCRTEMP_CSVLIST_COLWIDTH,
			                       Index + 1);
		}
	}

	m_NumColumns = Index;
	return true;
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Method - void ClearCsvList (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmScrTempPage3::ClearCsvList() {
	//DEFINE_FUNCTION("CEsmScrTempPage3::ClearCsvList()");
	BOOL Result;
	/* Delete rows */
	m_CsvList.DeleteAllItems();

	/* Delete all columns */
	do {
		Result = m_CsvList.DeleteColumn(0);
	} while (Result);

	m_NumColumns = 0;
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CEsmScrTempPage3::DoDataExchange(CDataExchange *pDX) {
	CPropertyPage::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEsmScrTempPage3)
	DDX_Control(pDX, IDC_CSVLIST, m_CsvList);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Method - bool FillCsvList (pCsvFile);
 *
 * Updates the contents of the CSV list with the given CSV file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CEsmScrTempPage3::FillCsvList(CCsvFile *pCsvFile) {
	CCsvRow *pRow;
	CSString *pString;
	CString Buffer;
	int RowIndex;
	int ColIndex;
	int ItemIndex;
	int ListIndex;
	/* Clear the current list */
	ClearCsvList();
	/* Add the required columns for the file */
	AddCsvColumns(pCsvFile);
	ItemIndex = 0;

	/* Add the row data */
	for (RowIndex = 1; RowIndex < pCsvFile->GetNumLines(); RowIndex++) {
		pRow = pCsvFile->GetRow(RowIndex);

		if (pRow == NULL || pRow->GetNumElements() == 0) {
			continue;
		}

		/* Add a new item */
		Buffer.Format(_T("%d"), ItemIndex + 1);
		ListIndex = m_CsvList.InsertItem(ItemIndex, Buffer);

		for (ColIndex = 0; ColIndex < pRow->GetNumElements()
		                   && ColIndex < m_NumColumns; ColIndex++) {
			pString = pRow->GetAt(ColIndex);
			m_CsvList.SetItemText(ListIndex,
			                      ColIndex + 1,
			                      pString == NULL ? _T("") : static_cast<const char *>(*pString));
		}

		ItemIndex++;
	}

	return true;
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CEsmScrTempPage3::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	m_CsvList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;
}


/*===========================================================================
 *
 * Class CEsmScrTempPage3 Method - void UpdatePage (void);
 *
 * Updates the page's controls from the variable data.
 *
 *=========================================================================*/
void CEsmScrTempPage3::UpdatePage() {
	FillCsvList(m_pParentView->GetCsvFile());
}
