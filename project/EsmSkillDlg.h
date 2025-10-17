/*===========================================================================
 *
 * File:    Esmskilldlg.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 18, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSKILLDLG_H
#define __ESMSKILLDLG_H


#include "project/EsmRecDialog.h"
#include "project/Resource.h"


/*===========================================================================
 *
 * Begin Class CEsmSkillDlg Definition
 *
 *=========================================================================*/
class CEsmSkillDlg : public CEsmRecDialog {
	DECLARE_DYNCREATE(CEsmSkillDlg);

  protected:
	CEsmSkill *m_pSkill;


  public:
	/* Construction */
	CEsmSkillDlg();

	/* Get class members */
	virtual bool IsModified();

	/* Set or update the record data */
	virtual void GetControlData();
	virtual void SetControlData();

	/* Dialog Data */

	//{{AFX_DATA(CEsmSkillDlg)
	enum {
		IDD = IDD_SKILL_DLG
	};

	CEdit m_ValueText4;
	CEdit m_ValueText3;
	CEdit m_ValueText2;

	CEdit m_ActionText4;
	CEdit m_ActionText3;
	CEdit m_ActionText2;

	CEdit m_ValueText1;
	CEdit m_ActionText1;
	CEdit m_DescText;

	CComboBox m_SpecialList;
	CComboBox m_AttributeList;

	CEdit m_NameText;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmSkillDlg)

  protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmSkillDlg)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
