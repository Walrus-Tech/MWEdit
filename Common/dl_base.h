/*===========================================================================
 *
 * File:	DL_Base.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	Sunday, April 01, 2001
 *
 * Contains common definitions, types, etc... for Dave's Library of common
 * code.
 *
 * 18 September 2003
 *	- Added the DL_RGB() macro.
 *	- Added the TSTRCAT() macro.
 *
 *=========================================================================*/
#ifndef __DL_BASE_H
#define __DL_BASE_H


/*===========================================================================
 *
 * Begin Windows Pragmas
 *
 * Some windows specific pragma directives to eliminate some annoying
 * level 4 warnings.
 *	4514 = Unused inline function has been removed
 *	4512 = Assignment operator could not be generated
 *	
 *=========================================================================*/
#if defined(_WIN32)
  #pragma warning( disable : 4514 )
  #pragma warning( disable : 4512 )
#endif
/*===========================================================================
 *		End of Windows Pragmas
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Include Files
 *
 *=========================================================================*/
  #include <stdlib.h>
  #include <stdio.h>
  #include <limits.h>
/*===========================================================================
 *		End of Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin File Identification
 *
 * Definitions for identifying the file.
 *
 *=========================================================================*/
  #define DL_BASE_NAME    "DL_Base.cpp"
  #define DL_BASE_VERSION "0.01d"
  #define DL_BASE_AUTHOR  "Dave Humphrey"
  #define DL_BASE_EMAIL   "uesp@m0use.net"
  #define DL_BASE_DATE    "1 April 2001"
/*===========================================================================
 *		End of File Identification
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enable Debug Memory Handler for Windows
 *
 * By including "crtdgb.h" 
 *
 *=========================================================================*/
#if defined(_DEBUG) && defined(_WIN32) && !defined(__BCPLUSPLUS__) && !defined(_WIN32_WCE)
  //#define _CRTDBG_MAP_ALLOC
  #include "crtdbg.h"
#endif

#if defined(_WIN32_WCE)
  //#include "dbgapi.h"
#endif
/*===========================================================================
 *		End of Enable Debug Memory Handler for Windows
 *=========================================================================*/


/*===========================================================================
 *
 * Begin System Specific Creation Macros
 *
 * Macros to help create system specific commands.
 *
 *=========================================================================*/
#if defined(__MSDOS__)
  #define SYS_MSDOS(Cmd) Cmd
  #define SYS_WIN32(Cmd)
  #define SYS_UNIX(Cmd)  
  #define SYS_NONE(Cmd)
#elif defined(_WIN32)
  #define SYS_MSDOS(Cmd) 
  #define SYS_WIN32(Cmd) Cmd
  #define SYS_UNIX(Cmd) 
  #define SYS_NONE(Cmd)
#else
  #define SYS_MSDOS(Cmd) 
  #define SYS_WIN32(Cmd)
  #define SYS_UNIX(Cmd)
  #define SYS_NONE(Cmd) Cmd  
#endif
/*===========================================================================
 *		End of System Specific Creation Macros
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Time Stamp Macro
 *
 * Various compilers have different definitions for the time stamp.
 *
 *=========================================================================*/
#if defined(__TURBOC__)
  #define __DL_TIMESTAMP__ __TIME__
#elif defined(_WIN32)
  #define __DL_TIMESTAMP__ __TIMESTAMP__
#endif
/*===========================================================================
 *		End of Time Stamp Macro
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Various Keyword Definitions
 *
 *=========================================================================*/
#if defined(_WIN32)
  #define ASM __asm
  #define interrupt 
#elif defined(__TURBOC__)  
  #define ASM asm
#endif
/*===========================================================================
 *		End of Various Keyword Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Boolean Type Definition
 *
 * Define the standard boolean type if not previously defined. Use
 * unsigned char to match that used in MSVC++. 
 *
 *=========================================================================*/
#if defined(_WIN32)
  //typedef bool boolean;
  //#define TRUE  true
  //#define FALSE false
  #define __BOOLEAN_DEF
  typedef unsigned char boolean;  

  #if !defined(TRUE)
    #define TRUE  1
    #define FALSE 0
  #endif

#else
  #define __BOOLEAN_DEF
  typedef unsigned char boolean;  

  #if !defined(TRUE)
    #define TRUE  ((boolean)1)
    #define FALSE ((boolean)0)
  #endif

