// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Timeline/ITimelineModel.h"
#include "Resource/TextureAtlas/TextureAtlasTypes.h"
#include "Core/Geometry/Color4.h"

MEDUSA_BEGIN;

class TimelineModelFactory:public Singleton<TimelineModelFactory>,public BaseResourceFactory<ITimelineModel>
{
	friend class Singleton<TimelineModelFactory>;
public:
	TimelineModelFactory();
	~TimelineModelFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	MeshTimelineModel* CreateMeshFromSingleTexture(const StringRef& name, const FileIdRef& textureName, uint coloumn, uint row = 1, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);
	MeshTimelineModel* CreateMeshFromTextureAtlas(const StringRef& name, const StringRef& regionPattern,const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat = TextureAtlasFileFormat::Spine, uint atlasPageCount = 1, const Color4F& color = Color4F::White, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);
	MeshTimelineModel* CreateMeshFromTextures(const StringRef& name, const StringRef& textureNamePattern, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);

	ITimelineModel* CreateSkeletonFromModel(const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);
	ITimelineModel* CreateCameraFromModel(const StringRef& cameraName,const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);
	ITimelineModel* CreateLightFromModel(const StringRef& lightName,const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);
};

MEDUSA_END;