// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonAnimationModel.h"


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
	mColorTimelineDict.Clear();
	mTextureTimelineDict.Clear();
	mRotationTimelineDcit.Clear();
	mScaleTimelineDcit.Clear();
	mTranslateTimelineDcit.Clear();
	mVertexTimelineDcit.Clear();
	mIKTimelineDcit.Clear();

}


bool SkeletonAnimationModel::Initialize()
{
	//fix all timeline model's duration
	UpdateTimelineDuration();
	return true;
}

void SkeletonAnimationModel::AddColorTimeline(SkeletonSlotModel* slot, const Share<ColorTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mColorTimelineDict.Add(slot, timeline);
}

void SkeletonAnimationModel::AddTextureTimeline(SkeletonSlotModel* slot, const Share<StringTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mTextureTimelineDict.Add(slot, timeline);

}

void SkeletonAnimationModel::AddRotationTimeline(SkeletonBoneModel* bone, const Share<RotationTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mRotationTimelineDcit.Add(bone, timeline);
}

void SkeletonAnimationModel::AddScaleTimeline(SkeletonBoneModel* bone, const Share<ScaleTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mScaleTimelineDcit.Add(bone, timeline);
}

void SkeletonAnimationModel::AddTranslateTimeline(SkeletonBoneModel* bone, const Share<TranslateTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mTranslateTimelineDcit.Add(bone, timeline);

}


void SkeletonAnimationModel::AddVertexTimeline(KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*> slotAttachment, const Share<VertexTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mVertexTimelineDcit.Add(slotAttachment, timeline);

}

void SkeletonAnimationModel::SetDrawOrderTimeLine(const Share<DrawOrderTimelineModel>& val)
{
	mDuration = Math::Max(mDuration, val->Duration());
	mDrawOrderTimeLine = val;

}

void SkeletonAnimationModel::SetTriggerTimeline(const Share<TriggerTimelineModel>& val)
{
	mDuration = Math::Max(mDuration, val->Duration());
	mTriggerTimeline = val;
}

void SkeletonAnimationModel::AddIKTimeline(SkeletonIKModel* ik, const Share<IKTimelineModel>& timeline)
{
	mDuration = Math::Max(mDuration, timeline->Duration());
	mIKTimelineDcit.Add(ik, timeline);

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

void SkeletonAnimationModel::Precompute(float fps)
{
	FOR_EACH_DICTIONARY_VALUE_TO(mColorTimelineDict, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mTextureTimelineDict, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mRotationTimelineDcit, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mScaleTimelineDcit, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mTranslateTimelineDcit, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mVertexTimelineDcit, Precompute(fps));
	FOR_EACH_DICTIONARY_VALUE_TO(mIKTimelineDcit, Precompute(fps));

	if (mTriggerTimeline != nullptr)
	{
		mTriggerTimeline->Precompute(fps);
	}
	
}

void SkeletonAnimationModel::RemovePrecomputed()
{
	FOR_EACH_DICTIONARY_VALUE_TO(mColorTimelineDict, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mTextureTimelineDict, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mRotationTimelineDcit, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mScaleTimelineDcit, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mTranslateTimelineDcit, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mVertexTimelineDcit, RemovePrecomputed());
	FOR_EACH_DICTIONARY_VALUE_TO(mIKTimelineDcit, RemovePrecomputed());

	if (mTriggerTimeline != nullptr)
	{
		mTriggerTimeline->RemovePrecomputed();
	}
}



MEDUSA_END;