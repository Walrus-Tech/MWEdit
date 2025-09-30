/*===========================================================================
 *
 * File:    EsmScriptCompareDlg.CPP
 * Author:  Dave Humphrey (uesp@sympatico.ca)
 * Created On:  September 8, 2006
 *
 * Description
 *
 *=========================================================================*/
#include "stdafx.h"
#include "MWEdit.h"
#include "EsmScriptCompareDlg.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

DEFINE_FILE("EsmScriptCompareDlg.CPP");
IMPLEMENT_DYNCREATE(CEsmScriptCompareDlg, CFormView)


/*===========================================================================
 *
 * Begin CEsmScriptCompareDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CEsmScriptCompareDlg, CFormView)
	//{{AFX_MSG_MAP(CEsmScriptCompareDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Constructor
 *
 *=========================================================================*/
CEsmScriptCompareDlg::CEsmScriptCompareDlg() : CFormView(CEsmScriptCompareDlg::IDD) {
	//{{AFX_DATA_INIT(CEsmScriptCompareDlg)
	//}}AFX_DATA_INIT
	m_pDlgHandler = NULL;
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Destructor
 *
 *=========================================================================*/
CEsmScriptCompareDlg::~CEsmScriptCompareDlg() {
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Method - void AddLogText (pString, Args);
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::AddLogText(const TCHAR *pString, va_list Args) {
	CString Buffer;
	int Length;
	Buffer.FormatV(pString, Args);
	Buffer += _T("\r\n");
	Length = m_LogText.GetWindowTextLength();
	m_LogText.SetSel(Length, Length);
	m_LogText.ReplaceSel(Buffer);
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::DoDataExchange(CDataExchange *pDX) {
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEsmScriptCompareDlg)
	DDX_Control(pDX, IDC_LOGTEXT, m_LogText);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#if _DEBUG

void CEsmScriptCompareDlg::AssertValid() const {
	CFormView::AssertValid();
}

void CEsmScriptCompareDlg::Dump(CDumpContext &dc) const {
	CFormView::Dump(dc);
}

#endif


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Event - void OnCancel ();
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::OnCancel() {
	GetParentFrame()->DestroyWindow();
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Event - void OnDestroy();
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::OnDestroy() {
	CFormView::OnDestroy();
	m_pDlgHandler->OnCloseScriptCompareDlg();
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::OnInitialUpdate() {
	CFormView::OnInitialUpdate();
	ResizeParentToFit(FALSE);
	UpdateTitle();
	/* Find the uses information for the current record */
	//ShowWindow(SW_NORMAL);
	//RedrawWindow();
	//GetParentFrame()->ShowWindow(SW_NORMAL);
	//UpdateUses();
}


/*===========================================================================
 *
 * Class CEsmScriptCompareDlg Method - void UpdateTitle (void);
 *
 * Updates the parent frame title based on the current document and
 * record information.
 *
 *=========================================================================*/
void CEsmScriptCompareDlg::UpdateTitle() {
	CString Buffer;
	Buffer.Format(_T("%s -- Script Compare"), m_pDlgHandler->GetDocument()->GetTitle());
	GetParentFrame()->SetWindowText(Buffer);
}
