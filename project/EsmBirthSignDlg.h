/*===========================================================================
 *
 * File:    Esmbirthsigndlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 19, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMBIRTHSIGNDLG_H
#define __ESMBIRTHSIGNDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"
#include "EsmListCtrl.h"


/*===========================================================================
 *
 * Begin Class CEsmBirthSignDlg Definition
 *
 *=========================================================================*/
class CEsmBirthSignDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmBirthSignDlg);

  protected:
	CEsmBirthSign *m_pBirthSign;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmBirthSignDlg();


	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmBirthSignDlg)
	enum {
		IDD = IDD_BIRTHSIGN_DLG
	};

	CEdit m_DescText;

	CEsmListCtrl m_SpellList;

	CButton m_TextureButton;

	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmBirthSignDlg)
  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmBirthSignDlg)
	afx_msg LRESULT OnRecordDrop(LPARAM lParam, LPARAM wParam);
	afx_msg LRESULT OnRecordKey(LPARAM lParam, LPARAM wParam);
	afx_msg void OnTexturebutton();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
