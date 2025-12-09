/*===========================================================================
 *
 * File:    Esmrefcellpage.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMREFCELLPAGE_H
#define __ESMREFCELLPAGE_H


#include "project/ColorStatic1.h"
#include "project/EsmSubListCtrl.h"


/* Types of modified records */
#define ESMCELLREF_MODTYPE_NEW    1
#define ESMCELLREF_MODTYPE_DEL    2
#define ESMCELLREF_MODTYPE_CLEAN  3
#define ESMCELLREF_MODTYPE_MOD    4


class CEsmRecDialog;
class CMWEditDoc;

/* Holds information on modified references */
typedef struct {
	CEsmSubCellRef *pOldCellRef;
	CEsmSubCellRef *pNewCellRef;
	long Type;
	bool IsNew;
} cellrefdata_t;

typedef TPtrArray<cellrefdata_t> CEsmCellRefArray;


/*===========================================================================
 *
 * Begin Class CEsmRefCellPage Definition
 *
 *=========================================================================*/
class CEsmRefCellPage : public CPropertyPage {
	DECLARE_DYNCREATE(CEsmRefCellPage);

  protected:
	esmrecinfo_t *m_pRecInfo;
	CEsmRecDialog *m_pDlgParent;
	CEsmCellRefArray m_ModCellRefs;


	/* Add/clean/delete/modify a cell reference in the cell */
	bool AddNewCellRef(cellrefdata_t *pCellRefData);
	bool CleanCellRef(cellrefdata_t *pCellRefData);
	bool DeleteCellRef(cellrefdata_t *pCellRefData);
	bool ModifyCellRef(cellrefdata_t *pCellRefData);

	/* Add a cell reference to the modified reference array */
	cellrefdata_t *AddNewCellRef(CEsmSubCellRef *pCellRef);
	cellrefdata_t *CleanCellRef(CEsmSubCellRef *pCellRef);
	cellrefdata_t *DeleteCellRef(CEsmSubCellRef *pCellRef);
	cellrefdata_t *ModifyCellRef(CEsmSubCellRef *pCellRef);

	/* Delete any cell references in the new cell ref array */
	void ClearCellRefArray();

	/* Delete or undelete a specific record */
	void DeleteIndex(const int ListIndex, const bool Delete);

	/* Attempt to find a new/old cell reference object */
	cellrefdata_t *FindNewCellRef(CEsmSubCellRef *pCellRef);
	cellrefdata_t *FindOldCellRef(CEsmSubCellRef *pCellRef);


  public:
	/* Construction */
	CEsmRefCellPage();
	~CEsmRefCellPage();

	/* Get class members */
	CMWEditDoc *GetDocument();

	/* Set class members */
	void SetRecInfo(esmrecinfo_t *pRecInfo) {
		m_pRecInfo = pRecInfo;
	}

	void SetEsmRecParent(CEsmRecDialog *pDialog) {
		m_pDlgParent = pDialog;
	}

	/* Get/set control data */
	void GetControlData();
	void SetControlData();

	/* Update record data */
	int OnUpdateItem(esmrecinfo_t *pRecInfo);

	/* Update the cell reference list */
	void UpdateCellRefList();

	/* Dialog Data */

	//{{AFX_DATA(CEsmRefCellPage)
	enum {
		IDD = IDD_REFCELL_PAGE
	};

	CEsmSubListCtrl m_CellRefList;
	//}}AFX_DATA

	/* ClassWizard generate virtual function overrides */

	//{{AFX_VIRTUAL(CEsmRefCellPage)

  protected:
	virtual void DoDataExchange(CDataExchange *pDX);

	//}}AFX_VIRTUAL

  protected:
	/* Generated message map functions */

	//{{AFX_MSG(CEsmRefCellPage)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnRecordEdit(LPARAM lParam, LPARAM wParam);
	afx_msg LRESULT OnRecordKey(LPARAM lParam, LPARAM wParam);
	afx_msg LRESULT OnRecordDrop(LPARAM lParam, LPARAM wParam);
	afx_msg void OnContextMenu(CWnd *pWnd, CPoint point);
	afx_msg void OnEditClean();
	afx_msg void OnCellrefEditref();
	afx_msg void OnUpdateCellrefEditref(CCmdUI *pCmdUI);
	afx_msg void OnCellrefEdit();
	afx_msg void OnUpdateCellrefEdit(CCmdUI *pCmdUI);
	afx_msg void OnCellrefDelete();
	afx_msg void OnUpdateCellrefDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditClean(CCmdUI *pCmdUI);
	afx_msg void OnCellrefUndelete();
	afx_msg void OnUpdateCellrefUndelete(CCmdUI *pCmdUI);
	afx_msg void OnCellrefCreatecopy();
	afx_msg void OnUpdateCellrefCreatecopy(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
