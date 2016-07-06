// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/System/PublishTarget.h"
#include "Core/IO/FileDefines.h"

MEDUSA_BEGIN;

class FileIdRef
{
public:
	FileIdRef() :Order(0) {}
	FileIdRef(const StringRef& name, uint order = 0) :Name(name), Order(order) {}

	template<uint TSize>
	FileIdRef(const StackString<TSize>& name, uint order = 0) : Name(name), Order(order) {}

	FileIdRef(const HeapString& name, uint order = 0) :Name(name), Order(order) {}
	FileIdRef(const char* name, uint order = 0) :Name(name), Order(order) {}
	FileIdRef(const std::basic_string<char, std::char_traits<char>, std::allocator<char> >& str, uint order = 0) :Name(str), Order(order) {}

	constexpr FileIdRef(const char* name,uint length, uint order) :Name(name, length), Order(order) {}
	template<size_t size>
	constexpr FileIdRef(const char(&str)[size], uint order = 0)
		: Name(str), Order(order)
	{

	}

	~FileIdRef() = default;
	bool operator<(const FileIdRef& fileId)const;
	void operator=(const FileIdRef& fileId) { Name = fileId.Name; Order = fileId.Order; }
	bool operator==(const FileIdRef& fileId)const { return Name == fileId.Name && Order == fileId.Order; }
	bool operator!=(const FileIdRef& fileId)const { return Name != fileId.Name || Order != fileId.Order; }
	bool IsValid()const { return !Name.IsEmpty(); }
	bool IsEmpty()const { return Name.IsEmpty(); }
	bool IsPath()const;


	template<typename TChar>
	THeapString<TChar> ToString(const TStringRef<TChar>& format = TStringRef<TChar>::Empty)const
	{
		HeapString str = ToString(PublishTarget::MatchAll);
		return StringParser::ToStringT<TChar>(str);
	}

	HeapString ToString(const PublishTarget& tag = PublishTarget::MatchAll)const;
	FileType Type()const;

	intp HashCode()const
	{
		return Name.HashCode() ^ Order;
	}

public:
	StringRef Name;	//performance hit
	uint Order;
	const static FileIdRef Empty;
};

MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <>
struct LuaTypeMapping <FileIdRef>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const FileIdRef& val)
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

	static FileIdRef Get(lua_State* L, int index)
	{
		FileIdRef result;
		LuaStack s(L);
		if (s.IsTable(index))
		{
			result.Name = s.Get<StringRef>("Name");
			result.Order = s.Get<uint>("Order");
		}
		else
		{
			result.Name = s.Get<StringRef>(index);
		}

		return result;
	}

	static FileIdRef Optional(lua_State* L, int index, const FileIdRef& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, FileIdRef& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};
MEDUSA_END;

#endif

