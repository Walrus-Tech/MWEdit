/*===========================================================================
 *
 * File:    Dl_tooltip.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  October 11, 2003
 *
 * Description
 *
 *=========================================================================*/

/* Include Files */
#include "stdafx.h"
#include "dl_tooltip.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

DEFINE_FILE("dl_ToolTip.cpp");
/*===========================================================================
 *      End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CDlToolTip Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CDlToolTip, CWnd)
	//{{AFX_MSG_MAP(CDlToolTip)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *      End of CDlToolTip Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Constructor
 *
 *=========================================================================*/
CDlToolTip::CDlToolTip() {
	//DEFINE_FUNCTION("CDlToolTip::CDlToolTip()");
	/* Register the window class */
	m_szClass = AfxRegisterWndClass(0);
	m_nShowDelay = DLTOOLTIP_SHOW_DELAY;
	m_ptOrigin = CPoint(0, 0);
	m_pFont = NULL;
	m_IsOpen = false;
}

/*===========================================================================
 *      End of Class CDlToolTip Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Destructor
 *
 *=========================================================================*/
CDlToolTip::~CDlToolTip() {
	//DEFINE_FUNCTION("CDlToolTip::~CDlToolTip()");
}

/*===========================================================================
 *      End of Class CDlToolTip Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Method - BOOL Create (pParentWnd);
 *
 *=========================================================================*/
BOOL CDlToolTip::Create(CWnd *pParentWnd) {
	BOOL bSuccess;
	/* Must have a parent */
	ASSERT(pParentWnd != NULL);
	/* Attempt to create the custom window */
	bSuccess = CreateEx(NULL,
	                    m_szClass,
	                    NULL,
	                    WS_POPUP,
	                    0,
	                    0,
	                    0,
	                    0,
	                    pParentWnd->GetSafeHwnd(),
	                    NULL,
	                    NULL);
	/* Use default GUI font for default font */
	m_pFont = CFont::FromHandle((HFONT)::GetStockObject(ANSI_FIXED_FONT));
	return (bSuccess);
}

/*===========================================================================
 *      End of Class Method CDlToolTip::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Method - BOOL GetWindowRegion (pDC, phRegion, pSize);
 *
 * Computes the tooltip window region.
 *
 *=========================================================================*/
BOOL CDlToolTip::GetWindowRegion(CDC *pDC, HRGN *phRegion, CSize *pSize) {
	CRect rcWnd;
	CFont *pSysFont;
	/* Ensure valid input */
	ASSERT(pDC != NULL);
	ASSERT(phRegion != NULL);
	/* Calculate thea are for the tip text */
	pSysFont = (CFont *)pDC->SelectObject(m_pFont);
	pDC->DrawText(m_szText, &rcWnd, DT_CALCRECT);
	pDC->SelectObject(pSysFont);
	/* Adjust for the rounded corners */
	rcWnd.InflateRect(DLTOOLTIP_CX_ROUNDED, DLTOOLTIP_CY_ROUNDED);
	/* Create the region */
	*phRegion = ::CreateRectRgn(0, 0, rcWnd.Width(), rcWnd.Height());

	/* Set the window size */
	if (pSize != NULL) {
		pSize->cx = rcWnd.Width();
		pSize->cy = rcWnd.Height() + DLTOOLTIP_CY_LEADER;
	}

	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CDlToolTip::GetWindowRegion()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CDlToolTip::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1 ) {
		return (-1);
	}

	return (0);
}

/*===========================================================================
 *      End of Class Event CDlToolTip::OnCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Event - void OnDestroy ();
 *
 *=========================================================================*/
void CDlToolTip::OnDestroy() {
	KillTimer(m_nTimer);
	CWnd::OnDestroy();
	m_IsOpen = false;
}

/*===========================================================================
 *      End of Class Event CDlToolTip::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Event - void OnPaint ();
 *
 *=========================================================================*/
