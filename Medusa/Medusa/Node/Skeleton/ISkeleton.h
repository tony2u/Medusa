// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/Event.h"
#include "Core/Event/EventArg/TriggerEventArg.h"

MEDUSA_BEGIN;

class ISkeleton :public INode
{
	MEDUSA_RTTI(ISkeleton, INode);
public:
	typedef Event<void(SkeletonAnimation* ani, float time, const TriggerEventArg& eventArg)> TriggerEvent;
	typedef TriggerEvent::DelegateType TriggerDelegate;
	TriggerEvent OnEvent;
private:
	typedef Dictionary<HeapString, TriggerEvent, DefaultHashCoder, NoHashCoder, DefaultCompare, NoCompare> TriggerEventDict;
	typedef Dictionary<SkeletonAnimationModel*, TriggerEventDict*> TriggerDict;
public:
	ISkeleton(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);

	ISkeleton(StringRef name, const Share<ISkeletonModel>& model);
	virtual ~ISkeleton();
	virtual bool OnUpdate(float dt, NodeUpdateFlags flag = NodeUpdateFlags::None)override;

	void UpdateBones();
	void ApplyBoneBoundingToSize();
	void ApplySlotBoundingToSize();


	void SetToSetupPose();
	void SetBonesToSetupPose();
	void SetSlotsToSetupBose();
	void SetDrawOrderToSetupPose();

	bool SetAvatarName(const StringRef& avatarName);

	const Share<ISkeletonModel>& Model() const { return mModel; }

	const List<SkeletonBone*>& Bones() const { return mBones; }
	SkeletonBone* FindBone(const StringRef& name)const;

	const List<SkeletonSlot*>& Slots() const { return mSlots; }
	SkeletonSlot* FindSlot(const StringRef& name)const;
	void RemoveAllSlots();
	void AddSlot(SkeletonSlot* slot);
	void RemoveAllSlotsFromParent();
	void AddSlotToParent(SkeletonSlot* slot);

	bool AddNodeToBone(const StringRef& boneName, INode* node);


	List<SkeletonIK*> IKs() const { return mIKs; }
	SkeletonIK* FindIK(const StringRef& name)const;


	SkeletonAvatarModel* AvatarModel() const { return mAvatarModel; }
	void SetAvatarModel(SkeletonAvatarModel* val) { mAvatarModel = val; }

	ISkeletonAttachmentModel* FindAttachment(const StringRef& slotName, const StringRef attachmentName)const;
	ISkeletonAttachmentModel* FindAttachment(const StringRef attachmentName)const;

	//Debug
	bool IsBoneVisible() const { return mIsBoneVisible; }
	void SetBoneVisible(bool val);
	bool IsSlotVisible() const { return mIsSlotVisible; }
	void SetSlotVisible(bool val);

	//animation
	void StopAllAnimations();
	bool StopAnimation(const StringRef& name);
	SkeletonAnimation* PlayAnimation(const StringRef& name, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);
	SkeletonAnimation* BlendToAnimation(const StringRef& name, bool isRepeatForever = false);
	SkeletonAnimation* FindAnimation(const StringRef& name)const;
	bool IsAnimationRunning(const StringRef& name)const;

	size_t AnimationCount()const;
	SkeletonAnimation* PlayAnimationByIndex(size_t index, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);
	SkeletonAnimation* FindAnimationByIndex(size_t index)const;
	intp CurrentAnimationIndex()const;

	SkeletonAnimation* SwitchToAnimation(const StringRef& name, bool isRepeatForever = false);
	SkeletonAnimation* SwitchToAnimationByIndex(size_t index, bool isRepeatForever = false);

	//trigger
	bool RegisterTriggerHandler(const StringRef& animationName, const StringRef& triggerName, TriggerDelegate handler);
	bool FireTrigger(SkeletonAnimation* ani, float time, const TriggerEventArg& eventArg);
public:
	SkeletonAnimation* PlayAnimation(SkeletonAnimationModel* model, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);
	SkeletonAnimation* CreateAnimationByIndex(size_t index, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);
	SkeletonAnimation* CreateAnimation(const StringRef& name, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);
	SkeletonAnimation* CreateAnimation(SkeletonAnimationModel* model, bool isRepeatForever = false, float beforeDelay = 0.f, float repeatDuration = 0.f, float afterDelay = 0.f);

protected:
	Share<ISkeletonModel> mModel = nullptr;
	SkeletonAvatarModel* mAvatarModel = nullptr;

	List<SkeletonBone*> mBones;
	Dictionary<StringRef, SkeletonBone*> mBoneDict;

	List<SkeletonSlot*> mSetupSlots;	//order in setup mode
	List<SkeletonSlot*> mSlots;
	Dictionary<StringRef, SkeletonSlot*> mSlotDict;

	List<SkeletonIK*> mIKs;
	Dictionary<StringRef, SkeletonIK*> mIKDict;

	//trigger
	TriggerDict mTriggers;

	/*
	every ik need to transform bone in forward direction by timeline,then calculate ik(by Mix percent to rotate),
	then use updated bone's rotation to transform bone's final position
	So every ik has a forward bone list meaning forward dependcy,and a backward bone list to update bone,which are next bone's forward list
	so mBoneUpdateList's count should be ik's count+1
	*/
	List<List<SkeletonBone*>, NoCompare> mBoneUpdateList;

	bool mIsBoneVisible = false;
	bool mIsSlotVisible = false;
};

MEDUSA_END;
