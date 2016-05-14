// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/StringRef.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Lua/ILuaObject.h"
#include "Core/Lua/LuaObjectValue.h"
#include "Core/Lua/LuaObjectPtr.h"


//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

template <typename T, typename enabled = void>
struct LuaTypeMapping;

template <typename T, bool TIsReference>
struct LuaClassMapping;

template <typename T>
struct LuaClassMapping<T, false>	//pass by value
{
	static void Push(lua_State* L, T value)
	{
		LuaObjectValue<T>::New(L, value);
	}

	static T Get(lua_State* L, int index)
	{
		return *ILuaObject::GetReferenceObject<T>(L, index);
	}

	static T Optional(lua_State* L, int index, T def)
	{
		if (lua_isnoneornil(L, index))
			return def;
		return *ILuaObject::GetReferenceObject<T>(L, index);
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		if (lua_isnoneornil(L, index))
			return false;
		outValue = *ILuaObject::GetReferenceObject<T>(L, index);
		return true;
	}
};

template <typename T>
struct LuaClassMapping<T, true>	//pass by ref
{
	static void Push(lua_State* L, T& value)
	{
		LuaObjectPtr<T>::New(L, value);
	}

	static T& Get(lua_State* L, int index)
	{
		return *ILuaObject::GetReferenceObject<T>(L, index);
	}

	static T& Optional(lua_State* L, int index, T& def)
	{
		if (lua_isnoneornil(L, index))
			return def;
		return *ILuaObject::GetReferenceObject<T>(L, index);
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		if (lua_isnoneornil(L, index))
			return false;
		outValue = *ILuaObject::GetReferenceObject<T>(L, index);
		return true;
	}
};

template <typename T>
struct LuaTypeMapping<LuaCustomObjectPtr<T>>
{
	static void Push(lua_State* L, LuaCustomObjectPtr<T> value)
	{
		LuaObjectPtr<T>::New(L, value.Ptr,value.TypeName);
	}
};


template <typename T>
struct LuaIntegerTypeMapping
{
	static void Push(lua_State* L, T value)
	{
		lua_pushinteger(L, static_cast<lua_Integer>(value));
	}

	static T Get(lua_State* L, int index)
	{
		return static_cast<T>(luaL_checkinteger(L, index));
	}

	static T Optional(lua_State* L, int index, T def)
	{
		return static_cast<T>(luaL_optinteger(L, index, static_cast<lua_Integer>(def)));
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		RETURN_FALSE_IF(lua_isnone(L, index));
		outValue = static_cast<T>(luaL_checkinteger(L, index));
		return true;
	}
};

template <typename T>
struct LuaUserDataTypeMapping
{
	static void Push(lua_State* L, T value)
	{
		void* userdata = lua_newuserdata(L, sizeof(T));
		::new (userdata) T(value);
	}

	static T Get(lua_State* L, int index)
	{
		return *static_cast<T*>(lua_touserdata(L, index));
	}

	static T Optional(lua_State* L, int index, T def)
	{
		return lua_isnone(L, index) ? def : *static_cast<T*>(lua_touserdata(L, index));;
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = *static_cast<T*>(lua_touserdata(L, index));
		return true;
	}
};

struct LuaTypeExists
{
	template <typename T, typename = decltype(T())>
	static std::true_type test(int);

	template <typename>
	static std::false_type test(...);
};

template <typename T>
struct LuaTypeMappingExists
{
	using Type = decltype(LuaTypeExists::test<LuaTypeMapping<T>>(0));
	static constexpr bool value = Type::value;
};

template <typename T>
struct LuaType : std::conditional <Compile::TypeTraits<T>::IsFunction|| std::is_member_pointer<T>::value, LuaUserDataTypeMapping<T>,
	typename std::conditional <Compile::IsCustomEnum<T>::Value, LuaIntegerTypeMapping<T>,
	typename std::conditional <
	std::is_class<typename std::decay<T>::type>::value && !LuaTypeMappingExists<typename std::decay<T>::type>::value,
	LuaClassMapping<typename std::decay<T>::type, std::is_reference<T>::value>,
	LuaTypeMapping<typename std::decay<T>::type >> ::type>::type>::type
{

};


