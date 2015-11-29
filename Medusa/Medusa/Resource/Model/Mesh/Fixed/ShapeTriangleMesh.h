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
class ShapeTriangleMesh :public IMesh
{
public:
	ShapeTriangleMesh( bool isStatic = false);
	virtual ~ShapeTriangleMesh(void);
public:


	virtual size_t VertexCount()const { return 3; }
	virtual size_t IndexCount()const { return 3; }

	const Array<Point3F, 3>& Vertices()  const { return mVertices; }
	const Array<Color4F, 3>& Colors() const { return mColors; }

	void SetVertex(uint i, const Point3F& val);

	void SetColor(uint i, const Color4F& val);
	void SetColorAll(const Color4F& val);

	virtual INode* CreateCloneInstance()const;
	bool CopyFrom(const ShapeTriangleMesh& val);

	void Initialize(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	void Initialize(float width, float height, const Color4F& color);

public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix4& matrix)const;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const;

protected:
	Array<Point3F, 3> mVertices;
	Array<Color4F, 3> mColors;

};

MEDUSA_END;