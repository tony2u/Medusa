// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISkeletonAttachmentModel.h"
#include "Core/Geometry/Polygon.h"

MEDUSA_BEGIN;


class SkeletonBoundingBoxAttachmentModel :public ISkeletonAttachmentModel
{
public:
	SkeletonBoundingBoxAttachmentModel(const StringRef& name);
	virtual ~SkeletonBoundingBoxAttachmentModel();
	virtual SkeletonAttachmentType Type()const override { return SkeletonAttachmentType::BoundingBox; }

	virtual bool Initialize()override;

	const PolygonF& Polygon() const { return mPolygon; }
	PolygonF& MutablePolygon() { return mPolygon; }

	void AddVertex(const Point2F& pos);

	bool HitTestLocal(const Point2F& localPos)const;
protected:
	PolygonF mPolygon;

};

MEDUSA_END;
