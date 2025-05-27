/*===========================================================================
 *
 * File:    EsmNpc.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 *=========================================================================*/
#ifndef __ESMNPC_H
#define __ESMNPC_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmItem1.h"
#include "EsmSubName.h"
#include "EsmSubNPDT.h"
#include "EsmSubNPCO.h"
#include "EsmSubNPCS.h"
#include "EsmSubLong.h"
#include "EsmSubAIDT.h"
#include "EsmSubFloat.h"
#include "EsmSubAI_A.h"
#include "EsmSubAI_E.h"
#include "EsmSubAI_F.h"
#include "EsmSubAI_T.h"
#include "EsmSubAI_W.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
class CEsmInfo;
/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmNpc Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmNpc : public CEsmItem1 {
	DECLARE_SUBRECCREATE();

	/*---------- Begin Protected Class Members --------------------*/
  protected:
	CEsmSubNPDTS *m_pNpcShortData;
	CEsmSubNPDTL *m_pNpcLongData;
	CEsmSubLong *m_pFlag;
	CEsmSubNameFix *m_pRace;
	CEsmSubNameFix *m_pAnimation;
	CEsmSubNameFix *m_pFaction;
	CEsmSubNameFix *m_pHeadModel;
	CEsmSubNameFix *m_pClass;
	CEsmSubNameFix *m_pHairModel;
	CEsmSubAIDT *m_pAIData;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CEsmNpc();
	//virtual ~CEsmArmor() { Destroy(); }
	virtual void Destroy(void);

	/* Add item/spells to the NPC */
	bool AddItem(const TCHAR *pItemID);
	bool AddItemCount(const TCHAR *pItemID, const int Count);
	bool AddItemEx(const TCHAR *pString);
	bool AddSpell(const TCHAR *pSpell);

	/* Overload to account for the different NPC data record sizes */
	virtual CEsmSubRecord *AllocNewSubRecord(const TCHAR *pType, const long RecordSize = 0);

	/* Compare two fields of the record */
	virtual int CompareFields(const int FieldID, CEsmRecord *pRecord);

	/* Create a new record */
	static CEsmRecord *Create(void);

	/* Create a new, empty, record */
	virtual void CreateNew(CEsmFile *pFile);

	/* Ensure the correct data is allocated */
	void CreateNPCData(const bool IsShort);

	/* Checks if a dialogue info applies to the NPC */
	bool DoesInfoApply(CEsmInfo *pInfo);

	/* Find an item/spell record on the NPC */
	CEsmSubNPCO *FindItem(const TCHAR *pItemID);
	CEsmSubNPCS *FindSpell(const TCHAR *pSpellID);

	/* Get a string representation of a particular field */
	virtual const TCHAR *GetFieldString(const int FieldID);

	/* Return a text representation of the item type */
	virtual const TCHAR *GetItemType(void) {
		return _T("NPC");
	}

	/* Get NPC data */
	npcshortdata_t *GetShortData(void) {
		return (m_pNpcShortData ? m_pNpcShortData->GetNPCData() : NULL);
	}

	npclongdata_t *GetLongData(void) {
		return (m_pNpcLongData ? m_pNpcLongData->GetNPCData() : NULL);
	}

	aidata_t *GetAIData(void) {
		return (m_pAIData ? m_pAIData->GetAIData() : NULL);
	}

	const char *GetTravelCell(const int Index);

	/* Get string class members */
	const TCHAR *GetAnimation(void) {
		return (m_pAnimation ? m_pAnimation->GetName() : _T(""));
	}

	const TCHAR *GetHairModel(void) {
		return (m_pHairModel ? m_pHairModel->GetName() : _T(""));
	}

	const TCHAR *GetHeadModel(void) {
		return (m_pHeadModel ? m_pHeadModel->GetName() : _T(""));
	}

	const TCHAR *GetClass(void) {
		return (m_pClass ? m_pClass->GetName() : _T(""));
	}

	const TCHAR *GetRace(void) {
		return (m_pRace ? m_pRace->GetName() : _T(""));
	}

	const TCHAR *GetFaction(void) {
		return (m_pFaction ? m_pFaction->GetName() : _T(""));
	}

	/* Get class members */
	long GetDisposition(void);
	long GetFactionID(void);
	long GetGold(void);
	long GetLevel(void);
	long GetRank(void);
	long GetReputation(void);
	long GetHealth(void);
	long GetMagic(void);
	long GetFatigue(void);
	long GetSkill(const TCHAR *pString);
	long GetAttribute(const TCHAR *pString);
	long GetSkill(const int SkillIndex);
	long GetAttribute(const int AttrIndex);
	long GetFlag(void) {
		return (m_pFlag ? m_pFlag->GetValue() : 0);
	}

	long GetAIFlags(void) {
		return (m_pAIData ? m_pAIData->GetFlags() : 0);
	}

	bool IsAutoCalc(void) {
		return ((GetFlag() & MWESM_NPCFLAG_AUTOCALC) != 0);
	}

	bool IsRespawn(void) {
		return ((GetFlag() & MWESM_NPCFLAG_RESPAWN) != 0);
	}

	bool IsFemale(void) {
		return ((GetFlag() & MWESM_NPCFLAG_FEMALE) != 0);
	}

	bool IsEssential(void) {
		return ((GetFlag() & MWESM_NPCFLAG_ESSENTIAL) != 0);
	}

	bool IsAiBuyWeapon(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_WEAPON) : false);
	}

	bool IsAiBuyArmor(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_ARMOR) : false);
	}

	bool IsAiBuyClothing(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_CLOTHING) : false);
	}

	bool IsAiBuyBook(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_BOOK) : false);
	}

	bool IsAiBuyIngrediant(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_INGREDIANT) : false);
	}

	bool IsAiBuyPick(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_PICK) : false);
	}

	bool IsAiBuyProbe(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_PROBE) : false);
	}

	bool IsAiBuyLight(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_LIGHT) : false);
	}

	bool IsAiBuyApparatus(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_APPARATUS) : false);
	}

	bool IsAiBuyRepair(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_REPAIR) : false);
	}

	bool IsAiBuyMisc(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_MISC) : false);
	}

	bool IsAiBuySpell(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_SPELL) : false);
	}

	bool IsAiBuyMagicItem(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_MAGICITEM) : false);
	}

	bool IsAiBuyPotion(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_POTION) : false);
	}

	bool IsAiTraining(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_TRAINING) : false);
	}

	bool IsAiSpellMaking(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_SPELLMAKING) : false);
	}

	bool IsAiEnchanting(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_ENCHANTING) : false);
	}

	bool IsAiRepairItem(void) {
		return (m_pAIData ? m_pAIData->IsFlag(MWESM_AIFLAG_REPAIRITEM) : false);
	}

	/* Used to save the various record elements */
	virtual void OnAddSubRecord(CEsmSubRecord *pSubRecord);

	/* Set class methods */
	void SetFlag(const long Flag) {
		if (m_pFlag) {
			m_pFlag->SetValue(Flag);
		}
	}

	void SetAnimation(const TCHAR *pString);
	void SetDisposition(const int Value);
	void SetLevel(const int Value);
	void SetRank(const int Value);
	void SetGold(const long Value);
	void SetHealth(const long Value);
	void SetFatigue(const long Value);
	void SetSpellPts(const long Value);
	void SetFemale(const bool Flag) {
		if (m_pFlag) {
			m_pFlag->SetFlag(MWESM_NPCFLAG_FEMALE, Flag);
		}
	}

	void SetAutoCalc(const bool Flag);
	void SetRespawn(const bool Flag) {
		if (m_pFlag) {
			m_pFlag->SetFlag(MWESM_NPCFLAG_RESPAWN, Flag);
		}
	}

	void SetEssential(const bool Flag) {
		if (m_pFlag) {
			m_pFlag->SetFlag(MWESM_NPCFLAG_ESSENTIAL, Flag);
		}
	}

	void SetHairModel(const TCHAR *pString) {
		if (m_pHairModel) {
			m_pHairModel->SetName(pString);
		}
	}

	void SetHeadModel(const TCHAR *pString) {
		if (m_pHeadModel) {
			m_pHeadModel->SetName(pString);
		}
	}

	void SetClass(const TCHAR *pString) {
		if (m_pClass) {
			m_pClass->SetName(pString);
		}
	}

	void SetRace(const TCHAR *pString) {
		if (m_pRace) {
			m_pRace->SetName(pString);
		}
	}

	void SetFaction(const TCHAR *pString) {
		if (m_pFaction) {
			m_pFaction->SetName(pString);
		}
	}

	void SetBloodType(const TCHAR *pString);
	void SetSkill(const TCHAR *pString);
	void SetSkill(const TCHAR *pString, const int SkillIndex);
	void SetAttribute(const TCHAR *pString);
	void SetAttribute(const TCHAR *pString, const int AttrIndex);

	/* Set a certain field of the record */
	virtual bool SetFieldValue(const int FieldID, const TCHAR *pString);

};

/*===========================================================================
 *      End of Class CEsmNpc Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/

/* Function to convert blood type values */
const TCHAR *GetEsmNpcBloodType(const int Index);
int GetEsmNpcBloodType(const TCHAR *pString);

/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmNpc.H
 *=========================================================================*/
