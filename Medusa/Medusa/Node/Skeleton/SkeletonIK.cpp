// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonIK.h"
#include "Resource/Skeleton/SkeletonIKModel.h"
#include "Resource/Skeleton/SkeletonBoneModel.h"
#include "Core/Log/Log.h"
#include "ISkeleton.h"
#include "SkeletonBone.h"
#include "Geometry/IK/IKSolver2D.h"


MEDUSA_BEGIN;

SkeletonIK::SkeletonIK(ISkeleton* animation, const SkeletonIKModel*const model)
	:mAnimation(animation), mModel(model), mTargetBone(nullptr)
{
	SetToSetupPose();
}


SkeletonIK::~SkeletonIK()
{

}

void SkeletonIK::SetToSetupPose()
{
	mIsBendPositive = mModel->IsBendPositive();
	mMix = mModel->Mix();
	mTargetBone = mAnimation->FindBone(mModel->TargetBone()->Name());

	mBones.Clear();
	const List<SkeletonBoneModel*>& bones = mModel->Bones();
	for(auto boneModel: bones)
	{
		SkeletonBone* bone = mAnimation->FindBone(boneModel->Name());
		mBones.Add(bone);
	}



}

bool SkeletonIK::IsAffectBone(SkeletonBone* bone) const
{
	SkeletonBone* parent = mBones[0];

	if (mBones.Count() == 2)
	{
		SkeletonBone* child = mBones.Last();
		do
		{
			RETURN_TRUE_IF_EQUAL(bone, child);
			child = child->Parent();
		} while (child != parent);
	}
	else if (mBones.Count() == 1)
	{
		return parent == bone;
	}


	return false;
}

void SkeletonIK::Apply()
{
	//TODO: not test enough
	if (Math::IsZero(mMix))
	{
		return;
	}

	//only support 2d

	if (mBones.Count() == 1)
	{
		SkeletonBone* bone = mBones.First();
		//Rotation3F parentRotaion = (bone->Parent() == nullptr || !bone->Model()->IsInheritRotation()) ? Rotation3F::Zero : bone->Parent()->Rotation();
		Point3F delta = mTargetBone->Position() - bone->Position();

		Rotation3F rotation = Rotation3F::Zero;
		rotation.Z = Math::Atan2(delta.Y, delta.X);

		rotation = bone->Rotation()*(1.f - mMix) + rotation*mMix;
		bone->SetRotation(rotation);
		return;
	}
	else if (mBones.Count() == 2)
	{
		SkeletonBone* parent = mBones[0];
		SkeletonBone* child = mBones[1];

		/*
		our target is to construct a world coordinate with parent in origin to calcuate rotation angle
		Notice bone's pos in in parent space,and scale effects on child nodes
		*/
		//Note that at this time, parent and child has no rotation at all,but still have scales
		Point3F targetPos = mTargetBone->Position();

		SkeletonBone* parentParent = parent->Parent();
		if (parentParent != nullptr)
		{
			//convert to parent space,not need parent rotation now,so cannot use parent->TransformToLocal directly
			//have to conter to parentParent space,then multiply parentParent scale matrix
			targetPos = parentParent->TransformToLocal(targetPos);

			//now targetPos and parent->Position(); are in parentParent space
			targetPos-= parent->Position();

			//multiply parentParent scale matrix to conver to parent space
			targetPos.X *= parentParent->Scale().X;
			targetPos.Y *= parentParent->Scale().Y;
			
		}
		else
		{
			//parent is root,so parent's parent is a translation matrix and scale matrix is 1
			targetPos -= parent->Position();
		}

		Point3F childPos = child->Position();
		if (child->Parent()==parent)
		{
			//child in parent's space, multiply parent's matrix to convert to parent's world coordinate space
			childPos.X *= parent->Scale().X;
			childPos.Y *= parent->Scale().Y;
		}
		else
		{
			//child is a more deep child node, first conver to world space
			Point3F childWorldPos=child->WorldPosition();
			//then convert to parent space
			childPos = parent->TransformToLocal(childWorldPos);
			//multiply parentParent scale matrix to conver to parent space
			childPos.X *= parent->Scale().X;
			childPos.Y *= parent->Scale().Y;
		}

		float parentBoneLength = childPos.Length();
		//child's rotation is 0 initial,so can multiply scale.x directly
		float childBoneLength = child->Model()->Length()*child->Scale().X;

		Rotation3F currentChildRotation(0.f,0.f,Math::Atan2(childPos.Y, childPos.X));

		float outParentRotation;
		float outChildRotation;

		if (IKSolver2D::AnalyzeTwoBone(parentBoneLength, childBoneLength, targetPos.X, targetPos.Y, mIsBendPositive, outParentRotation, outChildRotation))
		{
			//subtract current rotation to get dleta rotation
			Rotation3F parentRotation(0.f, 0.f, outParentRotation);
			parentRotation -= currentChildRotation;
			parent->SetRotation(parent->Rotation()*(1.f - mMix) + parentRotation*mMix);
			Rotation3F rotation(0.f,0.f,outChildRotation);

			rotation += currentChildRotation + parent->Rotation() - child->Parent()->Rotation();

			child->SetRotation(child->Rotation()*(1.f - mMix) + rotation*mMix);

		}

	}
	else
	{
		Log::AssertFailed("Not support multiple bones now");
	}

}





MEDUSA_END;
