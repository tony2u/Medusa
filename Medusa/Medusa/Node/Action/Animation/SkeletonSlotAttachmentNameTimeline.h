// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Action/Timeline/ITimeline.h"

MEDUSA_BEGIN;

class SkeletonSlotAttachmentNameTimeline:public ITimeline
{
public:
	SkeletonSlotAttachmentNameTimeline(StringTimelineModel* model, bool isRepeatForever = false);
	virtual ~SkeletonSlotAttachmentNameTimeline();
	virtual bool Initialize(void* target)override;

protected:

	virtual bool OnUpdate(float prevElapsed,float dt, float blend = 1.f)override;

};

MEDUSA_END;
