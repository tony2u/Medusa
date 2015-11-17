// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureNineGridMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Node/Sprite/NineGridSprite.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

TextureNineGridMesh::TextureNineGridMesh(IEffect* effect/*=nullptr*/, IMaterial* material/*=nullptr*/, bool isStatic/*=false*/)
	:IMesh(effect, material, isStatic), mTargetSize(Size2F::Zero), mPadding(ThicknessF::Zero), mTextureRect(Rect2F::Zero)
{

}


TextureNineGridMesh::~TextureNineGridMesh(void)
{
}



void TextureNineGridMesh::Initialize(const Size2F& targetSize, const ThicknessF& padding, const Rect2F& textureRect/*=Rect2F::Zero*/, const Color4F& color/*=Color4F::White*/)
{
	mVertices.ClearZero();
	mTexcoords.ClearZero();
	mColors.ClearZero();

	RETURN_IF_EQUAL(mTargetSize, targetSize);

	mPadding = padding;
	mTextureRect = textureRect;

	UpdateToNewTargetSize(targetSize);

	SetColorAll(color);
}



void TextureNineGridMesh::UpdateToNewTargetSize(const Size2F& targetSize)
{
	/*
	0	1	2	3
	4	5	6	7
	8	9	10	11
	12	13	14	15
	*/


	RETURN_IF_EQUAL(mTargetSize, targetSize);

	if (Math::IsZero(targetSize.Width)||Math::IsZero(targetSize.Height))
	{
		return;
	}
	mTargetSize = targetSize;
	Size2U textureSize = mMaterial->FirstTexture()->Size();
	if (mTextureRect.IsEmpty())
	{
		mTextureRect.Size = textureSize;
	}

	mVertices[0].X = mVertices[4].X = mVertices[8].X = mVertices[12].X = 0.f;
	mVertices[1].X = mVertices[5].X = mVertices[9].X = mVertices[13].X = mPadding.Left;
	mVertices[2].X = mVertices[6].X = mVertices[10].X = mVertices[14].X = targetSize.Width - mPadding.Right;
	mVertices[3].X = mVertices[7].X = mVertices[11].X = mVertices[15].X = targetSize.Width;


	mVertices[0].Y = mVertices[1].Y = mVertices[2].Y = mVertices[3].Y = targetSize.Height;
	mVertices[4].Y = mVertices[5].Y = mVertices[6].Y = mVertices[7].Y = targetSize.Height - mPadding.Top;
	mVertices[8].Y = mVertices[9].Y = mVertices[10].Y = mVertices[11].Y = mPadding.Bottom;
	mVertices[12].Y = mVertices[13].Y = mVertices[14].Y = mVertices[15].Y = 0.f;


	mTexcoords[0].X = mTexcoords[4].X = mTexcoords[8].X = mTexcoords[12].X = mTextureRect.Origin.X / textureSize.Width;
	mTexcoords[1].X = mTexcoords[5].X = mTexcoords[9].X = mTexcoords[13].X = (mTextureRect.Origin.X + mPadding.Left) / textureSize.Width;
	mTexcoords[2].X = mTexcoords[6].X = mTexcoords[10].X = mTexcoords[14].X = (mTextureRect.Right() - mPadding.Right) / textureSize.Width;
	mTexcoords[3].X = mTexcoords[7].X = mTexcoords[11].X = mTexcoords[15].X = (mTextureRect.Right()) / textureSize.Width;

	mTexcoords[0].Y = mTexcoords[1].Y = mTexcoords[2].Y = mTexcoords[3].Y = mTextureRect.Origin.Y / textureSize.Height;
	mTexcoords[4].Y = mTexcoords[5].Y = mTexcoords[6].Y = mTexcoords[7].Y = (mTextureRect.Origin.Y + mPadding.Top) / textureSize.Height;
	mTexcoords[8].Y = mTexcoords[9].Y = mTexcoords[10].Y = mTexcoords[11].Y = (mTextureRect.Top() - mPadding.Bottom) / textureSize.Height;
	mTexcoords[12].Y = mTexcoords[13].Y = mTexcoords[14].Y = mTexcoords[15].Y = mTextureRect.Top() / textureSize.Height;

	OnVertexChanged();
	OnTexcoordChanged();

	mSize = targetSize;

}

INode* TextureNineGridMesh::CreateCloneInstance() const
{
	NineGridSprite* sprite = new NineGridSprite(StringRef::Empty);
	sprite->Mesh()->CopyFrom(*this);


	return sprite;
}

bool TextureNineGridMesh::CopyFrom(const TextureNineGridMesh& val)
{
	IMesh::CopyFrom(val);

	mVertices = val.Vertices();
	mTexcoords = val.Texcoords();
	mColors = val.Colors();
	mHasAlpha = val.HasAlpha();


	return true;
}



void TextureNineGridMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix) const
{
	TryUpdateVertex(bufferObject,vertexIndex,mVertices, matrix);
	
}

void TextureNineGridMesh::AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex) const
{
	bufferObject.SetDataRange(vertexIndex, mTexcoords);

}

void TextureNineGridMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);
	
}

void TextureNineGridMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	IndexGraphicsBuffer::ItemType indices[54];
	FOR_EACH_SIZE(i, 54)
	{
		indices[i] = (IndexGraphicsBuffer::ItemType)(vertexIndex + mIndices[i]);
	}

	bufferObject.SetDataRange(indexIndex, (IndexGraphicsBuffer::ItemType*)indices, (size_t)54);
}

void TextureNineGridMesh::SetColor(uint i, const Color4F& val)
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

void TextureNineGridMesh::SetColorAll(const Color4F& val)
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

void TextureNineGridMesh::SetVertices(const Array<Point3F, 16>& val)
{
	mVertices = val;
	OnVertexChanged();
}

void TextureNineGridMesh::SetTexcoords(const Array<Point2F, 16>& val)
{
	mTexcoords = val;
	OnTexcoordChanged();

}

void TextureNineGridMesh::SetVertex(uint i, const Point3F& val)
{
	mVertices[i] = val;
	OnVertexChanged();

}

void TextureNineGridMesh::SetTexcoord(uint i, const Point2F& val)
{
	mTexcoords[i] = val;
	OnTexcoordChanged();

}


/*
0	1	2	3
4	5	6	7
8	9	10	11
12	13	14	15
*/
const ushort TextureNineGridMesh::mIndices[54] = { 0, 4, 1, 1, 4, 5, 1, 5, 2, 2, 5, 6, 2, 6, 3, 3, 6, 7,
4, 8, 5, 5, 8, 9, 5, 9, 6, 6, 9, 10, 6, 10, 7, 7, 10, 11,
8, 12, 9, 9, 12, 13, 9, 13, 10, 10, 13, 14, 10, 14, 11, 11, 14, 15 };


MEDUSA_END;
