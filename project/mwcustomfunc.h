/*===========================================================================
 *
 * File:    Mwcustomfunc.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  August 21, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __MWCUSTOMFUNC_H
#define __MWCUSTOMFUNC_H


#include "file/genfile.h"
#include "string/sstring.h"
#include "contain/dl_map.h"
#include "Esmscriptdefs.h"


/*===========================================================================
 *
 * Begin Class CMwCustomFunction Definition
 *
 * Description
 *
 *=========================================================================*/
class CMwCustomFunction {
  private:
	esmscrfuncinfo_t m_Data; /* Function data */
	dword m_LineCount;


  protected:
	bool ParseFuncOptions(dword &Options, const char *pValue);
	bool ParseFuncArgOptions(dword &Options, const char *pValue);
	bool ParseReturnOptions(dword &Options, const char *pValue);


  public:
	/* Class Constructors/Destructors */
	CMwCustomFunction();
	//virtual ~CMwCustomFunction() { Destroy(); }
	//virtual void Destroy (void);

	/* Get class members */
	esmscrfuncinfo_t &GetData() {
		return m_Data;
	}

	const char *GetName() {
		return m_Data.Name;
	}

	/* Read in function parameters from a file */
	bool Read(CGenFile &File, dword &LineCount);

	/* Sets a parameter based on the string inputs */
	bool SetParameter(const char *pVariable, const char *pValue);

	/* Set class members */
	void SetName(const char *pValue) {
		strnncpy(m_Data.Name, pValue, MWESM_SCRIPT_FUNCNAMESIZE);
	}

	void SetOpCode(const short Value) {
		m_Data.OpCode = Value;
	}

	void SetOptions(const dword Value) {
		m_Data.Flags = Value;
	}

	void SetReturnOptions(const dword Value) {
		m_Data.Return = Value;
	}

	void SetArgOptions(const dword Index, const dword Value) {
		if (Index <= MWESM_SCRIPT_MAXARGS) {
			m_Data.Var[Index] = Value;
		}
	}
};


/* Map of custom functions */
typedef TGenMap<CSString, CMwCustomFunction *, const char *> CMwCustomFunctions;


/* Input functions from a file */
bool ReadMwCustomFunctions(CMwCustomFunctions &Functions, const char *pFilename);


/* Global custom function map */
extern CMwCustomFunctions g_CustomFunctions;


#endif
