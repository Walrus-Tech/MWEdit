/*===========================================================================
 *
 * File:	EsmNpc.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	February 3, 2003
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "EsmNpc.h"
#include "EsmInfo.h"
#include "EsmSubPos6.h"
#include "utility/namelist.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
  DEFINE_FILE("EsmNpc.cpp");
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sub-Record Create Array
 *
 *=========================================================================*/
const esmsubreccreate_t CEsmNpc::s_SubRecCreate[] = {
	{ MWESM_SUBREC_NAME,	CEsmSubName::Create },
	{ MWESM_SUBREC_FNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_MODL,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_SCRI,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_ANAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_BNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_CNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_KNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_RNAM,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_NPDT,	CEsmSubNPDTL::Create },
	{ MWESM_SUBREC_FLAG,	CEsmSubLong::Create },
	{ MWESM_SUBREC_NPCO,	CEsmSubNPCO::Create },
	{ MWESM_SUBREC_NPCS,	CEsmSubNPCS::Create },
	{ MWESM_SUBREC_AIDT,	CEsmSubAIDT::Create },
	{ MWESM_SUBREC_AI_A,	CEsmSubAI_A::Create },
	{ MWESM_SUBREC_AI_E,	CEsmSubAI_E::Create },
	{ MWESM_SUBREC_AI_E,	CEsmSubAI_F::Create },
	{ MWESM_SUBREC_AI_T,	CEsmSubAI_T::Create },
	{ MWESM_SUBREC_AI_W,	CEsmSubAI_W::Create },
	{ MWESM_SUBREC_CNDT,	CEsmSubNameFix::Create },
	{ MWESM_SUBREC_DODT,	CEsmSubPos6::Create },
	{ MWESM_SUBREC_DNAM,	CEsmSubName::Create },
	{ MWESM_SUBREC_XSCL,	CEsmSubFloat::Create },
	{ NULL,			CEsmSubRecord::Create }	/* Must be last record */
 };
/*===========================================================================
 *		End of Sub-Record Create Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Blood Type Definitions
 *
 *=========================================================================*/
static valuenames_t l_BloodTypes[] = {
	{ MWESM_NPCFLAG_BLOODRED,   _T("Default (Red)") },
	{ MWESM_NPCFLAG_BLOODSKEL,  _T("Skeleton (White)") },
	{ MWESM_NPCFLAG_BLOODMETAL, _T("Metal (Gold)") },
	{ MWESM_NPCFLAG_BLOODRED,   _T("Default") },
	{ MWESM_NPCFLAG_BLOODSKEL,  _T("Skeleton") },
	{ MWESM_NPCFLAG_BLOODMETAL, _T("Metal") },
	{ MWESM_NPCFLAG_BLOODRED,   _T("Red") },
	{ MWESM_NPCFLAG_BLOODSKEL,  _T("White") },
	{ MWESM_NPCFLAG_BLOODMETAL, _T("Gold") },
	{ -1, NULL }
 };


const TCHAR* GetEsmNpcBloodType (const int Index) {
  const TCHAR* pString = FindValueName(l_BloodTypes,  Index);
  return (pString == NULL ? _T("") : pString);
 }


int GetEsmNpcBloodType (const TCHAR* pString) {
  long lBloodType;
  bool Result = FindNameValue(lBloodType, l_BloodTypes, pString);
  return (Result ? lBloodType : MWESM_NPCFLAG_BLOODRED);
 }
/*===========================================================================
 *		End of Blood Type Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Class CEsmNpc Constructor
 *
 *=========================================================================*/
CEsmNpc::CEsmNpc () {
  //DEFINE_FUNCTION("CEsmNpc::CEsmNpc()");
  m_pNpcShortData = NULL;
  m_pNpcLongData  = NULL;
  m_pFlag	  = NULL;
  m_pRace	  = NULL;
  m_pAnimation    = NULL;
  m_pHeadModel    = NULL;
  m_pHairModel    = NULL;
  m_pAIData       = NULL;
  m_pClass        = NULL;
  m_pFaction      = NULL;
 }
/*===========================================================================
 *		End of Class CEsmNpc Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - void Destroy (void);
 *
 * Description
 *
 *=========================================================================*/
