#pragma once

#include <algorithm>

#include <GeneralStructures.h>

#include <New/Type/AttachmentTypeClass.h>
#include <Ext/TechnoType/Body.h>

class AttachmentClass
{
public:
	static std::vector<AttachmentClass*> Array;

	TechnoTypeExt::ExtData::AttachmentDataEntry* Data;
	TechnoClass* Parent;
	TechnoClass* Child;

	AttachmentClass(TechnoTypeExt::ExtData::AttachmentDataEntry* data,
		TechnoClass* pParent, TechnoClass* pChild = nullptr) :
		Data(data),
		Parent(pParent),
		Child(pChild)
	{
		Array.push_back(this);
	}

	AttachmentClass() :
		Data(),
		Parent(),
		Child()
	{
		Array.push_back(this);
	}

	~AttachmentClass()
	{
		auto position = std::find(Array.begin(), Array.end(), this);
		if (position != Array.end())
			Array.erase(position);
	}

	AttachmentTypeClass* GetType();
	TechnoTypeClass* GetChildType();

	void Initialize();
	void CreateChild();
	void AI();
	void Uninitialize();
	void ChildDestroyed();

	void Unlimbo();
	void Limbo();

	bool AttachChild(TechnoClass* pChild);
	bool DetachChild(bool force = false);

	bool Load(PhobosStreamReader& stm, bool registerForChange);
	bool Save(PhobosStreamWriter& stm) const;

private:
	template <typename T>
	bool Serialize(T& stm);
};