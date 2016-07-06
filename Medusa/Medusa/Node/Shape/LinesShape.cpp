// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LinesShape.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Resource/Material/MaterialFactory.h"

MEDUSA_BEGIN;


LinesShape::~LinesShape( void )
{

}

bool LinesShape::Initialize()
{
	return true;
}

void LinesShape::AppendPoint(const Point3F& val)
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeGeneralMesh>();
	mesh->AppendVertexAndIndex(val);
	mesh->AppendColor(Color4F::White);
}

void LinesShape::ClearPoints()
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeGeneralMesh>();
	mesh->Clear();
}

MEDUSA_END;
