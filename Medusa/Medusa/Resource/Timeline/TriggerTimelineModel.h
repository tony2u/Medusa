// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/OnceTimelineModel.h"
#include "Core/Command/EventArg/TriggerEventArg.h"

MEDUSA_BEGIN;

class TriggerTimelineModel :public OnceTimelineModel<TriggerEventArg>
{
public:
	TriggerTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~TriggerTimelineModel(void);

	
};

MEDUSA_END;
