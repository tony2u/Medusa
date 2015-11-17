// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RotationTimelineModel.h"

MEDUSA_BEGIN;


RotationTimelineModel::RotationTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{

}


RotationTimelineModel::~RotationTimelineModel(void)
{
}

void RotationTimelineModel::AddRotation(float time, const Rotation3F& rotation, Math::TweenType tweenType, const List<float>& args)
{
	mRotations.Add(rotation);
	AddFrame(time, (uint)mRotations.Count() - 1, tweenType, args);

}

Rotation3F RotationTimelineModel::GetRotation(float time) const
{
	if (mIsPreCalculated)
	{
		intp index = GetPreCalculatedIndex(time);
		return mPreCalcualtedRotations[index];
	}
	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (TryGetFrame(time, outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			Rotation3F prev = mRotations[outPrevFrameIndex];
			Rotation3F next = mRotations[outNextFrameIndex];
			return prev + prev.CloserDiffTo(next)*outPercent;
		}
		else
		{
			return mRotations[outNextFrameIndex];
		}
	}

	return Rotation3F::Zero;
}

void RotationTimelineModel::RemovePreCalculated()
{
	ITimelineModel::RemovePreCalculated();
	mPreCalcualtedRotations.Clear();
}

void RotationTimelineModel::OnPreCalculateBegin()
{
	mPreCalcualtedRotations.Clear();
}

void RotationTimelineModel::AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	Rotation3F rotation = Rotation3F::Zero;
	if (nextFrameIndex != prevFrameIndex)
	{
		Rotation3F prev = mRotations[prevFrameIndex];
		Rotation3F next = mRotations[nextFrameIndex];
		rotation = prev + prev.CloserDiffTo(next)*percent;
	}
	else
	{
		rotation = mRotations[nextFrameIndex];
	}

	mPreCalcualtedRotations.Add(rotation);
}

MEDUSA_END;