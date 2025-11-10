/*===========================================================================
 *
 * File:    Xmlelem.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "File/XML/XmlElem.h"
#include <ctype.h>


DEFINE_FILE("XmlElem.cpp");

/* Class static members */
XMLFILE_CALLBACK CXmlElement::m_CallBackFunc = NULL;
xmlcallbackinfo_t CXmlElement::m_CallBackInfo = {
	0,
	0,
	0,
	0,
	0.0f,
	NULL,
	NULL,
	NULL
};
bool CXmlElement::m_OutputCR = true;


/*===========================================================================
 *
 * Class CXmlElement Constructor
 *
 *=========================================================================*/
CXmlElement::CXmlElement() : m_Elements(XMLFILE_DEFAULT_ELEMENTS),
	m_Attributes(XMLFILE_DEFAULT_ATTRIBUTES) {
	//DEFINE_FUNCTION("CXmlElement::CXmlElement()");
	m_pParent = NULL;
	m_IsEmpty = false;
	m_IsRoot = false;
	m_StartLine = 0;
	m_EndLine = 0;
	m_Level = 0;
}


/*===========================================================================
 *
 * Class CXmlElement Method - void Destroy (void);
 *
 *=========================================================================*/
void CXmlElement::Destroy() {
	//DEFINE_FUNCTION("CXmlElement::Destroy()");
	CXmlElement *pElement;
	CXmlAttribute *pAttribute;
	int Index;

	/* Delete all child elements */
	for (Index = 0; Index < m_Elements.GetSize(); Index++) {
		pElement = m_Elements.GetAt(Index);
		DestroyPointer(pElement);
	}

	/* Delete all attributes */
	for (Index = 0; Index < m_Attributes.GetSize(); Index++) {
		pAttribute = m_Attributes.GetAt(Index);
		DestroyPointer(pAttribute);
	}

	m_Name.Empty();
	m_Content.Empty();
	m_Elements.RemoveAll();
	m_Attributes.RemoveAll();
	m_StartLine = 0;
	m_EndLine = 0;
	m_Level = 0;
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlAttribute* AddAttribute (pName, pValue);
 *
 * Adds an attribute to the element. Returns the attribute on success.
 *
 *=========================================================================*/
CXmlAttribute *CXmlElement::AddAttribute(const TCHAR *pName, const TCHAR *pValue) {
	DEFINE_FUNCTION("CXmlElement::AddAttribute()");
	CXmlAttribute *pNewAttribute;
	CreatePointer(pNewAttribute, CXmlAttribute);
	pNewAttribute->SetName(pName);
	pNewAttribute->SetValue(pValue);
	m_Attributes.Add(pNewAttribute);
	return pNewAttribute;
}


CXmlAttribute *CXmlElement::AddAttribute(const TCHAR *pName, const long lValue) {
	TCHAR Buffer[32];
	snprintf(Buffer, 31, _T("%ld"), lValue);
	return AddAttribute(pName, Buffer);
}

CXmlAttribute *CXmlElement::AddAttribute(const TCHAR *pName, const int lValue) {
	TCHAR Buffer[32];
	snprintf(Buffer, 31, _T("%d"), lValue);
	return AddAttribute(pName, Buffer);
}

CXmlAttribute *CXmlElement::AddAttribute(const TCHAR *pName, const float fValue) {
	TCHAR Buffer[64];
	snprintf(Buffer, 63, _T("%f"), fValue);
	return AddAttribute(pName, Buffer);
}


CXmlAttribute *CXmlElement::AddAttribute(const TCHAR *pName, const bool bValue) {
	return AddAttribute(pName, BooleanToString(bValue));
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlElement* AddChild (pName, IsEmpty);
 *
 * Adds a child element to the element.  Returns the element on success.
 *
 *=========================================================================*/
CXmlElement *CXmlElement::AddChild(const TCHAR *pName, const bool IsEmpty) {
	DEFINE_FUNCTION("CXmlElement::AddChild()");
	CXmlElement *pNewElement;
	CreatePointer(pNewElement, CXmlElement);
	pNewElement->SetName(pName);
	pNewElement->SetIsEmpty(IsEmpty);
	pNewElement->SetParent(this);
	m_Elements.Add(pNewElement);
	return pNewElement;
}

CXmlElement *CXmlElement::AddChildHead(const TCHAR *pName, const bool IsEmpty) {
	DEFINE_FUNCTION("CXmlElement::AddChildHead()");
	CXmlElement *pNewElement;
	CreatePointer(pNewElement, CXmlElement);
	pNewElement->SetName(pName);
	pNewElement->SetIsEmpty(IsEmpty);
	pNewElement->SetParent(this);
	m_Elements.AddHead(pNewElement);
	return pNewElement;
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlAttribute* FindAttribute (pName);
 *
 * Finds the attribute of the element with the given name.  Returns NULL
 * if it is not found.
 *
 *=========================================================================*/
CXmlAttribute *CXmlElement::FindAttribute(const TCHAR *pName) {
	CXmlAttribute *pAttribute;
	int Index;

	for (Index = 0; Index < m_Attributes.GetSize(); Index++) {
		pAttribute = m_Attributes.GetAt(Index);

		if (pAttribute->IsName(pName)) {
			return pAttribute;
		}
	}

	/* Child element not found */
	ErrorHandler.AddError(ERR_BADINPUT,
	                      _T("%05ld: Element '%s' does not have an attribute '%s'!"),
	                      m_StartLine + 1,
	                      m_Name, pName);
	return NULL;
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlElement* FindChild (pName);
 *
 * Finds and returns the child element that has the given name (not case
 * sensitive). Returns NULL if it was not found.
 *
 *=========================================================================*/
CXmlElement *CXmlElement::FindChild(const TCHAR *pName) {
	int Index;

	for (Index = 0; Index < m_Elements.GetSize(); Index++) {
		if (m_Elements.GetAt(Index)->IsName(pName)) {
			return m_Elements.GetAt(Index);
		}
	}

	/* Child element not found */
	ErrorHandler.AddError(ERR_BADINPUT,
	                      _T("%05ld: Element '%s' does not have a child element '%s'!"),
	                      m_StartLine + 1,
	                      m_Name, pName);
	return NULL;
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlElement* FindChild (pName, pAttrName, pValue);
 *
 * An extended find method that looks for the given element with the supplied
 * attribute name/value pair.  Returns NULL if it is not found.
 *
 *=========================================================================*/
CXmlElement *CXmlElement::FindChild(const TCHAR *pName,
                                    const TCHAR *pAttrName,
                                    const TCHAR *pValue) {
	CXmlElement *pElement;
	CXmlAttribute *pAttribute;
	int ElemIndex;
	/* Search for all matching child elements */
	pElement = FindFirstChild(pName, ElemIndex);

	while (pElement != NULL) {
		pAttribute = pElement->FindAttribute(pAttrName);

		if (pAttribute != NULL) {
			if (pAttribute->IsValue(pValue)) {
				return pElement;
			}
		}

		pElement = FindNextChild(pName, ElemIndex);
	}

	/* Not found */
	return NULL;
}


/*===========================================================================
 *
 * Class CXmlElement Method - CXmlElement* FindNextChild (pName, ElemIndex);
 *
 * Finds the first child element after the given index with the given
 * name.  Returns NULL if the element is not found.  Updates the ElemIndex
 * to the found element.
 *
 *=========================================================================*/
CXmlElement *CXmlElement::FindNextChild(const TCHAR *pName, int &ElemIndex) {
	CXmlElement *pElement;

	for (ElemIndex++; ElemIndex < m_Elements.GetSize(); ElemIndex++) {
		pElement = m_Elements.GetAt(ElemIndex);

		if (pElement->IsName(pName)) {
			return pElement;
		}
	}

	/* Child element not found */
	return NULL;
}


/*===========================================================================
 *
 * Class CXmlElement Method - void InitRoot (void);
 *
 * Initializes the default root element.
 *
 *=========================================================================*/
void CXmlElement::InitRoot() {
	SetName(_T("?xml"));
	AddAttribute(_T("version"), _T("1.0"));
	AddAttribute(_T("encoding"), _T("UTF-8"));
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool Read (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the element, attributes, and any child elements from the current
 * position in the given buffer.  Returns false on any error.
 *
 *=========================================================================*/
bool CXmlElement::Read(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	bool FoundName = false;
	bool Result;
	TCHAR *pContentStart = NULL;
	int ContentPos;
	int CallBackResult;
	/* Attempt to read the open tag and attributes */
	Result = ReadOpen(pBuffer, BufferPos, FileSize, LineCount);

	if (!Result) {
		return false;
	}

	if (m_IsEmpty) {
		return true;
	}

	m_Content.Empty();

	/* Update the callback function, if any */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.BytesParsed = BufferPos;
		m_CallBackInfo.FileSize = FileSize;
		m_CallBackInfo.LineCount = LineCount;
		m_CallBackInfo.pMessage = NULL;
		m_CallBackInfo.pCurrentElem = GetName();
		m_CallBackInfo.PercentDone = 50.0f
		                             + (float)((FileSize - BufferPos)
		                             * 50.0
		                             / (float)BufferPos);
		m_CallBackInfo.EventCode = XMLELEM_CBCODE_ELEMSTART;
		CallBackResult = m_CallBackFunc(&m_CallBackInfo);

		if (CallBackResult < 0) {
			return false;
		}
	}

	/* Read any content, child elements and end tag */
	while (BufferPos < FileSize) {
		switch (pBuffer[BufferPos]) {
			case '<':
				if (pBuffer[BufferPos + 1] == '/') {
					/* Save the content, if any */
					if (pContentStart != NULL) {
						m_Content.Copy(pContentStart, BufferPos - ContentPos);
						m_Content.Trim();
					}

					BufferPos++;
					Result = ReadEnd(pBuffer, BufferPos, FileSize, LineCount);
					return (Result);
				} else {
					Result = ReadChild(pBuffer, BufferPos, FileSize, LineCount);

					if (!Result) {
						return false;
					}

					pContentStart = NULL;
				}

				break;

			case '\n':
				LineCount++; /* Fall through */

			case '\r':
				BufferPos++;
				break;

			default:
				if (pContentStart == NULL) {
					ContentPos = BufferPos;
					pContentStart = pBuffer + BufferPos;
				}

				BufferPos++;
				break;
		}
	}

	/* Unexpected end of file unless we are in the root */
	if (IsRoot()) {
		return true;
	}

	ErrorHandler.AddError(ERR_READFILE,
	                      _T("%05ld: End of file reached in element %s!"),
	                      m_StartLine + 1,
	                      GetName());
	return false;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool ReadAttribute (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Input one element attribute starting at the current position in the
 * file buffer.  Returns false on any error.
 *
 *=========================================================================*/
bool CXmlElement::ReadAttribute(TCHAR *pBuffer,
                                int &BufferPos,
                                const int FileSize,
                                long &LineCount) {
	DEFINE_FUNCTION("CXmlElement::ReadAttribute()");
	CXmlAttribute *pAttribute;
	CreatePointer(pAttribute, CXmlAttribute);
	m_Attributes.Add(pAttribute);
	return pAttribute->Read(pBuffer, BufferPos, FileSize, LineCount);
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool ReadChild (pBuffer, BufferPos, FileSize);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlElement::ReadChild(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	DEFINE_FUNCTION("CXmlElement::ReadChild()");
	CXmlElement *pElement;
	bool Result;
	CreatePointer(pElement, CXmlElement);
	pElement->SetParent(this);
	m_Elements.Add(pElement);
	pElement->SetLevel(m_Level + 1);
	Result = pElement->Read(pBuffer, BufferPos, FileSize, LineCount);
	return Result;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool ReadEnd (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlElement::ReadEnd(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	bool FoundStart = false;

	while (BufferPos < FileSize) {
		switch (pBuffer[BufferPos]) {
			case '/':
				FoundStart = true;
				BufferPos++;
				break;

			case '>':
				BufferPos++;
				m_EndLine = LineCount;
				return true;

			case '\n':
				LineCount++; /* Fall through */

			default:
				BufferPos++;
				break;
		}
	}

	return true;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool ReadName (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the XML element name from the current position in the file buffer.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CXmlElement::ReadName(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	TCHAR *pParse = pBuffer + BufferPos;
	TCHAR *pStartPos = NULL;
	int StartPos = -1;

	while (BufferPos < FileSize) {
		switch (*pParse) {
			case '\n':
				LineCount++; /* Fall through */

			case '>':
			case '/': /* End of element */
			case ' ': /* End of element name */
			case '\t':
			case '\r':
				if (pStartPos != NULL) {
					m_Name.Copy(pStartPos, BufferPos - StartPos);
				}

				m_StartLine = LineCount;
				return true;

			default:
				if (pStartPos == NULL) {
					pStartPos = pParse;
					StartPos = BufferPos;
				}

				pParse++;
				BufferPos++;
				break;
		}
	}

	m_StartLine = LineCount;
	return true;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool ReadOpen (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the open element and its attributes.  Returns false on any error.
 *
 *  <Element [attr1="aaa" attrib2="bbb" ....] [/]>
 *
 *=========================================================================*/
bool CXmlElement::ReadOpen(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	bool FoundName = false;
	bool Result;
	m_IsEmpty = false;

	/* Don't exceed file buffer size */
	while (BufferPos < FileSize) {
		switch (pBuffer[BufferPos]) {
			case '<':
				BufferPos++;
				Result = ReadName(pBuffer, BufferPos, FileSize, LineCount);

				if (!Result) {
					return false;
				}

				FoundName = true;
				break;

			case '/':
				BufferPos++;

				if (pBuffer[BufferPos] != '>') {
					ErrorHandler.AddError(ERR_READFILE,
					                      _T("%05ld: Invalid character sequence '/%c' found in element!"),
					                      m_StartLine + 1,
					                      pBuffer[BufferPos]);
					return false;
				}

				BufferPos++;
				m_IsEmpty = true;
				return true;

			case '>':
				BufferPos++;
				return true;

			case '\n':
				LineCount++; /* Fall through */

			case ' ':
			case '\t':
			case '\r':
				BufferPos++;
				break;

			default:

				/* Input element attribute */
				if (FoundName) {
					Result = ReadAttribute(pBuffer, BufferPos, FileSize, LineCount);

					if (!Result) {
						return false;
					}
				} else {
					BufferPos++;
				}

				break;
		}
	}

	/* Unexpected end of file */
	ErrorHandler.AddError(ERR_READFILE,
	                      _T("%05ld: End of file reached in element!"),
	                      m_StartLine + 1);
	return false;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool Write ( File);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlElement::Write(CGenFile &File) {
	bool Result;
	int CallBackResult;
	int Index;

	/* Update the callback function, if any */
	if (m_CallBackFunc != NULL) {
		m_CallBackInfo.BytesParsed = -1;
		m_CallBackInfo.FileSize = File.Tell();
		m_CallBackInfo.LineCount = -1;
		m_CallBackInfo.pMessage = NULL;
		m_CallBackInfo.pCurrentElem = GetName();
		m_CallBackInfo.PercentDone = -1;
		m_CallBackInfo.EventCode = XMLELEM_CBCODE_ELEMSTART;
		CallBackResult = m_CallBackFunc(&m_CallBackInfo);

		if (CallBackResult < 0) {
			return false;
		}
	}

	/* Output the element */
	for (Index = 0; Index < m_Level; Index++) {
		File.Printf(_T("\t"));
	}

	Result = File.Printf("<%s", m_Name);
	Result &= WriteAttributes(File);

	if (m_IsEmpty) {
		Result &= File.Printf("/>%c", m_OutputCR ? '\n' : ' ');
	} else {
		if (m_IsRoot) {
			Result &= File.Printf("?");
		}

		Result &= File.Printf(">%c", m_OutputCR ? '\n' : ' ');

		if (!m_Content.IsEmpty()) {
			Result &= File.Printf("%s%c", m_Content, m_OutputCR ? ' ' : ' ');
		}

		Result &= WriteChildren(File);

		if (!m_IsRoot) {
			for (Index = 0; Index < m_Level; Index++) {
				Result &= File.Printf(_T("\t"));
			}

			Result &= File.Printf("</%s>%c", m_Name, m_OutputCR ? '\n' : ' ');
		}
	}

	return Result;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool WriteAttributes (File);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlElement::WriteAttributes(CGenFile &File) {
	bool Result = true;
	int Index;

	for (Index = 0; Index < m_Attributes.GetSize(); Index++) {
		Result &= m_Attributes.GetAt(Index)->Write(File);
	}

	return Result;
}


/*===========================================================================
 *
 * Class CXmlElement Method - bool WriteChildren (File);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlElement::WriteChildren(CGenFile &File) {
	bool Result = true;
	int Index;

	for (Index = 0; Index < m_Elements.GetSize(); Index++) {
		Result &= m_Elements.GetAt(Index)->Write(File);
	}

	return Result;
}
