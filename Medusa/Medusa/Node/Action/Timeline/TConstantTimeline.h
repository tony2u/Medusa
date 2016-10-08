// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Action/Timeline/ITimeline.h"

MEDUSA_BEGIN;

template<typename T, class TCompare = EqualCompare>
class TConstantTimeline :public ITimeline
{
	using ModelType = TConstantTimelineModel<T, TCompare>;
	
public:
	TConstantTimeline(const Share<ModelType>& model, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty)
		: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
	{

	}
	TConstantTimeline(const Share<ModelType>& model, bool isRepeatForever=false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty)
		: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
	{

	}

	Event<void(int frameIndex, const T&)> OnValueUpdated;
protected:
	virtual bool OnUpdate(float prevElapsed, float dt, float blend = 1.f)override
	{
		auto model = mModel.CastPtr<ModelType>();
		int frameIndex = UpdateFrameIndex();
		const T& value = model->Get(frameIndex);
		OnValueUpdated(frameIndex, value);
		return true;
	}

};

MEDUSA_END;
