/*===========================================================================
 *
 * File:    Winutil.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, May 08, 2002
 *
 * Various windows related utility functions.
 *
 * 17 September 2003
 *  - Addition of the GetCurSelListItemData() and GetCurSelComboItemData()
 *    functions.
 *
 * 24 September 2003
 *  - Added the OpenWebPage() function.
 *
 * 5 October 2003
 *  - Added the FindWindowHandle() function.
 *
 * 1 December 2003
 *  - Re-added the CopyTextToClipboard() and GetClipboardText() functions.
 *
 *=========================================================================*/
#include "project/StdAfx.h"
#include "Windows/WinUtil.h"
#include "Common/dl_file.h"
#include "process.h"


DEFINE_FILE("WinUtil.cpp");


/*===========================================================================
 *
 * Function - bool AddComboString (ComboBox, pString, Data);
 *
 * Adds a string/data value pair to the given combo list. Returns false
 * on any error.
 *
 *=========================================================================*/
bool AddComboString(CComboBox &ComboBox, const TCHAR *pString, const int Data) {
	int ListIndex;
	ListIndex = ComboBox.AddString(pString);

	if (ListIndex >= 0) {
		ComboBox.SetItemData(ListIndex, Data);
	} else {
		return false;
	}

	return true;
}


/*===========================================================================
 *
 * Function - bool AddListString (ListBox, pString, Data);
 *
 * Adds a string/data value pair to the given listbox. Returns false
 * on any error.
 *
 *=========================================================================*/
bool AddListString(CListBox &ListBox, const TCHAR *pString, const int Data) {
	int ListIndex;
	ListIndex = ListBox.AddString(pString);

	if (ListIndex >= 0) {
		ListBox.SetItemData(ListIndex, Data);
	} else {
		return false;
	}

	return true;
}


/*===========================================================================
 *
 * Function - bool BrowseForFolder (pPath, hWnd, pTitle);
 *
 * Displays a folder browse dialog, allowing the user to select a folder.
 * Returns true on success and saves the path to the given string.  Assumes
 * that the input string is at least _MAX_PATH characters long.
 *
 *=========================================================================*/
bool BrowseForFolder(CString &Path, HWND hWnd, const TCHAR *pTitle) {
	bool Result;
	Result = BrowseForFolder(Path.GetBuffer(_MAX_PATH + 1), hWnd, pTitle);
	Path.ReleaseBuffer();
	return Result;
}

bool BrowseForFolder(TCHAR *pPath, HWND hWnd, const TCHAR *pTitle) {
	DEFINE_FUNCTION("BrowseForFolder()");
	BOOL Result;
	LPITEMIDLIST pItemIDList;
	BROWSEINFO BrowseInfo;

	/* Ensure valid input */
	ASSERT(pPath != NULL);

	/* Set the browse data structure */
	BrowseInfo.hwndOwner = hWnd;
	BrowseInfo.lpszTitle = pTitle == NULL ? _T("Select Folder") : pTitle;
	BrowseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN;
	BrowseInfo.pidlRoot = NULL;
	BrowseInfo.pszDisplayName = pPath;
	BrowseInfo.lpfn = NULL;
	BrowseInfo.iImage = 0;

	/* Display the shell folder browse dialog */
	pItemIDList = SHBrowseForFolder(&BrowseInfo);

	if (pItemIDList == NULL) {
		return false;
	}

	/* Retrieve the pathname */
	Result = SHGetPathFromIDList(pItemIDList, pPath);

	if (Result) {
		return true;
	}

	return false;
}


/*===========================================================================
 *
 * Function - bool ClipCopyFromWnd (pWnd);
 *
 * Attempts to copy text in the given window. Returns false on any error.
 *
 *=========================================================================*/
bool ClipCopyFromWnd(CWnd *pWnd) {
	CEdit *pEditWnd;

	/* Ignore if no control currently has the focus */
	if (pWnd == NULL) {
		return false;
	}

	/* Only support copying from certain types of controls */
	if (!pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
		return false;
	}

	pEditWnd = (CEdit *)pWnd;
	pEditWnd->Copy();
	return true;
}


/*===========================================================================
 *
 * Function - bool ClipCutFromWnd (pWnd);
 *
 *  Attempts to cut text in the given window. Returns false on any error.
 *
 *=========================================================================*/
