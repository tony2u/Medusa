// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonAnimationModel.h"
#include "Resource/Timeline/ColorTimelineModel.h"
#include "Resource/Timeline/StringTimelineModel.h"
#include "Resource/Timeline/RotationTimelineModel.h"
#include "Resource/Timeline/ScaleTimelineModel.h"
#include "Resource/Timeline/TranslateTimelineModel.h"
#include "Resource/Timeline/VertexTimelineModel.h"
#include "Resource/Timeline/DrawOrderTimelineModel.h"
#include "Resource/Timeline/TriggerTimelineModel.h"
#include "Resource/Timeline/IKTimelineModel.h"


MEDUSA_BEGIN;


SkeletonAnimationModel::SkeletonAnimationModel(const StringRef& name)
	:mName(name),
	mDuration(0.f),
	mDrawOrderTimeLine(nullptr),
	mTriggerTimeline(nullptr),
	mSkeletonModel(nullptr)
{

}


SkeletonAnimationModel::~SkeletonAnimationModel(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mColorTimelineDict);
	SAFE_DELETE_DICTIONARY_VALUE(mTextureTimelineDict);
	SAFE_DELETE_DICTIONARY_VALUE(mRotationTimelineDcit);
	SAFE_DELETE_DICTIONARY_VALUE(mScaleTimelineDcit);
	SAFE_DELETE_DICTIONARY_VALUE(mTranslateTimelineDcit);
	SAFE_DELETE_DICTIONARY_VALUE(mVertexTimelineDcit);
	SAFE_DELETE_DICTIONARY_VALUE(mIKTimelineDcit);


	SAFE_RELEASE(mDrawOrderTimeLine);
	SAFE_RELEASE(mTriggerTimeline);




}


bool SkeletonAnimationModel::Initialize()
{
	//fix all timeline model's duration
	UpdateTimelineDuration();
	return true;
}

void SkeletonAnimationModel::AddColorTimeline(SkeletonSlotModel* slot, ColorTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mColorTimelineDict.Add(slot, timeline);
	SAFE_RETAIN(timeline);
}

void SkeletonAnimationModel::AddTextureTimeline(SkeletonSlotModel* slot, StringTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mTextureTimelineDict.Add(slot, timeline);
	SAFE_RETAIN(timeline);

}

void SkeletonAnimationModel::AddRotationTimeline(SkeletonBoneModel* bone, RotationTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mRotationTimelineDcit.Add(bone, timeline);
	SAFE_RETAIN(timeline);

}

void SkeletonAnimationModel::AddScaleTimeline(SkeletonBoneModel* bone, ScaleTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mScaleTimelineDcit.Add(bone, timeline);
	SAFE_RETAIN(timeline);

}

void SkeletonAnimationModel::AddTranslateTimeline(SkeletonBoneModel* bone, TranslateTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mTranslateTimelineDcit.Add(bone, timeline);
	SAFE_RETAIN(timeline);

}


void SkeletonAnimationModel::AddVertexTimeline(KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*> slotAttachment, VertexTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mVertexTimelineDcit.Add(slotAttachment, timeline);
	SAFE_RETAIN(timeline);

}

void SkeletonAnimationModel::SetDrawOrderTimeLine(DrawOrderTimelineModel* val)
{
	mDuration = Math::Max(mDuration, val->Duration());
	SAFE_ASSIGN_REF(mDrawOrderTimeLine, val);

}

void SkeletonAnimationModel::SetTriggerTimeline(TriggerTimelineModel* val)
{
	mDuration = Math::Max(mDuration, val->Duration());
	SAFE_ASSIGN_REF(mTriggerTimeline, val);
}

void SkeletonAnimationModel::AddIKTimeline(SkeletonIKModel* ik, IKTimelineModel* timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mIKTimelineDcit.Add(ik, timeline);
	SAFE_RETAIN(timeline);


}

void SkeletonAnimationModel::UpdateTimelineDuration()
{
	FOR_EACH_DICTIONARY_VALUE_TO(mColorTimelineDict,SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mTextureTimelineDict, SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mRotationTimelineDcit, SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mScaleTimelineDcit, SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mTranslateTimelineDcit, SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mVertexTimelineDcit, SetDuration(mDuration));
	FOR_EACH_DICTIONARY_VALUE_TO(mIKTimelineDcit, SetDuration(mDuration));
	

	if (mTriggerTimeline!=nullptr)
	{
		mTriggerTimeline->SetDuration(mDuration);
	}
}

void SkeletonAnimationModel::PreCalculate(float fps)
{
	FOR_EACH_DICTIONARY_VALUE_TO(mColorTimelineDict, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mTextureTimelineDict, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mRotationTimelineDcit, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mScaleTimelineDcit, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mTranslateTimelineDcit, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mVertexTimelineDcit, PreCalculate(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mIKTimelineDcit, PreCalculate(fps));

	if (mTriggerTimeline != nullptr)
	{
		mTriggerTimeline->PreCalculate(fps);
	}
	
}

void SkeletonAnimationModel::RemovePreCalculated()
{
	FOR_EACH_DICTIONARY_VALUE_TO(mColorTimelineDict, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mTextureTimelineDict, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mRotationTimelineDcit, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mScaleTimelineDcit, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mTranslateTimelineDcit, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mVertexTimelineDcit, RemovePreCalculated());
	FOR_EACH_DICTIONARY_VALUE_TO(mIKTimelineDcit, RemovePreCalculated());

	if (mTriggerTimeline != nullptr)
	{
		mTriggerTimeline->RemovePreCalculated();
	}
}



MEDUSA_END;