/*===========================================================================
 *
 * File:    Esmsounddlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 16, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSOUNDDLG_H
#define __ESMSOUNDDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"
#include "project/EsmListCtrl.h"


/*===========================================================================
 *
 * Begin Class CEsmSoundDlg Definition
 *
 *=========================================================================*/
class CEsmSoundDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmSoundDlg);

  protected:
	CEsmSound *m_pSound;


	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);

  public:
	/* Construction */
	CEsmSoundDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmSoundDlg)
	enum {
		IDD = IDD_SOUND_DLG
	};

	CButton m_SoundButton;

	CEdit m_MinRangeText;
	CEdit m_MaxRangeText;
	CEdit m_VolumeText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmSoundDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmSoundDlg)
	afx_msg void OnSoundbutton();
	afx_msg void OnPlaysound();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
