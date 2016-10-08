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
	auto model = TimelineModelFactory::Instance().CreateRenderingObjectFromTextures(modelName, textureNamePattern, fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	ani->SetName(modelName);
	return ani;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromSingleTexture(const StringRef& modelName, const FileIdRef& textureName, uint coloumn, uint row/*=1*/, uint startIndex /*= 0*/, uint endIndex /*= Math::UIntMaxValue*/, float fps/*=24.f*/, bool isRepeatForever /*= false*/)
{
	auto model = TimelineModelFactory::Instance().CreateRenderingObjectFromSingleTexture(modelName, textureName, coloumn, row, startIndex, endIndex, fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	ani->SetName(modelName);
	return ani;
}

RenderingObjectTimeline* TimelineFactory::CreateRenderingObjectTimelineFromTextureAtlas(const FileIdRef& atlasFileId, const StringRef& regionPattern, TextureAtlasType fileFormat /*= TextureAtlasFileFormat::Spine*/, const Color4F& color /*= Color4F::White*/, float fps /*= 24.f*/, bool isRepeatForever /*= false*/)
{
	auto model = TimelineModelFactory::Instance().CreateRenderingObjectFromTextureAtlas(atlasFileId.Name, atlasFileId, regionPattern, fileFormat, color, fps);
	RenderingObjectTimeline* ani = new RenderingObjectTimeline(model, isRepeatForever);
	ani->SetName(atlasFileId.Name);
	return ani;
}



MEDUSA_END;

