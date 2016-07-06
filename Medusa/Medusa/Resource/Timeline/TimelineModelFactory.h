// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Timeline/ITimelineModel.h"
#include "Resource/Timeline/RenderingObjectTimelineModel.h"
#include "Resource/TextureAtlas/TextureAtlasDefines.h"
#include "Geometry/Color4.h"

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
	Share<RenderingObjectTimelineModel> CreateRenderingObjectFromSingleTexture(const StringRef& name, const FileIdRef& textureName, uint coloumn, uint row = 1, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);
	Share<RenderingObjectTimelineModel> CreateRenderingObjectFromTextureAtlas(const StringRef& name, const FileIdRef& atlasFileId,const StringRef& regionPattern,TextureAtlasType fileFormat = TextureAtlasType::None, const Color4F& color = Color4F::White, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);
	Share<RenderingObjectTimelineModel> CreateRenderingObjectFromTextures(const StringRef& name, const StringRef& textureNamePattern, float fps = 24.f, ResourceShareType shareType = ResourceShareType::Share);

	Share<ITimelineModel> CreateSkeletonFromModel(const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);
	Share<ITimelineModel> CreateCameraFromModel(const StringRef& cameraName,const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);
	Share<ITimelineModel> CreateLightFromModel(const StringRef& lightName,const StringRef& modelName,ResourceShareType shareType = ResourceShareType::Share);


};

MEDUSA_END;