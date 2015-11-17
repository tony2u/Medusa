// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/ScaleTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/ScaleTimelineModel.h"

MEDUSA_BEGIN;


ScaleTimeline::ScaleTimeline(ScaleTimelineModel* model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

ScaleTimeline::ScaleTimeline(ScaleTimelineModel* model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

ScaleTimeline::~ScaleTimeline()
{
}


bool ScaleTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	ScaleTimelineModel* model = (ScaleTimelineModel*)mModel;
	Scale3F val = model->GetScale(Elapsed())*blend;
	INode* node = (INode*)mTarget;
	node->SetScale(val);

	return true;
}

MEDUSA_END;
