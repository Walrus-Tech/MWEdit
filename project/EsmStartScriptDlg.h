/*===========================================================================
 *
 * File:    Esmstartscriptdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 13, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSTARTSCRIPTDLG_H
#define __ESMSTARTSCRIPTDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmStartScriptDlg Definition
 *
 *=========================================================================*/
class CEsmStartScriptDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmStartScriptDlg);

  protected:
	CEsmStartScript *m_pStartScript;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Standard constructor */
	CEsmStartScriptDlg(CWnd *pParent = NULL);

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmStartScriptDlg)
	enum {
		IDD = IDD_STARTSCRIPT_DLG
	};

	CButton m_BlockedCheck;
	CButton m_PersistCheck;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmStartScriptDlg)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual void OnInitialUpdate();

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmStartScriptDlg)
	afx_msg void OnSelchangeScriptlist();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION}}


#endif
