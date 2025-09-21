/*===========================================================================
 *
 * File:    ChildFrmVar.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, 03 February, 2003
 *
 * Implementation of the CChildFrameVar class
 *
 *=========================================================================*/


#include "stdafx.h"
#include "MWEdit.h"
#include "ChildFrmVar.h"


#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChildFrameVar, CMDIChildWnd)
DEFINE_FILE("ChildFrmVar.cpp");


/*===========================================================================
 *
 * Class CChildFrameVar Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CChildFrameVar, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrameVar)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CChildFrameVar Constructor
 *
 *=========================================================================*/
CChildFrameVar::CChildFrameVar() {
	m_IsFakeMaximized = false;
}


/*===========================================================================
 *
 * Class CChildFrameVar Destructor
 *
 *=========================================================================*/
CChildFrameVar::~CChildFrameVar() {
}


/*===========================================================================
 *
 * Class CChildFrameVar Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CChildFrameVar::PreCreateWindow(CREATESTRUCT &cs) {
	//cs.style &= ~WS_THICKFRAME;
	//cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_MAXIMIZE;

	if ( !CMDIChildWnd::PreCreateWindow(cs) ) {
		return FALSE;
	}

	return TRUE;
}


#ifdef _DEBUG
/*===========================================================================
 *
 * CChildFrameVar Diagnostics
 *
 *=========================================================================*/
void CChildFrameVar::AssertValid() const {
	CMDIChildWnd::AssertValid();
}

void CChildFrameVar::Dump(CDumpContext &dc) const {
	CMDIChildWnd::Dump(dc);
}
#endif


/*===========================================================================
 *
 * Class CChildFrameVar Event - void OnClose (void);
 *
 *=========================================================================*/
void CChildFrameVar::OnClose() {
	DestroyWindow();
}


/*===========================================================================
 *
 * Class CChildFrameVar Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CChildFrameVar::OnSize(UINT nType, int cx, int cy) {
	/* Cannot maximize this type of frame */
	/*if (nType == SIZE_MAXIMIZED) {

	  CMDIChildWnd::OnSize(SIZE_RESTORED, 200, 200);

	 }

	else  //*/
	CMDIChildWnd::OnSize(nType, cx, cy);
	m_IsFakeMaximized = false;
}


/*===========================================================================
 *
 * Class CChildFrameVar Method - void FakeMaximize (void);
 *
 *=========================================================================*/
void CChildFrameVar::FakeMaximize() {
	CRect ClientRect;
	CRect RestoreRect;

	if (m_IsFakeMaximized) {
		SetWindowPos(NULL,
		             m_RestoreRect.left,
		             m_RestoreRect.top,
		             m_RestoreRect.Width(),
		             m_RestoreRect.Height(),
		             SWP_NOZORDER);
		m_IsFakeMaximized = false;
	} else {
		if (IsIconic()) {
			ShowWindow(SW_RESTORE);
		}

		GetWindowRect(&RestoreRect);
		GetParent()->ScreenToClient(&RestoreRect);
		GetParent()->GetClientRect(&ClientRect);
		SetWindowPos(NULL, 0, 0, ClientRect.Width(), ClientRect.Height(), SWP_NOZORDER);
		m_IsFakeMaximized = true;
		m_RestoreRect = RestoreRect;
	}
}


/*===========================================================================
 *
 * Class CChildFrameVar Event - void OnSysCommand (nID, Param);
 *
 *=========================================================================*/
void CChildFrameVar::OnSysCommand(UINT nID, LPARAM Param) {
	if ((nID & 0xFFF0) == SC_MAXIMIZE) {
		FakeMaximize();
		return;
	} else if ((nID & 0xFFF0) == SC_MINIMIZE) {
		m_IsFakeMaximized = false;
	}

	CMDIChildWnd::OnSysCommand(nID, Param);
}
