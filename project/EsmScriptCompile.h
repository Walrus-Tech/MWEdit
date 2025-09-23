/*===========================================================================
 *
 * File:    Esmscriptcompile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, February 14, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSCRIPTCOMPILE_H
#define __ESMSCRIPTCOMPILE_H


#include "EsmScriptDefs.h"
#include "EsmScriptError.h"
#include "string/SString.h"
#include "contain/PtrArray.h"
#include "contain/GenStack.h"
#include "mwcustomfunc.h"
#include "esmfile.h"

#if MWEDIT_SCRIPT_MWSE
	#include <queue>
	#include <stack>
#endif


/* Token flags */
#define ESTF_ONE                        1
#define ESTF_MANY                       2
#define ESTF_OPT                        4
#define ESTF_STOP                       8

/* Used to detect the special 34th local variable bug */
#define ESMSCR_SPECIALLOCALVAR_INDEX    33

/* Return codes */
#define ESMSCR_RESULT_OK                0
#define ESMSCR_RESULT_ERROR            -1
#define ESMSCR_RESULT_WARNING           1
#define ESMSCR_RESULT_BLOCKEND          2
#define ESMSCR_RESULT_TABLEEND          3
#define ESMSCR_RESULT_NOTOKEN           4

/* Special function opcodes */
#define ESMSCR_FUNCOPCODE_MESSAGEBOX 0x1000

/* Flags for custom character types */
#define ESMSCR_CHARTYPE_SPACE           1
#define ESMSCR_CHARTYPE_PUNCT           2
#define ESMSCR_CHARTYPE_DIGIT           4
#define ESMSCR_CHARTYPE_SYMBOLF         8
#define ESMSCR_CHARTYPE_SYMBOL         16

/* Special characters */
#define ESMSCR_CHAR_EOL                '\r'
#define ESMSCR_CHAR_COMMENT            ';'
#define ESMSCR_CHAR_STRING             '"'

/* Max defined variable length */
#define ESMSCR_VAR_MAXLENGTH            32

/* Maximum compiled script data length */
#define ESMSCR_DATA_SIZE                65535

/* Number of local variables allowed (game limited?) */
#define ESMSCR_MAX_LOCALVARS            255

/* Variable types */
#define ESMSCR_VAR_UNKNOWN             -1
#define ESMSCR_VAR_SHORT                0
#define ESMSCR_VAR_LONG                 1
#define ESMSCR_VAR_FLOAT                2

/* Compiler message levels */
#define ESMSCR_MSGLEVEL_ERROR          -1
#define ESMSCR_MSGLEVEL_NONE            0
#define ESMSCR_MSGLEVEL_WARNING         1

#define ESMSCR_MAX_FUNCARGS MWESM_SCRIPT_MAXARGS

/* Return values for checking function arguments */
#define ESMSC_FUNCARG_OK                0
#define ESMSC_FUNCARG_ERROR            -1
#define ESMSC_FUNCARG_ENDTABLE         -2

/* Number of message IDs */
#define ESMSCR_MAX_MESSAGES            64

/* Max token string length for stack */
#define ESMSCR_STACK_MAXTOKENSIZE      63


/* Class forward definition */
class CEsmScriptCompile;
class CMWEditDoc;

/* Custom block parsing function type */
typedef int (CEsmScriptCompile::* ESMSCRBLOCK_FUNC) (void);

/* Token parsing table structure */
typedef struct espt_TAG {
	int TokenID;
	int Flags;
	espt_TAG *pParseTable;
	ESMSCRBLOCK_FUNC ParseFunc;
	ESMSCRBLOCK_FUNC OutputFunc;
} esmscrparsetable_t;

/* Holds defined type information */
typedef struct esmscrtypeinfo {
	TCHAR Name[ESMSCR_VAR_MAXLENGTH + 1];
	int Type;

	void SetName(const TCHAR *pString) {
		strnncpy(Name, pString, ESMSCR_VAR_MAXLENGTH);
	}
} esmscrtypeinfo_t;

/* Holds message level values */
struct emscrmsglevel_t {
	int MessageID;
	int Level;
};

/* Used for the expression stack */
struct esmscrstack_t {
	int TokenID;
	TCHAR Token[ESMSCR_STACK_MAXTOKENSIZE + 1];
};

/* Used for IF statement blocks and the if statement stack */
struct esmscrifblock_t {
	int IfStartPos;
	int StartStatementCount;
};


