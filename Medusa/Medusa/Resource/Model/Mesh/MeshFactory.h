// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Thickness.h"
#include "Core/Geometry/Size2.h"
#include "Resource/TextureAtlas/TextureAtlasTypes.h"
#include "Core/Collection/SortedDictionary.h"

MEDUSA_BEGIN;

class MeshFactory :public Singleton<MeshFactory>
{
	friend class Singleton<MeshFactory>;
public:
	MeshFactory();
	~MeshFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	ShapeQuadMesh* CreateShapeQuadMesh(const Size2F& rectSize, const Color4F& color);
	ShapeQuadMesh* CreateShapeQuadMesh(const Rect2F& rect, const Color4F& color);

	ShapeTriangleMesh* CreateShapeTriangleMesh(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	ShapeTriangleMesh* CreateShapeTriangleMesh(float width, float height, const Color4F& color);
	ShapeGeneralMesh* CreateShapeCircleMesh(float radius,float precision, const Color4F& color);



	TextureQuadMesh* CreateTextureQuadMesh(const Size2F& textureSize, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);
	TextureQuadMesh* CreateTextureQuadMesh(const FileIdRef& textureName, const FileMapOrderItem& orderItem, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);

	TextureQuadMesh* CreateTextureQuadMeshFromAtlasRegion(TextureAtlasRegion* region, const Color4F& color = Color4F::White);


	TextureNineGridMesh* CreateTextureNineGridMesh(const Size2F& targetSize, const Size2F& textureSize, const ThicknessF& padding, const Rect2F& textureRect = Rect2F::Zero, const Color4F& color = Color4F::White);
	TextureGeneralMesh* CreateTextureGeneralMesh(ITexture* texture, bool isStatic = false);



};

MEDUSA_END;