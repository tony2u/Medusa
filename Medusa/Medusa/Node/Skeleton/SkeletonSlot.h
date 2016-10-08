// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Color4.h"
#include "Node/INode.h"


MEDUSA_BEGIN;

class SkeletonSlot :public INode
{
	MEDUSA_NODE(SkeletonSlot,INode);
public:
	SkeletonSlot(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);

	SkeletonSlot(ISkeleton* skeleton, SkeletonSlotModel* model);
	virtual ~SkeletonSlot();

	ISkeletonAttachmentModel* Attachment() const { return mAttachment; }
	void SetAttachment(ISkeletonAttachmentModel* val);
	void SetAttachment(const StringRef& attachmentName);
	void SetAttachmentFromModel();

	ISkeleton* Skeleton() const { return mSkeleton; }
	void SetSkeleton(ISkeleton* val) { mSkeleton = val; }

	void SetToSetupPose();

	virtual bool HitTestLocal(const Point2F& localPos)const override;
	Rect2F CalculateBoundingBox();
	Rect2F GetModelBoundingBox()const;


protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags)override;
protected:
	ISkeleton* mSkeleton = nullptr;
	SkeletonSlotModel* mModel=nullptr;
	ISkeletonAttachmentModel* mAttachment=nullptr;


};
MEDUSA_ENABLE_STATIC_CONSTRUCTOR(SkeletonSlot);

MEDUSA_END;
