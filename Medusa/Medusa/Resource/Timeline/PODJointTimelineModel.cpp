// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODJointTimelineModel.h"
#include "Resource/Model/Scene/PODModel.h"

MEDUSA_BEGIN;

PODJointTimelineModel::PODJointTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


PODJointTimelineModel::~PODJointTimelineModel(void)
{
}

bool PODJointTimelineModel::Initialize(const PODNode* node )
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	mNode=node;
	return true;
}


bool PODJointTimelineModel::TryGetMatrix( float frame,Matrix& outMatrix ) const
{
	return mNode->TryGetMatrix(frame,outMatrix);
}


MEDUSA_END;