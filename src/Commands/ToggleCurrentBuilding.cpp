#include "ToggleCurrentBuilding.h"

#include <Utilities/GeneralUtils.h>
#include <Ext/BuildingType/Body.h>

const char* ToggleCurrentBuildingCommandClass::GetName() const
{
	return "ToggleCurrentBuilding";
}

const wchar_t* ToggleCurrentBuildingCommandClass::GetUIName() const
{
	return GeneralUtils::LoadStringUnlessMissing("TXT_ToggleCurrentBuilding", L"Toggle Current Building");
}

const wchar_t* ToggleCurrentBuildingCommandClass::GetUICategory() const
{
	return CATEGORY_DEVELOPMENT;
}

const wchar_t* ToggleCurrentBuildingCommandClass::GetUIDescription() const
{
	return GeneralUtils::LoadStringUnlessMissing("TXT_ToggleCurrentBuilding_DESC", L"Toggle Current Building.");
}

void ToggleCurrentBuildingCommandClass::Execute(WWKey eInput) const
{
	auto pBuilding = specific_cast<BuildingClass*>(DisplayClass::Instance->CurrentBuilding);
	auto pType = pBuilding ? pBuilding->Type : nullptr;
	auto pTypeExt = pType ? BuildingTypeExt::ExtMap.Find(pType) : nullptr;
	if (pTypeExt && pTypeExt->ToggleBuildingType.isset())
	{
		auto pTypeNew = pTypeExt->ToggleBuildingType.Get();
		if (auto const pBuildingNew = static_cast<BuildingClass*>(pTypeNew->CreateObject(HouseClass::CurrentPlayer)))
		{
			//pBuilding->ClearSidebarTabObject(); // 无效

			//Debug::LogAndMessage("TypeIndexPre: %d", HouseClass::CurrentPlayer->ProducingBuildingTypeIndex); // -1

			DisplayClass::Instance->CurrentBuildingType = pTypeNew;
			DisplayClass::Instance->CurrentBuilding = pBuildingNew;

			//DisplayClass::Instance->unknown_1194 = pTypeNew; // FE
			//DisplayClass::Instance->unknown_1190 = pBuildingNew; // FE

			//DisplayClass::Instance->unknown_11AC = DisplayClass::Instance->unknown_1198; // 无效

			auto nCell = pTypeNew->GetFoundationData(1);
			DisplayClass::Instance->SetActiveFoundation(*nCell);

			//pBuildingNew->ClearSidebarTabObject(); // 无效
			//MapClass::Instance->MarkNeedsRedraw(1); // 无效

			//Debug::LogAndMessage("TypeIndexNow: %d", HouseClass::CurrentPlayer->ProducingBuildingTypeIndex); // -1
		}
	}
}
