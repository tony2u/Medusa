// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonSlot.h"
#include "Resource/Skeleton/SkeletonSlotModel.h"
#include "Resource/Skeleton/SkeletonAvatarModel.h"
#include "Resource/Skeleton/Attachment/ISkeletonAttachmentModel.h"
#include "Resource/Skeleton/Attachment/SkeletonBoundingBoxAttachmentModel.h"

#include "Core/Log/Log.h"
#include "ISkeleton.h"

MEDUSA_BEGIN;

SkeletonSlot::SkeletonSlot(ISkeleton* skeleton, SkeletonSlotModel* model)
	:INode(model->Name()), mSkeleton(skeleton),mModel(model), mAttachment(nullptr)
{
	SetToSetupPose();
	Stop();
}


SkeletonSlot::~SkeletonSlot()
{

}

void SkeletonSlot::SetToSetupPose()
{
	SetColor(mModel->Color());
	StringRef attachmentName = mModel->AttachmentName();
	SetAttachment(attachmentName);

}

void SkeletonSlot::SetAttachment(ISkeletonAttachmentModel* val)
{
	RETURN_IF_EQUAL(mAttachment, val);
	mAttachment = val;
	if (mAttachment != nullptr)
	{
		SetMesh(mAttachment->GetMesh());
	}
	else
	{
		SetMesh(nullptr);
	}
}

void SkeletonSlot::SetAttachment(const StringRef& attachmentName)
{
	if (attachmentName.IsEmpty())
	{
		SetAttachment(nullptr);
		return;
	}

	if (mAttachment != nullptr&&mAttachment->Name() == attachmentName)
	{
		return;
	}

	ISkeletonAttachmentModel* attachment = mSkeleton->AvatarModel()->FindAttachment(mModel, attachmentName);
	if (attachment == nullptr)
	{
		Log::AssertFailedFormat("Cannot find slot attachment:{}", attachmentName.c_str());
		return;
	}
	SetAttachment(attachment);
}

bool SkeletonSlot::HitTestLocal(const Point2F& localPos) const
{
	if (mAttachment != nullptr&&mAttachment->Type() == SkeletonAttachmentType::BoundingBox)
	{
		SkeletonBoundingBoxAttachmentModel* boundingBox = (SkeletonBoundingBoxAttachmentModel*)mAttachment;
		return boundingBox->HitTestLocal(localPos);
	}
	return INode::HitTestLocal(localPos);
}


void SkeletonSlot::OnMoveableDirty(MoveableChangedFlags changedFlags)
{
	INode::OnMoveableDirty(changedFlags);
	//update bounding box 
}

Rect2F SkeletonSlot::CalculateBoundingBox()
{
	if (mAttachment != nullptr&&mAttachment->Type() == SkeletonAttachmentType::BoundingBox)
	{
		SkeletonBoundingBoxAttachmentModel* boundingBox = (SkeletonBoundingBoxAttachmentModel*)mAttachment;


		const List<Point2F>& vertices = boundingBox->Polygon().Vertices();

		RangeF rangeX;
		RangeF rangeY;
		FOR_EACH_COLLECTION(i, vertices)
		{
			Point2F pos = *i;
			pos = TransformToWorld(pos);
			rangeX.Expand(pos.X);
			rangeY.Expand(pos.Y);
		}

		return Rect2F(rangeX.Min, rangeY.Min, rangeX.Length(), rangeY.Length());
	}
	return Rect2F::Zero;
}

Rect2F SkeletonSlot::GetModelBoundingBox() const
{
	//no rotation or scale on this slot
	if (mAttachment != nullptr&&mAttachment->Type() == SkeletonAttachmentType::BoundingBox)
	{
		SkeletonBoundingBoxAttachmentModel* boundingBox = (SkeletonBoundingBoxAttachmentModel*)mAttachment;
		return boundingBox->Polygon().BoundingBox();
	}
	return Rect2F::Zero;
}

void SkeletonSlot::SetAttachmentFromModel()
{
	SetAttachment(mModel->AttachmentName());
}

MEDUSA_IMPLEMENT_RTTI(SkeletonSlot, INode);


MEDUSA_END;
