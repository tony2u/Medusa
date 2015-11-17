// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Matrix.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/MoveableInheritFlags.h"
#include "Core/Geometry/MoveableChangedFlags.h"
#include "Core/Geometry/Cube.h"

MEDUSA_BEGIN;

/*
NOTE:
???????????????????,???????????????,
??
(S1*R1*T1)*(S2*R2*T2)=(S1*S2)*(R1*R2)*T1*T2
????????????,?????,??????,??????????,??????????
??,???,???????

*/

class BoneMoveable
{
public:
	BoneMoveable();
	virtual ~BoneMoveable(void);
	const Size3F& Size() const { return mSize; }
	void SetSize(const Size3F& val);
	void SetSize(float width, float height, float depth = 0.f) { SetSize(Size3F(width, height, depth)); }

	Size3F LocalSize()const;
	void SetLocalSize(const Size3F& val);
	void SetLocalSize(float width, float height, float depth = 0.f) { SetLocalSize(Size3F(width, height, depth)); }

	Size3F WorldSize()const;

	const Point3F& Position() const { return mPosition; }
	void SetPosition(const Point3F& val);
	void SetPosition(float x,float y,float z=0.f){SetPosition(Point3F(x,y,z));}
	void SetPositionX(float x){SetPosition(Point3F(x,mPosition.Y,mPosition.Z));}
	void SetPositionY(float y){SetPosition(Point3F(mPosition.X,y,mPosition.Z));}
	void Move(const Point3F& val){SetPosition(mPosition+val);}


	Point3F LocalPosition()const;	//left bottom, without anchor
	void SetLocalPosition(const Point3F& val);
	void SetLocalPosition(float x,float y,float z=0.f){SetLocalPosition(Point3F(x,y,z));}

	const Point3F& WorldPosition() const { return mWorldPosition; }

	bool IsFlipX()const{ return mFlip.Has(FlipMask::X); }
	bool IsFlipY()const{ return mFlip.Has(FlipMask::Y); }
	bool IsFlipZ()const{ return mFlip.Has(FlipMask::Z); }

	void SetFlipX(bool val);
	void SetFlipY(bool val);
	void SetFlipZ(bool val);

	const Rotation3F& Rotation() const { return mRotation; }
	void SetRotation(const Rotation3F& val);
	void SetRotation(float x,float y,float z=0.f){SetRotation(Rotation3F(x,y,z));}

	const Scale3F& Scale() const { return mScale; }
	void SetScale(const Scale3F& val);
	void SetScale(float x,float y,float z=1.f){SetScale(Scale3F(x,y,z));}
	void SetScaleX(float x){SetScale(Scale3F(x,mScale.Y,mScale.Z));}
	void SetScaleY(float y){SetScale(Scale3F(mScale.X,y,mScale.Z));}
	void SetScale(float val){SetScale(Scale3F(val,val,1.f));}


	const Rotation3F& WorldRotation() const { return mWorldRotation; }
	const Scale3F& WorldScale() const { return mWorldScale; }
	const FlipMask& WorldFlip() const { return mWorldFlip; }

	bool IsWorldFlipX()const { return mWorldFlip.Has(FlipMask::X); }
	bool IsWorldFlipY()const { return mWorldFlip.Has(FlipMask::Y); }
	bool IsWorldFlipZ()const { return mWorldFlip.Has(FlipMask::Z); }

	const Matrix& LocalMatrix()const{ return mMatrix.Value(); }
	void SetMatrix(const Matrix& val);
	bool IsMatrixDirty()const{return mMatrix.IsDirty();}

	const Matrix& WorldMatrix()const;
	bool IsWorldMatrixDirty()const;
	bool CheckWorldMatrixDirtyToRoot()const;

	void ForceSetWorldMatrix(const Matrix& val);
	bool TryUpdateWorldMatrix()const{return mWorldMatrix.TryUpdate();}
	size_t WorldMatrixVersion()const{return mWorldMatrix.Version();}

	MoveableInheritFlags InheritFlag() const { return mInheritFlag; }
	void SetInheritFlag(MoveableInheritFlags val);

	bool IsInheritScale()const;
	void EnableInheritScale(bool val);

	bool IsInheritRotation()const;
	void EnableInheritRotation(bool val);
public:
	Point3F TransformToWorld(const Point3F& val)const;
	Rect2F TransformToWorld(const Rect2F& val)const;
	Point3F TransformToLocal(const Point3F& val)const;
	Point2F TransformToLocal(const Point2F& val)const;
	Rect2F TransformToLocal(const Rect2F& val)const;



	bool UpdateWorldMatrix(bool forceUpdateWorldMatrix = false);
	void UpdateWorldMatrixByInherit();

	const Matrix& WorldInverseMatrix()const { return mWorldInverseMatrix.Value(); }

	const BoundingBox& GetBoundingBox()const { return mBoundingBox.Value(); }
	const BoundingBox& WorldBoundingBox()const { return mWorldBoundingBox.Value(); }
	void ForceSetWorldBoundingBox(const BoundingBox& val);

	bool HitTestWorld(const Point2F& worldPos)const;
	virtual bool HitTestLocal(const Point2F& localPos)const;
protected:
	BoneMoveable* ParentMoveable() const { return mParentMoveable; }
	void SetParentMoveable(BoneMoveable* val);

	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags){}

private:
	void OnUpdateMatrix(Matrix& transform, int32 dirtyFlag);
	void OnUpdateWorldMatrix(Matrix& transform, int32 dirtyFlag);
	void OnUpdateWorldInverseMatrix(Matrix& transform, int32 dirtyFlag);
	void OnUpdateBoundingBox(BoundingBox& outVal, int32 dirtyFlag);
	void OnUpdateWorldBoundingBox(BoundingBox& outVal, int32 dirtyFlag);
protected:
	BoneMoveable* mParentMoveable;
	
	Size3F mSize;
	Point3F mPosition;
	Rotation3F mRotation;
	Scale3F mScale;
	FlipMask mFlip;

	Point3F mWorldPosition;
	Rotation3F mWorldRotation;
	Scale3F mWorldScale;
	FlipMask mWorldFlip;

	MoveableInheritFlags mInheritFlag;



	LazyMatrix mMatrix;
	LazyMatrix mWorldMatrix;
	LazyMatrix mWorldInverseMatrix;

	LazyBoundingBox mBoundingBox;	//self bounding box
	LazyBoundingBox mWorldBoundingBox;	//recursive bounding box
};

MEDUSA_END;