#pragma once

#include <Utilities/Template.h>
#include <Utilities/Enumerable.h>
#include <Utilities/Enum.h>

class AttachEffectTypeClass : public Enumerable<AttachEffectTypeClass>
{
public:

	Valueable<int> FirePower;
	Valueable<int> ROF;
	Valueable<int> Armor;
	Valueable<int> Speed;
	Valueable<int> ROT;
	Valueable<double> FirePower_Multiplier;
	Valueable<double> ROF_Multiplier;
	Valueable<double> Armor_Multiplier;
	Valueable<double> Speed_Multiplier;
	Valueable<double> ROT_Multiplier;
	Valueable<bool> Cloak;
	Valueable<bool> Decloak;
	Valueable<bool> DisableWeapon;
	Nullable<int> AllowMinHealth;
	Valueable<DisableWeaponCate> DisableWeapon_Category;
	ValueableVector<AnimTypeClass*> Anim;
	ValueableVector<AnimTypeClass*> EndedAnim;
	Valueable<bool> Anim_RandomPick;
	Valueable<bool> EndedAnim_RandomPick;
	ValueableVector<WeaponTypeClass*> WeaponList;
	ValueableVector<WeaponTypeClass*> AttackedWeaponList;
	Valueable<bool> RandomDuration;
	Valueable<Vector2D<int>> RandomDuration_Interval;
	Valueable<int> Duration;
	Valueable<int> Delay;
	Valueable<int> Loop_Delay;
	Nullable<int> Loop_Duration;
	Valueable<bool> ImmuneMindControl;
	Valueable<bool> ReplaceWeapon;
	Promotable<WeaponTypeClass*> ReplacePrimary;
	Promotable<WeaponTypeClass*> ReplaceSecondary;
	PromotableVector<WeaponTypeClass*> ReplaceGattlingWeapon;
	Nullable<ArmorType> ReplaceArmor;
	Nullable<ArmorType> ReplaceArmor_Shield;
	Nullable<WeaponTypeClass*> ReplaceDeathWeapon;
	Valueable<bool> ForceExplode;
	Valueable<AnimTypeClass*> InfDeathAnim;
	Nullable<int> Coexist_Maximum;
	Valueable<bool> WeaponList_FireOnAttach;
	Valueable<bool> PenetratesIronCurtain;
	Valueable<bool> DiscardOnEntry;
	Valueable<bool> Cumulative;
	Valueable<bool> IfExist_IgnoreOwner;
	Valueable<int> IfExist_AddTimer;
	Valueable<int> IfExist_AddTimer_Cap;
	Valueable<bool> IfExist_ResetTimer;
	Valueable<bool> IfExist_ResetAnim;
	Valueable<bool> ShowAnim_Cloaked;
	Valueable<bool> HideImage;

	int ArrayIndex;

	AttachEffectTypeClass(const char* pTitle = NONE_STR) : Enumerable<AttachEffectTypeClass>(pTitle)
		, FirePower(0)
		, ROF(0)
		, Armor(0)
		, Speed(0)
		, ROT(0)
		, FirePower_Multiplier(1.0)
		, ROF_Multiplier(1.0)
		, Armor_Multiplier(1.0)
		, Speed_Multiplier(1.0)
		, ROT_Multiplier(1.0)
		, DisableWeapon(false)
		, DisableWeapon_Category(DisableWeaponCate::CantFire)
		, Cloak(false)
		, Decloak(false)
		, AllowMinHealth()
		, Anim()
		, EndedAnim()
		, Anim_RandomPick(false)
		, WeaponList()
		, WeaponList_FireOnAttach(false)
		, AttackedWeaponList()
		, Duration(0)
		, RandomDuration(false)
		, RandomDuration_Interval(Vector2D<int>::Empty)
		, Delay(0)
		, ImmuneMindControl(false)
		, ReplaceArmor()
		, ReplaceArmor_Shield()
		, ReplaceWeapon()
		, ReplacePrimary(nullptr)
		, ReplaceSecondary(nullptr)
		, ReplaceGattlingWeapon()
		, ReplaceDeathWeapon()
		, ForceExplode(false)
		, InfDeathAnim()
		, PenetratesIronCurtain(false)
		, DiscardOnEntry(false)
		, Cumulative(false)
		, IfExist_IgnoreOwner(false)
		, IfExist_AddTimer(0)
		, IfExist_AddTimer_Cap(-1)
		, IfExist_ResetTimer(true)
		, IfExist_ResetAnim(false)
		, Loop_Delay(0)
		, Loop_Duration()
		, ShowAnim_Cloaked(false)
		, HideImage(false)
		, Coexist_Maximum()
		, ArrayIndex(Array.size())
	{ }

	virtual ~AttachEffectTypeClass() = default;

	virtual void LoadFromINI(CCINIClass* pINI);
	virtual void LoadFromStream(PhobosStreamReader& stm);
	virtual void SaveToStream(PhobosStreamWriter& stm);
	
private:

	template <typename T>
	void Serialize(T& stm);
};
