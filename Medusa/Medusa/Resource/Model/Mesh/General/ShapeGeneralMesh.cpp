// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShapeGeneralMesh.h"
#include "Core/Geometry/Vertex/ShapeVertex.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Core/Geometry/Quad.h"
#include "Node/Sprite/Sprite.h"
#include "Core/Geometry/Matrix4.h"

MEDUSA_BEGIN;


ShapeGeneralMesh::ShapeGeneralMesh(bool isStatic/*=false*/)
	:IMesh(isStatic)
{

}


ShapeGeneralMesh::~ShapeGeneralMesh(void)
{
}

void ShapeGeneralMesh::Initialize(const Size2F& rectSize, const Color4F& color)
{
	mSize = rectSize;
	SetVertexBySize(rectSize);
	SetColorAll(color);
}

void ShapeGeneralMesh::Initialize(const Rect2F& rect, const Color4F& color)
{
	mSize = rect.Size;
	SetVertexByRect(rect);
	SetColorAll(color);

}
void ShapeGeneralMesh::Initialize(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color)
{
	SetColorAll(color);

	mVertices.Add(p1);
	mVertices.Add(p2);
	mVertices.Add(p3);
	OnVertexChanged();

	uint indices[6] = { 0, 1, 2 };
	mIndices.AppendRange(indices, 3);
	OnIndexChanged();

}

void ShapeGeneralMesh::Initialize(float width, float height, const Color4F& color)
{
	Point3F p1(0.f, width*0.5f, 0.f);
	Point3F p2(0.f, -width*0.5f, 0.f);
	Point3F p3(height, 0.f, 0.f);
	Initialize(p1, p2, p3, color);
}


void ShapeGeneralMesh::ExpandVertexRectSize(const Size2F& val)
{
	Point3F origin = mVertices[0];
	SetVertexByRect(Rect2F(origin.To2D(), val));
}


void ShapeGeneralMesh::SetVertexBySize(const Size2F& val)
{
	SetVertexByRect(Rect2F(Point2F::Zero, val));
}

void ShapeGeneralMesh::SetVertexByRect(const Rect2F& val)
{
	mVertices.Clear();
	mVertices.NewAdd() = val.Origin;
	mVertices.NewAdd() = val.RightBottom();
	mVertices.NewAdd() = val.RightTop();
	mVertices.NewAdd() = val.LeftTop();
	OnVertexChanged();

	mIndices.Clear();
	const uint indices[6] = { 0, 1, 2, 2, 3, 0 };
	mIndices.AppendRange(indices, 6);
	OnIndexChanged();
}


void ShapeGeneralMesh::SetColorAll(const Color4F& val)
{
	mHasAlpha = !Math::IsEqual(val.A, 1.f);
	mColors.ForceReserveCount(VertexCount());
	mColors.SetAll(val);
	OnColorChanged();
}


void ShapeGeneralMesh::AppendIndex(uint index)
{
	mIndices.Append(index);
	OnIndexChanged();
}

void ShapeGeneralMesh::AppendIndices(uint* items, uint count)
{
	mIndices.AppendRange(items, count);
	OnIndexChanged();
}


void ShapeGeneralMesh::AppendQuadIndex()
{
	uint indexBegin = static_cast<uint>(VertexCount()) - 4;
	uint indices[6] = { indexBegin, indexBegin + 1, indexBegin + 2, indexBegin + 2, indexBegin + 3, indexBegin };
	AppendIndices(indices, 6);

}

void ShapeGeneralMesh::AppendVertex(const Point3F& vertex, uint count/*=1*/)
{
	mVertices.Append(vertex, count);
	OnVertexChanged();

}

void ShapeGeneralMesh::AppendColor(const Color4F& color, uint count/*=1*/)
{
	mColors.Append(color, count);
	if (!Math::IsEqual(color.A, 1.f))
	{
		mHasAlpha = true;
	}
	OnColorChanged();

}

void ShapeGeneralMesh::AppendQuad(const QuadShapeVertex& quad)
{
	mVertices.Append(quad.LeftBottom.Position);
	mVertices.Append(quad.RightBottom.Position);
	mVertices.Append(quad.RightTop.Position);
	mVertices.Append(quad.LeftTop.Position);
	OnVertexChanged();

	mColors.Append(quad.LeftBottom.Color);
	if (!Math::IsEqual(quad.LeftBottom.Color.A, 1.f))
	{
		mHasAlpha = true;
	}
	mColors.Append(quad.RightBottom.Color);
	if (!Math::IsEqual(quad.RightBottom.Color.A, 1.f))
	{
		mHasAlpha = true;
	}
	mColors.Append(quad.RightTop.Color);
	if (!Math::IsEqual(quad.RightTop.Color.A, 1.f))
	{
		mHasAlpha = true;
	}
	mColors.Append(quad.LeftTop.Color);
	if (!Math::IsEqual(quad.LeftTop.Color.A, 1.f))
	{
		mHasAlpha = true;
	}
	OnColorChanged();

	uint indexBegin = static_cast<uint>(VertexCount()) - 4;
	uint indices[6] = { indexBegin, indexBegin + 1, indexBegin + 2, indexBegin + 2, indexBegin + 3, indexBegin };
	mIndices.AppendRange(indices, 6);
	OnIndexChanged();
}

void ShapeGeneralMesh::AppendVertices(const Point3F* vertices, size_t count)
{
	mVertices.AppendRange(vertices, count);
	OnVertexChanged();

}


void ShapeGeneralMesh::Clear()
{
	IMesh::Clear();

	mVertices.Clear();
	mColors.Clear();
	mIndices.Clear();

	mHasAlpha = false;
	OnAllComponentChanged();


}

INode* ShapeGeneralMesh::CreateCloneInstance()const
{
	Sprite* sprite = new Sprite();
	sprite->Mesh()->CopyFrom(*this);
	return sprite;
}

void ShapeGeneralMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	TryUpdateVertex(bufferObject, vertexIndex, mVertices, matrix);

}


void ShapeGeneralMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);


}

void ShapeGeneralMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	size_t count = mIndices.Count();
	FOR_EACH_SIZE(i, count)
	{
		bufferObject.AppendOrUpdateData(indexIndex + i, static_cast<ushort>(vertexIndex + mIndices[i]));
	}
}

bool ShapeGeneralMesh::CopyFrom(const ShapeGeneralMesh& val)
{
	IMesh::CopyFrom(val);
	mVertices = val.Vertices();
	mColors = val.Colors();
	mIndices = val.Indices();
	mHasAlpha = val.HasAlpha();

	return false;
}



MEDUSA_END;