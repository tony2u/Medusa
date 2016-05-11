// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureQuadMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Node/Sprite/Sprite.h"
MEDUSA_BEGIN;

TextureQuadMesh::TextureQuadMesh( bool isStatic/*=false*/)
	:IMesh(isStatic)
{

}


TextureQuadMesh::~TextureQuadMesh(void)
{
}


void TextureQuadMesh::SetVertexBySize(const Size2F& val)
{
	mSize = val;

	mVertices[0] = Point3F::Zero;
	mVertices[1] = Point3F(val.Width, 0.f);
	mVertices[2] = Point3F(val.Width, val.Height);
	mVertices[3] = Point3F(0.f, val.Height);

	OnVertexChanged();


}

void TextureQuadMesh::SetTexcoordByRect(const Size2U& textureSize, const Rect2F& textureRect)
{
	mSize = textureRect.Size;

	float x = textureRect.Origin.X / textureSize.Width;
	float y = textureRect.Origin.Y / textureSize.Height;
	float w = textureRect.Size.Width / textureSize.Width;
	float h = textureRect.Size.Height / textureSize.Height;

	mTexcoords[0] = Point2F(x, y);
	mTexcoords[1] = Point2F(x + w, y);
	mTexcoords[2] = Point2F(x + w, y + h);
	mTexcoords[3] = Point2F(x, y + h);
	OnTexcoordChanged();

}

void TextureQuadMesh::Initialize(const Size2U& textureSize, const Rect2F& textureRect/*=Rect2F::Zero*/, const Color4F& color/*=Color4F::White*/)
{
	if (textureRect.IsEmpty())
	{
		SetVertexBySize(textureSize);
		SetTexcoordByRect(textureSize, Rect2F(Point2F::Zero, textureSize));
	}
	else
	{
		SetVertexBySize(textureRect.Size);
		SetTexcoordByRect(textureSize, textureRect);
	}
	SetColorAll(color);
}

void TextureQuadMesh::Initialize(const Rect2F& quadRect, const Rect2F& texcoord, const Color4F& color /*= Color4F::White*/)
{
	mSize = quadRect.Size;

	mVertices[0] = quadRect.LeftBottom();
	mVertices[1] = quadRect.RightBottom();
	mVertices[2] = quadRect.RightTop();
	mVertices[3] = quadRect.LeftTop();
	OnVertexChanged();


	mTexcoords[0] = texcoord.LeftBottom();
	mTexcoords[1] = texcoord.RightBottom();
	mTexcoords[2] = texcoord.RightTop();
	mTexcoords[3] = texcoord.LeftTop();
	OnTexcoordChanged();

	SetColorAll(color);
}

void TextureQuadMesh::Initialize(const List<Point3F>& vertices, const List<Point2F>& texcoords, const Color4F& color /*= Color4F::White*/)
{
	mSize.Width = vertices[1].X - vertices[0].X;
	mSize.Height = vertices[3].Y - vertices[0].Y;

	mVertices = vertices;
	OnVertexChanged();

	mTexcoords = texcoords;
	OnTexcoordChanged();

	SetColorAll(color);
}

INode* TextureQuadMesh::CreateCloneInstance() const
{
	Sprite* sprite = new Sprite();
	sprite->Mesh()->CopyFrom(*this);
	return sprite;
}

bool TextureQuadMesh::CopyFrom(const TextureQuadMesh& val)
{
	IMesh::CopyFrom(val);

	mVertices = val.Vertices();
	mTexcoords = val.Texcoords();
	mColors = val.Colors();
	mHasAlpha = val.HasAlpha();

	return true;
}



void TextureQuadMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	if (mFixType == MeshFixType::ForceToQuad)
	{
		RETURN_IF_EMPTY(mVertices);
		bufferObject.ReserveSize(vertexIndex, mVertices.Count());

		Array<Point3F, 4> tempVertices;

		const Point3F* verticesPtr = mVertices.Items();

		//Because it's horizontal, only need to calculate bottom-left and top-left position
		tempVertices[0] = matrix.Transform(verticesPtr[0]);
		tempVertices[2] = matrix.Transform(verticesPtr[2]);

		tempVertices[1].X = tempVertices[2].X;
		tempVertices[1].Y = tempVertices[0].Y;
		tempVertices[1].Z = tempVertices[0].Z;

		tempVertices[3].X = tempVertices[0].X;
		tempVertices[3].Y = tempVertices[2].Y;
		tempVertices[3].Z = tempVertices[0].Z;

		bufferObject.SetDataRange(vertexIndex, tempVertices);
	}
	else
	{
		TryUpdateVertex(bufferObject, vertexIndex, mVertices, matrix);
	}


}

void TextureQuadMesh::AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex) const
{
	bufferObject.SetDataRange(vertexIndex, mTexcoords);
}

void TextureQuadMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);

}

void TextureQuadMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	IndexGraphicsBuffer::ItemType indices[6] = { (IndexGraphicsBuffer::ItemType)vertexIndex, (IndexGraphicsBuffer::ItemType)(vertexIndex + 1), (IndexGraphicsBuffer::ItemType)(vertexIndex + 2), (IndexGraphicsBuffer::ItemType)(vertexIndex + 2), (IndexGraphicsBuffer::ItemType)(vertexIndex + 3), (IndexGraphicsBuffer::ItemType)vertexIndex };
	bufferObject.SetDataRange(indexIndex, (IndexGraphicsBuffer::ItemType*)indices, (size_t)6);

	//0,1,2,2,3,0,
	//bufferObject.AppendOrUpdateData(indexIndex,static_cast<ushort>(vertexIndex));
	//bufferObject.AppendOrUpdateData(indexIndex+1,static_cast<ushort>(vertexIndex+1));
	//bufferObject.AppendOrUpdateData(indexIndex+2,static_cast<ushort>(vertexIndex+2));

	//bufferObject.AppendOrUpdateData(indexIndex+3,static_cast<ushort>(vertexIndex+2));
	//bufferObject.AppendOrUpdateData(indexIndex+4,static_cast<ushort>(vertexIndex+3));
	//bufferObject.AppendOrUpdateData(indexIndex+5,static_cast<ushort>(vertexIndex));
}

void TextureQuadMesh::SetColor(uint i, const Color4F& val)
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

void TextureQuadMesh::SetColorAll(const Color4F& val)
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

void TextureQuadMesh::SetVertices(const List<Point3F>& val)
{
	mVertices = val;
	OnVertexChanged();

}

void TextureQuadMesh::SetTexcoords(const List<Point2F>& val)
{
	mTexcoords = val;
	OnTexcoordChanged();

}

void TextureQuadMesh::SetVertex(uint i, const Point3F& val)
{
	mVertices[i] = val;
	OnVertexChanged();

}

void TextureQuadMesh::SetTexcoord(uint i, const Point2F& val)
{
	mTexcoords[i] = val;
	OnTexcoordChanged();

}

MEDUSA_END;
