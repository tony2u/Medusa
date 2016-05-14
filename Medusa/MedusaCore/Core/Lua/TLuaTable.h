// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "LuaRef.h"
#include "LuaDefines.h"
#include "Core/String/HeapString.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

template<typename TDerived>
class TLuaTable
{
public:
	TLuaTable(lua_State* state, const StringRef& name = StringRef::Empty)
		: mState(state), mName(name)
	{
		mRef = LuaRef::NewTable(state);
		mRef.SetMetaTable(mRef);	//set metatable to self
		mRef.Rawset(LuaNames::Name, mName);
		mRef.Rawset(LuaNames::Getters, LuaRef::NewTable(mState));
		mRef.Rawset(LuaNames::Setters, LuaRef::NewTable(mState));

		mRef.Rawset(LuaMetaMethods::Index, &TLuaTable<TDerived>::OnIndex);	//<_G>,<table>
		mRef.Rawset(LuaMetaMethods::NewIndex, &TLuaTable<TDerived>::OnNewIndex);	//<_G>,<table>
	}

	TLuaTable(lua_State* state, const LuaRef& self, const StringRef& name = StringRef::Empty)
		: mState(state), mRef(self), mName(name)
	{
		Log::AssertFormat(mRef != nullptr, "Cannot create lua table:{} using null ref.", name);

		if (mName.IsEmpty())
		{
			LuaRef nameRef = mRef.Rawget(LuaNames::Name);
			mName = nameRef.To<HeapString>();
		}
	}

	virtual ~TLuaTable(void) {}

	TLuaTable(const TLuaTable& other) :mState(other.mState), mRef(other.mRef) {}
	TLuaTable& operator=(const TLuaTable& other)
	{
		if (this != &other)
		{
			mState = other.mState;
			mRef = other.mRef;
		}

		return *this;
	}
	TLuaTable(TLuaTable&& other)
		:mState(other.mState), mRef(std::move(other.mRef))
	{
		other.mState = nullptr;
	}
	TLuaTable& operator=(TLuaTable&& other)
	{
		if (this != &other)
		{
			mState = other.mState;
			other.mState = nullptr;

			mRef = std::move(other.mRef);
		}
		return *this;
	}

	lua_State* State() const { return mState; }
	const LuaRef& Ref() const { return mRef; }
	StringRef Name()const { return mName; }
public:
	template<typename T>
	TDerived& AddConst(StringRef name, const T& val)
	{
		SetGetter(name, LuaRef::From(mState, val));
		SetReadonly(name);
		return (TDerived&)*this;
	}

	template<typename T>
	TDerived& AddReference(StringRef name, T& val, bool writable = true)
	{
		SetGetter(name, LuaRef::NewFunctionWith(mState, OnGetVariable<T>, &val));
		if (writable)
		{
			SetSetter(name, LuaRef::NewFunctionWith(mState, OnSetVariable<T>, &val));
		}
		else
		{
			SetReadonly(name);
		}
		return (TDerived&)*this;
	}

	template<typename T>
	TDerived& AddReference(StringRef name, const T& val)
	{
		SetGetter(name, LuaRef::NewFunctionWith(mState, OnGetVariable<T>, &val));
		SetReadonly(name);
		return (TDerived&)*this;
	}


	template<typename TGetter, typename TSetter>
	TDerived& AddProperty(StringRef name, const TGetter& getter, const TSetter& setter)
	{
		using getterType = std::decay<TGetter>::type;
		using setterType = std::decay<TSetter>::type;

		SetGetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<getterType>::Call, getter));
		SetSetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<setterType>::Call, setter));

		return (TDerived&)*this;
	}

	template<typename TGetter>
	TDerived& AddPropertyGet(StringRef name, const TGetter& getter)
	{
		using getterType = std::decay<TGetter>::type;
		SetGetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<getterType>::Call, getter));
		return (TDerived&)*this;
	}

	template<typename TSetter>
	TDerived& AddPropertySet(StringRef name, const TSetter& setter)
	{
		using setterType = std::decay<TSetter>::type;
		SetSetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<setterType>::Call, setter));
		return (TDerived&)*this;
	}

	template<typename TFunc>
	TDerived& AddFunction(StringRef name, const TFunc& func)
	{
		using funcType = std::decay<TFunc>::type;
		typename Compile::FunctionTraits<TFunc>::type* funcPtr = func;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<funcType>::Call, funcPtr));

		return (TDerived&)*this;
	}

	template<typename TFunc, typename TArgModifiers>
	TDerived& AddFunction(StringRef name, const TFunc& func, TArgModifiers)
	{
		using funcType = std::decay<TFunc>::type;
		using argType = std::decay<TArgModifiers>::type;
		typename Compile::FunctionTraits<TFunc>::type* funcPtr = func;

		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<funcType, argType>::Call, funcPtr));
		return (TDerived&)*this;
	}


	template<typename TClass, typename TFunc>
	TDerived& AddMemberFunctionAsStatic(StringRef name, const TClass& obj, const TFunc& func)
	{
		using funcType = std::decay<TFunc>::type;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethodToStatic<TClass, funcType>::Call, &obj, func));
		return (TDerived&)*this;
	}

	template<typename TClass, typename TFunc, typename TArgModifiers>
	TDerived& AddMemberFunctionAsStatic(StringRef name, const TClass& obj, const TFunc& func, TArgModifiers)
	{
		using funcType = std::decay<TFunc>::type;
		using argType = std::decay<TArgModifiers>::type;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethodToStatic<TClass, funcType, argType>::Call, &obj, func));
		return (TDerived&)*this;
	}
