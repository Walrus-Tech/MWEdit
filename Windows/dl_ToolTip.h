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


#include "Windows/WinUtil.h"


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
 *
 * Begin Class CDlToolTip Definition
 *
 * Simple custom tool tip class.
 *
 *=========================================================================*/
class CDlToolTip : CWnd {
  private:
	LPCTSTR m_szClass; /* Window class */
	CPoint m_ptOrigin;
	int m_nShowDelay;
	UINT m_nTimer;
	CFont *m_pFont;
	CString m_szText;
	bool m_IsOpen;


  protected:
	/* Compute the window region */
	BOOL GetWindowRegion(CDC *pDC, HRGN *phRegion, CSize *pSize = NULL);

	//{{AFX_MSG(CDlToolTip)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();

  public:
	/* Class Constructors/Destructors */
	CDlToolTip();
	virtual ~CDlToolTip();

	/* Create the custom window */
	BOOL Create(CWnd *parent);

	/* Get class members */
	bool IsOpen() {
		return m_IsOpen;
	}

	CPoint &GetToolTipPoint() {
		return m_ptOrigin;
	}

	/* Show or hide the tool tip */
	void Hide() {
		ShowWindow(SW_HIDE);
		m_IsOpen = false;
	}

	void Show(const TCHAR *pszText, CPoint *pPoint = NULL);

	/* Set class member */
	void SetShowDelay(int nDelay) {
		m_nShowDelay = nDelay;
	}

	void SetFont(CFont *pFont) {
		m_pFont = pFont;

		if (IsWindow(m_hWnd)) {
			RedrawWindow();
		}
	}
};


#endif
