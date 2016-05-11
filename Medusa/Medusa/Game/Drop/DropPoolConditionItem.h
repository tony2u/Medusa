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

class DropPoolConditionItem
{
public:
	struct Schema;
	DropPoolConditionItem();
	~DropPoolConditionItem();
//SIREN_HEADER_COPY_BEGIN
public:
	DropPoolConditionItem(const DropPoolConditionItem& other)
	{
		mPredicateId = other.mPredicateId;
		mItem = other.mItem;
	}
	DropPoolConditionItem& operator=(const DropPoolConditionItem& other)
	{
		mPredicateId = other.mPredicateId;
		mItem = other.mItem;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DropPoolConditionItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, PredicateId);
	SIREN_METHOD(DropPoolItem, Item);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mPredicateId;
	DropPoolItem mItem;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct DropPoolConditionItem::Schema
{
	SIREN_FIELD(0, 0, Required, DropPoolConditionItem, uint, mPredicateId);
	SIREN_FIELD(1, 1, Required, DropPoolConditionItem, DropPoolItem, mItem);
	SIREN_FIELDS_2(void,DropPoolConditionItem);
};

//SIREN_HEADER_SCHEMA_END

MEDUSA_END;