// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileIdRef.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;

class FileId
{
public:
	struct Schema;
	FileId() :Order(0) {}
	FileId(const StringRef& name, uint order = 0) :Name(name), Order(order) {}

	FileId(const FileIdRef& other) :Name(other.Name), Order(other.Order) {}
	FileId(const FileId& other) :Name(other.Name), Order(other.Order) {}
	FileId(FileId&& other) :Name(std::move(other.Name)), Order(other.Order) {}
	FileId(FileIdRef&& other) :Name(std::move(other.Name)), Order(other.Order) {}

	FileId& operator=(const FileId& other) { Name = other.Name; Order = other.Order; return *this; }
	FileId& operator=(FileId&& other) { Name = std::move(other.Name); Order = other.Order; return *this; }
	FileId& operator=(const FileIdRef& other) { Name = other.Name; Order = other.Order; return *this; }
	FileId& operator=(FileIdRef&& other) { Name = std::move(other.Name); Order = other.Order; return *this; }


	~FileId() {}
	bool operator<(const FileId& fileId)const;
	
	

	bool operator==(const FileId& fileId)const { return Name == fileId.Name && Order == fileId.Order; }
	bool operator!=(const FileId& fileId)const { return Name != fileId.Name || Order != fileId.Order ; }
	bool operator==(const FileIdRef& fileId)const { return Name == fileId.Name && Order == fileId.Order; }
	bool operator!=(const FileIdRef& fileId)const { return Name != fileId.Name || Order != fileId.Order; }

	bool IsValid()const { return !Name.IsEmpty(); }
	bool IsEmpty()const { return Name.IsEmpty(); }
	bool IsPath()const;

	void Reset() { Name.Clear(); Order = 0; }

	FileIdRef ToRef()const { return FileIdRef(Name, Order); }
	operator FileIdRef()const { return FileIdRef(Name, Order); }

	intp HashCode()const
	{
		return Name.HashCode() ^ Order;
	}

	static FileId ParseFrom(const StringRef& name);

	template<typename TChar>
	THeapString<TChar> ToString(const TStringRef<TChar>& format= TStringRef<TChar>::Empty)const
	{
		HeapString str = ToString(PublishTarget::MatchAll);
		return StringParser::ToStringT<TChar>(str);
	}


	HeapString ToString(const PublishTarget& tag = PublishTarget::MatchAll)const;
	FileType Type()const;

public:
	HeapString Name;
	uint Order;
	const static FileId Empty;
};

struct FileId::Schema
{
	SIREN_FIELD(0, 0, Required, FileId, HeapString, Name);
	SIREN_FIELD(1, 1, Optional, FileId, uint, Order);
	SIREN_FIELDS_2(void, FileId);
};


MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <>
struct LuaTypeMapping <FileId>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const FileId& val)
	{
		LuaStack s(L);
		if (val.Order != 0)
		{
			s.NewTable(0, 2);
			s.Rawset("Name", val.Name);
			s.Rawset("Order", val.Order);
		}
		else
		{
			s.Push(val.Name);
		}

	}

	static FileId Get(lua_State* L, int index)
	{
		FileId result;
		LuaStack s(L);
		if (s.IsTable(index))
		{
			s.RawGetField(index);
			result.Name = s.Get<StringRef>("Name");
			result.Order = s.Get<uint>("Order");
			s.Pop(1);
		}
		else
		{
			result.Name = s.RawgetAt<StringRef>(index);
		}

		return result;
	}

	static FileId Optional(lua_State* L, int index, const FileId& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, FileId& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};
MEDUSA_END;

#endif

