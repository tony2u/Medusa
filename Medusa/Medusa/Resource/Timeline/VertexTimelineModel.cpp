// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "VertexTimelineModel.h"

MEDUSA_BEGIN;


VertexTimelineModel::VertexTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


VertexTimelineModel::~VertexTimelineModel(void)
{
}



List<Point3F>& VertexTimelineModel::NewAddVertexList()
{
	return mVertexList.NewAdd();
}

void VertexTimelineModel::AddVertexFrame(float time, Math::TweenType tweenType, const List<float>& args)
{
	AddFrame(time, (uint)mVertexList.Count() - 1, tweenType, args);
}


const List<Point3F>& VertexTimelineModel::GetVertices(uint index) const
{
	return mVertexList[index];
}

MEDUSA_END;