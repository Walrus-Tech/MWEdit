/*===========================================================================
 *
 * File:    Esmbase.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  February 7, 2003
 *
 * Description
 *
 * 4 January 2004
 *  - Changed the local attributes array to a valuenames_t, including
 *    the 3-character attribute abbreviations. Modified the local
 *    attribute functions accordingly.
 *
 *=========================================================================*/
#include "esm/EsmDefs.h"
#include "Common/dl_str.h"
#include "Common/Utility/namelist.h"
#include "project/EsmGlobOptions.h"


DEFINE_FILE("EsmBase.cpp")


/*===========================================================================
 *
 * Begin Magic Effect Array
 *
 *=========================================================================*/
#define EFF_DUR MWESM_EFFECTFLAG_HASDUR
#define EFF_MAG MWESM_EFFECTFLAG_HASMAG
#define EFF_ALC MWESM_EFFECTFLAG_ALCHEMY
#define EFF_DEF EFF_DUR | EFF_ALC | EFF_MAG
#define EFF_SEL MWESM_EFFECTFLAG_SELFONLY
#define EFF_NOS MWESM_EFFECTFLAG_NOSELF
#define EFF_TRB MWESM_EFFECTFLAG_TRIB
#define EFF_BLD MWESM_EFFECTFLAG_BLDM

