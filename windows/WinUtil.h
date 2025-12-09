/*===========================================================================
 *
 * File:    Winutil.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, May 08, 2002
 *
 * Description
 *
 *=========================================================================*/
#ifndef __WINUTIL_H
#define __WINUTIL_H

#include <afxcmn.h>

#include "Common/dl_err.h"


/* Options for the MakeTimeString() function, bit field values */
#define TIMESTRING_SHORTTIME 1
#define TIMESTRING_LONGTIME  2
#define TIMESTRING_SHORTDATE 4
#define TIMESTRING_LONGDATE  8

/* Shortcut to access the selected list item data */
#define GETLISTDATA(List, Var) if (List.GetCurSel() >= 0) Var = List.GetItemData(List.GetCurSel());

/* Shortcuts to font creation */
#define CFONT_CREATE(Font, Size, Bold, Italic, FontName) Font.CreateFont(Size, 0, 0, 0, Bold, Italic, 0, 0, \
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FontName);


/* Adds a string data value pair to a combo or list box */
bool AddComboString(CComboBox &ComboBox, const TCHAR *pString, const int Data);
bool AddListString(CListBox &ListBox, const TCHAR *pString, const int Data);

/* Display a browse folder dialog */
bool BrowseForFolder(TCHAR *pPath, HWND hWnd, const TCHAR *pTitle);
bool BrowseForFolder(CString &Path, HWND hWnd, const TCHAR *pTitle);

/* Clipboard functions */
bool CopyTextToClipboard(const TCHAR *pString, const int Length);

/* Creates a new shortcut */
bool CreateShortcut(LPTSTR lpszPathObj,
                    LPTSTR pWorkingPath,
                    LPTSTR pArgs,
                    LPTSTR pIconPath,
                    LPTSTR lpszPathLink,
                    LPTSTR lpszDesc);

/* Find a tree control item */
HTREEITEM FindTreeItem(const char *pName, CTreeCtrl &TreeCtrl, HTREEITEM Root);

/* Find a window based on its instance handle */
HWND FindWindowHandle(HINSTANCE hInstance);

/* Get the item data from the currently selected list item, if any */
bool GetCurSelListItemData(long &Data, CListBox &ListBox);
bool GetCurSelComboItemData(long &Data, CComboBox &ComboBox);

/* Attempt to open a web page */
HINSTANCE OpenWebPage(const TCHAR *pSiteAddress);

/* Execute a simple DOS command */
int RunDOSCommand(const TCHAR *pFilename);

/* String conversion functions */
bool StringToInteger(const TCHAR *pString, int &DestValue);
bool StringToFloat(const TCHAR *pString, float &DestValue);
bool StringToBool(const TCHAR *pString, bool &DestValue);

/* Trim whitespace from a string object */
inline CString &TrimStringSpace(CString &String) {
	String.TrimRight(_T(" \n\r\t"));
	String.TrimLeft(_T(" \n\r\t"));
	return String;
}

/* Find an item in a combobox/listbox based on its item data */
int FindComboListItem(CComboBox &ComboBox, const DWORD ItemData, const bool Select = false);
int FindListItem(CListBox &ListBox, const DWORD ItemData, const bool Select = false);

/* Get the currently active view/document */

/* Clipboard functions */
bool ClipCopyFromWnd(CWnd *pWnd);
bool ClipCutFromWnd(CWnd *pWnd);
bool ClipPasteToWnd(CWnd *pWnd);

/* CString clipboard versions */
inline bool CopyTextToClipboard(CString &String) {
	return CopyTextToClipboard(String, String.GetLength());
}

bool GetClipboardText(CString &Buffer);

CDocument *GetActiveDocument();
CView *GetActiveView();
CDocument *GetActiveFrameDocument(CFrameWnd *pFrame);
CView *GetActiveFrameView(CFrameWnd *pFrame);

/* Attempt to find a currently open view */
CView *GetView(const CRuntimeClass *pRunTimeClass);

/* Create a time/date string */
void MakeTimeString(CString &Buffer, const int Options);

/* Path functions for string objects */
CString &ExtractPath(CString &PathBuffer, const TCHAR *pPath);
CString &TerminatePathString(CString &PathBuffer);

/* Parse a word from a character buffer */
bool GetStringWord(CString &OutputString, const TCHAR *pBuffer, int &StartPos);

/* Open a context menu */
bool OpenContextMenu(CWnd *pParent, CWnd *pWnd, CPoint Point, const DWORD MenuResource);


/* Set the internal window text directly */
void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText);


#endif
