#include "Body.h"

#include <ScenarioClass.h>
#include <WarheadTypeClass.h>

#include <Ext/Anim/Body.h>
#include <Ext/WarheadType/Body.h>
#include <Ext/WeaponType/Body.h>

DEFINE_HOOK(0x422CAB, AnimClass_DrawIt_XDrawOffset, 0x5)
{
	GET(AnimClass* const, pThis, ECX);
	GET_STACK(Point2D*, pCoord, STACK_OFFS(0x100, -0x4));

	if (auto const pThisTypeExt = AnimTypeExt::ExtMap.Find(pThis->Type))
		pCoord->X += pThisTypeExt->XDrawOffset;

	return 0;
}

DEFINE_HOOK(0x423B95, AnimClass_AI_HideIfNoOre_Threshold, 0x8)
{
	GET(AnimClass* const, pThis, ESI);
	GET(AnimTypeClass* const, pType, EDX);

	if (pType->HideIfNoOre)
	{
		auto nThreshold = abs(AnimTypeExt::ExtMap.Find(pType)->HideIfNoOre_Threshold.Get());
		auto pCell = pThis->GetCell();

		pThis->Invisible = !pCell || pCell->GetContainedTiberiumValue() <= nThreshold;
	}

	return 0x423BBF;
}

DEFINE_HOOK(0x424CB0, AnimClass_In_Which_Layer_AttachedObjectLayer, 0x6)
{
	enum { ReturnValue = 0x424CBF };

	GET(AnimClass*, pThis, ECX);

	auto pExt = AnimTypeExt::ExtMap.Find(pThis->Type);

	if (pThis->OwnerObject && pExt->Layer_UseObjectLayer.isset())
	{
		Layer layer = pThis->Type->Layer;

		if (pExt->Layer_UseObjectLayer.Get())
			layer = pThis->OwnerObject->InWhichLayer();

		R->EAX(layer);

		return ReturnValue;
	}

	return 0;
}

DEFINE_HOOK(0x424C49, AnimClass_AttachTo_BuildingCoords, 0x5)
{
	GET(AnimClass*, pThis, ESI);
	GET(ObjectClass*, pObject, EDI);
	GET(CoordStruct*, pCoords, EAX);

	auto pExt = AnimTypeExt::ExtMap.Find(pThis->Type);

	if (pExt->UseCenterCoordsIfAttached)
	{
		pCoords = pObject->GetCenterCoord(pCoords);
		pCoords->X += 128;
		pCoords->Y += 128;
	}

	return 0;
}

DEFINE_HOOK(0x423CC1, AnimClass_AI_HasExtras_Expired, 0x6)
{
	enum { SkipGameCode = 0x423EFD };

	GET(AnimClass* const, pThis, ESI);
	GET(bool const, heightFlag, EAX);

	if (!pThis || !pThis->Type)
		return SkipGameCode;

	CoordStruct nLocation;
	pThis->GetCenterCoord(&nLocation);
	auto const pOwner = AnimExt::GetOwnerHouse(pThis);
	auto const pAnimTypeExt = AnimTypeExt::ExtMap.Find(pThis->Type);
	AnimTypeClass* pSplashAnim = nullptr;

	if (pThis->GetCell()->LandType != LandType::Water || heightFlag || pAnimTypeExt->ExplodeOnWater)
	{
		if (auto const pWarhead = pThis->Type->Warhead)
		{
			auto const nDamage = Game::F2I(pThis->Type->Damage);
			TechnoClass* pOwnerTechno = abstract_cast<TechnoClass*>(pThis->OwnerObject);

			if (pAnimTypeExt->Warhead_Detonate)
			{
				WarheadTypeExt::DetonateAt(pWarhead, nLocation, pOwnerTechno, nDamage);
			}
			else
			{
				MapClass::DamageArea(nLocation, nDamage, pOwnerTechno, pWarhead, pWarhead->Tiberium, pOwner);
				MapClass::FlashbangWarheadAt(nDamage, pWarhead, nLocation);
			}
		}

		if (auto const pExpireAnim = pThis->Type->ExpireAnim)
		{
			if (auto pAnim = GameCreate<AnimClass>(pExpireAnim, nLocation, 0, 1, 0x2600u, 0, 0))
				AnimExt::SetAnimOwnerHouseKind(pAnim, pOwner, nullptr, false);
		}
	}
	else
	{
		TypeList<AnimTypeClass*> defaultSplashAnims;

		if (!pThis->Type->IsMeteor)
		{
			defaultSplashAnims = TypeList<AnimTypeClass*>();
			defaultSplashAnims.AddItem(RulesClass::Instance->Wake);
		}
		else
		{
			defaultSplashAnims = RulesClass::Instance->SplashList;
		}

		auto const splash = pAnimTypeExt->SplashAnims.GetElements(defaultSplashAnims);

		if (splash.size() > 0)
		{
			auto nIndexR = (splash.size() - 1);
			auto nIndex = pAnimTypeExt->SplashAnims_PickRandom ?
				ScenarioClass::Instance->Random.RandomRanged(0, nIndexR) : nIndexR;

			pSplashAnim = splash.at(nIndex);
		}
	}

	if (pSplashAnim)
	{
		if (auto const pSplashAnimCreated = GameCreate<AnimClass>(pSplashAnim, nLocation, 0, 1, 0x600u, false))
			AnimExt::SetAnimOwnerHouseKind(pSplashAnimCreated, pOwner, nullptr, false);
	}

	return SkipGameCode;
}