bool ClipCutFromWnd(CWnd *pWnd) {
	CEdit *pEditWnd;

	/* Ignore if no control currently has the focus */
	if (pWnd == NULL) {
		return false;
	}

	/* Only support cutting from certain types of controls */
	if (!pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
		return false;
	}

	pEditWnd = (CEdit *)pWnd;
	pEditWnd->Cut();
	return true;
}


/*===========================================================================
 *
 * Function - bool ClipPasteToWnd (pWnd);
 *
 * Attempts to paste text to the given window. Returns false on any error.
 *
 *=========================================================================*/
bool ClipPasteToWnd(CWnd *pWnd) {
	CEdit *pEditWnd;

	/* Ignore if no control currently has the focus */
	if (pWnd == NULL) {
		return false;
	}

	/* Only support pasting to certain types of controls */
	if (!pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
		return false;
	}

	pEditWnd = (CEdit *)pWnd;
	pEditWnd->Paste();
	return true;
}


/*===========================================================================
 *
 * Function - bool CopyTextToClipboard (pString, Length);
 *
 * Copies text to the clipboard returning false on any error.
 *
 *=========================================================================*/
bool CopyTextToClipboard(const TCHAR *pString, const int Length) {
	HANDLE hText;
	TCHAR *pText;
	BOOL Result;
	/* Allocate the clipboard data buffer */
	hText = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, Length + 2);

	if (hText == NULL) {
		ErrorHandler.AddError(ERR_MEM, _T("Failed to globally allocated %d bytes!"), Length);
		return false;
	}

	/* Attempt to copy the text */
	pText = (TCHAR *)GlobalLock(hText);

	if (pText == NULL) {
		ErrorHandler.AddError(ERR_MEM, _T("Failed to lock the global memory!"));
		GlobalFree(hText);
		return false;
	}

	strnncpy(pText, pString, Length);
	Result = GlobalUnlock(hText);

	if (Result) {
		ErrorHandler.AddError(ERR_MEM, _T("Failed to unlock the global memory handle!"));
		GlobalFree(hText);
		return false;
	}

	/* Attempt to open the clipboard */
	Result = OpenClipboard(NULL);

	if (!Result) {
		ErrorHandler.AddError(ERR_WINDOWS, _T("Failed to open the clipboard!"));
		GlobalFree(hText);
		return false;
	}

	EmptyClipboard();
	SetClipboardData(CF_TEXT, hText);
	CloseClipboard();
	return true;
}


/*===========================================================================
 *
 * Function - bool CreateShortcut (pPathObj, pArgs, pIconPath, pPathLink, pDesc);
 *
 * Uses the shell's IShellLink and IPersistFile interfaces  to create and
 * store a shortcut to the specified object. Returns true on success.
 *
 *  pPathObj  - The filename to create the shortcut to.
 *  pArgs     - Optional arguments to the program.
 *  pIconPath - Path to the icon file (optional).
 *  pPathLink - The path where the shell link is to be saved.
 *  pDesc     - The description of the shell link.
 *
 *=========================================================================*/
bool CreateShortcut(LPTSTR pPathObj,
                    LPTSTR pWorkingPath,
                    LPTSTR pArgs,
                    LPTSTR pIconPath,
                    LPTSTR pPathLink,
                    LPTSTR pDesc) {
	HRESULT hResult;
	IShellLink *pShellLink;
	IPersistFile *pPersistFile;
	/* Get a pointer to the IShellLink interface. */
	hResult = CoCreateInstance(CLSID_ShellLink,
	                           NULL,
	                           CLSCTX_INPROC_SERVER,
	                           IID_IShellLink,
	                           (void **)&pShellLink);

	if (SUCCEEDED(hResult)) {
		/* Set the path to the shortcut target and add the description */
		pShellLink->SetPath(pPathObj);
		pShellLink->SetDescription(pDesc);

		if (pWorkingPath != NULL) {
			pShellLink->SetWorkingDirectory(pWorkingPath);
		}

		if (pArgs != NULL) {
			pShellLink->SetArguments(pArgs);
		}

		if (pIconPath != NULL) {
			pShellLink->SetIconLocation(pIconPath, 0);
		}

		/* Query IShellLink for the IPersistFile interface for saving the
		   shortcut in persistent storage */
		hResult = pShellLink->QueryInterface(IID_IPersistFile, (void **)&pPersistFile);

		if (SUCCEEDED(hResult)) {
			WORD TempBuffer[MAX_PATH + 1];
			/*  Ensure that the string is ANSI */
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pPathLink, -1, (LPWSTR)TempBuffer, MAX_PATH);
			/* Save the link by calling IPersistFile::Save */
			hResult = pPersistFile->Save((LPCOLESTR)TempBuffer, TRUE);
			pPersistFile->Release();
		}

		pShellLink->Release();
	}

	if (SUCCEEDED(hResult)) {
		return true;
	}

	return false;
}


