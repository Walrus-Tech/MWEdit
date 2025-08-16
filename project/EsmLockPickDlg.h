/*===========================================================================
 *
 * File:    Esmlockpickdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 16, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMLOCKPICKDLG_H
#define __ESMLOCKPICKDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmLockPickDlg Definition
 *
 *=========================================================================*/
class CEsmLockPickDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmLockPickDlg);

  protected:
	CEsmLockPick *m_pLockPick;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmLockPickDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmLockPickDlg)
	enum {
		IDD = IDD_LOCKPICK_DLG
	};

	CButton m_PersistCheck;
	CButton m_BlockedCheck;

	CEdit m_ValueText;
	CEdit m_QualityText;
	CEdit m_WeightText;
	CEdit m_UsesText;
	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmLockPickDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmLockPickDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
