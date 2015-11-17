// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SRTMoveable.h"
#include "Core/Log/Log.h"
#include "Core/Geometry/Rect2.h"

MEDUSA_BEGIN;


SRTMoveable::SRTMoveable()
	:mParentMoveable(nullptr),
	mPosition(Point3F::Zero),
	mRotation(Rotation3F::Zero), mScale(Scale3F::One), mFlip(FlipMask::None), mMatrix(Matrix::Identity), mWorldMatrix(Matrix::Identity)
{
	mMatrix.SetUpdateDelegate(Bind(&SRTMoveable::OnUpdateMatrix,this));
	mWorldMatrix.SetUpdateDelegate(Bind(&SRTMoveable::OnUpdateWorldMatrix,this));

}


SRTMoveable::~SRTMoveable(void)
{
}

void SRTMoveable::OnUpdateMatrix(Matrix& transform,int32 dirtyFlag)
{
	transform.ResetWorld(mScale, mRotation, mPosition, mFlip);

}


void SRTMoveable::OnUpdateWorldMatrix(Matrix& transform, int32 dirtyFlag)
{
	if (mParentMoveable != nullptr&&mParentMoveable->IsWorldMatrixDirty())
	{
		ForceSetWorldMatrix(LocalMatrix()*(mParentMoveable->WorldMatrix()));
	}
	else
	{
		ForceSetWorldMatrix(LocalMatrix());
	}
}


void SRTMoveable::SetMatrix(const Matrix& val)
{
	mMatrix.SetValue(val);
	mWorldMatrix.SetDirty();

	val.DecomposeXYZ(mScale, mRotation, mPosition);

	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);
}

bool SRTMoveable::IsWorldMatrixDirty() const
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


const Matrix& SRTMoveable::WorldMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
	}
	return mWorldMatrix.Value();
}



void SRTMoveable::ForceSetWorldMatrix(const Matrix& val)
{
	mWorldMatrix.SetValue(val);

	OnMoveableDirty(MoveableChangedFlags::WorldMatrixChanged);
}

Point3F SRTMoveable::WorldPosition() const
{
	if (mParentMoveable != nullptr)
	{
		return mParentMoveable->WorldMatrix().Transform(mPosition);
	}
	return mPosition;
}


Point3F SRTMoveable::LocalPosition() const
{
	return LocalMatrix().Translation();
}



void SRTMoveable::SetPosition(const Point3F& val)
{
	RETURN_IF_EQUAL(mPosition, val);

	mPosition = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::PositionChanged);
}


void SRTMoveable::SetLocalPosition(const Point3F& val)
{
	SetPosition(val);
}


void SRTMoveable::SetRotation(const Rotation3F& val)
{
	RETURN_IF_EQUAL(mRotation, val);

	mRotation = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::RotationChanged);

}

void SRTMoveable::SetScale(const Scale3F& val)
{
	RETURN_IF_EQUAL(mScale, val);

	mScale = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::ScaleChanged);

}



void SRTMoveable::SetFlipX(bool val)
{
	RETURN_IF_EQUAL(IsFlipX(), val);
	mFlip.SetOrRemoveIf(FlipMask::X, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);

}

void SRTMoveable::SetFlipY(bool val)
{
	RETURN_IF_EQUAL(IsFlipY(), val);
	mFlip.SetOrRemoveIf(FlipMask::Y, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}

void SRTMoveable::SetFlipZ(bool val)
{
	RETURN_IF_EQUAL(IsFlipZ(), val);
	mFlip.SetOrRemoveIf(FlipMask::Z, val);
	OnMoveableDirty(MoveableChangedFlags::FlipChanged);
}



Point3F SRTMoveable::TransformToWorld(const Point3F& val) const
{
	return WorldMatrix().Transform(val);
}

Rect2F SRTMoveable::TransformToWorld(const Rect2F& val) const
{
	return WorldMatrix().Transform(val);
}


void SRTMoveable::SetParentMoveable(SRTMoveable* val)
{
	if (mParentMoveable!=val)
	{
		mParentMoveable = val;
		mWorldMatrix.SetDirty();
	}
}




MEDUSA_END;