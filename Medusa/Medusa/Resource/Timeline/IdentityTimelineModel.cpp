// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IdentityTimelineModel.h"
#include "Core/Geometry/Matrix.h"

MEDUSA_BEGIN;

IdentityTimelineModel::IdentityTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


IdentityTimelineModel::~IdentityTimelineModel(void)
{
}


bool IdentityTimelineModel::TryGetMatrix( float frame,Matrix& outMatrix ) const
{
	outMatrix=Matrix::Identity;
	return true;
}


MEDUSA_END;