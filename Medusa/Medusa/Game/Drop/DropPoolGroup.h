// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Game/Drop/DropPoolRandomItem.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DropPoolGroup
{
public:
	struct Schema;
	DropPoolGroup();
	~DropPoolGroup();
//SIREN_HEADER_COPY_BEGIN
public:
	DropPoolGroup(const DropPoolGroup& other)
	{
		mPreventDuplicate = other.mPreventDuplicate;
		mMinTimes = other.mMinTimes;
		mMaxTimes = other.mMaxTimes;
		mItems = other.mItems;
	}
	DropPoolGroup& operator=(const DropPoolGroup& other)
	{
		mPreventDuplicate = other.mPreventDuplicate;
		mMinTimes = other.mMinTimes;
		mMaxTimes = other.mMaxTimes;
		mItems = other.mItems;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DropPoolGroup);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(bool, PreventDuplicate);
	SIREN_METHOD(uint, MinTimes);
	SIREN_METHOD(uint, MaxTimes);
	SIREN_METHOD_LIST(DropPoolRandomItem, Items);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	bool mPreventDuplicate;
	uint mMinTimes;
	uint mMaxTimes;
	List<DropPoolRandomItem> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolGroup::Schema
{
	SIREN_PROPERTY(0, 0, Optional, DropPoolGroup, bool, mPreventDuplicate);
	SIREN_PROPERTY(1, 1, Optional, DropPoolGroup, uint, mMinTimes);
	SIREN_PROPERTY(2, 2, Optional, DropPoolGroup, uint, mMaxTimes);
	SIREN_PROPERTY_LIST(3, 3, Required, DropPoolGroup, DropPoolRandomItem, mItems);
	SIREN_PROPERTIES_4(void,DropPoolGroup);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;