/*===========================================================================
 *
 * Function - CString ExtractPath (PathBuffer, pPath);
 *
 * Saves just the path portion of the gven path to the string variable.
 *
 *=========================================================================*/
CString &ExtractPath(CString &PathBuffer, const TCHAR *pPath) {
	ExtractPath(PathBuffer.GetBuffer(_MAX_PATH), pPath, _MAX_PATH);
	PathBuffer.ReleaseBuffer(-1);
	return PathBuffer;
}


/*===========================================================================
 *
 * Function - int FindComboListItem (ComboBox, ItemData, Select);
 *
 * Finds an item in a combo list box with the given item data.  Returns the
 * items index or -1 on any error.
 *
 *=========================================================================*/
int FindComboListItem(CComboBox &ComboBox, const DWORD ItemData, const bool Select) {
	int Index;

	for (Index = 0; Index < ComboBox.GetCount(); Index++) {
		if (ComboBox.GetItemData(Index) == ItemData) {
			if (Select) {
				ComboBox.SetCurSel(Index);
			}

			return Index;
		}
	}

	/* No item found */
	if (Select) {
		ComboBox.SetCurSel(-1);
	}

	return -1;
}


/*===========================================================================
 *
 * Function - int FindListItem (ListBox, ItemData, Select);
 *
 * Finds an item in a list box with the given item data.  Returns the
 * items index or -1 on any error.
 *
 *=========================================================================*/
int FindListItem(CListBox &ListBox, const DWORD ItemData, const bool Select) {
	int Index;

	for (Index = 0; Index < ListBox.GetCount(); Index++) {
		if (ListBox.GetItemData(Index) == ItemData) {
			if (Select) {
				ListBox.SetCurSel(Index);
			}

			return Index;
		}
	}

	/* No item found */
	if (Select) {
		ListBox.SetCurSel(-1);
	}

	return -1;
}


/*===========================================================================
 *
 * Function - HTREEITEM FindTreeItem (pName, TreeCtrl, Root);
 *
 * Finds an item in a tree control with the given name under the given
 * tree level.  If the input Root is NULL, the root level is used, otherwise
 * the search is conducted using the children of the given root node.  Returns
 * the tree item if found, or NULL otherwise.
 *
 *=========================================================================*/
HTREEITEM FindTreeItem(const TCHAR *pName, CTreeCtrl &TreeCtrl, HTREEITEM Root) {
	DEFINE_FUNCTION("FindTreeItem()");
	HTREEITEM hFind = Root;
	CString Buffer;

	if (hFind == NULL) {
		hFind = TreeCtrl.GetRootItem();
	} else {
		hFind = TreeCtrl.GetChildItem(hFind);
	}

	while (hFind != NULL) {
		Buffer = TreeCtrl.GetItemText(hFind);

		if (Buffer.CompareNoCase(pName) == 0) {
			return hFind;
		}

		hFind = TreeCtrl.GetNextItem(hFind, TVGN_NEXT);
	}

	return NULL;
}


/*===========================================================================
 *
 * Function - HWND FindWindowHandle (hInstance);
 *
 * Attempts to find and return the window with the given application instance
 * handle. Returns NULL on any error.
 *
 *=========================================================================*/
HWND FindWindowHandle(HINSTANCE hInstance) {
	HWND hWnd;
	/* Enumerate through all windows */
	hWnd = FindWindow(NULL, NULL);

	while (hWnd != NULL) {
		/* Only bother with top-level windows */
		if (::GetParent(hWnd) == NULL) {
			/* Check the instance handle for the app */
			if (hInstance == (HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE)) {
				return hWnd;
			}
		}

		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}

	return NULL;
}


