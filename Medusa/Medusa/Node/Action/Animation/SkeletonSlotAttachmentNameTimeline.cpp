// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonSlotAttachmentNameTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/StringTimelineModel.h"
#include "Node/Skeleton/SkeletonSlot.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SkeletonSlotAttachmentNameTimeline::SkeletonSlotAttachmentNameTimeline(StringTimelineModel* model, bool isRepeatForever /*= false*/)
	:ITimeline(model, isRepeatForever)
{
}


SkeletonSlotAttachmentNameTimeline::~SkeletonSlotAttachmentNameTimeline()
{
}


bool SkeletonSlotAttachmentNameTimeline::Initialize(void* target)
{
	RETURN_FALSE_IF_FALSE(ITimeline::Initialize(target));
	INode* node = (INode*)mTarget;
	if (!node->IsA<SkeletonSlot>())
	{
		Log::AssertFailed("SkeletonSlotAttachmentTimeline only accept target inherit from SkeletonSlot");
		return false;
	}

	return true;
}


bool SkeletonSlotAttachmentNameTimeline::OnUpdate(float prevElapsed, float dt, float blend /*= 1.f*/)
{
	StringTimelineModel* model = (StringTimelineModel*)mModel;
	SkeletonSlot* slot = (SkeletonSlot*)mTarget;

	StringRef slotName= slot->Name();
	float time = Elapsed();
	intp index = model->GetSteppedFrameIndex(time);
	if (index < 0)
	{
		slot->SetAttachmentFromModel();
	}
	else
	{
		StringRef val = model->GetString(index);
		slot->SetAttachment(val);
	}
	
	return true;
}

MEDUSA_END;
