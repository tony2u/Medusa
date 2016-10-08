// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonBoundingBoxAttachmentModel.h"

MEDUSA_BEGIN;


SkeletonBoundingBoxAttachmentModel::SkeletonBoundingBoxAttachmentModel(const StringRef& name)
	:ISkeletonAttachmentModel(name)
{

}


SkeletonBoundingBoxAttachmentModel::~SkeletonBoundingBoxAttachmentModel(void)
{

}

void SkeletonBoundingBoxAttachmentModel::AddVertex(const Point2F& pos)
{
	mPolygon.AddVertex(pos);
}

bool SkeletonBoundingBoxAttachmentModel::Initialize()
{
	mPolygon.EnableRange(true);
	mPolygon.EnablePrecomputed(true);

	return true;
}

bool SkeletonBoundingBoxAttachmentModel::HitTestLocal(const Point2F& localPos) const
{
	return mPolygon.Contains(localPos);

}



MEDUSA_END;