// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/IResource.h"
#include "Core/Collection/List.h"
#include "Geometry/Size2.h"

MEDUSA_BEGIN;

class ISkeletonModel :public IResource
{
public:
	ISkeletonModel(const FileIdRef& fileId);
	virtual ~ISkeletonModel(void);

	virtual bool Initialize()override;

	virtual ResourceType Type()const override{ return ResourceType::Skeleton; }
	static ResourceType ClassGetResourceType() { return ResourceType::Skeleton; }

	Size2F GetBoundingSize() const { return mBoundingSize; }
	void SetBoundingSize(const Size2F& val) { mBoundingSize = val; }
	const Share<TextureAtlas>& GetAtlas() const { return mAtlas; }

	const List<SkeletonBoneModel*>& Bones() const { return mBones; }
	List<SkeletonBoneModel*>& MutableBones() { return mBones; }

	void AddBone(SkeletonBoneModel* bone);
	SkeletonBoneModel* FindBone(const StringRef& name)const;

	const List<SkeletonSlotModel*>& Slots() const { return mSlots; }

	void AddSlot(SkeletonSlotModel* slot);
	SkeletonSlotModel* FindSlot(const StringRef& name)const;
	intp FindSlotIndex(const StringRef& name)const;
	intp FindSlotIndex(SkeletonSlotModel* slot)const;



	SkeletonAvatarModel* DefaultAvatar() const { return mDefaultAvatar; }
	void AddAvatar(SkeletonAvatarModel* avatar, bool isDefault = false);
	SkeletonAvatarModel* FindAvatar(const StringRef& name)const;

	const List<SkeletonTriggerModel*>& Triggers() const { return mTriggers; }
	void AddTrigger(SkeletonTriggerModel* val);
	SkeletonTriggerModel* FindTrigger(const StringRef& name)const;

	const List<SkeletonAnimationModel*>& Animations() const { return mAnimations; }
	void AddAnimation(SkeletonAnimationModel* val);
	SkeletonAnimationModel* FindAnimation(const StringRef& name)const;
	size_t AnimationCount()const { return mAnimations.Count(); }
	SkeletonAnimationModel* FindAnimationByIndex(size_t index)const { return mAnimations[index]; }
	intp FindAnimationIndex(const StringRef& name)const;
	intp FindAnimationIndex(SkeletonAnimationModel* val)const;



	const List<SkeletonIKModel*>& IKs() const { return mIKs; }
	void AddIK(SkeletonIKModel* ik);
	SkeletonIKModel* FindIK(const StringRef& name)const;

	ISkeletonAttachmentModel* FindAttachment(const StringRef& slotName, const StringRef attachmentName, const StringRef& avatarName = StringRef::Empty)const;
	ISkeletonAttachmentModel* FindAttachment(const StringRef attachmentName)const;

	void PreCalculate(float fps);
	void RemovePreCalculated();
protected:
	Size2F mBoundingSize;
	Share<TextureAtlas> mAtlas=nullptr;


	List<SkeletonBoneModel*> mBones;
	List<SkeletonSlotModel*> mSlots;
	List<SkeletonAvatarModel*> mAvatars;
	List<SkeletonTriggerModel*> mTriggers;
	List<SkeletonAnimationModel*> mAnimations;
	List<SkeletonIKModel*> mIKs;

	SkeletonAvatarModel* mDefaultAvatar=nullptr;
	Dictionary<StringRef, SkeletonBoneModel*> mBoneDict;
	Dictionary<StringRef, SkeletonSlotModel*> mSlotDict;
	Dictionary<StringRef, SkeletonAvatarModel*> mAvatarDict;
	Dictionary<StringRef, SkeletonTriggerModel*> mTriggerDict;
	Dictionary<StringRef, SkeletonAnimationModel*> mAnimationDict;
	Dictionary<StringRef, SkeletonIKModel*> mIKDict;




};

MEDUSA_END;
