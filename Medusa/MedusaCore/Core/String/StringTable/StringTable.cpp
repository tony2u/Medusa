// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "StringTable.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"
#include "Core/Hash/HashUtility.h"
#include "Core/IO/FileSystem.h"
#include "Core/Siren/Siren.h"


MEDUSA_BEGIN;

StringTable::StringTable()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

StringTable::~StringTable()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END

	Unload();
}


bool StringTable::Initialize(const FileIdRef& fileId, uint format /*= 0*/)
{
	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	RETURN_FALSE_IF_EMPTY(data);
	return LoadFromData(fileId, data, format);
}



bool StringTable::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format/*=0*/)
{
	RETURN_FALSE_IF_FALSE(Siren::DeserializeBinaryTo(data, *this));


	return true;
}

void StringTable::Unload()
{
	mItems.Clear();
}


StringRef StringTable::GetString(const FileIdRef& fileId)const
{
	const StringNameItem* nameItem = mItems.TryGet(fileId.Name);
	Log::AssertNotNullFormat(nameItem, "Cannot find string:{}", fileId.Name.c_str());
	const HeapString* str = nameItem->Find((uint)fileId.Order);
	Log::AssertNotNullFormat(str, "Cannot find string:{} order:{}", fileId.Name.c_str(), (int)fileId.Order);
	return str->ToString();
}


bool StringTable::Contains(const FileIdRef& fileId) const
{
	const StringNameItem* nameItem = mItems.TryGet(fileId.Name);
	RETURN_FALSE_IF_NULL(nameItem);
	return nameItem->Contains((uint)fileId.Order);
}


const Dictionary<uint, HeapString>* StringTable::GetAllStrings(StringRef name) const
{
	const StringNameItem* nameItem = mItems.TryGet(name);
	RETURN_NULL_IF_NULL(nameItem);
	return &(nameItem->Items());
}

bool StringTable::Add(const FileIdRef& fileId, const StringRef& val)
{
	StringNameItem* nameItem = mItems.TryGet(fileId.Name);
	if (nameItem == nullptr)
	{
		nameItem = &mItems.NewAdd(fileId.Name);
		nameItem->SetName(fileId.Name);
	}

	return nameItem->Add((uint)fileId.Order, val);
}

bool StringTable::Add(const StringRef& name, uint order, const StringRef& val)
{
	return Add(FileIdRef(name, order), val);
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(StringTable, 11);
SIREN_FIELD_METADATA_STRUCT(0, StringTable, Items, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;