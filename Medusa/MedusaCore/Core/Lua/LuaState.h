// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "Core/Log/Log.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/String/StringRef.h"
#include "LuaStack.h"
#include "LuaModule.h"
#include "LuaClass.h"
#include "LuaSelector.h"
#include "LuaObjectPtr.h"
#include "LuaObjectValue.h"

MEDUSA_BEGIN;

class LuaState
{
	friend class LuaEngine;
public:
	LuaState(bool openDefaultLibs = true);
	LuaState(lua_State* state, bool isOwner = false);
	~LuaState(void);

	LuaState(const LuaState &other) = delete;
	LuaState &operator=(const LuaState &other) = delete;
	LuaState(LuaState &&other)
		: mState(other.mState),
		mIsOwner(other.mIsOwner)
	{
		other.mState = nullptr;
	}

	LuaState &operator=(LuaState &&other)
	{
		if (&other == this)
			return *this;
		mState = other.mState;
		mIsOwner = other.mIsOwner;
		other.mState = nullptr;
		return *this;
	}


	lua_State* GetState() const { return mState; }
	void SetState(lua_State* val) { mState = val; }

	const lua_Number* Version()const { return lua_version(mState); }
	void DumpGlobals();
	void AddPackagePath(const StringRef& path);
	void SetPackagePath(const StringRef& path);

	void AddPackageLoader(lua_CFunction loader);
	void RegisterExtension(const StringRef& name, lua_CFunction loader);


	bool DoFile(const FileIdRef& file, int resultCount = 0);
	bool DoBuffer(StringRef buffer, int resultCount = 0,StringRef name=StringRef::Empty);

	LuaRef DoFileWithReturn(const FileIdRef& file);
	LuaRef DoBufferWithReturn(StringRef buffer, StringRef name = StringRef::Empty);


	void ForceGC();

	template<typename T=LuaRef>
	T Get(StringRef name)
	{
		return LuaRef::EvaluateGet(mState,name).To<T>();
	}

	template<typename T>
	bool Set(StringRef name, const T& val)
	{
		return LuaRef::EvaluateSet(mState, name, val);
	}

public:
	template<typename T>
	LuaState& AddVaraiable(StringRef name, const T& val)
	{
		LuaStack s(mState);
		s.PushGlobal();
		s.Push(name);
		s.Push(val);
		s.RawSetField();
		s.PopNoReturn();
		return *this;
	}

	template<typename TFunc>
	LuaState& AddFunction(StringRef name, const TFunc& func)
	{
		LuaStack s(mState);
		s.PushGlobal();

		s.Push(name);
		using funcType = std::decay<TFunc>::type;
		s.PushFunctionWith(typename LuaBindMethod<funcType>::Call, func);
		s.RawSetField();

		s.PopNoReturn();

		return *this;
	}

	LuaSelector operator[](StringRef name)
	{
		return LuaSelector(mState, name);
	}
public:
	LuaModule BeginModule(StringRef name);

	template<typename T>
	LuaClass<T> BeginClass(StringRef name = StringRef::Empty)const
	{
		if (name.IsEmpty())
		{
			name = LuaClass<T>::FixedClassName();
		}

		LuaRef parent = LuaRef::Global(mState);
		auto ref = parent.Rawget(name);
		if (ref != nullptr)
		{
			return LuaClass<T>(mState, ref, name);
		}
		else
		{
			LuaClass<T> cls(mState, name);
			parent.Rawset(name, cls.Ref());
			return cls;
		}

	}

	LuaStack CurrentStack()const { return LuaStack(mState); }

private:
	//debug
	static int OnPrint(lua_State* state);
	static int OnPackageLoader(lua_State* state);	//rewrite this function to support your all loader

	static int OnIndex(lua_State* state);
	static int OnNewIndex(lua_State* state);
	static void OnParentIndex(lua_State* state);

private:


private:
	lua_State* mState = nullptr;
	bool mIsOwner = false;
};



MEDUSA_END
#endif