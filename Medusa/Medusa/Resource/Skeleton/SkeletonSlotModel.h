// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/HeapString.h"
#include "Core/Geometry/Color4.h"

MEDUSA_BEGIN;

class SkeletonSlotModel
{
public:
	SkeletonSlotModel(const StringRef& name);
	~SkeletonSlotModel();

	StringRef Name() const { return mName; }

	StringRef AttachmentName() const { return mAttachmentName; }
	void SetAttachmentName(StringRef val) { mAttachmentName = val; }

	const Color4F& Color() const { return mColor; }
	void SetColor(const Color4F& val) { mColor = val; }

	bool IsAdditiveBlending() const { return mIsAdditiveBlending; }
	void EnableAdditiveBlending(bool val) { mIsAdditiveBlending = val; }

	SkeletonBoneModel* ParentBone() const { return mParentBone; }
	void SetParentBone(SkeletonBoneModel* val) { mParentBone = val; }
protected:
	SkeletonBoneModel* mParentBone=nullptr;
	
	HeapString mName;
	HeapString mAttachmentName;

	Color4F mColor;

	bool mIsAdditiveBlending=true;

};

MEDUSA_END;
