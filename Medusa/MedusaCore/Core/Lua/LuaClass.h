// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "LuaCompat.h"
#include "LuaRef.h"
#include "LuaFunctor.h"
#include "LuaObjectValue.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

template<typename TClass>
class LuaClass :public TLuaTable<LuaClass<TClass>>
{
	using SelfType = LuaClass<TClass>;
	using BaseType = TLuaTable<LuaClass<TClass>>;
public:
	static StringRef FixedClassName() { return Compile::TypeTraits<TClass>::FixedClassName(); }
public:
	explicit LuaClass(lua_State* state, const StringRef& name = StringRef::Empty)
		:BaseType(state, name.IsEmpty() ? FixedClassName() : name)
	{
		//override index and new index 
		mRef.Rawset(LuaMetaMethods::Index, &SelfType::OnIndex);
		mRef.Rawset(LuaMetaMethods::NewIndex, &SelfType::OnNewIndex);
		mRef.Rawset(LuaMetaMethods::GC, &OnGC);
		mRef.Rawset(LuaMetaMethods::ToString, &OnToString);
		mRef.Rawset(LuaMetaMethods::ToWatch, &OnToWatch);

		mRef.Rawset(LuaNames::Delete, &OnGC);

		int hashCode =(int) typeid(TClass).hash_code();
		LuaRef classTable= LuaRef::ClassTable(state);
		classTable.Rawset(hashCode, mRef);	//set integer index
		classTable.Rawset(this->mName, mRef);	//also set name index

	}

	explicit LuaClass(lua_State* state, const LuaRef& self, const StringRef& name = StringRef::Empty)
		:BaseType(state, self, name.IsEmpty() ? FixedClassName() : name)
	{

	}

	~LuaClass(void)
	{

	}
public:
	template<typename TBase>
	SelfType& InheritFrom()
	{
		LuaRef classes = LuaRef::ClassTable(mState);
		LuaRef baseClass = classes.Rawget((int)typeid(TBase).hash_code(), mRef);

		if (baseClass != nullptr)
		{
			mRef.Rawset(LuaNames::Base, baseClass);
		}
		else
		{
			Log::AssertFailedFormat("Cannot InheritFrom {}. Have to register base class first", LuaClass<TBase>::FixedClassName());
		}

		return *this;
	}

	SelfType& InheritFrom(const StringRef& baseName)
	{
		LuaRef classes = LuaRef::ClassTable(mState);
		LuaRef baseClass = classes.Rawget(baseName, mRef);

		if (baseClass != nullptr)
		{
			mRef.Rawset(LuaNames::Base, baseClass);
		}
		else
		{
			Log::AssertFailedFormat("Cannot InheritFrom {}. Have to register base class first", baseName);
		}

		return *this;
	}


	template<typename TArgs>
	SelfType& AddConstruct(TArgs)	//e.g. LUA_ARGS(_opt<std::string>
	{
		mRef.Rawset(LuaMetaMethods::Call, &(typename LuaClassConstructor<TClass, TArgs, 2>::Call));
		return *this;
	}

	template<typename TArgs>
	SelfType& AddNew(TArgs)	//e.g. LUA_ARGS(_opt<std::string>
	{
		mRef.Rawset(LuaNames::New, &(typename LuaClassConstructor<TClass, TArgs, 2>::Call));
		return *this;
	}

	//Add or replace a factory function, that is a normal/static function that return the object, pointer or smart pointer of the type:
	template<typename TFunc>
	SelfType& AddFactory(const TFunc& func)
	{
		using funcType = std::decay<TFunc>::type;
		mRef.Rawset(LuaNames::New, LuaRef::NewFunctionWith(mState, typename LuaBindMethod<TClass, funcType, 2>::Call, func));	//
		return *this;
	}

	template<typename T>
	SelfType& AddMemberVariable(StringRef name, T TClass::* val, bool writable = true)
	{
		SetGetter(name, LuaRef::NewFunctionWith(mState, &OnGetMemberVariable<T>, val));
		if (writable)
		{
			SetSetter(name, LuaRef::NewFunctionWith(mState, &OnSetMemberVariable<T>, val));
		}
		else
		{
			SetReadonly(name);
		}

		return *this;
	}

	template<typename T>
	SelfType& AddMemberVariable(StringRef name, const T TClass::* val, bool writable = true)
	{
		SetGetter(name, LuaRef::NewFunctionWith(mState, &OnGetMemberVariable<T>, val));
		SetReadonly(name);
		return *this;
	}


