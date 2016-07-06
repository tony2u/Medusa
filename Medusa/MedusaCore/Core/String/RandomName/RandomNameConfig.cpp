// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "RandomNameConfig.h"
//SIREN_BODY_INCLUDE_END
#include "Core/IO/FileSystem.h"
#include "Core/Math/Random/Random.h"
#include "Core/Siren/Siren.h"
#include "Core/IO/FileIdRef.h"


MEDUSA_BEGIN;

RandomNameConfig::RandomNameConfig()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

RandomNameConfig::~RandomNameConfig()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
	Unload();
}


bool RandomNameConfig::Initialize(const FileIdRef& fileId, uint format /*= 0*/)
{
	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	return LoadFromData(fileId, data, format);
}

bool RandomNameConfig::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format/*=0*/)
{
	Unload();
	RETURN_FALSE_IF_FALSE(Siren::DeserializeBinaryTo(data, *this));

	for(const auto& item: mItems)
	{
		List<const RandomNameConfigItem*>* itemList = mItemDict.GetOptional(item.Position(), nullptr);
		if (itemList == nullptr)
		{
			itemList = new List<const RandomNameConfigItem*>();
			mItemDict.Add(item.Position(), itemList);
		}

		itemList->Add(&item);
	}


	return true;
}

void RandomNameConfig::Unload()
{
	mItems.Clear();
	mItemDict.Clear();
}

HeapString RandomNameConfig::GetRandomName3(uint seed/*=0*/) const
{
	Random random(seed);
	List<const RandomNameConfigItem*>* items0 = mItemDict.GetOptional(0, nullptr);
	List<const RandomNameConfigItem*>* items1 = mItemDict.GetOptional(1, nullptr);
	List<const RandomNameConfigItem*>* items2 = mItemDict.GetOptional(2, nullptr);
	HeapString result;
	if (items0 != nullptr&&!items0->IsEmpty())
	{
		intp index = random.Next(static_cast<int>(items0->Count()) - 1);
		result += items0->Get(index)->Value();
	}
	bool has1 = random.NextBool();
	if (items1 != nullptr&&!items1->IsEmpty() && has1)
	{
		intp index = random.Next(static_cast<int>(items1->Count()) - 1);
		result += items1->Get(index)->Value();
	}

	if (items2 != nullptr&&!items2->IsEmpty())
	{
		intp index = random.Next(static_cast<int>(items2->Count()) - 1);
		result += items2->Get(index)->Value();
	}

	return result;

}
//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(RandomNameConfig, 16);
SIREN_FIELD_METADATA_STRUCT(0, RandomNameConfig, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;