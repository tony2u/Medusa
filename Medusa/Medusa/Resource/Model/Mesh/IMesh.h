// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "MeshComponentVersions.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Size3.h"
#include "Rendering/RenderingFlags.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/RenderableChangedFlags.h"
#include "Core/Geometry/Matrix.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;


class IMesh :public ISharableThreadSafe
{
public:
	IMesh(IEffect* effect = nullptr, IMaterial* material = nullptr, bool isStatic = false);
	virtual ~IMesh(void);

	Event<void(RenderableChangedFlags)> OnMeshChanged;
public:
	uint Id()const { return mId; }
	bool IsStatic() const { return mIsStatic; }
	virtual void SetIsStatic(bool val);

	bool IsValid()const { return mEffect != nullptr&&mMaterial != nullptr; }
	const IEffect* Effect() const { return mEffect; }
	void SetEffect(const IEffect* val);

	const IMaterial* Material() const { return mMaterial; }
	void SetMaterial(const IMaterial* val);

	virtual bool HasBlend()const;
	bool HasAlpha() const { return mHasAlpha; }
	void ForceSetHasAlpha(bool val) { mHasAlpha = val; }	//mHasAlpha will be calculated automatically inside,but you can change it forcedly

	const Size3F& Size() const { return mSize; }
	void SetSize(const Size3F& val) { mSize = val; }

	GraphicsDrawMode DrawMode() const { return mDrawMode; }
	void SetDrawMode(GraphicsDrawMode val);

	const MeshComponentVersions& Version() const { return mVersion; }
	MeshComponentVersions& MutableVersion() { return mVersion; }

	MeshFixType FixType() const { return mFixType; }
	void SetFixType(MeshFixType val) { mFixType = val; }


	virtual size_t VertexCount()const = 0;
	virtual size_t IndexCount()const = 0;
	virtual bool HasNormal()const { return false; }

	virtual void Clear();
	virtual INode* CreateCloneInstance()const = 0;
	bool CopyFrom(const IMesh& val);


	virtual void AddToVertexBufferObject(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix)const {};
	virtual void AddToNormalBufferObject(NormalGraphicsBuffer& bufferObject, size_t vertexIndex, const Matrix& matrix)const {};
	virtual void AddToTexCoordBufferObject(TexCoordGraphicsBuffer& bufferObject, size_t vertexIndex)const {};
	virtual void AddToColorBufferObject(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const Color4F& parentColor = Color4F::White)const {};
	virtual void AddToIndexBufferObject(IndexGraphicsBuffer& bufferObject, size_t vertexIndex, size_t indexIndex)const {};

	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) {}
	virtual void Apply() {}
	virtual void Restore() {}

	virtual void OnVertexChanged();
	virtual void OnNormalChanged();
	virtual void OnTexcoordChanged();
	virtual void OnColorChanged();
	virtual void OnIndexChanged();
	virtual void OnAllComponentChanged();

protected:
	bool TryUpdateVertex(VertexGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& vertices, const Matrix& matrix) const;
	bool TryUpdateNormal(NormalGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Point3F>& normals, const Matrix& matrix ) const;
	bool TryUpdateColor(ColorGraphicsBuffer& bufferObject, size_t vertexIndex, const ICollection<Color4F>& colors, const Color4F& parentColor = Color4F::White) const;
protected:
	uint mId;
	const IEffect* mEffect=nullptr;	//batch
	const IMaterial* mMaterial=nullptr;	//batch
	GraphicsDrawMode mDrawMode= GraphicsDrawMode::Triangles;//batch

	bool mHasAlpha=false;
	bool mIsStatic=false;
	Size3F mSize;

	MeshComponentVersions mVersion;
	MeshFixType mFixType= MeshFixType::None;
};

MEDUSA_END;