/*===========================================================================
 *
 * File:    Esmregiondlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 20, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMREGIONDLG_H
#define __ESMREGIONDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"
#include "project/EsmListCtrl.h"
#include "project/ColorStatic1.h"


/*===========================================================================
 *
 * Begin Class CEsmRegionDlg Definition
 *
 *=========================================================================*/
class CEsmRegionDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmRegionDlg);

  protected:
	CEsmRegion *m_pRegion;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmRegionDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmRegionDlg)
	enum {
		IDD = IDD_REGION_DLG
	};

	CColorStatic m_ColorBox;

	CSpinButtonCtrl m_BSpin;
	CSpinButtonCtrl m_GSpin;
	CSpinButtonCtrl m_RSpin;

	CEdit m_BlueText;
	CEdit m_GreenText;
	CEdit m_RedText;
	CEdit m_BlightText;
	CEdit m_AshText;
	CEdit m_ThunderText;
	CEdit m_RainText;
	CEdit m_OvercastText;
	CEdit m_FoggyText;
	CEdit m_CloudyText;
	CEdit m_ClearText;

	CComboBox m_CreatureList;

	CEsmListCtrl m_SoundList;

	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmRegionDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmRegionDlg)
	afx_msg LRESULT OnRecordDrop(LPARAM lParam, LPARAM wParam);
	afx_msg LRESULT OnRecordKey(LPARAM lParam, LPARAM wParam);
	void OnEndlabeleditItemlist(NMHDR *pNMHDR, LRESULT *pResult);
	void OnChangeColor();
	afx_msg void OnColorbutton();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
