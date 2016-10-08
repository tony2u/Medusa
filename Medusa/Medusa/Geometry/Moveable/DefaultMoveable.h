// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point3.h"
#include "Geometry/Rotation3.h"
#include "Geometry/Scale3.h"
#include "Geometry/Matrix4.h"
#include "Core/Pattern/LazyValue.h"
#include "Geometry/Cube.h"


MEDUSA_BEGIN;

//model => local => world

class DefaultMoveable
{
public:
	DefaultMoveable();
	virtual ~DefaultMoveable(void);
	void SetMoveable(const DefaultMoveable& val);

	Size2F Size2D() const { return mSize.To2D(); }
	const Size3F& Size() const { return mSize; }
	void SetSize(const Size3F& val);
	void SetSize(float width, float height, float depth = 0.f) { SetSize(Size3F(width, height, depth)); }
	void SetWidth(float width) { SetSize(Size3F(width, mSize.Height, mSize.Depth)); }
	void SetHeight(float height) { SetSize(Size3F(mSize.Width, height, mSize.Depth)); }
	float Width()const { return mSize.Width; }
	float Height()const { return mSize.Height; }
	float Depth()const { return mSize.Depth; }

	Size3F LocalSize()const;	//like bound size
	Size2F LocalSize2D()const;	//like bound size

	void SetLocalSize(const Size3F& val);
	void SetLocalSize(float width, float height, float depth = 0.f) { SetLocalSize(Size3F(width, height, depth)); }

	Size3F WorldSize()const;
	Size2F WorldSize2D()const;


	float X()const { return mPosition.X; }
	float Y()const { return mPosition.Y; }
	float Z()const { return mPosition.Z; }

	const Point3F& Position() const { return mPosition; }
	Point2F Position2D() const { return mPosition.To2D(); }

	void SetPosition(const Point3F& val);
	void SetPosition(const Point2F& val) { SetPosition(Point3F(val.X, val.Y, mPosition.Z)); }
	void SetPosition(float x, float y, float z = 0.f) { SetPosition(Point3F(x, y, z)); }
	void SetPositionX(float x) { SetPosition(Point3F(x, mPosition.Y, mPosition.Z)); }
	void SetPositionY(float y) { SetPosition(Point3F(mPosition.X, y, mPosition.Z)); }
	void SetPositionZ(float z) { SetPosition(Point3F(mPosition.X, mPosition.Y, z)); }
	void SetPositionXY(float x, float y) { SetPosition(Point3F(x, y, mPosition.Z)); }

	void Move(const Point3F& val) { SetPosition(mPosition + val); }
	void Move(const Point2F& val) { SetPositionXY(mPosition.X + val.X, mPosition.Y + val.Y); }

	void MoveX(float x) { SetPositionX(mPosition.X + x); }
	void MoveY(float y) { SetPositionY(mPosition.Y + y); }
	void MoveZ(float z) { SetPositionZ(mPosition.Z + z); }
	void MoveXY(float x, float y) { SetPositionXY(mPosition.X + x, mPosition.Y + y); }


	Point3F LocalPosition()const;	//left bottom, without anchor
	Point2F LocalPosition2D()const;	//left bottom, without anchor

	void SetLocalPosition(const Point3F& val);
	void SetLocalPosition(float x, float y, float z = 0.f) { SetLocalPosition(Point3F(x, y, z)); }

	Point3F WorldPosition()const;
	Point2F WorldPosition2D()const;


	bool IsFlipX()const { return MEDUSA_FLAG_HAS(mFlip,FlipMask::X); }
	bool IsFlipY()const { return MEDUSA_FLAG_HAS(mFlip, FlipMask::Y); }
	bool IsFlipZ()const { return MEDUSA_FLAG_HAS(mFlip, FlipMask::Z);  }

	void SetFlipX(bool val);
	void SetFlipY(bool val);
	void SetFlipZ(bool val);
	FlipMask Flip() const { return mFlip; }
	void SetFlip(FlipMask val);

	const Point2F& Anchor2D() const { return mAnchor.To2D(); }
	const Point3F& Anchor() const { return mAnchor; }
	void SetAnchor(const Point3F& val);
	void SetAnchor(float x, float y, float z = 0.f) { SetAnchor(Point3F(x, y, z)); }

	float AnchorX()const { return mAnchor.X; }
	float AnchorY()const { return mAnchor.Y; }
	float AnchorZ()const { return mAnchor.Z; }
	void SetAnchorX(float val);
	void SetAnchorY(float val);
	void SetAnchorZ(float val);
	void SetAnchorPoint(AnchorPoint point);


	void RemoveAnchor();	//keep local position not changed

	float RotationX()const { return mRotation.X; }
	float RotationY()const { return mRotation.Y; }
	float RotationZ()const { return mRotation.Z; }
	float Rotation2D() const { return mRotation.Z; }

