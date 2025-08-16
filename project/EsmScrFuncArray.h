/*===========================================================================
 *
 * File:    Esmscrfuncarray.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  September 2, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSCRFUNCARRAY_H
#define __ESMSCRFUNCARRAY_H


#include "EsmScrFuncData.h"
#include "contain/PtrArray.h"


/* Default data file */
#define MWESM_SFDATA_DEFAULTFILE _T("Functions.dat")


/* Array of function definition objects */
typedef TPtrArray<CEsmScrFuncData> CEsmSFDataArray;


/*===========================================================================
 *
 * Begin Class CEsmScrFuncArray Definition
 *
 * Holds an array of string function definitions
 *
 *=========================================================================*/
class CEsmScrFuncArray {
  private:
	CEsmSFDataArray m_Functions; /* Function definition array */


  protected:
	/* Input function data from the file */
	bool ReadFunction(CGenFile &File, const TCHAR *pFuncName);


  public:
	/* Class Constructors/Destructors */
	CEsmScrFuncArray();

	virtual ~CEsmScrFuncArray() {
		Destroy();
	}

	virtual void Destroy();

	/* Find and return a function record */
	CEsmScrFuncData *FindFunction(const TCHAR *pName);

	/* Get class members */
	int GetCount() {
		return m_Functions.GetNumElements();
	}

	CEsmScrFuncData *GetFunction(const int Index) {
		return m_Functions.GetAt(Index);
	}

	bool IsValidIndex(const int Index) {
		return m_Functions.IsValidIndex(Index);
	}

	/* Load a function data file */

	bool LoadDefault() {
		return Load(MWESM_SFDATA_DEFAULTFILE);
	}

	bool Load(const TCHAR *pFilename);
	bool Read(CGenFile &File);
};


#endif
