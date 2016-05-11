// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ISkeleton.h"
#include "Core/Log/Log.h"
#include "Resource/Skeleton/ISkeletonModel.h"
#include "Resource/Skeleton/SkeletonBoneModel.h"
#include "Resource/Skeleton/SkeletonSlotModel.h"
#include "Resource/Skeleton/SkeletonIKModel.h"
#include "Resource/Skeleton/SkeletonAvatarModel.h"


#include "SkeletonBone.h"
#include "SkeletonSlot.h"
#include "SkeletonIK.h"
#include "Node/Action/Animation/SkeletonAnimation.h"
#include "Resource/Skeleton/SkeletonAnimationModel.h"
#include "Core/Action/DelayAction.h"
#include "Core/Action/Composite/SequenceAction.h"
#include "Core/Action/Composite/SpeedAction.h"
#include "Core/Action/Composite/CountDownAction.h"

#include "Geometry/Range.h"


MEDUSA_BEGIN;

ISkeleton::ISkeleton(StringRef name, ISkeletonModel* model)
	:INode(name), mModel(model),
	mAvatarModel(nullptr),
	mIsBoneVisible(false),
	mIsSlotVisible(true)
{
	Start();
	SAFE_RETAIN(mModel);
	SetSize(model->GetBoundingSize());

	SetAvatarModel(mModel->DefaultAvatar());

	//create bones
	const List<SkeletonBoneModel*>& bones = mModel->Bones();
	FOR_EACH_COLLECTION(i, bones)
	{
		SkeletonBoneModel* boneModel = *i;
		SkeletonBone* bone = new SkeletonBone(boneModel);
		bone->SetSkeleton(this);
		mBones.Add(bone);
		mBoneDict.Add(boneModel->Name(), bone);
	}

	FOR_EACH_COLLECTION(i, mBones)
	{
		SkeletonBone* bone = *i;
		SkeletonBoneModel* parentBoneModel = bone->Model()->Parent();
		if (parentBoneModel != nullptr)
		{
			SkeletonBone* parentBone = FindBone(parentBoneModel->Name());
			parentBone->AddBone(bone);
		}
	}

	//create slots

	const List<SkeletonSlotModel*>& slots = mModel->Slots();
	uintp slotCount = slots.Count();
	FOR_EACH_SIZE(i, slotCount)
	{
		SkeletonSlotModel* slotModel = slots[i];
		SkeletonBone* bone = FindBone(slotModel->ParentBone()->Name());
		SkeletonSlot* slot = new SkeletonSlot(this, slotModel);
		slot->EnableManaged();
		//slot->SetLogicZ(i);
		bone->AddSlot(slot);

		mSlots.Add(slot);
		mSlotDict.Add(slotModel->Name(), slot);
		AddChild(slot);
	}


	//ik
	const List<SkeletonIKModel*> iks = mModel->IKs();
	FOR_EACH_COLLECTION(i, iks)
	{
		SkeletonIKModel* ikModel = *i;
		SkeletonIK* ik = new SkeletonIK(this, ikModel);
		mIKs.Add(ik);
		mIKDict.Add(ikModel->Name(), ik);
	}

	//bone update list
	mBoneUpdateList.ForceReserveCount(iks.Count() + 1);


	size_t boneCount = mBones.Count();
	size_t ikCount = iks.Count();
	FOR_EACH_SIZE(i, boneCount)
	{
		SkeletonBone* bone = mBones[i];
		SkeletonBone* currentBone = bone;
		bool isFound = false;
		do
		{
			FOR_EACH_SIZE(j, ikCount)
			{
				SkeletonIK* ik = mIKs[j];
				if (ik->IsAffectBone(currentBone))
				{
					mBoneUpdateList[j].Add(bone);//prev 
					mBoneUpdateList[j + 1].Add(bone);//next
					isFound = true;
					break;
				}
			}

			currentBone = currentBone->Parent();
		} while (currentBone != nullptr&&!isFound);

		if (!isFound)
		{
			mBoneUpdateList[0].Add(bone);//irrelevant bones,place them to prev
		}
	}

	UpdateBones();
}


