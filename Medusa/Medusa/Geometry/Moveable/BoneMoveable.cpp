// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BoneMoveable.h"
#include "Core/Log/Log.h"
#include "Geometry/Rect2.h"

MEDUSA_BEGIN;


BoneMoveable::BoneMoveable()
	:mParentMoveable(nullptr),
	 mSize(Size3F::Zero), mPosition(Point3F::Zero),
	mRotation(Rotation3F::Zero), mScale(Scale3F::One), mFlip(FlipMask::None),
	mWorldPosition(Point3F::Zero),mWorldRotation(Rotation3F::Zero), mWorldScale(Scale3F::One), mWorldFlip(FlipMask::None), 
	mMatrix(Matrix4::Identity), mWorldMatrix(Matrix4::Identity), mWorldInverseMatrix(Matrix4::Identity)
{
	mMatrix.SetUpdateDelegate(Bind(&BoneMoveable::OnUpdateMatrix, this));
	mWorldMatrix.SetUpdateDelegate(Bind(&BoneMoveable::OnUpdateWorldMatrix, this));
	mWorldInverseMatrix.SetUpdateDelegate(Bind(&BoneMoveable::OnUpdateWorldInverseMatrix,this));
	mBoundingBox.SetUpdateDelegate(Bind(&BoneMoveable::OnUpdateBoundingBox, this));
	mWorldBoundingBox.SetUpdateDelegate(Bind(&BoneMoveable::OnUpdateWorldBoundingBox, this));

}


BoneMoveable::~BoneMoveable(void)
{
}

void BoneMoveable::OnUpdateMatrix(Matrix4& transform,int32 dirtyFlag)
{
	//size do not used to update matrix
	transform.ResetWorldWithoutAnchor(mScale,Rotation2F::Zero, mRotation, mPosition, mFlip);
}


void BoneMoveable::OnUpdateWorldMatrix(Matrix4& transform, int32 dirtyFlag)
{
	UpdateWorldMatrixByInherit();
}


void BoneMoveable::OnUpdateWorldInverseMatrix(Matrix4& transform, int32 dirtyFlag)
{
	transform = mWorldMatrix.Value();
	transform.Inverse();
}

void BoneMoveable::ForceSetMatrix(const Matrix4& val)
{
	mMatrix.SetValue(val);
	mWorldMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	val.DecomposeXYZ(mScale, mRotation, mPosition);

	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);
}

bool BoneMoveable::IsWorldMatrixDirty() const
{
	return mWorldMatrix.IsDirty();
}

bool BoneMoveable::CheckWorldMatrixDirtyToRoot() const
{
	if (mParentMoveable != nullptr&&mParentMoveable->IsWorldMatrixDirty())
	{
		return true;
	}
	else
	{
		return mWorldMatrix.IsDirty();
	}
}

const Matrix4& BoneMoveable::WorldMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
	}
	return mWorldMatrix.Value();
}



void BoneMoveable::ForceSetWorldMatrix(const Matrix4& val)
{
	mWorldMatrix.SetValue(val);
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::WorldMatrixChanged);
}


Point3F BoneMoveable::LocalPosition() const
{
	return LocalMatrix().Translation();
}

Size3F BoneMoveable::LocalSize() const
{
	return GetBoundingBox().Size;
}

Size3F BoneMoveable::WorldSize() const
{
	return WorldBoundingBox().Size;
}

void BoneMoveable::SetSize(const Size3F& val)
{
	RETURN_IF_EQUAL(mSize, val);
	mSize = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::SizeChanged);
}
void BoneMoveable::SetPosition(const Point3F& val)
{
	RETURN_IF_EQUAL(mPosition, val);

	mPosition = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::PositionChanged);
}


void BoneMoveable::SetLocalPosition(const Point3F& val)
{
	SetPosition(val);
}


void BoneMoveable::SetRotation(const Rotation3F& val)
{
	RETURN_IF_EQUAL(mRotation, val);

	mRotation = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::RotationChanged);

}

void BoneMoveable::SetScale(const Scale3F& val)
{
	RETURN_IF_EQUAL(mScale, val);

	mScale = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::ScaleChanged);

}



void BoneMoveable::SetFlipX(bool val)
{
	RETURN_IF_EQUAL(IsFlipX(), val);
	MEDUSA_FLAG_ENABLE(mFlip, FlipMask::X, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);

}

