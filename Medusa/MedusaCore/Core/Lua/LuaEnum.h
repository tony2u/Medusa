// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "LuaCompat.h"
#include "LuaRef.h"
#include "LuaFunctor.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

template<typename TEnum>
class LuaEnum :public TLuaTable<LuaEnum<TEnum>>
{
	using SelfType = LuaEnum<TEnum>;
	using BaseType = TLuaTable<LuaEnum<TEnum>>;
public:
	static StringRef FixedClassName() { return Compile::TypeTraits<TEnum>::FixedClassName(); }
public:
	explicit LuaEnum(lua_State* state, const StringRef& name = StringRef::Empty)
		:BaseType(state, name.IsEmpty() ? FixedClassName() : name)
	{
		int hashCode = typeid(TEnum).hash_code();
		LuaRef classTable= LuaRef::ClassTable(state);
		classTable.Rawset(hashCode, mRef);	//set integer index
		classTable.Rawset(this->mName, mRef);	//also set name index
	}

	explicit LuaEnum(lua_State* state, const LuaRef& self, const StringRef& name = StringRef::Empty)
		:BaseType(state, self, name.IsEmpty() ? FixedClassName() : name)
	{

	}

	~LuaEnum(void)
	{

	}
	
};

MEDUSA_END;
#endif