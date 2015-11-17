// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;
template<typename T>
class Nullable
{
public:
	typedef T ValueType;
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
public:
	Nullable() :mHasValue(false) {}
	Nullable(TParameterType val, bool hasValue = true) :mValue(val), mHasValue(hasValue) {}

	Nullable(const Nullable& field) { mValue = field.mValue; mHasValue = field.HasValue(); }
	Nullable& operator=(const Nullable& field) { mValue = field.mValue; mHasValue = field.HasValue(); return *this; }

	Nullable(Nullable&& field) 
		:mValue(std::move(field.mValue)) 
	{
		mHasValue = field.HasValue(); field.mHasValue = false;
	}
	Nullable& operator=(Nullable&& field) { mValue = std::move(field.mValue); mHasValue = field.HasValue(); field.mHasValue = false; return *this; }

	Nullable& operator=(TParameterType val) { mValue = val; mHasValue = true; return *this; }
	Nullable& operator=(void* p) { if (p == nullptr) { mHasValue = false; } else { MEDUSA_ASSERT_FAILED("Invalid assign."); } return *this; }
public:
	bool HasValue() const { return mHasValue; }
	void Clear() { mHasValue = false; }
	T& Value()
	{
		return mValue;
	}

	const T& Value()const
	{
		return mValue;
	}
	void SetValue(TParameterType val) { mValue = val; mHasValue = true; }
private:
	T mValue;
	bool mHasValue;
};
MEDUSA_END;