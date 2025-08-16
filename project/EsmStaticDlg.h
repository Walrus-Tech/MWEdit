/*===========================================================================
 *
 * File:    Esmstaticdlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 16, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSTATICDLG_H
#define __ESMSTATICDLG_H


#include "EsmRecDialog.h"
#include "Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmStaticDlg Definition
 *
 *=========================================================================*/
class CEsmStaticDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmStaticDlg);

  protected:
	CEsmStatic *m_pStatic;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);


  public:
	/* Construction */
	CEsmStaticDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmStaticDlg)
	enum {
		IDD = IDD_STATIC_DLG
	};

	CButton m_PersistCheck;
	CButton m_BlockedCheck;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmStaticDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmStaticDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