protected:
	void SetGetter(StringRef name, const LuaRef& val)
	{
		mRef.Rawget(LuaNames::Getters).Rawset(name, val);
	}
	void SetSetter(StringRef name, const LuaRef& val)
	{
		mRef.Rawget(LuaNames::Setters).Rawset(name, val);
	}
	void SetReadonly(StringRef name)
	{
		LuaStack s(mState);
		mRef.PushToStack();
		s.RawPushField(LuaNames::Setters);
		s.Push(name);	//table,setters,name
		s.PushFunctionWith(OnSetReadonly, name);	//table,setters,name,func
		s.RawSetField();	//table,setters
		s.PopNoReturn();
	}
private:
	static int OnIndex(lua_State* state)
	{
		//table,key
		LuaStack s(state);
		s.PushMetaTable(1);	//table,key,mt
		s.Duplicate(2);		//table,key,mt,key

		s.RawGetField();	//table,key,mt,val
		if (s.IsNull())
		{
			s.PopNoReturn();	//table,key,mt
			s.PushField(LuaNames::Getters);	//table,key,mt,getters

			s.Duplicate(2);	//table,key,mt,getters,key
			s.RawGetField();	//table,key,mt,getters,val

			if (s.IsCFunction())
			{
				lua_call(state, 0, 1);
			}
		}

		return 1;
	}
	static int OnNewIndex(lua_State* state)
	{
		//table,key,val
		LuaStack s(state);
		s.PushMetaTable(1);	//table,key,val,mt
		s.PushField(LuaNames::Setters);	//table,key,val,mt,setters
		assert(s.IsTable());

		s.Duplicate(2);	//table,key,val,mt,setters,key
		s.RawGetField();		//table,key,val,mt,setters,func

		if (s.IsCFunction())
		{
			s.Duplicate(3);	//table,key,val,mt,setters,func,val
			lua_call(state, 1, 0);
		}
		else
		{
			assert(s.IsNull());
			s.PopNoReturn(3);	//table,key,val
			s.RawSetField();
		}
		return 0;
	}
	static int OnSetReadonly(lua_State* state)
	{
		return luaL_error(state, "Failed to set '%s' because read-only", lua_tostring(state, lua_upvalueindex(1)));
	}

	template<typename T>
	static int OnGetVariable(lua_State* state)
	{
		try
		{
			assert(lua_islightuserdata(state, lua_upvalueindex(1)));
			auto ptr = static_cast<const T*>(lua_touserdata(state, lua_upvalueindex(1)));
			assert(ptr);

			LuaType<T&>::Push(state, *ptr);	//always push reference of object
			return 1;
		}
		catch (std::exception& e)
		{
			return luaL_error(state, e.what());
		}
	}

	template<typename T>
	static int OnSetVariable(lua_State* state)
	{
		try
		{
			assert(lua_islightuserdata(state, lua_upvalueindex(1)));
			auto ptr = static_cast<T*>(lua_touserdata(state, lua_upvalueindex(1)));
			assert(ptr);

			*ptr = LuaType<T>::Get(state, 1);
			return 0;
		}
		catch (std::exception& e)
		{
			return luaL_error(state, e.what());
		}
	}
protected:
	lua_State* mState = nullptr;
	LuaRef mRef;
	HeapString mName;

};

MEDUSA_END;
#endif