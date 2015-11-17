// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ColorTimelineModel.h"

MEDUSA_BEGIN;


ColorTimelineModel::ColorTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


ColorTimelineModel::~ColorTimelineModel(void)
{
}

void ColorTimelineModel::AddColor(float time, const Color4F& color)
{
	mColors.Add(color);
	AddFrame(time, (uint)mColors.Count() - 1);
}

Color4F ColorTimelineModel::GetColor(float time) const
{
	if (mIsPreCalculated)
	{
		intp index = GetPreCalculatedIndex(time);
		return mPreCalculatedColors[index];
	}

	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (TryGetFrame(time, outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			return mColors[outPrevFrameIndex] * (1.f - outPercent) + mColors[outNextFrameIndex] * outPercent;
		}
		else
		{
			return mColors[outNextFrameIndex];
		}
	}

	return Color4F::White;
}

void ColorTimelineModel::OnPreCalculateBegin()
{
	mPreCalculatedColors.Clear();
}


void ColorTimelineModel::AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	Color4F color = Color4F::White;
	if (isFound)
	{
		if (nextFrameIndex != prevFrameIndex)
		{
			color = mColors[prevFrameIndex] * (1.f - percent) + mColors[nextFrameIndex] * percent;
		}
		else
		{
			color = mColors[nextFrameIndex];
		}
	}
	mPreCalculatedColors.Add(color);

}

void ColorTimelineModel::RemovePreCalculated()
{
	ITimelineModel::RemovePreCalculated();
	mPreCalculatedColors.Clear();
}



MEDUSA_END;