// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODLightTimelineModel.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

PODLightTimelineModel::PODLightTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


PODLightTimelineModel::~PODLightTimelineModel(void)
{
}

bool PODLightTimelineModel::Initialize( StringRef lightName,StringRef targetNodeName/*=StringRef::Empty*/ )
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	mLightName=lightName;
	mTargetNodeName=targetNodeName;
	return true;
}


MEDUSA_END;