/*===========================================================================
 *
 * File:    EsmsubRADT.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 3, 2003
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ESMSUBRADT_H
#define __ESMSUBRADT_H


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

/* Number of skill bonuses for each race */
#define MWESM_RACEDATA_NUMBONUSES 7

/* Race flags */
#define MWESM_RACEFLAG_PLAYABLE   1
#define MWESM_RACEFLAG_BEAST      2

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
	long SkillID;
	long Bonus;
} raceskilldata_t;

typedef struct {
	raceskilldata_t SkillBonuses[MWESM_RACEDATA_NUMBONUSES];
	long Strength[2];
	long Intelligence[2];
	long Willpower[2];
	long Agility[2];
	long Speed[2];
	long Endurance[2];
	long Personality[2];
	long Luck[2];
	float Height[2];
	float Weight[2];
	long Flags;
} racedata_t;

#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CEsmSubRADT Definition
 *
 * Description
 *
 *=========================================================================*/
class CEsmSubRADT : public CEsmSubRecord {

	/*---------- Begin Protected Class Members --------------------*/
  protected:


	/*---------- Begin Protected Class Methods --------------------*/
  protected:


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	//CEsmSubRADT();
	//virtual ~CEsmSubRADT() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a name object */
	static CEsmSubRecord *Create() {
		CEsmSubRecord *pSubRecord;
		CreatePointerL(pSubRecord, CEsmSubRADT);
		return pSubRecord;
	}

	/* Create a new sub-record */
	virtual void CreateNew() {
		CEsmSubRecord::CreateNew();
		CreateArrayPointerL(m_pData, byte, sizeof(racedata_t));
		m_RecordSize = sizeof(racedata_t);
		memset(m_pData, 0, sizeof(racedata_t));

		GetRaceData()->SkillBonuses[0].SkillID = 0;
		GetRaceData()->SkillBonuses[1].SkillID = 1;
		GetRaceData()->SkillBonuses[2].SkillID = 2;
		GetRaceData()->SkillBonuses[3].SkillID = 3;
		GetRaceData()->SkillBonuses[4].SkillID = 4;
		GetRaceData()->SkillBonuses[5].SkillID = 5;
		GetRaceData()->SkillBonuses[6].SkillID = 6;

		GetRaceData()->Strength[0] = 30;
		GetRaceData()->Strength[1] = 30;

		GetRaceData()->Intelligence[0] = 30;
		GetRaceData()->Intelligence[1] = 30;

		GetRaceData()->Willpower[0] = 30;
		GetRaceData()->Willpower[1] = 30;

		GetRaceData()->Agility[0] = 30;
		GetRaceData()->Agility[1] = 30;

		GetRaceData()->Speed[0] = 30;
		GetRaceData()->Speed[1] = 30;

		GetRaceData()->Endurance[0] = 30;
		GetRaceData()->Endurance[1] = 30;

		GetRaceData()->Personality[0] = 30;
		GetRaceData()->Personality[1] = 30;

		GetRaceData()->Luck[0] = 30;
		GetRaceData()->Luck[1] = 30;

		GetRaceData()->Height[0] = 1.0f;
		GetRaceData()->Height[1] = 1.0f;
		GetRaceData()->Weight[0] = 1.0f;
		GetRaceData()->Weight[1] = 1.0f;
	}

	/* Get class members */
	racedata_t *GetRaceData() {
		return (racedata_t *)m_pData;
	}

	long GetFlags() {
		return GetRaceData()->Flags;
	}

	bool IsPlayable() {
		return (GetFlags() & MWESM_RACEFLAG_PLAYABLE) != 0;
	}

	bool IsBeast() {
		return (GetFlags() & MWESM_RACEFLAG_BEAST) != 0;
	}

	long GetStrengthM() {
		return GetRaceData()->Strength[0];
	}

	long GetIntelligenceM() {
		return GetRaceData()->Intelligence[0];
	}

	long GetWillpowerM() {
		return GetRaceData()->Willpower[0];
	}

	long GetAgilityM() {
		return GetRaceData()->Agility[0];
	}

	long GetSpeedM() {
		return GetRaceData()->Speed[0];
	}

	long GetEnduranceM() {
		return GetRaceData()->Endurance[0];
	}

	long GetPersonalityM() {
		return GetRaceData()->Personality[0];
	}

	long GetLuckM() {
		return GetRaceData()->Luck[0];
	}

	long GetStrengthF() {
		return GetRaceData()->Strength[1];
	}

	long GetIntelligenceF() {
		return GetRaceData()->Intelligence[1];
	}

	long GetWillpowerF() {
		return GetRaceData()->Willpower[1];
	}

	long GetAgilityF() {
		return GetRaceData()->Agility[1];
	}

