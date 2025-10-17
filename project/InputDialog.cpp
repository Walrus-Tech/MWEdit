/*===========================================================================
 *
 * File:    Inputdialog.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  April 5, 2003
 *
 * Description
 *
 * 14 September 2003
 *  - Input textbox has initial focus.
 *
 *=========================================================================*/
#include "project/StdAfx.h"
#include "project/MWEdit.h"
#include "project/InputDialog.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

DEFINE_FILE("InputDialog.cpp");


/*===========================================================================
 *
 * Begin CInputDialog Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CInputDialog, CDialog)
	//{{AFX_MSG_MAP(CInputDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CInputDialog Constructor
 *
 *=========================================================================*/
CInputDialog::CInputDialog(CWnd *pParent) : CDialog(CInputDialog::IDD, pParent) {
	//{{AFX_DATA_INIT(CInputDialog)
	//}}AFX_DATA_INIT
}


/*===========================================================================
 *
 * Class CInputDialog Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CInputDialog::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CInputDialog)
	DDX_Control(pDX, IDC_MAINLABEL, m_MainLabel);
	DDX_Control(pDX, IDC_EDIT1, m_InputText);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Class CInputDialog Method - bool DoModal (pResult, pLabel, pTitle);
 *
 *=========================================================================*/
bool CInputDialog::DoModal(CString *pResult, const TCHAR *pLabel, const TCHAR *pTitle) {
	int Result;
	m_pLabel = pLabel;
	m_pTitle = pTitle;
	m_pOutputString = pResult;
	Result = CDialog::DoModal();

	if (Result != IDOK) {
		return false;
	}

	return true;
}


/*===========================================================================
 *
 * Class CInputDialog Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CInputDialog::OnInitDialog() {
	CDialog::OnInitDialog();
	SetWindowText(m_pTitle == NULL ? _T("Input Text") : m_pTitle);
	m_MainLabel.SetWindowText(m_pLabel == NULL ? _T("Input text:") : m_pLabel);
	m_InputText.SetWindowText(m_pOutputString == NULL ? _T("") : (const TCHAR *)*m_pOutputString);
	m_InputText.SetFocus();
	return FALSE;
}


/*===========================================================================
 *
 * Class CInputDialog Event - void OnOK ();
 *
 *=========================================================================*/
void CInputDialog::OnOK() {
	if (m_pOutputString != NULL) {
		m_InputText.GetWindowText(*m_pOutputString);
	}

	CDialog::OnOK();
}


/*===========================================================================
 *
 * Function - bool InputDialog (pResult, pLabel, pTitle);
 *
 * Main access function for displaying a standard input dialog box.
 *
 *=========================================================================*/
bool InputDialog(CString *pResult, const TCHAR *pLabel, const TCHAR *pTitle) {
	CInputDialog Dlg;
	return Dlg.DoModal(pResult, pLabel, pTitle);
}
