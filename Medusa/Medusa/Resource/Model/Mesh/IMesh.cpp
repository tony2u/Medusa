// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IMesh.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Matrix4.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"

MEDUSA_BEGIN;

IMesh::IMesh(bool isStatic/*=false*/)
	:mIsStatic(isStatic),
	mSize(Size3F::Zero)
{
	static uint id = 0;
	mId = ++id;
}

IMesh::~IMesh(void)
{
	
}

void IMesh::SetIsStatic(bool val)
{
	mIsStatic = val;
}

bool IMesh::CopyFrom(const IMesh& val)
{

	OnAllComponentChanged();

	return true;
}

bool IMesh::HasBlend() const
{
	return  mHasAlpha;
}

void IMesh::Clear()
{

}

void IMesh::OnVertexChanged()
{
	++mVersion.VertexMesion;
	OnMeshChanged(RenderableChangedFlags::NewVertex);
}

void IMesh::OnNormalChanged()
{
	++mVersion.NormalVersion;
	OnMeshChanged(RenderableChangedFlags::NewNormal);
}

void IMesh::OnTexcoordChanged()
{
	++mVersion.TexCoordVersion;
	OnMeshChanged(RenderableChangedFlags::NewTexCoord);
}

void IMesh::OnColorChanged()
{
	++mVersion.ColorVersion;
	OnMeshChanged(RenderableChangedFlags::NewColor);
}

void IMesh::OnIndexChanged()
{
	++mVersion.IndexVersion;
	OnMeshChanged(RenderableChangedFlags::NewIndex);
}

void IMesh::OnAllComponentChanged()
{
	mVersion.IncreaseAll();
	OnMeshChanged(RenderableChangedFlags::DataTotalChanged);
}


bool IMesh::TryUpdateVertex(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& vertices, const Matrix4& matrix) const
{
	RETURN_TRUE_IF_EMPTY(vertices);
	bufferObject.ReserveSize(vertexIndex, vertices.Count());

	size_t count = vertices.Count();
	const Point3F* verticesPtr = vertices.Items();
	FOR_EACH_SIZE(i, count)
	{
		Point3F pos = matrix.Transform(verticesPtr[i]);
		bufferObject.AppendOrUpdateData(vertexIndex + i, pos);
	}

	return true;
}

bool IMesh::TryUpdateNormal(NormalGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& normals, const Matrix4& matrix) const
{
	RETURN_TRUE_IF_EMPTY(normals);

	bufferObject.ReserveSize(vertexIndex, normals.Count());

	Matrix4 matrixCopy = matrix;

	//normal
	matrixCopy.Inverse();
	matrixCopy.Transpose();

	size_t count = normals.Count();
	const Point3F* itemsPtr = normals.Items();

	FOR_EACH_SIZE(i, count)
	{
		Point3F vec = matrixCopy.TransformVector(itemsPtr[i]);
		bufferObject.AppendOrUpdateData(vertexIndex + i, vec);
	}

	return true;
}

bool IMesh::TryUpdateColor(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Color4F>& colors, const Color4F& parentColor /*= Color4F::White*/) const
{
	RETURN_TRUE_IF_EMPTY(colors);
	bufferObject.ReserveSize(vertexIndex, colors.Count());

	if (parentColor == Color4F::White)
	{
		bufferObject.SetDataRange(vertexIndex, colors);
	}
	else
	{
		size_t count = colors.Count();
		const Color4F* itemsPtr = colors.Items();

		FOR_EACH_SIZE(i, count)
		{
			Color4F color = itemsPtr[i] * parentColor;
			bufferObject.AppendOrUpdateData(vertexIndex + i, color);
		}
	}

	return true;
}



MEDUSA_END;