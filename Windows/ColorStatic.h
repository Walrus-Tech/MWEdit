/*===========================================================================
 *
 * File:    Colorstatic1.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 16, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __COLORSTATIC_H
#define __COLORSTATIC_H



/*===========================================================================
 *
 * Begin Class CColorStatic Definition
 *
 *=========================================================================*/
class CColorStatic : public CStatic {

  public:
	COLORREF m_Color;
	int m_Red;
	int m_Green;
	int m_Blue;
	bool m_Modified;

	/* Construction */
	CColorStatic();
	virtual ~CColorStatic();

	/* Get class members */
	COLORREF GetColor(void) {
		return (m_Color);
	}

	bool IsModified(void) {
		return (m_Modified);
	}

	/* Set class members */
	void SetModified(const bool Flag) {
		m_Modified = Flag;
	}

	void SetColor(int Red, int Green, int Blue) {
		m_Red = Red;
		m_Green = Green;
		m_Blue = Blue;
		m_Color = RGB(m_Red, m_Green, m_Blue);
	}

	void SetColor(const long ColorRef) {
		m_Red = GetRValue(ColorRef);
		m_Green = GetGValue(ColorRef);
		m_Blue = GetBValue(ColorRef);
		m_Color = ColorRef;
	}

	/* ClassWizard generated virtual function overrides */
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

	/* Generated message map functions */
  protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();

};

/*===========================================================================
 *      End of Class CColorStatic Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *      End of File Colorstatic1.H
 *=========================================================================*/
