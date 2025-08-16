/*===========================================================================
 *
 * File:    Esmmiscdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 16, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMMISCDLG_H
#define __ESMMISCDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmMiscDlg Definition
 *
 *=========================================================================*/
class CEsmMiscDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmMiscDlg);

  protected:
	CEsmMisc *m_pMisc;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmMiscDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmMiscDlg)
	enum {
		IDD = IDD_MISC_DLG
	};

	CButton m_PersistCheck;
	CButton m_BlockedCheck;

	CEdit m_ValueText;
	CEdit m_WeightText;
	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmMiscDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmMiscDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
