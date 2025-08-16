/*===========================================================================
 *
 * File:    Esmcelldlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 21, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCELLDLG_H
#define __ESMCELLDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"
#include "EsmIntCellPage.h"
#include "EsmExtCellPage.h"
#include "EsmRefCellPage.h"
#include "windows/TabCtrlSheet.h"


/*===========================================================================
 *
 * Begin Class CEsmCellDlg Definition
 *
 *=========================================================================*/
class CEsmCellDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmCellDlg);

  protected:
	CEsmIntCellPage m_IntCellPage; /* Tab control pages */
	CEsmExtCellPage m_ExtCellPage;
	CEsmRefCellPage m_RefCellPage;

	CEsmCell *m_pCell;


	/* Update modified items during edit */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmCellDlg();


	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmCellDlg)
	enum {
		IDD = IDD_CELL_DLG
	};

	CEdit m_GridText;

	CTabCtrlSheet m_TabControl;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmCellDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL


  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmCellDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
