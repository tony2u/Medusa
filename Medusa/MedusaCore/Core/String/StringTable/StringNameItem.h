// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"
#include "Core/String/HeapString.h"
//SIREN_HEADER_INCLUDE_BEGIN
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class StringNameItem
{

public:
	struct Schema;
	StringNameItem();
	StringNameItem(const StringRef& name);
	StringNameItem(uint order, const StringRef& filePath);
	~StringNameItem();
	bool operator==(const StringNameItem& other)const { return mName == other.mName; }
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(uint, HeapString, Items);
//SIREN_HEADER_METHOD_END

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	bool Contains(uint order)const;
	bool Initialize();
	bool Add(uint order, const StringRef& val);
	const HeapString* Find(uint order)const;
//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<uint, HeapString> mItems;
//SIREN_HEADER_FIELD_END

	HeapString mName;
	Dictionary<uint, HeapString>::KeyValuePairType* mFirstItem;
};

//SIREN_HEADER_SCHEMA_BEGIN
struct StringNameItem::Schema
{
	SIREN_PROPERTY_DICTIONARY(0, 0, Required, StringNameItem, uint, HeapString, mItems);
	SIREN_PROPERTIES_1(void,StringNameItem);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;