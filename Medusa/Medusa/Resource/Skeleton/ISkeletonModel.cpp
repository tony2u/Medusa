// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ISkeletonModel.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "SkeletonBoneModel.h"
#include "SkeletonAvatarModel.h"
#include "SkeletonTriggerModel.h"
#include "SkeletonAnimationModel.h"
#include "Core/Log/Log.h"
#include "SkeletonSlotModel.h"
#include "SkeletonIKModel.h"


MEDUSA_BEGIN;


ISkeletonModel::ISkeletonModel(const FileIdRef& fileId)
	:IResource(fileId),
	mBoundingSize(Size2F::Zero)
{

}


ISkeletonModel::~ISkeletonModel(void)
{
	SAFE_RELEASE(mAtlas);

	SAFE_DELETE_COLLECTION(mBones);
	SAFE_DELETE_COLLECTION(mAnimations);
	SAFE_DELETE_COLLECTION(mAvatars);
	SAFE_DELETE_COLLECTION(mTriggers);

	SAFE_DELETE_COLLECTION(mSlots);

	SAFE_DELETE_COLLECTION(mIKs);


	mBoneDict.Clear();
	mSlotDict.Clear();
	mAvatarDict.Clear();
}


bool ISkeletonModel::Initialize()
{
	//setup bone parent relationship
	FOR_EACH_COLLECTION(i, mBones)
	{
		SkeletonBoneModel* bone = *i;
		StringRef parentName = bone->ParentName();
		if (!parentName.IsEmpty())
		{
			SkeletonBoneModel* parentBone = FindBone(parentName);
			if (parentBone == nullptr)
			{
				Log::AssertFailedFormat("Cannot find bone:{} 's parent bone:{}", bone->Name().c_str(), parentName.c_str());
				return false;
			}
			parentBone->AddChildBone(bone);
		}
	}
	//calculate bounding box

	return true;
}

void ISkeletonModel::AddBone(SkeletonBoneModel* bone)
{
	mBones.Add(bone);
	mBoneDict.Add(bone->Name(), bone);
}

SkeletonBoneModel* ISkeletonModel::FindBone(const StringRef& name) const
{
	return mBoneDict.GetOptional(name, nullptr);
}

void ISkeletonModel::AddSlot(SkeletonSlotModel* slot)
{
	mSlots.Add(slot);
	mSlotDict.Add(slot->Name(), slot);
}

SkeletonSlotModel* ISkeletonModel::FindSlot(const StringRef& name) const
{
	return mSlotDict.GetOptional(name, nullptr);
}

void ISkeletonModel::AddAvatar(SkeletonAvatarModel* avatar, bool isDefault /*= false*/)
{
	mAvatars.Add(avatar);
	mAvatarDict.Add(avatar->Name(), avatar);
	if (isDefault || mDefaultAvatar == nullptr)
	{
		mDefaultAvatar = avatar;
	}
}

SkeletonAvatarModel* ISkeletonModel::FindAvatar(const StringRef& name) const
{
	return mAvatarDict.GetOptional(name, nullptr);
}

void ISkeletonModel::AddTrigger(SkeletonTriggerModel* val)
{
	mTriggers.Add(val);
	mTriggerDict.Add(val->Name(), val);
}

SkeletonTriggerModel* ISkeletonModel::FindTrigger(const StringRef& name) const
{
	return mTriggerDict.GetOptional(name, nullptr);
}

void ISkeletonModel::AddAnimation(SkeletonAnimationModel* val)
{
	mAnimations.Add(val);
	mAnimationDict.Add(val->Name(), val);
	val->SetSkeletonModel(this);
}

SkeletonAnimationModel* ISkeletonModel::FindAnimation(const StringRef& name) const
{
	return mAnimationDict.GetOptional(name, nullptr);
}

intp ISkeletonModel::FindSlotIndex(const StringRef& name) const
{
	RETURN_OBJECT_IF_EMPTY(mSlots, -1);

	FOR_EACH_SIZE(i, mSlots.Count() - 1)
	{
		if (mSlots[i]->Name() == name)
		{
			return i;
		}
	}

	return -1;
}

intp ISkeletonModel::FindSlotIndex(SkeletonSlotModel* slot) const
{
	return mSlots.IndexOf(slot);
}

void ISkeletonModel::AddIK(SkeletonIKModel* ik)
{
	mIKs.Add(ik);
	mIKDict.Add(ik->Name(), ik);
}

SkeletonIKModel* ISkeletonModel::FindIK(const StringRef& name) const
{
	return mIKDict.GetOptional(name, nullptr);
}

intp ISkeletonModel::FindAnimationIndex(const StringRef& name) const
{
	SkeletonAnimationModel* model = FindAnimation(name);
	RETURN_OBJECT_IF_NULL(model, -1);
	return mAnimations.IndexOf(model);
}

intp ISkeletonModel::FindAnimationIndex(SkeletonAnimationModel* val) const
{
	return mAnimations.IndexOf(val);
}

ISkeletonAttachmentModel* ISkeletonModel::FindAttachment(const StringRef& slotName, const StringRef attachmentName, const StringRef& avatarName /*= StringRef::Empty*/) const
{
	SkeletonAvatarModel* avatar = mDefaultAvatar;
	if (!avatarName.IsEmpty())
	{
		avatar = FindAvatar(avatarName);
	}
	RETURN_NULL_IF_NULL(avatar);
	SkeletonSlotModel* slotModel = FindSlot(slotName);
	RETURN_NULL_IF_NULL(slotModel);

	return avatar->FindAttachment(slotModel, attachmentName);
}

ISkeletonAttachmentModel* ISkeletonModel::FindAttachment(const StringRef attachmentName) const
{
	return mDefaultAvatar->FindAttachment(attachmentName);
}

void ISkeletonModel::PreCalculate(float fps)
{
	FOR_EACH_ITEM_TO(mAnimations, PreCalculate(fps));
}

void ISkeletonModel::RemovePreCalculated()
{
	FOR_EACH_ITEM_TO(mAnimations, RemovePreCalculated());
}




MEDUSA_END;