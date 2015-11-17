// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IMesh.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Matrix.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"

MEDUSA_BEGIN;

IMesh::IMesh(IEffect* effect/*=nullptr*/, IMaterial* material/*=nullptr*/, bool isStatic/*=false*/)
	:mEffect(effect),
	mMaterial(material),
	mIsStatic(isStatic),
	mSize(Size3F::Zero)
{
	static uint id = 0;
	mId = ++id;

	SAFE_RETAIN(mEffect);
	SAFE_RETAIN(mMaterial);
}


IMesh::~IMesh(void)
{
	SAFE_RELEASE(mEffect);
	SAFE_RELEASE(mMaterial);
}


void IMesh::SetIsStatic(bool val)
{
	mIsStatic = val;
}


void IMesh::SetMaterial(const IMaterial* val)
{
	if (mMaterial != val)
	{
		SAFE_ASSIGN_REF(mMaterial, val);
		OnMeshChanged(RenderableChangedFlags::BatchChanged);
	}
}

void IMesh::SetEffect(const IEffect* val)
{
	if (mEffect != val)
	{
		SAFE_ASSIGN_REF(mEffect, val);
		OnMeshChanged(RenderableChangedFlags::BatchChanged);

	}
}

void IMesh::SetDrawMode(GraphicsDrawMode val)
{
	if (mDrawMode != val)
	{
		mDrawMode = val;
		OnMeshChanged(RenderableChangedFlags::BatchChanged);
	}
}

bool IMesh::CopyFrom(const IMesh& val)
{
	SetEffect(val.Effect());
	SetMaterial(val.Material());
	OnAllComponentChanged();

	return true;
}

bool IMesh::HasBlend() const
{
	RETURN_FALSE_IF_NULL(mMaterial);
	RETURN_FALSE_IF_NULL(mEffect);

	return mMaterial->IsBlendEnabled() || mHasAlpha;
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


bool IMesh::TryUpdateVertex(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& vertices, const Matrix& matrix) const
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

bool IMesh::TryUpdateNormal(NormalGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& normals, const Matrix& matrix) const
{
	RETURN_TRUE_IF_EMPTY(normals);

	bufferObject.ReserveSize(vertexIndex, normals.Count());

	Matrix matrixCopy = matrix;

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