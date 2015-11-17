// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;
template<typename T>
class SwapValue :public INonCopyable<SwapValue<T>>
{
public:
	typedef T ValueType;
	typedef typename Compile::TypeTraits<T>::ReferenceType ValueRef;
	typedef typename Compile::TypeTraits<T>::ConstReferenceType ConstValueRef;
	typedef typename Compile::TypeTraits<T>::ParameterType ParameterType;

public:
	SwapValue()
	{
		mFrontValuePtr = &mFrontValue;
		mBackValuePtr = &mBackValue;
	}
	explicit SwapValue(ParameterType val) :mFrontValue(val), mBackValue(val)
	{
		mFrontValuePtr = &mFrontValue;
		mBackValuePtr = &mBackValue;
	}

	explicit SwapValue(ParameterType val, ParameterType val2) :mFrontValue(val), mBackValue(val2)
	{
		mFrontValuePtr = &mFrontValue;
		mBackValuePtr = &mBackValue;
	}

public:
	ConstValueRef Get(bool isFront)const { return isFront ? (ConstValueRef)*mFrontValuePtr : (ConstValueRef)*mBackValuePtr; }
	ValueRef Mutable(bool isFront) { return isFront ? (ValueRef)*mFrontValuePtr : (ValueRef)*mBackValuePtr; }
	ConstValueRef GetReversely(bool isFront)const { return isFront ? (ConstValueRef)*mBackValuePtr : (ConstValueRef)*mFrontValuePtr; }
	ValueRef MutableReversely(bool isFront) { return isFront ? (ValueRef)*mBackValuePtr : (ValueRef)*mFrontValuePtr; }
	void Set(ParameterType val, bool isFront) { (isFront ? *mFrontValuePtr : *mBackValuePtr) = val; }
	void SetReversely(ParameterType val, bool isFront) { (isFront ? *mBackValuePtr : *mFrontValuePtr) = val; }



	bool IsFront() const { return mFrontValuePtr == &mFrontValue; }
	ConstValueRef Front()const { return (ConstValueRef)*mFrontValuePtr; }
	ConstValueRef Back()const { return (ConstValueRef)*mBackValuePtr; }
	ValueRef MutableFront() { return (ValueRef)*mFrontValuePtr; }
	ValueRef MutableBack() { return (ValueRef)*mBackValuePtr; }
	void SetFront(ParameterType val) { *mFrontValuePtr = val; }
	void SetBack(ParameterType val) { *mBackValuePtr = val; }



	//alias
	bool IsLeft() const { return mFrontValuePtr == &mFrontValue; }
	ConstValueRef Left()const { return (ConstValueRef)*mFrontValuePtr; }
	ConstValueRef Right()const { return (ConstValueRef)*mBackValuePtr; }
	ValueRef MutableLeft() { return (ValueRef)*mFrontValuePtr; }
	ValueRef MutableRight() { return (ValueRef)*mBackValuePtr; }
	void SetLeft(ParameterType val) { *mFrontValuePtr = val; }
	void SetRight(ParameterType val) { *mBackValuePtr = val; }

	bool IsFirst() const { return mFrontValuePtr == &mFrontValue; }
	ConstValueRef First()const { return (ConstValueRef)*mFrontValuePtr; }
	ConstValueRef Second()const { return (ConstValueRef)*mBackValuePtr; }
	ValueRef MutableFirst() { return (ValueRef)*mFrontValuePtr; }
	ValueRef MutableSecond() { return (ValueRef)*mBackValuePtr; }
	void SetFirst(ParameterType val) { *mFrontValuePtr = val; }
	void SetSecond(ParameterType val) { *mBackValuePtr = val; }

	void Swap()
	{
		T* p = mFrontValuePtr;
		mFrontValuePtr = mBackValuePtr;
		mBackValuePtr = p;
	}
private:
	T mFrontValue;
	T mBackValue;
	T* mFrontValuePtr;
	T* mBackValuePtr;
};
MEDUSA_END;