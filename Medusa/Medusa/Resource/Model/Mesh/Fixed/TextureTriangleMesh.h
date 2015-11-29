// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Color4.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one component
*/
class TextureTriangleMesh :public IMesh
{
public:
	TextureTriangleMesh( bool isStatic = false);
	virtual ~TextureTriangleMesh(void);
public:


	virtual size_t VertexCount()const { return 3; }
	virtual size_t IndexCount()const { return 3; }

	const Array<Point3F, 3>& Vertices()  const { return mVertices; }
	const Array<Point2F, 3>& Texcoords() const { return mTexcoords; }
	const Array<Color4F, 3>& Colors() const { return mColors; }

	void SetVertex(uint i, const Point3F& val);
	void SetTexcoord(uint i, const Point2F& val);

	void SetColor(uint i, const Color4F& val);
	void SetColorAll(const Color4F& val);

	virtual INode* CreateCloneInstance()const;
public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix)const;
	virtual void AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex)const;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const;

public:
	bool CopyFrom(const TextureTriangleMesh& val);
protected:
	Array<Point3F, 3> mVertices;
	Array<Point2F, 3> mTexcoords;
	Array<Color4F, 3> mColors;
};

MEDUSA_END;