	template<typename TGetter, typename TSetter>
	SelfType& AddMemberProperty(StringRef name, const TGetter& getter, const TSetter& setter)
	{
		using getterType = std::decay<TGetter>::type;
		using setterType = std::decay<TSetter>::type;

		SetGetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, getterType>::Call, getter));
		SetSetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, setterType>::Call, setter));

		return *this;
	}

	template<typename TGetter>
	SelfType& AddMemberPropertyGet(StringRef name, const TGetter& getter)
	{
		using getterType = std::decay<TGetter>::type;
		SetGetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, getterType>::Call, getter));
		return *this;
	}

	template<typename TSetter>
	SelfType& AddMemberPropertySet(StringRef name, const TSetter& setter)
	{
		using setterType = std::decay<TSetter>::type;
		SetSetter(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, setterType>::Call, setter));
		return *this;
	}

	template<typename TFunc>
	SelfType& AddMemberFunction(StringRef name, const TFunc& func)
	{
		using funcType = std::decay<TFunc>::type;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, funcType>::Call, func));

		return *this;
	}

	template<typename TFunc, typename TArgModifiers>
	SelfType& AddMemberFunction(StringRef name, const TFunc& func, TArgModifiers)
	{
		using funcType = std::decay<TFunc>::type;
		using argType = std::decay<TArgModifiers>::type;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindMemberMethod<TClass, funcType, argType>::Call, func));
		return *this;
	}

	template<typename TFunc>
	SelfType& AddFunctionAsMember(StringRef name, const TFunc& func)
	{
		using funcType = std::decay<TFunc>::type;
		typename Compile::FunctionTraits<TFunc>::type* funcPtr = func;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindStaticToMember<TClass, funcType>::Call, funcPtr));

		return *this;
	}

	template<typename TFunc, typename TArgModifiers>
	SelfType& AddFunctionAsMember(StringRef name, const TFunc& func, TArgModifiers)
	{
		using funcType = std::decay<TFunc>::type;
		using argType = std::decay<TArgModifiers>::type;
		typename Compile::FunctionTraits<TFunc>::type* funcPtr = func;
		mRef.Rawset(name, LuaRef::NewFunctionWith(mState, typename LuaBindStaticToMember<TClass, funcType, argType>::Call, funcPtr));
		return *this;
	}
