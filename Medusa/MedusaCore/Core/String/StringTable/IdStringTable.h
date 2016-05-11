// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/String/StringTable/StringId.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class IdStringTable
{
public:
	struct Schema;
	IdStringTable();
	~IdStringTable();
//SIREN_HEADER_COPY_BEGIN
public:
	IdStringTable(const IdStringTable& other)
	{
		mItems = other.mItems;
	}
	IdStringTable& operator=(const IdStringTable& other)
	{
		mItems = other.mItems;
		return *this;
	}
//SIREN_HEADER_COPY_END
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(IdStringTable);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(StringId, HeapString, Items);
//SIREN_HEADER_METHOD_END
//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<StringId, HeapString> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct IdStringTable::Schema
{
	SIREN_FIELD_DICTIONARY(0, 0, Required, IdStringTable, StringId, HeapString, mItems);
	SIREN_FIELDS_1(void,IdStringTable);
};

//SIREN_HEADER_SCHEMA_END

MEDUSA_END;