void BoneMoveable::SetFlipY(bool val)
{
	RETURN_IF_EQUAL(IsFlipY(), val);
	MEDUSA_FLAG_ENABLE(mFlip, FlipMask::Y, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}

void BoneMoveable::SetFlipZ(bool val)
{
	RETURN_IF_EQUAL(IsFlipZ(), val);
	MEDUSA_FLAG_ENABLE(mFlip, FlipMask::Z, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}



Point3F BoneMoveable::TransformToWorld(const Point3F& val) const
{
	return WorldMatrix().Transform(val);
}

Rect2F BoneMoveable::TransformToWorld(const Rect2F& val) const
{
	return WorldMatrix().Transform(val);
}

Point3F BoneMoveable::TransformToLocal(const Point3F& val) const
{
	return WorldInverseMatrix().Transform(val);
}
Point2F BoneMoveable::TransformToLocal(const Point2F& val) const
{
	return WorldInverseMatrix().Transform(val);
}

Rect2F BoneMoveable::TransformToLocal(const Rect2F& val) const
{
	return WorldInverseMatrix().Transform(val);
}

bool BoneMoveable::UpdateWorldMatrix(bool forceUpdateWorldMatrix /*= false*/)
{
	if (forceUpdateWorldMatrix)
	{
		UpdateWorldMatrixByInherit();
	}
	else
	{
		if (IsWorldMatrixDirty())
		{
			UpdateWorldMatrixByInherit();
			forceUpdateWorldMatrix = true;
		}
	}

	return forceUpdateWorldMatrix;
}

void BoneMoveable::UpdateWorldMatrixByInherit()
{
	if (mParentMoveable == nullptr)
	{
		mWorldScale = mScale;
		mWorldRotation = mRotation;
		mWorldPosition = mPosition;

		mWorldMatrix = mMatrix.Value();
		return;
	}

	mWorldPosition = mParentMoveable->WorldMatrix().Transform(mPosition);
	mWorldScale = mScale;
	mWorldRotation = mRotation;

	if (!MEDUSA_FLAG_HAS(mInheritFlag, MoveableInheritFlags::IgnoreScale))
	{
		mWorldScale *= mParentMoveable->WorldScale();
	}

	if (!MEDUSA_FLAG_HAS(mInheritFlag, MoveableInheritFlags::IgnoreRotation))
	{
		mWorldRotation += mParentMoveable->WorldRotation();
	}

	mWorldFlip = mFlip;
	if (!MEDUSA_FLAG_HAS(mInheritFlag, MoveableInheritFlags::IgnoreFlip))
	{
		if (mParentMoveable->IsWorldFlipX())
		{
			MEDUSA_FLAG_ENABLE(mWorldFlip, FlipMask::X, !MEDUSA_FLAG_HAS(mFlip, FlipMask::X));
		}

		if (mParentMoveable->IsWorldFlipY())
		{
			MEDUSA_FLAG_ENABLE(mWorldFlip, FlipMask::Y, !MEDUSA_FLAG_HAS(mFlip, FlipMask::Y));
		}

		if (mParentMoveable->IsWorldFlipZ())
		{
			MEDUSA_FLAG_ENABLE(mWorldFlip, FlipMask::Z, !MEDUSA_FLAG_HAS(mFlip, FlipMask::Z));
		}
	}

	mWorldMatrix.OldValue().ResetWorldWithoutAnchor(mWorldScale, Rotation2F::Zero, mWorldRotation, mWorldPosition, mWorldFlip);
	mWorldMatrix.SetDirty(false);


}

void BoneMoveable::SetInheritFlag(MoveableInheritFlags val)
{
	RETURN_IF_EQUAL(mInheritFlag, val);
	mInheritFlag = val;

	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::InheritChanged);
}


void BoneMoveable::EnableInheritScale(bool val)
{
	MEDUSA_FLAG_ENABLE(mInheritFlag, MoveableInheritFlags::IgnoreScale, !val);
}

void BoneMoveable::EnableInheritRotation(bool val)
{
	MEDUSA_FLAG_ENABLE(mInheritFlag, MoveableInheritFlags::IgnoreRotation, !val);
}

bool BoneMoveable::IsInheritScale() const
{
	return !MEDUSA_FLAG_HAS(mInheritFlag, MoveableInheritFlags::IgnoreScale);
}

bool BoneMoveable::IsInheritRotation() const
{
	return !MEDUSA_FLAG_HAS(mInheritFlag, MoveableInheritFlags::IgnoreRotation);
}

void BoneMoveable::OnUpdateBoundingBox(BoundingBox& outVal, int32 dirtyFlag)
{
	CubeF cube;
	cube.Origin = Point3F::Zero;
	cube.Size = mSize;
	outVal = LocalMatrix().Transform(cube);
}


void BoneMoveable::OnUpdateWorldBoundingBox(BoundingBox& outVal, int32 dirtyFlag)
{
	CubeF cube;
	cube.Origin = Point3F::Zero;
	cube.Size = mSize;

	outVal = WorldMatrix().Transform(cube);
}

void BoneMoveable::ForceSetWorldBoundingBox(const BoundingBox& val)
{
	mWorldBoundingBox = val;
}

bool BoneMoveable::HitTestWorld(const Point2F& worldPos) const
{
	Point2F localPos = TransformToLocal(worldPos);
	return HitTestLocal(localPos);
}


bool BoneMoveable::HitTestLocal(const Point2F& localPos) const
{
	return (localPos.X >= 0.f&&localPos.X <= mSize.Width) && (localPos.Y >= 0.f&&localPos.Y <= mSize.Height);
}

void BoneMoveable::SetParentMoveable(BoneMoveable* val)
{
	if (mParentMoveable!=val)
	{
		mParentMoveable = val;
		mWorldMatrix.SetDirty();
		mBoundingBox.SetDirty();
		mWorldBoundingBox.SetDirty();
	}
	
}



MEDUSA_END;