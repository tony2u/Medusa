// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Game/Drop/DropPoolItem.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DropPoolRandomItem : public DropPoolItem
{
public:
	struct Schema;
	DropPoolRandomItem();
	~DropPoolRandomItem();
//SIREN_HEADER_COPY_BEGIN
public:
	DropPoolRandomItem(const DropPoolRandomItem& other)
	{
		mProbability = other.mProbability;
	}
	DropPoolRandomItem& operator=(const DropPoolRandomItem& other)
	{
		mProbability = other.mProbability;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DropPoolRandomItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Probability);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mProbability;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolRandomItem::Schema
{
	SIREN_PROPERTY(0, 3, Optional, DropPoolRandomItem, uint, mProbability);
	SIREN_PROPERTIES_1(DropPoolItem,DropPoolRandomItem);
};//SIREN_HEADER_SCHEMA_END

struct DropPoolRandomItemProbalityFunc
{
	static uint Get(const DropPoolRandomItem& t1)
	{
		return t1.Probability();
	}
};

struct DropPoolRandomItemProbalityFuncForPointer
{
	static uint Get(const DropPoolRandomItem*const& t1)
	{
		return t1->Probability();
	}
};

MEDUSA_END;