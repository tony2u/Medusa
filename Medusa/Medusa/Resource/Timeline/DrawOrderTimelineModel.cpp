// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DrawOrderTimelineModel.h"

MEDUSA_BEGIN;


DrawOrderTimelineModel::DrawOrderTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


DrawOrderTimelineModel::~DrawOrderTimelineModel(void)
{
}


List<uint>& DrawOrderTimelineModel::NewDrawOrderList()
{
	return mDrawOrderList.NewAdd();
}

void DrawOrderTimelineModel::AddDrawOrderFrame(float time)
{
	AddFrame(time, (uint)mDrawOrderList.Count() - 1);

}
bool DrawOrderTimelineModel::IsDrawOrderChanged(float prevTime, float currentTime) const
{
	intp prevFrameIndex = this->GetSteppedFrameIndex(prevTime);
	intp currentFrameIndex = this->GetSteppedFrameIndex(currentTime);
	return prevFrameIndex != currentFrameIndex;
}


const List<uint>& DrawOrderTimelineModel::GetDrawOrder(float time) const
{
	intp frameIndex = this->GetSteppedFrameIndex(time);
	return mDrawOrderList[frameIndex];
}


void DrawOrderTimelineModel::RemovePreCalculated()
{
	ITimelineModel::RemovePreCalculated();
	mPreCalculatedDrawOrderList.Clear();
}

void DrawOrderTimelineModel::OnPreCalculateBegin()
{
	mPreCalculatedDrawOrderList.Clear();
}

void DrawOrderTimelineModel::AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	if (isFound)
	{
		mPreCalculatedDrawOrderList.Add(mDrawOrderList[prevFrameIndex]);
	}
}


MEDUSA_END;