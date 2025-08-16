/*===========================================================================
 *
 * File:    Activatordlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 10, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ACTIVATORDLG_H
#define __ACTIVATORDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmActivatorDlg Definition
 *
 *=========================================================================*/
class CEsmActivatorDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmActivatorDlg);

  protected:
	CEsmActivator *m_pActivator;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmActivatorDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmActivatorDlg)
	enum {
		IDD = IDD_ACTIVATOR_DLG
	};

	CButton m_PersistCheck;
	CButton m_BlockedCheck;
	CEdit m_NameText;
	//}}AFX_DATA


	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmActivatorDlg)
  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmActivatorDlg)
	afx_msg void OnScriptEdit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION

#endif
