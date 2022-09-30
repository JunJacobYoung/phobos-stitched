#include "AttachmentClass.h"

#include <BulletClass.h>
#include <BulletTypeClass.h>
#include <WarheadTypeClass.h>
#include <DriveLocomotionClass.h>

#include <ObjBase.h>

#include <Ext/Techno/Body.h>

std::vector<AttachmentClass*> AttachmentClass::Array;

AttachmentTypeClass* AttachmentClass::GetType()
{
	return Data->Type;
}

TechnoTypeClass* AttachmentClass::GetChildType()
{
	return Data->TechnoType;
}

CoordStruct AttachmentClass::GetChildLocation()
{
	return TechnoExt::GetFLHAbsoluteCoords(this->Parent, this->Data->FLH, this->Data->IsOnTurret);
}

void AttachmentClass::Initialize()
{
	if (this->Child)
		return;

	if (this->GetType()->RestoreAtCreation)
		this->CreateChild();
}

void AttachmentClass::CreateChild()
{
	if (auto const pChildType = this->GetChildType())
	{
		this->Child = abstract_cast<TechnoClass*>(pChildType->CreateObject(this->Parent->Owner));

		if (this->Child != nullptr)
		{
			auto const pChildExt = TechnoExt::ExtMap.Find(this->Child);
			pChildExt->ParentAttachment = this;

			FootClass* pFoot = abstract_cast<FootClass*>(this->Child);

			if (pFoot != nullptr)
				pFoot->Locomotor->Lock();
		}
		else
		{
			Debug::Log("[" __FUNCTION__ "] Failed to create child %s of parent %s!\n",
				pChildType->ID, this->Parent->GetTechnoType()->ID);
		}
	}
}

void AttachmentClass::AI()
{
	AttachmentTypeClass* pType = this->GetType();

	if (this->Child)
	{
		this->Child->SetLocation(this->GetChildLocation());

		this->Child->OnBridge = this->Parent->OnBridge;

		DirStruct childDir = this->Data->IsOnTurret
			? this->Parent->SecondaryFacing.Current() : this->Parent->PrimaryFacing.Current();

		this->Child->PrimaryFacing.Set_Current(childDir);

		if (pType->InheritTilt)
		{
			this->Child->AngleRotatedForwards = this->Parent->AngleRotatedForwards;
			this->Child->AngleRotatedSideways = this->Parent->AngleRotatedSideways;

			// DriveLocomotionClass doesn't tilt only with angles set, hence why we
			// do this monstrosity in order to inherit timer and ramp data - Kerbiter
			FootClass* pParentAsFoot = abstract_cast<FootClass*>(this->Parent);
			FootClass* pChildAsFoot = abstract_cast<FootClass*>(this->Child);
			if (pParentAsFoot && pChildAsFoot)
			{
				auto pParentLoco = static_cast<LocomotionClass*>(pParentAsFoot->Locomotor.get());
				auto pChildLoco = static_cast<LocomotionClass*>(pChildAsFoot->Locomotor.get());

				CLSID locoCLSID;
				if (SUCCEEDED(pParentLoco->GetClassID(&locoCLSID))
					&& (locoCLSID == LocomotionClass::CLSIDs::Drive
						|| locoCLSID == LocomotionClass::CLSIDs::Ship) &&
					SUCCEEDED(pChildLoco->GetClassID(&locoCLSID))
					&& (locoCLSID == LocomotionClass::CLSIDs::Drive
						|| locoCLSID == LocomotionClass::CLSIDs::Ship))
				{
					// shh DriveLocomotionClass almost equates to ShipLocomotionClass
					// for this particular case it's OK to cast to it - Kerbiter
					auto pParentDriveLoco = static_cast<DriveLocomotionClass*>(pParentLoco);
					auto pChildDriveLoco = static_cast<DriveLocomotionClass*>(pChildLoco);

					pChildDriveLoco->SlopeTimer = pParentDriveLoco->SlopeTimer;
					pChildDriveLoco->PreviousRamp = pParentDriveLoco->PreviousRamp;
					pChildDriveLoco->CurrentRamp = pParentDriveLoco->CurrentRamp;
				}
			}
		}

		if (pType->InheritStateEffects)
		{
			this->Child->CloakState = this->Parent->CloakState;
			this->Child->BeingWarpedOut = this->Parent->BeingWarpedOut;
			this->Child->Deactivated = this->Parent->Deactivated;
			this->Child->Flash(this->Parent->Flashing.DurationRemaining);

			this->Child->IronCurtainTimer = this->Parent->IronCurtainTimer;
			this->Child->IdleActionTimer = this->Parent->IdleActionTimer;
			this->Child->IronTintTimer = this->Parent->IronTintTimer;
			this->Child->CloakDelayTimer = this->Parent->CloakDelayTimer;
			this->Child->ChronoLockRemaining = this->Parent->ChronoLockRemaining;
			this->Child->Berzerk = this->Parent->Berzerk;
			this->Child->ChronoWarpedByHouse = this->Parent->ChronoWarpedByHouse;
			this->Child->EMPLockRemaining = this->Parent->EMPLockRemaining;
			this->Child->ShouldLoseTargetNow = this->Parent->ShouldLoseTargetNow;
		}

		if (pType->InheritOwner)
			this->Child->SetOwningHouse(this->Parent->GetOwningHouse(), false);
	}
}

