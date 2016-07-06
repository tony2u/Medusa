// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonBone.h"
#include "Resource/Skeleton/SkeletonBoneModel.h"
#include "Core/Log/Log.h"
#include "SkeletonSlot.h"
#include "Node/NodeFactory.h"
#include "ISkeleton.h"
#include "Node/Shape/IShape.h"
#include "Core/Math/Random/Random.h"

MEDUSA_BEGIN;

SkeletonBone::SkeletonBone(const SkeletonBoneModel*const model)
	: mModel(model)
{
	SetToSetupPose(false);
	SetSize(Math::Max(5.f, (float)mModel->Length()), 5.f);

}


SkeletonBone::~SkeletonBone()
{

}

void SkeletonBone::SetToSetupPose(bool isApply /*= true*/)
{
	SetPosition(mModel->Position());
	SetScale(mModel->Scale());
	SetRotation(mModel->Rotation());
	SetInheritFlag(mModel->InheritFlag());
	if (isApply)
	{
		Apply();
	}
}

void SkeletonBone::AddBone(SkeletonBone* bone)
{
	mBones.Add(bone);
	bone->SetParent(this);
}

void SkeletonBone::AddSlot(INode* slot)
{
	mNeedApplyToSlot = true;
	mSlots.Add(slot);
}

void SkeletonBone::Apply(bool forceUpdateWorldMatrix /*= false*/)
{
	bool isWorldMatrixDirty = IsWorldMatrixDirty();
	forceUpdateWorldMatrix = this->UpdateWorldMatrix(forceUpdateWorldMatrix);
	isWorldMatrixDirty |= forceUpdateWorldMatrix;
	if (isWorldMatrixDirty || mNeedApplyToSlot)
	{
		//const Matrix& matrix = WorldMatrix();
		//update slot
		for (auto slot : mSlots)
		{
			slot->SetPosition(mWorldPosition);
			slot->SetScale(mWorldScale);
			slot->SetRotation(mWorldRotation);
			slot->SetFlip(mWorldFlip);
			//slot->SetSRTFromMatrix(matrix);
		}
		mNeedApplyToSlot = false;
	}


	//update bones
	for (auto bone : mBones)
	{
		bone->Apply(forceUpdateWorldMatrix);
	}

	if (isWorldMatrixDirty || mNeedApplyToSlot)
	{
		if (mDebugDrawShape != nullptr)
		{
			mDebugDrawShape->SetPosition(mWorldPosition);
			mDebugDrawShape->SetFlip(mWorldFlip);
			mDebugDrawShape->SetScale(mWorldScale);
			mDebugDrawShape->SetRotation(mWorldRotation);
		}
	}


}


void SkeletonBone::SetIsVisible(bool val)
{
	if (val)
	{
		if (mDebugDrawShape == nullptr)
		{
			//uint length = mModel->Length();
			//length = Math::Max(length, 5U);

			/*Color4F color;
			color.A = 1.f;
			Random random;
			color.R = random.NextFloat();
			color.G = random.NextFloat();
			color.B = random.NextFloat();*/
			Color4F color = mModel->Color();

			mDebugDrawShape = NodeFactory::Instance().CreateTriangle(mSize.Height, mSize.Width, color);
			
			mDebugDrawShape->SetPosition(WorldPosition());
			mDebugDrawShape->SetFlip(WorldFlip());
			mDebugDrawShape->SetScale(WorldScale());
			mDebugDrawShape->SetRotation(WorldRotation());
			mDebugDrawShape->EnableManaged();
			mSkeleton->AddChild(mDebugDrawShape);
		}

	}
	else
	{
		if (mDebugDrawShape != nullptr)
		{
			mSkeleton->DeleteChild(mDebugDrawShape);
			mDebugDrawShape = nullptr;
		}
	}

}

void SkeletonBone::SetParent(SkeletonBone* val)
{
	mParent = val;
	SetParentMoveable(mParent);
}





MEDUSA_END;