/*===========================================================================
 *
 * Begin Class CEsmScriptCompile Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmScriptCompile {
  protected:
	CMWEditDoc *m_pDocument;        /* Parent document */

	static CEsmFile m_ExtraFile;    /* Used to find 'extra' records */
	static CEsmRecordRefMap m_ExtraRecords;

	TCHAR *m_pScriptText;           /* Raw script text buffer */
	byte *m_pOutBuffer;             /* Compiled script output buffer */
	CSString m_ScriptName;          /* Script ID */

	TCHAR *m_pParse;                /* Current parsing buffer position */

	CSString m_Token;               /* Current token parsing information */
	CSString m_LastToken;
	int m_TokenID;
	int m_CurrentLine;
	int m_CurrentCharPos;
	int m_StartCharPos;
	int m_StartLine;
	bool m_TokenParsed;
	bool m_LineHasRef;
	CSString m_LineRefToken;
	int m_LineRefID;
	bool m_LastTokenNegative;
	bool m_LastSetNegative;

	esmscrfuncinfo_t *m_pCurrentFunc; /* Used when parsing a function statement block */
	int m_NumFuncArgs;
	int m_LastFuncArg;
	int m_FuncArgIndex;

	CSString m_ErrorMessage;          /* Holds the last compiler error message */
	bool m_HasErrorMsg;
	int m_NumErrors;
	int m_NumWarnings;

	CEsmScriptErrArray m_ErrorArray;  /* Array of script errors from last compile */

	int *m_pCharTypes;                /* Pointer to a character type array */

	/* Holds the script local variable definitions */
	esmscrtypeinfo_t m_ShortVars[ESMSCR_MAX_LOCALVARS];
	esmscrtypeinfo_t m_LongVars[ESMSCR_MAX_LOCALVARS];
	esmscrtypeinfo_t m_FloatVars[ESMSCR_MAX_LOCALVARS];
	int m_NumShortVars;
	int m_NumLongVars;
	int m_NumFloatVars;

	/* Compile warning/error options */
	emscrmsglevel_t m_MsgLevels[ESMSCR_MAX_MESSAGES];
	int m_NumMsgLevels;

#if MWEDIT_SCRIPT_MWSE

	CSString m_refObject;

	/* Extended function param stack */
	std::stack<esmscrstack_t *> m_ArgXStack;

	/* Extended function result queue */
	std::queue<esmscrstack_t *> m_LetQueue;

	/* Extended function if stack */
	std::stack<esmscrifblock_t *> m_XIfStack;

