/*===========================================================================
 *
 * File:    Xmlfile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __XMLFILE_H
#define __XMLFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "XmlElem.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Callback event codes */
#define XMLFILE_CBCODE_READSTART  101
#define XMLFILE_CBCODE_READDONE   102
#define XMLFILE_CBCODE_READING    103
#define XMLFILE_CBCODE_PARSEDONE  110
#define XMLFILE_CBCODE_WRITESTART 121
#define XMLFILE_CBCODE_WRITEDONE  122
#define XMLFILE_CBCODE_WRITING    123

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CXmlFile Definition
 *
 * Description
 *
 *=========================================================================*/
class CXmlFile {

	/*---------- Begin Private Class Members ----------------------*/
  protected:
	CSString m_Filename;
	CGenFile m_File;
	CXmlElement m_RootElement;
	long m_LineCount;

	/* Callback information for load/save */
	XMLFILE_CALLBACK m_CallBackFunc;
	xmlcallbackinfo_t m_CallBackInfo;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CXmlFile();
	virtual ~CXmlFile() {
		Destroy();
	}

	virtual void Destroy(void);

	/* Get class members */
	CXmlElement *GetRootElement(void) {
		return (&m_RootElement);
	}

	const TCHAR *GetFilename(void) const {
		return (m_Filename);
	}

	long GetLineCount(void) const {
		return (m_LineCount);
	}

	/* Set the callback function and data */
	void SetCallback(XMLFILE_CALLBACK pCallBack, void *pUserData) {
		m_CallBackFunc = pCallBack;
		m_CallBackInfo.pUserData = pUserData;
	}

	/* Input an XML file */
	bool Read(const TCHAR *pFilename);

	/* Used during the callback of the read event */
	int OnReadCallback(const long FileSize, const long BytesRead);

	/* Output an XML file */
	bool Write(const TCHAR *pFilename);

};

/*===========================================================================
 *      End of Class CXmlFile Definition
 *=========================================================================*/

#endif
/*===========================================================================
 *      End of File Xmlfile.H
 *=========================================================================*/
