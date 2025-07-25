/*===========================================================================
 *
 * File:    Esmcreaturepage4.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  March 1, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */

#include "stdafx.h"
#include "MWEdit.h"
#include "EsmCreaturePage4.h"
#include "EsmAiActivateDlg.h"
#include "EsmAiEscortDlg.h"
#include "EsmAiTravelDlg.h"
#include "EsmAiWanderDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEsmCreaturePage4, CPropertyPage);
DEFINE_FILE("EsmCreaturePage4.cpp");

/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CEsmCreaturePage4 Message Map
 *
 *=========================================================================*/

BEGIN_MESSAGE_MAP(CEsmCreaturePage4, CPropertyPage)
	//{{AFX_MSG_MAP(CEsmCreaturePage4)
	ON_BN_CLICKED(IDC_ACTIVATEBUTTON, OnActivatebutton)
	ON_BN_CLICKED(IDC_ESCORTBUTTON, OnEscortbutton)
	ON_BN_CLICKED(IDC_FOLLOWBUTTON, OnFollowbutton)
	ON_BN_CLICKED(IDC_TRAVELBUTTON, OnTravelbutton)
	ON_BN_CLICKED(IDC_WANDERBUTTON, OnWanderbutton)
	ON_BN_CLICKED(IDC_EDITBUTTON, OnEditbutton)
	ON_BN_CLICKED(IDC_DELETEBUTTON, OnDeletebutton)
	ON_MESSAGE(ESMLIST_NOTIFY_ONKEY, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnRecordKey)
	ON_MESSAGE(ESMLIST_NOTIFY_ONEDIT, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnEditRecord)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_PACKAGELIST, OnItemchangingPackagelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*===========================================================================
 *      End of CEsmCreaturePage4 Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Constructor
 *
 *=========================================================================*/

CEsmCreaturePage4::CEsmCreaturePage4() : CPropertyPage(CEsmCreaturePage4::IDD), m_PackageArray(0) {
	//{{AFX_DATA_INIT(CEsmCreaturePage4)
	//}}AFX_DATA_INIT
}

/*===========================================================================
 *      End of Class CEsmCreaturePage4 Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Destructor
 *
 *=========================================================================*/

CEsmCreaturePage4::~CEsmCreaturePage4() {
	ClearPackageArray();
}

/*===========================================================================
 *      End of Class CEsmCreaturePage4 Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void AddAIRecords (pType);
 *
 * Protected class method that copies and saves all the AI sub-records
 * of the given type in the current NPC record.
 *
 *=========================================================================*/

