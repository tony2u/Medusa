// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITimeline.h"
#include "Resource/Timeline/ITimelineModel.h"

MEDUSA_BEGIN;


ITimeline::ITimeline(ITimelineModel* model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	:BaseFiniteRepeatableCountDownDelayAction(model->Duration(), repeatCount, beforeDelay, repeatDuration, afterDelay, name),
	mModel(model)
{
	SAFE_RETAIN(mModel);
}

ITimeline::ITimeline(ITimelineModel* model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: BaseFiniteRepeatableCountDownDelayAction(model->Duration(), isRepeatForever, beforeDelay, repeatDuration, afterDelay, name),
	mModel(model)
{
	SAFE_RETAIN(mModel);
}


ITimeline::~ITimeline()
{
	SAFE_RELEASE(mModel);
}

int ITimeline::CurrentFrameIndex() const
{
	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	mModel->TryGetFrame(mElapsed, outPrevFrameIndex, outNextFrameIndex, outPercent);
	return outNextFrameIndex;
}

MEDUSA_END;
