// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

template<typename T, class TCompare = EqualCompare>
class TConstantTimelineModel :public ITimelineModel
{
public:
	using ITimelineModel::ITimelineModel;
	virtual bool SupportPrecompute()const override { return false; }

	void Add(float time, const T& val)
	{
		mItems.Add(val);
		AddFrame(time, (uint)mItems.Count() - 1, Math::TweenType::None);
	}

	const T& Get(intp index)const
	{
		return mItems[index];
	}
	const T& Get(float time)const
	{
		intp index = GetSteppedFrameIndex(time);
		return mItems[index];
	}

protected:
	List<T, TCompare> mItems;

};

MEDUSA_END;
