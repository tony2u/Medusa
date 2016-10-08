// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TranslateTimelineModel.h"

MEDUSA_BEGIN;


TranslateTimelineModel::TranslateTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


TranslateTimelineModel::~TranslateTimelineModel(void)
{
}


void TranslateTimelineModel::AddTranslate(float time, const Point3F& translate, Math::TweenType tweenType, const List<float>& args)
{
	mTranslates.Add(translate);
	AddFrame(time,(uint) mTranslates.Count() - 1,tweenType,args);
}

Point3F TranslateTimelineModel::GetTranslate(float time) const
{
	if (mIsPrecomputed)
	{
		intp index = GetPrecomputedIndex(time);
		return mPrecomputedTranslates[index];
	}

	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (TryGetFrame(time, outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			return mTranslates[outPrevFrameIndex] * (1.f - outPercent) + mTranslates[outNextFrameIndex] * outPercent;
		}
		else
		{
			return mTranslates[outNextFrameIndex];
		}
	}

	return Point3F::Zero;
}

void TranslateTimelineModel::RemovePrecomputed()
{
	ITimelineModel::RemovePrecomputed();
	mPrecomputedTranslates.Clear();
}

void TranslateTimelineModel::OnPrecomputeBegin()
{
	mPrecomputedTranslates.Clear();
}

void TranslateTimelineModel::AddPrecomputedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	Point3F pos = Point3F::Zero;
	if (nextFrameIndex != prevFrameIndex)
	{
		pos = mTranslates[prevFrameIndex] * (1.f - percent) + mTranslates[nextFrameIndex] * percent;
	}
	else
	{
		pos = mTranslates[nextFrameIndex];
	}
	mPrecomputedTranslates.Add(pos);
}

MEDUSA_END;