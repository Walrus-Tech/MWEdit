/*===========================================================================
 *
 * File:    ChildFrm.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, 03 February, 2003
 *
 * Definition of the CChildFrame class.
 *
 *=========================================================================*/
#ifndef __ChildFrm_H
#define __ChildFrm_H


/*===========================================================================
 *
 * Class CChildFrame Definition
 *
 *=========================================================================*/
class CChildFrame : public CMDIChildWnd {
	DECLARE_DYNCREATE(CChildFrame)

  protected:
	bool m_IsFakeMaximized;
	CRect m_RestoreRect;


  public:
	/* Class constructor/destructor */
	CChildFrame();
	virtual ~CChildFrame();

	void FakeMaximize();

	/* Diagnostics routines */
#if _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow (CREATESTRUCT &cs);
	//}}AFX_VIRTUAL


	/*---------- Generated message map functions ------------------*/
  protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSysCommand (UINT nID, LPARAM Param);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION

#endif
