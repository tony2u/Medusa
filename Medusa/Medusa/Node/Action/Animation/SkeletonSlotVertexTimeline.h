// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Action/Timeline/ITimeline.h"

MEDUSA_BEGIN;

class SkeletonSlotVertexTimeline:public ITimeline
{
public:
	SkeletonSlotVertexTimeline(VertexTimelineModel* model, ISkeletonAttachmentModel* attachmentModel,bool isRepeatForever = false);
	virtual ~SkeletonSlotVertexTimeline();
	virtual bool Initialize(void* target)override;
protected:
	virtual bool OnUpdate(float prevElapsed,float dt, float blend = 1.f)override;

	ISkeletonAttachmentModel* mAttachmentModel;

};

MEDUSA_END;
