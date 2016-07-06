// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

template<typename T>
class OnceTimelineModel :public ITimelineModel
{
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
	typedef typename Compile::TypeTraits<T>::ConstReturnType TConstReturnType;

public:
	OnceTimelineModel(const FileIdRef& fileId, float duration = 0.f)
		:ITimelineModel(fileId, duration)
	{
	}
	virtual ~OnceTimelineModel(void) {}

	void AddItem(float time, TParameterType item)
	{
		mItems.Add(item);
		AddFrame(time, (uint)mItems.Count() - 1);
	}

	bool TryFire(float prevTime, float currentTime, uintp& outBeginIndex, uintp& outEndIndex)
	{
		outBeginIndex = 0;
		outEndIndex = 0;
		intp prevFrameIndex = this->GetSteppedFrameIndex(prevTime);
		intp currentFrameIndex = this->GetSteppedFrameIndex(currentTime);
		if (currentFrameIndex <= prevFrameIndex)
		{
			return false;
		}
		outBeginIndex = prevFrameIndex + 1;
		outEndIndex = currentFrameIndex;
		return true;
	}

	TConstReturnType GetItem(uintp index)const { return mItems[index]; }
	void SetItem(uintp index, TParameterType val) { mItems[index] = val; }
	const List<T, NoCompare >& Items() const { return mItems; }
	List<T, NoCompare >& MutableItems()  { return mItems; }


	virtual void Clear()
	{
		ITimelineModel::Clear();
		mItems.Clear();
	}

protected:
	List<T, NoCompare > mItems;
};

MEDUSA_END;
