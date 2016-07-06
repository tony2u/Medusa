// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonAnimation.h"
#include "Resource/Skeleton/SkeletonAnimationModel.h"
#include "Node/INode.h"
#include "Core/Log/Log.h"
#include "Node/Skeleton/ISkeleton.h"
#include "Resource/Skeleton/SkeletonSlotModel.h"
#include "Resource/Skeleton/SkeletonBoneModel.h"
#include "Resource/Skeleton/SkeletonIKModel.h"


#include "Node/Action/Timeline/ColorTimeline.h"

#include "Node/Skeleton/SkeletonSlot.h"
#include "Node/Skeleton/SkeletonBone.h"
#include "Node/Skeleton/SkeletonIK.h"


#include "SkeletonSlotAttachmentNameTimeline.h"
#include "SkeletonSlotVertexTimeline.h"

#include "Resource/Timeline/ScaleTimelineModel.h"
#include "Resource/Timeline/RotationTimelineModel.h"
#include "Resource/Timeline/TranslateTimelineModel.h"
#include "Resource/Timeline/IKTimelineModel.h"
#include "Resource/Timeline/DrawOrderTimelineModel.h"
#include "Resource/Timeline/TriggerTimelineModel.h"


MEDUSA_BEGIN;


SkeletonAnimation::SkeletonAnimation(SkeletonAnimationModel* model, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	:IAnimation(model->Duration(), isRepeatForever, beforeDelay, repeatDuration, afterDelay, name),
	mModel(model)

{

}

SkeletonAnimation::~SkeletonAnimation()
{
	SAFE_DELETE_COLLECTION(mTimelines);
}


bool SkeletonAnimation::Initialize(void* target)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteRepeatableAction::Initialize(target));

	//create time lines
	ISkeleton* skeleton = (ISkeleton*)target;
	const Dictionary<SkeletonSlotModel*, Share<ColorTimelineModel>>& colorTimelineDict = mModel->ColorTimelineDict();
	for(auto i: colorTimelineDict)
	{
		SkeletonSlotModel* slotModel = i.Key;
		auto& timelineModel = i.Value;

		SkeletonSlot* slot = skeleton->FindSlot(slotModel->Name());
		ColorTimeline* timeline = new ColorTimeline(timelineModel, true);
		timeline->Initialize(slot);
		mTimelines.Add(timeline);
	}

	const Dictionary<SkeletonSlotModel*, Share<StringTimelineModel>>& textureTimelineDict = mModel->TextureTimelineDict();
	for (auto i : textureTimelineDict)
	{
		SkeletonSlotModel* slotModel = i.Key;
		auto timelineModel = i.Value;

		SkeletonSlot* slot = skeleton->FindSlot(slotModel->Name());
		SkeletonSlotAttachmentNameTimeline* timeline = new SkeletonSlotAttachmentNameTimeline(timelineModel, true);
		timeline->Initialize(slot);
		mTimelines.Add(timeline);

	}

	const Dictionary<SkeletonBoneModel*, Share<RotationTimelineModel>>& rotationTimelineDcit = mModel->RotationTimelineDcit();
	for (auto i : rotationTimelineDcit)
	{
		SkeletonBoneModel* boneModel = i.Key;
		auto& timelineModel = i.Value;
		SkeletonBone* bone = skeleton->FindBone(boneModel->Name());

		auto& timeline = mBoneRotaionTimelines.NewAdd();
		timeline.Key = bone;
		timeline.Value = timelineModel;
	}

	const Dictionary<SkeletonBoneModel*, Share<ScaleTimelineModel>>& scaleTimelineDcit = mModel->ScaleTimelineDcit();
	for (auto i : scaleTimelineDcit)
	{
		SkeletonBoneModel* boneModel = i.Key;
		auto& timelineModel = i.Value;
		SkeletonBone* bone = skeleton->FindBone(boneModel->Name());

		auto& timeline = mBoneScaleTimelines.NewAdd();
		timeline.Key = bone;
		timeline.Value = timelineModel;
	}


	const Dictionary<SkeletonBoneModel*, Share<TranslateTimelineModel>>& translateTimelineDcit = mModel->TranslateTimelineDcit();
	for (auto i : translateTimelineDcit)
	{
		SkeletonBoneModel* boneModel = i.Key;
		auto& timelineModel = i.Value;
		SkeletonBone* bone = skeleton->FindBone(boneModel->Name());

		auto& timeline = mBoneTranslateTimelines.NewAdd();
		timeline.Key = bone;
		timeline.Value = timelineModel;
	}

	const Dictionary<KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*>, Share<VertexTimelineModel>>& vertexTimelineDcit = mModel->VertexTimelineDcit();
	for (auto i : vertexTimelineDcit)
	{
		const KeyValuePair<SkeletonSlotModel*, ISkeletonAttachmentModel*>& p = i.Key;
		SkeletonSlotModel* slotModel = p.Key;
		ISkeletonAttachmentModel* attachmentModel = p.Value;

		SkeletonSlot* slot = skeleton->FindSlot(slotModel->Name());

		auto& timelineModel = i.Value;
		SkeletonSlotVertexTimeline* timeline = new SkeletonSlotVertexTimeline(timelineModel, attachmentModel);
		timeline->Initialize(slot);
		mTimelines.Add(timeline);
	}

	const Dictionary<SkeletonIKModel*, Share<IKTimelineModel>>& ikTimelineDcit = mModel->IKTimelineDcit();
	for (auto i : ikTimelineDcit)
	{
		SkeletonIKModel* ikModel = i.Key;
		auto& timelineModel = i.Value;
		SkeletonIK* ik = skeleton->FindIK(ikModel->Name());

		auto& timeline = mIKTimelines.NewAdd();
		timeline.Key = ik;
		timeline.Value = timelineModel;
	}


	return true;
}

