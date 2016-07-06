// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ResourceManager.h"
#include "Resource/Timeline/TimelineModelFactory.h"
#include "Resource/Camera/CameraFactory.h"
#include "Resource/Effect/Pass/RenderPassFactory.h"
#include "Resource/Effect/Shader/ShaderFactory.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/Image/ImageFactory.h"
#include "Resource/Light/LightFactory.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Resource/Texture/TextureFactory.h"
#include "Resource/Audio/AudioFactory.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Resource/Skeleton/SkeletonModelFactory.h"
#include "Resource/Map/Tiled/TiledMapFactory.h"
#include "Resource/Map/Tiled/TiledTilesetFactory.h"

MEDUSA_BEGIN;

ResourceManager::ResourceManager(void)
{
	mResourceFactories.Add(&TimelineModelFactory::Instance());
	mResourceFactories.Add(&CameraFactory::Instance());
	mResourceFactories.Add(&ShaderFactory::Instance());
	mResourceFactories.Add(&RenderPassFactory::Instance());
	mResourceFactories.Add(&EffectFactory::Instance());
	mResourceFactories.Add(&ImageFactory::Instance());
	mResourceFactories.Add(&LightFactory::Instance());
	mResourceFactories.Add(&TextureFactory::Instance());
	mResourceFactories.Add(&MaterialFactory::Instance());
	mResourceFactories.Add(&ModelFactory::Instance());
	mResourceFactories.Add(&RenderTargetFactory::Instance());
	mResourceFactories.Add(&FontFactory::Instance());

#ifdef MEDUSA_AL
	mResourceFactories.Add(&AudioFactory::Instance());
#endif

	mResourceFactories.Add(&TextureAtlasFactory::Instance());
	mResourceFactories.Add(&SkeletonModelFactory::Instance());

	mResourceFactories.Add(&TiledMapFactory::Instance());
	mResourceFactories.Add(&TiledTilesetFactory::Instance());


}

ResourceManager::~ResourceManager(void)
{
}

bool ResourceManager::Initialize()
{
	for(auto item: mResourceFactories)
	{
		RETURN_FALSE_IF_FALSE(item->Initialize());
	}

	return true;
}


bool ResourceManager::Uninitialize()
{
	//reverse order
	int count = (int)mResourceFactories.Count();
	FOR_EACH_INT32_END_BEGIN(i, count - 1, 0)
	{
		auto item = mResourceFactories[i];
		RETURN_FALSE_IF_FALSE(item->Uninitialize());
	}
	

	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());
	
	return true;
}


void ResourceManager::Clear()
{
	FOR_EACH_TO(mResourceFactories, Clear());
}


void ResourceManager::Shrink()
{
	FOR_EACH_TO(mResourceFactories, Shrink());
}


void ResourceManager::ReleaseCache()
{
	FOR_EACH_TO(mResourceFactories, ReleaseCache());
}

void ResourceManager::OnUpdate(float dt)
{
	Shrink();
}


MEDUSA_END;