#endif

	/* Expression stack */
	CGenStack m_ExprStack;
	int m_NumOutputExpr;

	char *m_pLocalVarData;  /* Holds the local variable block data */
	int m_LocalVarDataSize;

	char m_ScriptData[ESMSCR_DATA_SIZE];
	int m_ScriptDataSize;
	int m_LastLineDataPos;
	int m_LastIfPos;
	int m_LastSetPos;
	int m_NumSetExpr;
	bool m_IsEmptyIf;
	bool m_LastSetSymbol;
	bool m_IsSetExpr;
	bool m_OutputFuncIDRef;
	int m_LastMsgBoxBut;
	int m_LastMsgBoxArgs;
	int m_NumMsgButtons;
	int m_NumMsgArgs;
	int m_ManyArgPos;
	bool m_LastFuncArgSymbol;
	int m_FuncOptCount;
	int m_FuncOptPos;
	int m_StatementCount;

	CGenStack m_IfStatementStack; /* Tracks statement count for if statements */


	/* Add a local variable to the defined array */
	bool AddLocalVar(const TCHAR *pName, const int Type);

	/* Add compiled script data */
	bool AddScriptData(const void *pData, const int Size);
	bool InsertScriptDataRef(const TCHAR *pData, int Size);

	/* Adds an if statement block data to the stack */
	bool AddIfBlock(const int StatementCount, const int ScriptPos);

	/* Add error or warning messages */
	void AddError(const TCHAR *pString, ...);
	void AddWarning(const TCHAR *pString, ...);
	bool AddMessage(const int MessageID, const TCHAR *pString, ...);

	/* Ensure that the current token is the given type */
	int AssertToken(const int Token);
	int AssertToken(const int Token1, const int Token2);

	/* Checks to see if given function argument ID is valid */
	bool CheckFuncID(const long long ArgFlags, const TCHAR *pID, const bool Optional);
	bool CheckFuncID1(const long long ArgFlags, const TCHAR *pID, const bool Optional);

	/* Checks if the current function parameter/argument is valid */
	int CheckFuncArg();

	/* Delete any objects that remain in the expression stack */
	void ClearExprStack();
	void ClearIfStatementStack();

	/* Find a record in the parent document or extra file */
	CEsmRecord *FindRecord(const char *pID);
	CEsmRecord *FindRecord(const char *pID, const char *pType);
	CEsmRecord *FindRecordCarryable(const char *pID);

	/* Find various symbols */
	bool FindLocalVar(const TCHAR *pName);
	int FindLocalVarIndex(const TCHAR *pName, char &Type);
	int GetGlobalType(const TCHAR *pName);
	CEsmGlobal *GetGlobal(const TCHAR *pName);
	bool IsSymbolID(CSString& Token);
	short GetAnimGroupID(const TCHAR *pString);

	/* Converts a function argument ID type flags to a string */
	const TCHAR *GetFuncArgIDType(const long long FuncArgs);
	const TCHAR *GetFuncArgRefType(const long long FuncArgs);

	/* Generates the script local variable data block */
	void MakeScriptVarData();
	int ComputeLocalVarDataSize();

	/* Get the top if statement block from the stack */
	esmscrifblock_t *PopIfBlock();


  public:
	/* Class Constructors/Destructors */
	CEsmScriptCompile();
	virtual ~CEsmScriptCompile() {
		Destroy();
	}

	virtual void Destroy();

	/* Delete all the current compiler errors */
	void ClearErrors();

	/* Main access method */
	int Compile();

	/* Find the message level corresponding to the given message ID */
	int FindMsgLevel(const int MessageID);

	/* Get class members */
	char *GetLocalVarData() {
		return m_pLocalVarData;
	}

	char *GetScriptData() {
		return m_ScriptData;
	}

	const TCHAR *GetScriptName() {
		return m_ScriptName;
	}

	int GetScriptDataSize() {
		return m_ScriptDataSize;
	}

	int GetLocalVarDataSize() {
		return m_LocalVarDataSize;
	}

	int GetNumShortLocals() {
		return m_NumShortVars;
	}

	int GetNumLongLocals() {
		return m_NumLongVars;
	}

	int GetNumFloatLocals() {
		return m_NumFloatVars;
	}

	int GetNumErrors() {
		return m_NumErrors;
	}

	int GetNumWarnings() {
		return m_NumWarnings;
	}

	bool HasScriptName() {
		return !m_ScriptName.IsEmpty();
	}

	/* Access the extra file member */
	static CEsmFile &GetExtraFile() {
		return m_ExtraFile;
	}

	CEsmScriptErrArray *GetErrorArray() {
		return &m_ErrorArray;
	}

	esmscrfuncinfo_t *GetCurrentFunc() {
		return m_pCurrentFunc;
	}

	int GetNumFuncArgs() {
		return m_NumFuncArgs;
	}

	int GetLastFuncArg() {
		return m_LastFuncArg;
	}

	int GetFuncArgIndex() {
		return m_FuncArgIndex;
	}

	CSString *GetToken() {
		return &m_Token;
	}

	int GetTokenID() {
		return m_TokenID;
	}

	int GetCurrentChar() {
		return m_CurrentCharPos;
	}

	int GetCurrentLine() {
		return m_CurrentLine;
	}

	/* Initialize the extra record map */
	static void InitializeExtraRecords();

	/* Parse table callback functions */
	int ParseNewLocalVar();
	int ParseFuncRef();
	int ParseVarRef();
	int ParseIfVarRef();
	int ParseVarRef1(const bool InIf);
	int ParseStringID();
	int ParseStringIDSet();
	int ParseStringIDIf();
	int ParseStringIDPush();
	int ParsePushStringID();
	int ParseLineStringID() {
		m_StatementCount++;
		return ParseStringID();
	}

	int ParseFunctionLine() {
		m_StatementCount++;
		return ESMSCR_RESULT_OK;
	}

	int ParseSymbolID();
	int ParsePushSymbolID();
	int ParseLineSymbolID() {
		m_StatementCount++;
		return ParseSymbolID();
	}

	int ParseFuncArg();
	int ParseCheckFuncArg();
	int ParseChoiceFunction();
	int ParseFunction();
	int ParseFuncArg1();
	int ParseFuncComma();
	int ParseFuncEnd();
	int ParseRExprStart();
	int ParseIfRExprStart();
	int ParsePushToken();
	int ParseFuncAddOp();
	int ParseSetFirstAddOp();

	/* Character type functions */
	bool IsParseDigit() {
		return (m_pCharTypes[(*m_pParse) & 0xFF] & ESMSCR_CHARTYPE_DIGIT) != 0;
	}

	bool IsParseOperator() {
		return (m_pCharTypes[(*m_pParse) & 0xFF] & ESMSCR_CHARTYPE_PUNCT) != 0;
	}

	bool IsParseSymbol() {
		return (m_pCharTypes[(*m_pParse) & 0xFF] & ESMSCR_CHARTYPE_SYMBOL) != 0;
	}

	bool IsParseSymbolF() {
		return (m_pCharTypes[(*m_pParse) & 0xFF] & ESMSCR_CHARTYPE_SYMBOLF) != 0;
	}

	bool IsParseComment() {
		return *m_pParse == ESMSCR_CHAR_COMMENT;
	}

	bool IsParseStringChar() {
		return *m_pParse == ESMSCR_CHAR_STRING;
	}

	bool IsParseWhiteSpace() {
		return (m_pCharTypes[(*m_pParse) & 0xFF] & ESMSCR_CHARTYPE_SPACE) != 0;
	}

	/* Get/skip the base token types */
	int GetNextToken();
	int GetNumberToken();
	int GetOperatorToken();
	int GetStringToken();
	int GetSymbolToken();
	void SkipTokenComment();
	void SkipTokenWhiteSpace();

	/* Output table callback methods */
	int OutputToken(const short Value);
	int OutputOneExpr();
	int OutputEnd() {
		m_StatementCount++;
		return OutputToken(0x0101);
	}

	int OutputEndWhile();
	int OutputIf();
	int OutputElseIf();
	int OutputElse();
	int OutputEndIf();
	int OutputWhile();
	int OutputWhileFinish();
	int OutputReturn() {
		m_StatementCount++;
		return OutputToken(0x0124);
	}

	int OutputSet();
	int OutputObjRef() {
		return OutputToken(0x010c);
	}

	int OutputIfLocal();
	int OutputIfGlobal();
	int OutputIfRelOp();
	int OutputIfRAddOp();
	int OutputIfRNumber();
	int OutputIfRLocal();
	int OutputIfRGlobal();
	int OutputIfEmpty();
	int OutputIfFinish();
	int OutputIfFunction();
	int OutputSetLocal();
	int OutputSetGlobal();
	int OutputSetEnd();
	int OutputExprStack();
	int OutputIfLeftExprStack();
	int OutputIfRightExprStack();
	int OutputFunction();
	int OutputLineFunction();
	int OutputFuncArgXYZ();
	int OutputFuncArgNum();
	int OutputFuncArgGlobal();
	int OutputFuncArgLocal();
	int OutputFuncArgStrSym();
	int OutputFuncArgSym();
	int OutputFuncArgString();
	int OutputFuncArgReset();
	int OutputFuncEnd();
	int OutputScriptName() {
		m_ScriptName = m_Token;
		return 0;
	}

	int OutputFuncArgAnim(const short AnimID) {
		return AddScriptData(&AnimID, 2);
	}

	int OutputEffect(const int EffectID);


