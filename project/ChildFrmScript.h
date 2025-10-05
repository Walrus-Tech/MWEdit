/*===========================================================================
 *
 * File:    Childfrmscript.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 3, 2003
 *
 * Defines the child frame class for the script window.
 *
 *=========================================================================*/
#ifndef __CHILDFRMSCRIPT_H
#define __CHILDFRMSCRIPT_H


#include "project/Resource.h"
#include "project/EsmScriptDefs.h"
#include "project/splitterwnd.h"


/*===========================================================================
 *
 * Begin Class CChildFrmScript Definition
 *
 *=========================================================================*/
class CScriptErrorView;
class CEsmScriptDlg;

class CChildFrmScript : public CMDIChildWnd {
	DECLARE_DYNCREATE(CChildFrmScript);

  protected:
	CMwSplitterWnd m_wndSplitter;
	CScriptErrorView *m_pErrorView;
	CEsmScriptDlg *m_pScriptView;
	bool m_IsFakeMaximized;
	CRect m_RestoreRect;
	bool m_Created;


	/* Protected constructor used by dynamic creation */
	CChildFrmScript();

	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);


  public:
	virtual ~CChildFrmScript();

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	void FakeMaximize();


	/* Generated message map functions */

	//{{AFX_MSG(CChildFrmScript)
	afx_msg LRESULT OnClearError(LPARAM lParam, WPARAM wParam);
	afx_msg LRESULT OnUpdateError(LPARAM lParam, WPARAM wParam);
	afx_msg LRESULT OnGotoError(LPARAM lParam, WPARAM wParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnMove(int cx, int cy);
	afx_msg void OnKillFocus(CWnd *pWnd);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSysCommand(UINT nID, LPARAM Param);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


#endif
