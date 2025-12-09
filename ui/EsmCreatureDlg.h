/*===========================================================================
 *
 * File:    Esmcreaturedlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 15, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMCREATUREDLG_H
#define __ESMCREATUREDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"
#include "Windows/TabCtrlSheet.h"
#include "project/EsmCreaturePage1.h"
#include "project/EsmCreaturePage2.h"
#include "project/EsmCreaturePage3.h"
#include "project/EsmCreaturePage4.h"
#include "project/EsmCreaturePage5.h"


/*===========================================================================
 *
 * Begin Class CEsmCreatureDlg Definition
 *
 *=========================================================================*/
class CEsmCreatureDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmCreatureDlg);

  protected:
	CEsmCreaturePage1 m_Page1;
	CEsmCreaturePage2 m_Page2;
	CEsmCreaturePage3 m_Page3;
	CEsmCreaturePage4 m_Page4;
	CEsmCreaturePage5 m_Page5;

	CEsmCreature *m_pCreature;


  public:
	/* Construction */
	CEsmCreatureDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmCreatureDlg)
	enum {
		IDD = IDD_CREATURE_DLG
	};

	CTabCtrlSheet m_MainTab;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmCreatureDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmCreatureDlg)
	afx_msg void OnScriptEdit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