template <>
struct LuaTypeMapping <bool>
{
	static void Push(lua_State* L, bool value)
	{
		lua_pushboolean(L, value);
	}

	static bool Get(lua_State* L, int index)
	{
		return lua_toboolean(L, index) == 1;
	}

	static bool Optional(lua_State* L, int index, bool def)
	{
		return lua_isnone(L, index) ? def : lua_toboolean(L, index) == 1;
	}

	static bool TryGet(lua_State* L, int index, bool& outValue)
	{
		RETURN_FALSE_IF(lua_isnone(L, index));
		outValue = lua_toboolean(L, index) == 1;
		return true;
	}

};

template <> struct LuaTypeMapping <char> : LuaIntegerTypeMapping <char> {};
template <> struct LuaTypeMapping <short> : LuaIntegerTypeMapping <short> {};
template <> struct LuaTypeMapping <int> : LuaIntegerTypeMapping <int> {};
template <> struct LuaTypeMapping <long> : LuaIntegerTypeMapping <long> {};


#if LUA_VERSION_NUM <= 502

template <typename T>
struct LuaUnsignedTypeMapping
{
	static void Push(lua_State* L, T value)
	{
		lua_pushunsigned(L, static_cast<lua_Unsigned>(value));
	}

	static T Get(lua_State* L, int index)
	{
		return static_cast<T>(luaL_checkunsigned(L, index));
	}

	static T Optional(lua_State* L, int index, T def)
	{
		return static_cast<T>(luaL_optunsigned(L, index, static_cast<lua_Unsigned>(def)));
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		RETURN_FALSE_IF(lua_isnone(L, index));
		outValue = static_cast<T>(luaL_checkunsigned(L, index));
		return true;
	}
};

#else

template <typename T>
using LuaUnsignedTypeMapping = LuaIntegerTypeMapping<T>;

#endif

template <> struct LuaTypeMapping <unsigned char> : LuaIntegerTypeMapping <unsigned char> {};
template <> struct LuaTypeMapping <unsigned short> : LuaIntegerTypeMapping <unsigned short> {};
template <> struct LuaTypeMapping <unsigned int> : LuaIntegerTypeMapping <unsigned int> {};
template <> struct LuaTypeMapping <unsigned long> : LuaIntegerTypeMapping <unsigned long> {};


template <typename T>
struct LuaNumberTypeMapping
{
	static void Push(lua_State* L, T value)
	{
		lua_pushnumber(L, static_cast<lua_Number>(value));
	}

	static T Get(lua_State* L, int index)
	{
		return static_cast<T>(luaL_checknumber(L, index));
	}

	static T Optional(lua_State* L, int index, T def)
	{
		return static_cast<T>(luaL_optnumber(L, index, static_cast<lua_Number>(def)));
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		RETURN_FALSE_IF(lua_isnone(L, index));
		outValue = static_cast<T>(luaL_checknumber(L, index));
		return true;
	}
};

template <> struct LuaTypeMapping <float> : LuaNumberTypeMapping <float> {};
template <> struct LuaTypeMapping <double> : LuaNumberTypeMapping <double> {};
template <> struct LuaTypeMapping <long double> : LuaNumberTypeMapping <long double> {};



#if MEDUSA_LUA_UNSAFE_INT64 && (LUA_VERSION_NUM <= 502 || defined(LUA_32BITS))

template <typename T>
struct LuaUnsafeInt64TypeMapping
{
	static void Push(lua_State* L, T value)
	{
		lua_Number f = static_cast<lua_Number>(value);
#if MEDUSA_LUA_UNSAFE_INT64_CHECK
		T verify = static_cast<T>(f);
		if (value != verify) {
			luaL_error(L, "unsafe cast from 64-bit int");
		}
#endif
		lua_pushnumber(L, f);
	}

