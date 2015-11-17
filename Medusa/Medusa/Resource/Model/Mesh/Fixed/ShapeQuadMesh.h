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
We choose separate buffer instead of interleaved, because we want to update only one componet
*/
class ShapeQuadMesh :public IMesh
{
public:
	ShapeQuadMesh(IEffect* effect = nullptr, IMaterial* material = nullptr, bool isStatic = false);
	virtual ~ShapeQuadMesh(void);
public:

	virtual size_t VertexCount()const { return 4; }
	virtual size_t IndexCount()const { return 6; }

	Array<Point3F, 4>& MutableVertices() { return mVertices; }

	const Array<Point3F, 4>& GetVertices()  const { return mVertices; }
	const Array<Color4F, 4>& GetColors() const { return mColors; }

	void SetVertices(const Array<Point3F, 4>& val);


	void SetVertex(uint i, const Point3F& val);
	void SetVertexBySize(const Size2F& val);
	void SetVertexByRect(const Rect2F& val);

	void SetColor(uint i, const Color4F& val);
	void SetColorAll(const Color4F& val);

	void Initialize(const Size2F& rectSize, const Color4F& color);
	void Initialize(const Rect2F& rect, const Color4F& color);

	virtual INode* CreateCloneInstance()const;

public:
	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix)const;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const;

public:
	bool CopyFrom(const ShapeQuadMesh& val);

protected:
	Array<Point3F, 4> mVertices;
	Array<Color4F, 4> mColors;
};

MEDUSA_END;