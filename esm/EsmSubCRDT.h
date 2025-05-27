/*===========================================================================
 *
 * File:    EsmsubCTDT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * For the NPDT data in the creature records.
 *
 *=========================================================================*/
#ifndef __ESMSUBCRDT_H
#define __ESMSUBCRDT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
#include "EsmSubBase.h"
/*===========================================================================
 *      End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Creature types */
#define MWESM_CREATYPE_MIN      0
#define MWESM_CREATYPE_CREATURE 0
#define MWESM_CREATYPE_DAEDRA   1
#define MWESM_CREATYPE_UNDEAD   2
#define MWESM_CREATYPE_HUMANIOD 3
#define MWESM_CREATYPE_MAX      3

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

typedef struct {
	long Type;
	long Level;
	long Strength;
	long Intelligence;
	long Willpower;
	long Agility;
	long Speed;
	long Endurance;
	long Personality;
	long Luck;
	long Health;
	long SpellPts;
	long Fatigue;
	long Soul;
	long Combat;
	long Magic;
	long Stealth;
	long AttackMin1;
	long AttackMax1;
	long AttackMin2;
	long AttackMax2;
	long AttackMin3;
	long AttackMax3;
	long Gold;
} creaturedata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubCRDT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubCRDT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubCRDT();
	//virtual ~CEsmSubCRDT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create(void) {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubCRDT);
		return (pSubRecord);
	}

	/* Create a new sub-record */
	virtual void CreateNew(void) {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(creaturedata_t));
		m_RecordSize = sizeof(creaturedata_t);
		memset(m_pData, 0, sizeof(creaturedata_t));
	}

	/* Get class members */
	creaturedata_t *GetCreatureData(void) {
		return ((creaturedata_t *)m_pData);
	}

	long GetCreaType(void) {
		return (GetCreatureData()->Type);
	}

	long GetLevel(void) {
		return (GetCreatureData()->Level);
	}

	long GetStrength(void) {
		return (GetCreatureData()->Strength);
	}

	long GetIntelligence(void) {
		return (GetCreatureData()->Intelligence);
	}

	long GetWillpower(void) {
		return (GetCreatureData()->Willpower);
	}

	long GetAgility(void) {
		return (GetCreatureData()->Agility);
	}

	long GetSpeed(void) {
		return (GetCreatureData()->Speed);
	}

	long GetEndurance(void) {
		return (GetCreatureData()->Endurance);
	}

	long GetPersonality(void) {
		return (GetCreatureData()->Personality);
	}

	long GetLuck(void) {
		return (GetCreatureData()->Luck);
	}

	long GetHealth(void) {
		return (GetCreatureData()->Health);
	}

	long GetSpellPts(void) {
		return (GetCreatureData()->SpellPts);
	}

	long GetFatigue(void) {
		return (GetCreatureData()->Fatigue);
	}

	long GetSoul(void) {
		return (GetCreatureData()->Soul);
	}

	long GetCombat(void) {
		return (GetCreatureData()->Combat);
	}

	long GetMagic(void) {
		return (GetCreatureData()->Magic);
	}

	long GetStealth(void) {
		return (GetCreatureData()->Stealth);
	}

	long GetAttackMin1(void) {
		return (GetCreatureData()->AttackMin1);
	}

	long GetAttackMin2(void) {
		return (GetCreatureData()->AttackMin2);
	}

	long GetAttackMin3(void) {
		return (GetCreatureData()->AttackMin3);
	}

	long GetAttackMax1(void) {
		return (GetCreatureData()->AttackMax1);
	}

	long GetAttackMax2(void) {
		return (GetCreatureData()->AttackMax2);
	}

	long GetAttackMax3(void) {
		return (GetCreatureData()->AttackMax3);
	}

	long GetGold(void) {
		return (GetCreatureData()->Gold);
	}

	/* Set class members */
	void SetCreaType(const long Type) {
		if (Type >= MWESM_CREATYPE_MIN && Type <= MWESM_CREATYPE_MAX) {
			GetCreatureData()->Type = Type;
		}
	}

	void SetLevel(const long Value) {
		GetCreatureData()->Level = Value;
	}

	void SetStrength(const long Value) {
		GetCreatureData()->Strength = Value;
	}

	void SetIntelligence(const long Value) {
		GetCreatureData()->Intelligence = Value;
	}

	void SetWillpower(const long Value) {
		GetCreatureData()->Willpower = Value;
	}

	void SetAgility(const long Value) {
		GetCreatureData()->Agility = Value;
	}

	void SetSpeed(const long Value) {
		GetCreatureData()->Speed = Value;
	}

	void SetEndurance(const long Value) {
		GetCreatureData()->Endurance = Value;
	}

	void SetPersonality(const long Value) {
		GetCreatureData()->Personality = Value;
	}

	void SetLuck(const long Value) {
		GetCreatureData()->Luck = Value;
	}

	void SetHealth(const long Value) {
		GetCreatureData()->Health = Value;
	}

	void SetSpellPts(const long Value) {
		GetCreatureData()->SpellPts = Value;
	}

	void SetFatigue(const long Value) {
		GetCreatureData()->Fatigue = Value;
	}

	void SetSoul(const long Value) {
		GetCreatureData()->Soul = Value;
	}

	void SetCombat(const long Value) {
		GetCreatureData()->Combat = Value;
	}

	void SetMagic(const long Value) {
		GetCreatureData()->Magic = Value;
	}

	void SetStealth(const long Value) {
		GetCreatureData()->Stealth = Value;
	}

	void SetAttackMin1(const long Value) {
		GetCreatureData()->AttackMin1 = Value;
	}

	void SetAttackMin2(const long Value) {
		GetCreatureData()->AttackMin2 = Value;
	}

	void SetAttackMin3(const long Value) {
		GetCreatureData()->AttackMin3 = Value;
	}

	void SetAttackMax1(const long Value) {
		GetCreatureData()->AttackMax1 = Value;
	}

	void SetAttackMax2(const long Value) {
		GetCreatureData()->AttackMax2 = Value;
	}

	void SetAttackMax3(const long Value) {
		GetCreatureData()->AttackMax3 = Value;
	}

	void SetGold(const long Value) {
		GetCreatureData()->Gold = Value;
	}

};

/*===========================================================================
 *      End of Class CEsmSubCRDT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubaCRDT.H
 *=========================================================================*/
