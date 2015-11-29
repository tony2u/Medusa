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


MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one component
*/
class TextureGeneralMesh :public IMesh
{
public:
	TextureGeneralMesh( bool isStatic = false);
	virtual ~TextureGeneralMesh(void);
public:
	virtual size_t VertexCount()const override { return mVertices.Count(); }
	virtual size_t IndexCount()const override { return mIndices.Count(); }

	const List<Point3F>& Vertices()  const { return mVertices; }
	const List<Point2F>& Texcoords() const { return mTexcoords; }
	const List<Color4F>& Colors() const { return mColors; }
	const List<uint>& Indices() const { return mIndices; }

	List<Point3F>& MutableVertices() { return mVertices; }
	List<Point2F>& MutableTexcoords() { return mTexcoords; }
	List<Color4F>& MutableColors() { return mColors; }
	List<uint>& MutableIndices() { return mIndices; }

	void AppendQuad(const QuadTextureVertex& quad);

	void AppendVertex(const Point3F& vertex, uint count = 1);

	void AppendVertices(const Point3F* vertices, size_t count);

	void AppendTexcoord(const Point2F& texcoord, uint count = 1);
	void AppendTexcoords(const Point2F* texcoords, size_t count);

	void AppendColor(const Color4F& color, uint count = 1);

	void AppendQuadIndex();

	void AppendIndex(uint index);
	void AppendIndices(uint* items, uint count);

	void AppendQuadRawData2D(const float* vertices, const float* texcoords, const Color4F& color, bool isInvertTexcoordY = false);

	void AppendRawData2D(const float* vertices, const float* texcoords, uint vertexCount, const uint* indices, uint indexCount, const Color4F& color, bool isInvertTexcoordY = false);

	virtual void Clear()override;

	virtual INode* CreateCloneInstance()const override;
public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix)const override;
	virtual void AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex)const override;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const override;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const override;
public:
	bool CopyFrom(const TextureGeneralMesh& val);

protected:

	List<Point3F> mVertices;
	List<Point2F> mTexcoords;
	List<Color4F> mColors;
	List<uint> mIndices;


};

MEDUSA_END;