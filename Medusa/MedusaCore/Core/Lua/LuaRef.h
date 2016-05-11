// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "LuaTypeMapping.h"
#include "LuaStack.h"
#include "LuaStackAutoReset.h"

MEDUSA_BEGIN;


class LuaRef
{
public:
	const static LuaRef Empty;
public:
	constexpr LuaRef() {}
	LuaRef(lua_State* state);
	LuaRef(lua_State* state, std::nullptr_t) :mState(state), mRef(LUA_REFNIL) {}
	LuaRef(lua_State* state, int index);
	LuaRef(lua_State* state, StringRef name);

	~LuaRef(void);

	LuaRef(const LuaRef& other);
	LuaRef& operator=(const LuaRef& other);
	LuaRef(LuaRef&& other);
	LuaRef& operator=(LuaRef&& other);
	LuaRef& operator=(std::nullptr_t);

	bool IsReferenceEqual(const LuaRef& other)const;
	int Compare(const LuaRef& other)const;
	bool operator==(const LuaRef& other)const;
	bool operator!=(const LuaRef& other)const;
	bool operator<(const LuaRef& other)const;
	bool operator<=(const LuaRef& other)const;
	bool operator>(const LuaRef& other)const;
	bool operator>=(const LuaRef& other)const;

	bool operator==(std::nullptr_t)const { return !IsValid(); }
	bool operator!=(std::nullptr_t)const { return IsValid(); }


	explicit operator bool()const { return mRef != LUA_NOREF&&mRef != LUA_REFNIL; }
public:
	static LuaRef PopFromStack(lua_State* state);
	static LuaRef RefToTop(lua_State* state);


	static LuaRef NewUserData(lua_State* state, size_t size, void** outUserData = nullptr);
	static LuaRef Global(lua_State* state);
	static LuaRef Registry(lua_State* state);
	static LuaRef ClassTable(lua_State* state);

	static LuaRef EvaluateGet(lua_State* state, StringRef name);

	template<typename T>
	static bool EvaluateSet(lua_State* state, StringRef name, const T& val)
	{
		return LuaRef::Global(state).EvaluateSet(name, val);
	}

	static LuaRef NewTable(lua_State* state, int arraySize = 0, int recordCount = 0);
	static LuaRef NewTableWithMeta(lua_State* state, StringRef name);

	template<typename T>
	static LuaRef From(lua_State* state, const T& val)
	{
		LuaStack s(state);
		s.Push(val);
		return PopFromStack(state);
	}

	template <typename... TArgs>
	static LuaRef NewFunctionWith(lua_State* state, lua_CFunction func, TArgs&&... upvalues)
	{
		LuaStack s(state);
		s.PushFunctionWith(func, std::forward<TArgs>(upvalues)...);
		return PopFromStack(state);
	}

	template <typename TArg1, typename... TArgs>
	static void FromValues(List<LuaRef>& outRefs, lua_State* state, TArg1&& arg1, TArgs&&... values)
	{
		outRefs.Add(LuaRef::From(state, std::forward<TArg1>(arg1)));
		FromValues(outRefs, state, std::forward<TArgs>(values)...);
	}

	static void FromValues(List<LuaRef>& outRefs, lua_State* state)
	{

	}

public:
	lua_State* State() const { return mState; }
	void SetState(lua_State* val) { mState = val; }
	bool IsValid()const { return mRef != LUA_NOREF&&mRef != LUA_REFNIL; }
	void PushToStack()const;
	int Type()const;
	const LuaRef& CheckType(int type)const;

	template<typename T>
	T To()const
	{
		PushToStack();
		LuaStack s(mState);
		return s.Pop<T>();
	}
public:
	LuaRef GetMetaTable()const;
	void SetMetaTable(const LuaRef& meta);

