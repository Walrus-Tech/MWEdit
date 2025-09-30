/*===========================================================================
 *
 * File:    Esmstartscriptdlg.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 13, 2003
 *
 * Description
 *
 * 3 November 2003
 *  - Used the base class script list member.
 *
 *=========================================================================*/
#include "stdafx.h"
#include "MWEdit.h"
#include "EsmStartScriptDlg.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEsmStartScriptDlg, CEsmRecDialog);
DEFINE_FILE("EsmStartScriptDlg.cpp");


/*===========================================================================
 *
 * Begin CEsmStartScriptDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CEsmStartScriptDlg, CEsmRecDialog)
	//{{AFX_MSG_MAP(CEsmStartScriptDlg)
	ON_CBN_SELCHANGE(IDC_SCRIPTLIST, OnSelchangeScriptlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Constructor
 *
 *=========================================================================*/
CEsmStartScriptDlg::CEsmStartScriptDlg (CWnd* pParent) : CEsmRecDialog(CEsmStartScriptDlg::IDD) {
	//{{AFX_DATA_INIT(CEsmStartScriptDlg)
	//}}AFX_DATA_INIT
	m_pStartScript = NULL;
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CEsmStartScriptDlg::DoDataExchange(CDataExchange *pDX) {
	CEsmRecDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEsmStartScriptDlg)
	DDX_Control(pDX, IDC_BLOCKEDCHECK, m_BlockedCheck);
	DDX_Control(pDX, IDC_PERSISTCHECK, m_PersistCheck);
	DDX_Control(pDX, IDC_SCRIPTLIST, m_ScriptList);
	DDX_Control(pDX, IDC_IDTEXT, m_IDText);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CEsmStartScriptDlg::GetControlData() {
	DEFINE_FUNCTION("CEsmStartScriptDlg::GetControlData()");
	CString Buffer;
	/* Update the record pointer and data */
	m_pStartScript = (CEsmStartScript *)GetRecInfo()->pRecord;

	if (m_pStartScript == NULL) {
		return;
	}

	/* ID, if changed */

	if (m_IDText.GetModify()) {
		m_IDText.GetWindowText(Buffer);
		m_pStartScript->SetID(TrimStringSpace(Buffer));
	}

	/* Script name */
	m_ScriptList.GetWindowText(Buffer);
	m_pStartScript->SetName(TrimStringSpace(Buffer));

	/* Record flags */
	m_pStartScript->SetPersist(m_PersistCheck.GetCheck() != 0);
	m_pStartScript->SetBlocked(m_BlockedCheck.GetCheck() != 0);
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Method - bool IsModified (void);
 *
 *=========================================================================*/
bool CEsmStartScriptDlg::IsModified() {
	if (m_Modified) {
		return true;
	}

	/* Check edit controls for changes */

	if (m_IDText.GetModify()) {
		m_Modified = true;
	}

	return m_Modified;
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CEsmStartScriptDlg::OnInitialUpdate() {
	CEsmRecDialog::OnInitialUpdate();
	UpdateTitle(NULL);

	/* Initialize the armor record */
	ASSERT(GetRecInfo() != NULL);
	m_pStartScript = (CEsmStartScript *)GetRecInfo()->pRecord;

	/* Generate the auto ID if it is a new record */

	if (m_RecEditInfo.IsNew && m_pStartScript != NULL) {
		m_pStartScript->SetID(GetDocument()->MakeNewINFOId());
	}

	/* Initialize the ui controls/lists */
	FillEsmScriptCombo(m_ScriptList);
	/* Update the UI data */
	SetControlData();
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Event - void OnSelchangeScriptlist ();
 *
 *=========================================================================*/
void CEsmStartScriptDlg::OnSelchangeScriptlist() {
	m_Modified = true;
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Event - int OnUpdateItem (pRecInfo);
 *
 *=========================================================================*/
int CEsmStartScriptDlg::OnUpdateItem(esmrecinfo_t *pRecInfo) {
	CString Buffer;

	/* Refill the script list if required */

	if (pRecInfo->pRecord->IsType(MWESM_REC_SCRI)) {
		esmrecinfo_t *pRecInfo = NULL;
		int Index;
		Index = m_ScriptList.GetCurSel();

		if (Index >= 0) {
			pRecInfo = (esmrecinfo_t *)m_ScriptList.GetItemData(Index);
		}

		FillEsmScriptCombo(m_ScriptList);
		FindComboListItem(m_ScriptList, (DWORD)pRecInfo, true);
	}

	return 0;
}


/*===========================================================================
 *
 * Class CEsmStartScriptDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CEsmStartScriptDlg::SetControlData() {
	/* Ignore if the current item is not valid */
	if (m_pStartScript == NULL) {
		return;
	}

	/* Armor ID, update title as well */
	m_IDText.SetWindowText(m_pStartScript->GetID());
	UpdateTitle(m_pStartScript->GetID());

	/* Item lists */
	m_ScriptList.SelectString(-1, m_pStartScript->GetName());

	/* Record flags */
	m_BlockedCheck.SetCheck(m_pStartScript->IsBlocked());
	m_PersistCheck.SetCheck(m_pStartScript->IsPersist());
}
