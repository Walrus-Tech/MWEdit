/*===========================================================================
 *
 * File:    Custrichedit.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, February 21, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "stdafx.h"
#include "CustRichEdit.h"
#include "dl_err.h"
#include "afxrich.h"


#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


DEFINE_FILE("CustRichEdit.cpp");


/*===========================================================================
 *
 * Begin CCustRichEdit Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CCustRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CCustRichEdit)
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CCustRichEdit Constructor
 *
 *=========================================================================*/
CCustRichEdit::CCustRichEdit() {
}


/*===========================================================================
 *
 * Class CCustRichEdit Destructor
 *
 *=========================================================================*/
CCustRichEdit::~CCustRichEdit() {
}


/*===========================================================================
 *
 * Class CCustRichEdit Method - BOOL Create (lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
 *
 * Description
 *
 *=========================================================================*/
BOOL CCustRichEdit::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID) {
	CWnd *l_pWnd = this ;
	return l_pWnd->Create(_T("RichEdit"), NULL, dwStyle, rect, pParentWnd, nID);
}


/*===========================================================================
 *
 * Class CCustRichEdit Method - int GetCurLineCharPos (void);
 *
 * Returns the 0-based character position in the current line.
 *
 *=========================================================================*/
int CCustRichEdit::GetCurLineCharPos() {
	long StartChar;
	long EndChar;
	int CharPos;
	GetSel(StartChar, EndChar);
	CharPos = StartChar - LineIndex(-1);
	return CharPos;
}


/*===========================================================================
 *
 * Class CCustRichEdit Method - const TCHAR* GetCurLineText (Buffer);
 *
 * Returns the current line of text.
 *
 *=========================================================================*/
const TCHAR *CCustRichEdit::GetCurLineText(CString &Buffer) {
	int LineSize;
	int LineIndex;
	TCHAR *pBuffer;
	/* Get the current line text buffer */
	LineIndex = LineFromChar(-1);
	LineSize = LineLength(-1);

	if (LineSize > 0) {
		pBuffer = Buffer.GetBuffer(LineSize + 4);
		GetLine(LineIndex, pBuffer, LineSize + 4);
		pBuffer[LineSize] = NULL_CHAR;
		Buffer.ReleaseBuffer(LineSize);
	} else {
		Buffer.Empty();
	}

	return (const TCHAR *)Buffer;
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - UINT OnGetDlgCode ();
 *
 *=========================================================================*/
UINT CCustRichEdit::OnGetDlgCode() {
	return CRichEditCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - void OnChar (nChar, nRepCnt, nFlags);
 *
 *=========================================================================*/
void CCustRichEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == '\t') {
		//this->ReplaceSel("\t", TRUE);
	}

	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
	GetParent()->SendMessage(CRE_UPDATEPOS, nChar, 0);
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - void OnKeyDown (nChar, nRepCnt, nFlags);
 *
 *=========================================================================*/
void CCustRichEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == '\t') {
		//this->ReplaceSel("test", TRUE);
	} else {
		CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	}

	GetParent()->SendMessage(CRE_UPDATEPOS, 0, nChar);
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - void OnLButtonDown (nFlags, point);
 *
 *=========================================================================*/
void CCustRichEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	CRichEditCtrl::OnLButtonDown(nFlags, point);
	GetParent()->SendMessage(CRE_UPDATEPOS, -1, 0);
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - void OnRButtonDown (nFlags, point);
 *
 *=========================================================================*/
void CCustRichEdit::OnRButtonDown(UINT nFlags, CPoint point) {
	CRichEditCtrl::OnRButtonDown(nFlags, point);
	GetParent()->SendMessage(CRE_UPDATEPOS, -1, 0);
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - int OnCreate (LPCREATESTRUCT lpCreateStruct);
 *
 *=========================================================================*/
int CCustRichEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	return 0;
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - BOOL OnMouseWheel (nFlags, zDetla, pt);
 *
 *=========================================================================*/
BOOL CCustRichEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	GetParent()->SendMessage(CRE_UPDATESCROLL, -1, 0);
	return CRichEditCtrl::OnMouseWheel(nFlags, zDelta, pt);
}


/*===========================================================================
 *
 * Class CCustRichEdit Event - void OnVScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CCustRichEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	GetParent()->SendMessage(CRE_UPDATESCROLL, -1, 0);
	CRichEditCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
