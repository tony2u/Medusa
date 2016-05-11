// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class StringId
{
public:
	struct Schema;
	StringId();
	~StringId();
//SIREN_HEADER_COPY_BEGIN
public:
	StringId(const StringId& other)
	{
		mId = other.mId;
		mCheck1 = other.mCheck1;
		mCheck2 = other.mCheck2;
	}
	StringId& operator=(const StringId& other)
	{
		mId = other.mId;
		mCheck1 = other.mCheck1;
		mCheck2 = other.mCheck2;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(StringId);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(int, Id);
	SIREN_METHOD(int, Check1);
	SIREN_METHOD(int, Check2);
//SIREN_HEADER_METHOD_END
	intp HashCode()const { return mId; }

//SIREN_HEADER_FIELD_BEGIN
protected:
	int mId;
	int mCheck1;
	int mCheck2;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct StringId::Schema
{
	SIREN_FIELD(0, 0, Required, StringId, int, mId);
	SIREN_FIELD(1, 1, Required, StringId, int, mCheck1);
	SIREN_FIELD(2, 2, Required, StringId, int, mCheck2);
	SIREN_FIELDS_3(void,StringId);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;