// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/TextureAtlas/TextureAtlasDefines.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;

class TimelineFactory :public Singleton < TimelineFactory >
{
	friend class Singleton < TimelineFactory > ;
public:
	TimelineFactory();
	~TimelineFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	RenderingObjectTimeline* CreateRenderingObjectTimelineFromTextures(const StringRef& modelName, const StringRef& textureNamePattern, float fps = 24.f, bool isRepeatForever = false);

	RenderingObjectTimeline* CreateRenderingObjectTimelineFromSingleTexture(const StringRef& modelName, const FileIdRef& textureName, uint coloumn, uint row = 1, float fps = 24.f, bool isRepeatForever = false);
	RenderingObjectTimeline* CreateRenderingObjectTimelineFromTextureAtlas(const FileIdRef& atlasFileId,const StringRef& regionPattern,TextureAtlasType fileFormat = TextureAtlasType::None, const Color4F& color = Color4F::White, float fps = 24.f, bool isRepeatForever = false);



};

MEDUSA_END;