/*===========================================================================
 *
 * File:    SString.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, May 08, 2001
 *
 * Contains the definition for the CSString class for handling simple
 * strings.
 *
 *=========================================================================*/
#ifndef __SSTRING_H
#define __SSTRING_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "dl_base.h"
#include "dl_mem.h"
#include "dl_str.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Number of extra bytes to allocate when creating strings */
#define SSTRING_ALLOC_EXTRA 32

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

class CSStringData {
  public:
	int Length;     /* Size of string in characters */
	int AllocLength;    /* Allocated size of string in characters */
	TCHAR *GetData() {
		return (TCHAR*)(this + 1);
	}
};

/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSString Definition
 *
 * A simple class for handling strings.
 *
 *=========================================================================*/
class CSString {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	TCHAR *m_pString;  /* The string data */


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Allocate string buffers of a given size */
	void AllocString (const int StringSize);
	void AllocCopy (const int StringSize);

	/* Create a string buffer from two source strings */
	void ConcatStrings (const int String1Size, const TCHAR* pString1,
	                    const int String2Size, const TCHAR* pString2);

	/* Free the current string data */
	void FreeData (void);

	/* Access the string data */
	CSStringData *GetData (void) const {
		IASSERT(m_pString != NULL);
		return (((CSStringData *)m_pString) - 1);
	}

	/* Initializes the string data */
	void Init (void);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors */
	CSString ();
	CSString (const TCHAR* pString);
	CSString (const TCHAR* pString, const int Length);
	CSString (const CSString& SrcString);
	CSString (const int StringSize);
	CSString (const TCHAR Char, const int Count);

	/* Class Destructors */
	~CSString();
	void Destroy (void);

	/* String comparison */
	int Compare (const TCHAR* pString) const;
	int CompareNoCase (const TCHAR* pString) const;

	/* Copy a number of characters from source strings */
	void Copy (const TCHAR* pString, const int Count);
	void Copy (const CSString& String, const int Count);

	/* Empties the string contents */
	void Empty (void);

	/* Search for sub-strings */
	int Find (const TCHAR* pSearch);
	int FindI (const TCHAR* pSearch);

	/* Frees any extra memory allocated for the string */
	void FreeExtra (void);

	/* Get the length, in bytes, of the string */
	int GetLength (void) const;
	int GetAllocLength (void) const;

	/* Checks for an empty (zero sized) string */
	bool IsEmpty (void);

	/* Extract sub-strings from string */
	CSString Left (const int Count) const;
	CSString Mid (const int Index, const int Count) const;
	CSString Mid (const int Index) const;
	CSString Right (const int Count) const;

	/* Makes the string lower/upper case */
	void MakeLower (void);
	void MakeUpper (void);

	/* Set a specific character in the string */
	void SetAt (const int Index, const TCHAR Char);

	/* Set the maximum string size */
	void SetSize (const int Size);

	/* Trims whitespace from left/right sides of string */
	CSString &TrimLeft (void);
	CSString &TrimRight (void);
	CSString &Trim (void);

	/* Truncate the string at the given index */
	void Truncate (const int Index);

	void UpdateLength (void);

	/* Overloaded copy operators */
	const CSString &operator= (const CSString& SrcString);
	const CSString &operator= (const TCHAR Char);
	const CSString &operator= (const TCHAR* pSrcString);

	/* String concatenation */
	const CSString &operator+= (const CSString& String);
	const CSString &operator+= (const TCHAR Char);
	const CSString &operator+= (const TCHAR* pString);
	const CSString &Append (const TCHAR* pString, const int Length);

	/* Addition operators, friend functions */
	friend CSString operator+ (const CSString& String1, const CSString& String2);
	friend CSString operator+ (const TCHAR Char, const CSString& String);
	friend CSString operator+ (const CSString& String, const TCHAR Char);
	friend CSString operator+ (const TCHAR* pString1, const CSString& String2);
	friend CSString operator+ (const CSString& String1, const TCHAR* pString2);

	/* Get a specific character from the string */
	TCHAR operator[] (const int Index) const;
	TCHAR GetAt (const int Index) const;

	/* Return a const pointer to the string buffer */
	operator const TCHAR* (void) const;

};

/*===========================================================================
 *      End of Class CSString Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Begin Inline CSString Methods
 *
 *=========================================================================*/


inline CSString &TerminatePathString (CSString& PathBuffer) {
	if (PathBuffer.GetLength() == 0) {
		return (PathBuffer);
	}

	if (PathBuffer.GetAt(PathBuffer.GetLength() - 1) != '\\') {
		PathBuffer += '\\';
	}

	return (PathBuffer);
}

/* String comparison, case sensitive, returns as per strcmp() */
inline int CSString::Compare (const TCHAR* pString) const {
	IASSERT(pString != NULL);
	return (strcmp(m_pString, pString));
}

/* String comparison, case insensitive, returns as per stricmp() */
inline int CSString::CompareNoCase (const TCHAR* pString) const {
	IASSERT(pString != NULL);
	return (_stricmp(m_pString, pString));
}

/* Creates a new string at most Count bytes in size */
inline void CSString::Copy (const TCHAR* pString, const int Count) {
	//int InputSize = SafeStrLen(pString);

	/* Check for special cases */
	if (Count <= 0) {
		Empty();
		return;
	}

	if (GetLength() < Count) {
		FreeData();
		AllocString(Count);
	}

	if (pString != NULL) {
		memcpy(m_pString, pString, Count * sizeof(TCHAR));
	}

	m_pString[Count] = NULL_CHAR;
	GetData()->Length = Count;
	//if (InputSize < Count) GetData()->Length = InputSize;
}

