// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Action/Timeline/ITimeline.h"

MEDUSA_BEGIN;

class ScaleTimeline:public ITimeline
{
public:
	ScaleTimeline(ScaleTimelineModel* model, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	ScaleTimeline(ScaleTimelineModel* model, bool isRepeatForever, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);

	virtual ~ScaleTimeline();
protected:
	virtual bool OnUpdate(float prevElapsed,float dt, float blend = 1.f)override;

};

MEDUSA_END;