	static T Get(lua_State* L, int index)
	{
		return static_cast<T>(luaL_checknumber(L, index));
	}

	static T Optional(lua_State* L, int index, T def)
	{
		return lua_isnoneornil(L, index) ? def : static_cast<T>(luaL_checknumber(L, index));
	}

	static bool TryGet(lua_State* L, int index, T& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = static_cast<T>(luaL_checknumber(L, index));
		return true;
	}
};

template <>
struct LuaTypeMapping <long long> : LuaUnsafeInt64TypeMapping <long long> {};

template <>
struct LuaTypeMapping <unsigned long long> : LuaUnsafeInt64TypeMapping <unsigned long long> {};

#elif LUA_VERSION_NUM >= 503

template <>
struct LuaTypeMapping <long long> : LuaIntegerTypeMapping <long long> {};

template <>
struct LuaTypeMapping <unsigned long long> : LuaIntegerTypeMapping <unsigned long long> {};

#endif

template <>
struct LuaTypeMapping <lua_CFunction>
{
	static void Push(lua_State* L, lua_CFunction val)
	{
		lua_pushcfunction(L, val);
	}

	static lua_CFunction Get(lua_State* L, int index)
	{
		return lua_tocfunction(L, index);
	}

	static void* Optional(lua_State* L, int index, lua_CFunction def)
	{
		return lua_isnoneornil(L, index) ? def : lua_tocfunction(L, index);
	}

	static bool TryGet(lua_State* L, int index, lua_CFunction& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = lua_tocfunction(L, index);
		return true;
	}
};


template <typename T>
struct LuaTypeMapping <T*>
{
	static void Push(lua_State* L, T* val)
	{
		lua_pushstring(L, LuaNames::ClassesTable.c_str());
		lua_gettable(L, LUA_REGISTRYINDEX);

		lua_pushinteger(L, typeid(T).hash_code());
		lua_rawget(L, -2);//meta

		if (lua_isnoneornil(L, -1))
		{
			//not registered class
			lua_pop(L, 2);
			lua_pushlightuserdata(L, (void*)val);
		}
		else
		{
			//registered class
			lua_pop(L, 2);
			LuaObjectPtr<T>::New(L, val);
		}
	}

	static T* Get(lua_State* L, int index)
	{
		lua_getmetatable(L, index);	//obj,mt
		if (lua_isnoneornil(L, -1))
		{
			//not registered class
			lua_pop(L, 1);
			return (T*)lua_touserdata(L, index);
		}
		else
		{
			lua_pop(L, 1);
			return ILuaObject::GetReferenceObject<T>(L, index);
		}
	}

	static T* Optional(lua_State* L, int index, T* def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, T*& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};

template <>
struct LuaTypeMapping <std::nullptr_t>
{
	static void Push(lua_State* L, std::nullptr_t)
	{
		lua_pushnil(L);
	}
};

template <>
struct LuaTypeMapping <const char*>
{
	static void Push(lua_State* L, const char* str)
	{
		lua_pushstring(L, str);
	}

	static const char* Get(lua_State* L, int index)
	{
		return luaL_checkstring(L, index);
	}

	static const char* Optional(lua_State* L, int index, const char* def)
	{
		return luaL_optstring(L, index, def);
	}

	static bool TryGet(lua_State* L, int index, const char*& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = luaL_checkstring(L, index);
		return true;
	}
};


template <>
struct LuaTypeMapping <char*>
{
	static void Push(lua_State* L, const char* str)
	{
		lua_pushstring(L, str);
	}
};

template <>
struct LuaTypeMapping <std::string>
{
	static void Push(lua_State* L, const std::string& str)
	{
		lua_pushlstring(L, str.data(), str.length());
	}