inline int CSString::Find (const TCHAR* pString) {
	if (pString == NULL || *pString == NULL_CHAR) {
		return (-1);
	}

	TCHAR* pFind = TSTRSTR(m_pString, pString);

	if (pFind == NULL) {
		return (-1);
	}

	return (pFind - m_pString);
}

inline int CSString::FindI (const TCHAR* pString) {
	if (pString == NULL || *pString == NULL_CHAR) {
		return (-1);
	}

	TCHAR* pFind = stristr(m_pString, pString);

	if (pFind == NULL) {
		return (-1);
	}

	return (pFind - m_pString);
}

/* Return the current string size */
inline int CSString::GetLength (void) const {
	return (GetData()->Length);
}

/* Get the current allocated size of string */
inline int CSString::GetAllocLength (void) const {
	return (GetData()->AllocLength);
}

/* Returns TRUE if the string is empty, "" */
inline bool CSString::IsEmpty (void) {
	return ((GetLength() == 0) ? TRUE : FALSE);
}

/* Returns a string containing the first Count characters from the
 * left of the string object */
inline CSString CSString::Left (const int Count) const {
	int NewCount = Count;

	if (NewCount > GetLength()) {
		NewCount = GetLength();
	}

	if (NewCount < 0) {
		NewCount = 0;
	}

	CSString NewString(m_pString, NewCount);
	return NewString;
}

/* Makes the string all lower/upper case */
inline void CSString::MakeLower (void) {
	_strlwr(m_pString);
}

inline void CSString::MakeUpper (void) {
	_strupr(m_pString);
}

/* Returns a new string starting at the 0-based index of the current string */
inline CSString CSString::Mid (const int Index) const {
	int NewIndex = Index;

	if (NewIndex > GetLength()) {
		NewIndex = GetLength();
	}

	if (NewIndex < 0) {
		NewIndex = 0;
	}

	CSString NewString(m_pString + NewIndex);
	return NewString;
}

/* Returns a new string starting at the 0-based index of the current string
 * with the given length. */
inline CSString CSString::Mid (const int Index, const int Length) const {
	int NewIndex = Index;
	int NewLength;

	if (NewIndex > GetLength()) {
		NewIndex = GetLength();
	}

	if (NewIndex < 0) {
		NewIndex = 0;
	}

	if (NewLength < 0) {
		NewLength = 0;
	}

	if (NewLength + NewIndex > GetLength()) {
		NewLength = GetLength() - NewIndex;
	}

	CSString NewString(m_pString + NewIndex, NewLength);
	return NewString;
}

/* Returns a string containing the first Count characters from the
 * right side of the string object */
inline CSString CSString::Right (const int Count) const {
	int NewCount = Count;

	if (NewCount > GetLength()) {
		NewCount = GetLength();
	}

	if (NewCount < 0) {
		NewCount = 0;
	}

	CSString NewString(m_pString + GetLength() - NewCount, NewCount);
	return NewString;
}

inline void CSString::SetSize (const int Size) {
	AllocCopy(Size);
}

/* Trim whitespace from right and left sides of string */
inline CSString &CSString::Trim (void) {
	TrimLeft();
	TrimRight();
	return (*this);
}

/* Access the (const TCHAR*) string */
inline CSString::operator const TCHAR* (void) const {
	return (m_pString);
}

/* Get the specified character from the string.  ASSERTs if given an
   invalid index (0 returns the first character in string). */
inline TCHAR CSString::operator[] (const int Index) const {
	return GetAt(Index);
}

/* Same as operator[], return a specific character in string */
inline TCHAR CSString::GetAt (const int Index) const {
	IASSERT(Index < GetLength() && Index >= 0);
	return (m_pString[Index]);
}

/* Sets a specific character in the string.  ASSERTs if an invalid
 * index is given.  0 is the first character in string. */
inline void CSString::SetAt (const int Index, const TCHAR TCHAR) {
	IASSERT(Index < GetLength() && Index >= 0);
	m_pString[Index] = TCHAR;
}

/* Truncate the string at the given index */
inline void CSString::Truncate (const int Index) {
	if (Index < 0 || Index >= GetLength()) {
		return;
	}

	m_pString[Index] = NULL_CHAR;
	GetData()->Length = Index;
}


inline void CSString::UpdateLength (void) {
	int Index = GetLength() - 1;

	while (Index > 0) {
		if (m_pString[Index] != NULL_CHAR) {
			GetData()->GetData()[Index + 1] = NULL_CHAR;
			GetData()->Length = Index + 1;
			return;
		}

		Index--;
	}
}

/* String comparisons */
inline bool operator== (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) == 0);
}

inline bool operator== (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) == 0);
}

inline bool operator== (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) == 0);
}

inline bool operator!= (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) != 0);
}

inline bool operator!= (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) != 0);
}

inline bool operator!= (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) != 0);
}

inline bool operator<= (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) <= 0);
}

inline bool operator<= (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) >= 0);
}

inline bool operator<= (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) <= 0);
}

inline bool operator>= (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) >= 0);
}

inline bool operator>= (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) <= 0);
}

inline bool operator>= (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) >= 0);
}

inline bool operator< (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) < 0);
}

inline bool operator< (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) > 0);
}

inline bool operator< (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) < 0);
}

inline bool operator> (const CSString& String1, const CSString& String2) {
	return (String1.Compare(String2) > 0);
}

inline bool operator> (const TCHAR* String1, const CSString& String2) {
	return (String2.Compare(String1) < 0);
}

inline bool operator> (const CSString& String1, const TCHAR* String2) {
	return (String1.Compare(String2) > 0);
}



/*===========================================================================
 *      End of Begin Inline CSString Methods
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Sstring.H
 *=========================================================================*/
