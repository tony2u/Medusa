// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureTriangleMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Core/Geometry/Matrix.h"

MEDUSA_BEGIN;


TextureTriangleMesh::TextureTriangleMesh(IEffect* effect/*=nullptr*/, IMaterial* material/*=nullptr*/, bool isStatic/*=false*/)
	:IMesh(effect, material, isStatic)
{

}


TextureTriangleMesh::~TextureTriangleMesh(void)
{
}


INode* TextureTriangleMesh::CreateCloneInstance()const
{
	return nullptr;
}


void TextureTriangleMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix) const
{
	TryUpdateVertex(bufferObject,vertexIndex,mVertices, matrix);
	
}


void TextureTriangleMesh::AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex) const
{
	bufferObject.SetDataRange(vertexIndex, mTexcoords);
}

void TextureTriangleMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);
	
}

void TextureTriangleMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
{
	IndexGraphicsBuffer::ItemType indices[3] = { (IndexGraphicsBuffer::ItemType)vertexIndex, (IndexGraphicsBuffer::ItemType)(vertexIndex + 1), (IndexGraphicsBuffer::ItemType)(vertexIndex + 2) };
	bufferObject.SetDataRange(indexIndex, (IndexGraphicsBuffer::ItemType*)indices, (size_t)3);
}

void TextureTriangleMesh::SetColor(uint i, const Color4F& val)
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

void TextureTriangleMesh::SetColorAll(const Color4F& val)
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

bool TextureTriangleMesh::CopyFrom(const TextureTriangleMesh& val)
{
	IMesh::CopyFrom(val);

	mVertices = val.Vertices();
	mTexcoords = val.Texcoords();
	mColors = val.Colors();
	mHasAlpha = val.HasAlpha();

	return true;
}

void TextureTriangleMesh::SetVertex(uint i, const Point3F& val)
{
	mVertices[i] = val;
	OnVertexChanged();

}

void TextureTriangleMesh::SetTexcoord(uint i, const Point2F& val)
{
	mTexcoords[i] = val;
	OnTexcoordChanged();

}



MEDUSA_END;