/*===========================================================================
 *
 * Function - bool GetCurSelListItemData (Data, ListBox);
 *
 * Attempt to access the item data of the currently selected list item.
 * Returns false if there is no item currently selected. Only valid for
 * single selected lists.
 *
 *=========================================================================*/
bool GetCurSelListItemData(long &Data, CListBox &ListBox) {
	int CurSel;
	/* Get the selected item index, if any */
	CurSel = ListBox.GetCurSel();

	if (CurSel == LB_ERR) {
		return false;
	}

	/* Access the selected item data */
	Data = ListBox.GetItemData(CurSel);
	return true;
}


/*===========================================================================
 *
 * Function - bool GetCurSelComboItemData (Data, ComboBox);
 *
 * Attempt to access the item data of the currently selected list item.
 * Returns false if there is no item currently selected. Only valid for
 * single selected lists.
 *
 *=========================================================================*/
bool GetCurSelComboItemData(long &Data, CComboBox &ComboBox) {
	int CurSel;
	/* Get the selected item index, if any */
	CurSel = ComboBox.GetCurSel();

	if (CurSel == LB_ERR) {
		return false;
	}

	/* Access the selected item data */
	Data = ComboBox.GetItemData(CurSel);
	return true;
}


/*========================================================================
 *
 * Function - CDocument* GetActiveDocument (void);
 *
 * Attempts to return the currently active document.  Returns NULL on any
 * error.
 *
 *======================================================================*/
CDocument *GetActiveDocument() {
	CWinApp *pApp = AfxGetApp();
	CWnd *pFrame = pApp->GetMainWnd();
	CDocument *pDoc;
	CMDIFrameWnd *pMDIFrame;

	/* Ensure the main window is the valid type */
	if (pFrame == NULL) {
		return NULL;
	}

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))) {
		return NULL;
	}

	pMDIFrame = (CMDIFrameWnd *)pFrame;
	/* Get the active document of mdi frame */
	pDoc = GetActiveFrameDocument(pMDIFrame);

	if (pDoc == NULL) {
		return NULL;
	}

	return pDoc;
}


/*========================================================================
 *
 * Function - CView* GetActiveView (void);
 *
 * Attempts to return the currently active view.  Returns NULL on any
 * error.
 *
 *======================================================================*/
CView *GetActiveView() {
	CWinApp *pApp = AfxGetApp();
	CWnd *pFrame = pApp->GetMainWnd();
	CMDIChildWnd *pChild;
	CView *pView;
	CMDIFrameWnd *pMDIFrame;

	/* Ensure the main window is the valid type */
	if (pFrame == NULL) {
		return NULL;
	}

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))) {
		return NULL;
	}

	pMDIFrame = (CMDIFrameWnd *)pFrame;
	pChild = (CMDIChildWnd *)pMDIFrame->GetActiveFrame();

	if (pChild == NULL) {
		return NULL;
	}

	pView = pChild->GetActiveView();
	return pView;
}


/*===========================================================================
 *
 * Function - bool GetClipboardText (Buffer);
 *
 * Copies the text in the clipboard to the given string. Returns false
 * on any error.
 *
 *=========================================================================*/
bool GetClipboardText(CString &Buffer) {
	BOOL Result;
	HANDLE hText;
	TCHAR *pText;
	/* Attempt to open the clipboard */
	Result = ::OpenClipboard(NULL);

	if (!Result) {
		ErrorHandler.AddError(ERR_WINDOWS, _T("Failed to open the clipboard!"));
		return false;
	}

	/* Attempt to retrieve some text data from the clipboard */
	hText = GetClipboardData(CF_TEXT);

	if (hText == NULL) {
		ErrorHandler.AddError(ERR_WINDOWS, _T("Failed to get the clipboard text data!"));
		CloseClipboard();
		return false;
	}

	pText = (TCHAR *)GlobalLock(hText);

	if (pText == NULL) {
		ErrorHandler.AddError(ERR_WINDOWS, _T("Failed to get the clipboard text pointer!"));
		CloseClipboard();
		return false;
	}

	/* Copy the clipboard text */
	Buffer = pText;
	GlobalUnlock(hText);
	CloseClipboard();
	return true;
}


