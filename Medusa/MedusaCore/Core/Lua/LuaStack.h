// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "LuaTypeMapping.h"

MEDUSA_BEGIN;


class LuaStack
{
public:
	LuaStack(lua_State* state);
	~LuaStack(void);
public:
	lua_State* State() const { return mState; }
	void SetState(lua_State* val) { mState = val; }
	int Count()const { return lua_gettop(mState); }
	void SetCount(int val) { lua_settop(mState, val); }
	void Dump()const;
	void DumpCallStack()const;
	static void Dump(lua_State* val);
	static void DumpCallStack(lua_State* val);

public:
	template<typename T>
	inline T Get(int index)const
	{
		return LuaType<T>::Get(mState, index);
	}

	template<typename T>
	inline T Optional(int index, const T& defaultVal)const
	{
		return LuaType<T>::Optional(mState, index, defaultVal);
	}

	template<typename T>
	inline void Push(const T& val)const
	{
		LuaType<T>::Push(mState, val);
	}

	inline void Push(lua_CFunction val, int nArgs)const { lua_pushcclosure(mState, val, nArgs); }
	inline void Push(const char* val, size_t len)const { lua_pushlstring(mState, val, len); }
	inline void PushGlobal()const { lua_pushglobaltable(mState); }

	template <typename... TArgs>
	void PushFunctionWith(lua_CFunction func, TArgs&&... upvalues)
	{
		PushValues(std::forward<TArgs>(upvalues)...);
		lua_pushcclosure(mState, func, sizeof...(TArgs));
	}

	template <typename TArg0, typename... TArgs>
	void PushValues(TArg0&& p0, TArgs&&... p)const
	{
		Push(std::forward<TArg0>(p0));
		PushValues(std::forward<TArgs>(p)...);
	}

	void PushValues()const
	{
		// template terminate function
	}


	template<typename T>
	T Top() const { return Get<T>(-1); }
	void PopNoReturn(int count = 1) const { lua_pop(mState, count); }

	template<typename T> inline T Pop()const { T r = Top<T>(); PopNoReturn(); return r; }
	template<> inline void Pop() const { PopNoReturn(); }

	template<typename T> inline T Pop(const T& def)const { T r = Optional<T>(-1, def); PopNoReturn(); return r; }
public:
	bool IsValid(int index = -1)const { return !lua_isnoneornil(mState, index); }

	bool IsNull(int index = -1)const { return lua_isnoneornil(mState, index); }
	bool IsCFunction(int index = -1)const { return lua_iscfunction(mState, index) == 1; }
	bool IsTable(int index = -1)const { return lua_istable(mState, index); }
	bool IsUserData(int index = -1)const { return lua_isuserdata(mState, index) == 1; }

	void Duplicate(int index = -1)const { return lua_pushvalue(mState, index); }
	void RemoveAt(int index = -1)const { return lua_remove(mState, index); }
	void InsertTo(int index)const { return lua_insert(mState, index); }
	void Replace(int index)const { return lua_replace(mState, index); }
	void Copy(int fromIndex, int toIndex)const { return lua_copy(mState, fromIndex, toIndex); }

	template<typename T>
	T GetGlobal(StringRef name)const
	{
		PushGlobal(name);
		return Pop<T>();
	}

	template <typename TValue, typename TKey>
	TValue Rawget(const TKey& key, int tableIndex = -2) const
	{
		Push(key);
		lua_rawget(mState, tableIndex);
		return Pop<TValue>();
	}

	template <typename TValue, typename TKey>
	void Rawset(const TKey& key, const TValue& val, int tableIndex = -3) const
	{
		Push(key);
		Push(val);
		lua_rawset(mState, tableIndex);
	}

	template <typename TValue>
	TValue Rawget(void* key) const
	{
		return Rawgetp<TValue>(key);
	}

	template <typename TValue>
	TValue Rawgetp(void* key) const
	{
		lua_rawgetp(mState, -1, key);
		return Pop<TValue>();
	}

	template <typename TValue>
	TValue Rawgetp(void* key, const TValue& def) const
	{
		lua_rawgetp(mState, -1, key);
		return Pop(def);
	}

	template <typename TValue>
	TValue Rawget(void* key, const TValue& def) const
	{
		return Rawgetp(key, def);
	}

	template <typename TValue>
	void Rawsetp(void* key, const TValue& val, int tableIndex = -2) const
	{
		Push(key);
		lua_rawsetp(mState, tableIndex, key);
	}

	template <typename TValue>
	void Rawset(void* key, const TValue& val) const
	{
		Rawsetp(key, val);
	}