	template <typename TValue = LuaRef, typename TKey>
	TValue Rawget(const TKey& key) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		lua_rawget(mState, -2);
		TValue v = LuaType<TValue>::Get(mState, -1);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TValue, typename TKey>
	void Rawset(const TKey& key, const TValue& val) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		LuaType<TValue>::Push(mState, val);
		lua_rawset(mState, -3);
		lua_pop(mState, 1);
	}


	template <typename TValue = LuaRef>
	TValue Rawget(void* key) const
	{
		return Rawgetp<TValue>(key);
	}

	template <typename TValue = LuaRef>
	TValue Rawgetp(void* key) const
	{
		PushToStack();
		lua_rawgetp(mState, -1, key);
		TValue v = LuaType<TValue>::Get(mState, -1);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TValue = LuaRef>
	TValue Rawgetp(void* key, const TValue& def) const
	{
		PushToStack();
		lua_rawgetp(mState, -1, key);
		TValue v = LuaType<TValue>::Optional(mState, -1, def);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TValue = LuaRef>
	TValue Rawget(void* key, const TValue& def) const
	{
		return Rawgetp(key, def);
	}

	template <typename TValue>
	void Rawsetp(void* key, const TValue& val) const
	{
		PushToStack();
		LuaType<TValue>::Push(mState, val);
		lua_rawsetp(mState, -2, key);
		lua_pop(mState, 1);
	}

	template <typename TValue>
	void Rawset(void* key, const TValue& val) const
	{
		Rawsetp(key, val);
	}

	template <typename TValue = LuaRef>
	TValue Rawget(int i) const
	{
		PushToStack();
		lua_rawgeti(mState, -1, i);
		TValue v = LuaType<TValue>::Get(mState, -1);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TValue = LuaRef>
	TValue Rawget(int i, const TValue& def) const
	{
		PushToStack();
		lua_rawgeti(mState, -1, i);
		TValue v = LuaType<TValue>::Optional(mState, -1, def);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TValue>
	void Rawset(int i, const TValue& val) const
	{
		PushToStack();
		LuaType<TValue>::Push(mState, val);
		lua_rawseti(mState, -2, i);
		lua_pop(mState, 1);
	}


	template<typename TKey>
	bool Has(const TKey& key)const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		lua_gettable(mState, -2);
		bool ok = !lua_isnoneornil(mState, -1);
		lua_pop(mState, 2);
		return ok;
	}

	template <typename TValue = LuaRef, typename TKey>
	TValue Get(const TKey& key) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		lua_gettable(mState, -2);
		TValue v = LuaType<TValue>::Get(mState, -1);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TKey, typename TValue>
	bool TryGet(const TKey& key, TValue& outValue) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		lua_gettable(mState, -2);
		if (lua_isnoneornil(mState, -1))
		{
			lua_pop(mState, 2);
			return false;
		}
		outValue = LuaType<TValue>::Get(mState, -1);
		lua_pop(mState, 2);
		return true;
	}


	template <typename TKey, typename TValue>
	TValue Optional(const TKey& key, const TValue& def) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		lua_gettable(mState, -2);
		TValue v = LuaType<TValue>::Optional(mState, -1, def);
		lua_pop(mState, 2);
		return v;
	}

	template <typename TKey, typename TValue>
	void Set(const TKey& key, const TValue& val) const
	{
		PushToStack();
		LuaType<TKey>::Push(mState, key);
		LuaType<TValue>::Push(mState, val);
		lua_settable(mState, -3);
		lua_pop(mState, 1);
	}

	template <typename TKey>
	void Remove(const TKey& key) const
	{
		Set(key, nullptr);
	}

	int RawLength()const;
	int Length()const;
public:
	template<typename R = void, typename... TArgs>
	R Invoke(TArgs&&... args)const
	{
		LuaStackAutoReset save(mState);
		PushToStack();
		LuaStack s(mState);
		return s.Invoke<R>(std::forward<TArgs>(args)...);	//func,ret
	}

	template<typename... TArgs>
	bool InvokeWithNoReturn(TArgs&&... args)const
	{
		return InvokeWithReturnCount(0, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	bool InvokeWithReturnCount(uint retCount, TArgs&&... args)const
	{
		PushToStack();
		LuaStack s(mState);
		int funcIndex = s.Count();
		bool isSuccess = s.InvokeWithReturnCount(retCount, std::forward<TArgs>(args)...);	//func,ret
		s.RemoveAt(funcIndex);	//ret
		return isSuccess;
	}

	template<typename R = void, typename... TArgs>
	R InvokeMember(const StringRef& name, TArgs&&... args)const
	{
		return Get(name).Invoke<R>(*this, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	bool InvokeMemberWithNoReturn(const StringRef& name, TArgs&&... args)const
	{
		auto member = Get(name);
		if (member.IsValid())
		{
			return member.InvokeWithReturnCount(0, *this, std::forward<TArgs>(args)...);
		}
		return false;
	}

	LuaRef EvaluateGet(StringRef path)const;

	template<typename T>
	bool EvaluateSet(StringRef path, const T& val)const
	{
		return EvaluateSetHelper(path, LuaRef::From(mState, val));
	}

private:
	bool EvaluateSetHelper(StringRef path, const LuaRef& val)const;

private:
	lua_State* mState = nullptr;
	int mRef = LUA_NOREF;
};

//mapping luaref
template <>
struct LuaTypeMapping <LuaRef>	//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const LuaRef& r)
	{
		if (r.IsValid())
		{
			r.PushToStack();
		}
		else
		{
			lua_pushnil(L);
		}
	}

	static LuaRef Get(lua_State* L, int index)
	{
		return lua_isnone(L, index) ? LuaRef() : LuaRef(L, index);
	}

	static LuaRef Optional(lua_State* L, int index, const LuaRef& def)
	{
		return lua_isnone(L, index) ? def : LuaRef(L, index);
	}
};

MEDUSA_END;
#endif