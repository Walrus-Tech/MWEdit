/*===========================================================================
 *
 * File:    Esmextcellpage.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMEXTCELLPAGE_H
#define __ESMEXTCELLPAGE_H


#include "project/ColorStatic1.h"
#include "esm/EsmFile.h"


class CEsmRecDialog;
class CMWEditDoc;


/*===========================================================================
 *
 * Begin Class CEsmExtCellPage Definition
 *
 *=========================================================================*/
class CEsmExtCellPage : public CPropertyPage {
	DECLARE_DYNCREATE(CEsmExtCellPage);

  protected:
	esmrecinfo_t *m_pRecInfo;
	CEsmRecDialog *m_pDlgParent;


  public:
	/* Construction */
	CEsmExtCellPage();
	~CEsmExtCellPage();

	/* Get class members */
	CMWEditDoc *GetDocument();

	/* Set class members */
	void SetRecInfo(esmrecinfo_t *pRecInfo) {
		m_pRecInfo = pRecInfo;
	}

	void SetEsmRecParent(CEsmRecDialog *pDialog) {
		m_pDlgParent = pDialog;
	}

	/* Get/set control data */
	void GetControlData();
	void SetControlData();

	/* Update record data */
	int OnUpdateItem(esmrecinfo_t *pRecInfo);

	/* Dialog Data */

	//{{AFX_DATA(CEsmExtCellPage)
	enum {
		IDD = IDD_EXTCELL_PAGE
	};

	CButton m_ColorButton;

	CColorStatic m_ColorBox;

	CSpinButtonCtrl m_BSpin;
	CSpinButtonCtrl m_GSpin;
	CSpinButtonCtrl m_RSpin;

	CEdit m_BlueText;
	CEdit m_GreenText;
	CEdit m_RedText;

	CComboBox m_RegionList;

	CButton m_MapCheck;
	CButton m_SleepCheck;
	//}}AFX_DATA

	/* ClassWizard generate virtual function overrides */

	//{{AFX_VIRTUAL(CEsmExtCellPage)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmExtCellPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnColorbutton();
	afx_msg void OnChangeColor();
	afx_msg void OnMapcheck();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
