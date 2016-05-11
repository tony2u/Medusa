// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Geometry/Color4.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Collection/Array.h"
#include "Geometry/Rect2.h"
#include "Geometry/Thickness.h"


MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one component
*/
class TextureNineGridMesh :public IMesh
{
public:
	TextureNineGridMesh( bool isStatic = false);
	virtual ~TextureNineGridMesh(void);
public:
	virtual size_t VertexCount()const { return 16; }
	virtual size_t IndexCount()const { return 54; }

	const Array<Point3F, 16>& Vertices()  const { return mVertices; }
	const Array<Point2F, 16>& Texcoords() const { return mTexcoords; }
	const Array<Color4F, 16>& Colors() const { return mColors; }

	Array<Point3F, 16>& MutableVertices() { return mVertices; }
	Array<Point2F, 16>& MutableTexcoords() { return mTexcoords; }


	void SetVertices(const Array<Point3F, 16>& val);
	void SetTexcoords(const Array<Point2F, 16>& val);


	void SetVertex(uint i, const Point3F& val);
	void SetTexcoord(uint i, const Point2F& val);

	void SetColor(uint i, const Color4F& val);
	void SetColorAll(const Color4F& val);

	void Initialize(const Size2F& targetSize, const Size2F& textureSize, const ThicknessF& padding, const Rect2F& textureRect = Rect2F::Zero, RotateDirection rotation = RotateDirection::None, const Color4F& color = Color4F::White);

	void UpdateToNewTargetSize(const Size2F& targetSize);
	void UpdateToNewTextureSize(const Size2F& textureSize, RotateDirection rotation = RotateDirection::None);
	



	virtual INode* CreateCloneInstance()const;

public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix)const;
	virtual void AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex)const;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const;

public:
	bool CopyFrom(const TextureNineGridMesh& val);

protected:
	Array<Point3F, 16> mVertices;
	Array<Point2F, 16> mTexcoords;
	Array<Color4F, 16> mColors;

	const static ushort mIndices[54];

	Size2F mTargetSize;

	ThicknessF mPadding;
	Rect2F mTextureRect;
};

MEDUSA_END;