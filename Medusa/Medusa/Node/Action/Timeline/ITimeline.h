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
	ITimeline(const Share<ITimelineModel>& model, bool isRepeatForever=false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	ITimeline(const Share<ITimelineModel>& model, intp currentCount, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);

	virtual ~ITimeline();

	const Share<ITimelineModel>& Model() const { return mModel; }
	void SetModel(const Share<ITimelineModel>& val) { mModel = val; }

	int FindFrameIndex(uint startIndex = 0)const;
	int UpdateFrameIndex(uint startIndex = 0);

	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseFiniteRepeatableCountDownDelayAction::Reset());
		mPrevFrameIndexFetched=-1;
		return true;
	}
protected:
	virtual void BuildClone(IAction& obj) override;
protected:
	Share<ITimelineModel> mModel;
	int mPrevFrameIndexFetched = -1;	//-1: not used
};
MEDUSA_END;