private:
	static int OnIndex(lua_State* state)
	{
		//table,key
		LuaStack s(state);
		s.PushMetaTable(1);	//table,key,mt

		while (true)
		{
			s.Duplicate(2);		//table,key,mt,key
			s.RawGetField();	//table,key,mt,val

			BREAK_IF_FALSE(s.IsNull());	//val founded

			s.PopNoReturn();	//table,key,mt
			s.RawPushField(LuaNames::Getters);	//table,key,mt,getters

			s.Duplicate(2);	//table,key,mt,getters,key
			s.RawGetField();	//table,key,mt,getters,val

			if (!s.IsNull())
			{
				//founded

				if (s.IsCFunction())
				{
					if (s.IsUserData(1))
					{
						//table is a user data, that means it's a C++ object instance we pushed in, so current function is a member function
						s.Duplicate(1);	//push user data as object param for member function
						lua_call(state, 1, 1);
					}
					else
					{
						lua_call(state, 0, 1);
					}
				}

				break;
			}

			//try to find it in base class
			s.PopNoReturn(2);//table,key,mt
			s.RawPushField(LuaNames::Base);	//table,key,mt,basemt

			if (s.IsNull())
			{
				//no base class
#ifdef MEDUSA_LUA_EXTRA_LUA_FIELDS
				if (s.IsUserData(1))
				{
					lua_getuservalue(state, 1);	//push obj data
					if (!s.IsNull())
					{
						s.Duplicate(2);	//push key
						s.RawGetField();//lookup key in extra fields
					}
				}
#endif
				break;
			}

			assert(s.IsTable());
			s.RemoveAt(-2);	//remove mt, -->table,key,basemt
		}

		return 1;
	}


	static int OnNewIndex(lua_State* state)
	{
		//table,key,val
		LuaStack s(state);
		s.PushMetaTable(1);	//table,key,val,mt
		while (true)
		{
			s.PushField(LuaNames::Setters);	//table,key,val,mt,setters
			assert(s.IsTable());

			s.Duplicate(2);	//table,key,val,mt,setters,key
			s.RawGetField();		//table,key,val,mt,setters,func

			if (s.IsCFunction())
			{
				// setter function found, now need to test whether it is object (== userdata)
				if (s.IsUserData(1))
				{
					//table is a user data, that means it's a C++ object instance we pushed in, so current function is a member function
					s.Duplicate(1);	//push user data as object param 
					s.Duplicate(3);	//push new value as arg
					lua_call(state, 2, 0);
				}
				else
				{
					//static setter
					s.Duplicate(3);	//push new value as arg
					lua_call(state, 1, 0);
				}

				break;
			}

			//try base class
			s.PopNoReturn(2);	//table,key,val,mt
			s.PushField(LuaNames::Base);	//table,key,val,mt,basemt

			if (s.IsNull())
			{
#ifdef MEDUSA_LUA_EXTRA_LUA_FIELDS
				if (s.IsUserData(1))
				{
					lua_getuservalue(state, 1);	//push obj data, //table,key,val,mt,basemt,obj
					if (!s.IsNull())
					{
						s.Duplicate(2);
						s.Duplicate(3);
						s.RawSetField(-3);
					}
					else
					{
						//the data user data refer to is null, we set a new table for it
						s.NewTable();
						s.Duplicate(2);
						s.Duplicate(3);
						s.RawSetField(-3);
						lua_setuservalue(state, 1);
					}
				}
				else
				{
					//notice that the class itself we registered is a table in lua

					//set class field
					s.Duplicate(2);
					s.Duplicate(3);
					s.RawSetField(1);
					break;
				}

#endif
				// not base class, have to give up
				//table,key,val,mt,basemt
				s.Push(LuaNames::Name);
				s.RawGetField(-3);
				//table,key,val,mt,basemt,mtName
				return luaL_error(state, "Failed to set %s.%s. Not found or not writable.", luaL_optstring(state, -1, "<unknown>"), lua_tostring(state, 2));

			}

			assert(s.IsTable());
			s.RemoveAt(-2);//remove mt, -->table,key,basemt
		}

		return 0;

	}
	static int OnGC(lua_State* state)
	{
		try
		{
			ILuaObject* obj = ILuaObject::GetExactObject<TClass>(state);
			if (obj != nullptr)
			{
				obj->~ILuaObject();
			}
			return 0;
		}
		catch (const std::exception& e)
		{
			return luaL_error(state, e.what());
		}

	}

	static int OnToString(lua_State* state)
	{
		try
		{
			StringRef className = FixedClassName();
			ILuaObject* obj = ILuaObject::GetExactObject<TClass>(state);
			HeapString str;
			str.AppendFormat("<{}> {:X#}", className, obj->ObjectPtr());
			LuaStack s(state);
			s.Push(str);

			return 1;
		}
		catch (const std::exception& e)
		{
			return luaL_error(state, e.what());
		}

	}

	static int OnToWatch(lua_State* state)
	{
		try
		{
			StringRef className = FixedClassName();
			ILuaObject* obj = ILuaObject::GetExactObject<TClass>(state);
			HeapString str;
			str.AppendFormat("<{}> {:X#}", className, obj->ObjectPtr());
			LuaStack s(state);
			s.Push(str);

			return 1;
		}
		catch (const std::exception& e)
		{
			return luaL_error(state, e.what());
		}

	}


	template<typename T>
	static int OnGetMemberVariable(lua_State* state)
	{
		try
		{
			assert(lua_islightuserdata(state, lua_upvalueindex(1)));
			auto ptr = static_cast<T TClass::**>(lua_touserdata(state, lua_upvalueindex(1)));
			assert(ptr);

			const TClass* obj = ILuaObject::GetReferenceObject<TClass>(state, 1);	//1 is for obj

			LuaType<T&>::Push(state, obj->**ptr);	//always push reference of object
			return 1;
		}
		catch (std::exception& e)
		{
			return luaL_error(state, e.what());
		}
	}

	template<typename T>
	static int OnSetMemberVariable(lua_State* state)
	{
		try
		{
			assert(lua_islightuserdata(state, lua_upvalueindex(1)));
			auto ptr = static_cast<T TClass::**>(lua_touserdata(state, lua_upvalueindex(1)));
			assert(ptr);
			TClass* obj = ILuaObject::GetReferenceObject<TClass>(state, 1);	//1 is for obj
			obj->**ptr = LuaType<T>::Get(state, 2);
			return 0;
		}
		catch (std::exception& e)
		{
			return luaL_error(state, e.what());
		}
	}
};

MEDUSA_END;
#endif