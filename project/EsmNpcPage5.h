/*===========================================================================
 *
 * File:    Esmnpcpage5.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMNPCPAGE5_H
#define __ESMNPCPAGE5_H


#include "EsmListCtrl.h"


class CEsmDlgHandler;


/*===========================================================================
 *
 * Begin Class CEsmNpcPage5 Definition
 *
 *=========================================================================*/
class CEsmNpcPage5 : public CPropertyPage {
	DECLARE_DYNCREATE(CEsmNpcPage5);

  protected:
	esmrecinfo_t *m_pRecInfo;
	CEsmDlgHandler *m_pDlgHandler;


  public:
	/* Construction */
	CEsmNpcPage5();
	~CEsmNpcPage5();

	/* Get class members */
	CMWEditDoc *GetDocument();
	int OnUpdateItem(esmrecinfo_t *pRecInfo);

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

	/* Enables/disables controls */
	void UpdateAutoCalc(const bool AutoCalc);

	/* Dialog Data */

	//{{AFX_DATA(CEsmNpcPage5)
	enum {
		IDD = IDD_NPC_VIEW5
	};

	CComboBox m_CellList4;
	CComboBox m_CellList3;
	CComboBox m_CellList2;
	CComboBox m_CellList1;

	CButton m_RepairsItemsCheck;
	CButton m_TrainCheck;
	CButton m_SpellmakeCheck;
	CButton m_EnchantCheck;

	CEdit m_GoldText;

	CButton m_WeaponCheck;
	CButton m_SpellCheck;
	CButton m_MagicCheck;
	CButton m_RepairCheck;
	CButton m_PotionCheck;
	CButton m_ProbeCheck;
	CButton m_MiscCheck;
	CButton m_PickCheck;
	CButton m_LightCheck;
	CButton m_IngreCheck;
	CButton m_ClothCheck;
	CButton m_BookCheck;
	CButton m_ArmorCheck;
	CButton m_ApparatusCheck;
	//}}AFX_DATA

	/* ClassWizard generate virtual function overrides */

	//{{AFX_VIRTUAL(CEsmNpcPage5)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmNpcPage5)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
