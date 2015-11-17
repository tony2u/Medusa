// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Game/Drop/DropPoolItem.h"
#include "Game/Drop/DropPoolGroup.h"
#include "Game/Drop/DropPoolConditionItem.h"
#include "Game/Drop/DropPoolItemLimit.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DropPool
{
public:
	struct Schema;
	DropPool();
	~DropPool();
	//SIREN_HEADER_COPY_BEGIN
public:
	DropPool(const DropPool& other)
	{
		mFixedItems = other.mFixedItems;
		mRandomGroups = other.mRandomGroups;
		mConditionItems = other.mConditionItems;
		mItemLimits = other.mItemLimits;
	}
	DropPool& operator=(const DropPool& other)
	{
		mFixedItems = other.mFixedItems;
		mRandomGroups = other.mRandomGroups;
		mConditionItems = other.mConditionItems;
		mItemLimits = other.mItemLimits;
		return *this;
	}
//SIREN_HEADER_COPY_END
	//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DropPool);
//SIREN_HEADER_COMPARE_END
	//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_LIST(DropPoolItem, FixedItems);
	SIREN_METHOD_LIST(DropPoolGroup, RandomGroups);
	SIREN_METHOD_LIST(DropPoolConditionItem, ConditionItems);
	SIREN_METHOD_LIST(DropPoolItemLimit, ItemLimits);
//SIREN_HEADER_METHOD_END
public:
	bool Generate(const DropPoolConfig& config, List<DropPoolItem>& outItems, void* userData = nullptr)const;
	const DropPoolItem* GenerateFixedSingle()const;

	//SIREN_HEADER_FIELD_BEGIN
protected:
	List<DropPoolItem> mFixedItems;
	List<DropPoolGroup> mRandomGroups;
	List<DropPoolConditionItem> mConditionItems;
	List<DropPoolItemLimit> mItemLimits;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPool::Schema
{
	SIREN_PROPERTY_LIST(0, 0, Optional, DropPool, DropPoolItem, mFixedItems);
	SIREN_PROPERTY_LIST(1, 1, Optional, DropPool, DropPoolGroup, mRandomGroups);
	SIREN_PROPERTY_LIST(2, 2, Optional, DropPool, DropPoolConditionItem, mConditionItems);
	SIREN_PROPERTY_LIST(3, 3, Optional, DropPool, DropPoolItemLimit, mItemLimits);
	SIREN_PROPERTIES_4(void,DropPool);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;