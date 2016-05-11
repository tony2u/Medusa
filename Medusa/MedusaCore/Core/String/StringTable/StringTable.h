// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/String/StringTable/StringNameItem.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/IO/FileIdRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/IO/IFileLoadable.h"
#include "Core/String/Format/Format.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

class StringTable :public Singleton<StringTable>, public IFileLoadable
{
	friend class Singleton < StringTable >;
public:
	struct Schema;
	StringTable();
	~StringTable();

//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_DICTIONARY(HeapString, StringNameItem, Items);
//SIREN_HEADER_METHOD_END

	bool Initialize(const FileIdRef& fileId, uint format = 0);
	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0);
	virtual void Unload();

public:
	bool Contains(const FileIdRef& fileId)const;
	StringRef GetString(const FileIdRef& fileId)const;
	const Dictionary<uint, HeapString>* GetAllStrings(StringRef name)const;

	template<typename... TArgs>
	HeapString GetStringFormat(FileIdRef fileId, const TArgs&...args)const
	{
#ifdef MEDUSA_SAFE_CHECK
		Log::Assert(fileId.Name.EndWith("Format"), "key should ends with Format");
#endif // MEDUSA_SAFE_CHECK

		StringRef format = GetString(fileId);
		return String::Format(format, args...);
	}

	bool Add(const FileIdRef& fileId, const StringRef& val);
	bool Add(const StringRef& name, uint order, const StringRef& val);

//SIREN_HEADER_FIELD_BEGIN
protected:
	Dictionary<HeapString, StringNameItem> mItems;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct StringTable::Schema
{
	SIREN_FIELD_DICTIONARY(0, 0, Required, StringTable, HeapString, StringNameItem, mItems);
	SIREN_FIELDS_1(void,StringTable);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;