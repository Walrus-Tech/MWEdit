/*===========================================================================
 *
 * File:    Esmskilldlg.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 18, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "stdafx.h"
#include "MWEdit.h"
#include "EsmSkillDlg.h"


#if _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

DEFINE_FILE("EsmSkillDlg.cpp");
IMPLEMENT_DYNCREATE(CEsmSkillDlg, CEsmRecDialog);


/*===========================================================================
 *
 * Begin CEsmSkillDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CEsmSkillDlg, CEsmRecDialog)
	//{{AFX_MSG_MAP(CEsmSkillDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CEsmSkillDlg Constructor
 *
 *=========================================================================*/
CEsmSkillDlg::CEsmSkillDlg() : CEsmRecDialog(CEsmSkillDlg::IDD) {
	//{{AFX_DATA_INIT(CEsmSkillDlg)
	//}}AFX_DATA_INIT
	m_pSkill = NULL;
	m_HasIDText = false;
}


/*===========================================================================
 *
 * Class CEsmSkillDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CEsmSkillDlg::DoDataExchange(CDataExchange *pDX) {
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEsmSkillDlg)
	DDX_Control(pDX, IDC_VALUETEXT4, m_ValueText4);
	DDX_Control(pDX, IDC_VALUETEXT3, m_ValueText3);
	DDX_Control(pDX, IDC_VALUETEXT2, m_ValueText2);

	DDX_Control(pDX, IDC_ACTIONTEXT4, m_ActionText4);
	DDX_Control(pDX, IDC_ACTIONTEXT3, m_ActionText3);
	DDX_Control(pDX, IDC_ACTIONTEXT2, m_ActionText2);

	DDX_Control(pDX, IDC_VALUETEXT1, m_ValueText1);
	DDX_Control(pDX, IDC_ACTIONTEXT1, m_ActionText1);
	DDX_Control(pDX, IDC_DESCTEXT, m_DescText);

	DDX_Control(pDX, IDC_MAJORLIST6, m_SpecialList);
	DDX_Control(pDX, IDC_ATTRIBUTELIST, m_AttributeList);
	DDX_Control(pDX, IDC_NAMETEXT, m_NameText);
	//}}AFX_DATA_MAP
}


/*===========================================================================
 *
 * Class CEsmSkillDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CEsmSkillDlg::GetControlData() {
	DEFINE_FUNCTION("CEsmSkillDlg::GetControlData()");
	skilldata_t *pSkillData;
	const TCHAR *pAction;
	CString Buffer;

	/* Update the armor pointer and data */
	m_pSkill = (CEsmSkill *)GetRecInfo()->pRecord;
	ASSERT(m_pSkill != NULL);
	pSkillData = m_pSkill->GetSkillData();

	if (pSkillData == NULL) {
		return;
	}

	/* Item description */
	m_DescText.GetWindowText(Buffer);
	m_pSkill->SetDescription(TrimStringSpace(Buffer));

	/* Attribute lists */
	GETLISTDATA(m_AttributeList, pSkillData->Attribute);
	GETLISTDATA(m_SpecialList, pSkillData->Specialization);

	/* Use values */
	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 0);

	if (pAction != NULL) {
		m_ValueText1.GetWindowText(Buffer);
		pSkillData->UseValue1 = (float)atof(Buffer);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 1);

	if (pAction != NULL) {
		m_ValueText2.GetWindowText(Buffer);
		pSkillData->UseValue2 = (float)atof(Buffer);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 2);

	if (pAction != NULL) {
		m_ValueText3.GetWindowText(Buffer);
		pSkillData->UseValue3 = (float)atof(Buffer);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 3);

	if (pAction != NULL) {
		m_ValueText4.GetWindowText(Buffer);
		pSkillData->UseValue4 = (float)atof(Buffer);
	}
}


/*===========================================================================
 *
 * Class CEsmSkillDlg Method - bool IsModified (void);
 *
 *=========================================================================*/
bool CEsmSkillDlg::IsModified() {
	if (m_Modified) {
		return true;
	}

	/* Check edit controls for changes */

	if (m_DescText.GetModify()) {
		m_Modified = true;
	}

	return m_Modified;
}


/*===========================================================================
 *
 * Class CEsmSkillDlg Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CEsmSkillDlg::OnInitialUpdate() {
	CEsmRecDialog::OnInitialUpdate();
	UpdateTitle(NULL);

	/* Initialize the armor record */
	ASSERT(GetRecInfo() != NULL);
	m_pSkill = (CEsmSkill *)GetRecInfo()->pRecord;

	/* Initialize the lists */
	FillEsmAttributesCombo(m_AttributeList);
	FillEsmClassSpecCombo(m_SpecialList);

	/* Initialize the text controls */
	m_DescText.SetLimitText(256);
	m_ValueText1.SetLimitText(8);
	m_ValueText2.SetLimitText(8);
	m_ValueText3.SetLimitText(8);
	m_ValueText4.SetLimitText(8);

	/* Update the UI data */
	SetControlData();
}


/*===========================================================================
 *
 * Class CEsmSkillDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CEsmSkillDlg::SetControlData() {
	skilldata_t *pSkillData;
	CString Buffer;
	const TCHAR *pAction;

	/* Ignore if the current item is not valid */

	if (m_pSkill == NULL) {
		return;
	}

	pSkillData = m_pSkill->GetSkillData();

	if (pSkillData == NULL) {
		return;
	}

	/* Item name */
	m_NameText.SetWindowText(m_pSkill->GetName());
	m_NameText.SetModify(FALSE);

	/* Item description */
	m_DescText.SetWindowText(m_pSkill->GetDescription());
	m_DescText.SetModify(FALSE);

	/* Lists */
	FindComboListItem(m_AttributeList, pSkillData->Attribute, true);
	FindComboListItem(m_SpecialList, pSkillData->Specialization, true);

	/* Use values */
	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 0);

	if (pAction == NULL) {
		m_ActionText1.SetWindowText(_T(""));
		m_ValueText1.EnableWindow(FALSE);
	} else {
		Buffer.Format(_T("%.2f"), pSkillData->UseValue1);
		m_ValueText1.SetWindowText(Buffer);
		m_ActionText1.SetWindowText(pAction);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 1);

	if (pAction == NULL) {
		m_ActionText2.SetWindowText(_T(""));
		m_ValueText2.EnableWindow(FALSE);
	} else {
		Buffer.Format(_T("%.2f"), pSkillData->UseValue2);
		m_ValueText2.SetWindowText(Buffer);
		m_ActionText2.SetWindowText(pAction);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 2);

	if (pAction == NULL) {
		m_ActionText3.SetWindowText(_T(""));
		m_ValueText3.EnableWindow(FALSE);
	} else {
		Buffer.Format(_T("%.2f"), pSkillData->UseValue3);
		m_ValueText3.SetWindowText(Buffer);
		m_ActionText3.SetWindowText(pAction);
	}

	pAction = GetESMSkillAction(m_pSkill->GetSkillID(), 3);

	if (pAction == NULL) {
		m_ActionText4.SetWindowText(_T(""));
		m_ValueText4.EnableWindow(FALSE);
	} else {
		Buffer.Format(_T("%.2f"), pSkillData->UseValue4);
		m_ValueText4.SetWindowText(Buffer);
		m_ActionText4.SetWindowText(pAction);
	}
}
