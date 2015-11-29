// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/Cube.h"

MEDUSA_BEGIN;

class MatrixMoveable
{
public:
	MatrixMoveable();
	virtual ~MatrixMoveable(void);

	const Matrix4& GetMatrix()  { return mMatrix;}
	void SetMatrix(const Matrix4& val);
	bool IsMatrixDirty()const{return false;}

	const CubeF& GetBoundingBox() const { return mBoundingBox; }
	void SetBoundingBox(const CubeF& val){mBoundingBox=val;}

	const Matrix4& WorldMatrix(){return mWorldMatrix.Value();}
	bool IsWorldMatrixDirty()const{return mWorldMatrix.IsDirty();}
	void SetWorldMatrixDirty(){mWorldMatrix.SetDirty();mWorldInverseMatrix.SetDirty();}
	void ForceSetWorldMatrix(const Matrix4& val){mWorldMatrix=val;}
	bool TryUpdateWorldMatrix(){return mWorldMatrix.TryUpdate();}

	size_t WorldMatrixVersion()const{return mWorldMatrix.Version();}

	const Matrix4& GetWorldInverseMatrix(){return mWorldInverseMatrix.Value();}

protected:
	MatrixMoveable* ParentMoveable() const { return mParentMoveable; }
	void SetParentMoveable(MatrixMoveable* val) { mParentMoveable = val; }

	void OnUpdateWorldMatrix(Matrix4& transform, int32 dirtyFlag);
	void OnUpdateWorldInverseMatrix(Matrix4& transform, int32 dirtyFlag);

protected:
	MatrixMoveable* mParentMoveable;
	
	Matrix4 mMatrix;
	LazyMatrix4 mWorldMatrix;
	LazyMatrix4 mWorldInverseMatrix;

	CubeF mBoundingBox;	//self bounding box

};

MEDUSA_END;