#if MWEDIT_SCRIPT_MWSE

	int ParseFuncArgX();

	/* Fake output functions, the tokens are stored in a stack to be output in the correct order */
	int PushFuncXArgLocal();
	int PushFuncXArgNum();
	int PushFuncXArgString();
	int PushLetLocal();
	int PushFuncOp();

	/* Output extended function params from the stack */
	int OutputFuncOp();
	int OutputStoredFuncOp();
	int WriteFuncOp(const TCHAR *ident);
	int OutputFuncXArgLocal(const TCHAR *name);
	int OutputFuncXArgNum(int type, const TCHAR *token);
	char *OutputFuncXArgStringCat(char *buf, const void *newdata, int newdatalen);
	int OutputFuncXArgString(const TCHAR *token);
	int OutputFuncXBlock();
	int OutputLetEnd();
	int PushFuncXArg(int type, const TCHAR *token);

	/* Output extended if commands */
	int OutputXIf();
	int OutputXElse();
	int OutputXElseIf();
	int OutputXEndIf();
#endif

	/* Output extended while commands */
	int OutputXWhile();
	int OutputXEndWhile();

	/* Parse the given table */
	int ParseTable(esmscrparsetable_t *pTable);
	int ParseTableMany(esmscrparsetable_t &TableEntry);
	int ParseTableOne(esmscrparsetable_t &TableEntry);

	/* Set various message levels */
	void SetDefaultMsgLevels();
	void SetWeakMsgLevels();
	void SetStrongMsgLevels();

	/* Set the script text to be compiled */
	void SetScriptText(const TCHAR *pString, const int Size);

	/* Set class members */
	void SetDocument(CMWEditDoc *pDoc) {
		m_pDocument = pDoc;
	}

	void SetMsgLevel(const int Type);

	/* Updates the statement count from the previous if block */
	int UpdateLastIfBlock();
};


#endif