// Doesn't call destructor (to be managed by smart pointers)
void AttachmentClass::Uninitialize()
{
	if (this->Child)
	{
		auto pType = this->GetType();
		if (pType->DestructionWeapon_Child != nullptr)
			TechnoExt::FireWeaponAtSelf(this->Child, pType->DestructionWeapon_Child);

		if (!this->Child->InLimbo && pType->ParentDestructionMission.isset())
			this->Child->QueueMission(pType->ParentDestructionMission.Get(), false);
	}
}

void AttachmentClass::ChildDestroyed()
{
	AttachmentTypeClass* pType = this->GetType();
	if (pType->DestructionWeapon_Parent != nullptr)
		TechnoExt::FireWeaponAtSelf(this->Parent, pType->DestructionWeapon_Parent);

	//this->Child = nullptr;
}

void AttachmentClass::Unlimbo()
{
	if (this->Child)
	{
		CoordStruct childCoord = TechnoExt::GetFLHAbsoluteCoords(
			this->Parent, this->Data->FLH, this->Data->IsOnTurret);

		unsigned int childDir = this->Data->IsOnTurret
			? this->Parent->SecondaryFacing.Current().GetValue<16>() : this->Parent->PrimaryFacing.Current().GetValue<16>();

		++Unsorted::IKnowWhatImDoing;
		this->Child->Unlimbo(childCoord, static_cast<DirType>(childDir));
		--Unsorted::IKnowWhatImDoing;
	}
}

void AttachmentClass::Limbo()
{
	if (this->Child)
		this->Child->Limbo();
}

bool AttachmentClass::AttachChild(TechnoClass* pChild)
{
	if (this->Child)
		return false;

	this->Child = pChild;

	auto pChildExt = TechnoExt::ExtMap.Find(this->Child);
	pChildExt->ParentAttachment = this;
	FootClass* pFoot = abstract_cast<FootClass*>(pChild);

	if (pFoot != nullptr)
		pFoot->Locomotor->Lock();

	AttachmentTypeClass* pType = this->GetType();

	if (pType->InheritOwner)
	{
		if (auto pController = this->Child->MindControlledBy)
			pController->CaptureManager->Free(this->Child);
	}

	return true;
}

bool AttachmentClass::DetachChild(bool isForceDetachment)
{
	if (this->Child)
	{
		AttachmentTypeClass* pType = this->GetType();

		if (isForceDetachment)
		{
			if (pType->ForceDetachWeapon_Parent.isset())
				TechnoExt::FireWeaponAtSelf(this->Parent, pType->DestructionWeapon_Parent);

			if (pType->ForceDetachWeapon_Child.isset())
				TechnoExt::FireWeaponAtSelf(this->Child, pType->DestructionWeapon_Child);
		}

		if (!this->Child->InLimbo && pType->ParentDetachmentMission.isset())
			this->Child->QueueMission(pType->ParentDetachmentMission.Get(), false);

		if (pType->InheritOwner)
			this->Child->SetOwningHouse(this->Parent->GetOriginalOwner(), false);

		auto pChildExt = TechnoExt::ExtMap.Find(this->Child);
		pChildExt->ParentAttachment = nullptr;
		FootClass* pFoot = abstract_cast<FootClass*>(this->Child);

		if (pFoot != nullptr)
			pFoot->Locomotor->Unlock();

		this->Child = nullptr;

		return true;
	}

	return false;
}

#pragma region Save/Load

template <typename T>
bool AttachmentClass::Serialize(T& stm)
{
	return stm
		.Process(this->Data)
		.Process(this->Parent)
		.Process(this->Child)
		.Success();
};

bool AttachmentClass::Load(PhobosStreamReader& stm, bool RegisterForChange)
{
	return Serialize(stm);
}

bool AttachmentClass::Save(PhobosStreamWriter& stm) const
{
	return const_cast<AttachmentClass*>(this)->Serialize(stm);
}

bool AttachmentClass::LoadGlobals(PhobosStreamReader& stm)
{
	stm.Process(Array);
	return stm.Success();
}

bool AttachmentClass::SaveGlobals(PhobosStreamWriter& stm)
{
	stm.Process(Array);
	return stm.Success();
}

#pragma endregion 