	static std::string Get(lua_State* L, int index)
	{
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		return std::string(p, len);
	}

	static std::string Optional(lua_State* L, int index, const std::string& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, std::string& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		outValue.assign(p, len);
		return true;
	}
};

template <>
struct LuaTypeMapping <StringRef>
{
	static void Push(lua_State* L, const StringRef& str)
	{
		lua_pushlstring(L, str.c_str(), str.Length());
	}

	static StringRef Get(lua_State* L, int index)
	{
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		return StringRef(p, len);
	}

	static StringRef Optional(lua_State* L, int index, const StringRef& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, StringRef& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		outValue = StringRef(p, len);
		return true;
	}
};


template <>
struct LuaTypeMapping <HeapString>
{
	static void Push(lua_State* L, const HeapString& str)
	{
		lua_pushlstring(L, str.c_str(), str.Length());
	}

	static HeapString Get(lua_State* L, int index)
	{
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		return HeapString(p, len);
	}

	static HeapString Optional(lua_State* L, int index, const HeapString& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, HeapString& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		outValue = StringRef(p, len);
		return true;
	}
};

template <>
struct LuaTypeMapping <MemoryData>
{
	static void Push(lua_State* L, const MemoryData& val)
	{
		lua_pushlstring(L, (char*)val.Data(), val.ByteSize());
	}

	static MemoryData Get(lua_State* L, int index)
	{
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		return MemoryData::FromStatic((byte*)p, len);
	}

	static MemoryData Optional(lua_State* L, int index, const MemoryData& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, MemoryData& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		size_t len;
		const char* p = luaL_checklstring(L, index, &len);
		outValue = MemoryData::FromStatic((byte*)p, len);
		return true;
	}
};



template <typename TClass, typename R, typename... P>
struct LuaTypeMapping <R(TClass::*)(P...)> : LuaUserDataTypeMapping<R(TClass::*)(P...)> {};

template <typename TClass, typename R, typename... P>
struct LuaTypeMapping <R(TClass::*)(P...)const> : LuaUserDataTypeMapping<R(TClass::*)(P...)const> {};


template <typename R, typename... P>
struct LuaTypeMapping <R(*)(P...)>
{
	using ValueType = R(*)(P...);
	static void Push(lua_State* L, ValueType val)
	{
		lua_pushlightuserdata(L, val);
	}

	static ValueType Get(lua_State* L, int index)
	{
		return *static_cast<ValueType>(lua_touserdata(L, index));
	}

	static ValueType Optional(lua_State* L, int index, ValueType def)
	{
		return lua_isnone(L, index) ? def : *static_cast<ValueType>(lua_touserdata(L, index));;
	}

	static bool TryGet(lua_State* L, int index, ValueType& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = *static_cast<T*>(lua_touserdata(L, index));
		return true;
	}
};


/**
* Default type mapping to catch all enum conversion
*/
#if LUA_VERSION_NUM <= 502

template <typename T>
struct LuaTypeMapping <T, typename std::enable_if<std::is_enum<T>::value>::type>
	: std::conditional < std::is_unsigned<typename std::underlying_type<T>::type>::value,
	LuaUnsignedTypeMapping<T>,
	LuaIntegerTypeMapping < T >> ::type
{
};

#else

template <typename T>
struct LuaTypeMapping <T, typename std::enable_if<std::is_enum<T>::value>::type> : LuaIntegerTypeMapping<T> {};

#endif

template <typename T>
struct LuaTypeMapping <List<T>>
{
	static void Push(lua_State* L, const List<T>& val)
	{
		lua_newtable(L);
		if (!val.IsEmpty())
		{
			int i = 1;
			for (auto& v : val)
			{
				LuaType<T>::Push(L, v);
				lua_rawseti(L, -2, i++);
			}
		}
	}

