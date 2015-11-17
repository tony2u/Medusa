// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

class SkeletonIK
{
public:
	SkeletonIK(ISkeleton* animation, const SkeletonIKModel* const model);
	virtual ~SkeletonIK();

	void SetToSetupPose();
	bool IsAffectBone(SkeletonBone* bone)const;

	float Mix() const { return mMix; }
	void SetMix(float val) { mMix = val; }

	bool IsBendPositive() const { return mIsBendPositive; }
	void EnableBendPositive(bool val) { mIsBendPositive = val; }

	const List<SkeletonBone*>& Bones() const { return mBones; }
	void AddBone(SkeletonBone* bone);

	SkeletonBone* TargetBone() const { return mTargetBone; }
	void SetTargetBone(SkeletonBone* val) { mTargetBone = val; }

	void Apply();

protected:
	ISkeleton* mAnimation;
	const SkeletonIKModel* const mModel;
	bool mIsBendPositive;
	
	float mMix;
	
	List<SkeletonBone*> mBones;

	SkeletonBone* mTargetBone;
};

MEDUSA_END;
