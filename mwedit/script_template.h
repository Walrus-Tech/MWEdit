/*===========================================================================
 *
 * File:    Scripttemplate.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  October 8, 2003
 *
 * Defines the CEsmScriptTemplate class.
 *
 *=========================================================================*/
#ifndef __SCRIPTTEMPLATE_H
#define __SCRIPTTEMPLATE_H


#include "Common/dl_err.h"
#include "esm/EsmScript.h"
#include "Common/Contain/PtrArray.h"
#include "File/CsvFile.h"


/* Maximum size of template files */
#define ESM_SCRTEMP_MAXTEMPSIZE   ESM_SCRIPT_MAXTEXT

/* Maximum size of template variables */
#define ESM_SCRTEMP_MAXVARSIZE    31

/* Template characters */
#define ESM_SCRTEMP_TEMPCHAR1     '['
#define ESM_SCRTEMP_TEMPCHAR2     ']'

/* File parameters */
#define ESM_SCRTEMP_FILEEXT       _T("txt")
#define ESM_SCRTEMP_FILEFILTER    _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||")

/* Special variable names */
#define ESMSCRTEMP_CSV_SCRIPTNAME _T("ScriptName")


/* Holds information on a single template variable */
typedef struct esmscrtempvar {
	TCHAR Name[ESM_SCRTEMP_MAXVARSIZE + 1];
	int Uses;
	int CsvColIndex;

	bool IsName(const TCHAR *pString) {
		return StringCompare(Name, pString, false) == 0;
	}

	void SetName(const TCHAR *pString) {
		strnncpy(Name, pString, ESM_SCRTEMP_MAXVARSIZE);
	}
} esmscrtempvar_t;

typedef TPtrArray<esmscrtempvar_t> CEsmScrTempVarArray;


/*===========================================================================
 *
 * Begin Class CEsmScriptTemplate Definition
 *
 * Handles the loading and parsing of script template files.
 *
 *=========================================================================*/
class CEsmScriptTemplate {
  private:
	CSString m_TemplateText; /* The template text buffer */
	CSString m_Filename;
	CEsmScrTempVarArray m_TemplateVars;

	CSString m_ScriptName; /* Used for conversion */


  protected:
	/* Parses and adds a template variable */
	bool AddTemplateVariable(const TCHAR *pVariable, const int Length);


  public:
	/* Class Constructors/Destructors */
	CEsmScriptTemplate();

	virtual ~CEsmScriptTemplate() {
		Destroy();
	}

	virtual void Destroy();

	/* Parses and adds a template variable */
	bool AddTemplateVar(const TCHAR *pVariable);

	/* Delete any defined template variables */
	void ClearTemplateVars();

	/* Converts a script template text buffer */
	bool ConvertText(TCHAR *pOutBuffer, const int BufferSize, CCsvRow *pRow);

	/* Attempt to find a template variable */
	esmscrtempvar_t *FindTemplateVar(const TCHAR *pVariable);

	/* Find a variable value from a csv row */
	CSString *GetCsvString(const TCHAR *pVarName, CCsvRow *pRow);

	/* Get class members */
	const TCHAR *GetTemplateText() const {
		return m_TemplateText;
	}

	const TCHAR *GetFilename() const {
		return m_Filename;
	}

	int GetTemplateSize() const {
		return m_TemplateText.GetLength();
	}

	int GetNumTempVars() const {
		return m_TemplateVars.GetNumElements();
	}

	/* Access a template variable */
	esmscrtempvar_t *GetTemplateVar(const int Index) {
		return m_TemplateVars.GetAt(Index);
	}

	/* Attempt to load a script template file */
	bool Load(const TCHAR *pFilename);

	/* Parse the template text */
	bool ParseText();

	/* Set class members */
	void SetText(const TCHAR *pString) {
		m_TemplateText = pString;
	}

	void SetScriptName(const TCHAR *pString) {
		m_ScriptName = pString;
	}
};


#endif
