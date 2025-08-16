/*===========================================================================
 *
 * File:    Editundo.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  August 22, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __EDITUNDO_H
#define __EDITUNDO_H


#include "dl_err.h"
#include "contain/temarray.h"


/* Types of undo actions */
#define EDITUNDO_NONE         0
#define EDITUNDO_INSERTCHAR   1
#define EDITUNDO_INSERTSTRING 2
#define EDITUNDO_DELETECHAR   3
#define EDITUNDO_DELETESTRING 4
#define EDITUNDO_ENTIRETEXT   5

/* Default undo limit */
#define EDITUNDO_DEFAULT_LIMIT 100


/*===========================================================================
 *
 * Begin Class CEditUndo Definition
 *
 * Defines a single undo action for an edit control.
 *
 *=========================================================================*/
class CEditUndo {
  private:
	int m_Action;
	TCHAR m_Char;
	TCHAR *m_pString;
	dword m_StringLength;
	int m_SelStart;
	int m_SelEnd;


  public:
	/* Class Constructors/Destructors */
	CEditUndo();

	virtual ~CEditUndo() {
		Destroy();
	}

	virtual void Destroy();

	/* Get class members */
	int GetAction() {
		return m_Action;
	}

	TCHAR GetChar() {
		return m_Char;
	}

	const TCHAR *GetString() {
		return m_pString;
	}

	dword GetStringLength() {
		return m_StringLength;
	}

	int GetSelStart() {
		return m_SelStart;
	}

	int GetSelEnd() {
		return m_SelEnd;
	}

	/* Set class members */
	void SetAction(const int Action) {
		m_Action = Action;
	}

	void SetChar(const TCHAR Char) {
		m_Char = Char;
	}

	void SetSelStart(const int Value) {
		m_SelStart = Value;
	}

	void SetSelEnd(const int Value) {
		m_SelEnd = Value;
	}

	void SetString(const TCHAR *pString);
};

/* Array of undo actions */
typedef TTemplateArray<CEditUndo> CEditUndoList;


/*===========================================================================
 *
 * Begin Class CEditUndoStack Definition
 *
 * Description
 *
 *=========================================================================*/
class CEditUndoStack {
  private:
	CEditUndoList m_UndoStack;

	bool m_GroupUndos;
	int m_Limit;


  protected:
	bool GroupUndoInsertChar(CRichEditCtrl *pCtrl, CEditUndo *pUndo);


  public:
	/* Class Constructors/Destructors */
	CEditUndoStack();

	virtual ~CEditUndoStack() {
		Destroy();
	}

	virtual void Destroy();

	/* Create undo actions */
	void CreateInsertChar(const TCHAR Char, const int StartSel, const int EndSel);
	void CreateInsertString(const TCHAR *pString, const int StartSel, const int EndSel);
	void CreateDeleteChar(const TCHAR Char, const int StartSel, const int EndSel);
	void CreateDeleteString(const TCHAR *pString, const int StartSel, const int EndSel);
	void CreateEntireText(const TCHAR *pString);

	/* Get class members */
	dword GetSize() const {
		return m_UndoStack.GetNumElements();
	}

	dword GetLimit() const {
		return m_Limit;
	}

	/* Checks if the stack is empty or not */
	bool IsEmpty() const {
		return m_UndoStack.GetNumElements() == 0;
	}

	/* Helper handler functions */
	bool OnChar(CRichEditCtrl *pCtrl, const int CharCode);
	bool OnKeyDown(CRichEditCtrl *pCtrl, const int CharCode);
	int OnUndo(CRichEditCtrl *pCtrl);
	bool OnPaste(CRichEditCtrl *pCtrl);
	bool OnCut(CRichEditCtrl *pCtrl);

	/* Push a new undo action to the top of the stack */
	void Push(CEditUndo *pUndo) {
		m_UndoStack.Add(pUndo);
	}

	/* Remove an undo action from the top of the stack */
	CEditUndo *Pop();

	/* Set class members */
	void SetGroupUndos(const bool Flag) {
		m_GroupUndos = Flag;
	}

	void SetLimit(const dword Value) {
		m_Limit = Value;
	}
};


#endif
