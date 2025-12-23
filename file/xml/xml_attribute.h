/*===========================================================================
 *
 * File:    Xmlattr.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  January 25, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __XMLATTR_H
#define __XMLATTR_H


#include "Common/Contain/PtrArray.h"
#include "Common/String/SString.h"
#include "Common/File/GenFile.h"


/* Read method result values */
#define XMLFILE_READ_OK         0
#define XMLFILE_READ_ERROR      1
#define XMLFILE_READ_ENDELEM    2
#define XMLFILE_READ_CLOSEELEM  3
#define XMLFILE_READ_VALUESTART 4

/* Used only when inputting attributes */
#define XMLATTR_MAX_NAMESIZE  255


/*===========================================================================
 *
 * Begin Class CXmlAttribute Definition
 *
 * Description
 *
 *=========================================================================*/
class CXmlAttribute {
  protected:
	CSString m_Name;
	CSString m_Value;


	/* Helper input methods */
	bool ReadName(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount);
	bool ReadValue(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount);


  public:
	/* Class Constructors/Destructors */
	CXmlAttribute();
	virtual ~CXmlAttribute() {
		Destroy();
	}

	virtual void Destroy();

	/* Get class members */
	const TCHAR *GetName() const {
		return m_Name;
	}

	const TCHAR *GetValue() const {
		return m_Value;
	}

	/* Compare name/value */
	bool IsName(const TCHAR *pName) {
		return m_Name.CompareNoCase(pName) == 0;
	}

	bool IsValue(const TCHAR *pValue) {
		return m_Value.CompareNoCase(pValue) == 0;
	}

	/* Set class members */
	void SetName(const TCHAR *pString) {
		m_Name = pString;
	}

	void SetValue(const TCHAR *pString) {
		m_Value = pString;
	}

	void SetValue(const long Value);

	/* Read the attribute from the file */
	bool Read(TCHAR *pBuffer, int &BufferPos, const int FileSize, long &LineCount);

	/* Output attribute to a file */
	bool Write(CGenFile &File);

};

/* Array of attribute pointers */
typedef TPtrArray<CXmlAttribute> CAttributeArray;


#endif
