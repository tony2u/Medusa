// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LinesShape.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Resource/Material/MaterialFactory.h"

MEDUSA_BEGIN;


LinesShape::~LinesShape(void)
{

}

bool LinesShape::Initialize()
{
	return true;
}

void LinesShape::AppendPoints(const List<Point3F>& val)
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeGeneralMesh>();
	mesh->AppendVerticesAndIndexs(val);
	mesh->AppendColor(Color4F::White, (uint)val.Count());
}

void LinesShape::AppendPoint(const Point3F& val)
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeGeneralMesh>();
	mesh->AppendVertex(val);
	mesh->AppendIndex(mesh->VertexCount() - 1);
	mesh->AppendColor(Color4F::White);
}

void LinesShape::ClearPoints()
{
	auto mesh = mRenderingObject.Mesh().CastPtr<ShapeGeneralMesh>();
	mesh->Clear();
}

void LinesShape::AddLine(const Point3F& from, const Point3F& to)
{
	AppendPoint(from);
	AppendPoint(to);
}

MEDUSA_END;
