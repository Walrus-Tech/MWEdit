/*===========================================================================
 *
 * File:    Esminfodlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 22, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMINFODLG_H
#define __ESMINFODLG_H


#include "EsmInfo.h"
#include "contain/ptrarray.h"


class CMWEditDoc;


/*===========================================================================
 *
 * Begin Class CEsmInfoDlg Definition
 *
 *=========================================================================*/
class CEsmInfoDlg : public CDialog {
  protected:
	CEsmInfo *m_pInfo; /* The info object we are editting */
	bool m_IsNew;
	bool m_AlreadyIsNew;
	CMWEditDoc *m_pDocument;


  public:
	/* Construction */
	CEsmInfoDlg(CWnd *pParent = NULL);

	/* Main access method */
	bool DoModal(CEsmInfo *pInfo, const bool IsNew, CMWEditDoc *pDocument);

	/* Get class members */
	bool HasNewInfo() {
		return m_IsNew;
	}

	CEsmInfo *GetInfo() {
		return m_pInfo;
	}

	/* Set/get control data */
	void GetControlData();
	void SetControlData();
	void GetFuncData(const int Index, int &FuncIndex);
	void SetFuncData(const int Index, CEsmSubSCVR *pFuncData, CEsmSubRecord *pValue);

	/* Dialog Data */

	//{{AFX_DATA(CEsmInfoDlg)
	enum {
		IDD = IDD_INFO_DLG
	};

	CButton m_SoundButton;

	CStatic m_SoundLabel;

	CEdit m_ResultText;

	CComboBox m_PCRankList;
	CComboBox m_PCFactionList;
	CComboBox m_CellList;
	CComboBox m_RankList;
	CComboBox m_FactionList;
	CComboBox m_ClassList;
	CComboBox m_RaceList;
	CComboBox m_IDList;

	CEdit m_DispText;

	CComboBox m_GenderList;

	CEdit m_NameText;
	CEdit m_IDText;
	//}}AFX_DATA

	CEdit m_ValueText[MWESM_INFO_MAXFUNCS];

	CComboBox m_CompareList[MWESM_INFO_MAXFUNCS];
	CComboBox m_FuncVarList[MWESM_INFO_MAXFUNCS];
	CComboBox m_TypeList[MWESM_INFO_MAXFUNCS];


	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmInfoDlg)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmInfoDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIdlist();
	afx_msg void OnSoundbutton();
	//}}AFX_MSG

	afx_msg void OnSelChangeTypeList(const int Index);

	afx_msg void OnSelchangeTypelist1() {
		OnSelChangeTypeList(0);
	}

	afx_msg void OnSelchangeTypelist2() {
		OnSelChangeTypeList(1);
	}

	afx_msg void OnSelchangeTypelist3() {
		OnSelChangeTypeList(2);
	}

	afx_msg void OnSelchangeTypelist4() {
		OnSelChangeTypeList(3);
	}

	afx_msg void OnSelchangeTypelist5() {
		OnSelChangeTypeList(4);
	}

	afx_msg void OnSelchangeTypelist6() {
		OnSelChangeTypeList(5);
	}

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
