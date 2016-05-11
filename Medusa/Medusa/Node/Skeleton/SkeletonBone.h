// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point3.h"
#include "Geometry/Rotation3.h"
#include "Geometry/Scale3.h"
#include "Geometry/Moveable/BoneMoveable.h"

MEDUSA_BEGIN;


class SkeletonBone :public BoneMoveable
{
public:
	SkeletonBone(const SkeletonBoneModel*const model);
	virtual ~SkeletonBone();

	SkeletonBone* Parent() const { return mParent; }
	void SetParent(SkeletonBone* val);

	ISkeleton* Skeleton() const { return mSkeleton; }
	void SetSkeleton(ISkeleton* val) { mSkeleton = val; }

	const SkeletonBoneModel* Model() const { return mModel; }
	void SetToSetupPose(bool isApply=true);

	void AddBone(SkeletonBone* bone);
	void AddSlot(INode* slot);

	void Apply(bool forceUpdateWorldMatrix = false);

	bool IsVisible() const { return mDebugDrawShape != nullptr; }
	void SetIsVisible(bool val);
protected:
	ISkeleton* mSkeleton=nullptr;

	const SkeletonBoneModel*const mModel=nullptr;
	SkeletonBone* mParent=nullptr;

	List<INode*> mSlots;
	List<SkeletonBone*> mBones;

	IShape* mDebugDrawShape=nullptr;
	bool mNeedApplyToSlot=true;

};

MEDUSA_END;
