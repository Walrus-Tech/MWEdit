/*===========================================================================
 *
 * File:    Esmnpcpage2.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 23, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMNPCPAGE2_H
#define __ESMNPCPAGE2_H


#include "EsmListCtrl.h"


class CEsmDlgHandler;


/*===========================================================================
 *
 * Begin Class CEsmNpcPage2 Definition
 *
 *=========================================================================*/
class CEsmNpcPage2 : public CPropertyPage {
	DECLARE_DYNCREATE(CEsmNpcPage2);

  protected:
	esmrecinfo_t *m_pRecInfo;
	CEsmDlgHandler *m_pDlgHandler;


  public:
	/* Construction */
	CEsmNpcPage2();
	~CEsmNpcPage2();

	/* Get class members */
	CMWEditDoc *GetDocument();

	/* Update item data */
	virtual int OnUpdateItem(esmrecinfo_t *pRecInfo);

	/* Set class members */
	void SetRecInfo(esmrecinfo_t *pRecInfo) {
		m_pRecInfo = pRecInfo;
	}

	void SetDlgHandler(CEsmDlgHandler *pParent) {
		m_pDlgHandler = pParent;
	}

	/* Get/set control data */
	void GetControlData();
	void SetControlData();


	/* Dialog Data */

	//{{AFX_DATA(CEsmNpcPage2)
	enum {
		IDD = IDD_NPC_VIEW2
	};

	CEsmListCtrl m_SpellList;
	//}}AFX_DATA

	/* ClassWizard generate virtual function overrides */

	//{{AFX_VIRTUAL(CEsmNpcPage2)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmNpcPage2)
	afx_msg LRESULT OnRecordDrop(LPARAM lParam, LPARAM wParam);
	afx_msg LRESULT OnRecordKey(LPARAM lParam, LPARAM wParam);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
