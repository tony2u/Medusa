// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ScaleTimelineModel.h"

MEDUSA_BEGIN;


ScaleTimelineModel::ScaleTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


ScaleTimelineModel::~ScaleTimelineModel(void)
{
}



void ScaleTimelineModel::AddScale(float time, const Scale3F& scale, Math::TweenType tweenType, const List<float>& args)
{
	mScales.Add(scale);
	AddFrame(time, (uint)mScales.Count() - 1, tweenType, args);
}

Scale3F ScaleTimelineModel::GetScale(float time) const
{
	if (mIsPrecomputed)
	{
		intp index = GetPrecomputedIndex(time);
		return mPrecomputedScales[index];
	}

	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (TryGetFrame(time, outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			return mScales[outPrevFrameIndex] * (1.f - outPercent) + mScales[outNextFrameIndex] * outPercent;
		}
		else
		{
			return mScales[outNextFrameIndex];
		}
	}

	return Scale3F::One;
}

void ScaleTimelineModel::RemovePrecomputed()
{
	ITimelineModel::RemovePrecomputed();
	mPrecomputedScales.Clear();
}

void ScaleTimelineModel::OnPrecomputeBegin()
{
	mPrecomputedScales.Clear();
}

void ScaleTimelineModel::AddPrecomputedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	Scale3F scale = Scale3F::One;
	if (nextFrameIndex != prevFrameIndex)
	{
		scale = mScales[prevFrameIndex] * (1.f - percent) + mScales[nextFrameIndex] * percent;
	}
	else
	{
		scale = mScales[nextFrameIndex];
	}

	mPrecomputedScales.Add(scale);
}

MEDUSA_END;