/*===========================================================================
 *
 * File:    Tabctrlsheet.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, September 04, 2002
 *
 * Implements the CTabCtrlSheet class.
 *
 *=========================================================================*/
#include "stdafx.h"
#include "TabCtrlSheet.h"


DEFINE_FILE("TabStrlSheet.cpp");

/* Debug definitions */
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


/*===========================================================================
 *
 * Begin CTabCtrlSheet Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CTabCtrlSheet, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlSheet)
	ON_WM_GETDLGCODE()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CTabCtrlSheet Constructor
 *
 *=========================================================================*/
CTabCtrlSheet::CTabCtrlSheet() {
	m_NumPages = 0;
	m_CurrentPage = -1;
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Destructor
 *
 *=========================================================================*/
CTabCtrlSheet::~CTabCtrlSheet() {
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Method - bool AddTab (pTitle, pPage);
 *
 * Adds the given page/tab to the end of the tab ctrl.  Returns false on
 * any error.
 *
 *=========================================================================*/
bool CTabCtrlSheet::AddTab(const TCHAR *pTitle, CPropertyPage *pPage) {
	DEFINE_FUNCTION("CTabCtrlSheet::AddTab()");
	int Result;
	/* Ensure valid input */
	ASSERT(pTitle != NULL && pPage != NULL);

	/* Ensure the maximum number of sheets hasn't been reached */
	if (m_NumPages >= TCS_ARRAYSIZE) {
		return false;
	}

	/* Attempt to add the tab and sheet */
	m_pPages[m_NumPages] = pPage;
	Result = InsertItem(m_NumPages, pTitle);

	if (Result < 0) {
		return false;
	}

	m_NumPages++;
	return true;
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Method - void DisplayPage (PageIndex);
 *
 * Protected class method which displays the given tab page.  Resizes and
 * repositions the page to fit within the current tab display area.
 *
 *=========================================================================*/
void CTabCtrlSheet::DisplayPage(const int PageIndex) {
	CRect PageRect;
	/* Adjust the size/position of page and display it */
	PageRect = GetPageRect();
	m_pPages[PageIndex]->SetWindowPos(NULL,
	                                  PageRect.left,
	                                  PageRect.top,
	                                  PageRect.Width(),
	                                  PageRect.Height(),
	                                  SWP_SHOWWINDOW);
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Method - RECT GetPageRect (void);
 *
 * Returns the coordinates for outputting the tab pages within the tab
 * display area.
 *
 *=========================================================================*/
RECT CTabCtrlSheet::GetPageRect() {
	RECT PageRect;
	GetClientRect(&PageRect);
	AdjustRect(FALSE, &PageRect);
	return PageRect;
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Event - UINT OnGetDlgCode ();
 *
 *=========================================================================*/
UINT CTabCtrlSheet::OnGetDlgCode() {
	return (CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB | DLGC_WANTALLKEYS);
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Event - void OnSelchange (pNMHDR, pResult);
 *
 *=========================================================================*/
void CTabCtrlSheet::OnSelchange(NMHDR *pNMHDR, LRESULT *pResult) {
	int CurrentTab;
	CurrentTab = GetCurSel();
	SetCurrentPage(CurrentTab);
	*pResult = 0;
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Method - bool SetCurrentPage (PageIndex);
 *
 * Change the currently display page.  Updates the display and returns
 * true on success.  Protected class method.
 *
 *=========================================================================*/
bool CTabCtrlSheet::SetCurrentPage(const int PageIndex) {
	/* Ignore if nothing changed */
	if (m_CurrentPage == PageIndex) {
		return false;
	}

	/* Ensure valid input */
	if (PageIndex >= m_NumPages) {
		return false;
	}

	/* Hide the currently display page, if any */
	if (m_CurrentPage >= 0) {
		m_pPages[m_CurrentPage]->ShowWindow(SW_HIDE);
	}

	/* Display the new page if required */
	m_CurrentPage = PageIndex;

	if (m_CurrentPage >= 0) {
		DisplayPage(m_CurrentPage);
	}

	return true;
}


/*===========================================================================
 *
 * Class CTabCtrlSheet Method - bool SetPage (PageIndex);
 *
 * Sets the currently displayed page and tab to the given 0-based index.
 * Returns true on success.
 *
 *=========================================================================*/
bool CTabCtrlSheet::SetPage(const int PageIndex) {
	int iResult;
	bool Result;

	/* Ensure valid input */
	if (!IsValidPage(PageIndex)) {
		return false;
	}

	iResult = SetCurSel(PageIndex);

	if (iResult < 0) {
		return false;
	}

	Result = SetCurrentPage(PageIndex);
	return Result;
}

void CTabCtrlSheet::OnSysCommand(UINT nID, LPARAM lParam) {
	CTabCtrl::OnSysCommand(nID, lParam);
}

void CTabCtrlSheet::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
