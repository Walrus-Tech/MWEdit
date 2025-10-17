/*===========================================================================
 *
 * File:    Esmaiactivatedlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 24, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMAIACTIVATEDLG_H
#define __ESMAIACTIVATEDLG_H


#include "esm/EsmSubAI_A.h"


/*===========================================================================
 *
 * Begin Class CEsmAiActivateDlg
 *
 *=========================================================================*/
class CEsmAiActivateDlg : public CDialog {
  protected:
	CEsmSubAI_A *m_pSubRecord;


  public:
	/* Construction */
	CEsmAiActivateDlg(CWnd *pParent = NULL);


	/* Main access method */
	bool DoModal(CEsmSubAI_A *pSubRecord);

	/* Dialog Data */

	//{{AFX_DATA(CEsmAiActivateDlg)
	enum {
		IDD = IDD_AIACTIVATE_DLG
	};

	CComboBox m_TargetList;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
	//{{AFX_VIRTUAL(CEsmAiActivateDlg)


  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL


  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmAiActivateDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
