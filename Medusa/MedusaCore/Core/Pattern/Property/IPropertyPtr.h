// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Ptr/NotNullPtr.h"

MEDUSA_BEGIN;

template<typename TClass, typename T>
class IPropertyPtr
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
public:
	IPropertyPtr(TClass* obj, T TClass::* val) :mObj(obj), mValue(val) {}
	const T& Value()const { return mObj->*mValue; }
	void SetValue(TParameterType val)
	{
		OnChanged(mObj->*mValue, val);
		mObj->*mValue = val;
	}

	Event<void(TParameterType oldValue, TParameterType newValue)> OnChanged;
private:
	TClass* mObj;
	T TClass::* mValue;
};

MEDUSA_END;