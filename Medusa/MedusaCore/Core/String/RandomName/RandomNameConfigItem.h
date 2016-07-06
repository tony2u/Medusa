// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class RandomNameConfigItem
{
public:
	struct Schema;
	RandomNameConfigItem();
	~RandomNameConfigItem();
//SIREN_HEADER_COPY_BEGIN
public:
	RandomNameConfigItem(const RandomNameConfigItem& other)
	{
		mPosition = other.mPosition;
		mValue = other.mValue;
	}
	RandomNameConfigItem& operator=(const RandomNameConfigItem& other)
	{
		mPosition = other.mPosition;
		mValue = other.mValue;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(RandomNameConfigItem);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(uint, Position);
	SIREN_STRING(HeapString, Value);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	uint mPosition;
	HeapString mValue;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct RandomNameConfigItem::Schema
{
	SIREN_FIELD(0, 0, Required, RandomNameConfigItem, uint, mPosition);
	SIREN_FIELD(1, 1, Required, RandomNameConfigItem, HeapString, mValue);
	SIREN_FIELDS_2(void,RandomNameConfigItem);
};

//SIREN_HEADER_SCHEMA_END

MEDUSA_END;