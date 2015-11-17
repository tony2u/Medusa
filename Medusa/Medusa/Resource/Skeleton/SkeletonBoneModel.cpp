// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonBoneModel.h"
#include "SkeletonSlotModel.h"


MEDUSA_BEGIN;


SkeletonBoneModel::SkeletonBoneModel(const StringRef& name, const StringRef& parentName)
	:mName(name),
	mParentName(parentName),
	mColor(Color4F::White)
{
}


SkeletonBoneModel::~SkeletonBoneModel(void)
{
	
}


void SkeletonBoneModel::AddChildBone(SkeletonBoneModel* bone)
{
	bone->SetParent(this);
	mBones.Add(bone);
}

void SkeletonBoneModel::AddSlot(SkeletonSlotModel* slot)
{
	mSlots.Add(slot);
	slot->SetParentBone(this);
}

void SkeletonBoneModel::SetParent(SkeletonBoneModel* val)
{
	mParent = val;
	SetParentMoveable(mParent);
}



MEDUSA_END;