#endif
/*===========================================================================
 *		End of Boolean Type Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Misc. Macro Definitions
 *
 *=========================================================================*/

  #define DL_RGB(r, g ,b)  ((DWORD) (((BYTE) (r) | \
				((WORD) (g) << 8)) | \
				(((DWORD) (BYTE) (b)) << 16))) 
  #define DL_RED(color)   ((BYTE) ((color)&0xFF))
  #define DL_GREEN(color) ((BYTE) (((color)>>8)&0xFF))
  #define DL_BLUE(color)  ((BYTE) (((color)>>16)&0xFF))
 
/*===========================================================================
 *		End of Misc. Macro Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Basic Type Definitions
 *
 * Define the basic, non-standard, types commonly used.
 *
 *=========================================================================*/
  typedef unsigned char  byte;
  typedef unsigned char  uchar;
  typedef unsigned short ushort;
  typedef unsigned int   uint;
  typedef unsigned int   word;
  typedef unsigned long  ulong;
  typedef unsigned long  dword;

  // TODO redefinition
  //#define WORD_MAX  UINT_MAX
  //#define DWORD_MAX ULONG_MAX

	/* Define the TCHAR type if required */
#if defined(_WIN32) && !defined(__BORLANDC__)
  #include <tchar.h>
#else
  #if !defined(_TCHAR_DEFINED)
    #if defined(_UNICODE)
      typedef wchar_t TCHAR;
    #else
      typedef char TCHAR;
    #endif
    #define _TCHAR_DEFINED 1
  #endif

	/* Define the custom _T() macro for wide/single byte strings */
  #if !defined(_T)
    #if defined(_UNICODE)
      #define _T(text) L##text
    #else
      #define _T(text) text
    #endif
  #endif
#endif

	/* Basic string-tchar definitions as required */
#if defined(_UNICODE)
  #if defined(_WIN32)
    #define TSTRLEN(string) _tcslen(string)
    #define TSTRCMP(string1, string2) _tcscmp(string1, string2)
    #define  _stricmp(string1, string2) _tcsicmp(string1, string2)
    #define TSTRCPY(string1, string2) _tcscpy(string1, string2)
    #define TSTRCAT(string1, string2) _tcscat(string1, string2)
    #define TSTRCHR(string, char1) _tcschr(string, (TCHAR)char1)
    #define TSTRRCHR(string, char1) _tcsrchr(string, (TCHAR)char1)
    #define TSTRTOK(string1, string2) _tcstok(string1, string2)
    #define TSTRNCMP(string1, string2, length) _tcsncmp(string1, string2, length)
    #define TSTRNICMP(string1, string2, length) _tcsnicmp(string1, string2, length)
    #define TSTRSTR(string1, string2) _tcsstr(string1, string2)
    #define TFPRINTF _ftprintf
    #define TSTRNCAT(string1, string2, length) _tcsncat(string1, string2, length)
    #define TSTRNCPY(string1, string2, length) strnncpy(string1, string2, length)
    #define TFOPEN(Filename, mode) _tfopen(Filename, mode)
    #define TSTRFTIME(string1, length1, string2, time1) _tcsftime(string1, length1, string2, time1)
    #define TFPUTC(Char, Handle) _fputtc(Char, Handle)
    #define TPRINTF _tprintf
    #define TVPRINTF _vtprintf
    #define TVFPRINTF _vftprintf
    #define TISSPACE(char1) _istspace(char1)
    #define TISDIGIT(char1) _istdigit(char1)
    #define TISALPHA(char1) _istalpha(char1)
    #define TISLOWER(char1) _istlower(char1)
    #define TISUPPER(char1) _istupper(char1)
    #define TISPRINT(char1) _istprint(char1)
    #define TISSPACE(char1) _istspace(char1)
    #define TISXDIGIT(char1) _istxdigit(char1)
    #define TSTRTOL(string, ptr, base) _tcstol(string, ptr, base)
    #define TSTRTOD(string, ptr) _tcstod(string, ptr)
    #define TTOUPPER(char1) towupper(char1)
    #define TTOLOWER(char1) towlower(char1)
  #endif
