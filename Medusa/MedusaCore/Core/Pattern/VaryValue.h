// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;
enum class VaryCurve
{
	Start = 0,
	End = 1,
	Random = 2,
	Custom = 3,
	Gradient = 4,

};

template<typename T>
class VaryValue
{
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
	typedef Delegate<T(float, TParameterType, TParameterType)> TUpdateDelegateType;	//first dt(0~1),from,to
public:
	VaryValue() {}
	VaryValue(TParameterType start) :mStart(start), mEnd(start) {}
	VaryValue(TParameterType start, TParameterType end) :mStart(start), mEnd(end) {}

	VaryValue(const VaryValue& field) { mStart = field.mStart; mEnd = field.mEnd; mCurve = field.mCurve; mUpdateDelegate = field.mUpdateDelegate; }
	VaryValue& operator=(const VaryValue& field) { mStart = field.mStart; mEnd = field.mEnd; mCurve = field.mCurve; mUpdateDelegate = field.mUpdateDelegate; return *this; }
public:
	void Update(float dt) {}	//0~1
private:
	T mStart;
	T mEnd;
	VaryCurve mCurve;
	TUpdateDelegateType mUpdateDelegate;

};
MEDUSA_END;