void CEsmNpc::Destroy (void) {
  //DEFINE_FUNCTION("CEsmNpc::Destroy()");

	/* Clear the references */
  m_pNpcShortData = NULL;
  m_pNpcLongData  = NULL;
  m_pFlag	  = NULL;
  m_pRace	  = NULL;
  m_pAnimation    = NULL;
  m_pHeadModel    = NULL;
  m_pHairModel    = NULL;
  m_pAIData       = NULL;
  m_pClass        = NULL;
  m_pFaction      = NULL;

	/* Call the base class method */
  CEsmItem1::Destroy();
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - bool AddItem (pItemID);
 *
 * Adds the given item ID to the NPCs inventory. Does not check if the
 * ID is valid or not.
 *
 *=========================================================================*/
bool CEsmNpc::AddItem (const TCHAR* pItemID) {
  //DEFINE_FUNCTION("CEsmNpc::AddItem()");
  CEsmSubNPCO* pNewItem;

	/* Allocate the new item sub-record */
  pNewItem = (CEsmSubNPCO *) AllocateSubRecord(MWESM_SUBREC_NPCO);
  if (pNewItem == NULL) return (false);

  pNewItem->CreateNew();
  pNewItem->SetItem(pItemID);
  pNewItem->SetCount(1);

  return (true);
 }


bool CEsmNpc::AddItemCount (const TCHAR* pItemID, const int Count) {
  //DEFINE_FUNCTION("CEsmNpc::AddItemCount()");
  CEsmSubNPCO* pNewItem;

	/* Allocate the new item sub-record */
  pNewItem = (CEsmSubNPCO *) AllocateSubRecord(MWESM_SUBREC_NPCO);
  if (pNewItem == NULL) return (false);

  pNewItem->CreateNew();
  pNewItem->SetItem(pItemID);
  pNewItem->SetCount(Count);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::AddItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - bool AddItemEx (pString);
 *
 * Adds an item to the NPCs inventory.  Does not check if the ID is valid 
 * or not. Input string is expected to have the format:
 *
 *		item_id = Count
 *
 *=========================================================================*/
bool CEsmNpc::AddItemEx (const TCHAR* pString) {
  //DEFINE_FUNCTION("CEsmNpc::AddItemEx()");
  CEsmSubNPCO* pNewItem;
  const TCHAR* pParse;
  CSString     IDBuffer;
  int	       ItemCount = 1;

	/* Parse the input string */
  pParse = TSTRCHR(pString, '=');

  if (pParse != NULL) {
    IDBuffer.Copy(pString, pParse - pString);
    IDBuffer.Trim();
    ItemCount = atoi(pParse + 1);
    if (ItemCount <= 0) ItemCount = 1;
   }
  else {
    IDBuffer = pString;
   }

	/* Allocate the new item sub-record */
  pNewItem = (CEsmSubNPCO *) AllocateSubRecord(MWESM_SUBREC_NPCO);
  if (pNewItem == NULL) return (false);

  pNewItem->CreateNew();
  pNewItem->SetItem(IDBuffer);
  pNewItem->SetCount(ItemCount);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::AddItemEx()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - bool AddSpell (pSpellID);
 *
 * Adds the given spell to the NPC. Does not check if the
 * ID is valid or not.
 *
 *=========================================================================*/
bool CEsmNpc::AddSpell (const TCHAR* pSpellID) {
  //DEFINE_FUNCTION("CEsmNpc::AddSpell()");
  CEsmSubNPCS* pNewSpell;

	/* Allocate the new item sub-record */
  pNewSpell = (CEsmSubNPCS *) AllocateSubRecord(MWESM_SUBREC_NPCS);
  if (pNewSpell == NULL) return (false);

  pNewSpell->CreateNew();
  pNewSpell->SetName(pSpellID);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::AddSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CEsmNpc* AllocNewSubRecord (pType);
 *
 * Allocates a new subrecord of the given type.
 *
 *=========================================================================*/
CEsmSubRecord* CEsmNpc::AllocNewSubRecord (const TCHAR* pType, const long RecordSize) {
  CEsmSubRecord* pSubRecord;

	/* Check for special case */
  if ( _stricmp(pType, MWESM_SUBREC_NPDT) != 0) return CEsmItem1::AllocNewSubRecord(pType, RecordSize);

	/* Create and initialize the new record */
  if (RecordSize == sizeof(npclongdata_t)) 
    pSubRecord = CEsmSubNPDTL::Create();
  else if (RecordSize == sizeof(npclongdata_t)) 
    pSubRecord = CEsmSubNPDTS::Create();
  else 
    return CEsmItem1::AllocNewSubRecord(pType, RecordSize);

  pSubRecord->SetType(pType);
  pSubRecord->SetRecordSize(RecordSize);

  return (pSubRecord);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::AllocNewSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CEsmNpc Method - const GetTravelCell (Index);
 *
 *=========================================================================*/
const char* CEsmNpc::GetTravelCell (const int Index) {
  CEsmSubRecord* pDoorData;
  CEsmSubRecord* pCellName;
  int		 FindIndex;
  int		 Count = 0;

  if (Index < 0 || Index >= 4) return (NULL);
  pDoorData = FindFirst(MWESM_SUBREC_DODT, FindIndex);

  while (pDoorData != NULL) {
    pCellName = GetSubRecord(FindIndex + 1);

    if (Count == Index && pCellName != NULL && pCellName->IsType(MWESM_SUBREC_DNAM)) {
      return ((CEsmSubName *)pCellName)->GetName();
    }
    else if (Count == Index) {
      return (NULL);
    }

    ++Count;
    pDoorData = FindNext(MWESM_SUBREC_DODT, FindIndex);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method char* CEsmNpc::GetTravelCell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - int CompareFields (FieldID, pRecord);
 *
 * Compares the given field of the current record and the supplied record.
 * Returns a value which can be used for sorting the records..
 *
 *=========================================================================*/
int CEsmNpc::CompareFields (const int FieldID, CEsmRecord* pRecord) {
  //DEFINE_FUNCTION("CEsmNpc::CompareFields()");
  CEsmNpc*	 pNpc;
  aidata_t*	 pAiData1;
  aidata_t* 	 pAiData2;
  
	/* Ensure the correct type */
  if (!pRecord->IsType(MWESM_REC_NPC_)) return CEsmItem1::CompareFields(FieldID, pRecord);
  pNpc     = (CEsmNpc *) pRecord;
  pAiData1 = GetAIData();
  pAiData2 = pNpc->GetAIData();

  switch (FieldID) {
    case ESM_FIELD_FEMALE:
	return (int)IsFemale() - (int)pNpc->IsFemale();
    case ESM_FIELD_AUTOCALC:
	return (int)IsAutoCalc() - (int)pNpc->IsAutoCalc();
    case ESM_FIELD_ESSENTIAL:
	return (int)IsEssential() - (int)pNpc->IsEssential();
    case ESM_FIELD_RESPAWN:
	return (int)IsRespawn() - (int)pNpc->IsRespawn();
    case ESM_FIELD_LEVEL:
	return GetLevel() - pNpc->GetLevel();
    case ESM_FIELD_CLASS:
        return StringCompare(GetClass(), pNpc->GetClass(), true);
    case ESM_FIELD_RACE:
        return StringCompare(GetRace(), pNpc->GetRace(), true);
    case ESM_FIELD_ANIMATION:
        return StringCompare(GetAnimation(), pNpc->GetAnimation(), true);
    case ESM_FIELD_FACTION:
        return StringCompare(GetFaction(), pNpc->GetFaction(), true);
    case ESM_FIELD_RANK:
	return GetRank() - pNpc->GetRank();
    case ESM_FIELD_FIGHT:
	if (pAiData1 && pAiData2) return (pAiData1->Fight - pAiData2->Fight);
	if (pAiData1) return (pAiData1->Fight);
	if (pAiData2) return (pAiData2->Fight);
	return (0);
    case ESM_FIELD_ALARM:
    	if (pAiData1 && pAiData2) return (pAiData1->Alarm - pAiData2->Alarm);
	if (pAiData1) return (pAiData1->Alarm);
	if (pAiData2) return (pAiData2->Alarm);
	return (0);
    case ESM_FIELD_FLEE:
    	if (pAiData1 && pAiData2) return (pAiData1->Flee - pAiData2->Flee);
	if (pAiData1) return (pAiData1->Flee);
	if (pAiData2) return (pAiData2->Flee);
	return (0);
    case ESM_FIELD_HELLO:
    	if (pAiData1 && pAiData2) return (pAiData1->Hello - pAiData2->Hello);
	if (pAiData1) return (pAiData1->Hello);
	if (pAiData2) return (pAiData2->Hello);
	return (0);
    case ESM_FIELD_NPCAPPARATUS:
	return (int)IsAiBuyApparatus() - (int)pNpc->IsAiBuyApparatus(); 
    case ESM_FIELD_NPCARMORS:
    	return (int)IsAiBuyArmor() - (int)pNpc->IsAiBuyArmor(); 
    case ESM_FIELD_NPCBOOKS:
    	return (int)IsAiBuyBook() - (int)pNpc->IsAiBuyBook(); 
    case ESM_FIELD_NPCCLOTHING:
    	return (int)IsAiBuyClothing() - (int)pNpc->IsAiBuyClothing(); 
    case ESM_FIELD_NPCINGREDIANTS:
    	return (int)IsAiBuyIngrediant() - (int)pNpc->IsAiBuyIngrediant(); 
    case ESM_FIELD_NPCLIGHTS:
    	return (int)IsAiBuyLight() - (int)pNpc->IsAiBuyLight(); 
    case ESM_FIELD_NPCLOCKPICKS:
    	return (int)IsAiBuyPick() - (int)pNpc->IsAiBuyPick(); 
    case ESM_FIELD_NPCMISC:
    	return (int)IsAiBuyMisc() - (int)pNpc->IsAiBuyMisc(); 
    case ESM_FIELD_NPCPROBES:
    	return (int)IsAiBuyProbe() - (int)pNpc->IsAiBuyProbe(); 
    case ESM_FIELD_NPCPOTIONS:
    	return (int)IsAiBuyPotion() - (int)pNpc->IsAiBuyPotion(); 
    case ESM_FIELD_NPCREPAIRITEMS:
    	return (int)IsAiBuyRepair() - (int)pNpc->IsAiBuyRepair(); 
    case ESM_FIELD_NPCMAGICITEMS:
    	return (int)IsAiBuyMagicItem() - (int)pNpc->IsAiBuyMagicItem(); 
    case ESM_FIELD_NPCSPELLS:
    	return (int)IsAiBuySpell() - (int)pNpc->IsAiBuySpell(); 
    case ESM_FIELD_NPCWEAPONS:
    	return (int)IsAiBuyWeapon() - (int)pNpc->IsAiBuyWeapon(); 
    case ESM_FIELD_TRADEGOLD:
    case ESM_FIELD_GOLD:
	return GetGold() - pNpc->GetGold();
    case ESM_FIELD_NPCENCHANT:
    	return (int)IsAiEnchanting() - (int)pNpc->IsAiEnchanting(); 
    case ESM_FIELD_NPCSPELLMAKER:
    	return (int)IsAiSpellMaking() - (int)pNpc->IsAiSpellMaking(); 
    case ESM_FIELD_NPCTRAINING:
    	return (int)IsAiTraining() - (int)pNpc->IsAiTraining(); 
    case ESM_FIELD_NPCREPAIRS:
    	return (int)IsAiRepairItem() - (int)pNpc->IsAiRepairItem(); 
    case ESM_FIELD_NPCTRAVEL1:
        return StringCompare(GetTravelCell(0), pNpc->GetTravelCell(0), false);
    case ESM_FIELD_NPCTRAVEL2:
         return StringCompare(GetTravelCell(1), pNpc->GetTravelCell(1), false);
    case ESM_FIELD_NPCTRAVEL3:
         return StringCompare(GetTravelCell(2), pNpc->GetTravelCell(2), false);
    case ESM_FIELD_NPCTRAVEL4:
        return StringCompare(GetTravelCell(3), pNpc->GetTravelCell(3), false);
    default:	/* Call the base class method */
	return CEsmItem1::CompareFields(FieldID, pRecord); 
   }
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - CEsmRecord* Create (void);
 *
 * Static class method to create a new record object.
 *
 *=========================================================================*/
CEsmRecord* CEsmNpc::Create (void) {
  DEFINE_FUNCTION("CEsmNpc::Create()");
  CEsmRecord* pRecord;

  CreatePointer(pRecord, CEsmNpc);
  return (pRecord);
 }
/*===========================================================================
 *		End of Class Method CEsmArmor::Create()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - void CreateNew (pFile);
 *
 * Creates a new, empty, record.
 *
 *=========================================================================*/
void CEsmNpc::CreateNew (CEsmFile* pFile) {

	/* Call the base class record first */
  CEsmItem1::CreateNew(pFile);
  DeleteSubRecords(MWESM_SUBREC_MODL);
  m_pAnimation = NULL;

	/* Create the item sub-records */
  AllocateSubRecord(MWESM_SUBREC_NPDT, sizeof(npcshortdata_t));
  AllocateSubRecord(MWESM_SUBREC_FLAG);
  AllocateSubRecord(MWESM_SUBREC_RNAM);
  AllocateSubRecord(MWESM_SUBREC_ANAM);
  AllocateSubRecord(MWESM_SUBREC_BNAM);
  AllocateSubRecord(MWESM_SUBREC_CNAM);
  AllocateSubRecord(MWESM_SUBREC_KNAM);
  AllocateSubRecord(MWESM_SUBREC_AIDT);
  m_pNpcShortData->CreateNew();
  m_pFlag->CreateNew();
  m_pFlag->SetValue(MWESM_NPCFLAG_DEFAULT | MWESM_NPCFLAG_AUTOCALC);
  m_pAIData->CreateNew();
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::CreateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - void CreateNPCData (IsShort);
 *
 *=========================================================================*/
void CEsmNpc::CreateNPCData (const bool IsShort) { 
  
	/* Ignore if the correct type is already created */
  if (IsShort  && m_pNpcShortData != NULL) return;
  if (!IsShort && m_pNpcLongData  != NULL) return;

	/* Delete the current data */
  DeleteSubRecords(MWESM_SUBREC_NPDT);
  m_pNpcShortData = NULL;
  m_pNpcLongData  = NULL;

	/* Create new data */
  if (IsShort) {
    AllocateSubRecord(MWESM_SUBREC_NPDT, sizeof(npcshortdata_t));
    m_pNpcShortData->CreateNew();
   }
  else {
    AllocateSubRecord(MWESM_SUBREC_NPDT, sizeof(npclongdata_t));
    m_pNpcLongData->CreateNew();
   }

 }
/*===========================================================================
 *		End of Class Method CEsmNpc::CreateNPCData()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Class CEsmNpc Method - bool DoesInfoApply (pInfo);
 *
 *=========================================================================*/
bool CEsmNpc::DoesInfoApply (CEsmInfo* pInfo) {
  const TCHAR* pString;
  infodata_t*  pInfoData = pInfo->GetInfoData();
  
	/* Check ID */
  pString = pInfo->GetActor();
  if (*pString != NULL_CHAR && TSTRNICMP(pString, GetID(), MWESM_ID_MAXSIZE) != 0) return (false);

	/* Check gender */
  if (pInfoData->Gender != MWESM_INFOGENDER_NONE) {
    if (IsFemale()  && pInfoData->Gender == MWESM_INFOGENDER_MALE)   return (false);
    if (!IsFemale() && pInfoData->Gender == MWESM_INFOGENDER_FEMALE) return (false);
   }

	/* Check race */
  pString = pInfo->GetRace();
  if (*pString != NULL_CHAR && TSTRNICMP(pString, GetRace(), MWESM_ID_MAXSIZE) != 0) return (false);

  	/* Check class */
  pString = pInfo->GetClass();
  if (*pString != NULL_CHAR && TSTRNICMP(pString, GetClass(), MWESM_ID_MAXSIZE) != 0) return (false);

    	/* Check faction */
  pString = pInfo->GetFaction();
  if (*pString != NULL_CHAR && TSTRNICMP(pString, GetFaction(), MWESM_ID_MAXSIZE) != 0) return (false);

    	/* Check rank */
  if (pInfoData->Rank >= 0 && pInfoData->Rank > GetRank()) return (false);

	/* Check cell? */

  return (true);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::DoesInfoApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - CEsmSubNPCO* FindItem (pItemID);
 *
 * Searches the NPC for a particular item record. Returns the sub-record
 * or NULL if it does not exist.
 *
 *=========================================================================*/
CEsmSubNPCO* CEsmNpc::FindItem (const TCHAR* pItemID) {
  CEsmSubNPCO*	pItemRec;
  int		ArrayIndex;

	/* Search all NPC items for a match */
  pItemRec = (CEsmSubNPCO *) FindFirst(MWESM_SUBREC_NPCO, ArrayIndex);

  while (pItemRec != NULL) {
    if (_tcsicmp(pItemRec->GetItem(), pItemID) == 0) return (pItemRec);
    pItemRec = (CEsmSubNPCO *) FindNext(MWESM_SUBREC_NPCO, ArrayIndex);
   }
  
	/* Does not exist */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::FindItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - CEsmSubNPCS* FindSpell (pSpellID);
 *
 * Searches the NPC for a particular spell record. Returns the sub-record
 * or NULL if it does not exist.
 *
 *=========================================================================*/
CEsmSubNPCS* CEsmNpc::FindSpell (const TCHAR* pSpellID) {
  CEsmSubNPCS*	pSpellRec;
  int		ArrayIndex;

	/* Search all NPC items for a match */
  pSpellRec = (CEsmSubNPCS *) FindFirst(MWESM_SUBREC_NPCS, ArrayIndex);

  while (pSpellRec != NULL) {
    if (_tcsicmp(pSpellRec->GetName(), pSpellID) == 0) return (pSpellRec);
    pSpellRec = (CEsmSubNPCS *) FindNext(MWESM_SUBREC_NPCS, ArrayIndex);
   }
  
	/* Does not exist */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::FindSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TCHAR* CEsmNpc Method - const GetFieldString (FieldID);
 *
 * Returns a string representation of the given field. Always returns
 * a valid string.
 *
 *=========================================================================*/
const TCHAR* CEsmNpc::GetFieldString (const int FieldID) {
  //DEFINE_FUNCTION("CEsmNpc::GetFieldString()");
  static TCHAR  s_Buffer[32];
  aidata_t*	pAiData;

  switch (FieldID) {
    case ESM_FIELD_FEMALE:
	return BOOLTOYESNO(IsFemale());
    case ESM_FIELD_AUTOCALC:
	return BOOLTOYESNO(IsAutoCalc());
    case ESM_FIELD_ESSENTIAL:
	return BOOLTOYESNO(IsEssential());
    case ESM_FIELD_RESPAWN:
	return BOOLTOYESNO(IsRespawn());
    case ESM_FIELD_LEVEL:
	snprintf (s_Buffer, 31, _T("%ld"), GetLevel());
	return (s_Buffer);
    case ESM_FIELD_CLASS:
        return GetClass();
    case ESM_FIELD_RACE:
        return GetRace();
    case ESM_FIELD_ANIMATION:
        return GetAnimation();
    case ESM_FIELD_FACTION:
        return GetFaction();
    case ESM_FIELD_RANK:
        snprintf (s_Buffer, 31, _T("%ld"), GetRank());
	return (s_Buffer);
    case ESM_FIELD_BLOOD:
        return GetEsmNpcBloodType(GetFlag() & MWESM_NPCFLAG_BLOODMASK);
    case ESM_FIELD_DISPOSITION:
        snprintf (s_Buffer, 31, _T("%ld"), GetDisposition());
        return (s_Buffer);
    case ESM_FIELD_HAIR:
	return GetHairModel();
    case ESM_FIELD_HEAD:
	return GetHeadModel();
    case ESM_FIELD_STRENGTH:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_STR));
	return (s_Buffer);
    case ESM_FIELD_AGILITY:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_AGI));
	return (s_Buffer);
    case ESM_FIELD_SPEED:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_SPD));
	return (s_Buffer);
    case ESM_FIELD_ENDURANCE:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_END));
	return (s_Buffer);
    case ESM_FIELD_WILLPOWER:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_WIL));
	return (s_Buffer);
    case ESM_FIELD_INTELLIGENCE:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_INT));
	return (s_Buffer);
    case ESM_FIELD_PERSONALITY:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_PER));
	return (s_Buffer);
    case ESM_FIELD_LUCK:
        snprintf (s_Buffer, 31, _T("%ld"), GetAttribute(MWESM_ATTRIBUTE_LUC));
	return (s_Buffer);
    case ESM_FIELD_GOLD:
   case ESM_FIELD_TRADEGOLD:
        snprintf (s_Buffer, 31, _T("%ld"), GetGold());
	return (s_Buffer);
    case ESM_FIELD_HEALTH:
        snprintf (s_Buffer, 31, _T("%ld"), GetHealth());
	return (s_Buffer);
    case ESM_FIELD_SPELLPTS:
        snprintf (s_Buffer, 31, _T("%ld"), GetMagic());
	return (s_Buffer);
    case ESM_FIELD_FATIGUE:
        snprintf (s_Buffer, 31, _T("%ld"), GetFatigue());
	return (s_Buffer);
    case ESM_FIELD_FIGHT:
        pAiData = GetAIData();
	if (pAiData) 
	  snprintf (s_Buffer, 31, _T("%lu"), (unsigned int)pAiData->Fight);
	else
	  s_Buffer[0] = NULL_CHAR;
	return (s_Buffer);
    case ESM_FIELD_ALARM:
        pAiData = GetAIData();
	if (pAiData) 
	  snprintf (s_Buffer, 31, _T("%lu"), (unsigned int)pAiData->Alarm);
	else
	  s_Buffer[0] = NULL_CHAR;
	return (s_Buffer);
    case ESM_FIELD_FLEE:
        pAiData = GetAIData();
	if (pAiData) 
	  snprintf (s_Buffer, 31, _T("%lu"), (unsigned int)pAiData->Flee);
	else
	  s_Buffer[0] = NULL_CHAR;
	return (s_Buffer);
    case ESM_FIELD_HELLO:
        pAiData = GetAIData();
	if (pAiData) 
	  snprintf (s_Buffer, 31, _T("%lu"), (unsigned int)pAiData->Hello);
	else
	  s_Buffer[0] = NULL_CHAR;
	return (s_Buffer);   
    case ESM_FIELD_NPCAPPARATUS:
	return BOOLTOYESNO(IsAiBuyApparatus());
    case ESM_FIELD_NPCARMORS:
	return BOOLTOYESNO(IsAiBuyArmor());
    case ESM_FIELD_NPCBOOKS:
	return BOOLTOYESNO(IsAiBuyBook());
    case ESM_FIELD_NPCCLOTHING:
	return BOOLTOYESNO(IsAiBuyClothing());
    case ESM_FIELD_NPCINGREDIANTS:
	return BOOLTOYESNO(IsAiBuyIngrediant());
    case ESM_FIELD_NPCLIGHTS:
	return BOOLTOYESNO(IsAiBuyLight());
    case ESM_FIELD_NPCLOCKPICKS:
	return BOOLTOYESNO(IsAiBuyPick());
    case ESM_FIELD_NPCMISC:
	return BOOLTOYESNO(IsAiBuyMisc());
    case ESM_FIELD_NPCPROBES:
	return BOOLTOYESNO(IsAiBuyProbe());
    case ESM_FIELD_NPCPOTIONS:
	return BOOLTOYESNO(IsAiBuyPotion());
    case ESM_FIELD_NPCREPAIRITEMS:
	return BOOLTOYESNO(IsAiBuyRepair());
    case ESM_FIELD_NPCMAGICITEMS:
	return BOOLTOYESNO(IsAiBuyMagicItem());
    case ESM_FIELD_NPCSPELLS:
	return BOOLTOYESNO(IsAiBuySpell());
    case ESM_FIELD_NPCWEAPONS:
	return BOOLTOYESNO(IsAiBuyWeapon());
    case ESM_FIELD_NPCENCHANT:
	return BOOLTOYESNO(IsAiEnchanting());
    case ESM_FIELD_NPCSPELLMAKER:
	return BOOLTOYESNO(IsAiSpellMaking());
    case ESM_FIELD_NPCTRAINING:
	return BOOLTOYESNO(IsAiTraining());
    case ESM_FIELD_NPCREPAIRS:
	return BOOLTOYESNO(IsAiRepairItem());
    case ESM_FIELD_NPCTRAVEL1:
	strnncpy(s_Buffer, GetTravelCell(0), 31);
	return (s_Buffer);
    case ESM_FIELD_NPCTRAVEL2:
       	strnncpy(s_Buffer, GetTravelCell(1), 31);
	return (s_Buffer);
    case ESM_FIELD_NPCTRAVEL3:
	strnncpy(s_Buffer, GetTravelCell(2), 31);
	return (s_Buffer);
    case ESM_FIELD_NPCTRAVEL4:
	strnncpy(s_Buffer, GetTravelCell(3), 31);
	return (s_Buffer);
    default:	/* Call the base class record */
	return CEsmItem1::GetFieldString(FieldID);
   }
  
 }
