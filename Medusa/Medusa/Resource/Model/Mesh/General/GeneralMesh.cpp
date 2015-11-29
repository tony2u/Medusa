// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GeneralMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Core/Geometry/Quad.h"
#include "Node/Sprite/Sprite.h"
#include "Core/Geometry/Matrix4.h"

#include "Core/Geometry/Vertex/TextureVertex.h"
#include "Core/Geometry/Vertex/TextureNormalVertex.h"

MEDUSA_BEGIN;


GeneralMesh::GeneralMesh( bool isStatic/*=false*/) :IMesh(isStatic)
{

}


GeneralMesh::~GeneralMesh(void)
{
}

void GeneralMesh::AppendIndex(uint index)
{
	mIndices.Append(index);
	OnIndexChanged();
}

void GeneralMesh::AppendIndices(uint* items, uint count)
{
	mIndices.AppendRange(items, count);
	OnIndexChanged();
}


void GeneralMesh::AppendQuadIndex()
{
	uint indexBegin = static_cast<uint>(VertexCount()) - 4;
	uint indices[6] = { indexBegin, indexBegin + 1, indexBegin + 2, indexBegin + 2, indexBegin + 3, indexBegin };
	AppendIndices(indices, 6);

}

void GeneralMesh::AppendVertex(const Point3F& vertex, uint count/*=1*/)
{
	mVertices.Append(vertex, count);
	OnVertexChanged();

}

void GeneralMesh::AppendNormal(const Point3F& normal, uint count/*=1*/)
{
	mNormals.Append(normal, count);
	OnNormalChanged();

}

void GeneralMesh::AppendTexcoord(const Point2F& texcoord, uint count/*=1*/)
{
	mTexcoords.Append(texcoord, count);
	OnTexcoordChanged();

}

void GeneralMesh::AppendColor(const Color4F& color, uint count/*=1*/)
{
	mColors.Append(color, count);
	if (!Math::IsEqual(color.A, 1.f))
	{
		mHasAlpha = true;
	}
	OnColorChanged();
}

void GeneralMesh::AppendQuad(const QuadTextureVertex& quad)
{
	mVertices.Append(quad.LeftBottom.Position);
	mVertices.Append(quad.RightBottom.Position);
	mVertices.Append(quad.RightTop.Position);
	mVertices.Append(quad.LeftTop.Position);
	OnVertexChanged();

	mTexcoords.Append(quad.LeftBottom.Texcoord);
	mTexcoords.Append(quad.RightBottom.Texcoord);
	mTexcoords.Append(quad.RightTop.Texcoord);
	mTexcoords.Append(quad.LeftTop.Texcoord);
	OnTexcoordChanged();

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

void GeneralMesh::AppendQuad(const QuadTextureNormalVertex& quad)
{
	mVertices.Append(quad.LeftBottom.Position);
	mVertices.Append(quad.RightBottom.Position);
	mVertices.Append(quad.RightTop.Position);
	mVertices.Append(quad.LeftTop.Position);
	OnVertexChanged();

	mNormals.Append(quad.LeftBottom.Normal);
	mNormals.Append(quad.RightBottom.Normal);
	mNormals.Append(quad.RightTop.Normal);
	mNormals.Append(quad.LeftTop.Normal);
	OnNormalChanged();

	mTexcoords.Append(quad.LeftBottom.Texcoord);
	mTexcoords.Append(quad.RightBottom.Texcoord);
	mTexcoords.Append(quad.RightTop.Texcoord);
	mTexcoords.Append(quad.LeftTop.Texcoord);
	OnTexcoordChanged();

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

void GeneralMesh::AppendVertices(const Point3F* vertices, size_t count)
{
	mVertices.AppendRange(vertices, count);
	OnVertexChanged();
}

void GeneralMesh::AppendTexcoords(const Point2F* texcoords, size_t count)
{
	mTexcoords.AppendRange(texcoords, count);
	OnTexcoordChanged();
}

void GeneralMesh::Clear()
{
	IMesh::Clear();
	mVertices.Clear();
	mTexcoords.Clear();
	mNormals.Clear();
	mColors.Clear();
	mIndices.Clear();
	mHasAlpha = false;
	OnAllComponentChanged();
}

INode* GeneralMesh::CreateCloneInstance()const
{
	Sprite* sprite = new Sprite();
	sprite->Mesh()->CopyFrom(*this);
	return sprite;
}

void GeneralMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	TryUpdateVertex(bufferObject, vertexIndex, mVertices, matrix);
}

void GeneralMesh::AddToNormalBufferObject(NormalGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	TryUpdateNormal(bufferObject, vertexIndex, mNormals, matrix);
}

void GeneralMesh::AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex) const
{
	bufferObject.SetDataRange(vertexIndex, mTexcoords);
}

void GeneralMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);
	
}

void GeneralMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	size_t count = mIndices.Count();
	FOR_EACH_SIZE(i, count)
	{
		bufferObject.AppendOrUpdateData(indexIndex + i, static_cast<ushort>(vertexIndex + mIndices[i]));
	}
}

bool GeneralMesh::CopyFrom(const GeneralMesh& val)
{
	IMesh::CopyFrom(val);
	mVertices = val.Vertices();
	mNormals = val.Normals();
	mTexcoords = val.Texcoords();
	mColors = val.Colors();
	mIndices = val.Indices();

	mHasAlpha = val.HasAlpha();

	return false;
}



MEDUSA_END;