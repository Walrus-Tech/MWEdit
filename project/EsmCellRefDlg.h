/*===========================================================================
 *
 * File:    Esmcellrefdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 22, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCELLREFDLG_H
#define __ESMCELLREFDLG_H


#include "project/EsmSubCellRefDlg.h"
#include "esm/EsmCell.h"
#include "Common/Contain/PtrArray.h"


/*===========================================================================
 *
 * Begin Class CEsmCellRefDlg Definition
 *
 *=========================================================================*/
class CEsmCellRefDlg : public CDialog {
  protected:
	CEsmSubCellRef *m_pCellRef; /* The cell reference we are editting */
	CEsmCell *m_pCell;
	bool m_HasNewCellRef;
	bool m_IsAlreadyNew;


  public:
	/* Construction */
	CEsmCellRefDlg(CWnd *pParent = NULL);

	/* Main access method */
	bool DoModal(CEsmSubCellRef *pCellRef, const bool IsNew, CEsmCell *pCell);

	/* Get class members */
	bool HasNewCellRef() {
		return m_HasNewCellRef;
	}

	CEsmSubCellRef *GetCellRef() {
		return m_pCellRef;
	}

	/* Set/get control data */
	void GetControlData();
	void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmCellRefDlg)
	enum {
		IDD = IDD_CELLREF_DLG
	};

	CEdit m_ScaleText;
	CEdit m_ZRotText;
	CEdit m_YRotText;
	CEdit m_XRotText;
	CEdit m_ZPosText;
	CEdit m_YPosText;
	CEdit m_XPosText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmCellRefDlg)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

// Implementation

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmCellRefDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