/*========================================================================
 *
 * Function - CView* GetView (pRunTimeClass);
 *
 * Attempts to find and return a pointer to an view of the given type
 * of the current document.  Returns NULL on error or no view found.
 *
 *======================================================================*/
CView *GetView(const CRuntimeClass *pRunTimeClass) {
	CDocument *pDoc;
	CView *pView;
	POSITION ViewPos;
	/* Get the currently active document */
	pDoc = GetActiveDocument();

	if (pDoc == NULL) {
		return NULL;
	}

	/* Look through all views in current document */
	ViewPos = pDoc->GetFirstViewPosition();

	while (ViewPos != NULL) {
		pView = pDoc->GetNextView(ViewPos);

		if (pView == NULL) {
			continue;
		}

		/* Is this view the correct type? */
		if (pView->IsKindOf(pRunTimeClass)) {
			return pView;
		}
	}

	/* No matching view found */
	return NULL;
}


/*===================================================================
 *
 * Function - CDocument* GetActiveFrameDocument (pFrame);
 *
 * Returns the proper currently active document in frame.
 *
 *======================================================================*/
CDocument *GetActiveFrameDocument(CFrameWnd *pFrame) {
	DEFINE_FUNCTION("GetActiveFrameDocument()");
	CView *pView;
	CDocument *pDoc;
	/* Ensure valid input */
	ASSERT(pFrame != NULL);
	pView = GetActiveFrameView(pFrame);

	if (pView == NULL) {
		return NULL;
	}

	pDoc = pView->GetDocument();
	return pDoc;
}


/*========================================================================
 *
 * Function - CView* GetActiveFrameView (pFrame);
 *
 * Returns the proper currently active view for a frame.
 *
 *======================================================================*/
CView *GetActiveFrameView(CFrameWnd *pFrame) {
	DEFINE_FUNCTION("GetActiveFrameView()");
	CFrameWnd *pActiveFrame;
	CMDIChildWnd *pChild;
	CView *pView;
	/* Ensure valid input */
	ASSERT(pFrame != NULL);
	pActiveFrame = pFrame->GetActiveFrame();

	if (pActiveFrame == NULL) {
		return NULL;
	}

	if (!pActiveFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) {
		return NULL;
	}

	pChild = (CMDIChildWnd *)pActiveFrame;
	pView = pChild->GetActiveView();
	return pView;
}


/*===========================================================================
 *
 * Function - void MakeTimeString (Buffer, Options);
 *
 * Formats the given string with the time/data depending on the input options.
 *
 *=========================================================================*/
void MakeTimeString(CString &Buffer, const int Options) {
	CString TempString;
	CTime CurrentTime = CTime::GetCurrentTime();
	bool HasTime;
	/* Clear the current string */
	Buffer.Empty();
	HasTime = false;

	/* Add the time if required */
	if (Options & TIMESTRING_SHORTTIME) {
		Buffer = CurrentTime.Format(_T("%H:%M:%S"));
		HasTime = true;
	} else if (Options & TIMESTRING_LONGTIME) {
		Buffer = CurrentTime.Format(_T("%H:%M:%S %z"));
		HasTime = true;
	}

	/* Add the date if required */
	if (Options & TIMESTRING_SHORTDATE) {
		if (HasTime) {
			Buffer += _T(", ");
		}

		Buffer += CurrentTime.Format(_T("%d/%m/%y"));
	} else if (Options & TIMESTRING_LONGDATE) {
		if (HasTime) {
			Buffer += _T(", ");
		}

		Buffer += CurrentTime.Format(_T("%d %b %Y"));
	}
}


/*===========================================================================
 *
 * Function - bool GetStringWord (OutputString, pBuffer, StartPos);
 *
 * Parse a single word from the given string buffer. Returns false if no
 * word is available. Ignores whitespace.
 *
 *=========================================================================*/