/*===========================================================================
 *		End of Class Method TCHAR* CEsmNpc::GetFieldString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetDisposition (void);
 *
 *=========================================================================*/
long CEsmNpc::GetDisposition (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Disposition;
  else if (m_pNpcShortData != NULL)
    return m_pNpcShortData->GetNPCData()->Disposition;

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetDisposition()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetReputation (void);
 *
 *=========================================================================*/
long CEsmNpc::GetReputation (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Reputation;
  else if (m_pNpcShortData != NULL)
    return 0;

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetReputation()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetFactionID (void);
 *
 *=========================================================================*/
long CEsmNpc::GetFactionID (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->FactionID;
  else if (m_pNpcShortData != NULL)
    return m_pNpcShortData->GetNPCData()->FactionID;

  return (-1);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetFactionID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetGold (void);
 *
 *=========================================================================*/
long CEsmNpc::GetGold (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Gold;
  else if (m_pNpcShortData != NULL)
    return m_pNpcShortData->GetNPCData()->Gold;

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetGold()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetLevel (void);
 *
 *=========================================================================*/
long CEsmNpc::GetLevel (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Level;
  else if (m_pNpcShortData != NULL)
    return m_pNpcShortData->GetNPCData()->Level;

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetHealth (void);
 *
 *=========================================================================*/
long CEsmNpc::GetHealth (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Health;
  
  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetHealth()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetMagic (void);
 *
 *=========================================================================*/
long CEsmNpc::GetMagic (void) {
  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->SpellPts;
  
  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetMagic()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetFatigue (void);
 *
 *=========================================================================*/
long CEsmNpc::GetFatigue (void) {
  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Fatigue;
  
  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetFatigue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetRank (void);
 *
 *=========================================================================*/
long CEsmNpc::GetRank (void) {

  if (m_pNpcLongData != NULL) 
    return m_pNpcLongData->GetNPCData()->Rank;
  else if (m_pNpcShortData != NULL)
    return m_pNpcShortData->GetNPCData()->Rank;

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetRank()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetSkill (const TCHAR* pSkill);
 *
 *=========================================================================*/
long CEsmNpc::GetSkill (const TCHAR* pSkill) {
  bool Result;
  int  SkillIndex;

	/* Ensure the skill string is valid */
  Result = GetESMSkill(SkillIndex, pSkill);
  if (!Result) return (0);

  return (GetSkill(SkillIndex));
 }


long CEsmNpc::GetSkill (const int SkillIndex) {

  if (m_pNpcLongData != NULL)
    return m_pNpcLongData->GetSkill(SkillIndex);
  else if (m_pClass != NULL) {
    return (0);	/* TODO: Proper autocalc */
   }

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetSkill()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - long GetAttribute (const TCHAR* pAttribute);
 *
 *=========================================================================*/
long CEsmNpc::GetAttribute (const TCHAR* pAttribute) {
  bool Result;
  int  AttrIndex;

	/* Ensure the attribute string is valid */
  Result = GetESMAttribute(AttrIndex, pAttribute);
  if (!Result) return (0);

  return (GetAttribute(AttrIndex));
 }


long CEsmNpc::GetAttribute (const int AttrIndex) {

	/* Different methods for autocalc data */
  if (m_pNpcLongData != NULL) {
    switch (AttrIndex) {
      case MWESM_ATTRIBUTE_STR: return (long)(byte)m_pNpcLongData->GetStrength();
      case MWESM_ATTRIBUTE_AGI: return (long)(byte)m_pNpcLongData->GetAgility();
      case MWESM_ATTRIBUTE_SPD: return (long)(byte)m_pNpcLongData->GetSpeed();
      case MWESM_ATTRIBUTE_END: return (long)(byte)m_pNpcLongData->GetEndurance();
      case MWESM_ATTRIBUTE_PER: return (long)(byte)m_pNpcLongData->GetPersonality();
      case MWESM_ATTRIBUTE_INT: return (long)(byte)m_pNpcLongData->GetIntelligence();
      case MWESM_ATTRIBUTE_WIL: return (long)(byte)m_pNpcLongData->GetWillpower();
      case MWESM_ATTRIBUTE_LUC: return (long)(byte)m_pNpcLongData->GetLuck();
      default: return (0);
     }
   }
  else if (m_pClass != NULL) {
    return (0);	/* TODO: Proper autocalc */
   }

  return (0);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::GetAttribute()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CEsmNpc Event - void OnAddSubRecord (pSubRecord);
 *
 *=========================================================================*/
void CEsmNpc::OnAddSubRecord (CEsmSubRecord* pSubRecord) {

	/* There are two different NPDT record sizes */
  if (pSubRecord->IsType(MWESM_SUBREC_NPDT)) {
    if (pSubRecord->GetRecordSize() == sizeof(npcshortdata_t))
      m_pNpcShortData = (CEsmSubNPDTS *) pSubRecord;
    else if (pSubRecord->GetRecordSize() == sizeof(npclongdata_t))
      m_pNpcLongData  = (CEsmSubNPDTL *) pSubRecord;
   }
  else if (pSubRecord->IsType(MWESM_SUBREC_FLAG))
    m_pFlag = (CEsmSubLong *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_RNAM))
    m_pRace = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_MODL))
    m_pAnimation = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_BNAM))
    m_pHeadModel = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_CNAM))
    m_pClass = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_KNAM))
    m_pHairModel = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_ANAM))
    m_pFaction = (CEsmSubNameFix *) pSubRecord;
  else if (pSubRecord->IsType(MWESM_SUBREC_AIDT))
    m_pAIData = (CEsmSubAIDT *) pSubRecord;
  else
    CEsmItem1::OnAddSubRecord(pSubRecord);
  
 }