// Goes before and replaces Ares animation damage / weapon hook at 0x424538.
DEFINE_HOOK(0x424513, AnimClass_AI_Damage, 0x6)
{
	enum { SkipDamage = 0x42465D, Continue = 0x42464C };

	GET(AnimClass*, pThis, ESI);

	if (pThis->Type->Damage <= 0.0 || pThis->HasExtras)
		return SkipDamage;

	auto const pTypeExt = AnimTypeExt::ExtMap.Find(pThis->Type);
	int delay = pTypeExt->Damage_Delay.Get();

	int damageMultiplier = 1;

	if (pThis->OwnerObject && pThis->OwnerObject->WhatAmI() == AbstractType::Terrain)
		damageMultiplier = 5;

	bool adjustAccum = false;
	double damage = 0;
	int appliedDamage = 0;

	if (pTypeExt->Damage_ApplyOnce) // If damage is to be applied only once per animation loop
	{
		if (pThis->Animation.Value == std::max(delay - 1, 1))
			appliedDamage = static_cast<int>(std::round(pThis->Type->Damage)) * damageMultiplier;
		else
			return SkipDamage;
	}
	else if (delay <= 0 || pThis->Type->Damage < 1.0) // If Damage.Delay is less than 1 or Damage is a fraction.
	{
		adjustAccum = true;
		damage = damageMultiplier * pThis->Type->Damage + pThis->Accum;
		pThis->Accum = damage;

		// Deal damage if it is at least 1, otherwise accumulate it for later.
		if (damage >= 1.0)
			appliedDamage = static_cast<int>(std::round(damage));
		else
			return SkipDamage;
	}
	else
	{
		// Accum here is used as a counter for Damage.Delay, which cannot deal fractional damage.
		damage = pThis->Accum + 1.0;
		pThis->Accum = damage;

		if (damage < delay)
			return SkipDamage;

		// Use Type->Damage as the actually dealt damage.
		appliedDamage = static_cast<int>(std::round(pThis->Type->Damage)) * damageMultiplier;
	}

	if (appliedDamage <= 0 || pThis->IsPlaying)
		return SkipDamage;

	// Store fractional damage if needed, or reset the accum if hit the Damage.Delay counter.
	if (adjustAccum)
		pThis->Accum = damage - appliedDamage;
	else
		pThis->Accum = 0.0;

	auto const pExt = AnimExt::ExtMap.Find(pThis);
	TechnoClass* pInvoker = nullptr;

	if (pTypeExt->Damage_DealtByInvoker)
		pInvoker = pExt->Invoker ? pExt->Invoker : pThis->OwnerObject ? abstract_cast<TechnoClass*>(pThis->OwnerObject) : nullptr;

	if (pTypeExt->Weapon.isset())
	{
		WeaponTypeExt::DetonateAt(pTypeExt->Weapon.Get(), pThis->GetCoords(), pInvoker, appliedDamage);
	}
	else
	{
		auto pWarhead = pThis->Type->Warhead ? pThis->Type->Warhead :
			strcmp(pThis->Type->get_ID(), "INVISO") ? RulesClass::Instance->FlameDamage2 : RulesClass::Instance->C4Warhead;

		auto pOwner = pInvoker ? pInvoker->Owner : pThis->Owner ? pThis->Owner :
			pThis->OwnerObject ? pThis->OwnerObject->GetOwningHouse() : nullptr;

		MapClass::DamageArea(pThis->GetCoords(), appliedDamage, pInvoker, pWarhead, true, pOwner);
	}

	return Continue;
}

DEFINE_HOOK(0x424322, AnimClass_AI_TrailerInheritOwner, 0x6)
{
	GET(AnimClass*, pThis, ESI);
	GET(AnimClass*, pTrailerAnim, EAX);

	if (auto const pExt = AnimExt::ExtMap.Find(pThis))
	{
		if (auto const pTrailerAnimExt = AnimExt::ExtMap.Find(pTrailerAnim))
		{
			pTrailerAnim->Owner = pThis->Owner;
			pTrailerAnimExt->Invoker = pExt->Invoker;
		}
	}

	return 0;
}