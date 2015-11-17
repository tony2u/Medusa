// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/Mesh/Font/BaseFontMesh.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Color4.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Font/FontCharQuad.h"
#include "Graphics/Buffer/ListGraphicsBuffer.h"
#include "Graphics/Buffer/QuadIndexGraphicsBuffer.h"


MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one component
*/
class FntTextMesh :public BaseFontMesh
{
public:
	FntTextMesh(IEffect* effect = nullptr, IMaterial* material = nullptr, bool isStatic = false);
	virtual ~FntTextMesh(void);
public:
	virtual void SetIsStatic(bool val)override;

	virtual size_t VertexCount()const override { return mVertexTexcoordBuffer.Count() * 4; }
	virtual size_t IndexCount()const override { return mIndexBuffer.Count(); }
	virtual void Clear()override;

	virtual INode* CreateCloneInstance()const override;
	bool CopyFrom(const FntTextMesh& val);

	virtual void ReserveMesh(uint charCount)override;
	virtual void ShrinkMesh()override;

	virtual void AddFontChar(const IFont& font, const FontChar& fontChar, const Point3F& origin)override;

	virtual void Apply()override;
	virtual void Restore()override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None)override;

	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix)const override;
	virtual void AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex)const override;
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const override;
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const override;

	virtual Point2F GetCharPosition(uint charIndex)const override;
	virtual Point2F GetCursorPosition(uint charIndex)const override;
	virtual uint FindCharIndex(const Point2F& touchPosition, Point2F& outCharPosition)const override;

	virtual bool HasChars()const override { return mCharCount > 0; }
protected:
	ListGraphicsBuffer<FontCharQuad> mVertexTexcoordBuffer;
	List<Point3F> mPositions;
	List<wchar_t> mChars;

	QuadIndexGraphicsBuffer mIndexBuffer;
	uint mCharIndex=0;	//current char index
	uint mCharCount=0;
};

MEDUSA_END;