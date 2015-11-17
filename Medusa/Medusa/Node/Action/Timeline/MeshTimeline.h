// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Action/Timeline/ITimeline.h"

MEDUSA_BEGIN;

class MeshTimeline:public ITimeline
{
public:
	MeshTimeline(MeshTimelineModel* model, intp repeatCount, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);
	MeshTimeline(MeshTimelineModel* model, bool isRepeatForever, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f, const StringRef& name = StringRef::Empty);


	virtual ~MeshTimeline();
protected:
	virtual bool OnUpdate(float prevElapsed,float dt, float blend = 1.f)override;

};

MEDUSA_END;
