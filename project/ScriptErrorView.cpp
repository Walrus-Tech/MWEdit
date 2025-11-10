/*===========================================================================
 *
 * File:    Scripterrorview.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "project/StdAfx.h"
#include "project/MWEdit.h"
#include "project/ScriptErrorView.h"
#include "project/ScriptErrorDlg.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CScriptErrorView, CFormView);
DEFINE_FILE("ScriptErrorView.cpp");


/*===========================================================================
 *
 * Begin CScriptErrorView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CScriptErrorView, CFormView)
	//{{AFX_MSG_MAP(CScriptErrorView)
	ON_WM_SIZE()
	ON_LBN_DBLCLK(IDC_ERRORLIST, OnDblclkErrorlist)
	ON_COMMAND(ID_SCRERROR_GOTO, OnScrerrorGoto)
	ON_UPDATE_COMMAND_UI(ID_SCRERROR_GOTO, OnUpdateScrerrorGoto)
	ON_COMMAND(ID_SCRERROR_DETAILS, OnScrerrorDetails)
	ON_UPDATE_COMMAND_UI(ID_SCRERROR_DETAILS, OnUpdateScrerrorDetails)
	ON_COMMAND(ID_SCRERROR_COPY, OnScrerrorCopy)
	ON_UPDATE_COMMAND_UI(ID_SCRERROR_COPY, OnUpdateScrerrorCopy)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SCRERROR_FUNCHELP, OnScrerrorFunchelp)
	ON_UPDATE_COMMAND_UI(ID_SCRERROR_FUNCHELP, OnUpdateScrerrorFunchelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CScriptErrorView Constructor
 *
 *=========================================================================*/
CScriptErrorView::CScriptErrorView() : CFormView(CScriptErrorView::IDD) {
	//{{AFX_DATA_INIT(CScriptErrorView)
	//}}AFX_DATA_INIT
}


/*===========================================================================
 *
 * Class CScriptErrorView Destructor
 *
 *=========================================================================*/
CScriptErrorView::~CScriptErrorView() {
}


/*===========================================================================
 *
 * Class CScriptErrorView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CScriptErrorView::DoDataExchange(CDataExchange *pDX) {
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CScriptErrorView)
	DDX_Control(pDX, IDC_ERRORLIST, m_ErrorList);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Begin CScriptErrorView Diagnostics
 *
 *=========================================================================*/
#if _DEBUG

void CScriptErrorView::AssertValid() const {
	CFormView::AssertValid();
}

void CScriptErrorView::Dump(CDumpContext &dc) const {
	CFormView::Dump(dc);
}

#endif


/*===========================================================================
 *
 * Class CScriptErrorView Method - void ClearErrors (void);
 *
 *=========================================================================*/
