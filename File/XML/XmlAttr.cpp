/*===========================================================================
 *
 * File:    Xmlattr.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "xmlattr.h"


DEFINE_FILE("XmlAttr.cpp");


/*===========================================================================
 *
 * Class CXmlAttribute Constructor
 *
 *=========================================================================*/
CXmlAttribute::CXmlAttribute() {
	//DEFINE_FUNCTION("CXmlAttribute::CXmlAttribute()");
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - void Destroy (void);
 *
 *=========================================================================*/
void CXmlAttribute::Destroy() {
	//DEFINE_FUNCTION("CXmlAttribute::Destroy()");
	m_Name.Empty();
	m_Value.Empty();
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - bool Read (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the attribute from the current postion in the given file buffer.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CXmlAttribute::Read(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	bool Result;
	Result = ReadName(pBuffer, BufferPos, FileSize, LineCount);

	if (Result) {
		Result = ReadValue(pBuffer, BufferPos, FileSize, LineCount);
	}

	return Result;
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - bool ReadName (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the attribute name from the current postion in the given file buffer.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CXmlAttribute::ReadName(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount) {
	int StartPos = BufferPos;

	while (BufferPos < FileSize) {
		switch (pBuffer[BufferPos]) {
			case '\n':
				LineCount++; /* Fall through */

			case '\r':
			case '\t':
			case ' ': /* End of name */
			case '=':
				if (StartPos >= 0) {
					m_Name.Copy(pBuffer + StartPos, BufferPos - StartPos);
				}

				return true;

			case '>':
			case '/':
				return true;

			default: /* Add character to element name */
				BufferPos++;
				break;
		} /* End of switch */
	}

	return true;
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - bool ReadValue (pBuffer, BufferPos, FileSize, LineCount);
 *
 * Parses the attribute value from the current postion in the given file buffer.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CXmlAttribute::ReadValue(TCHAR *pBuffer,
                              int &BufferPos,
                              const int FileSize,
                              long &LineCount) {
	int StartPos = -1;
	TCHAR QuoteType = 0;
	bool FoundStart;

	while (BufferPos < FileSize) {
		switch (pBuffer[BufferPos]) {
			case '=':
				FoundStart = true;
				BufferPos++;
				break;

			case '\"':
			case '\'':
				if (QuoteType == pBuffer[BufferPos]) {
					m_Value.Copy(pBuffer + StartPos, BufferPos - StartPos);
					BufferPos++;
					return true;
				} else if (QuoteType == 0 && FoundStart) {
					QuoteType = pBuffer[BufferPos];
					StartPos = BufferPos + 1;
				}

				BufferPos++;
				break;

			case '>':
			case '/':
				if (QuoteType == 0) {
					return true;
				}

				BufferPos++;
				break;

			case '\n':
				LineCount++; /* Fall through */

			default:
				BufferPos++;
				break;
		} /* End of switch */
	}

	return true;
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - void SetValue (const long Value);
 *
 *=========================================================================*/
void CXmlAttribute::SetValue(const long Value) {
	TCHAR Buffer[48];
	ltoa(Value, Buffer, 10);
	SetValue(Buffer);
}


/*===========================================================================
 *
 * Class CXmlAttribute Method - bool Write (File);
 *
 * Description
 *
 *=========================================================================*/
bool CXmlAttribute::Write(CGenFile &File) {
	bool Result;
	Result = File.Printf(" %s=\"%s\"", m_Name, m_Value);
	return Result;
}
