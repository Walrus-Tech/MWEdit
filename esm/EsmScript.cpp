/*===========================================================================
 *
 * File:	EsmScript.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	February 3, 2003
 *
 * Description
 *
 * 6 October 2003
 *	- Added the IsUsed() method for checking record uses.
 *
 *=========================================================================*/

	/* Include Files */
#include "EsmScript.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
  DEFINE_FILE("EsmScript.cpp");
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmScript::s_SubRecCreate[] = {
	{ MWESM_SUBREC_SCHD,	CEsmSubSCHD::Create },
	{ MWESM_SUBREC_SCVR,	CEsmSubRecord::Create },
	{ MWESM_SUBREC_SCDT,	CEsmSubRecord::Create },
	{ MWESM_SUBREC_SCTX,	CEsmSubName::Create },
	{ NULL,			CEsmSubRecord::Create }	/* Must be last record */
 };
/*===========================================================================
 *		End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Constructor
 *
 *=========================================================================*/
CEsmScript::CEsmScript () {
  //DEFINE_FUNCTION("CEsmScript::CEsmScript()");
  m_pScriptHeader = NULL;
  m_pScriptVars   = NULL;
  m_pScriptText   = NULL;
  m_pScriptData   = NULL;
 }
/*===========================================================================
 *		End of Class CEsmScript Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmScript::Destroy (void) {
  //DEFINE_FUNCTION("CEsmScript::Destroy()");
  m_pScriptHeader = NULL;
  m_pScriptVars   = NULL;
  m_pScriptText   = NULL;
  m_pScriptData   = NULL;
  CEsmRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CEsmScript::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - void ClearCompileData (void);
 *
 * Clears any compiled information in the script.
 *
 *=========================================================================*/
void CEsmScript::ClearCompileData (void) {

	/* Reset the header data */
  if (m_pScriptHeader != NULL) {
    m_pScriptHeader->GetScriptHeadData()->LocalVarSize   = 0;
    m_pScriptHeader->GetScriptHeadData()->ScriptDataSize = 0;
    m_pScriptHeader->GetScriptHeadData()->NumShorts      = 0;
    m_pScriptHeader->GetScriptHeadData()->NumLongs       = 0;
    m_pScriptHeader->GetScriptHeadData()->NumFloats      = 0;
   }

	/* Reset the compiled script data */
  if (m_pScriptData != NULL) {
    m_pScriptData->CopyData(NULL, 0);
   }

 }
/*===========================================================================
 *		End of Class Method CEsmScript::ClearCompileData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmScript::CompareFields (const int FieldID, CEsmRecord* pRecord) {
  CEsmScript* pScript;

	/* Ensure the correct type */
  if (!pRecord->IsType(MWESM_REC_SCPT)) return CEsmRecord::CompareFields(FieldID, pRecord);
  pScript = (CEsmScript *) pRecord;

  switch (FieldID) {
    case ESM_FIELD_ID:
	return StringCompare(GetID(), pScript->GetID(), false);
    case ESM_FIELD_VALUE:
        return GetScriptSize() - pScript->GetScriptSize();
    default:
	return CEsmRecord::CompareFields(FieldID, pRecord); 
   }
 }
/*===========================================================================
 *		End of Class Method CEsmScript::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord* CEsmScript::Create (void) {
  DEFINE_FUNCTION("CEsmScript::Create()");
  CEsmRecord* pRecord;

  CreatePointer(pRecord, CEsmScript);
  return (pRecord);
 }
/*===========================================================================
 *		End of Class Method CEsmScript::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmScript::CreateNew (CEsmFile* pFile) {

	/* Call the base class record first */
  CEsmRecord::CreateNew(pFile);

	/* Create the item sub-records */
  AllocateSubRecord(MWESM_SUBREC_SCHD);
  AllocateSubRecord(MWESM_SUBREC_SCVR);
  AllocateSubRecord(MWESM_SUBREC_SCDT);
  AllocateSubRecord(MWESM_SUBREC_SCTX);

  m_pScriptVars->CreateNew();
  m_pScriptData->CreateNew();
  m_pScriptHeader->CreateNew();
 }
/*===========================================================================
 *		End of Class Method CEsmScript::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - bool ExportScript (pPath);
 *
 * Exports the script to a text file using the name of the script ID to
 * the given path (files automatically overwritten). Returns false on 
 * any error.
 *
 *=========================================================================*/
