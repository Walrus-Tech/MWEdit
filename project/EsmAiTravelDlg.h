/*===========================================================================
 *
 * File:    Esmaitraveldlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 24, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMAITRAVELDLG_H
#define __ESMAITRAVELDLG_H


#include "EsmSubAI_T.h"


/*===========================================================================
 *
 * Begin Class CEsmAiTravelDlg
 *
 *=========================================================================*/
class CEsmAiTravelDlg : public CDialog {
  protected:
	CEsmSubAI_T *m_pSubRecord;


  public:
	/* Construction */
	CEsmAiTravelDlg(CWnd *pParent = NULL);


	/* Main access method */
	bool DoModal(CEsmSubAI_T *pSubRecord);

	/* Dialog Data */

	//{{AFX_DATA(CEsmAiTravelDlg)
	enum {
		IDD = IDD_AITRAVEL_DLG
	};

	CEdit m_XText;
	CEdit m_YText;
	CEdit m_ZText;
	//}}AFX_DATA


	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmAiTravelDlg)
  protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL


  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmAiTravelDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
