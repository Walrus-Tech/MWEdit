/*===========================================================================
 *
 * File:    Tabctrlsheet.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, September 04, 2002
 *
 * Defines the CTabCtrlSheet class, extending the common CTabCtrl class.
 *
 *=========================================================================*/
#ifndef __TABCTRLSHEET_H
#define __TABCTRLSHEET_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "dl_err.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Number of sheets allowed in the extended tab control */
#define TCS_ARRAYSIZE 32

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTabCtrlSheet Definition
 *
 * Extends the common tab control class to include update and display of
 * the appropriate form, much like a property sheet but for use as a
 * control in a normal page.
 *
 *=========================================================================*/
class CTabCtrlSheet : public CTabCtrl {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CPropertyPage *m_pPages[TCS_ARRAYSIZE];    /* Array of pages to display */
	int m_NumPages;     /* Number of sheets currently defined */

	int m_CurrentPage;      /* The currently displayed sheet */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Displays the given page, resizing/repositioning as required */
	void DisplayPage (const int PageIndex);

	/* Change the currently displayed page */
	bool SetCurrentPage (const int PageIndex);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class construction/destruction */
	CTabCtrlSheet();
	virtual ~CTabCtrlSheet();

	/* Adds a page/tab to the end of the current tab list */
	bool AddTab (const TCHAR* pTitle, CPropertyPage* pPage);

	/* Return the currently displayed page */
	CPropertyPage *GetCurrentPage (void) {
		return (m_CurrentPage >= 0 ? m_pPages[m_CurrentPage] : NULL);
	}

	/* Return the coordinates of the page for moving/resizing */
	RECT GetPageRect (void);

	/* Checks the validity of a page index */
	bool IsValidPage (const int Index) const {
		return (Index >= 0 && Index < m_NumPages);
	}

	/* Sets the current tab/page to the given index */
	bool SetPage (const int PageIndex);


	/* ClassWizard generated virtual function overrides */
	//{{AFX_VIRTUAL(CTabCtrlSheet)
	//}}AFX_VIRTUAL

	/* Generated message map functions */
  protected:
	//{{AFX_MSG(CTabCtrlSheet)
  public:
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
  protected:
	afx_msg UINT OnGetDlgCode ();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/*===========================================================================
 *      End of Class CTabCtrlSheet Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *      End of File Tabctrlsheet.H
 *=========================================================================*/