	long GetSpeedF() {
		return GetRaceData()->Speed[1];
	}

	long GetEnduranceF() {
		return GetRaceData()->Endurance[1];
	}

	long GetPersonalityF() {
		return GetRaceData()->Personality[1];
	}

	long GetLuckF() {
		return GetRaceData()->Luck[1];
	}

	float GetHeightM() {
		return GetRaceData()->Height[0];
	}

	float GetWeightM() {
		return GetRaceData()->Weight[0];
	}

	float GetHeightF() {
		return GetRaceData()->Height[1];
	}

	float GetWeightF() {
		return GetRaceData()->Weight[1];
	}

	/* Get skill bonuses */
	bool IsValidBonus(const int Index) {
		return Index >= 0 && Index < MWESM_RACEDATA_NUMBONUSES;
	}

	raceskilldata_t *GetBonusPtr(const int Index) {
		return IsValidBonus(Index) ? &GetRaceData()->SkillBonuses[Index] : NULL;
	}

	long GetBonus(const int Index) {
		return IsValidBonus(Index) ? GetRaceData()->SkillBonuses[Index].Bonus : -1;
	}

	long GetBonusSkill(const int Index) {
		return IsValidBonus(Index) ? GetRaceData()->SkillBonuses[Index].SkillID : -1;
	}

	/* Set or clear flags */
	void SetFlag(const long Flag, const bool Set) {
		if (Set) {
			GetRaceData()->Flags |= Flag;
		} else {
			GetRaceData()->Flags &= ~Flag;
		}
	}

	/* Set class members */
	void SetPlayable(const bool Flag) {
		SetFlag(MWESM_RACEFLAG_PLAYABLE, Flag);
	}

	void SetBeast(const bool Flag) {
		SetFlag(MWESM_RACEFLAG_BEAST, Flag);
	}

	void SetStrengthM(const long Value) {
		GetRaceData()->Strength[0] = Value;
	}

	void SetIntelligenceM(const long Value) {
		GetRaceData()->Intelligence[0] = Value;
	}

	void SetWillpowerM(const long Value) {
		GetRaceData()->Willpower[0] = Value;
	}

	void SetAgilityM(const long Value) {
		GetRaceData()->Agility[0] = Value;
	}

	void SetSpeedM(const long Value) {
		GetRaceData()->Speed[0] = Value;
	}

	void SetEnduranceM(const long Value) {
		GetRaceData()->Endurance[0] = Value;
	}

	void SetPersonalityM(const long Value) {
		GetRaceData()->Personality[0] = Value;
	}

	void SetLuckM(const long Value) {
		GetRaceData()->Luck[0] = Value;
	}

	void SetStrengthF(const long Value) {
		GetRaceData()->Strength[1] = Value;
	}

	void SetIntelligenceF(const long Value) {
		GetRaceData()->Intelligence[1] = Value;
	}

	void SetWillpowerF(const long Value) {
		GetRaceData()->Willpower[1] = Value;
	}

	void SetAgilityF(const long Value) {
		GetRaceData()->Agility[1] = Value;
	}

	void SetSpeedF(const long Value) {
		GetRaceData()->Speed[1] = Value;
	}

	void SetEnduranceF(const long Value) {
		GetRaceData()->Endurance[1] = Value;
	}

	void SetPersonalityF(const long Value) {
		GetRaceData()->Personality[1] = Value;
	}

	void SetLuckF(const long Value) {
		GetRaceData()->Luck[1] = Value;
	}

	void SetWeightM(const float Value) {
		GetRaceData()->Weight[0] = Value;
	}

	void SetHeightM(const float Value) {
		GetRaceData()->Height[0] = Value;
	}

	void SetWeightF(const float Value) {
		GetRaceData()->Weight[1] = Value;
	}

	void SetHeightF(const float Value) {
		GetRaceData()->Height[1] = Value;
	}

	/* Set a skill bonus */
	void SetBonusSkill(const int Index, const long SkillID) {
		if (IsValidBonus(Index)) {
			GetRaceData()->SkillBonuses[Index].SkillID = SkillID;
		}
	}

	void SetBonus(const int Index, const long Value) {
		if (IsValidBonus(Index)) {
			GetRaceData()->SkillBonuses[Index].Bonus = Value;
		}
	}

	void SetBonus(const int Index, const long SkillID, const long Value) {
		if (IsValidBonus(Index)) {
			GetRaceData()->SkillBonuses[Index].SkillID = SkillID;
			GetRaceData()->SkillBonuses[Index].Bonus = Value;
		}
	}
};

/*===========================================================================
 *      End of Class CEsmSubRADT Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File EsmsubRIDT.H
 *=========================================================================*/
