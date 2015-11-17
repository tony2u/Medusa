// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
template<typename T>
class LazyValue
{
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
	typedef Delegate<void(TReferenceType outValue, int32 dirtyFlag)> TUpdateDelegateType;
public:
	LazyValue() :mDirtyFlag((int32)0xFFFFFFFF), mVersion(0) {}
	LazyValue(TParameterType val) :mValue(val), mDirtyFlag(0), mVersion(0) {}
	LazyValue(const LazyValue& field) { mValue = field.mValue; mDirtyFlag = field.DirtyFlag(); mVersion = field.Version(); }
	LazyValue& operator=(const LazyValue& field) { mValue = field.mValue; mDirtyFlag = field.DirtyFlag(); mVersion = field.Version(); return *this; }
	LazyValue& operator=(TParameterType val) { mValue = val; mDirtyFlag = 0; ++mVersion; return *this; }

	LazyValue(LazyValue&& other)
		:mValue(std::move(other.mValue)),
		mDirtyFlag(other.mDirtyFlag),
		mVersion(other.mVersion),
		mUpdateDelegate(std::move(other.mUpdateDelegate))
	{
		other.mDirtyFlag = 0;
		other.mVersion = 0;
		other.mUpdateDelegate = nullptr;
	}
	LazyValue& operator=(LazyValue&& other)
	{
		if (this != &other)
		{
			mValue = std::move(other.mValue);
			mDirtyFlag = other.mDirtyFlag;
			mVersion = other.mVersion;
			mUpdateDelegate = std::move(other.mUpdateDelegate);

			other.mDirtyFlag = 0;
			other.mVersion = 0;
			other.mUpdateDelegate = nullptr;
		}
		return *this;
	}

public:
	bool IsDirty()const { return mDirtyFlag != 0; }
	int32 DirtyFlag() const { return mDirtyFlag; }
	void SetDirty(bool val = true) { mDirtyFlag = val ? 1 : 0; }

	void SetDirtyFlag(int32 val = 1) { mDirtyFlag = val; }
	void AddDirtyFlag(int32 val) { mDirtyFlag |= val; }

	size_t Version() const { return mVersion; }
	bool IsInitialized()const { return mVersion > 0; }

	void CompleteUpdate() { mDirtyFlag = 0; ++mVersion; }

	const T& Value()const
	{
		if (mDirtyFlag)
		{
			ForceUpdate();
		}

		return mValue;
	}

	T& Value()
	{
		if (mDirtyFlag)
		{
			ForceUpdate();
		}

		return mValue;
	}

	const T& OldValue()const { return mValue; }
	T& OldValue() { return mValue; }

	bool TryUpdate()const
	{
		if (mDirtyFlag)
		{
			ForceUpdate();
			return true;
		}
		return false;
	}

	void ForceUpdate()const
	{
		mUpdateDelegate.TryInvoke(mValue, mDirtyFlag);
		mDirtyFlag = 0;
		++mVersion;
	}
	void SetValue(TParameterType val) { mValue = val; mDirtyFlag = 0; ++mVersion; }
	void SetUpdateDelegate(TUpdateDelegateType val) { mUpdateDelegate = val; }

private:
	mutable T mValue;
	mutable int32 mDirtyFlag;
	mutable size_t mVersion;
	TUpdateDelegateType mUpdateDelegate;
};
MEDUSA_END;