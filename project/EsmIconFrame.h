/*===========================================================================
 *
 * File:    Esmiconframe.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, February 13, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMICONFRAME_H
#define __ESMICONFRAME_H


#include "Common/dl_err.h"


/* Default icon width/height */

#define MWESM_ICON_DEFAULTWIDTH  32
#define MWESM_ICON_DEFAULTHEIGHT 32


/*===========================================================================
 *
 * Begin Class CEsmIcon Frame Definition
 *
 *=========================================================================*/
class CEsmIconFrame : public CStatic {
  protected:
	CBitmap m_Bitmap; /* The bitmap image to draw */
	bool m_IsInitialized;


  public:
	/* Construction/Destruction */
	CEsmIconFrame();
	virtual ~CEsmIconFrame();

	/* Called after the frame window is created */
	void OnInitialUpdate();

	/* Set class members */
	void SetIconBitmap(CBitmap *pBitmap);
	void SetEsmIcon(const TCHAR *pFilename, const bool RelativePath = true);

	/* ClassWizard generated virtual function overrides */

	//{{AFX_VIRTUAL(CEsmIconFrame)
	//}}AFX_VIRTUAL

	/* Generated message map functions */

  protected:
	//{{AFX_MSG(CEsmIconFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