void CEsmCreaturePage4::AddAIRecords(const TCHAR *pType) {
	CEsmCreature *pCreature;
	CEsmSubRecord *pSubRecord;
	CEsmSubRecord *pNewSubRec;
	int ArrayIndex;

	if (m_pRecInfo == NULL) {
		return;
	}

	pCreature = (CEsmCreature *)m_pRecInfo->pRecord;
	pSubRecord = pCreature->FindFirst(pType, ArrayIndex);

	while (pSubRecord != NULL) {
		pNewSubRec = pCreature->AllocNewSubRecord(pType);
		pNewSubRec->Copy(pSubRecord);
		m_PackageArray.Add(pNewSubRec);
		/* Check and copy any CNDT sub-records following the AI_? sub-record */
		pSubRecord = pCreature->GetSubRecord(ArrayIndex + 1);

		if (pSubRecord != NULL && pSubRecord->IsType(MWESM_SUBREC_CNDT)) {
			pNewSubRec = pCreature->AllocNewSubRecord(MWESM_SUBREC_CNDT);
			pNewSubRec->Copy(pSubRecord);
			m_PackageArray.Add(pNewSubRec);
		}

		pSubRecord = pCreature->FindNext(MWESM_SUBREC_NPCO, ArrayIndex);
	}
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::AddAIRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void ClearPackageArray (void);
 *
 *=========================================================================*/

void CEsmCreaturePage4::ClearPackageArray() {
	DEFINE_FUNCTION("CEsmCreaturePage4::ClearPackageArray()");
	CEsmSubRecord *pSubRec;
	int Index;

	for (Index = 0; Index < m_PackageArray.GetSize(); Index++) {
		pSubRec = m_PackageArray.GetAt(Index);
		DestroyPointer(pSubRec);
	}

	m_PackageArray.RemoveAll();
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::ClearPackageArray()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void DeleteSelectedItems (void);
 *
 *=========================================================================*/

void CEsmCreaturePage4::DeleteSelectedItems() {
	CEsmSubRecord *pSubRec;
	CEsmSubRecord *pSubNameRec;
	int ListIndex;
	ListIndex = m_PackageList.GetNextItem(-1, LVNI_SELECTED);

	while (ListIndex >= 0) {
		pSubRec = (CEsmSubRecord *)m_PackageList.GetItemData(ListIndex);
		pSubNameRec = FindCNDTSubRec(pSubRec);
		m_PackageArray.DeleteElement(pSubRec);
		DestroyPointer(pSubRec);

		if (pSubNameRec != NULL) {
			m_PackageArray.DeleteElement(pSubNameRec);
			DestroyPointer(pSubNameRec);
		}

		m_PackageList.DeleteItem(ListIndex);
		ListIndex = m_PackageList.GetNextItem(-1, LVNI_SELECTED);
	}
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::DeleteSelectedItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/

void CEsmCreaturePage4::DoDataExchange(CDataExchange *pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEsmCreaturePage4)
	DDX_Control(pDX, IDC_PACKAGEEDIT, m_PackageText);
	DDX_Control(pDX, IDC_HELLOTEXT, m_HelloText);
	DDX_Control(pDX, IDC_FLEETEXT, m_FleeText);
	DDX_Control(pDX, IDC_ALARMTEXT, m_AlarmText);
	DDX_Control(pDX, IDC_FIGHTTEXT, m_FightText);
	DDX_Control(pDX, IDC_PACKAGELIST, m_PackageList);
	//}}AFX_DATA_MAP
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void GetControlData (void);
 *
 *=========================================================================*/

void CEsmCreaturePage4::GetControlData() {
	CEsmCreature *pCreature;
	CEsmSubRecord *pSubRec;
	CString Buffer;
	aidata_t *pAiData;
	int Index;

	if (m_pRecInfo == NULL || m_pDlgHandler == NULL) {
		return;
	}

	pCreature = (CEsmCreature *)m_pRecInfo->pRecord;
	/* Save the basic AI settings */
	pAiData = pCreature->GetAIData();

	if (pAiData != NULL) {
		m_AlarmText.GetWindowText(Buffer);
		pAiData->Alarm = (byte)atoi(Buffer);
		m_FleeText.GetWindowText(Buffer);
		pAiData->Flee = (byte)atoi(Buffer);
		m_FightText.GetWindowText(Buffer);
		pAiData->Fight = (byte)atoi(Buffer);
		m_HelloText.GetWindowText(Buffer);
		pAiData->Hello = (byte)atoi(Buffer);
	}

	/* Delete the current AI package sub-records */
	pCreature->DeleteSubRecords(MWESM_SUBREC_AI_W);
	pCreature->DeleteSubRecords(MWESM_SUBREC_AI_T);
	pCreature->DeleteSubRecords(MWESM_SUBREC_AI_A);
	pCreature->DeleteSubRecords(MWESM_SUBREC_AI_F);
	pCreature->DeleteSubRecords(MWESM_SUBREC_AI_E);
	pCreature->DeleteSubRecords(MWESM_SUBREC_CNDT);

	/* Save the AI package sub-records */

	for (Index = 0; Index < m_PackageArray.GetSize(); Index++) {
		pSubRec = m_PackageArray.GetAt(Index);
		pCreature->AddSubRecord(pSubRec);
	}

	m_PackageArray.RemoveAll();
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - CEsmSubNameFix* FindCNDTSubRec (pSubRecord);
 *
 * Finds and returns the CNDT record associated with the given subrecord,
 * or NULL if none is found.
 *
 *=========================================================================*/

CEsmSubNameFix *CEsmCreaturePage4::FindCNDTSubRec(CEsmSubRecord *pSubRecord) {
	CEsmSubRecord *pSubRec;
	int Index;

	for (Index = 0; Index < m_PackageArray.GetSize(); Index++) {
		pSubRec = m_PackageArray.GetAt(Index);

		if (pSubRec == pSubRecord) {
			if (Index + 1 == m_PackageArray.GetSize()) {
				return NULL;
			}

			pSubRec = m_PackageArray.GetAt(Index + 1);

			if (pSubRec->IsType(MWESM_SUBREC_CNDT)) {
				return (CEsmSubNameFix *)pSubRec;
			}

			return NULL;
		}
	}

	return NULL;
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::FindCNDTSubRec()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - CMWEditDoc* GetDocument (void);
 *
 *=========================================================================*/

CMWEditDoc *CEsmCreaturePage4::GetDocument() {
	DEFINE_FUNCTION("CEsmCreaturePage4::GetDocument()");
	ASSERT(m_pDlgHandler != NULL);
	return m_pDlgHandler->GetDocument();
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::GetDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Event - LRESULT OnDblclkObjectlist (lParam, wParam);
 *
 *=========================================================================*/

LRESULT CEsmCreaturePage4::OnEditRecord(LPARAM lParam, WPARAM wParam) {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnEditRecord()");
	CEsmSubRecord *pSubRecord;
	bool Result = false;
	int ListIndex;

	/* Ignore if no item currently selected */

	if (lParam < 0) {
		return (0);
	}

	/* Display the model reference dialog */
	pSubRecord = (CEsmSubRecord *)m_PackageList.GetItemData(lParam);

	if (pSubRecord->IsType(MWESM_SUBREC_AI_A)) {
		CEsmAiActivateDlg Dialog;
		Result = Dialog.DoModal((CEsmSubAI_A *)pSubRecord);
	} else if (pSubRecord->IsType(MWESM_SUBREC_AI_W)) {
		CEsmAiWanderDlg Dialog;
		Result = Dialog.DoModal((CEsmSubAI_W *)pSubRecord);
	} else if (pSubRecord->IsType(MWESM_SUBREC_AI_E) || pSubRecord->IsType(MWESM_SUBREC_AI_F)) {
		CEsmAiEscortDlg Dialog;
		CString CellName;
		CEsmSubNameFix *pCellName;
		pCellName = FindCNDTSubRec(pSubRecord);
		Result = Dialog.DoModal((CEsmSubAI_E *)pSubRecord,
		                        pCellName ? pCellName->GetName() : NULL,
		                        pSubRecord->IsType(MWESM_SUBREC_AI_E) ? _T("Escort") : _T("Follow"));

		if (Result) {
			CellName = Dialog.GetCellName();

			if (CellName.IsEmpty() && pCellName != NULL) {
				m_PackageArray.DeleteElement(pCellName);
				DestroyPointer(pCellName);
			} else if (!CellName.IsEmpty() && pCellName == NULL) {
				CreatePointer(pCellName, CEsmSubNameFix);
				pCellName->SetType(MWESM_SUBREC_CNDT);
				pCellName->CreateNew();
				ListIndex = m_PackageArray.FindElement(pSubRecord);
				m_PackageArray.Insert(pCellName, ListIndex);
				pCellName->SetName(CellName);
			} else if (!CellName.IsEmpty() && pCellName != NULL) {
				pCellName->SetName(CellName);
			}
		}
	} else if (pSubRecord->IsType(MWESM_SUBREC_AI_T)) {
		CEsmAiTravelDlg Dialog;
		Result = Dialog.DoModal((CEsmSubAI_T *)pSubRecord);
	}

	if (Result) {
		UpdatePackageList();
	}

	return 0;
}

/*===========================================================================
 *      End of Class Event CEsmCreaturePage4::OnDblclkObjectlist()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/

BOOL CEsmCreaturePage4::OnInitDialog() {
	CPropertyPage::OnInitDialog();

	/* Spell List */
	m_PackageList.OnInitCtrl();
	m_PackageList.SetEnableDrag(false);
	m_PackageList.SetAcceptDrag(false);
	m_PackageList.SetWantKeys(true);
	m_PackageList.SetActNormal(true);
	m_PackageList.SetWantEditMsg(true);
	m_PackageList.InsertColumn(0, _T("Package"), LVCFMT_LEFT, 120, 0);

	return TRUE;
}

/*===========================================================================
 *      End of Class Event CEsmCreaturePage4::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Event - void OnItemchangingPackagelist (pNMHDR, pResult);
 *
 *=========================================================================*/

void CEsmCreaturePage4::OnItemchangingPackagelist(NMHDR *pNMHDR, LRESULT *pResult) {
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	*pResult = 0;

	if ((pNMListView->uChanged & LVIF_STATE) != 0
	    && (pNMListView->uNewState & LVIS_SELECTED ) != 0) {
		CEsmSubRecord *pSubRec = (CEsmSubRecord *)m_PackageList.GetItemData(pNMListView->iItem);
		OutputAIData(pSubRec);
	} else if ((pNMListView->uChanged & LVIF_STATE) != 0 ) {
		OutputAIData(NULL);
	} else if ((pNMListView->uChanged & LVIF_PARAM) != 0 ) {
		OutputAIData(NULL);
	}
}

/*===========================================================================
 *      End of Class Event CEsmCreaturePage4::OnItemchangingPackagelist()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Event - LRESULT OnRecordKey (lParam, wParam);
 *
 *=========================================================================*/

LRESULT CEsmCreaturePage4::OnRecordKey(LPARAM lParam, LPARAM wParam) {
	/* Delete all currently selected items */
	if (lParam == VK_DELETE || lParam == VK_BACK) {
		DeleteSelectedItems();
		return 1;
	}

	return 0;
}

/*===========================================================================
 *      End of Class Event CEsmCreaturePage4::OnRecordKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void OutputAIData (pSubRec);
 *
 * Attempts to output the given AI package sub-record to the text control.
 *
 *=========================================================================*/

void CEsmCreaturePage4::OutputAIData(CEsmSubRecord *pSubRec) {
	CString Buffer;

	if (pSubRec == NULL) {
		m_PackageText.SetWindowText(_T(""));
	} else if (pSubRec->IsType(MWESM_SUBREC_AI_T)) {
		ai_tdata_t *pAiData = ((CEsmSubAI_T *)pSubRec)->GetAIData();
		Buffer.Format(_T("X = %g\r\nY = %g\r\nZ = %g"), pAiData->X, pAiData->Y, pAiData->Z);
		m_PackageText.SetWindowText(Buffer);
	} else if (pSubRec->IsType(MWESM_SUBREC_AI_W)) {
		ai_wdata_t *pAiData = ((CEsmSubAI_W *)pSubRec)->GetAIData();
		Buffer.Format(
		    _T("Distance = %d\r\nDuration = %g hours\r\nTime of Day = %g:00\r\nIdle2 = %d\r\nIdle3 = %d\r\nIdle4 = %d\r\nIdle5 = %d\r\nIdle6 = %d\r\nIdle7 = %d\r\nIdle8 = %d\r\nIdle9 = %d"),
		    (int)pAiData->Distance,
		    (int)pAiData->Duration,
		    (int)pAiData->TimeOfDay,
		    (int)pAiData->Idle[0],
		    (int)pAiData->Idle[1],
		    (int)pAiData->Idle[2],
		    (int)pAiData->Idle[3],
		    (int)pAiData->Idle[4],
		    (int)pAiData->Idle[5],
		    (int)pAiData->Idle[6],
		    (int)pAiData->Idle[7]);
		m_PackageText.SetWindowText(Buffer);
	} else if (pSubRec->IsType(MWESM_SUBREC_AI_A)) {
		ai_adata_t *pAiData = ((CEsmSubAI_A *)pSubRec)->GetAIData();
		Buffer.Format(_T("Name = %s"), pAiData->Name);
		m_PackageText.SetWindowText(Buffer);
	} else if (pSubRec->IsType(MWESM_SUBREC_AI_E) || pSubRec->IsType(MWESM_SUBREC_AI_F)) {
		ai_edata_t *pAiData = ((CEsmSubAI_E *)pSubRec)->GetAIData();
		int ListIndex = m_PackageArray.FindElement(pSubRec);
		CEsmSubRecord* pCellName = m_PackageArray.GetAt(ListIndex + 1);

		if (pCellName != NULL && pCellName->IsType(MWESM_SUBREC_CNDT)) {
			if (pAiData->X != FLT_MAX)
				Buffer.Format(_T("Name = %s\n\rDuration = %d\r\nCell = %s\r\nX = %.0g\r\nY = %.0g\r\nZ = %.0g"),
				              pAiData->ID,
				              (int)pAiData->Duration,
				              ((CEsmSubNameFix *)pCellName)->GetName(),
				              pAiData->X,
				              pAiData->Y,
				              pAiData->Z);
			else {
				Buffer.Format(_T("Name = %s\r\nDuration = %d\r\nCell = %s"),
				              pAiData->ID,
				              (int)pAiData->Duration,
				              ((CEsmSubNameFix *)pCellName)->GetName());
			}
		} else {
			Buffer.Format(_T("Name = %s\r\nDuration = %d"), pAiData->ID, (int)pAiData->Duration);
		}

		m_PackageText.SetWindowText(Buffer);
	}
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::OutputAIData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void SetControlData (void);
 *
 *=========================================================================*/

void CEsmCreaturePage4::SetControlData() {
	CEsmCreature *pCreature;
	CString Buffer;
	aidata_t *pAiData;

	if (m_pRecInfo == NULL || m_pDlgHandler == NULL) {
		return;
	}

	m_PackageList.SetDlgHandler(m_pDlgHandler);
	pCreature = (CEsmCreature *)m_pRecInfo->pRecord;
	pAiData = pCreature->GetAIData();

	if (pAiData != NULL) {
		Buffer.Format(_T("%d"), (int)pAiData->Alarm);
		m_AlarmText.SetWindowText(Buffer);
		Buffer.Format(_T("%d"), (int)pAiData->Flee);
		m_FleeText.SetWindowText(Buffer);
		Buffer.Format(_T("%d"), (int)pAiData->Fight);
		m_FightText.SetWindowText(Buffer);
		Buffer.Format(_T("%d"), (int)pAiData->Hello);
		m_HelloText.SetWindowText(Buffer);
	}

	AddAIRecords(MWESM_SUBREC_AI_W);
	AddAIRecords(MWESM_SUBREC_AI_A);
	AddAIRecords(MWESM_SUBREC_AI_T);
	AddAIRecords(MWESM_SUBREC_AI_F);
	AddAIRecords(MWESM_SUBREC_AI_E);
	UpdatePackageList();
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Package Event Buttons
 *
 *=========================================================================*/

void CEsmCreaturePage4::OnActivatebutton() {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnActivatebutton()");
	CEsmSubAI_A *pNewSubRec;
	bool Result;

	/* Create the new sub-record */
	CreatePointer(pNewSubRec, CEsmSubAI_A);
	pNewSubRec->SetType(MWESM_SUBREC_AI_A);
	pNewSubRec->CreateNew();

	/* Display the dialog to edit it */
	CEsmAiActivateDlg Dialog;
	Result = Dialog.DoModal(pNewSubRec);

	/* Delete the new sub-record on cancel */

	if (!Result) {
		DestroyPointer(pNewSubRec);
		return;
	}

	/* Save the new sub-record and update display */
	m_PackageArray.Add(pNewSubRec);
	UpdatePackageList();
}

void CEsmCreaturePage4::OnEscortbutton() {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnEscortbutton()");
	CEsmSubAI_E *pNewSubRec;
	CEsmSubNameFix *pCellName;
	CString CellName;
	bool Result;

	/* Create the new sub-record */
	CreatePointer(pNewSubRec, CEsmSubAI_E);
	pNewSubRec->SetType(MWESM_SUBREC_AI_E);
	pNewSubRec->CreateNew();

	/* Display the dialog to edit it */
	CEsmAiEscortDlg Dialog;
	Result = Dialog.DoModal(pNewSubRec, NULL, _T("Escort"));

	/* Delete the new sub-record on cancel */

	if (!Result) {
		DestroyPointer(pNewSubRec);
		return;
	}

	/* Save the new sub-record */
	m_PackageArray.Add(pNewSubRec);
	/* Create the cell name record if required */
	CellName = Dialog.GetCellName();

	if (!CellName.IsEmpty()) {
		CreatePointer(pCellName, CEsmSubNameFix);
		pCellName->CreateNew();
		pCellName->SetType(MWESM_SUBREC_CNDT);
		pCellName->SetName(CellName);
		m_PackageArray.Add(pCellName);
	}

	UpdatePackageList();
}

void CEsmCreaturePage4::OnFollowbutton() {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnEscortbutton()");
	CEsmSubAI_E *pNewSubRec;
	CEsmSubNameFix *pCellName;
	CString CellName;
	bool Result;

	/* Create the new sub-record */
	CreatePointer(pNewSubRec, CEsmSubAI_E);
	pNewSubRec->SetType(MWESM_SUBREC_AI_F);
	pNewSubRec->CreateNew();

	/* Display the dialog to edit it */
	CEsmAiEscortDlg Dialog;
	Result = Dialog.DoModal(pNewSubRec, NULL, _T("Follow"));

	/* Delete the new sub-record on cancel */

	if (!Result) {
		DestroyPointer(pNewSubRec);
		return;
	}

	/* Save the new sub-record */
	m_PackageArray.Add(pNewSubRec);
	/* Create the cell name record if required */
	CellName = Dialog.GetCellName();

	if (!CellName.IsEmpty()) {
		CreatePointer(pCellName, CEsmSubNameFix);
		pCellName->SetType(MWESM_SUBREC_CNDT);
		pCellName->CreateNew();
		pCellName->SetName(CellName);
		m_PackageArray.Add(pCellName);
	}

	UpdatePackageList();
}

void CEsmCreaturePage4::OnTravelbutton() {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnTravelbutton()");
	CEsmSubAI_T *pNewSubRec;
	bool Result;

	/* Create the new sub-record */
	CreatePointer(pNewSubRec, CEsmSubAI_T);
	pNewSubRec->SetType(MWESM_SUBREC_AI_T);
	pNewSubRec->CreateNew();

	/* Display the dialog to edit it */
	CEsmAiTravelDlg Dialog;
	Result = Dialog.DoModal(pNewSubRec);

	/* Delete the new sub-record on cancel */

	if (!Result) {
		DestroyPointer(pNewSubRec);
		return;
	}

	/* Save the new sub-record and update display */
	m_PackageArray.Add(pNewSubRec);
	UpdatePackageList();
}

void CEsmCreaturePage4::OnWanderbutton() {
	DEFINE_FUNCTION("CEsmCreaturePage4::OnWanderbutton()");
	CEsmSubAI_W *pNewSubRec;
	bool Result;

	/* Create the new sub-record */
	CreatePointer(pNewSubRec, CEsmSubAI_W);
	pNewSubRec->SetType(MWESM_SUBREC_AI_W);
	pNewSubRec->CreateNew();

	/* Display the dialog to edit it */
	CEsmAiWanderDlg Dialog;
	Result = Dialog.DoModal(pNewSubRec);

	/* Delete the new sub-record on cancel */

	if (!Result) {
		DestroyPointer(pNewSubRec);
		return;
	}

	/* Save the new sub-record and update display */
	m_PackageArray.Add(pNewSubRec);
	UpdatePackageList();
}

void CEsmCreaturePage4::OnEditbutton() {
	POSITION SelPos;
	SelPos = m_PackageList.GetFirstSelectedItemPosition();

	if (SelPos == NULL) {
		return;
	}

	OnEditRecord(m_PackageList.GetNextSelectedItem(SelPos), 0);
}

void CEsmCreaturePage4::OnDeletebutton() {
	DeleteSelectedItems();
}

/*===========================================================================
 *      End of Package Event Buttons
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmCreaturePage4 Method - void UpdatePackageList (void);
 *
 *=========================================================================*/

void CEsmCreaturePage4::UpdatePackageList() {
	CEsmSubRecord *pSubRecord;
	int Index;
	int ListIndex;
	/* Clear the current list */
	m_PackageList.DeleteAllItems();

	for (Index = 0; Index < m_PackageArray.GetSize(); Index++) {
		pSubRecord = m_PackageArray.GetAt(Index);

		if (pSubRecord->IsType(MWESM_SUBREC_AI_W)) {
			ListIndex = m_PackageList.InsertItem(Index, _T("Wander"), -1);
		} else if (pSubRecord->IsType(MWESM_SUBREC_AI_A)) {
			ListIndex = m_PackageList.InsertItem(Index, _T("Activate"), -1);
		} else if (pSubRecord->IsType(MWESM_SUBREC_AI_E)) {
			ListIndex = m_PackageList.InsertItem(Index, _T("Escort"), -1);
		} else if (pSubRecord->IsType(MWESM_SUBREC_AI_T)) {
			ListIndex = m_PackageList.InsertItem(Index, _T("Travel"), -1);
		} else if (pSubRecord->IsType(MWESM_SUBREC_AI_F)) {
			ListIndex = m_PackageList.InsertItem(Index, _T("Follow"), -1);
		} else if (pSubRecord->IsType(MWESM_SUBREC_CNDT)) {
			ListIndex = -1;
		} else {
			ListIndex = m_PackageList.InsertItem(Index, _T("Unknown"), -1);
		}

		if (ListIndex >= 0) {
			m_PackageList.SetItemData(ListIndex, (DWORD)pSubRecord);
		}
	}
}

/*===========================================================================
 *      End of Class Method CEsmCreaturePage4::UpdatePackageList()
 *=========================================================================*/
