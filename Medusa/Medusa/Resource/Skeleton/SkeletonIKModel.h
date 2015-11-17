// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/HeapString.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class SkeletonIKModel
{
public:
	SkeletonIKModel(const StringRef& name);
	~SkeletonIKModel();

	StringRef Name() const { return mName; }

	bool IsBendPositive() const { return mIsBendPositive; }
	void EnableBendPositive(bool val) { mIsBendPositive = val; }

	float Mix() const { return mMix; }
	void SetMix(float val) { mMix = val; }

	const List<SkeletonBoneModel*>& Bones() const { return mBones; }
	void AddBone(SkeletonBoneModel* bone);

	SkeletonBoneModel* TargetBone() const { return mTargetBone; }
	void SetTargetBone(SkeletonBoneModel* val) { mTargetBone = val; }

protected:
	HeapString mName;

	List<SkeletonBoneModel*> mBones;
	SkeletonBoneModel* mTargetBone=nullptr;
	
	bool mIsBendPositive=true;
	float mMix=1.f;


};

MEDUSA_END;
