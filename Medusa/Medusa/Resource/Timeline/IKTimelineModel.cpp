// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IKTimelineModel.h"

MEDUSA_BEGIN;


IKTimelineModel::IKTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


IKTimelineModel::~IKTimelineModel(void)
{
}


void IKTimelineModel::AddData(float time, float mix, bool isBlendPositive, Math::TweenType tweenType, const List<float>& args)
{
	mMixes.Add(mix);
	mBlendPositives.Add(isBlendPositive);
	AddFrame(time, (uint)mMixes.Count() - 1, tweenType, args);

}

float IKTimelineModel::GetMix(float time) const
{
	if (mIsPrecomputed)
	{
		intp index = GetPrecomputedIndex(time);
		return mPrecomputedMixes[index];
	}

	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (TryGetFrame(time, outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			return mMixes[outPrevFrameIndex] * (1.f - outPercent) + mMixes[outNextFrameIndex] * outPercent;
		}
		else
		{
			return mMixes[outNextFrameIndex];
		}
	}

	return 0.f;
}

bool IKTimelineModel::IsBlendPositive(float time) const
{
	intp index = GetSteppedFrameIndex(time);
	return mBlendPositives[index];
}

void IKTimelineModel::OnPrecomputeBegin()
{
	mPrecomputedMixes.Clear();
	mPrecomputedBlendPositives.Clear();
}

void IKTimelineModel::AddPrecomputedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	float mix = 0.f;
	if (isFound)
	{
		if (nextFrameIndex != prevFrameIndex)
		{
			mix = mMixes[prevFrameIndex] * (1.f - percent) + mMixes[nextFrameIndex] * percent;
		}
		else
		{
			mix = mMixes[nextFrameIndex];
		}
	}
	mPrecomputedMixes.Add(mix);
	mPrecomputedBlendPositives.Add(mBlendPositives[prevFrameIndex]);

}

void IKTimelineModel::RemovePrecomputed()
{
	ITimelineModel::RemovePrecomputed();
	mPrecomputedMixes.Clear();
	mPrecomputedBlendPositives.Clear();
}

MEDUSA_END;