	static List<T> Get(lua_State* L, int index)
	{
		luaL_checktype(L, index, LUA_TTABLE);
		List<T> list;
		int n = luaL_len(L, index);
		for (int i = 1; i <= n; i++)
		{
			lua_rawgeti(L, index, i);
			list.Append(LuaType<T>::Get(L));
			lua_pop(L, 1);
		}
		return list;
	}

	static List<T> Optional(lua_State* L, int index, const List<T>& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, List<T>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue.Clear();
		luaL_checktype(L, index, LUA_TTABLE);
		int n = luaL_len(L, index);
		for (int i = 1; i <= n; i++)
		{
			lua_rawgeti(L, index, i);
			outValue.Append(LuaType<T>::Get(L));
			lua_pop(L, 1);
		}
		return true;
	}
};


template <typename TKey, typename TValue>
struct LuaTypeMapping <Dictionary<TKey, TValue>>
{
	static void Push(lua_State* L, const Dictionary<TKey, TValue>& val)
	{
		lua_newtable(L);
		if (!val.IsEmpty())
		{
			int i = 1;
			for (auto& v : val)
			{
				LuaType<TKey>::Push(L, v.Key);
				LuaType<TValue>::Push(L, v.Value);
				lua_settable(L, -3);
			}
		}
	}

	static Dictionary<TKey, TValue> Get(lua_State* L, int index)
	{
		index = lua_absindex(L, index);	//can only use abs index to call next
		luaL_checktype(L, index, LUA_TTABLE);
		Dictionary<TKey, TValue> map;
		lua_pushnil(L);
		while (lua_next(L, index))
		{
			TKey key = LuaType<TKey>::Get(L, -2);
			map.NewAdd(key) = LuaType<TValue>::Get(L);
			lua_pop(L, 1);
		}
		return map;
	}

	static Dictionary<TKey, TValue> Optional(lua_State* L, int index, const Dictionary<TKey, TValue>& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Dictionary<TKey, TValue>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue.Clear();
		index = lua_absindex(L, index);	//can only use abs index to call next
		luaL_checktype(L, index, LUA_TTABLE);
		lua_pushnil(L);
		while (lua_next(L, index))
		{
			TKey key = LuaType<TKey>::Get(L, -2);
			outValue.NewAdd(key) = LuaType<TValue>::Get(L);
			lua_pop(L, 1);
		}
		return map;
		return true;
	}
};


template <typename... T>
struct LuaTypeMapping <std::tuple<T...>>
{
	static void Push(lua_State* L, const std::tuple<T...>& val)
	{
		SetHelper(L, val, typename Compile::MakeIndexes<sizeof...(T)>::type())
	}

	static std::tuple<T...> Get(lua_State* L, int index)
	{
		return GetHelper(L, index, typename Compile::MakeIndexes<sizeof...(T)>::type());
	}

	static std::tuple<T...> Optional(lua_State* L, int index, const std::tuple<T...>& def)
	{
		return lua_isnoneornil(L, index) ? def : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, std::tuple<T...>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		return TryGetHelper(L, index, outValue, typename Compile::MakeIndexes<sizeof...(T)>::type());
	}
private:
	template<size_t... N>
	static std::tuple<T...> GetHelper(lua_State* L, int index, const Compile::IndexTuple< N... >&)
	{
		return std::make_tuple(LuaType<std::tuple_element<N, std::tuple<T...>>::type>::Get(L, index + N)...);
	}

	template<size_t... N>
	static void SetHelper(lua_State* L, const std::tuple<T...>& val, const Compile::IndexTuple< N... >&)
	{
		LuaType<std::tuple_element<N, std::tuple<T...>>::type>::Push(L, std::get<N>(val))...;
	}

	template<size_t... N>
	static bool TryGetHelper(lua_State* L, int index, std::tuple<T...>& outValue, const Compile::IndexTuple< N... >&)
	{
		(std::get<N>(outValue) = LuaType<std::tuple_element<N, std::tuple<T...>>::type>::Get(L, index + N))...;
	}
};


MEDUSA_END;
#endif