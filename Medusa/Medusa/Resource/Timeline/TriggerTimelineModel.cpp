// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TriggerTimelineModel.h"

MEDUSA_BEGIN;


TriggerTimelineModel::TriggerTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:OnceTimelineModel(fileId, duration)
{

}


TriggerTimelineModel::~TriggerTimelineModel(void)
{
}



MEDUSA_END;