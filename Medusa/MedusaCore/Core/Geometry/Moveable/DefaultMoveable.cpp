// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "DefaultMoveable.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;


DefaultMoveable::DefaultMoveable()
	:mParentMoveable(nullptr), 
	mSize(Size3F::Zero),mAnchor(Point3F::Zero), mPosition(Point3F::Zero),
	mRotation(Rotation3F::Zero), mScale(Scale3F::One), mFlip(FlipMask::None), 
	mMatrix(Matrix4::Identity), mWorldMatrix(Matrix4::Identity)
{
	mMatrix.SetUpdateDelegate(Bind(&DefaultMoveable::OnUpdateMatrix, this));
	mWorldMatrix.SetUpdateDelegate(Bind(&DefaultMoveable::OnUpdateWorldMatrix,this));
	mWorldInverseMatrix.SetUpdateDelegate(Bind(&DefaultMoveable::OnUpdateWorldInverseMatrix, this));
	mBoundingBox.SetUpdateDelegate(Bind(&DefaultMoveable::OnUpdateBoundingBox, this));
	mWorldBoundingBox.SetUpdateDelegate(Bind(&DefaultMoveable::OnUpdateWorldBoundingBox, this));

}


DefaultMoveable::~DefaultMoveable(void)
{
}

void DefaultMoveable::SetMoveable(const DefaultMoveable& val)
{
	mSize = val.mSize;
	mAnchor = val.mAnchor;
	mPosition = val.mPosition;
	mRotation = val.mRotation;
	mScale = val.mScale;
	mFlip = val.mFlip;
	mMatrix = val.mMatrix;
	mWorldMatrix = val.mWorldMatrix;
	mWorldInverseMatrix = val.mWorldInverseMatrix;
	mBoundingBox = val.mBoundingBox;
	mWorldBoundingBox = val.mWorldBoundingBox;
	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);
}

void DefaultMoveable::OnUpdateMatrix(Matrix4& transform, int32 dirtyFlag)
{
	transform.ResetWorld(mSize, mAnchor, mScale, mRotation, mPosition, mFlip);

}


void DefaultMoveable::OnUpdateWorldMatrix(Matrix4& transform, int32 dirtyFlag)
{
	if (mParentMoveable != nullptr)
	{
		ForceSetWorldMatrix(LocalMatrix()*(mParentMoveable->WorldMatrix()));
	}
	else
	{
		ForceSetWorldMatrix(LocalMatrix());
	}
}


void DefaultMoveable::OnUpdateWorldInverseMatrix(Matrix4& transform, int32 dirtyFlag)
{
	transform = mWorldMatrix.Value();
	transform.Inverse();
}


void DefaultMoveable::OnUpdateBoundingBox(BoundingBox& outVal, int32 dirtyFlag)
{
	CubeF cube;
	cube.Origin = Point3F::Zero;
	cube.Size = mSize;
	outVal = LocalMatrix().Transform(cube);
}


void DefaultMoveable::OnUpdateWorldBoundingBox(BoundingBox& outVal, int32 dirtyFlag)
{
	CubeF cube;
	cube.Origin = Point3F::Zero;
	cube.Size = mSize;

	outVal = WorldMatrix().Transform(cube);
}

void DefaultMoveable::ForceSetMatrix(const Matrix4& val)
{
	mMatrix.SetValue(val);
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);
}

void DefaultMoveable::SetSRTFromMatrix(const Matrix4& val)
{
	mMatrix.SetValue(val);
	val.DecomposeXYZ(mScale, mRotation, mPosition);
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);

}

bool DefaultMoveable::IsWorldMatrixDirty() const
{
	return mWorldMatrix.IsDirty();
}

bool DefaultMoveable::CheckWorldMatrixDirtyToRoot() const
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

const Matrix4& DefaultMoveable::WorldMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
	}
	return mWorldMatrix.Value();
}


const Matrix4& DefaultMoveable::WorldInverseMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
		mWorldInverseMatrix.ForceUpdate();
	}
	return mWorldInverseMatrix.Value();
}

void DefaultMoveable::ForceSetWorldMatrix(const Matrix4& val)
{
	mWorldMatrix.SetValue(val);
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::WorldMatrixChanged);
}

Point3F DefaultMoveable::WorldPosition() const
{
	if (mParentMoveable != nullptr)
	{
		return mParentMoveable->WorldMatrix().Transform(mPosition);
	}
	return mPosition;
}


Point3F DefaultMoveable::LocalPosition() const
{
	return LocalMatrix().Translation();
}

Size3F DefaultMoveable::LocalSize() const
{
	return GetBoundingBox().Size;
}

Size3F DefaultMoveable::WorldSize() const
{
	return WorldBoundingBox().Size;
}


void DefaultMoveable::SetSize(const Size3F& val)
{
	RETURN_IF_EQUAL(mSize, val);
	mSize = val;
	if (mAnchor != Point3F::Zero || !mFlip.IsZero())
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}

	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::SizeChanged);
}


void DefaultMoveable::SetLocalSize(const Size3F& val)
{
	const Size3F& localSize = LocalSize();
	RETURN_IF_EQUAL(localSize, val);

	mScale.X = val.Width / localSize.Width;
	mScale.Y = val.Height / localSize.Height;
	if (!Math::IsZero(localSize.Depth))
	{
		mScale.Z = val.Depth / localSize.Depth;
	}
	else
	{
		mScale.Z = 1.f;
	}

}

