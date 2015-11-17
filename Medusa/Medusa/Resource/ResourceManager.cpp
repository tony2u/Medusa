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


MEDUSA_BEGIN;

ResourceManager::ResourceManager(void)
{
	mResourceFactories.Add(&TimelineModelFactory::Instance());
	mResourceFactories.Add(&CameraFactory::Instance());
	mResourceFactories.Add(&RenderPassFactory::Instance());
	mResourceFactories.Add(&ShaderFactory::Instance());
	mResourceFactories.Add(&EffectFactory::Instance());
	mResourceFactories.Add(&FontFactory::Instance());
	mResourceFactories.Add(&ImageFactory::Instance());
	mResourceFactories.Add(&LightFactory::Instance());
	mResourceFactories.Add(&MaterialFactory::Instance());
	mResourceFactories.Add(&ModelFactory::Instance());
	mResourceFactories.Add(&RenderTargetFactory::Instance());
	mResourceFactories.Add(&TextureFactory::Instance());
	mResourceFactories.Add(&AudioFactory::Instance());
	mResourceFactories.Add(&TextureAtlasFactory::Instance());
	mResourceFactories.Add(&SkeletonModelFactory::Instance());

}

ResourceManager::~ResourceManager(void)
{
}

bool ResourceManager::Initialize()
{
	FOR_EACH_COLLECTION(i, mResourceFactories)
	{
		IResourceManageable* item = *i;
		RETURN_FALSE_IF_FALSE(item->Initialize());
	}

	return true;
}


bool ResourceManager::Uninitialize()
{
	FOR_EACH_COLLECTION(i, mResourceFactories)
	{
		IResourceManageable* item = *i;
		RETURN_FALSE_IF_FALSE(item->Uninitialize());
	}

	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());
	
	return true;
}


void ResourceManager::Clear()
{
	FOR_EACH_ITEM_TO(mResourceFactories, Clear());
}


void ResourceManager::Shrink()
{
	FOR_EACH_ITEM_TO(mResourceFactories, Shrink());
}


void ResourceManager::ReleaseCache()
{
	FOR_EACH_ITEM_TO(mResourceFactories, ReleaseCache());
}

void ResourceManager::OnUpdate(float dt)
{
	Shrink();
}


MEDUSA_END;