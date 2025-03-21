/*===========================================================================
 *
 * File:    Dl_tooltip.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  October 11, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __DL_TOOLTIP_H
#define __DL_TOOLTIP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "WinUtil.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Timer events */
#define DLTOOLTIP_TIMER_SHOW  1
#define DLTOOLTIP_TIMER_HIDE  2

/* Timer delays */
#define DLTOOLTIP_SHOW_DELAY  100
#define DLTOOLTIP_HIDE_DELAY  200

/* Region parameters */
#define DLTOOLTIP_CX_ROUNDED  7
#define DLTOOLTIP_CY_ROUNDED  3
#define DLTOOLTIP_CX_LEADER   25
#define DLTOOLTIP_CY_LEADER   25

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CDlToolTip Definition
 *
 * Simple custom tool tip class.
 *
 *=========================================================================*/
class CDlToolTip : CWnd {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	LPCTSTR m_szClass;  /* Window class */
	CPoint m_ptOrigin;
	int m_nShowDelay;
	UINT m_nTimer;
	CFont *m_pFont;
	CString m_szText;
	bool m_IsOpen;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Compute the window region */
	BOOL GetWindowRegion (CDC *pDC, HRGN* phRegion, CSize* pSize = NULL);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CDlToolTip();
	virtual ~CDlToolTip();

	/* Create the custom window */
	BOOL Create(CWnd *parent);

	/* Get class members */
	bool IsOpen (void) {
		return (m_IsOpen);
	}

	CPoint &GetToolTipPoint (void) {
		return (m_ptOrigin);
	}

	/* Show or hide the tool tip */
	void Hide (void) {
		ShowWindow(SW_HIDE);
		m_IsOpen = false;
	}

	void Show (const TCHAR* pszText, CPoint *pPoint = NULL);

	/* Set class member */
	void SetShowDelay (int nDelay) {
		m_nShowDelay = nDelay;
	}

	void SetFont (CFont *pFont) {
		m_pFont = pFont;

		if (IsWindow(m_hWnd)) {
			RedrawWindow();
		}
	};


  protected:

	//{{AFX_MSG(CDlToolTip)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();

};

/*===========================================================================
 *      End of Class CDlToolTip Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Dl_tooltip.H
 *=========================================================================*/
