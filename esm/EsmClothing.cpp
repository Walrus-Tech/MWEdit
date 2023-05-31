/*===========================================================================
 *
 * File:	EsmClothing.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "EsmClothing.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
  DEFINE_FILE("EsmClothing.cpp");
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmClothing::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_FNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MODL,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_ITEX,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_SCRI,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_ENAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_CTDT,	CEsmSubCTDT::Create },
	{ MWESM_SUBREC_INDX,	CEsmSubByte::Create },
	{ MWESM_SUBREC_BNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_CNAM,	CEsmSubNameFix::Create },
	{ NULL,			CEsmSubRecord::Create }	/* Must be last record */
 };
/*===========================================================================
 *		End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Clothing Type Array
 *
 *=========================================================================*/
const TCHAR* l_ClothTypes[] = {
	_T("Pants"),
	_T("Shoes"),
	_T("Shirt"),
	_T("Belt"),
	_T("Robe"),
	_T("R. Glove"),
	_T("L. Glove"),
	_T("Skirt"),
	_T("Ring"),
	_T("Amulet")
 };
/*===========================================================================
 *		End of Local Clothing Type Array
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Constructor
 *
 *=========================================================================*/
CEsmClothing::CEsmClothing () {
  //DEFINE_FUNCTION("CEsmClothing::CEsmClothing()");
  m_pClothData	= NULL;
 }
/*===========================================================================
 *		End of Class CEsmClothing Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmClothing::Destroy (void) {
  //DEFINE_FUNCTION("CEsmClothing::Destroy()");
  m_pClothData	= NULL;

  CEsmItem3::Destroy();
 }
/*===========================================================================
 *		End of Class Method CEsmClothing::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmClothing::CompareFields (const int FieldID, CEsmRecord* pRecord) {
  DEFINE_FUNCTION("CEsmClothing::CompareFields()");
  CEsmClothing* pCloth;

	/* Ensure the correct type */
  if (!pRecord->IsType(MWESM_REC_CLOT)) return CEsmItem3::CompareFields(FieldID, pRecord);
  pCloth = (CEsmClothing *) pRecord;

  switch (FieldID) {
    case ESM_FIELD_TYPE:
	return StringCompare(GetClothType(), pCloth->GetClothType(), FALSE);
    default:
	return CEsmItem3::CompareFields(FieldID, pRecord); 
   }
 }
/*===========================================================================
 *		End of Class Method CEsmClothing::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord* CEsmClothing::Create (void) {
  DEFINE_FUNCTION("CEsmClothing::Create()");
  CEsmRecord* pRecord;

  CreatePointer(pRecord, CEsmClothing);
  return (pRecord);
 }
/*===========================================================================
 *		End of Class Method CEsmClothing::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmClothing::CreateNew (CEsmFile* pFile) {

	/* Call the base class record first */
  CEsmItem3::CreateNew(pFile);

	/* Create the item sub-records */
  AllocateSubRecord(MWESM_SUBREC_CTDT);
  m_pClothData->CreateNew();
 }
/*===========================================================================
 *		End of Class Method CEsmClothing::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmClothing Method - const GetArmorType (void) const;
 *
 * Returns the armor type as a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR* CEsmClothing::GetClothType (void) { 
  if (GetClothData() == NULL) return _T("Unknown");
  return (GetESMClothType(GetClothData()->Type)); 
 }
/*===========================================================================
 *		End of Class Method TCHAR* CEsmClothing::GetArmorType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmClothing Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR* CEsmClothing::GetFieldString (const int FieldID) {

  switch (FieldID) {
    case ESM_FIELD_TYPE:
	return (GetClothType());
    default:
	return CEsmItem3::GetFieldString(FieldID);
   }
  
 }
/*===========================================================================
 *		End of Class Method TCHAR* CEsmClothing::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmClothing::OnAddSubRecord (CEsmSubRecord* pSubRecord) {

  if (pSubRecord->IsType(MWESM_SUBREC_CTDT))
    m_pClothData = (CEsmSubCTDT *) pSubRecord;
  else
    CEsmItem3::OnAddSubRecord(pSubRecord);

 }
/*===========================================================================
 *		End of Class Event CEsmClothing::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmClothing Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmClothing::SetFieldValue (const int FieldID, const TCHAR* pString) {

  switch (FieldID) { 
    case ESM_FIELD_TYPE:
	int Type = GetESMClothType(pString);
	if (Type >= 0) SetClothType(Type);
	return (true);
   };

	/* No matching field found */
  return CEsmItem3::SetFieldValue(FieldID, pString);
 }
/*===========================================================================
 *		End of Class Method CEsmClothing::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const TCHAR* GetESMClothType (ClothType);
 *
 * Converts an cloth type value into a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR* GetESMClothType (const int ClothType) {

	/* Check for a valid armor type */
  if (ClothType < MWESM_CLOTHTYPE_MIN || ClothType > MWESM_CLOTHTYPE_MAX)  return _T("Unknown");

	/* Return the armor type string from the name array */
  return l_ClothTypes[ClothType];
 }


bool GetESMClothType (int& OutIndex, const TCHAR* pString) {
  int Index;

	/* Check for a valid armor type */
  for (Index = MWESM_CLOTHTYPE_MIN; Index <= MWESM_CLOTHTYPE_MAX; Index++) {
    if ( _stricmp(l_ClothTypes[Index], pString) == 0) {
      OutIndex = Index;
      return (true);
     }
   }

  return (false);
 }


int GetESMClothType (const TCHAR* pString) {
  int Index;
  if (!GetESMClothType (Index, pString)) Index = MWESM_CLOTHTYPE_MIN;
  return (Index);
 }
/*===========================================================================
 *		End of Function TCHAR* GetESMClothType()
 *=========================================================================*/


