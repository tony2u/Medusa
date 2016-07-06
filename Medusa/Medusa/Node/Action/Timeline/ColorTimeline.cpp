// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/ColorTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/ColorTimelineModel.h"

MEDUSA_BEGIN;

ColorTimeline::ColorTimeline(const Share<ColorTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay,repeatDuration,afterDelay,name)
{

}

ColorTimeline::ColorTimeline(const Share<ColorTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

ColorTimeline::~ColorTimeline()
{
}


bool ColorTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	auto model = mModel.CastPtr<ColorTimelineModel>();
	Color4F color= model->GetColor(Elapsed())*blend;
	INode* node = (INode*)mTarget;
	node->SetColor(color);

	return true;
}

MEDUSA_END;
