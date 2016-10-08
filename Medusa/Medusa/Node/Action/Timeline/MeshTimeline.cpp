// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/MeshTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/MeshTimelineModel.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"

MEDUSA_BEGIN;

MeshTimeline::MeshTimeline(const Share<MeshTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

MeshTimeline::MeshTimeline(const Share<MeshTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}


MeshTimeline::~MeshTimeline()
{
}


bool MeshTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	uint frame= UpdateFrameIndex();
	auto model = mModel.CastPtr<MeshTimelineModel>();
	auto mesh = model->GetMeshByIndex(frame);
	INode* node = (INode*)mTarget;
	node->SetMesh(mesh);

	return true;
}

MEDUSA_END;
