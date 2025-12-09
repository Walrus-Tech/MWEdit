/*===========================================================================
 *
 * File:    Esmsettingdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 17, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSETTINGDLG_H
#define __ESMSETTINGDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmSettingDlg Definition
 *
 *=========================================================================*/
class CEsmSettingDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmSettingDlg);

  protected:
	CEsmGameSetting *m_pSetting;


  public:
	/* Construction */
	CEsmSettingDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmSettingDlg)
	enum {
		IDD = IDD_SETTING_DLG
	};

	CEdit m_ValueText;

	CStatic m_TypeLabel;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmSettingDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmSettingDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
