/*===========================================================================
 *
 * File:    Esmloaddlg.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  March 2, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "stdafx.h"
#include "MWEdit.h"
#include "EsmLoadDlg.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

DEFINE_FILE("EsmLoadDlg.cpp");


/*===========================================================================
 *
 * Begin CEsmLoadDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CEsmLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CEsmLoadDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Function - int *g_EsmLoadDlgCallback (Event, pMessage, Percent, UserData);
 *
 *=========================================================================*/
int g_EsmLoadDlgCallback(const int Event,
                         const TCHAR *pMessage,
                         const float Percent,
                         long UserData) {
	CEsmLoadDlg *pDialog = (CEsmLoadDlg *)UserData;
	pDialog->SetProgress(Percent);
	return 0;
}


/*===========================================================================
 *
 * Class CEsmLoadDlg Constructor
 *
 *=========================================================================*/
CEsmLoadDlg::CEsmLoadDlg(CWnd* pParent) : CDialog(CEsmLoadDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CEsmLoadDlg)
	//}}AFX_DATA_INIT
}


/*===========================================================================
 *
 * Class CEsmLoadDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CEsmLoadDlg::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEsmLoadDlg)
	DDX_Control(pDX, IDC_FILELABEL2, m_SubLabel);
	DDX_Control(pDX, IDC_FILELABEL, m_FileLabel);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Class CEsmLoadDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CEsmLoadDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	m_FileLabel.SetWindowText(_T(""));
	m_ProgressCtrl.SetRange(0, 200);
	m_ProgressCtrl.SetPos(0);

	return TRUE;
}