bool GetStringWord(CString &OutputString, const TCHAR *pBuffer, int &StartPos) {
	int BeginPos;

	/* Ignore initial whitespace */
	while (isspace(pBuffer[StartPos])) {
		StartPos++;
	}

	/* Ignore if at the end of the string */
	if (pBuffer[StartPos] == NULL_CHAR) {
		return false;
	}

	/* Start parsing */
	BeginPos = StartPos;

	/* Alphanumeric string */
	if (isalnum(pBuffer[StartPos])) {
		while (isalnum(pBuffer[StartPos]) || pBuffer[StartPos] == '.') {
			StartPos++;
		}

		//OutputString = CString(pBuffer + BeginPos, StartPos - BeginPos);
		int Size = StartPos - BeginPos;
		TCHAR *pString = OutputString.GetBuffer(Size + 1);
		strnncpy(pString, pBuffer + BeginPos, Size);
		OutputString.ReleaseBuffer(Size);
	}
	/* Quoted string */
	else if (pBuffer[StartPos] == '"') {
		StartPos++;

		while (pBuffer[StartPos] != '"' && pBuffer[StartPos] != NULL_CHAR) {
			StartPos++;
		}

		if (pBuffer[StartPos] == '"') {
			StartPos++;
		}

		//OutputString = CString(pBuffer + BeginPos, StartPos - BeginPos);
		int Size = StartPos - BeginPos;
		TCHAR *pString = OutputString.GetBuffer(Size + 1);
		strnncpy(pString, pBuffer + BeginPos, Size);
		OutputString.ReleaseBuffer(Size);
	}
	/* Other, operator, single character */
	else {
		OutputString = pBuffer[StartPos];
		StartPos++;
	}

	return true;
}


/*===========================================================================
 *
 * Function - bool OpenContextMenu (pParent, pWnd, Point, MenuResource);
 *
 * Attempts to open a context menu using the given information. Returns
 * false on any error.
 *
 *=========================================================================*/
bool OpenContextMenu(CWnd *pParent, CWnd *pWnd, CPoint Point, const DWORD MenuResource) {
	CMenu Menu;
	CMenu *pPopup;
	BOOL Result;
	CCmdUI MenuState;
	int Index;
	/* Get the popup menu to display */
	Result = Menu.LoadMenu(MenuResource);

	if (!Result) {
		return false;
	}

	pPopup = Menu.GetSubMenu(0);

	if (pPopup == NULL) {
		return false;
	}

	/* Force the update of the menu commands */
	for (Index = 0; Index < (int)pPopup->GetMenuItemCount(); Index++) {
		MenuState.m_nID = pPopup->GetMenuItemID(Index);
		MenuState.m_nIndex = Index;
		MenuState.m_pMenu = pPopup;
		MenuState.m_pOther = NULL;
		MenuState.m_pSubMenu = NULL;
		MenuState.m_nIndexMax = pPopup->GetMenuItemCount();

		if (MenuState.m_nID != 0) {
			pParent->OnCmdMsg(MenuState.m_nID, CN_UPDATE_COMMAND_UI, &MenuState, NULL);
		}
	}

	pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, Point.x, Point.y, pParent);
	return true;
}


/*===========================================================================
 *
 * Function - HINSTANCE OpenWebPage (pSiteAddress);
 *
 * Attempt to open the given web page address. Returns the handle to the
 * application instance on success.
 *
 *=========================================================================*/
HINSTANCE OpenWebPage(const TCHAR *pSiteAddress) {
	BOOL Result;
	SHELLEXECUTEINFO ShellInfo;

	/* Initialize the shellinfo structure */
	ShellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShellInfo.hwnd = NULL;
	ShellInfo.lpFile = pSiteAddress;
	ShellInfo.lpVerb = _T("open");
	ShellInfo.lpClass = NULL;
	ShellInfo.lpDirectory = NULL;
	ShellInfo.lpIDList = NULL;
	ShellInfo.lpParameters = NULL;
	ShellInfo.nShow = SW_SHOWNORMAL;

	/* Attempt to open the file/page */
	Result = ShellExecuteEx(&ShellInfo);

	if (!Result) {
		return NULL;
	}

	//hResult = ShellExecute (NULL, _T("open"), pSiteAddress, NULL, NULL, SW_SHOWNORMAL);
	return ShellInfo.hInstApp;
}


/*===========================================================================
 *
 * Function - int RunDOSCommand (pFilename);
 *
 * Execute a simple DOS command.  Returns the process handle or -1 on any
 * error.
 *
 *=========================================================================*/