	const Rotation3F& Rotation() const { return mRotation; }
	void SetRotation(const Rotation3F& val);
	void SetRotation(float x, float y, float z = 0.f) { SetRotation(Rotation3F(x, y, z)); }
	void SetRotationX(float val) { SetRotation(Rotation3F(val, mRotation.Y, mRotation.Z)); }
	void SetRotationY(float val) { SetRotation(Rotation3F(mRotation.X, val, mRotation.Z)); }
	void SetRotationZ(float val) { SetRotation(Rotation3F(mRotation.X, mRotation.Y, val)); }

	float SkewX() const { return mSkewXY.X; }
	float SkewY() const { return mSkewXY.Y; }
	const Rotation2F& SkewXY() const { return mSkewXY; }
	void SetSkewXY(const Rotation2F& val);
	void SetSkewXY(float x, float y) { SetSkewXY(Rotation2F(x, y)); }

	void SetSkewX(float val) { SetSkewXY(Rotation2F(val, mSkewXY.Y)); }
	void SetSkewY(float val) { SetSkewXY(Rotation2F(mSkewXY.X, val)); }



	float ScaleX()const { return mScale.X; }
	float ScaleY()const { return mScale.Y; }
	float ScaleZ()const { return mScale.Z; }

	Scale2F Scale2D() const { return mScale.To2D(); }
	const Scale3F& Scale() const { return mScale; }
	void SetScale(const Scale3F& val);
	void SetScale(float x, float y, float z = 1.f) { SetScale(Scale3F(x, y, z)); }
	void SetScaleX(float x) { SetScale(Scale3F(x, mScale.Y, mScale.Z)); }
	void SetScaleY(float y) { SetScale(Scale3F(mScale.X, y, mScale.Z)); }
	void SetScale(float val) { SetScale(Scale3F(val, val, 1.f)); }


	const Matrix4& LocalMatrix()const { return mMatrix.Value(); }
	void ForceSetMatrix(const Matrix4& val);
	bool IsMatrixDirty()const { return mMatrix.IsDirty(); }
	void SetSRTFromMatrix(const Matrix4& val);


	const Matrix4& WorldMatrix()const;
	bool IsWorldMatrixDirty()const;
	bool CheckWorldMatrixDirtyToRoot()const;

	void ForceSetWorldMatrix(const Matrix4& val);
	bool TryUpdateWorldMatrix()const { return mWorldMatrix.TryUpdate(); }
	size_t WorldMatrixVersion()const { return mWorldMatrix.Version(); }

	const Matrix4& WorldInverseMatrix()const;

	const BoundingBox& GetBoundingBox()const { return mBoundingBox.Value(); }
	const BoundingBox& WorldBoundingBox()const { return mWorldBoundingBox.Value(); }
	void ForceSetWorldBoundingBox(const BoundingBox& val);
public:
	Point3F TransformToLocal(const Point3F& val)const;
	Point2F TransformToLocal(const Point2F& val)const;
	Rect2F TransformToLocal(const Rect2F& val)const;

	Point3F TransformToWorld(const Point3F& val)const;
	Point2F TransformToWorld(const Point2F& val)const;
	Rect2F TransformToWorld(const Rect2F& val)const;

	bool HitTestWorld(const Point2F& worldPos)const;
	virtual bool HitTestLocal(const Point2F& localPos)const;
	bool HitTestParent(const Point2F& parentPos)const;


protected:
	DefaultMoveable* ParentMoveable() const { return mParentMoveable; }
	void SetParentMoveable(DefaultMoveable* val);

	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags) {}

private:
	void OnUpdateMatrix(Matrix4& transform, int32 dirtyFlag);
	void OnUpdateInverseMatrix(Matrix4& transform, int32 dirtyFlag);
	void OnUpdateWorldMatrix(Matrix4& transform, int32 dirtyFlag);
	void OnUpdateWorldInverseMatrix(Matrix4& transform, int32 dirtyFlag);
	void OnUpdateBoundingBox(BoundingBox& outVal, int32 dirtyFlag);
	void OnUpdateWorldBoundingBox(BoundingBox& outVal, int32 dirtyFlag);

protected:
	DefaultMoveable* mParentMoveable=nullptr;

	Size3F mSize;

	Point3F mAnchor;
	Point3F mPosition;
	Rotation3F mRotation;
	Rotation2F mSkewXY;

	Scale3F mScale;
	FlipMask mFlip;


	LazyMatrix4 mMatrix;
	LazyMatrix4 mInverseMatrix;
	LazyMatrix4 mWorldMatrix;
	LazyMatrix4 mWorldInverseMatrix;


	LazyBoundingBox mBoundingBox;	//self bounding box
	LazyBoundingBox mWorldBoundingBox;	//recursive bounding box
};

MEDUSA_END;