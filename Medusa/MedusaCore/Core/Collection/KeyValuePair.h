// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Hash/HashUtility.h"

MEDUSA_BEGIN;

template<typename TKey, typename TValue, typename TKeyHashCoder = DefaultHashCoder, typename TValueHashCoder = DefaultHashCoder>
struct KeyValuePair
{
	typedef TKey KeyType;
	typedef TValue ValueType;

	typedef typename Compile::TypeTraits<TKey>::ParameterType TKeyParameterType;
	typedef typename Compile::TypeTraits<TValue>::ParameterType TValueParameterType;
	TKey Key;
	TValue Value;

	KeyValuePair() :Key(), Value() {}
	KeyValuePair(TKeyParameterType key, TValueParameterType value) :Key(key), Value(value) {}
	KeyValuePair(const KeyValuePair& pair) :Key(pair.Key), Value(pair.Value) {}
	KeyValuePair& operator=(const KeyValuePair& pair) { Key = pair.Key; Value = pair.Value; return *this; }
	KeyValuePair(KeyValuePair&& pair) :Key(std::move(pair.Key)), Value(std::move(pair.Value)) {}
	KeyValuePair& operator=(KeyValuePair&& pair) { Key = std::move(pair.Key); Value = std::move(pair.Value); return *this; }


	bool operator==(const KeyValuePair& pair)const { return Key == pair.Key&&Value == pair.Value; }
	bool operator<(const KeyValuePair& pair)const { return Key < pair.Key&&Value < pair.Value; }
	intp HashCode()const
	{
		return TKeyHashCoder::HashCode(Key) ^ TValueHashCoder::HashCode(Value);
	}

};

MEDUSA_END;