int RunDOSCommand(const TCHAR *pFilename) {
	int ProcessHandle;
	const TCHAR *Args[4];
	/* Setup the program arguments */
	Args[0] = _tgetenv(_T("COMSPEC"));
	Args[1] = _T("/c");
	Args[2] = (TCHAR *)pFilename;
	Args[3] = NULL;

	/* Start the program depending on whether we found the COMSPEC variable */
	if (Args[0] == NULL) {
		Args[0] = _T("cmd.exe");
		ProcessHandle = _tspawnvpe(_P_NOWAIT, Args[0], Args, NULL);
	} else {
		ProcessHandle = _tspawnve(_P_NOWAIT, Args[0], Args, NULL);
	}

	return ProcessHandle;
}


/*===========================================================================
 *
 * Begin String Conversion Functions
 *   bool StringToInteger (pString, DestValue);
 *   bool StringToFloat   (pString, DestValue);
 *   bool StringToBool    (pString, DestValue);
 *
 * Converts TCHAR strings into the appropriate type, returning false on
 * any error.
 *
 *=========================================================================*/
bool StringToInteger(const TCHAR *pString, int &DestValue) {
	DEFINE_FUNCTION("StringToInteger()");
	int iValue;
	TCHAR *pEndPtr;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Convert the string to an integer */
	iValue = (int)TSTRTOL(pString, &pEndPtr, 0);

	/* Check for conversion errors */
	if (*pEndPtr != (TCHAR) 0 && !TISSPACE(*pEndPtr)) {
		ErrorHandler.AddError(ERR_BADINPUT, _T("Invalid integer parameter string!"));
		return false;
	}

	/* Save the number and return success */
	DestValue = iValue;
	return true;
}

bool StringToFloat(const TCHAR *pString, float &DestValue) {
	DEFINE_FUNCTION("StringToFloat()");
	float fValue;
	TCHAR *pEndPtr;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	/* Convert the string to a floating point value */
	fValue = (float)TSTRTOD(pString, &pEndPtr);

	/* Check for conversion errors */
	if (*pEndPtr != (TCHAR) 0 && !TISSPACE(*pEndPtr)) {
		ErrorHandler.AddError(ERR_BADINPUT, _T("Invalid float parameter string!"));
		return false;
	}

	/* Store the value and return success */
	DestValue = fValue;
	return true;
}

bool StringToBool(const TCHAR *pString, bool &DestValue) {
	DEFINE_FUNCTION("StringToBool()");
	bool bValue;
	int iValue;
	TCHAR *pEndPtr;
	/* Ensure valid input */
	ASSERT(pString != NULL);

	/* Check for an exact true/false string */
	if (_stricmp(pString, _T("true")) == 0) {
		bValue = true;
	} else if (_stricmp(pString, _T("false")) == 0) {
		bValue = false;
	} else { /* Check for a numeric boolean value */
		iValue = (int)TSTRTOL(pString, &pEndPtr, 0);

		if ((*pEndPtr != (TCHAR) 0 && !TISSPACE(*pEndPtr)) || iValue < 0 || iValue > 1) {
			ErrorHandler.AddError(ERR_BADINPUT, _T("Invalid boolean parameter string!"));
			return false;
		}

		bValue = iValue != 0;
	}

	/* Store the value and return success */
	DestValue = bValue;
	return true;
}


/*===========================================================================
 *
 * Function - void WINAPI SetInternalWindowText (hwnd, lpText);
 *
 * Description
 *
 *=========================================================================*/
void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText) {
	/* Turn off WS_VISIBLE if necessary to avoid painting */
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);

	if (dwStyle & WS_VISIBLE) {
		::SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_VISIBLE);
	}

	/* Call DefWindowProc directly to set internal window text */
	DefWindowProc(hwnd, WM_SETTEXT, 0, (LPARAM)lpText);

	/* Restore parent visible state */
	if (dwStyle & WS_VISIBLE) {
		::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
	}
}


/*===========================================================================
 *
 * Function - CString& TerminatePathString (PathBuffer);
 *
 * Ensures that the given string ends with a '\' character.
 *
 *=========================================================================*/
CString &TerminatePathString(CString &PathBuffer) {
	TCHAR *pBuffer = PathBuffer.GetBuffer(PathBuffer.GetLength() + 1);
	TerminatePath(pBuffer);
	PathBuffer.ReleaseBuffer(-1);
	return PathBuffer;
}
