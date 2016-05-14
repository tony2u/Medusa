// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "Core/String/StringRef.h"
#include "LuaDefines.h"
#include "TLuaTable.h"
#include "LuaClass.h"
#include "LuaEnum.h"
#include "LuaTable.h"


MEDUSA_BEGIN;


class LuaModule :public TLuaTable<LuaModule>
{
	using BaseType = TLuaTable<LuaModule>;
public:
	LuaModule(lua_State* state, const StringRef& name = StringRef::Empty);
	LuaModule(lua_State* state, const LuaRef& self, const StringRef& name = StringRef::Empty);

	LuaModule(const LuaModule& other) = default;
	LuaModule& operator=(const LuaModule& other) { return (LuaModule&)BaseType::operator=(other); }
	LuaModule(LuaModule&& other) = default;
	LuaModule& operator=(LuaModule&& other) { return (LuaModule&)BaseType::operator=(other); }

	virtual ~LuaModule(void);
public:
	LuaModule BeginModule(StringRef name);
	LuaTable BeginTable(StringRef name);


	template<typename T>
	LuaClass<T> BeginClass(StringRef name = StringRef::Empty)const
	{
		if (name.IsEmpty())
		{
			name = LuaClass<T>::FixedClassName();
		}

		auto ref = mRef.Rawget(name);
		if (ref != nullptr)
		{
			return LuaClass<T>(mState, ref, name);
		}
		else
		{
			LuaClass<T> cls(mState, name);
			mRef.Rawset(name, cls.Ref());
			return cls;
		}

	}

	template<typename T>
	LuaEnum<T> BeginEnum(StringRef name = StringRef::Empty)const
	{
		if (name.IsEmpty())
		{
			name = LuaEnum<T>::FixedClassName();
		}

		auto ref = mRef.Rawget(name);
		if (ref != nullptr)
		{
			return LuaEnum<T>(mState, ref, name);
		}
		else
		{
			LuaEnum<T> cls(mState, name);
			mRef.Rawset(name, cls.Ref());
			return cls;
		}

	}
private:

};

MEDUSA_END;
#endif