// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Matrix.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/MoveableChangedFlags.h"

MEDUSA_BEGIN;

//model => local => world

class SRTMoveable
{
public:
	SRTMoveable();
	virtual ~SRTMoveable(void);

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

	Point3F WorldPosition()const;

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

	const Matrix& LocalMatrix()const{ return mMatrix.Value(); }
	void SetMatrix(const Matrix& val);
	bool IsMatrixDirty()const{return mMatrix.IsDirty();}

	const Matrix& WorldMatrix()const;
	bool IsWorldMatrixDirty()const;
	void ForceSetWorldMatrix(const Matrix& val);
	bool TryUpdateWorldMatrix()const{return mWorldMatrix.TryUpdate();}
	size_t WorldMatrixVersion()const{return mWorldMatrix.Version();}

public:
	Point3F TransformToWorld(const Point3F& val)const;
	Rect2F TransformToWorld(const Rect2F& val)const;
protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags){}

	SRTMoveable* ParentMoveable() const { return mParentMoveable; }
	void SetParentMoveable(SRTMoveable* val);
private:
	void OnUpdateMatrix(Matrix& transform, int32 dirtyFlag);
	void OnUpdateWorldMatrix(Matrix& transform, int32 dirtyFlag);

protected:
	SRTMoveable* mParentMoveable;
	
	Point3F mPosition;
	Rotation3F mRotation;
	Scale3F mScale;
	FlipMask mFlip;

	LazyMatrix mMatrix;
	LazyMatrix mWorldMatrix;
};

MEDUSA_END;