esmeffectdata_t l_Effects[MWESM_MAX_EFFECTS] = {
	{
		_T("Water Breathing"),
		EFF_DUR | EFF_ALC,
		_T("sEffectWaterBreathing")
	},
	{
		_T("Swift Swim"),
		EFF_DEF,
		_T("sEffectSwiftSwim")
	},
	{
		_T("Water Walking"),
		EFF_DUR | EFF_ALC,
		_T("sEffectWaterWalking")
	},
	{
		_T("Shield"),
		EFF_DEF,
		_T("sEffectShield")
	},
	{
		_T("Fire Shield"),
		EFF_DEF,
		_T("sEffectFireShield")
	},
	{
		_T("Lightning Shield"),
		EFF_DEF,
		_T("sEffectLightningShield")
	},
	{
		_T("Frost Shield"),
		EFF_DEF,
		_T("sEffectFrostShield")
	},
	{
		_T("Burden"),
		EFF_DEF,
		_T("sEffectBurden")
	},
	{
		_T("Feather"),
		EFF_DEF,
		_T("sEffectFeather")
	},
	{
		_T("Jump"),
		EFF_DEF,
		_T("sEffectJump")
	},
	{
		_T("Levitate"),
		EFF_DEF,
		_T("sEffectLevitate")
	},
	{
		_T("SlowFall"),
		EFF_DEF,
		_T("sEffectSlowFall")
	},
	{
		_T("Lock"),
		EFF_DEF | EFF_NOS,
		_T("sEffectLock")
	},
	{
		_T("Open"),
		EFF_DEF | EFF_NOS,
		_T("sEffectOpen")
	},
	{
		_T("Fire Damage"),
		EFF_DEF,
		_T("sEffectFireDamage")
	},
	{
		_T("Shock Damage"),
		EFF_DEF,
		_T("sEffectShockDamage")
	},
	{
		_T("Frost Damage"),
		EFF_DEF,
		_T("sEffectFrostDamage")
	},
	{
		_T("Drain Attribute"),
		EFF_DEF,
		_T("sEffectDrainAttribute")
	},
	{
		_T("Drain Health"),
		EFF_DEF,
		_T("sEffectDrainHealth")
	},
	{
		_T("Drain Magicka"),
		EFF_DEF,
		_T("sEffectDrainSpellpoints")
	},
	{
		_T("Drain Fatigue"),
		EFF_DEF,
		_T("sEffectDrainFatigue")
	},
	{
		_T("Drain Skill"),
		EFF_DEF,
		_T("sEffectDrainSkill")
	},
	{
		_T("Damage Attribute"),
		EFF_DEF,
		_T("sEffectDamageAttribute")
	},
	{
		_T("Damage Health"),
		EFF_DEF,
		_T("sEffectDamageHealth")
	},
	{
		_T("Damage Magicka"),
		EFF_DEF,
		_T("sEffectDamageMagicka")
	},
	{
		_T("Damage Fatigue"),
		EFF_DEF,
		_T("sEffectDamageFatigue")
	},
	{
		_T("Damage Skill"),
		EFF_DEF,
		_T("sEffectDamageSkill")
	},
	{
		_T("Poison"),
		EFF_DEF,
		_T("sEffectPoison")
	},
	{
		_T("Weakness to Fire"),
		EFF_DEF,
		_T("sEffectWeaknessToFire")
	},
	{
		_T("Weakness to Frost"),
		EFF_DEF,
		_T("sEffectWeaknessToFrost")
	},
	{
		_T("Weakness to Shock"),
		EFF_DEF,
		_T("sEffectWeaknessToShock")
	},
	{
		_T("Weakness to Magicka"),
		EFF_DEF,
		_T("sEffectWeaknessToMagicka")
	},
	{
		_T("Weakness to Common Disease"),
		EFF_DEF,
		_T("sEffectWeaknessToCommonDisease")
	},
	{
		_T("Weakness to Blight Disease"),
		EFF_DEF,
		_T("sEffectWeaknessToBlightDisease")
	},
	{
		_T("Weakness to Corprus Disease"),
		EFF_DEF,
		_T("sEffectWeaknessToCorprusDisease")
	},
	{
		_T("Weakness to Poison"),
		EFF_DEF,
		_T("sEffectWeaknessToPoison")
	},
	{
		_T("Weakness to Normal Weapons"),
		EFF_DEF,
		_T("sEffectWeaknessToNormalWeapons")
	},
	{
		_T("Disintegrate Weapon"),
		EFF_DEF,
		_T("sEffectDisintegrateWeapon")
	},
	{
		_T("Disintegrate Armor"),
		EFF_DEF,
		_T("sEffectDisintegrateArmor")
	},
	{
		_T("Invisibility"),
		EFF_MAG | EFF_ALC,
		_T("sEffectInvisibility")
	},
	{
		_T("Chameleon"),
		EFF_DEF,
		_T("sEffectChameleon")
	},
	{
		_T("Light"),
		EFF_DEF,
		_T("sEffectLight")
	},
	{
		_T("Sanctuary"),
		EFF_DEF,
		_T("sEffectSanctuary")
	},
	{
		_T("Night Eye"),
		EFF_DEF,
		_T("sEffectNightEye")
	},
	{
		_T("Charm"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectCharm")
	},
	{
		_T("Paralyze"),
		EFF_DUR | EFF_ALC,
		_T("sEffectParalyze")
	},
	{
		_T("Silence"),
		EFF_DUR | EFF_ALC,
		_T("sEffectSilence")
	},
	{
		_T("Blind"),
		EFF_DUR | EFF_ALC | EFF_MAG,
		_T("sEffectBlind")
	},
	{
		_T("Sound"),
		EFF_DEF,
		_T("sEffectSound")
	},
	{
		_T("Calm Humanoid"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectCalmHumanoid")
	},
	{
		_T("Calm Creature"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectCalmCreature")
	},
	{
		_T("Frenzy Humanoid"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectFrenzyHumanoid")
	},
	{
		_T("Frenzy Creature"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectFrenzyCreature")
	},
	{
		_T("Demoralize Humanoid"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectDemoralizeHumanoid")
	},
	{
		_T("Demoralize Creature"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectDemoralizeCreature")
	},
	{
		_T("Rally Humanoid"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectRallyHumanoid")
	},
	{
		_T("Rally Creature"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectRallyCreature")
	},
	{
		_T("Dispel"),
		EFF_MAG | EFF_ALC,
		_T("sEffectDispel")
	},
	{
		_T("Soultrap"),
		EFF_DUR | EFF_NOS,
		_T("sEffectSoultrap")
	},
	{
		_T("Telekinesis"),
		EFF_DEF | EFF_SEL,
		_T("sEffectTelekinesis")
	},
	{
		_T("Mark"),
		EFF_ALC | EFF_SEL,
		_T("sEffectMark")
	},
	{
		_T("Recall"),
		EFF_ALC | EFF_SEL,
		_T("sEffectRecall")
	},
	{
		_T("Divine Intervention"),
		EFF_ALC | EFF_SEL,
		_T("sEffectDivineIntervention")
	},
	{
		_T("Almsivi Intervention"),
		EFF_ALC | EFF_SEL,
		_T("sEffectAlmsiviIntervention")
	},
	{
		_T("Detect Animal"),
		EFF_DEF | EFF_SEL,
		_T("sEffectDetectAnimal")
	},
	{
		_T("Detect Enchantment"),
		EFF_DEF | EFF_SEL,
		_T("sEffectDetectEnchantment")
	},
	{
		_T("Detect Key"),
		EFF_DEF | EFF_SEL,
		_T("sEffectDetectKey")
	},
	{
		_T("Spell Absorption"),
		EFF_DEF,
		_T("sEffectSpellAbsorption")
	},
	{
		_T("Reflect"),
		EFF_DEF,
		_T("sEffectReflect")
	},
	{
		_T("Cure Common Disease"),
		EFF_ALC,
		_T("sEffectCureCommonDisease")
	},
	{
		_T("Cure Blight Disease"),
		EFF_ALC,
		_T("sEffectCureBlightDisease")
	},
	{
		_T("Cure Corprus Disease"),
		EFF_ALC,
		_T("sEffectCureCorprusDisease")
	},
	{
		_T("Cure Poison"),
		EFF_ALC,
		_T("sEffectCurePoison")
	},
	{
		_T("Cure Paralyzation"),
		EFF_ALC,
		_T("sEffectCureParalyzation")
	},
	{
		_T("Restore Attribute"),
		EFF_DEF,
		_T("sEffectRestoreAttribute")
	},
	{
		_T("Restore Health"),
		EFF_DEF,
		_T("sEffectRestoreHealth")
	},
	{
		_T("Restore Magicka"),
		EFF_DEF,
		_T("sEffectRestoreSpellPoints")
	},
	{
		_T("Restore Fatigue"),
		EFF_DEF,
		_T("sEffectRestoreFatigue")
	},
	{
		_T("Restore Skill"),
		EFF_DEF,
		_T("sEffectRestoreSkill")
	},
	{
		_T("Fortify Attribute"),
		EFF_DEF,
		_T("sEffectFortifyAttribute")
	},
	{
		_T("Fortify Health"),
		EFF_DEF,
		_T("sEffectFortifyHealth")
	},
	{
		_T("Fortify Magicka"),
		EFF_DEF,
		_T("sEffectFortifySpellpoints")
	},
	{
		_T("Fortify Fatigue"),
		EFF_DEF,
		_T("sEffectFortifyFatigue")
	},
	{
		_T("Fortify Skill"),
		EFF_DEF,
		_T("sEffectFortifySkill")
	},
	{
		_T("Fortify Maximum Magicka"),
		EFF_DEF,
		_T("sEffectFortifyMagickaMultiplier")
	},
	{
		_T("Absorb Attribute"),
		EFF_DEF,
		_T("sEffectAbsorbAttribute")
	},
	{
		_T("Absorb Health"),
		EFF_DEF,
		_T("sEffectAbsorbHealth")
	},
	{
		_T("Absorb Magicka"),
		EFF_DEF,
		_T("sEffectAbsorbSpellPoints")
	},
	{
		_T("Absorb Fatigue"),
		EFF_DEF,
		_T("sEffectAbsorbFatigue")
	},
	{
		_T("Absorb Skill"),
		EFF_DEF,
		_T("sEffectAbsorbSkill")
	},
	{
		_T("Resist Fire"),
		EFF_DEF,
		_T("sEffectResistFire")
	},
	{
		_T("Resist Frost"),
		EFF_DEF,
		_T("sEffectResistFrost")
	},
	{
		_T("Resist Shock"),
		EFF_DEF,
		_T("sEffectResistShock")
	},
	{
		_T("Resist Magicka"),
		EFF_DEF,
		_T("sEffectResistMagicka")
	},
	{
		_T("Resist Common Disease"),
		EFF_DEF,
		_T("sEffectResistCommonDisease")
	},
	{
		_T("Resist Blight Disease"),
		EFF_DEF,
		_T("sEffectResistBlightDisease")
	},
	{
		_T("Resist Corprus Disease"),
		EFF_DEF,
		_T("sEffectResistCorprusDisease")
	},
	{
		_T("Resist Poison"),
		EFF_DEF,
		_T("sEffectResistPoison")
	},
	{
		_T("Resist Normal Weapons"),
		EFF_DEF,
		_T("sEffectResistNormalWeapons")
	},
	{
		_T("Resist Paralysis"),
		EFF_DEF,
		_T("sEffectResistParalysis")
	},
	{
		_T("Remove Curse"),
		EFF_DEF,
		_T("sEffectRemoveCurse")
	},
	{
		_T("Turn Undead"),
		EFF_DUR | EFF_NOS | EFF_SEL,
		_T("sEffectTurnUndead")
	},
	{
		_T("Summon Scamp"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonScamp")
	},
	{
		_T("Summon Clannfear"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonClannfear")
	},
	{
		_T("Summon Daedroth"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonDaedroth")
	},
	{
		_T("Summon Dremora"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonDremora")
	},
	{
		_T("Summon Ancestral Ghost"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonAncestralGhost")
	},
	{
		_T("Summon Skeletal Minion"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonSkeletalMinion")
	},
	{
		_T("Summon Bonewalker"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonLeastBonewalker")
	},
	{
		_T("Summon Greater Bonewalker"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonGreaterBonewalker")
	},
	{
		_T("Summon Bonelord"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonBonelord")
	},
	{
		_T("Summon Winged Twilight"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonWingedTwilight")
	},
	{
		_T("Summon Hunger"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonHunger")
	},
	{
		_T("Summon Golden Saint"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonGoldensaint")
	},
	{
		_T("Summon Flame Atronach"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonFlameAtronach")
	},
	{
		_T("Summon Frost Atronach"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonFrostAtronach")
	},
	{
		_T("Summon Storm Atronach"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonStormAtronach")
	},
	{
		_T("Fortify Attack"),
		EFF_DEF,
		_T("sEffectFortifyAttackBonus")
	},
	{
		_T("Command Creature"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectCommandCreatures")
	},
	{
		_T("Command Humanoid"),
		EFF_DUR | EFF_MAG | EFF_NOS,
		_T("sEffectCommandHumanoids")
	},
	{
		_T("Bound Dagger"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundDagger")
	},
	{
		_T("Bound Longsword"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundLongsword")
	},
	{
		_T("Bound Mace"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundMace")
	},
	{
		_T("Bound Battle Axe"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundBattleAxe")
	},
	{
		_T("Bound Spear"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundSpear")
	},
	{
		_T("Bound Longbow"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundLongbow")
	},
	{
		_T("EXTRA SPELL"),
		0,
		_T("sEffectExtraSpell")
	},
	{
		_T("Bound Cuirass"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundCuirass")
	},
	{
		_T("Bound Helm"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundHelm")
	},
	{
		_T("Bound Boots"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundBoots")
	},
	{
		_T("Bound Shield"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundShield")
	},
	{
		_T("Bound Gloves"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectBoundGloves")
	},
	{
		_T("Corprus"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectCorpus")
	},
	{
		_T("Vampirism"),
		EFF_ALC | EFF_SEL,
		_T("sEffectVampirism")
	},
	{
		_T("Summon Centurion Sphere"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCenturionSphere")
	},
	{
		_T("Sun Damage"),
		EFF_DEF | EFF_SEL,
		_T("sEffectSunDamage")
	},
	{
		_T("Stunted Magicka"),
		EFF_DUR | EFF_ALC | EFF_SEL,
		_T("sEffectStuntedMagicka")
	},
	{
		_T("sEffectSummonFabricant"),
		EFF_DUR | EFF_TRB | EFF_ALC | EFF_SEL,
		_T("sEffectSummonFabricant")
	},
	{
		_T("Call Wolf"),
		EFF_DUR | EFF_BLD | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCreature01")
	},
	{
		_T("Call Bear"),
		EFF_DUR | EFF_BLD | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCreature02")
	},
	{
		_T("Summon Bonewolf"),
		EFF_DUR | EFF_BLD | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCreature03")
	},
	{
		_T("sEffectSummonCreature04"),
		EFF_DUR | EFF_BLD | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCreature04")
	},
	{
		_T("sEffectSummonCreature05"),
		EFF_DUR | EFF_BLD | EFF_ALC | EFF_SEL,
		_T("sEffectSummonCreature05")
	}
};


/*===========================================================================
 *
 * Begin Skill Array
 *
 *=========================================================================*/
esmskilldata_t l_Skills[] = {
	{
		_T("Block"),
		_T("Successful Block"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Armorer"),
		_T("Successful Repair"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Medium Armor"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Heavy Armor"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Blunt Weapon"),
	 	_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Long Blade"),
		_T("Successful Attack"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Axe"),
		_T("Successful Attack"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Spear"),
		_T("Successful Attack"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Athletics"),
		_T("Second of Running"),
		_T("Second of Swimming"),
		NULL,
		NULL
	},
	{
		_T("Enchant"),
		_T("Recharge Item"),
		_T("Use Magic Item"),
		_T("Create Magic Item"),
		_T("Cast When Strikes")
	},
	{
		_T("Destruction"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Alteration"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Illusion"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Conjuration"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Mysticism"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Restoration"),
		_T("Successful Cast"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Alchemy"),
		_T("Potion Use"),
		_T("Ingrediant Use"),
		NULL,
		NULL
	},
	{
		_T("Unarmored"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Security"),
		_T("Defeat Trap"),
		_T("Pick Lock"),
		NULL,
		NULL
	},
	{
		_T("Sneak"),
		_T("Avoid Notice"),
		_T("Successful Pick Pocket"),
		NULL,
		NULL
	},
	{
		_T("Acrobatics"),
		_T("Jump"),
		_T("Fall"),
		NULL,
		NULL
	},
	{
		_T("Light Armor"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Short Blade"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Marksman"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	},
	{
		_T("Mercantile"),
		_T("Successful Bargain"),
		_T("Successful Bribe"),
		NULL,
		NULL
	},
	{
		_T("Speechcraft"),
		_T("Successful Persuasion"),
		_T("Failed Persuasion"),
		NULL,
		NULL
	},
	{
		_T("Hand-to-hand"),
		_T("Hit by Opponent"),
		NULL,
		NULL,
		NULL
	}
};


/*===========================================================================
 *
 * Begin Attribute Array
 *
 *=========================================================================*/
static valuenames_t l_Attributes[] = {
	{
		0,
		_T("Strength")
	},
	{
		1,
		_T("Intelligence")
	},
	{
		2,
		_T("Willpower")
	},
	{
		3,
		_T("Agility")
	},
	{
		4,
		_T("Speed")
	},
	{
		5,
		_T("Endurance")
	},
	{
		6,
		_T("Personality")
	},
	{
		7,
		_T("Luck")
	},
	{
		0,
		_T("Str")
	},
	{
		1,
		_T("Int")
	},
	{
		2,
		_T("Wil")
	},
	{
		3,
		_T("Agi")
	},
	{
		4,
		_T("Spd")
	},
	{
		5,
		_T("End")
	},
	{
		6,
		_T("Per")
	},
	{
		7,
		_T("Luc")
	},
	{
		0,
		NULL
	} /* Must be last element, must have 0 value */
};


/*===========================================================================
 *
 * Begin Spell Schools Array
 *
 *=========================================================================*/
const TCHAR *l_SpellSchools[] = {
	_T("Alteration"),
	_T("Conjuration"),
	_T("Destruction"),
	_T("Illusion"),
	_T("Mysticism"),
	_T("Restoration")
};


/*===========================================================================
 *
 * Begin Animation Groups Array
 *
 * At some point the values for the animation changed (possibly with one
 * of the expansions).
 *
 * In the latest Morrowind.exe the animation table starts at 0x38A970
 *
 *=========================================================================*/
esmanimdata_t l_AnimData[] = {
	{
		"Attack1",
		0x83,
		-1
	},
	{
		"Attack2",
		0x84,
		-1
	},
	{
		"Attack3",
		0x85,
		-1
	},
	{
		"Block Hit",
		0xA2,
		-1
	},
	{
		"Block Start",
		0x9A,
		-1
	},
	{
		"Block Stop",
		0xAA,
		-1
	},
	{
		"BowAndArrow",
		0x8B,
		0x83
	},
	{
		"Chop Hit",
		0x145,
		-1
	},
	{
		"Chop Large Follow Start",
		0x16D,
		-1
	},
	{
		"Chop Large Follow Stop",
		0x175,
		-1
	},
	{
		"Chop Max Attack",
		0x135,
		-1
	},
	{
		"Chop Medium Follow Start",
		0x15D,
		-1
	},
	{
		"Chop Medium Follow Stop",
		0x165,
		-1
	},
	{
		"Chop Min Attack",
		0x12D,
		-1
	},
	{
		"Chop Min Hit",
		0x13D,
		-1
	},
	{
		"Chop Small Follow Start",
		0x14D,
		-1
	},
	{
		"Chop Small Follow Stop",
		0x155,
		-1
	},
	{
		"Chop Start",
		0x125,
		-1
	},
	{
		"Crossbow",
		0x8A,
		0x82
	},
	{
		"Death1",
		0x1B,
		0x18
	},
	{
		"Death2",
		0x1C,
		0x19
	},
	{
		"Death3",
		0x1D,
		0x1A
	},
	{
		"Death4",
		0x1E,
		0x1B
	},
	{
		"Death5",
		0x1F,
		0x1C
	},
	{
		"DeathKnockDown",
		0x20,
		0x1D
	},
	{
		"DeathKnockOut",
		0x21,
		0x1E
	},
	{
		"Equip Attach",
		0xA3,
		-1
	},
	{
		"Equip Start",
		0x99,
		-1
	},
	{
		"Equip Stop",
		0xA9,
		-1
	},
	{
		"HandToHand",
		0x89,
		0x81
	},
	{
		"Hit1",
		0x13,
		0x13
	},
	{
		"Hit2",
		0x14,
		0x14
	},
	{
		"Hit3",
		0x15,
		0x16
	},
	{
		"Hit4",
		0x16,
		0x15
	},
	{
		"Hit5",
		0x17,
		0x17
	},
	{
		"idle",
		0x00,
		0x00
	},
	{
		"idle1h",
		0x0A,
		0x0A
	},
	{
		"idle2",
		0x01,
		0x01
	},
	{
		"idle2c",
		0x0B,
		0x0B
	},
	{
		"idle2w",
		0x0C,
		0x0C
	},
	{
		"idle3",
		0x02,
		0x02
	},
	{
		"idle4",
		0x03,
		0x03
	},
	{
		"idle5",
		0x04,
		0x04
	},
	{
		"idle6",
		0x05,
		0x05
	},
	{
		"idle7",
		0x06,
		0x06
	},
	{
		"idle8",
		0x07,
		0x07
	},
	{
		"idle9",
		0x08,
		0x08
	},
	{
		"idleCrossBow",
		0x0F,
		0x0F
	},
	{
		"idlehh",
		0x09,
		0x09
	},
	{
		"idleSneak",
		0x10,
		0x10
	},
	{
		"idleSpell",
		0x0E,
		0x0E
	},
	{
		"idleStorm",
		0x11,
		0x11
	},
	{
		"idleSwim",
		0x0D,
		0x0D
	},
	{
		"InventoryHandToHand",
		0x92,
		0x8A
	},
	{
		"InventoryWeaponOneHand",
		0x93,
		0x8B
	},
	{
		"InventoryWeaponTwoHand",
		0x94,
		0x8C
	},
	{
		"InventoryWeaponTwoWide",
		0x95,
		0x8D
	},
	{
		"Jump",
		0x43,
		0x3E
	},
	{
		"Jump1h",
		0x61,
		0x5C
	},
	{
		"Jump2c",
		0x70,
		0x6B
	},
	{
		"Jump2w",
		0x7F,
		0x7A
	},
	{
		"Jumphh",
		0x52,
		0x4D
	},
	{
		"KnockDown",
		0x22,
		0x1F
	},
	{
		"KnockOut",
		0x23,
		0x20
	},
	{
		"Loop Start",
		0xA7,
		-1
	},
	{
		"Loop Stop",
		0xAF,
		-1
	},
	{
		"PickProbe",
		0x91,
		0x89
	},
	{
		"RunBack",
		0x3C,
		0x37
	},
	{
		"RunBack1h",
		0x5A,
		0x55
	},
	{
		"RunBack2c",
		0x69,
		0x64
	},
	{
		"RunBack2w",
		0x78,
		0x73
	},
	{
		"RunBackhh",
		0x4B,
		0x46
	},
	{
		"RunForward",
		0x3B,
		0x36
	},
	{
		"RunForward1h",
		0x59,
		0x54
	},
	{
		"RunForward2c",
		0x68,
		0x63
	},
	{
		"RunForward2w",
		0x77,
		0x72
	},
	{
		"RunForwardhh",
		0x4A,
		0x45
	},
	{
		"RunLeft",
		0x3D,
		0x38
	},
	{
		"RunLeft1h",
		0x5B,
		0x56
	},
	{
		"RunLeft2c",
		0x6A,
		0x65
	},
	{
		"RunLeft2w",
		0x79,
		0x74
	},
	{
		"RunLefthh",
		0x4C,
		0x47
	},
	{
		"RunRight1h",
		0x5C,
		0x57
	},
	{
		"RunRight2c",
		0x6B,
		0x66
	},
	{
		"RunRight2w",
		0x7A,
		0x75
	},
	{
		"RunRighthh",
		0x4D,
		0x48
	},
	{
		"Self Release",
		0xD4,
		-1
	},
	{
		"Self Start",
		0xCC,
		-1
	},
	{
		"Self Stop",
		0xDC,
		-1
	},
	{
		"Shield",
		0x90,
		0x88
	},
	{
		"Shoot Attach",
		0xD1,
		-1
	},
	{
		"Shoot Follow Attach",
		0x101,
		-1
	},
	{
		"Shoot Follow Start",
		0xF9,
		-1
	},
	{
		"Shoot Follow Stop",
		0x109,
		-1
	},
	{
		"Shoot Max Attack",
		0xE1,
		-1
	},
	{
		"Shoot Min Attack",
		0xD9,
		-1
	},
	{
		"Shoot Min Hit",
		0xE9,
		-1
	},
	{
		"Shoot Release",
		0xF1,
		-1
	},
	{
		"Shoot Start",
		0xC9,
		-1
	},
	{
		"Slash Hit",
		0xED,
		-1
	},
	{
		"Slash Large Follow Start",
		0x115,
		-1
	},
	{
		"Slash Large Follow Stop",
		0x11D,
		-1
	},
	{
		"Slash Max Attack",
		0xDD,
		-1
	},
	{
		"Slash Medium Follow Start",
		0x105,
		-1
	},
	{
		"Slash Medium Follow Stop",
		0x10D,
		-1
	},
	{
		"Slash Min Attack",
		0xD5,
		-1
	},
	{
		"Slash Min Hit",
		0xE5,
		-1
	},
	{
		"Slash Small Follow Start",
		0xF5,
		-1
	},
	{
		"Slash Small Follow Stop",
		0xFD,
		-1
	},
	{
		"Slash Start",
		0xCD,
		-1
	},
	{
		"SneakBack",
		0x40,
		0x3B
	},
	{
		"SneakBack1h",
		0x5E,
		0x59
	},
	{
		"SneakBack2c",
		0x6D,
		0x68
	},
	{
		"SneakBack2w",
		0x7C,
		0x77
	},
	{
		"SneakBackhh",
		0x4F,
		0x4A
	},
	{
		"SneakForward",
		0x3F,
		0x3A
	},
	{
		"SneakForward1h",
		0x5D,
		0x58
	},
	{
		"SneakForward2c",
		0x6C,
		0x67
	},
	{
		"SneakForward2w",
		0x7B,
		0x76
	},
	{
		"SneakForwardhh",
		0x4E,
		0x49
	},
	{
		"SneakLeft",
		0x41,
		0x3C
	},
	{
		"SneakLeft1h",
		0x5F,
		0x5A
	},
	{
		"SneakLeft2c",
		0x6E,
		0x69
	},
	{
		"SneakLeft2w",
		0x7D,
		0x78
	},
	{
		"SneakLefthh",
		0x50,
		0x4B
	},
	{
		"SneakRight",
		0x42,
		0x3D
	},
	{
		"SneakRight1h",
		0x60,
		0x5B
	},
	{
		"SneakRight2c",
		0x6F,
		0x6A
	},
	{
		"SneakRight2w",
		0x7E,
		0x79
	},
	{
		"SneakRighthh",
		0x51,
		0x4C
	},
	{
		"SpellCast",
		0x80,
		0x7B
	},
	{
		"SpellTurnRight",
		0x82,
		0x7D
	},
	{
		"SpellTurnLeft",
		0x81,
		0x7C
	},
	{
		"Start",
		0x96,
		-1
	},
	{
		"Stop",
		0xD3,
		-1
	},
	{
		"SwimAttack1",
		0x86,
		-1
	},
	{
		"SwimAttack2",
		0x87,
		-1
	},
	{
		"SwimAttack3",
		0x88,
		-1
	},
	{
		"SwimDeath",
		0x24,
		0x21
	},
	{
		"SwimDeath2",
		0x25,
		-1
	},
	{
		"SwimDeath3",
		0x26,
		-1
	},
	{
		"SwimDeathKnockDown",
		0x27,
		0x22
	},
	{
		"SwimDeathKnockOut",
		0x28,
		0x23
	},
	{
		"SwimHit1",
		0x18,
		-1
	},
	{
		"SwimHit2",
		0x19,
		-1
	},
	{
		"SwimHit3",
		0x1A,
		-1
	},
	{
		"SwimKnockDown",
		0x2A,
		0x25
	},
	{
		"SwimKnockOut",
		0x29,
		0x24
	},
	{
		"SwimRunBack",
		0x30,
		0x2B
	},
	{
		"SwimRunForward",
		0x2F,
		0x2A
	},
	{
		"SwimRunLeft",
		0x31,
		0x2C
	},
	{
		"SwimRunRight",
		0x32,
		0x2D
	},
	{
		"SwimTurnLeft",
		0x33,
		0x2E
	},
	{
		"SwimTurnRight",
		0x34,
		0x2F
	},
	{
		"SwimWalkBack",
		0x2C,
		0x27
	},
	{
		"SwimWalkForward",
		0x2B,
		0x26
	},
	{
		"SwimWalkLeft",
		0x2D,
		0x28
	},
	{
		"SwimWalkRight",
		0x2E,
		0x29
	},
	{
		"Target Release",
		0x104,
		-1
	},
	{
		"Target Start",
		0xFC,
		-1
	},
	{
		"Target Stop",
		0x10C,
		-1
	},
	{
		"ThrowWeapon",
		0x8C,
		0x84
	},
	{
		"Thrust Hit",
		0x19D,
		-1
	},
	{
		"Thrust Large Follow Start",
		0x1C5,
		-1
	},
	{
		"Thrust Large Follow Stop",
		0x1CD,
		-1
	},
	{
		"Thrust Max Attack",
		0x18D,
		-1
	},
	{
		"Thrust Medium Follow Start",
		0x1B5,
		-1
	},
	{
		"Thrust Medium Follow Stop",
		0x1BD,
		-1
	},
	{
		"Thrust Min Attack",
		0x185,
		-1
	},
	{
		"Thrust Min Hit",
		0x195,
		-1
	},
	{
		"Thrust Small Follow Start",
		0x1A5,
		-1
	},
	{
		"Thrust Small Follow Stop",
		0x1AD,
		-1
	},
	{
		"Thrust Start",
		0x17D,
		-1
	},
	{
		"Torch",
		0x12,
		0x12
	},
	{
		"Touch Release",
		0xEC,
		-1
	},
	{
		"Touch Start",
		0xE4,
		-1
	},
	{
		"Touch Stop",
		0xF4,
		-1
	},
	{
		"TurnLeft",
		0x39,
		0x34
	},
	{
		"TurnLeft1h",
		0x57,
		0x52
	},
	{
		"TurnLeft2c",
		0x66,
		0x61
	},
	{
		"TurnLeft2w",
		0x75,
		0x70
	},
	{
		"TurnLefthh",
		0x48,
		0x43
	},
	{
		"TurnRight",
		0x3A,
		0x35
	},
	{
		"TurnRight1h",
		0x58,
		0x53
	},
	{
		"TurnRight2c",
		0x67,
		0x62
	},
	{
		"TurnRight2w",
		0x76,
		0x71
	},
	{
		"TurnRighthh",
		0x49,
		0x44
	},
	{
		"Unequip Detach",
		0xB9,
		-1
	},
	{
		"Unequip Start",
		0xB1,
		-1
	},
	{
		"Unequip Stop",
		0xC1,
		-1
	},
	{
		"WalkBack",
		0x36,
		0x31
	},
	{
		"WalkBack1h",
		0x54,
		0x4F
	},
	{
		"WalkBack2c",
		0x63,
		0x5E
	},
	{
		"WalkBack2w",
		0x72,
		0x6D
	},
	{
		"WalkBackhh",
		0x45,
		0x40
	},
	{
		"WalkForward",
		0x35,
		0x30
	},
	{
		"WalkForward1h",
		0x53,
		0x4E
	},
	{
		"WalkForward2c",
		0x62,
		0x5D
	},
	{
		"WalkForward2w",
		0x71,
		0x6C
	},
	{
		"WalkForwardhh",
		0x44,
		0x3F
	},
	{
		"WalkLeft",
		0x37,
		0x32
	},
	{
		"WalkLeft1h",
		0x55,
		0x50
	},
	{
		"WalkLeft2c",
		0x64,
		0x5F
	},
	{
		"WalkLeft2w",
		0x73,
		0x6E
	},
	{
		"WalkLefthh",
		0x46,
		0x41
	},
	{
		"WalkRight",
		0x38,
		0x33
	},
	{
		"WalkRight1h",
		0x56,
		0x51
	},
	{
		"WalkRight2c",
		0x65,
		0x60
	},
	{
		"WalkRight2w",
		0x74,
		0x6F
	},
	{
		"WalkRighthh",
		0x47,
		0x42
	},
	{
		"WeaponOneHand",
		0x8D,
		0x85
	},
	{
		"WeaponTwoHand",
		0x8E,
		0x86
	},
	{
		"WeaponTwoWide",
		0x8F,
		0x87
	},
	{
		NULL,
		-1,
		-1
	} /* Must be last element */
};


/*===========================================================================
 *
 * Begin Biped Object Type Array
 *
 *=========================================================================*/
const TCHAR *l_BipedParts[] = {
	_T("Head"),
	_T("Hair"),
	_T("Neck"),
	_T("Chest"),
	_T("Groin"),
	_T("Skirt"),
	_T("Right Hand"),
	_T("Left Hand"),
	_T("Right Wrist"),
	_T("Left Wrist"),
	_T("Shield"),
	_T("Right Forearm"),
	_T("Left Forearm"),
	_T("Right Upper Arm"),
	_T("Left Upper Arm"),
	_T("Right Foot"),
	_T("Left Foot"),
	_T("Right Ankle"),
	_T("Left Ankle"),
	_T("Right Knee"),
	_T("Left Knee"),
	_T("Right Upper Leg"),
	_T("Left Upper Leg"),
	_T("Right Pauldron"),
	_T("Left Pauldron"),
	_T("Weapon"),
	_T("Tail")
};


/*===========================================================================
 *
 * Begin Field Conversion Array
 *
 *=========================================================================*/
static valuenames_t l_FieldIDs[] = {
	{
		ESM_FIELD_ID,
		_T("ID")
	},
	{
		ESM_FIELD_COUNT,
		_T("Count")
	},
	{
		ESM_FIELD_NAME,
		_T("Name")
	},
	{
		ESM_FIELD_SCRIPT,
		_T("Script")
	},
	{
		ESM_FIELD_MODEL,
		_T("Model")
	},
	{
		ESM_FIELD_INVENTORY,
		_T("Inventory")
	},
	{
		ESM_FIELD_ICON,
		_T("Icon")
	},
	{
		ESM_FIELD_PERSIST,
		_T("Persist")
	},
	{
		ESM_FIELD_BLOCKED,
		_T("Blocked")
	},
	{
		ESM_FIELD_WEIGHT,
		_T("Weight")
	},
	{
		ESM_FIELD_COST,
		_T("Cost")
	},
	{
		ESM_FIELD_VALUE,
		_T("Value")
	},
	{
		ESM_FIELD_AUTOCALC,
		_T("Autocalc")
	},
	{
		ESM_FIELD_TYPE,
		_T("Type")
	},
	{
		ESM_FIELD_QUALITY,
		_T("Quality")
	},
	{
		ESM_FIELD_CLASS,
		_T("Class")
	},
	{
		ESM_FIELD_HEALTH,
		_T("Health")
	},
	{
		ESM_FIELD_ENCHANT,
		_T("Enchant")
	},
	{
		ESM_FIELD_ENCHANT,
		_T("Enchantment")
	},
	{
		ESM_FIELD_ENCHANTPTS,
		_T("EnchantPts")
	},
	{
		ESM_FIELD_RATING,
		_T("Rating")
	},
	{
		ESM_FIELD_RACE,
		_T("Race")
	},
	{
		ESM_FIELD_PART,
		_T("Part")
	},
	{
		ESM_FIELD_FEMALE,
		_T("Female")
	},
	{
		ESM_FIELD_PLAYABLE,
		_T("Playable")
	},
	{
		ESM_FIELD_CHANGED,
		_T("Changed")
	},
	{
		ESM_FIELD_SCROLL,
		_T("Scroll")
	},
	{
		ESM_FIELD_TEACHES,
		_T("Teaches")
	},
	{
		ESM_FIELD_ORGANIC,
		_T("Organic")
	},
	{
		ESM_FIELD_RESPAWN,
		_T("Respawn")
	},
	{
		ESM_FIELD_ITEMLIST,
		_T("Itemlist")
	},
	{
		ESM_FIELD_SOUND,
		_T("Sound")
	},
	{
		ESM_FIELD_LEVEL,
		_T("Level")
	},
	{
		ESM_FIELD_ESSENTIAL,
		_T("Essential")
	},
	{
		ESM_FIELD_MOVEMENT,
		_T("Movement")
	},
	{
		ESM_FIELD_WEAPSHLD,
		_T("Weapshld")
	},
	{
		ESM_FIELD_WEAPSHIELD,
		_T("WeapShield")
	},
	{
		ESM_FIELD_BIPED,
		_T("Biped")
	},
	{
		ESM_FIELD_BIPEDAL,
		_T("Bipedal")
	},
	{
		ESM_FIELD_CHARGE,
		_T("Charge")
	},
	{
		ESM_FIELD_EFFECT1,
		_T("Effect1")
	},
	{
		ESM_FIELD_EFFECT2,
		_T("Effect2")
	},
	{
		ESM_FIELD_EFFECT3,
		_T("Effect3")
	},
	{
		ESM_FIELD_EFFECT4,
		_T("Effect4")
	},
	{
		ESM_FIELD_ALLPC,
		_T("AllPC")
	},
	{
		ESM_FIELD_LIST,
		_T("List")
	},
	{
		ESM_FIELD_TIME,
		_T("Time")
	},
	{
		ESM_FIELD_RADIUS,
		_T("Radius")
	},
	{
		ESM_FIELD_USES,
		_T("Uses")
	},
	{
		ESM_FIELD_FACTION,
		_T("Faction")
	},
	{
		ESM_FIELD_RANK,
		_T("Rank")
	},
	{
		ESM_FIELD_ANIMATION,
		_T("Animation")
	},
	{
		ESM_FIELD_PCSTART,
		_T("PCStart")
	},
	{
		ESM_FIELD_SPEED,
		_T("Speed")
	},
	{
		ESM_FIELD_REACH,
		_T("Reach")
	},
	{
		ESM_FIELD_CHOPMIN,
		_T("ChopMin")
	},
	{
		ESM_FIELD_CHOPMAX,
		_T("ChopMax")
	},
	{
		ESM_FIELD_THRUSTMIN,
		_T("ThrustMin")
	},
	{
		ESM_FIELD_THRUSTMAX,
		_T("ThrustMax")
	},
	{
		ESM_FIELD_SLASHMIN,
		_T("SlashMin")
	},
	{
		ESM_FIELD_SLASHMAX,
		_T("SlashMax")
	},
	{
		ESM_FIELD_IGNORERESIST,
		_T("IgnoreResist")
	},
	{
		ESM_FIELD_SKILL,
		_T("Skill")
	},
	{
		ESM_FIELD_TEXT,
		_T("Text")
	},
	{
		ESM_FIELD_CHANCENONE,
		_T("ChanceNone")
	},
	{
		ESM_FIELD_CALCEACH,
		_T("CalcEach")
	},
	{
		ESM_FIELD_UNKNOWN,
		_T("Unknown")
	},
	{
		ESM_FIELD_ITEMTYPE,
		_T("ItemType")
	},
	{
		ESM_FIELD_CUSTOM,
		_T("Custom")
	},
	{
		ESM_FIELD_VOLUME,
		_T("Volume")
	},
	{
		ESM_FIELD_MINRANGE,
		_T("MinRange")
	},
	{
		ESM_FIELD_MAXRANGE,
		_T("MaxRange")
	},
	{
		ESM_FIELD_SCHOOL,
		_T("School")
	},
	{
		ESM_FIELD_NPCID,
		_T("NpcID")
	},
	{
		ESM_FIELD_DISPOSITION,
		_T("Disposition")
	},
	{
		ESM_FIELD_NPCFACTION,
		_T("NpcFaction")
	},
	{
		ESM_FIELD_NPCCELL,
		_T("NpcCell")
	},
	{
		ESM_FIELD_INFOFUNC1,
		_T("InfoFunc1")
	},
	{
		ESM_FIELD_INFOFUNC2,
		_T("InfoFunc2")
	},
	{
		ESM_FIELD_INFOFUNC3,
		_T("InfoFunc3")
	},
	{
		ESM_FIELD_INFOFUNC4,
		_T("InfoFunc4")
	},
	{
		ESM_FIELD_INFOFUNC5,
		_T("InfoFunc5")
	},
	{
		ESM_FIELD_INFOFUNC6,
		_T("InfoFunc6")
	},
	{
		ESM_FIELD_ATTRIBUTE,
		_T("Attribute")
	},
	{
		ESM_FIELD_CREATURE,
		_T("Creature")
	},
	{
		ESM_FIELD_REGION,
		_T("Region")
	},
	{
		ESM_FIELD_GRID,
		_T("Grid")
	},
	{
		ESM_FIELD_REFCOUNT,
		_T("RefCount")
	},
	{
		ESM_FIELD_USERDATA,
		_T("UserData")
	},
	{
		ESM_FIELD_TOPIC,
		_T("Topic")
	},
	{
		ESM_FIELD_PREV,
		_T("Prev")
	},
	{
		ESM_FIELD_NEXT,
		_T("Next")
	},
	{
		ESM_FIELD_CELLX,
		_T("CellX")
	},
	{
		ESM_FIELD_CELLY,
		_T("CellY")
	},
	{
		ESM_FIELD_CELL,
		_T("Cell")
	},
	{
		ESM_FIELD_DATA,
		_T("Data")
	},
	{
		ESM_FIELD_DELETE,
		_T("Delete")
	},
	{
		ESM_FIELD_DESC,
		_T("Desc")
	},
	{
		ESM_FIELD_DESC,
		_T("Descript")
	},
	{
		ESM_FIELD_DESC,
		_T("Description")
	},
	{
		ESM_FIELD_EFFECT,
		_T("Effect")
	},
	{
		ESM_FIELD_ITEM,
		_T("Item")
	},   /* Fields added v0.5.6 */
	{
		ESM_FIELD_ITEMEX,
		_T("ItemEx")
	},
	{
		ESM_FIELD_SPELL,
		_T("Spell")
	},
	{
		ESM_FIELD_HEAD,
		_T("Head")
	},
	{
		ESM_FIELD_HAIR,
		_T("Hair")
	},
	{
		ESM_FIELD_BLOOD,
		_T("Blood")
	},
	{
		ESM_FIELD_STRENGTH,
		_T("Strength")
	},
	{
		ESM_FIELD_AGILITY,
		_T("Agility")
	},
	{
		ESM_FIELD_ENDURANCE,
		_T("Endurance")
	},
	{
		ESM_FIELD_WILLPOWER,
		_T("Willpower")
	},
	{
		ESM_FIELD_INTELLIGENCE,
		_T("Intelligence")
	},
	{
		ESM_FIELD_LUCK,
		_T("Luck")
	},
	{
		ESM_FIELD_PERSONALITY,
		_T("Personality")
	},
	{
		ESM_FIELD_STRENGTH,
		_T("Str")
	},
	{
		ESM_FIELD_AGILITY,
		_T("Agi")
	},
	{
		ESM_FIELD_ENDURANCE,
		_T("End")
	},
	{
		ESM_FIELD_WILLPOWER,
		_T("Wil")
	},
	{
		ESM_FIELD_INTELLIGENCE,
		_T("Int")
	},
	{
		ESM_FIELD_LUCK,
		_T("Luc")
	},
	{
		ESM_FIELD_PERSONALITY,
		_T("Per")
	},
	{
		ESM_FIELD_SPEED,
		_T("Spd")
	},
	{
		ESM_FIELD_GOLD,
		_T("Gold")
	},
	{
		ESM_FIELD_FATIGUE,
		_T("SpellPts")
	},
	{
		ESM_FIELD_SPELLPTS,
		_T("Magic")
	},
	{
		-1,
		NULL
	}
};


/*===========================================================================
 *
 * Function - const TCHAR* GetESMSkill (SkillID);
 *
 * Converts the input skill ID to a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *GetESMSkill(const int SkillID) {
	if (SkillID < 0 || SkillID >= MWESM_MAX_SKILLS) {
		return _T("");
	}

	return l_Skills[SkillID].Name;
}

bool GetESMSkill(int &OutSkill, const TCHAR *pString) {
	int Index;

	for (Index = 0; Index < MWESM_MAX_SKILLS; Index++) {
		if (_stricmp(l_Skills[Index].Name, pString) == 0) {
			OutSkill = Index;
			return true;
		}
	}

	return false;
}

int GetESMSkill(const TCHAR *pString) {
	int Index;

	for (Index = 0; Index < MWESM_MAX_SKILLS; Index++) {
		if (_stricmp(l_Skills[Index].Name, pString) == 0) {
			return Index;
		}
	}

	return 0;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMSkillAction (SkillID, Action);
 *
 *=========================================================================*/
const TCHAR *GetESMSkillAction(const int SkillID, const int Action) {
	if (SkillID < 0 || SkillID >= MWESM_MAX_SKILLS) {
		return NULL;
	}

	if (Action == 0) {
		return l_Skills[SkillID].Action1;
	}

	if (Action == 1) {
		return l_Skills[SkillID].Action2;
	}

	if (Action == 2) {
		return l_Skills[SkillID].Action3;
	}

	if (Action == 3) {
		return l_Skills[SkillID].Action4;
	}

	return NULL;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMEffect (EffectID);
 *
 *  Converts the input effect ID to a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *GetESMEffect(const int EffectID) {
	if (EffectID < 0 || EffectID >= MWESM_MAX_EFFECTS) {
		return _T("");
	}

	return l_Effects[EffectID].Name;
}


/*===========================================================================
 *
 * Function - const esmeffectdata_t* GetESMEffectData (EffectID);
 *
 *=========================================================================*/
const esmeffectdata_t *GetESMEffectData(const int EffectID) {
	if (EffectID < 0 || EffectID >= MWESM_MAX_EFFECTS) {
		return NULL;
	}

	return &(l_Effects[EffectID]);
}


/*===========================================================================
 *
 * Function - const int  FindESMEffectID (pEffectID);
 *
 * Returns the Effect index for the given effect ID string, or -1 if the
 * ID string is invalid.
 *
 *=========================================================================*/
int FindESMEffectID(const TCHAR *pEffectID) {
	int Index;

	for (Index = 0; Index < MWESM_MAX_EFFECTS; Index++) {
		if (l_Effects[Index].IsID(pEffectID)) {
			return Index;
		}
	}

	return -1;
}

bool GetESMEffectID(int &EffectID, const TCHAR *pString) {
	int Index;

	for (Index = 0; Index < MWESM_MAX_EFFECTS; Index++) {
		if (_stricmp(l_Effects[Index].ID, pString) == 0) {
			EffectID = Index;
			return true;
		}

		if (_stricmp(l_Effects[Index].Name, pString) == 0) {
			EffectID = Index;
			return true;
		}
	}

	return false;
}

int GetESMEffectID(const TCHAR *pString) {
	int Index;

	for (Index = 0; Index < MWESM_MAX_EFFECTS; Index++) {
		if (_stricmp(l_Effects[Index].ID, pString) == 0) {
			return Index;
		}

		if (_stricmp(l_Effects[Index].Name, pString) == 0) {
			return Index;
		}
	}

	return -1;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMAttribute (AttributeID);
 *
 * Converts the input attribute ID to a string.  Always returns a valid string.
 *
 *=========================================================================*/
const TCHAR *GetESMAttribute(const int AttributeID) {
	if (AttributeID < 0 || AttributeID >= MWESM_MAX_ATTRIBUTES) {
		return _T("");
	}

	return l_Attributes[AttributeID].pName;
}

bool GetESMAttribute(int &OutAttr, const TCHAR *pString) {
	bool Result;
	long Index;
	Result = FindNameValue(Index, l_Attributes, pString);
	OutAttr = Index;
	return Result;
}

int GetESMAttribute(const TCHAR *pString) {
	return FindNameValue(l_Attributes, pString);
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMSpellSchool (SpellSchool);
 *
 *=========================================================================*/
const TCHAR *GetESMSpellSchool(const int SpellSchool) {
	if (SpellSchool < MWESM_SCHOOL_MIN || SpellSchool > MWESM_SCHOOL_MAX) {
		return _T("");
	}

	return l_SpellSchools[SpellSchool];
}


/*===========================================================================
 *
 * Function - const TCHAR* GetESMClassSpec (Spec);
 *
 *=========================================================================*/
const TCHAR *GetESMClassSpec(const int Spec) {
	switch (Spec) {
		case MWESM_CLASSSPEC_COMBAT:
			return _T("Combat");

		case MWESM_CLASSSPEC_MAGIC:
			return _T("Magic");

		case MWESM_CLASSSPEC_STEALTH:
			return _T("Stealth");

		default:
			return _T("Unknown");
	}
}


/*===========================================================================
 *
 * Function - short GetESMAnimGroupID (pGroup);
 *
 * Attempts to find and return the given animation group ID. Returns -1 if
 * the group is not found.
 *
 *=========================================================================*/
short GetESMAnimGroupID(const TCHAR *pGroup) {
	int Index;

	for (Index = 0; l_AnimData[Index].pName != NULL; Index++) {
		if (l_AnimData[Index].IsName(pGroup)) {
			return l_AnimData[Index].ID;
		}
	}

	/* None found */
	return -1;
}

short GetESMAnimGroupOldID(const TCHAR *pGroup) {
	int Index;

	for (Index = 0; l_AnimData[Index].pName != NULL; Index++) {
		if (l_AnimData[Index].IsName(pGroup)) {
			return l_AnimData[Index].OldID;
		}
	}

	/* None found */
	return -1;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetMWBipedPartType (Type);
 *
 *=========================================================================*/
const TCHAR *GetMWBipedPartType(const int Type) {
	if (Type < MWESM_BIPEDPART_MIN || Type > MWESM_BIPEDPART_MAX) {
		return _T("Unknown");
	}

	return l_BipedParts[Type];
}


/*===========================================================================
 *
 * Function - int GetEsmFieldID (pString);
 *
 * Converts a field string to an ID value. Returns a negative value on any
 * error.
 *
 *=========================================================================*/
int GetEsmFieldID(const TCHAR *pString) {
	bool Result;
	long iResult;
	Result = FindNameValue(iResult, l_FieldIDs, pString);

	if (!Result) {
		return -1;
	}

	return iResult;
}


/*===========================================================================
 *
 * Function - const TCHAR* GetEsmFieldName (FieldID);
 *
 * Returns the field name of the given field ID, or an empty string.
 *
 *=========================================================================*/
const TCHAR *GetEsmFieldName(const int FieldID) {
	return FindValueName(l_FieldIDs, FieldID);
}


/*===========================================================================
 *
 * Function - bool IsESMAttributeEffect (EffectID);
 *
 *=========================================================================*/
bool IsESMAttributeEffect(const int EffectID) {
	switch (EffectID) {
		case MWESM_EFFECT_DRAINATTR:
		case MWESM_EFFECT_ABSORBATTR:
		case MWESM_EFFECT_FORTATTR:
		case MWESM_EFFECT_RESTOREATTR:
		case MWESM_EFFECT_DAMAGEATTR:
			return true;

		default:
			return false;
	}
}


/*===========================================================================
 *
 * Function - bool IsESMSkillEffect (EffectID);
 *
 *=========================================================================*/
bool IsESMSkillEffect(const int EffectID) {
	switch (EffectID) {
		case MWESM_EFFECT_DRAINSKILL:
		case MWESM_EFFECT_ABSORBSKILL:
		case MWESM_EFFECT_FORTSKILL:
		case MWESM_EFFECT_RESTORESKILL:
		case MWESM_EFFECT_DAMAGESKILL:
			return true;

		default:
			return false;
	}
}


/*===========================================================================
 *
 * Function - bool IsESMRecordCarryable (pType);
 *
 * Returns true if the given record type represents an object that can be
 * carried (Armor, weapons, etc...).
 *
 *=========================================================================*/
bool IsESMRecordCarryable(const TCHAR *pType) {
	static long s_ValidTypes[] = {
		*(long *)MWESM_REC_ALCH,
		*(long *)MWESM_REC_APPA,
		*(long *)MWESM_REC_ARMO,
		*(long *)MWESM_REC_BOOK,
		*(long *)MWESM_REC_CLOT,
		*(long *)MWESM_REC_INGR,
		*(long *)MWESM_REC_LEVI,
		*(long *)MWESM_REC_LIGH,
		*(long *)MWESM_REC_LOCK,
		*(long *)MWESM_REC_MISC,
		*(long *)MWESM_REC_REPA,
		*(long *)MWESM_REC_PROB,
		*(long *)MWESM_REC_WEAP,
		0
	};
	int Index;
	long TypeLong = *(long *)pType;

	for (Index = 0; s_ValidTypes[Index] != 0; Index++) {
		if (TypeLong == s_ValidTypes[Index]) {
			return true;
		}
	}

	/* Matching object not found */
	return false;
}


/*===========================================================================
 *
 * Function - bool IsESMRecordModel (const TCHAR* pType);
 *
 * Returns true if the given record is a type that has a model and can be
 * placed in the world.
 *
 *=========================================================================*/
bool IsESMRecordModel(const TCHAR *pType) {
	static long s_ValidTypes[] = {
		*(long *)MWESM_REC_STAT,
		*(long *)MWESM_REC_ACTI,
		*(long *)MWESM_REC_DOOR,
		*(long *)MWESM_REC_CREA,
		*(long *)MWESM_REC_LEVC,
		*(long *)MWESM_REC_LEVI,
		*(long *)MWESM_REC_NPC_,
		*(long *)MWESM_REC_CONT,
		0
	};
	int Index;
	long TypeLong = *(long *)pType;

	/* All carryable records are included */
	if (IsESMRecordCarryable(pType)) {
		return true;
	}

	for (Index = 0; s_ValidTypes[Index] != 0; Index++) {
		if (TypeLong == s_ValidTypes[Index]) {
			return true;
		}
	}

	return false;
}


/*===========================================================================
 *
 * Function - TCHAR* RemoveIDQuotes (pBuffer, pID);
 *
 * Removes any quotes from the input ID and copies it into the given buffer
 * which is returned. Ensure that the input buffer is large enough to hold
 * the ID string (MWESM_ID_MAXSIZE * 2 ).
 *
 *=========================================================================*/
TCHAR *RemoveIDQuotes(TCHAR *pBuffer, const TCHAR *pID) {
	if (*pID == '"') {
		int Length;
		strnncpy(pBuffer, pID + 1, MWESM_ID_MAXSIZE * 2);
		Length = TSTRLEN(pBuffer);

		if (Length > 0) {
			pBuffer[Length - 1] = NULL_CHAR;
		}

		return pBuffer;
	}

	return (TCHAR *)pID;
}
