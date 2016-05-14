// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA
#include "LuaCompat.h"
#include "Core/String/HeapString.h"
#include "LuaRef.h"

MEDUSA_BEGIN;


class LuaSelector
{
public:
	LuaSelector(lua_State* state, StringRef path);
	~LuaSelector(void);
public:
	LuaSelector(const LuaSelector& val);
	LuaSelector(LuaSelector&& val);
	LuaSelector& operator=(const LuaSelector& val);
	LuaSelector& operator=(LuaSelector&& val);

	bool operator==(LuaSelector &other) = delete;// Allow automatic casting when used in comparisons

public:
	//get 
	template<typename T>
	operator T() const { return RetrieveGet(1).To<T>(); }

	template<typename... P>
	operator std::tuple<P...>() const
	{
		using pureTupleType = std::tuple<P...>;
		LuaStackAutoReset save(mState);
		Retrieve(sizeof...(P));
		return LuaType<pureTupleType>::Get(mState, -(intp)sizeof...(P));
	}

	//operator bool() const { return RetrieveGet(1).To<bool>(); }
	//operator char() const { return RetrieveGet(1).To<char>(); }
	//operator byte() const { return RetrieveGet(1).To<byte>(); }
	//operator short() const { return RetrieveGet(1).To<short>(); }
	//operator ushort() const { return RetrieveGet(1).To<ushort>(); }
	//operator int() const { return RetrieveGet(1).To<int>(); }
	//operator uint() const { return RetrieveGet(1).To<uint>(); }
	//operator int64() const { return RetrieveGet(1).To<int64>(); }
	//operator uint64() const { return RetrieveGet(1).To<uint64>(); }
	//operator float() const { return RetrieveGet(1).To<float>(); }
	//operator double() const { return RetrieveGet(1).To<double>(); }
	//operator StringRef() const { return RetrieveGet(1).To<StringRef>(); }

	//have to specify const char*
	bool operator==(const char* val)const { return RetrieveGet(1).To<StringRef>() == StringRef(val); }
	friend bool operator==(const char* val, const LuaSelector& sel) { return (StringRef)sel == StringRef(val); }

	template <typename T>
	inline bool operator==(T&& t) const { return T(*this) == t; }

	template <typename T>
	friend bool operator==(T&& t, const LuaSelector& s) { return T(s) == t; }

	// If the selector is an rvalue, modify in place. Otherwise, create a new Selector and return it.
#ifdef MEDUSA_HAS_REF_QUALIFIER
	LuaSelector&& operator[](const StringRef& name) &&
	{
		mPath += '.';
		mPath += name;
		return std::move(*this);
	}

	LuaSelector&& operator[](const char* name)&&
	{
		mPath += '.';
		mPath += name;
		return std::move(*this);
	}

	LuaSelector&& operator[](const int index) &&
	{
		mPath += '[';
		mPath += StringParser::ToString(index);
		mPath += ']';

		return std::move(*this);
	}
#endif

	LuaSelector operator[](const StringRef& name)const MEDUSA_REF_LVALUE
	{
		auto newPath = mPath;
		newPath += '.';
		newPath += name;
		return LuaSelector(mState, newPath);
	}

	LuaSelector operator[](const char* name)const MEDUSA_REF_LVALUE
	{
		return operator[](StringRef(name));
	}
	
	LuaSelector operator[](const int index)const MEDUSA_REF_LVALUE
	{
		auto newPath = mPath;
		newPath += '[';
		newPath +=StringParser::ToString(index);
		newPath += ']';
		return LuaSelector(mState, newPath);
	}

public:
	//set
	template<typename T>
	LuaSelector& operator=(const T& val) 
	{
		LuaRef::EvaluateSet(mState, mPath, val);
		return *this;
	}


public:
	//return const obj to avoid further []
	template <typename... TArgs>
	const LuaSelector operator()(TArgs&&... args) const
	{
		LuaSelector copy{ *this };
		copy.mIsFunctorActive = true;
		LuaRef::FromValues(copy.mFunctorArguments, mState, std::forward<TArgs>(args)...);
		return copy;
	}

private:
	void Retrieve(uint retCount = 0)const;
	LuaRef RetrieveGet(uint retCount = 0)const;

	LuaRef Get()const;
	bool ExecuteFunctor(uint retCount)const;


protected:
	lua_State* mState = nullptr;
	HeapString mPath;	//"a.b[2].c"	  

	mutable bool mIsFunctorActive = false;
	List<LuaRef> mFunctorArguments;

};


namespace Lua
{
	namespace detail
	{
		template <typename... T>
		class Tuple :public std::tuple<T&...>	//[IGNORE_PRE_DECLARE]
		{
		public:
			Tuple(T&... args) : std::tuple<T&...>(args...) {}

			void operator=(const LuaSelector& val)
			{
				using pureTupleType = std::tuple<T...>;
				std::tuple<T&...>::operator=((pureTupleType)val);
			}
		};

	}
	
	template <typename... T>
	detail::Tuple<T...> tie(T&... args)
	{
		return detail::Tuple<T...>(args...);
	}
}


MEDUSA_END;
#endif