void CScriptErrorView::ClearErrors() {
	m_ErrorList.ResetContent();
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CScriptErrorView::OnContextMenu(CWnd *pWnd, CPoint Point) {
	CMenu Menu;
	CMenu *pPopup;
	CCmdUI MenuState;
	int Result;
	int Index;

	if (pWnd->GetDlgCtrlID() == IDC_ERRORLIST) {
		Result = Menu.LoadMenu(IDR_SCRERROR_MENU);

		if (!Result) {
			return;
		}

		pPopup = Menu.GetSubMenu(0);

		if (pPopup == NULL) {
			return;
		}

		/* Force the update of the menu commands */

		for (Index = 0; Index < (int)pPopup->GetMenuItemCount(); Index++) {
			MenuState.m_nID = pPopup->GetMenuItemID(Index);
			MenuState.m_nIndex = Index;
			MenuState.m_pMenu = pPopup;
			MenuState.m_pOther = NULL;
			MenuState.m_pSubMenu = NULL;
			MenuState.m_nIndexMax = pPopup->GetMenuItemCount();

			if (MenuState.m_nID != 0) {
				OnCmdMsg(MenuState.m_nID, CN_UPDATE_COMMAND_UI, &MenuState, NULL);
			}
		}

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, Point.x, Point.y, this);
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnDblclkErrorlist ();
 *
 *=========================================================================*/
void CScriptErrorView::OnDblclkErrorlist() {
	CEsmScriptError *pError;
	int ListIndex;
	/* Get the currently selected error */
	ListIndex = m_ErrorList.GetCurSel();

	if (ListIndex < 0) {
		return;
	}

	pError = (CEsmScriptError *)m_ErrorList.GetItemDataPtr(ListIndex);
	/* Send a message to the parent frame */
	GetParentFrame()->SendMessage(MSG_SCRIPTFRM_GOTOLINE, pError->GetLine(), pError->GetCharacter());
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CScriptErrorView::OnInitialUpdate() {
	CFormView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	if (IsWindow(m_ErrorList.m_hWnd)) {
		CRect WndRect;
		GetWindowRect(&WndRect);
		m_ErrorList.SetWindowPos(NULL,
		                         0,
		                         0,
		                         WndRect.Width(),
		                         WndRect.Height(),
		                         SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CScriptErrorView::OnSize(UINT nType, int cx, int cy) {
	CFormView::OnSize(nType, cx, cy);

	if (IsWindow(m_ErrorList.m_hWnd)) {
		CRect WndRect;
		GetWindowRect(&WndRect);
		m_ErrorList.SetWindowPos(NULL,
		                         0,
		                         0,
		                         WndRect.Width(),
		                         WndRect.Height(),
		                         SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnScrerrorGoto ();
 *
 *=========================================================================*/
void CScriptErrorView::OnScrerrorGoto() {
	OnDblclkErrorlist();
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnScrerrorDetails ();
 *
 *=========================================================================*/
void CScriptErrorView::OnScrerrorDetails() {
	CEsmScriptError *pError;
	int ListIndex;
	int Result;
	/* Get the currently selected error */
	ListIndex = m_ErrorList.GetCurSel();

	if (ListIndex < 0) {
		return;
	}

	pError = (CEsmScriptError *)m_ErrorList.GetItemDataPtr(ListIndex);

	if (pError->GetLine() == 0) {
		return;
	}

	CScriptErrorDlg ErrorDlg;
	/* Initialize and display the modal dialog */
	ErrorDlg.SetScriptError(pError);
	Result = ErrorDlg.DoModal();

	/* Check result if we need to do anything */

	if (Result == SCRERRDLG_RESULT_GOTO) {
		OnScrerrorGoto();
	} else if (Result == SCRERRDLG_RESULT_MOREHELP) {
		OnScrerrorFunchelp();
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnScrerrorCopy ();
 *
 *=========================================================================*/
void CScriptErrorView::OnScrerrorCopy() {
	CString ErrorString;
	int ListIndex;
	HGLOBAL hMemory;
	TCHAR *pData;
	int Result;

	/* Get the error to copy */
	ListIndex = m_ErrorList.GetCurSel();

	if (ListIndex < 0) {
		return;
	}

	m_ErrorList.GetText(ListIndex, ErrorString);
	/* Attempt to allocate global memory block */
	hMemory = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, ErrorString.GetLength() + 1);

	if (hMemory == NULL) {
		return;
	}

	pData = (TCHAR *)GlobalLock(hMemory);

	if (pData != NULL) {
		strnncpy(pData, ErrorString, ErrorString.GetLength() + 1);
		GlobalUnlock(hMemory);
	}

	/* Attempt to open the clipboard for input */
	Result = OpenClipboard();

	if (!Result) {
		return;
	}

	/* Send data to clipboard and close it */
	SetClipboardData(CF_TEXT, hMemory);
	CloseClipboard();
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnScrerrorFunchelp ();
 *
 *=========================================================================*/
void CScriptErrorView::OnScrerrorFunchelp() {
	CMWEditApp *pApp = (CMWEditApp *)AfxGetApp();
	CEsmScriptError *pError;
	int ListIndex;

	/* Get the currently selected error */
	ListIndex = m_ErrorList.GetCurSel();

	if (ListIndex < 0) {
		return;
	}

	pError = (CEsmScriptError *)m_ErrorList.GetItemDataPtr(ListIndex);

	if (pError->GetFunction() != NULL) {
		pApp->OpenFuncHelpView(pError->GetFunction()->Name);
	} else {
		pApp->OpenFuncHelpView();
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnUpdateScrerrorFunchelp (pCmdUI);
 *
 *=========================================================================*/
void CScriptErrorView::OnUpdateScrerrorFunchelp(CCmdUI *pCmdUI) {
	int ListIndex;
	ListIndex = m_ErrorList.GetCurSel();

	if (ListIndex < 0) {
		pCmdUI->Enable(FALSE);
	} else {
		CEsmScriptError *pError = (CEsmScriptError *)m_ErrorList.GetItemDataPtr(ListIndex);
		pCmdUI->Enable(pError->GetFunction() != NULL);
	}
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnUpdateScrerrorCopy (pCmdUI);
 *
 *=========================================================================*/
void CScriptErrorView::OnUpdateScrerrorCopy(CCmdUI *pCmdUI) {
	int ListIndex;
	ListIndex = m_ErrorList.GetCurSel();
	pCmdUI->Enable(ListIndex >= 0);
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnUpdateScrerrorDetails (pCmdUI);
 *
 *=========================================================================*/
void CScriptErrorView::OnUpdateScrerrorDetails(CCmdUI *pCmdUI) {
	int ListIndex;
	ListIndex = m_ErrorList.GetCurSel();
	pCmdUI->Enable(ListIndex >= 0);
}


/*===========================================================================
 *
 * Class CScriptErrorView Event - void OnUpdateScrerrorGoto (pCmdUI);
 *
 *=========================================================================*/
void CScriptErrorView::OnUpdateScrerrorGoto(CCmdUI *pCmdUI) {
	int ListIndex;
	ListIndex = m_ErrorList.GetCurSel();
	pCmdUI->Enable(ListIndex >= 0);
}


/*===========================================================================
 *
 * Class CScriptErrorView Method - void UpdateErrors (pErrorArray);
 *
 *=========================================================================*/
void CScriptErrorView::UpdateErrors(CEsmScriptErrArray *pErrorArray) {
	CEsmScriptError *pError;
	CString Buffer;
	int Index;
	int ListResult;

	/* Clear the current list */
	m_ErrorList.ResetContent();

	if (pErrorArray == NULL) {
		return;
	}

	for (Index = 0; Index < pErrorArray->GetNumElements(); Index++) {
		pError = pErrorArray->GetAt(Index);

		if (pError->GetLine() == 0) {
			Buffer.Format(_T("%s"), pError->GetMessage());
		} else {
			Buffer.Format(_T("Line %4d (%3d): %s %4d: %s"),
			              pError->GetLine(),
			              pError->GetCharacter(),
			              pError->GetTypeString(),
			              pError->GetErrorCode(),
			              pError->GetMessage());

			if (pError->GetFunction() != NULL) {
				Buffer += _T(" (");
				Buffer += pError->GetFunction()->Name;
				Buffer += _T(")");
			}
		}

		ListResult = m_ErrorList.AddString(Buffer);

		if (ListResult >= 0) {
			m_ErrorList.SetItemDataPtr(ListResult, (void *)pError);
		}
	}
}
