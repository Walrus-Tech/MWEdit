/*===========================================================================
 *
 * File:    Xmlelem.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __XMLELEM_H
#define __XMLELEM_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "XmlAttr.h"
#include "PtrArray.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Initial array sizes */
#define XMLFILE_DEFAULT_ELEMENTS  16
#define XMLFILE_DEFAULT_ATTRIBUTES    4

/* Used only when inputting elements */
#define XMLELEM_MAX_NAMESIZE 255

/* Element callback event codes */
#define XMLELEM_CBCODE_ELEMSTART 1

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/* Array of XML element pointers */
class CXmlElement;
typedef TPtrArray<CXmlElement> CElementArray;

/* Type used for the load/write callback */
typedef struct {
	int EventCode;
	long LineCount;
	long FileSize;
	long BytesParsed;
	float PercentDone;
	const TCHAR *pCurrentElem;
	const TCHAR *pMessage;
	void *pUserData;
} xmlcallbackinfo_t;

/* Load/write callback function */
typedef int (*XMLFILE_CALLBACK) (xmlcallbackinfo_t* pCallbackInfo);

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CXmlElement Definition
 *
 * Description
 *
 *=========================================================================*/
class CXmlElement {

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CXmlElement *m_pParent;  /* Parent element */

	static bool m_OutputCR; /* Output a CR at ends of elements, etc... */

	CSString m_Name;     /* Element name */
	bool m_IsEmpty;  /* Element is empty */
	bool m_IsRoot;   /* Is special root element */
	int m_Level;    /* Use for 'tabbing' output files */

	long m_StartLine;    /* Start/end line of element */
	long m_EndLine;

	CSString m_Content;  /* Element content, if any */
	CElementArray m_Elements; /* Array of child elements */
	CAttributeArray m_Attributes;   /* Array of attributes */

	/* Static callback information for load/save */
	static XMLFILE_CALLBACK m_CallBackFunc;
	static xmlcallbackinfo_t m_CallBackInfo;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper input routines */
	bool ReadAttribute (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);
	bool ReadChild (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);
	bool ReadEnd (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);
	bool ReadName (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);
	bool ReadOpen (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);

	/* Output helpers */
	bool WriteAttributes (CGenFile& File);
	bool WriteChildren (CGenFile& File);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CXmlElement();
	virtual ~CXmlElement() {
		Destroy();
	}

	virtual void Destroy (void);

	/* Add attributes and child elements */
	CXmlElement *AddChildHead (const TCHAR* pName, const bool IsEmpty = false);
	CXmlElement *AddChild (const TCHAR* pName, const bool IsEmpty = false);
	CXmlAttribute *AddAttribute (const TCHAR* pName, const TCHAR* pValue);
	CXmlAttribute *AddAttribute (const TCHAR* pName, const long lValue);
	CXmlAttribute *AddAttribute (const TCHAR* pName, const int iValue);
	CXmlAttribute *AddAttribute (const TCHAR* pName, const float fValue);
	CXmlAttribute *AddAttribute (const TCHAR* pName, const bool bValue);

	/* Attempt to find a child element with the given name */
	CXmlAttribute *FindAttribute (const TCHAR* pName);
	CXmlElement *FindChild (const TCHAR* pName);
	CXmlElement *FindFirstChild (const TCHAR* pName, int &ElemIndex) {
		ElemIndex = -1;
		return FindNextChild(pName, ElemIndex);
	}

	CXmlElement *FindNextChild (const TCHAR* pName, int &ElemIndex);

	/* Find a child element with the given attribute name and value */
	CXmlElement *FindChild (const TCHAR* pName, const TCHAR* pAttribute, const TCHAR* pValue);

	/* Get class members */
	CXmlElement *GetParent (void) {
		return (m_pParent);
	}

	const TCHAR *GetName (void) const {
		return (m_Name);
	}

	const TCHAR *GetContent(void) const {
		return (m_Content);
	}

	bool IsEmpty (void) const {
		return (m_IsEmpty);
	}

	bool IsRoot (void) const {
		return (m_IsRoot);
	}

	int GetLevel (void) const {
		return (m_Level);
	}

	CSString &GetContentString (void) {
		return (m_Content);
	}

	int GetContentSize (void) const {
		return (m_Content.GetLength());
	}

	/* Compare element strings */
	bool IsName (const TCHAR* pName) {
		return m_Name.CompareNoCase(pName) == 0;
	}

	/* Access the child elements */
	int GetNumChildren (void) const {
		return (m_Elements.GetSize());
	}

	CXmlElement *GetChild (const int Index) {
		return (m_Elements.GetAt(Index));
	}

	/* Access the element attributes */
	int GetNumAttributes (void) const {
		return (m_Attributes.GetSize());
	}

	CXmlAttribute *GetAttribute (const int Index) {
		return (m_Attributes.GetAt(Index));
	}

	/* Initialize the default root element */
	void InitRoot (void);

	/* Inputs element from the given file */
	bool Read (TCHAR* pBuffer, int &BufferPos, const int FileSize, long &LineCount);

	/* Set class members */
	void SetParent (CXmlElement* pParent) {
		m_pParent = pParent;
	}

	void SetName (const TCHAR* pString) {
		m_Name = pString;
	}

	void SetIsEmpty (const bool Flag) {
		m_IsEmpty = Flag;
	}

	void SetIsRoot (const bool Flag) {
		m_IsRoot = Flag;
	}

	void SetLevel (const int Level) {
		m_Level = Level;
	}

	void SetContent (const TCHAR* pString) {
		m_Content = pString;
	}

	void SetContentLength (const int Length) {
		m_Content.SetSize(Length);
	}

	/* Set the callback function and data */
	static void SetCallback (XMLFILE_CALLBACK pCallBack, void* pUserData) {
		m_CallBackFunc = pCallBack;
		m_CallBackInfo.pUserData = pUserData;
	}

	/* Output element to the file */
	bool Write (CGenFile& File);

};

/*===========================================================================
 *      End of Class CXmlElement Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *      End of File Xmlelem.H
 *=========================================================================*/