ISkeleton::~ISkeleton()
{
	SAFE_DELETE_COLLECTION(mBones);
	SAFE_DELETE_COLLECTION(mIKs);

	SAFE_RELEASE(mModel);

	SAFE_DELETE_DICTIONARY_VALUE(mTriggers);
}

bool ISkeleton::OnUpdate(float dt, NodeUpdateFlags flag /*= NodeUpdateFlags::None*/)
{
	//return true;
	
	//run animation
	//return true;
	//update transform
	UpdateBones();

	return true;
}

void ISkeleton::UpdateBones()
{
	size_t updateCount = mBoneUpdateList.Count();
	size_t ikCount = mIKs.Count();
	FOR_EACH_SIZE(i, updateCount)
	{
		List<SkeletonBone*>& bones = mBoneUpdateList[i];
		FOR_EACH_COLLECTION(j, bones)
		{
			SkeletonBone* bone = *j;
			bone->Apply();
		}

		if (i < ikCount)
		{
			SkeletonIK* ik = mIKs[i];
			ik->Apply();
		}
	}
}


void ISkeleton::ApplyBoneBoundingToSize()
{
	RangeF rangeX;
	RangeF rangeY;
	FOR_EACH_COLLECTION(i, mBones)
	{
		SkeletonBone* bone = *i;
		const BoundingBox& boundingBox = bone->WorldBoundingBox();
		rangeX.Expand(boundingBox.Left());
		rangeX.Expand(boundingBox.Right());
		rangeY.Expand(boundingBox.Bottom());
		rangeY.Expand(boundingBox.Top());
	}

	mSize.Width = rangeX.Length();
	mSize.Height = rangeY.Length();
}


void ISkeleton::ApplySlotBoundingToSize()
{
	RangeF rangeX;
	RangeF rangeY;
	FOR_EACH_COLLECTION(i, mSlots)
	{
		INode* slot = *i;
		const BoundingBox& boundingBox = slot->GetBoundingBox();
		rangeX.Expand(boundingBox.Left());
		rangeX.Expand(boundingBox.Right());
		rangeY.Expand(boundingBox.Bottom());
		rangeY.Expand(boundingBox.Top());
	}

	mSize.Width = rangeX.Length();
	mSize.Height = rangeY.Length();
}

void ISkeleton::SetToSetupPose()
{
	SetBonesToSetupPose();
	SetSlotsToSetupBose();
	SetDrawOrderToSetupPose();
}

void ISkeleton::SetBonesToSetupPose()
{
	FOR_EACH_COLLECTION(i, mBones)
	{
		SkeletonBone* bone = *i;
		bone->SetToSetupPose(false);
	}

	UpdateBones();
}

void ISkeleton::SetSlotsToSetupBose()
{
	FOR_EACH_COLLECTION(i, mSlots)
	{
		SkeletonSlot* slot = *i;
		slot->SetToSetupPose();
	}
}

void ISkeleton::SetDrawOrderToSetupPose()
{
	bool isInSetupOrder = true;
	uintp slotCount = mSlots.Count();
	uintp managedCount = mManagedNodes.Count();
	for (uint i = 0, j = 0; i < slotCount&&j < managedCount;)
	{
		SkeletonSlot* slot = mSlots[i];
		INode* node = this->mManagedNodes[j];
		if (slot == node)	//ptr equals
		{
			++i;
			++j;
		}
		else
		{
			if (node->IsA<SkeletonSlot>())
			{
				isInSetupOrder = false;
				break;
			}
			else
			{
				++j;
			}
		}
	}


	if (isInSetupOrder)
	{
		//no need to change if already in setup draw order
		//return;
	}

	RemoveAllSlotsFromParent();
	FOR_EACH_COLLECTION(i, mSlots)
	{
		SkeletonSlot* slot = *i;
		AddSlotToParent(slot);
	}
}

bool ISkeleton::SetAvatarName(const StringRef& avatarName)
{
	mAvatarModel = mModel->FindAvatar(avatarName);
	if (mAvatarModel == nullptr)
	{
		Log::AssertFailedFormat("Cannot find avatar:{}", avatarName.c_str());
		mAvatarModel = mModel->DefaultAvatar();
		return false;
	}

	return true;
}