/*===========================================================================
 *		End of Class Event CEsmNpc::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - bool SetFieldValue (pString);
 *
 * Sets a particular field to the given value. Returns false on any error.
 * Assumes that the input string is non-NULL.
 *
 *=========================================================================*/
bool CEsmNpc::SetFieldValue (const int FieldID, const TCHAR* pString) {

  switch (FieldID) { 
    case ESM_FIELD_ITEM:
        AddItem(pString);
	return (true);
    case ESM_FIELD_ITEMEX:
        AddItemEx(pString);
        return (true);
    case ESM_FIELD_SPELL:
        AddSpell(pString);
        return (true);
    case ESM_FIELD_HEAD:
        SetHeadModel(pString);
        return (true);
    case ESM_FIELD_HAIR:
        SetHairModel(pString);
        return (true);
    case ESM_FIELD_BLOOD:
        SetBloodType(pString);
        return (true);
    case ESM_FIELD_FEMALE:
	SetFemale(StringToBoolean(pString));
	return (true);
    case ESM_FIELD_AUTOCALC:
	SetAutoCalc(StringToBoolean(pString));
	return (true);
    case ESM_FIELD_ESSENTIAL:
	SetEssential(StringToBoolean(pString));
	return (true);
    case ESM_FIELD_RESPAWN:
	SetRespawn(StringToBoolean(pString));
	return (true);
    case ESM_FIELD_LEVEL:
	SetLevel(atoi(pString));
	return (true);
    case ESM_FIELD_CLASS:
        SetClass(pString);
	return (true);
    case ESM_FIELD_RACE:
        SetRace(pString);
	return (true);
    case ESM_FIELD_ANIMATION:
        SetAnimation(pString);
	return (true);
    case ESM_FIELD_FACTION:
        SetFaction(pString);
	return (true);
    case ESM_FIELD_RANK:
	SetRank(atoi(pString));
    	return (true);
    case ESM_FIELD_DISPOSITION:
        SetDisposition(atoi(pString));
        return (true);
    case ESM_FIELD_ATTRIBUTE:
        SetAttribute(pString);
        return (true);
    case ESM_FIELD_SKILL:
        SetSkill(pString);
        return (true);
    case ESM_FIELD_STRENGTH:
        SetAttribute(pString, MWESM_ATTRIBUTE_STR);
        return (true);
    case ESM_FIELD_AGILITY:
        SetAttribute(pString, MWESM_ATTRIBUTE_AGI);
        return (true);
    case ESM_FIELD_SPEED:
        SetAttribute(pString, MWESM_ATTRIBUTE_SPD);
        return (true);
    case ESM_FIELD_ENDURANCE:
        SetAttribute(pString, MWESM_ATTRIBUTE_END);
        return (true);
    case ESM_FIELD_WILLPOWER:
        SetAttribute(pString, MWESM_ATTRIBUTE_WIL);
        return (true);
    case ESM_FIELD_INTELLIGENCE:
        SetAttribute(pString, MWESM_ATTRIBUTE_INT);
        return (true);
    case ESM_FIELD_LUCK:
        SetAttribute(pString, MWESM_ATTRIBUTE_LUC);
        return (true);
    case ESM_FIELD_PERSONALITY:
        SetAttribute(pString, MWESM_ATTRIBUTE_PER);
        return (true);
    case ESM_FIELD_GOLD:
        SetGold(atol(pString));
        return (true);
    case ESM_FIELD_HEALTH:
        SetHealth(atol(pString));
	return (true);
    case ESM_FIELD_SPELLPTS:
        SetSpellPts(atol(pString));
	return (true);
    case ESM_FIELD_FATIGUE:
        SetFatigue(atol(pString));
	return (true);
   };

	/* No matching field found */
  return CEsmItem1::SetFieldValue(FieldID, pString);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::SetFieldValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmNpc Method - void SetAnimation (pString);
 *
 *=========================================================================*/
void CEsmNpc::SetAnimation (const TCHAR* pString) {
  DEFINE_FUNCTION("CEsmNpc::SetAnimation()");

  if (pString == NULL || *pString == NULL_CHAR) {
    if (m_pAnimation != NULL) DeleteSubRecords(MWESM_SUBREC_MODL);
    m_pAnimation = NULL;
   }
  else {
    if (m_pAnimation == NULL) {
      AllocateSubRecord(MWESM_SUBREC_MODL);
      ASSERT(m_pAnimation != NULL);
      m_pAnimation->CreateNew();
     }
    m_pAnimation->SetName(pString);
   }
 }

void CEsmNpc::SetDisposition (const int Value) {
  if (m_pNpcLongData != NULL)
    m_pNpcLongData->GetNPCData()->Disposition = Value;
  else if (m_pNpcShortData != NULL)
    m_pNpcShortData->GetNPCData()->Disposition = Value;
 }


void CEsmNpc::SetLevel (const int Value) {
  if (m_pNpcLongData != NULL)
    m_pNpcLongData->GetNPCData()->Level = Value;
  else if (m_pNpcShortData != NULL)
    m_pNpcShortData->GetNPCData()->Level = Value;
 }


void CEsmNpc::SetRank (const int Value) {
  if (m_pNpcLongData != NULL)
    m_pNpcLongData->GetNPCData()->Rank = Value;
  else if (m_pNpcShortData != NULL)
    m_pNpcShortData->GetNPCData()->Rank = Value;
 }


void CEsmNpc::SetGold (const long Value) {
  if (m_pNpcLongData != NULL)
    m_pNpcLongData->GetNPCData()->Gold = Value;
  else if (m_pNpcShortData != NULL)
    m_pNpcShortData->GetNPCData()->Gold = Value;
 }


void CEsmNpc::SetBloodType (const TCHAR* pString) {
  SetFlag(GetFlag() & (~MWESM_NPCFLAG_BLOODMASK) | GetEsmNpcBloodType(pString));
 }


	/* Expects a string in the format "Skill = Value" */
void CEsmNpc::SetSkill (const TCHAR* pString) {
  const TCHAR* pParse;
  const TCHAR* pSkillPtr = NULL;
  CSString     SkillBuffer;
  bool	       Result;
  int	       SkillValue = 15;
  int	       SkillIndex;

	/* Ignore if auto-calc value is set */
  if (IsAutoCalc() || m_pNpcLongData == NULL) return;

	/* Parse the input string */
  pParse = TSTRCHR(pString, '=');

  if (pParse != NULL) {
    SkillBuffer.Copy(pString, pParse - pString);
    SkillBuffer.Trim();
    pSkillPtr = pParse + 1;
   }
  else {
    SkillBuffer = pString;
   }

	/* Set the skill if it is valid */
  Result = GetESMSkill (SkillIndex, SkillBuffer);
  if (Result) SetSkill(pSkillPtr, SkillIndex);
 }


void CEsmNpc::SetSkill (const TCHAR* pString, const int SkillIndex) {
  int SkillValue = 15;

	/* Ignore if auto-calc value is set */
  if (IsAutoCalc() || m_pNpcLongData == NULL) return;

	/* Convert the string value if valid */
  if (pString != NULL) {
    SkillValue = atoi(pString);
    if (SkillValue < 0)   SkillValue = 0;
    if (SkillValue > 255) SkillValue = 255;
   }

	/* Set the skill */
  m_pNpcLongData->SetSkill(SkillIndex, SkillValue);
 }


	/* Expects a string in the format "Attribute = Value" */
void CEsmNpc::SetAttribute (const TCHAR* pString) {
  const TCHAR* pParse;
  const TCHAR* pAttrPtr = NULL;
  CSString     AttrBuffer;
  bool	       Result;
  int	       AttrValue = 15;
  int	       AttrIndex;

	/* Ignore if auto-calc value is set */
  if (IsAutoCalc() || m_pNpcLongData == NULL) return;

	/* Parse the input string */
  pParse = TSTRCHR(pString, '=');

  if (pParse != NULL) {
    AttrBuffer.Copy(pString, pParse - pString);
    AttrBuffer.Trim();
    pAttrPtr = pParse + 1;
   }
  else {
    AttrBuffer = pString;
   }

	/* Get the attribte index */
  Result = GetESMAttribute(AttrIndex, AttrBuffer);
  if (!Result) return;
  
  SetAttribute(pAttrPtr, AttrIndex);
 }


void CEsmNpc::SetAttribute (const TCHAR* pString, const int AttrIndex) {
  int AttrValue = 15;

  	/* Ignore if auto-calc value is set */
  if (IsAutoCalc() || m_pNpcLongData == NULL) return;

	/* Convert the string value if valid */
  if (pString != NULL) {
    AttrValue = atoi(pString);
    if (AttrValue < 0)   AttrValue = 0;
    if (AttrValue > 255) AttrValue = 255;
   }

  switch (AttrIndex) {
    case MWESM_ATTRIBUTE_STR:
	m_pNpcLongData->SetStrength(AttrValue);
	break;
    case MWESM_ATTRIBUTE_AGI:
	m_pNpcLongData->SetAgility(AttrValue);
	break;
    case MWESM_ATTRIBUTE_SPD:
	m_pNpcLongData->SetSpeed(AttrValue);
	break;
    case MWESM_ATTRIBUTE_WIL:
	m_pNpcLongData->SetWillpower(AttrValue);
	break;
    case MWESM_ATTRIBUTE_INT:
	m_pNpcLongData->SetIntelligence(AttrValue);
	break;
    case MWESM_ATTRIBUTE_PER:
	m_pNpcLongData->SetPersonality(AttrValue);
	break;
    case MWESM_ATTRIBUTE_END:
	m_pNpcLongData->SetEndurance(AttrValue);
	break;
    case MWESM_ATTRIBUTE_LUC:
	m_pNpcLongData->SetLuck(AttrValue);
	break;
   }

 }


void CEsmNpc::SetAutoCalc (const bool AutoCalcFlag) {
  npcshortdata_t* pShortData;
  npclongdata_t*  pLongData;

	/* Set the actual flag */
  if (m_pFlag) m_pFlag->SetFlag(MWESM_NPCFLAG_AUTOCALC, AutoCalcFlag); 

	/* Ignore if the flag hasn't changed */
  if (m_pNpcLongData  != NULL && !AutoCalcFlag) return;
  if (m_pNpcShortData != NULL &&  AutoCalcFlag) return;

	/* Allocate the new data sub-record */
  if (AutoCalcFlag) {
    AllocateSubRecord(MWESM_SUBREC_NPDT, sizeof(npcshortdata_t));
    m_pNpcShortData->CreateNew();
   }
  else {
    AllocateSubRecord(MWESM_SUBREC_NPDT, sizeof(npclongdata_t));
    m_pNpcLongData->CreateNew();
   }

	/* Copy the old record data to the new, delete the old */
  if (AutoCalcFlag && m_pNpcLongData != NULL) {
    pShortData = m_pNpcShortData->GetNPCData();
    pLongData  = m_pNpcLongData->GetNPCData();

		/* Copy common elements */
    pShortData->Disposition = pLongData->Disposition;
    pShortData->FactionID   = pLongData->FactionID;
    pShortData->Gold        = pLongData->Gold;
    pShortData->Level	    = pLongData->Level;
    pShortData->Rank	    = pLongData->Rank;

		/* Delete the old long data */	
    DeleteSubRecord(m_pNpcLongData);
    DestroyPointer(m_pNpcLongData);
   }
  else if (!AutoCalcFlag && m_pNpcShortData != NULL) {
    pShortData = m_pNpcShortData->GetNPCData();
    pLongData  = m_pNpcLongData->GetNPCData();

		/* Copy common elements */
    pLongData->Disposition = pShortData->Disposition;
    pLongData->FactionID   = pShortData->FactionID;
    pLongData->Gold        = pShortData->Gold;
    pLongData->Level	   = pShortData->Level;
    pLongData->Rank	   = pShortData->Rank;

		/* Delete the old short data */
    DeleteSubRecord(m_pNpcShortData);
    DestroyPointer(m_pNpcShortData);
   }

 }


void CEsmNpc::SetHealth (const long Value) {
  if (m_pNpcLongData != NULL) m_pNpcLongData->SetHealth((short)Value);
 }


void CEsmNpc::SetSpellPts (const long Value) {
  if (m_pNpcLongData != NULL) m_pNpcLongData->SetSpellPts((short)Value);
 }


void CEsmNpc::SetFatigue (const long Value) {
  if (m_pNpcLongData != NULL) m_pNpcLongData->SetFatigue((short)Value);
 }
/*===========================================================================
 *		End of Class Method CEsmNpc::Set....()
 *=========================================================================*/



