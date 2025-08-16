/*===========================================================================
 *
 * File:    Esmrecdialog.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 8, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMRECDIALOG_H
#define __ESMRECDIALOG_H


#include "EsmFile.h"
#include "EsmUtils.h"
#include "windows/WinUtil.h"
#include "MWEditDoc.h"
#include "EsmIconFrame.h"


/* Custom messaages */
#define ESMDLG_MSG_ONINFOEDIT 0x8301


class CEsmDlgHandler;
class CMWEditDoc;
class CMWEditApp;


/*===========================================================================
 *
 * Begin Class CEsmRecDialog Definition
 *
 *=========================================================================*/
class CEsmRecDialog : public CFormView {
	DECLARE_DYNCREATE(CEsmRecDialog);

  protected:
	esmreceditinfo_t m_RecEditInfo; /* Information about the record being editted */
	CEsmDlgHandler *m_pParent;
	int m_DialogID;
	const TCHAR *m_pTitle;          /* Title prefix (ex: 'Armor') */
	bool m_Modified;
	HACCEL m_hAccelator;
	CEdit m_IDText;                 /* Control for the object ID, if any */
	bool m_HasIDText;
	CButton m_IconButton;
	CButton m_ModelButton;
	CComboBox m_ScriptList;
	CEsmIconFrame m_IconPicture;


	/* Checks the ID text of the dialog to see if it has changed */
	virtual void CheckIDText();

	/* virtual update methods */
	virtual int OnUpdateRecord() {
		return 0;
	}

	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo) {
		return 0;
	}

	virtual int OnUpdateAddItem(esmrecinfo_t *pRecInfo) {
		return OnUpdateItem(pRecInfo);
	}


  public:
	/* Construction */
	CEsmRecDialog(const int IDD = 0);
	virtual ~CEsmRecDialog();

	/* Get class members */
	esmrecinfo_t *GetRecInfo() {
		return m_RecEditInfo.pRecInfo;
	}

	virtual bool IsModified() {
		return m_Modified;
	}

	bool IsRecord(esmrecinfo_t *pRecInfo);

	CEsmDlgHandler *GetParentDlg() {
		return m_pParent;
	}

	/* Retrieve the parent document object */
	CMWEditDoc *GetDocument();
	CMWEditApp *GetApp() {
		return (CMWEditApp *)AfxGetApp();
	}

	/* Set or update the record data */
	virtual void GetControlData(){ ; }
	virtual void SetControlData(){ ; }

	/* Record events */
	virtual int OnPostSaveRecord();
	virtual int OnPreSaveRecord();

	/* Set class members */
	void SetModified(const bool Flag = true) {
		m_Modified = Flag;
	}

	void SetRecInfo(esmrecinfo_t *pRecInfo) {
		m_RecEditInfo.pRecInfo = pRecInfo;
	}

	void SetIsNew(const bool IsNew) {
		m_RecEditInfo.IsNew = IsNew;
		m_RecEditInfo.HasAdded = false;
	}

	void SetParent(CEsmDlgHandler *pParent) {
		m_pParent = pParent;
	}

	void SetTitle(const TCHAR *pString) {
		m_pTitle = pString;
	}

	/* Update the window's title */
	void UpdateTitle(const TCHAR *pItemID);

	/* Dialog Data */

	//{{AFX_DATA(CEsmRecDialog)
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmRecDialog)

  public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmRecDialog)
	afx_msg void OnDestroy();
	afx_msg void OnCancel();
	afx_msg void OnIconbutton();
	afx_msg void OnModelbutton();
	afx_msg void OnSave();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnScriptEdit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
