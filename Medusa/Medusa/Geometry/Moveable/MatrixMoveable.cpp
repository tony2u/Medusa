// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MatrixMoveable.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


MatrixMoveable::MatrixMoveable()
	:mParentMoveable(nullptr),mMatrix(Matrix4::Identity), mWorldMatrix(Matrix4::Identity)
{
	mWorldMatrix.SetUpdateDelegate(Bind(&MatrixMoveable::OnUpdateWorldMatrix,this));
	mWorldInverseMatrix.SetUpdateDelegate(Bind(&MatrixMoveable::OnUpdateWorldInverseMatrix,this));

}


MatrixMoveable::~MatrixMoveable(void)
{
}


void MatrixMoveable::OnUpdateWorldMatrix(Matrix4& transform, int32 dirtyFlag)
{
	if (mParentMoveable != nullptr&&mParentMoveable->IsWorldMatrixDirty())
	{
		ForceSetWorldMatrix(GetMatrix()*(mParentMoveable->WorldMatrix()));
	}
	else
	{
		ForceSetWorldMatrix(GetMatrix());
	}
}


void MatrixMoveable::OnUpdateWorldInverseMatrix(Matrix4& transform, int32 dirtyFlag)
{
	transform=mWorldMatrix.Value();
	transform.Inverse();
}

void MatrixMoveable::SetMatrix( const Matrix4& val )
{
	mMatrix=val;
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
}


MEDUSA_END;