bool CEsmScript::ExportScript (const TCHAR* pPath) {
  bool  Result;
  TCHAR Filename[_MAX_PATH+64];

	/* Create the output filename */
  snprintf (Filename, _MAX_PATH+40, _T("%s%s.txt"), pPath, GetID());

	/* Output the script text */
  Result = WriteFile((const byte*)GetScriptText(), GetScriptSize(), Filename, false);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CEsmScript::ExportScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - short FindLocalVar (pLocalVar, VarType);
 *
 *=========================================================================*/
short CEsmScript::FindLocalVar (const TCHAR* pLocalVar, char& VarType) {
  scriptheaddata_t* pHeader;
  char*		 pParse;
  int		 DataIndex;
  int		 Length;
  int		 TypeIndex;
  bool		 IsShort = false;
  bool		 IsLong  = false;
  bool		 IsFloat = false;

	/* Get the variable data sub-record */
  if (m_pScriptVars == NULL || m_pScriptHeader == NULL) return (-1);
  pParse = (char *) m_pScriptVars->GetData();
  pHeader = m_pScriptHeader->GetScriptHeadData();
  if (pParse == NULL || pHeader == NULL) return (-1);
  DataIndex = 0;
  TypeIndex = 0;

  if (pHeader->NumShorts == 0) {
    if (pHeader->NumLongs == 0) {
      IsFloat = true;
      VarType = 'f';
     }
    else {
      IsLong = true;
      VarType = 'l';
     }
   }
  else {
    IsShort = true;
    VarType = 's';
   }

  while (DataIndex < m_pScriptVars->GetRecordSize()) {
    Length = strlen(pParse);
    if ( _stricmp(pLocalVar, pParse) == 0) return(TypeIndex + 1);
    pParse    += Length + 1;
    DataIndex += Length + 1;

    TypeIndex++;

    if (IsShort) {
      if (TypeIndex >= pHeader->NumShorts) {
        TypeIndex = 0;
        if (pHeader->NumLongs == 0) {
          IsFloat = true;
	  IsShort = false;
          VarType = 'f';
         }
        else {
          IsLong  = true;
	  IsShort = false;
          VarType = 'l';
         }
       }
     }
    else if (IsLong) {
      if (TypeIndex >= pHeader->NumLongs) {
        TypeIndex = 0;
        IsFloat = true;
	IsLong  = false;
        VarType = 'f';
       }
     }
    else if (IsFloat) {
      if (TypeIndex >= pHeader->NumFloats) break;
    }
   }
  
  return (-1);
 }
/*===========================================================================
 *		End of Class Method CEsmScript::FindLocalVar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmScript Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR* CEsmScript::GetFieldString (const int FieldID) {
  static TCHAR s_Buffer[32];

  switch (FieldID) {
    case ESM_FIELD_ID:
    	return (GetID());
    case ESM_FIELD_VALUE:
        snprintf (s_Buffer, 31, _T("%d"), GetScriptSize());
        return s_Buffer;
    default:
	return CEsmRecord::GetFieldString(FieldID);
   }
  
 }
/*===========================================================================
 *		End of Class Method TCHAR* CEsmScript::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Method - bool IsUsed (pID);
 *
 * Sees if the given ID is used by the given script.
 *
 *=========================================================================*/
bool CEsmScript::IsUsed (const TCHAR* pID) { 
  const char* pData;
  const char* pCheckData;
  int	      FindIndex;
  int	      IDSize = SafeStrLen(pID);
  
	/* Ignore if there is nothing to look at */
  if (m_pScriptData == NULL) return (false);
  pData = (const char *) m_pScriptData->GetData();
  FindIndex = 0;

  while (FindIndex >= 0) {

		/* Attempt to find the next occurence, if any */
    FindIndex = memisearch(pData, pID, m_pScriptData->GetRecordSize(), IDSize, FindIndex);
    if (FindIndex < 0) break;

		/* Ignore if we are at the very start of the buffer */
    if (FindIndex < 1) {
      FindIndex++;
      continue;
     }

    pCheckData = pData + FindIndex - 1;

		/* Plain string, exact length */
    if (pCheckData[0] == IDSize) {
      return (true);
     }	
		/* Special short variables */
    else if (pCheckData[0] == 4 && IDSize < 4) {
      if (memcmp(pData + FindIndex + IDSize, _T("\0\0\0\0\0"), 4 - IDSize) == 0) return (true);
     }	
    
    FindIndex++;
   }

  return (false);
 }
/*===========================================================================
 *		End of Class Method CEsmScript::IsUsed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmScript Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmScript::OnAddSubRecord (CEsmSubRecord* pSubRecord) {

  if (pSubRecord->IsType(MWESM_SUBREC_SCHD))
    m_pScriptHeader = (CEsmSubSCHD *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_SCVR))
    m_pScriptVars = pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_SCDT))
    m_pScriptData = pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_SCTX))
    m_pScriptText = (CEsmSubName *)pSubRecord;
  else
    CEsmRecord::OnAddSubRecord(pSubRecord);

 }
/*===========================================================================
 *		End of Class Event CEsmArmor::CEsmScript()
 *=========================================================================*/


