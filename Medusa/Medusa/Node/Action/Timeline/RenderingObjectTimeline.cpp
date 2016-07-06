// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/RenderingObjectTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/RenderingObjectTimelineModel.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"

MEDUSA_BEGIN;

RenderingObjectTimeline::RenderingObjectTimeline(const Share<RenderingObjectTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

RenderingObjectTimeline::RenderingObjectTimeline(const Share<RenderingObjectTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}


RenderingObjectTimeline::~RenderingObjectTimeline()
{
}


bool RenderingObjectTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	uint frame=CurrentFrameIndex();
	auto model = mModel.CastPtr<RenderingObjectTimelineModel>();
	auto* obj= model->GetItemByIndex(frame);
	INode* node = (INode*)mTarget;
	node->SetRenderingObject(*obj);

	return true;
}

MEDUSA_END;
