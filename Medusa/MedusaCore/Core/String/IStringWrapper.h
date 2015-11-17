// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;

template<typename T>
class TIStringWrapper
{
	using OtherCharType = typename std::conditional<std::is_same<T, char>::value, wchar_t, char>::type;
public:
	bool SetString(const TStringRef<T>& val) { RETURN_FALSE_IF_EQUAL(mString, val); mString = val; OnStringChanged(); return true; }
	bool SetString(const TStringRef<OtherCharType>& val)
	{
		StringParser::ConvertToBuffer(val, mString);
		OnStringChanged();
		return true;
	}


	TStringRef<T> String()const { return mString; }
	THeapString<T>& MutableString() { return mString; }


	template<typename... TArgs>
	void FormatString(const T* inFormat, const TArgs&... args) 
	{
		mString.Format(inFormat, args...);
		OnStringChanged();
	}

	template<typename... TArgs>
	void FormatString(const OtherCharType* inFormat, const TArgs&... args)
	{
		THeapString<OtherCharType> str;
		str.Format(inFormat, args...);
		StringParser::ConvertToBuffer(str, mString);
		OnStringChanged();
	}

	template<typename TValue>
	bool SetValueToString(TValue val)
	{
		return SetString(StringParser::ToStringT<T>(val));
	}

	virtual void OnStringChanged() {}
protected:
	THeapString<T> mString;
};

using IStringWrapper = TIStringWrapper<char>;
using IWStringWrapper = TIStringWrapper<wchar_t>;

MEDUSA_END;
