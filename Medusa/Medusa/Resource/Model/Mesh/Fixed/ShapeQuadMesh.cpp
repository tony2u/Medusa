// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShapeQuadMesh.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
#include "Core/Geometry/Matrix4.h"

MEDUSA_BEGIN;

ShapeQuadMesh::ShapeQuadMesh( bool isStatic/*=false*/)
	:IMesh(isStatic)
{

}


ShapeQuadMesh::~ShapeQuadMesh(void)
{
}



void ShapeQuadMesh::Initialize(const Size2F& rectSize, const Color4F& color)
{
	SetVertexBySize(rectSize);
	SetColorAll(color);
}

void ShapeQuadMesh::Initialize(const Rect2F& rect, const Color4F& color)
{
	SetVertexByRect(rect);
	SetColorAll(color);
}

void ShapeQuadMesh::SetVertexBySize(const Size2F& val)
{
	mSize = val;

	mVertices[0] = Point3F::Zero;
	mVertices[1] = Point3F(val.Width, 0.f);
	mVertices[2] = Point3F(val.Width, val.Height);
	mVertices[3] = Point3F(0.f, val.Height);

	OnVertexChanged();


}

void ShapeQuadMesh::SetVertexByRect(const Rect2F& val)
{
	mSize = val.Size;

	mVertices[0] = val.Origin;
	mVertices[1] = val.RightBottom();
	mVertices[2] = val.RightTop();
	mVertices[3] = val.LeftTop();

	OnVertexChanged();

}

INode* ShapeQuadMesh::CreateCloneInstance() const
{
	return nullptr;
}

void ShapeQuadMesh::AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix) const
{
	if (mFixType == MeshFixType::ForceToQuad)
	{
		RETURN_IF_EMPTY(mVertices);
		bufferObject.ReserveSize(vertexIndex, mVertices.Count());

		Array<Point3F, 4> tempVertices;

		const Point3F* verticesPtr = mVertices.Items();

		//because horizontal, only need to calculate bottom-left and top-left positions
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


void ShapeQuadMesh::AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor/*=Color4F::White*/) const
{
	TryUpdateColor(bufferObject, vertexIndex, mColors, parentColor);

}

void ShapeQuadMesh::AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex) const
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


bool ShapeQuadMesh::CopyFrom(const ShapeQuadMesh& val)
{
	IMesh::CopyFrom(val);

	mVertices = val.GetVertices();
	mColors = val.GetColors();
	mHasAlpha = val.HasAlpha();

	return true;
}

void ShapeQuadMesh::SetColor(uint i, const Color4F& val)
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

void ShapeQuadMesh::SetColorAll(const Color4F& val)
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

void ShapeQuadMesh::SetVertices(const Array<Point3F, 4>& val)
{
	mVertices = val;
	OnVertexChanged();
}

void ShapeQuadMesh::SetVertex(uint i, const Point3F& val)
{
	mVertices[i] = val;
	OnVertexChanged();
}



MEDUSA_END;