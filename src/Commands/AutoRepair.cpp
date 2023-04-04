#include "AutoRepair.h"

#include <Utilities/GeneralUtils.h>

const char* AutoRepairCommandClass::GetName() const
{
	return "AutoRepair";
}

const wchar_t* AutoRepairCommandClass::GetUIName() const
{
	return GeneralUtils::LoadStringUnlessMissing("TXT_AutoRepair", L"Auto Repair");
}

const wchar_t* AutoRepairCommandClass::GetUICategory() const
{
	return CATEGORY_DEVELOPMENT;
}

const wchar_t* AutoRepairCommandClass::GetUIDescription() const
{
	return GeneralUtils::LoadStringUnlessMissing("TXT_AutoRepair_DESC", L"Toggle between repairing buildings automatically or not.");
}

void AutoRepairCommandClass::Execute(WWKey eInput) const
{
    RulesClass::Instance->RepairSell = RulesClass::Instance->RepairSell > 0 ? 0 : 1;
}
