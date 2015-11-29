// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShapeTriangleMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Core/Geometry/Matrix4.h"
MEDUSA_BEGIN;


ShapeTriangleMesh::ShapeTriangleMesh( bool isStatic/*=false*/)
	:IMesh(isStatic)
{

}


ShapeTriangleMesh::~ShapeTriangleMesh(void)
{
}



INode* ShapeTriangleMesh::CreateCloneInstance()const
{
	return nullptr;
}


void ShapeTriangleMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	TryUpdateVertex(bufferObject,vertexIndex,mVertices, matrix);
	
}


void ShapeTriangleMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);
	
}

void ShapeTriangleMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	IndexGraphicsBuffer::ItemType indices[3] = { (IndexGraphicsBuffer::ItemType)vertexIndex, (IndexGraphicsBuffer::ItemType)(vertexIndex + 1), (IndexGraphicsBuffer::ItemType)(vertexIndex + 2) };
	bufferObject.SetDataRange(indexIndex, (IndexGraphicsBuffer::ItemType*)indices, (size_t)3);
}

bool ShapeTriangleMesh::CopyFrom(const ShapeTriangleMesh& val)
{
	IMesh::CopyFrom(val);

	mVertices = val.Vertices();
	mColors = val.Colors();
	mHasAlpha = val.HasAlpha();
	return true;
}

void ShapeTriangleMesh::Initialize(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color)
{
	SetColorAll(color);
	SetVertex(0, p1);
	SetVertex(1, p2);
	SetVertex(2, p3);
}

void ShapeTriangleMesh::Initialize(float width, float height, const Color4F& color)
{
	Point3F p1(0.f, width*0.5f, 0.f);
	Point3F p2(0.f, -width*0.5f, 0.f);
	Point3F p3(height, 0.f, 0.f);
	Initialize(p1, p2, p3, color);
}

void ShapeTriangleMesh::SetColor(uint i, const Color4F& val)
{
	if (!Math::IsEqual(val.A, 1.f))
	{
		mHasAlpha = true;
		mColors[i] = val;

	}
	else
	{
		mColors[i] = val;
		mHasAlpha = false;
		FOR_EACH_SIZE(j, mColors.Size)
		{
			mHasAlpha |= !Math::IsEqual(mColors[j].A, 1.f);
		}
	}


	OnColorChanged();

}

void ShapeTriangleMesh::SetColorAll(const Color4F& val)
{
	mColors.SetAll(val);
	OnColorChanged();
	if (!Math::IsEqual(val.A, 1.f))
	{
		mHasAlpha = true;
	}
	else
	{
		mHasAlpha = false;
	}

}

void ShapeTriangleMesh::SetVertex(uint i, const Point3F& val)
{
	mVertices[i] = val;
	OnVertexChanged();
}




MEDUSA_END;