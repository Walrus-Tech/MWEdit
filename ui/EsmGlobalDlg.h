/*===========================================================================
 *
 * File:    Esmglobaldlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 12, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMGLOBALDLG_H
#define __ESMGLOBALDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmGlobalDlg Definition
 *
 *=========================================================================*/
class CEsmGlobalDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmGlobalDlg);

  protected:
	CEsmGlobal *m_pGlobal;


  public:
	/* Construction */
	CEsmGlobalDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmGlobalDlg)
	enum {
		IDD = IDD_GLOBAL_DLG
	};

	CEdit m_ValueText;

	CComboBox m_TypeList;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmGlobalDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmGlobalDlg)
	afx_msg void OnSelchangeTypelist();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