SkeletonBone* ISkeleton::FindBone(const StringRef& name) const
{
	return mBoneDict.GetOptional(name, nullptr);
}

SkeletonSlot* ISkeleton::FindSlot(const StringRef& name) const
{
	return mSlotDict.GetOptional(name, nullptr);
}

SkeletonIK* ISkeleton::FindIK(const StringRef& name) const
{
	return mIKDict.GetOptional(name, nullptr);
}

void ISkeleton::SetBoneVisible(bool val)
{
	RETURN_IF_EQUAL(mIsBoneVisible, val);
	mIsBoneVisible = val;

	FOR_EACH_COLLECTION(i, mBones)
	{
		SkeletonBone* bone = *i;
		bone->SetIsVisible(val);
	}
}

void ISkeleton::SetSlotVisible(bool val)
{
	RETURN_IF_EQUAL(mIsSlotVisible, val);
	mIsSlotVisible = val;

	FOR_EACH_COLLECTION(i, mSlots)
	{
		SkeletonSlot* slot = *i;
		slot->SetVisible(val);
	}
}


void ISkeleton::RemoveAllSlots()
{
	RemoveAllSlotsFromParent();
	mSlots.Clear();
	mSlotDict.Clear();
}

void ISkeleton::RemoveAllSlotsFromParent()
{
	FOR_EACH_COLLECTION(i, mSlots)
	{
		SkeletonSlot* slot = *i;
		RemoveChild(slot);
	}
}

void ISkeleton::AddSlotToParent(SkeletonSlot* slot)
{
	slot->EnableManaged();
	AddChild(slot);
}


void ISkeleton::AddSlot(SkeletonSlot* slot)
{
	//Log::AssertFormat(!mSlots.Contains(slot), "Duplicate add slot:{}", slot->Name().c_str());
	mSlots.Add(slot);
	mSlotDict.Add(slot->Name(), slot);
}

SkeletonAnimation* ISkeleton::PlayAnimationByIndex(size_t index, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	SkeletonAnimation* action = CreateAnimationByIndex(index, isRepeatForever, beforeDelay, repeatDuration, afterDelay);
	return (SkeletonAnimation*)RunAction(action);
}

SkeletonAnimation* ISkeleton::PlayAnimation(const StringRef& name, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	SkeletonAnimation* action = CreateAnimation(name, isRepeatForever, beforeDelay, repeatDuration, afterDelay);
	return (SkeletonAnimation*)RunAction(action);
}

SkeletonAnimation* ISkeleton::PlayAnimation(SkeletonAnimationModel* model, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	SkeletonAnimation* action = CreateAnimation(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay);
	return (SkeletonAnimation*)RunAction(action);
}


SkeletonAnimation* ISkeleton::CreateAnimationByIndex(size_t index, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	SkeletonAnimationModel* model = mModel->FindAnimationByIndex(index);
	SkeletonAnimation* ani = FindAnimation(model->Name());
	RETURN_SELF_IF_NOT_NULL(ani);
	return CreateAnimation(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay);
}

SkeletonAnimation* ISkeleton::CreateAnimation(const StringRef& name, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	SkeletonAnimation* ani = FindAnimation(name);
	RETURN_SELF_IF_NOT_NULL(ani);
	SkeletonAnimationModel* model = mModel->FindAnimation(name);
	if (model==nullptr)
	{
		Log::AssertFailedFormat("Cannot find animation name:{}", name.c_str());
		return nullptr;
	}
	return CreateAnimation(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay);
}

SkeletonAnimation* ISkeleton::CreateAnimation(SkeletonAnimationModel* model, bool isRepeatForever /*= false*/, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/)
{
	return new SkeletonAnimation(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, model->Name());
}

SkeletonAnimation* ISkeleton::FindAnimation(const StringRef& name) const
{
	return (SkeletonAnimation*)FindActionByName(name);
}


SkeletonAnimation* ISkeleton::FindAnimationByIndex(size_t index) const
{
	SkeletonAnimationModel* model = mModel->FindAnimationByIndex(index);
	return (SkeletonAnimation*)FindActionByName(model->Name());

}

