/*===========================================================================
 *
 * File:    Esmdoordlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 15, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMDOORDLG_H
#define __ESMDOORDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmDoorDlg Definition
 *
 *=========================================================================*/
class CEsmDoorDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmDoorDlg);

  protected:
	CEsmDoor *m_pDoor;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmDoorDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmDoorDlg)
	enum {
		IDD = IDD_DOOR_DLG
	};

	CComboBox m_OpenList;
	CComboBox m_CloseList;
	CComboBox m_ScriptList;

	CButton m_PersistCheck;
	CButton m_BlockedCheck;

	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmDoorDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmDoorDlg)
	afx_msg void OnOpenbutton();
	afx_msg void OnClosebutton();
	afx_msg void OnOpenPlay();
	afx_msg void OnClosePlay();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