void CDlToolTip::OnPaint() {
	CPaintDC dc(this);
	CRect ClientRect;
	CBrush WindowBrush;
	CBrush FrameBrush;
	CBrush InnerFrameBrush;
	HRGN hRegion;
	CRgn *pRegion;
	CFont *pSysFont;
	/* Get the client rectangle */
	GetClientRect(ClientRect);
	/* Create the brushes */
	InnerFrameBrush.CreateSolidBrush(::GetSysColor(COLOR_SCROLLBAR));
	FrameBrush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
	WindowBrush.CreateSolidBrush(::GetSysColor(COLOR_INFOBK));
	/* Get the window region */
	GetWindowRegion(&dc, &hRegion);
	pRegion = CRgn::FromHandle(hRegion);
	/* Draw the frame */
	dc.FillRgn(pRegion, &WindowBrush);
	//dc.FrameRgn(pRegion, &InnerFrameBrush, 3, 3);
	dc.FrameRgn(pRegion, &FrameBrush, 1, 1);
	/* Adjust the area for the icon */
	ClientRect.DeflateRect(DLTOOLTIP_CX_ROUNDED, DLTOOLTIP_CY_ROUNDED, 0, 0);
	/* Set the font */
	pSysFont = (CFont *)dc.SelectObject(m_pFont);
	/* Draw the tip text */
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_szText, &ClientRect, DT_TOP | DT_LEFT);
	/* Clean up GDI */
	::DeleteObject(hRegion);
	dc.SelectObject(pSysFont);
}

/*===========================================================================
 *      End of Class Event CDlToolTip::OnPaint()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Event - void OnTimer (nIDEvent);
 *
 *=========================================================================*/
void CDlToolTip::OnTimer(UINT nIDEvent) {
	HRGN hRegion;
	CSize WindowSize;
	CDC *pDC;
	CPoint ptCursor;

	switch (nIDEvent) {
		/* Show the tip window */
		case DLTOOLTIP_TIMER_SHOW:
			KillTimer(m_nTimer);
			pDC = GetDC();
			GetWindowRegion(pDC, &hRegion, &WindowSize);
			ReleaseDC(pDC);
			::SetWindowRgn(m_hWnd, hRegion, TRUE);
			SetWindowPos(&wndTop,
			             m_ptOrigin.x + DLTOOLTIP_CX_ROUNDED,
			             m_ptOrigin.y + DLTOOLTIP_CY_ROUNDED,
			             WindowSize.cx,
			             WindowSize.cy,
			             SWP_NOACTIVATE | SWP_SHOWWINDOW);
			m_IsOpen = true;
			//m_nTimer = SetTimer(DLTOOLTIP_TIMER_HIDE, DLTOOLTIP_HIDE_DELAY, NULL);
			break;

		/* Hide the tip window */
		case DLTOOLTIP_TIMER_HIDE:
			GetCursorPos(&ptCursor);

			if (ptCursor != m_ptOrigin) {
				KillTimer(m_nTimer);
				ShowWindow(SW_HIDE);
				m_IsOpen = false;
			}

			break;
	}

	CWnd::OnTimer(nIDEvent);
}

/*===========================================================================
 *      End of Class Event CDlToolTip::OnTimer()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CDlToolTip Method - void Show (pszText, pPoint);
 *
 * Shows the tooltip at the given position in the parent window.
 *
 *=========================================================================*/
void CDlToolTip::Show(const TCHAR *pszText, CPoint *pPoint) {
	/* Determine where to show the tooltip */
	if (pPoint != NULL) {
		m_ptOrigin = *pPoint;
	} else {
		GetCursorPos(&m_ptOrigin);
	}

	m_szText = pszText;
	/* Start the show timer */
	m_nTimer = SetTimer(DLTOOLTIP_TIMER_SHOW, m_nShowDelay, NULL);
}

/*===========================================================================
 *      End of Class Method CDlToolTip::Show()
 *=========================================================================*/