bool ISkeleton::IsAnimationRunning(const StringRef& name) const
{
	return this->IsActionRunningByName(name);
}


SkeletonAnimation* ISkeleton::BlendToAnimation(const StringRef& name, bool isRepeatForever /*= false*/)
{
	return nullptr;
}

bool ISkeleton::StopAnimation(const StringRef& name)
{
	return StopActionByName(name);
}

void ISkeleton::StopAllAnimations()
{
	const List<SkeletonAnimationModel*>& animations = mModel->Animations();
	FOR_EACH_COLLECTION(i, animations)
	{
		SkeletonAnimationModel* ani = *i;
		StopActionByName(ani->Name());
	}
	SetToSetupPose();
}

size_t ISkeleton::AnimationCount() const
{
	return mModel->AnimationCount();
}

intp ISkeleton::CurrentAnimationIndex() const
{
	const List<SkeletonAnimationModel*>& animations = mModel->Animations();
	FOR_EACH_COLLECTION(i, animations)
	{
		SkeletonAnimationModel* model = *i;
		SkeletonAnimation* ani = FindAnimation(model->Name());
		if (ani != nullptr)
		{
			return mModel->FindAnimationIndex(model);
		}
	}

	return -1;
}

SkeletonAnimation* ISkeleton::SwitchToAnimation(const StringRef& name, bool isRepeatForever /*= false*/)
{
	StopAllAnimations();
	return PlayAnimation(name, isRepeatForever);
}

SkeletonAnimation* ISkeleton::SwitchToAnimationByIndex(size_t index, bool isRepeatForever /*= false*/)
{
	StopAllAnimations();
	return PlayAnimationByIndex(index, isRepeatForever);
}

bool ISkeleton::AddNodeToBone(const StringRef& boneName, INode* node)
{
	SkeletonBone* bone = FindBone(boneName);
	RETURN_FALSE_IF_NULL(bone);
	bone->AddSlot(node);
	AddChild(node);
	return true;
}

ISkeletonAttachmentModel* ISkeleton::FindAttachment(const StringRef& slotName, const StringRef attachmentName) const
{
	SkeletonSlotModel* slotModel = mModel->FindSlot(slotName);
	return mAvatarModel->FindAttachment(slotModel, attachmentName);
}

ISkeletonAttachmentModel* ISkeleton::FindAttachment(const StringRef attachmentName) const
{
	return mAvatarModel->FindAttachment(attachmentName);

}

bool ISkeleton::RegisterTriggerHandler(const StringRef& animationName, const StringRef& triggerName, TriggerDelegate handler)
{
	SkeletonAnimationModel* aniModel = mModel->FindAnimation(animationName);
	RETURN_FALSE_IF_NULL(aniModel);
	TriggerEventDict* eventDict = mTriggers.GetOptional(aniModel, nullptr);
	if (eventDict == nullptr)
	{
		eventDict = new TriggerEventDict();
		mTriggers.Add(aniModel, eventDict);
	}

	TriggerEvent* events= eventDict->TryGetByOtherKey(triggerName, triggerName.HashCode());
	if (events==nullptr)
	{
		TriggerEvent& newEvents = eventDict->NewAdd(triggerName);
		events = &newEvents;
	}

	events->Add(handler);

	return true;
}

bool ISkeleton::FireTrigger(SkeletonAnimation* ani, float time, const TriggerEventArg& eventArg)
{
	SkeletonAnimationModel* aniModel = mModel->FindAnimation(ani->Name());
	RETURN_FALSE_IF_NULL(aniModel);
	TriggerEventDict* eventDict = mTriggers.GetOptional(aniModel, nullptr);
	RETURN_FALSE_IF_NULL(eventDict);
	StringRef triggerName= eventArg.Name();
	TriggerEvent* events = eventDict->TryGetByOtherKey(triggerName, triggerName.HashCode());
	RETURN_FALSE_IF_NULL(events);
	events->Invoke(ani, time, eventArg);
	return true;
}



MEDUSA_IMPLEMENT_RTTI(ISkeleton, INode);
MEDUSA_END;
