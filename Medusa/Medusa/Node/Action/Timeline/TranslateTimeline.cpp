// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/TranslateTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/TranslateTimelineModel.h"

MEDUSA_BEGIN;

TranslateTimeline::TranslateTimeline(const Share<TranslateTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

TranslateTimeline::TranslateTimeline(const Share<TranslateTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

TranslateTimeline::~TranslateTimeline()
{
}


bool TranslateTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	auto model = mModel.CastPtr<TranslateTimelineModel>();
	Point3F val = model->GetTranslate(Elapsed())*blend;
	INode* node = (INode*)mTarget;
	node->SetPosition(val);

	return true;
}

MEDUSA_END;
