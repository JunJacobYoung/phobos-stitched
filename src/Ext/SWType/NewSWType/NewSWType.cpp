#include "NewSWType.h"
#include "MultipleSWFirer.h"

std::vector<std::unique_ptr<NewSWType>> NewSWType::Array;

void NewSWType::Register(std::unique_ptr<NewSWType> pType)
{
	//Ares capture positive, so we use negative...
	pType->SetTypeIndex(-static_cast<int>(Array.size() + 2));
	Array.emplace_back(std::move(pType));
}

void NewSWType::Init()
{
	if (!Array.empty())
		return;

	Register(std::make_unique<MultipleSWFirer>());
}

void NewSWType::Clear()
{
	Array.clear();
}

int NewSWType::GetNewSWTypeIdx(const char* TypeID)
{
	for (const auto& it : Array)
	{
		if (!_strcmpi(it->GetTypeID(), TypeID))
			return it->GetTypeIndex();
	}

	return -1;
}

NewSWType* NewSWType::GetNthItem(int idx)
{
	return Array[-idx - 2].get();
}

int NewSWType::GetTypeIndex()
{
	return this->TypeIndex;
}

void NewSWType::SetTypeIndex(int idx)
{
	this->TypeIndex = idx;
}

template <typename T>
bool NewSWType::Serialize(T& stm)
{
	stm
		.Process(this->TypeIndex)
		;
	return stm.Success();
}

bool NewSWType::Save(PhobosStreamWriter& stm)
{
	return Serialize(stm);
}

bool NewSWType::Load(PhobosStreamReader& stm)
{
	return Serialize(stm);
}

bool NewSWType::LoadGlobals(PhobosStreamReader& stm)
{
	Init();
	return stm.Success();
}

bool NewSWType::SaveGlobals(PhobosStreamWriter& stm)
{
	return stm.Success();
}