	template <typename TValue>
	TValue RawgetAt(int i) const
	{
		lua_rawgeti(mState, -1, i);
		return Pop<TValue>();
	}

	template <typename TValue>
	TValue RawgetAt(int i, const TValue& def) const
	{
		lua_rawgeti(mState, -1, i);
		return Pop<TValue>(def);
	}

	template <typename TValue>
	void RawsetAt(int i, const TValue& val, int tableIndex = -2) const
	{
		Push(val);
		lua_rawseti(mState, tableIndex, i);
	}

	void RawsetAt(int i, int tableIndex = -2) const
	{
		lua_rawseti(mState, tableIndex, i);
	}

	template<typename TKey>
	bool Has(const TKey& key, int tableIndex = -2)const
	{
		Push(key);
		lua_gettable(mState, tableIndex);
		bool ok = !lua_isnoneornil(mState, -1);
		lua_pop(mState, 1);
		return ok;
	}


	template <typename TValue, typename TKey>
	TValue Get(const TKey& key, int tableIndex = -2) const
	{
		Push(key);
		lua_gettable(mState, tableIndex);
		return Pop<TValue>();
	}

	template <typename TValue, typename TKey>
	TValue Get(const TKey& key, const TValue& def,int tableIndex=-2) const
	{
		Push(key);

		lua_gettable(mState, tableIndex);
		return Pop<TValue>(def);
	}

	template <typename TValue, typename TKey>
	void Set(const TKey& key, const TValue& val, int tableIndex = -3) const
	{
		Push(key);
		Push(val);

		lua_settable(mState, tableIndex);
	}

	template <typename TKey>
	void Remove(const TKey& key) const
	{
		Set(key, nullptr);
	}

	int RawLength()const;
	int Length()const;
	int FieldCount(int index = -2)const;

	template <typename TKey>
	bool RawPushField(const TKey& key, int tableIndex = -2) const
	{
		Push(key);
		lua_rawget(mState, tableIndex);
		return IsValid();
	}

	bool RawPushFieldAt(int i) const
	{
		lua_rawgeti(mState, -1, i);
		return IsValid();
	}

	bool RawPushField(void* key) const
	{
		lua_rawgetp(mState, -1, key);
		return IsValid();
	}

	template <typename TKey>
	bool PushField(const TKey& key, int tableIndex = -2) const
	{
		Push(key);
		lua_gettable(mState, tableIndex);
		return IsValid();
	}

	void RawGetField(int tableIndex = -2)
	{
		lua_rawget(mState, tableIndex);
	}

	void GetField(int tableIndex = -2)
	{
		lua_gettable(mState, tableIndex);
	}

	void RawSetField(int tableIndex = -3)
	{
		lua_rawset(mState, tableIndex);
	}

	void SetField(int tableIndex = -3)
	{
		lua_settable(mState, tableIndex);
	}

	bool NewTable(int arraySize = 0, int recordCount = 0);
	bool NewTable(StringRef name, int arraySize = 0, int recordCount = 0);


	bool PushMetaTable(int index = -1)const;
	void SetMetaTable(int index = -1);


	int GetType(int index = -1)const
	{
		return lua_type(mState, index);
	}
	
	StringRef GetTypeName(int index = -1)const
	{
		return lua_typename(mState, index);
	}

public:
	int SetErrorHandler()const;

	template<typename R = void, typename... TArgs>
	R Invoke(TArgs&&... args)const
	{
		InvokeWithReturnCount(Compile::ReturnCountTraits<R>::Value, std::forward<TArgs>(args)...);
		return Pop<R>();
	}
	template<typename... TArgs>
	bool InvokeWithNoReturn(TArgs&&... args)const
	{
		return InvokeWithReturnCount(0, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	bool InvokeWithReturnCount(uint retCount, TArgs&&... args)const
	{
		int errorFunc = SetErrorHandler();	//func,err
		int funcIndex = errorFunc - 1;

		//swap error func and func
		Duplicate(funcIndex);
		Copy(errorFunc, funcIndex);
		Replace(errorFunc);
		//err,func
		errorFunc = errorFunc - 1;

		PushValues(std::forward<TArgs>(args)...);

		int statusCode = lua_pcall(mState, sizeof...(args), retCount, errorFunc);	//err,func,ret
		RemoveAt(errorFunc);	//func,ret

		return statusCode == LUA_OK;
	}

private:
	static int OnError(lua_State* state);
private:
	lua_State* mState = nullptr;
};

MEDUSA_END;
#endif