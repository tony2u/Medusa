// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
#include "Geometry/Color4.h"
#include "Geometry/Moveable/BoneMoveable.h"

MEDUSA_BEGIN;




class SkeletonBoneModel :public BoneMoveable
{
public:
	SkeletonBoneModel(const StringRef& name, const StringRef& parentName);
	~SkeletonBoneModel();

	StringRef Name() const { return mName; }
	StringRef ParentName() const { return mParentName; }


	SkeletonBoneModel* Parent() const { return mParent; }
	void SetParent(SkeletonBoneModel* val);

	uint Length() const { return mLength; }
	void SetLength(uint val) { mLength = val; }

	Color4F Color() const { return mColor; }
	void SetColor(Color4F val) { mColor = val; }

	void AddChildBone(SkeletonBoneModel* bone);
	void AddSlot(SkeletonSlotModel* slot);
protected:
	SkeletonBoneModel* mParent=nullptr;
	List<SkeletonBoneModel*> mBones;
	List<SkeletonSlotModel*> mSlots;

	HeapString mName;
	HeapString mParentName;

	uint mLength;		//only used to debug draw bone
	Color4F mColor;		//only used to debug draw bone
	
	Point3F mPosition;
	Rotation3F mRotation;
	Scale3F mScale;
};

MEDUSA_END;