bool SkeletonAnimation::Start()
{
	RETURN_FALSE_IF_FALSE(IAnimation::Start());
	for (auto timeline : mTimelines)
	{
		timeline->Start();
	}


	return true;
}

bool SkeletonAnimation::Stop()
{
	RETURN_FALSE_IF_FALSE(IAnimation::Stop());
	for (auto timeline : mTimelines)
	{
		timeline->Stop();
	}

	return true;
}

bool SkeletonAnimation::Reset()
{
	RETURN_FALSE_IF_FALSE(IAnimation::Reset());
	for (auto timeline : mTimelines)
	{
		timeline->Reset();
	}

	return true;
}



bool SkeletonAnimation::OnUpdate(float prevElapsed, float dt, float blend /*= 1.f*/)
{
	//return true;
	ISkeleton* skeleton = (ISkeleton*)this->mTarget;

	for (auto timeline : mTimelines)
	{
		timeline->Update(dt, blend);
	}
	//return true;
	/*
	the value stored in timeline is extactly value on time, we need to multiply delta with blend and then add to origin value,
	delta=current animation value-(cur skeleton value- initial value)
	*/

	float time = Elapsed();
	for(const auto& timeline: mBoneScaleTimelines)
	{
		SkeletonBone* bone = timeline.Key;

		Scale3F val = timeline.Value->GetScale(time);
		val -= bone->Scale() - bone->Model()->Scale();
		val -= Scale3F::One;	//value start from 1, so need to -1 
		val *= blend;
		val += bone->Scale();

		bone->SetScale(val);
	}

	for (const auto& timeline : mBoneRotaionTimelines)
	{
		SkeletonBone* bone = timeline.Key;

		Rotation3F val = timeline.Value->GetRotation(time);
		val -= bone->Rotation() - bone->Model()->Rotation();
		val *= blend;
		val += bone->Rotation();
		bone->SetRotation(val);
	}

	for (const auto& timeline : mBoneTranslateTimelines)
	{
		SkeletonBone* bone = timeline.Key;
		Point3F val = timeline.Value->GetTranslate(time);
		val -= bone->Position() - bone->Model()->Position();
		val *= blend;
		val += bone->Position();

		bone->SetPosition(val);
	}

	/*
	FOR_EACH_COLLECTION(i, mIKTimelines)
	{
	const KeyValuePair<SkeletonIK*, Share<IKTimelineModel>>& timeline = *i;
	timeline.Key->SetMix(timeline.Value->GetMix(Elapsed())*blend);
	timeline.Key->EnableBendPositive(timeline.Value->IsBlendPositive(Elapsed()));

	}
	*/

	auto drawOrderTimelineModel = mModel->DrawOrderTimeLine();
	if (drawOrderTimelineModel != nullptr)
	{
		bool isChanged = drawOrderTimelineModel->IsDrawOrderChanged(prevElapsed, time);
		if (isChanged)
		{
			const List<uint>& orderList = drawOrderTimelineModel->GetDrawOrder(time);
			const List<SkeletonSlot*>& setupSlots = skeleton->Slots();
			skeleton->RemoveAllSlotsFromParent();

			uintp orderCount = orderList.Count();

			uintp i = 0;
			for (; i < orderCount; ++i)
			{
				uint index = orderList[i];
				SkeletonSlot* slot = setupSlots[index];
				skeleton->AddSlotToParent(slot);
			}
			//at some times, setup have more slot than draw order, eg. we add a slot to bone manually.
			uintp setupCount = setupSlots.Count();
			for (; i < setupCount; ++i)
			{
				SkeletonSlot* slot = setupSlots[i];
				skeleton->AddSlotToParent(slot);
			}

		}
	}

	auto triggerTimelineModel = mModel->TriggerTimeline();
	if (triggerTimelineModel != nullptr)
	{
		uintp outBeginIndex;
		uintp outEndIndex;
		if (triggerTimelineModel->TryFire(prevElapsed, time, outBeginIndex, outEndIndex))
		{
			FOR_EACH_UINT_BEGIN_END(i, outBeginIndex, outEndIndex)
			{
				const TriggerEventArg& e = triggerTimelineModel->GetItem(i);
				skeleton->FireTrigger(this, time, e);
			}
		}
	}

	return true;
}



MEDUSA_END;