#else
  #define TSTRCPY(string1, string2) strcpy(string1, string2)
  #define TSTRCAT(string1, string2) strcat(string1, string2)
  #define TSTRCMP(string1, string2) strcmp(string1, string2)
  #define  _stricmp(string1, string2) stricmp(string1, string2)
  #define TSTRLEN(string) strlen(string)
  #define TSTRCHR(string, char1) strchr(string, char1)
  #define TSTRRCHR(string, char1) strrchr(string, char1)
  #define TSTRTOK(string1, string2) strtok(string1, string2)
  #define TSTRNCMP(string1, string2, length) strncmp(string1, string2, length)
  #define TSTRNICMP(string1, string2, length) strnicmp(string1, string2, length)
  #define TSTRNCPY(string1, string2, length) strnncpy(string1, string2, length)
  #define TSTRSTR(string1, string2) strstr(string1, string2)
  #define TFPRINTF fprintf
  #define TSTRNCAT(string1, string2, length) strncat(string1, string2, length)
  #define TFOPEN(Filename, mode) fopen(Filename, mode)
  #define TSTRFTIME(string1, length1, string2, time1) strftime(string1, length1, string2, time1)
  #define TFPUTC(Char, Handle) fputc(Char, Handle)
  #define TPRINTF printf
  #define TVPRINTF vprintf
  #define TVFPRINTF vfprintf
  #define TISSPACE(char1) isspace(char1)
  #define TISDIGIT(char1) isdigit(char1)
  #define TISALPHA(char1) isalpha(char1)
  #define TISLOWER(char1) islower(char1)
  #define TISUPPER(char1) isupper(char1)
  #define TISPRINT(char1) isprint(char1)
  #define TISSPACE(char1) isspace(char1)
  #define TISXDIGIT(char1) isxdigit(char1)
  #define TSTRTOL(string, ptr, base) strtol(string, ptr, base)
  #define TSTRTOD(string, ptr) strtod(string, ptr)
  #define TTOUPPER(char1) toupper(char1)
  #define TTOLOWER(char1) tolower(char1)
#endif

	/* The type for the new qsort() user compare function */
  typedef int (_cdecl* PQSORT_CMPFUNC)      (const void* pElem1, const void* pElem2, const long lUserData );
  typedef int (_cdecl* PQSORT_CMPFUNC_ORIG) (const void* pElem1, const void* pElem2);

/*===========================================================================
 *		End of Basic Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definition Macro
 *
 * Use this macro at the beginning of a function to store the function
 * name as a static string allowing the output of the function name
 * in debugging messages.  The string only exists in debug builds and is
 * an empty string in release builds.  
 *
 *=========================================================================*/
#if defined(_DEBUG)
  #define DEFINE_FUNCTION(FuncString) static TCHAR ThisFunction[] = _T(FuncString);
  extern TCHAR ThisFunction[10];
#else
  //#define DEFINE_FUNCTION(FuncString) static char ThisFunction[] = "";
  #define DEFINE_FUNCTION(FuncString)
  #define ThisFunction _T("")
#endif
/*===========================================================================
 *		End of Function Definition Macro
 *=========================================================================*/


/*===========================================================================
 *
 * Begin File Definition Macro
 *
 * Similar to the function macro above but for individual source files
 * instead.  Include the macro at the top of a file to create a static
 * string ThisFile for use in debug messages.  Only defined in debug builds.
 * Use the ThisFile string instead of __FILE__ to reduce the amount of 
 * global strings the program allocates.
 *
 *=========================================================================*/
  #define DEFINE_FILE(string) static TCHAR ThisFile[] = _T(string);

	/* Eliminates errors from not using the DEFINE_FILE() macro */
  extern TCHAR ThisFile[]; 
/*===========================================================================
 *		End of File Definition Macro
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Character Definitions
 *
 * Define commonly used character macros.
 *
 *=========================================================================*/
  #define NULL_CHAR ((TCHAR)'\0')
  #define DEL_CHAR  ((TCHAR)'\b')
  #define ESC_CHAR  ((TCHAR)'\x1B')
  #define LF_CHAR   ((TCHAR)'\n')
  #define CR_CHAR   ((TCHAR)'\r')
  #define TAB_CHAR  ((TCHAR)'\t')
  #define GARBAGE_CHAR  ((TCHAR)0xCC)
  #define BLOCKEND_CHAR ((TCHAR)0xFC)
  #define DEGREE_CHAR   ((TCHAR)248)
  #define MU_CHAR	((TCHAR)230)
/*===========================================================================
 *		End of Character Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin BIT Field Manipulation Macros
 *
 * Definitions to help manipulate bit flags.
 *
 *=========================================================================*/

  #define CHECK_BITFLAG(Variable, Flag) ( ((Variable) & (Flag)) != 0)
  #define STORE_BITFLAG(Variable, Flag) ((Variable) |=  (Flag))
  #define CLEAR_BITFLAG(Variable, Flag) ((Variable) &= ~(Flag))
  #define SET_BITFLAG(Variable, Flag, Bool) ((Bool) ? STORE_BITFLAG(Variable, Flag) : CLEAR_BITFLAG(Variable, Flag))

