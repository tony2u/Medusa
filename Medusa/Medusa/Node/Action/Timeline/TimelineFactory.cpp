// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TimelineFactory.h"
#include "MeshTimeline.h"
#include "RenderingObjectTimeline.h"
#include "Resource/Timeline/TimelineModelFactory.h"


MEDUSA_BEGIN;

TimelineFactory::TimelineFactory()
{

}

TimelineFactory::~TimelineFactory()
{

}

bool TimelineFactory::Initialize()
{
	return true;
}

bool TimelineFactory::Uninitialize()
{
	return true;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromTextures(const StringRef& modelName, const StringRef& textureNamePattern, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	RenderingObjectTimelineModel* model = TimelineModelFactory::Instance().CreateRenderingObjectFromTextures(modelName, textureNamePattern,fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	return ani;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromSingleTexture(const StringRef& modelName, const FileIdRef& textureName, uint coloumn, uint row/*=1*/, float fps/*=24.f*/, bool isRepeatForever /*= false*/)
{
	RenderingObjectTimelineModel* model = TimelineModelFactory::Instance().CreateRenderingObjectFromSingleTexture(modelName, textureName, coloumn, row, fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	return ani;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromTextureAtlas(const StringRef& name, const StringRef& regionPattern, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	RenderingObjectTimelineModel* model = TimelineModelFactory::Instance().CreateMeshFromTextureAtlas(name, regionPattern, atlasFileId, fileFormat, atlasPageCount, color, fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	return ani;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromTextureAtlasDefault(const StringRef& name, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	FileId atlasFileId;
	atlasFileId.Name = name;
	atlasFileId.Name += ".atlas";
	return CreateRenderingObjectTimelineFromTextureAtlas(name, name, atlasFileId, fileFormat, atlasPageCount, color, fps, isRepeatForever);
}


MEDUSA_END;

