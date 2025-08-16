/*===========================================================================
 *
 * File:    EsmScriptCompareDlg.H
 * Author:  Dave Humphrey (uesp@sympatico.ca)
 * Created On:  September 8, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSCRIPTCOMPAREDLG_H
#define __ESMSCRIPTCOMPAREDLG_H


#include "MWEditDoc.h"
#include "EsmListCtrl.h"


class CEsmDlgHandler;


/*===========================================================================
 *
 * Begin CEsmScriptCompareDlg Definition
 *
 *=========================================================================*/
class CEsmScriptCompareDlg : public CFormView {
  protected:
	CEsmDlgHandler *m_pDlgHandler; /* Reference to parent handler */


	CEsmScriptCompareDlg();
	virtual ~CEsmScriptCompareDlg();

	DECLARE_DYNCREATE(CEsmScriptCompareDlg);


  public:
	/* Add text to the log */
	void AddLogText(const TCHAR *pString, va_list Args);

	/* Clear the text */
	void ClearText() {
		m_LogText.SetWindowText("");
	}

	/* Set class members */
	void SetDlgHandler(CEsmDlgHandler *pParent) {
		m_pDlgHandler = pParent;
	}

	/* Update the view title */
	void UpdateTitle();

	/* Dialog Data */

	//{{AFX_DATA(CEsmScriptCompareDlg)
	enum {
		IDD = IDD_SCRIPTCOMPARE_DLG
	};

	CEdit m_LogText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmScriptCompareDlg)

  public:
	virtual void OnInitialUpdate();

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Class diagnostics */

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

	/* Generated message map functions */

	//{{AFX_MSG(CEsmScriptCompareDlg)
	afx_msg void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
