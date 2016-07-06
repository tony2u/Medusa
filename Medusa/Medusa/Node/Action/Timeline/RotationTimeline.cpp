// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/RotationTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/RotationTimelineModel.h"

MEDUSA_BEGIN;


RotationTimeline::RotationTimeline(const Share<RotationTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

RotationTimeline::RotationTimeline(const Share<RotationTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

RotationTimeline::~RotationTimeline()
{
}


bool RotationTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	auto model = mModel.CastPtr<RotationTimelineModel>();
	Rotation3F val= model->GetRotation(Elapsed())*blend;
	INode* node = (INode*)mTarget;
	node->SetRotation(val);

	return true;
}

MEDUSA_END;
