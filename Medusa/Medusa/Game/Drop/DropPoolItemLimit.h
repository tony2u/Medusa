// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DropPoolItemLimit
{
public:
	struct Schema;
	DropPoolItemLimit();
	~DropPoolItemLimit();
//SIREN_HEADER_COPY_BEGIN
public:
	DropPoolItemLimit(const DropPoolItemLimit& other)
	{
		mItemId = other.mItemId;
		mType = other.mType;
		mMinCount = other.mMinCount;
		mMaxCount = other.mMaxCount;
	}
	DropPoolItemLimit& operator=(const DropPoolItemLimit& other)
	{
		mItemId = other.mItemId;
		mType = other.mType;
		mMinCount = other.mMinCount;
		mMaxCount = other.mMaxCount;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	bool operator<(const DropPoolItemLimit& other)const { return mType < other.mType&&mItemId < other.mItemId; }
	bool operator==(const DropPoolItemLimit& other)const { return mType == other.mType&&mItemId == other.mItemId; }
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, ItemId);
	SIREN_METHOD(int, Type);
	SIREN_METHOD(int, MinCount);
	SIREN_METHOD(int, MaxCount);
//SIREN_HEADER_METHOD_END
public:
	intp HashCode()const { return mItemId^mType; }
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mItemId;
	int mType;
	int mMinCount;
	int mMaxCount;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolItemLimit::Schema
{
	SIREN_PROPERTY(0, 0, Required, DropPoolItemLimit, uint, mItemId);
	SIREN_PROPERTY(1, 1, Optional, DropPoolItemLimit, int, mType);
	SIREN_PROPERTY(2, 2, Required, DropPoolItemLimit, int, mMinCount);
	SIREN_PROPERTY(3, 3, Required, DropPoolItemLimit, int, mMaxCount);
	SIREN_PROPERTIES_4(void,DropPoolItemLimit);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;