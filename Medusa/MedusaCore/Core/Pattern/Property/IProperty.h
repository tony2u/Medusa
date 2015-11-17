// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

template<typename T>
class IProperty
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
public:
	IProperty(TParameterType defaultValue) :mValue(defaultValue) {}
	IProperty() {}
	const T& Value()const { return mValue; }
	void SetValue(TParameterType val)
	{
		OnChanged(mValue, val);
		mValue = val;
	}

	Event<void(TParameterType oldValue, TParameterType newValue)> OnChanged;
private:
	T mValue;
};

MEDUSA_END;