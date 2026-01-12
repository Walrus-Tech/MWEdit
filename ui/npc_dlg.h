/*===========================================================================
 *
 * File:    Esmnpcdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 23, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMNPCDLG_H
#define __ESMNPCDLG_H


#include "ui/npc_page_1.h"
#include "ui/npc_page_2.h"
#include "ui/npc_page_3.h"
#include "ui/npc_page_4.h"
#include "ui/npc_page_5.h"
#include "ui/rec_dialog.h"
#include "ui/Resource.h"
#include "windows/tab_ctrl_sheet.h"


/*===========================================================================
 *
 * Begin Class CEsmNpcDlg Definition
 *
 *=========================================================================*/
class CEsmNpcDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmNpcDlg);

  protected:
	CEsmNpcPage1 m_Page1;
	CEsmNpcPage2 m_Page2;
	CEsmNpcPage3 m_Page3;
	CEsmNpcPage4 m_Page4;
	CEsmNpcPage5 m_Page5;
	CEsmNpc *m_pNpc;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmNpcDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmNpcDlg)
	enum {
		IDD = IDD_NPC_DLG
	};

	CTabCtrlSheet m_MainTab;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmNpcDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmNpcDlg)
	afx_msg void OnSelchangingMaintab(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
