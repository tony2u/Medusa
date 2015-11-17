// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TimelineFactory.h"
#include "MeshTimeline.h"
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

MeshTimeline* TimelineFactory::CreateMeshTimelineFromTextures(const StringRef& modelName, const StringRef& textureNamePattern, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	MeshTimelineModel* model = TimelineModelFactory::Instance().CreateMeshFromTextures(modelName, textureNamePattern,fps);
	MeshTimeline* ani = new MeshTimeline(model, isRepeatForever);
	return ani;
}

MeshTimeline* TimelineFactory::CreateMeshTimelineFromSingleTexture(const StringRef& modelName, const FileIdRef& textureName, uint coloumn, uint row/*=1*/, float fps/*=24.f*/, bool isRepeatForever /*= false*/)
{
	MeshTimelineModel* model = TimelineModelFactory::Instance().CreateMeshFromSingleTexture(modelName, textureName, coloumn, row, fps);
	MeshTimeline* ani = new MeshTimeline(model, isRepeatForever);
	return ani;
}

MeshTimeline* TimelineFactory::CreateMeshTimelineFromTextureAtlas(const StringRef& name, const StringRef& regionPattern, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	MeshTimelineModel* model = TimelineModelFactory::Instance().CreateMeshFromTextureAtlas(name, regionPattern, atlasFileId, fileFormat, atlasPageCount, color, fps);
	MeshTimeline* ani = new MeshTimeline(model, isRepeatForever);
	return ani;
}

MeshTimeline* TimelineFactory::CreateMeshTimelineFromTextureAtlasDefault(const StringRef& name, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, const Color4F& color /*= Color4F::White*/, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	FileId atlasFileId;
	atlasFileId.Name = name;
	atlasFileId.Name += ".atlas";
	return CreateMeshTimelineFromTextureAtlas(name, name, atlasFileId, fileFormat, atlasPageCount, color, fps, isRepeatForever);
}


MEDUSA_END;

