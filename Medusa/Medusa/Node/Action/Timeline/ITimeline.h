// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseFiniteRepeatableCountDownDelayAction.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class ITimeline :public BaseFiniteRepeatableCountDownDelayAction
{
public:
	ITimeline(const Share<ITimelineModel>& model, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	ITimeline(const Share<ITimelineModel>& model, bool isRepeatForever, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);

	virtual ~ITimeline();

	const Share<ITimelineModel>& Model() const { return mModel; }
	void SetModel(const Share<ITimelineModel>& val) { mModel = val; }

	int CurrentFrameIndex()const;
protected:
	Share<ITimelineModel> mModel;

};
MEDUSA_END;
