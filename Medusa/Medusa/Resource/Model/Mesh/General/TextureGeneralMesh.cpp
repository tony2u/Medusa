// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureGeneralMesh.h"
#include "Core/Geometry/Vertex/TextureVertex.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Core/Geometry/Quad.h"
#include "Node/Sprite/Sprite.h"
#include "Core/Geometry/Matrix4.h"

MEDUSA_BEGIN;


TextureGeneralMesh::TextureGeneralMesh( bool isStatic/*=false*/) :IMesh(isStatic)
{

}


TextureGeneralMesh::~TextureGeneralMesh(void)
{
}

void TextureGeneralMesh::AppendIndex(uint index)
{
	mIndices.Append(index);
	OnIndexChanged();

}

void TextureGeneralMesh::AppendIndices(uint* items, uint count)
{
	mIndices.AppendRange(items, count);
	OnIndexChanged();

}


void TextureGeneralMesh::AppendQuadIndex()
{
	uint indexBegin = static_cast<uint>(VertexCount()) - 4;
	uint indices[6] = { indexBegin, indexBegin + 1, indexBegin + 2, indexBegin + 2, indexBegin + 3, indexBegin };
	AppendIndices(indices, 6);

}

void TextureGeneralMesh::AppendVertex(const Point3F& vertex, uint count/*=1*/)
{
	mVertices.Append(vertex, count);
	OnVertexChanged();

}

void TextureGeneralMesh::AppendTexcoord(const Point2F& texcoord, uint count/*=1*/)
{
	mTexcoords.Append(texcoord, count);
	OnTexcoordChanged();

}

void TextureGeneralMesh::AppendColor(const Color4F& color, uint count/*=1*/)
{
	mColors.Append(color, count);
	if (!Math::IsEqual(color.A, 1.f))
	{
		mHasAlpha = true;
	}

	OnColorChanged();

}

void TextureGeneralMesh::AppendQuad(const QuadTextureVertex& quad)
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
	const uint indices[6] = { indexBegin, indexBegin + 1, indexBegin + 2, indexBegin + 2, indexBegin + 3, indexBegin };
	mIndices.AppendRange(indices, 6);
	OnIndexChanged();


}

void TextureGeneralMesh::AppendVertices(const Point3F* vertices, size_t count)
{
	mVertices.AppendRange(vertices, count);
	OnVertexChanged();


}

void TextureGeneralMesh::AppendTexcoords(const Point2F* texcoords, size_t count)
{
	mTexcoords.AppendRange(texcoords, count);
	OnTexcoordChanged();

}

void TextureGeneralMesh::AppendQuadRawData2D(const float* vertices, const float* texcoords, const Color4F& color, bool isInvertTexcoordY /*= false*/)
{
	const static uint indices[6] = { 0, 1, 2, 2, 3, 0 };
	AppendRawData2D(vertices, texcoords, 8, indices, 6, color, isInvertTexcoordY);
}


void TextureGeneralMesh::AppendRawData2D(const float* vertices, const float* texcoords, uint vertexCount, const uint* indices, uint indexCount, const Color4F& color, bool isInvertTexcoordY /*= false*/)
{
	uint count = vertexCount / 2;
	FOR_EACH_SIZE(i, count)
	{
		Point3F pos(vertices[i * 2], vertices[i * 2 + 1]);
		mVertices.Append(pos);

		if (isInvertTexcoordY)
		{
			Point2F texcoord(texcoords[i * 2], 1.f - texcoords[i * 2 + 1]);
			mTexcoords.Append(texcoord);

		}
		else
		{
			Point2F texcoord(texcoords[i * 2], texcoords[i * 2 + 1]);
			mTexcoords.Append(texcoord);
		}
	}

	OnTexcoordChanged();
	OnVertexChanged();


	mColors.Append(color, count);
	if (!Math::IsEqual(color.A, 1.f))
	{
		mHasAlpha = true;
	}
	OnColorChanged();


	uint indexBegin = static_cast<uint>(VertexCount()) - 4;
	FOR_EACH_SIZE(i, indexCount)
	{
		mIndices.Append(indexBegin + indices[i]);
	}

	OnIndexChanged();


}


void TextureGeneralMesh::Clear()
{
	IMesh::Clear();
	mVertices.Clear();
	mTexcoords.Clear();
	mColors.Clear();
	mIndices.Clear();

	mHasAlpha = false;

}

INode* TextureGeneralMesh::CreateCloneInstance()const
{
	Sprite* sprite = new Sprite();
	sprite->Mesh()->CopyFrom(*this);
	return sprite;
}

void TextureGeneralMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	TryUpdateVertex(bufferObject,vertexIndex,mVertices, matrix);
	
}

void TextureGeneralMesh::AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex) const
{
	bufferObject.SetDataRange(vertexIndex, mTexcoords);
}

void TextureGeneralMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);
	
}

void TextureGeneralMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	size_t count = mIndices.Count();
	FOR_EACH_SIZE(i, count)
	{
		bufferObject.AppendOrUpdateData(indexIndex + i, static_cast<ushort>(vertexIndex + mIndices[i]));
	}
}

bool TextureGeneralMesh::CopyFrom(const TextureGeneralMesh& val)
{
	IMesh::CopyFrom(val);
	mVertices = val.Vertices();
	mTexcoords = val.Texcoords();
	mColors = val.Colors();
	mIndices = val.Indices();

	mHasAlpha = val.HasAlpha();

	return false;
}




MEDUSA_END;