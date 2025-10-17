/*===========================================================================
 *
 * File:    Esmscrfuncarray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 2, 2003
 *
 * Description
 *
 *=========================================================================*/
#include "project/EsmScrFuncArray.h"


DEFINE_FILE("EsmScrFuncArray.cpp");


/*===========================================================================
 *
 * Class CEsmScrFuncArray Constructor
 *
 *=========================================================================*/
CEsmScrFuncArray::CEsmScrFuncArray () : m_Functions(0) {
	//DEFINE_FUNCTION("CEsmScrFuncArray::CEsmScrFuncArray()");
}


/*===========================================================================
 *
 * Class CEsmScrFuncArray Method - void Destroy (void);
 *
 *=========================================================================*/
void CEsmScrFuncArray::Destroy() {
	DEFINE_FUNCTION("CEsmScrFuncArray::Destroy()");
	CEsmScrFuncData *pFunction;
	int Index;

	/* Delete all function objects in the array */

	for (Index = 0; Index < m_Functions.GetNumElements(); Index++) {
		pFunction = m_Functions.GetAt(Index);
		DestroyPointer(pFunction);
	}

	m_Functions.RemoveAll();
}


/*===========================================================================
 *
 * Class CEsmScrFuncArray Method - CEsmScrFuncData* FindFunction (pName);
 *
 * Finds and returns the given function definition record or NULL if it
 * is not found. Does not use a fast search method.
 *
 *=========================================================================*/
CEsmScrFuncData *CEsmScrFuncArray::FindFunction(const TCHAR *pName) {
	CEsmScrFuncData *pFunction;
	int Index;

	/* Look at all function objects in the array */

	for (Index = 0; Index < m_Functions.GetNumElements(); Index++) {
		pFunction = m_Functions.GetAt(Index);

		if (pFunction->IsName(pName)) {
			return pFunction;
		}
	}

	return NULL;
}


/*===========================================================================
 *
 * Class CEsmScrFuncArray Method - bool Load (pFilename);
 *
 * Attempts to load function definitions from the given data file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CEsmScrFuncArray::Load(const TCHAR *pFilename) {
	CGenFile File;
	bool Result;
	/* Attempt to open the file for input */
	Result = File.Open(pFilename, _T("rt"));

	if (!Result) {
		return false;
	}

	/* Clear the current contents */
	Destroy();
	/* Input the data file */
	return Read(File);
}


/*===========================================================================
 *
 * Class CEsmScrFuncArray Method - bool Read (File);
 *
 * Reads the function data from the given open file. Returns false on any
 * error.
 *
 *=========================================================================*/
bool CEsmScrFuncArray::Read(CGenFile &File) {
	TCHAR LineBuffer[ESM_SFDATA_LINELENGTH];
	TCHAR *pVariable;
	TCHAR *pValue;
	int LineResult;
	bool Result;

	/* Read until end of file */

	while (!File.IsEOF()) {
		/* Input one line from the file */
		LineResult = File.ReadLine(LineBuffer, ESM_SFDATA_LINELENGTH);

		if (LineResult == READLINE_MSL) {
			LineResult = File.ReadLine();
		}

		if (LineResult == READLINE_ERROR) {
			return false;
		}

		/* Attempt to parse the input line */
		Result = SeperateVarValue(&pVariable, &pValue, LineBuffer);

		if (!Result) {
			continue;
		}

		/* Check for the start of a function definition */

		if (_stricmp(pVariable, _T("Function")) == 0) {
			Result = ReadFunction(File, pValue);

			if (!Result) {
				return false;
			}
		}
	}

	return true;
}


/*===========================================================================
 *
 * Class CEsmScrFuncArray Method - bool ReadFunction (File, pFuncName);
 *
 * Reads a single function data record from the current position in the
 * given file. Creates the function with the specified name. Returns false
 * on any error.
 *
 *=========================================================================*/
bool CEsmScrFuncArray::ReadFunction(CGenFile &File, const TCHAR *pFuncName) {
	DEFINE_FUNCTION("CEsmScrFuncArray::ReadFunction()");
	CEsmScrFuncData *pFunction;

	/* Allocate and initialize the new function object */
	CreatePointer(pFunction, CEsmScrFuncData);
	m_Functions.Add(pFunction);
	pFunction->SetFunction(pFuncName);

	/* Input the function record */
	return pFunction->ReadData(File);
}