/*===========================================================================
 *		End of BIT Field Manipulation Macros
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Mathematical Constants
 *
 * Commonly used math constants accurate to 21 decimal places.
 *
 *=========================================================================*/
#if !defined(M_PI)
  #define M_E         2.71828182845904523536
  #define M_LOG2E     1.44269504088896340736
  #define M_LOG10E    0.434294481903251827651
  #define M_LN2       0.693147180559945309417
  #define M_LN10      2.30258509299404568402
  #define M_PI        3.14159265358979323846
  #define M_PI_2      1.57079632679489661923
  #define M_PI_4      0.785398163397448309616
  #define M_1_PI      0.318309886183790671538
  #define M_2_PI      0.636619772367581343076
  #define M_1_SQRTPI  0.564189583547756286948 
  #define M_2_SQRTPI  1.12837916709551257390
  #define M_SQRT2     1.41421356237309504880
  #define M_SQRT_2    0.707106781186547524401
  #define M_RAD2DEG   57.29577951
  #define M_DEG2RAD   0.017453292
#endif
/*===========================================================================
 *		End of Mathematical Constants
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Limit Fix Macros
 *
 *=========================================================================*/
  #define FIXLIMIT(Value, Min, Max) if ((Value) < (Min)) (Value) = (Min); else if ((Value) > (Max)) (Value) = (Max); 
/*===========================================================================
 *		End of Limit Fix Macros
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Assertion Definition
 *
 * Define the standard ASSERT type macros if not previously defined.
 *
 *=========================================================================*/
#if !defined(ASSERT)

  #if defined(DEBUG) || defined(__DEBUG) || defined(_DEBUG)
    #define ASSERT(exp)  { if (!(exp)) { CustomAssert(_T(#exp), ThisFile, ThisFunction, __LINE__); } }
    #undef TRACE
    #define TRACE(msg)   { SystemLog.Printf(_T("%s - %s"), ThisFunction, msg); }
    #define TRACE1(msg, exp)   { SystemLog.Printf(msg, exp); }
  #else
    #define ASSERT(exp)  { }
    #undef TRACE
    #define TRACE(msg)   { }
    #define TRACE1(msg, exp)   { }
  #endif

#endif

#if defined(DEBUG) || defined(__DEBUG) || defined(_DEBUG)
  #define IASSERT(exp) { if (!(exp)) { CustomAssert(_T(#exp), _T(""), _T(""), __LINE__); } }
  #define ABORT(msg)   { CustomAssert(msg, _T(""), __FILE__, __LINE__); }
  #define IFTRACE(exp, msg) { if (exp) SystemLog.Printf(_T("%s - %s"), ThisFunction, msg); }
#else
  #define IASSERT(exp) { }
  #define ABORT(exp)   { }
  #define IFTRACE(exp, msg) { }
#endif
/*===========================================================================
 *		End of Assertion Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* A custom assert procedure used by the ASSERT macro */
  void CustomAssert (const TCHAR* pString,   const TCHAR* pFile, 
		     const TCHAR* pFunction, const long  Line);

	/* Create the exception 'throw' function for DOS systems */
  #if defined(__TURBOC__) && !defined(__BCPLUSPLUS__)
    void throw (const char* pString);
  #endif

	/* Standard qsort() replacement */
  void qsort (void* pBase, size_t NumElements, size_t ElementWidth,
              PQSORT_CMPFUNC pCmpFunc, long lUserData );

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Inline Function - int l_QSortCompare (pElem1, pElem2);
 *
 * Inline function used by the improved qsort() algorithm.  This function
 * is the one passed onto, and called by, the standard qsort() function.
 * It then passes the call onto the extended compare function specified
 * by the used, along with the custom user data.
 *
 * Note: This function is included in the header only for the purpose
 * of defining it as inline, hopefully improving sort speeds.  Should
 * only be used by the qsort() routine in DL_BASE.CPP.  Similarily
 * with the defined local parameters.
 *
 *=========================================================================*/

	/* Local variables needed, do not use! */
extern long           l_QSortUserData;
extern PQSORT_CMPFUNC l_QSortCmpFunc;

inline int l_QSortCompare (const void* pElem1, const void* pElem2) {
  //DEFINE_FUNCTION("l_QSortCompare()");

	/* Pass the call onto the extended function */
  return l_QSortCmpFunc(pElem1, pElem2, l_QSortUserData);
 }
/*===========================================================================
 *		End of Function l_QSortCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Global Variable Definitions
 *
 *=========================================================================*/
  extern TCHAR LocalePathChar;
/*===========================================================================
 *		End of Global Variable Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File DL_Base.H
 *=========================================================================*/
