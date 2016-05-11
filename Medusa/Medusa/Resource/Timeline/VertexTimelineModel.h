// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;

class VertexTimelineModel:public ITimelineModel
{
public:
	VertexTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~VertexTimelineModel(void);

	List<Point3F>& NewAddVertexList();
	void AddVertexFrame(float time, Math::TweenType tweenType, const List<float>& args);

	const List<Point3F>& GetVertices(uint index)const;
protected:
	List<List<Point3F>, NoCompare<List<Point3F>> > mVertexList;	//delta
};

MEDUSA_END;
