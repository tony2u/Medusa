// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END
#include "DropPoolItemLimit.h"

MEDUSA_BEGIN;

class DropPoolItem
{
public:
	struct Schema;
	DropPoolItem();
	~DropPoolItem();
//SIREN_HEADER_COPY_BEGIN
public:
	DropPoolItem(const DropPoolItem& other)
	{
		mId = other.mId;
		mType = other.mType;
		mCount = other.mCount;
	}
	DropPoolItem& operator=(const DropPoolItem& other)
	{
		mId = other.mId;
		mType = other.mType;
		mCount = other.mCount;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	bool operator<(const DropPoolItem& other)const { return mType < other.mType&&mId < other.mId; }
	bool operator==(const DropPoolItem& other)const { return mType == other.mType&&mId == other.mId; }

	bool operator<(const DropPoolItemLimit& other)const { return mType < other.Type()&&mId < other.ItemId(); }
	bool operator==(const DropPoolItemLimit& other)const { return mType == other.Type()&&mId == other.ItemId(); }
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Id);
	SIREN_METHOD(int, Type);
	SIREN_METHOD(int, Count);
//SIREN_HEADER_METHOD_END
public:
	intp HashCode()const { return mId^mType; }
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mId;
	int mType;
	int mCount;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolItem::Schema
{
	SIREN_PROPERTY(0, 0, Required, DropPoolItem, uint, mId);
	SIREN_PROPERTY(1, 1, Optional, DropPoolItem, int, mType);
	SIREN_PROPERTY(2, 2, Optional, DropPoolItem, int, mCount);
	SIREN_PROPERTIES_3(void,DropPoolItem);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;