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


MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one componet
*/
class ShapeGeneralMesh :public IMesh
{
public:
	ShapeGeneralMesh(bool isStatic = false);
	virtual ~ShapeGeneralMesh(void);
public:
	virtual size_t VertexCount()const override { return mVertices.Count(); }
	virtual size_t IndexCount()const override { return mIndices.Count(); }

	const List<Point3F>& Vertices()  const { return mVertices; }
	const List<Color4F>& Colors() const { return mColors; }
	const List<uint>& Indices() const { return mIndices; }


	void Initialize(const Size2F& rectSize, const Color4F& color);
	void Initialize(const Rect2F& rect, const Color4F& color);
	void Initialize(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	void Initialize(float width, float height, const Color4F& color);

	void InitializeBorder(const Size2F& rectSize, const Color4F& color);
	void InitializeBorder(const Rect2F& rect, const Color4F& color);
	void InitializeBorder(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	void InitializeBorder(float width, float height, const Color4F& color);

	void SetVertexBySize(const Size2F& val);
	void SetVertexByRect(const Rect2F& val);
	void ExpandVertexRectSize(const Size2F& val);

	void SetColorAll(const Color4F& val);

	void AppendQuad(const QuadShapeVertex& quad);

	void AppendVertex(const Point3F& vertex, uint count = 1);

	void AppendVertices(const Point3F* vertices, size_t count);

	void AppendColor(const Color4F& color, uint count = 1);

	void AppendQuadIndex();

	void AppendIndex(uint index);
	void AppendIndices(uint* items, uint count);
	virtual void Clear()override;

	virtual INode* CreateCloneInstance()const override;
public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix)const override;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const override;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const override;
public:
	bool CopyFrom(const ShapeGeneralMesh& val);

protected:
	List<Point3F> mVertices;
	List<Color4F> mColors;
	List<uint> mIndices;
};

MEDUSA_END;