void DefaultMoveable::SetPosition(const Point3F& val)
{
	RETURN_IF_EQUAL(mPosition, val);

	mPosition = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::PositionChanged);
}


void DefaultMoveable::SetLocalPosition(const Point3F& val)
{
	RemoveAnchor();
	SetPosition(val);
}


void DefaultMoveable::SetRotation(const Rotation3F& val)
{
	RETURN_IF_EQUAL(mRotation, val);

	mRotation = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::RotationChanged);

}

void DefaultMoveable::SetScale(const Scale3F& val)
{
	RETURN_IF_EQUAL(mScale, val);

	mScale = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::ScaleChanged);

}

void DefaultMoveable::SetAnchor(const Point3F& val)
{
	RETURN_IF_EQUAL(mAnchor, val);

	mAnchor = val;
	if (mSize != Size3F::Zero)
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}

	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::AnchorChanged);
}


void DefaultMoveable::SetAnchorPoint(AnchorPoint point)
{
	switch (point)
	{
		case AnchorPoint::LeftBottom:
			SetAnchor(mppp(0.f, 0.f, 0.f));
			break;
		case AnchorPoint::LeftCenter:
			SetAnchor(mppp(0.f, 0.5f, 0.f));
			break;
		case AnchorPoint::LeftTop:
			SetAnchor(mppp(0.f, 1.f, 0.f));
			break;
		case AnchorPoint::MiddleBottom:
			SetAnchor(mppp(0.5f, 0.f, 0.f));
			break;
		case AnchorPoint::MiddleCenter:
			SetAnchor(mppp(0.5f, 0.5f, 0.f));
			break;
		case AnchorPoint::MiddleTop:
			SetAnchor(mppp(0.5f, 1.f, 0.f));
			break;
		case AnchorPoint::RightBottom:
			SetAnchor(mppp(1.f, 0.f, 0.f));
			break;
		case AnchorPoint::RightCenter:
			SetAnchor(mppp(1.f, 0.5f, 0.f));
			break;
		case AnchorPoint::RightTop:
			SetAnchor(mppp(1.f, 1.f, 0.f));
			break;
		default:
			break;
	}
}


void DefaultMoveable::SetAnchorX(float val)
{
	SetAnchor(Point3F(val, mAnchor.Y, mAnchor.Z));
}

void DefaultMoveable::SetAnchorY(float val)
{
	SetAnchor(Point3F(mAnchor.X, val, mAnchor.Z));
}

void DefaultMoveable::SetAnchorZ(float val)
{
	SetAnchor(Point3F(mAnchor.X, mAnchor.Y, val));
}

void DefaultMoveable::RemoveAnchor()
{
	if (mAnchor != Point3F::Zero)
	{
		mPosition = LocalPosition();
		mAnchor = Point3F::Zero;
	}
}

void DefaultMoveable::SetFlipX(bool val)
{
	RETURN_IF_EQUAL(IsFlipX(), val);
	mFlip.SetOrRemoveIf(FlipMask::X, val);
	if (mSize != Size3F::Zero)
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);

}

void DefaultMoveable::SetFlipY(bool val)
{
	RETURN_IF_EQUAL(IsFlipY(), val);
	mFlip.SetOrRemoveIf(FlipMask::Y, val);
	if (mSize != Size3F::Zero)
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}

void DefaultMoveable::SetFlipZ(bool val)
{
	RETURN_IF_EQUAL(IsFlipZ(), val);
	mFlip.SetOrRemoveIf(FlipMask::Z, val);
	if (mSize != Size3F::Zero)
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}

void DefaultMoveable::SetFlip(FlipMask val)
{
	RETURN_IF_EQUAL(mFlip, val);
	mFlip = val;
	if (mSize != Size3F::Zero)
	{
		mMatrix.SetDirty();
		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
	}


	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}


Rect2F DefaultMoveable::TransformToWorld(const Rect2F& val) const
{
	return WorldMatrix().Transform(val);
}
Point3F DefaultMoveable::TransformToWorld(const Point3F& val) const
{
	return WorldMatrix().Transform(val);
}


Point2F DefaultMoveable::TransformToWorld(const Point2F& val) const
{
	return WorldMatrix().Transform(val);
}

Point3F DefaultMoveable::TransformToLocal(const Point3F& val) const
{
	return WorldInverseMatrix().Transform(val);
}

Point2F DefaultMoveable::TransformToLocal(const Point2F& val) const
{
	return WorldInverseMatrix().Transform(val);
}

Rect2F DefaultMoveable::TransformToLocal(const Rect2F& val) const
{
	return WorldInverseMatrix().Transform(val);
}

void DefaultMoveable::ForceSetWorldBoundingBox(const BoundingBox& val)
{
	mWorldBoundingBox = val;
}

bool DefaultMoveable::HitTestWorld(const Point2F& worldPos) const
{
	Point2F localPos = TransformToLocal(worldPos);
	return HitTestLocal(localPos);
}


bool DefaultMoveable::HitTestLocal(const Point2F& localPos) const
{
	return (localPos.X >= 0.f&&localPos.X <= mSize.Width) && (localPos.Y >= 0.f&&localPos.Y <= mSize.Height);
}

void DefaultMoveable::SetParentMoveable(DefaultMoveable* val)
{
	if (mParentMoveable!=val)
	{
		mParentMoveable = val;

		mWorldMatrix.SetDirty();
		mWorldInverseMatrix.SetDirty();
		mWorldBoundingBox.SetDirty();
	}
}




MEDUSA_END;