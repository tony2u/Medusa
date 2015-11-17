// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Resource/TextureAtlas/TextureAtlasTypes.h"
#include "Core/Geometry/Color4.h"

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
	MeshTimeline* CreateMeshTimelineFromTextures(const StringRef& modelName, const StringRef& textureNamePattern, float fps = 24.f, bool isRepeatForever = false);

	MeshTimeline* CreateMeshTimelineFromSingleTexture(const StringRef& modelName, const FileIdRef& textureName, uint coloumn, uint row = 1, float fps = 24.f, bool isRepeatForever = false);
	MeshTimeline* CreateMeshTimelineFromTextureAtlas(const StringRef& name, const StringRef& regionPattern,const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat = TextureAtlasFileFormat::Spine, uint atlasPageCount = 1, const Color4F& color = Color4F::White, float fps = 24.f, bool isRepeatForever = false);
	MeshTimeline* CreateMeshTimelineFromTextureAtlasDefault(const StringRef& name, TextureAtlasFileFormat fileFormat = TextureAtlasFileFormat::Spine, uint atlasPageCount = 1, const Color4F& color = Color4F::White, float fps = 24.f, bool isRepeatForever = false);



};

MEDUSA_END;