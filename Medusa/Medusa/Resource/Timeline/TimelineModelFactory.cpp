// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TimelineModelFactory.h"
#include "Resource/Timeline/ITimelineModel.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/Model/Scene/BaseSceneModel.h"
#include "Resource/Timeline/MeshTimelineModel.h"
#include "Resource/Timeline/RenderingObjectTimelineModel.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Material/MaterialFactory.h"
#include "Rendering/RenderingObjectFactory.h"

MEDUSA_BEGIN;

TimelineModelFactory::TimelineModelFactory()
{

}

TimelineModelFactory::~TimelineModelFactory()
{

}

bool TimelineModelFactory::Initialize()
{
	return true;
}

bool TimelineModelFactory::Uninitialize()
{
	Clear();
	return true;
}



Share<ITimelineModel> TimelineModelFactory::CreateSkeletonFromModel(const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<ITimelineModel> item;
	if (shareType != ResourceShareType::None)
	{
		item = Find(modelName);
		RETURN_SELF_IF_NOT_NULL(item);
	}

	

	auto model = ModelFactory::Instance().Create(modelName).CastPtr<BaseSceneModel>();
	if (model != nullptr)
	{
		item = model->CreateSkeletonTimelineModel();
		Add(item, shareType);
	}
	return item;
}

Share<ITimelineModel> TimelineModelFactory::CreateCameraFromModel(const StringRef& cameraName, const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<ITimelineModel> item = nullptr;
	if (shareType != ResourceShareType::None)
	{
		item = Find(cameraName);
		RETURN_SELF_IF_NOT_NULL(item);
	}

	auto model = ModelFactory::Instance().Create(modelName).CastPtr<BaseSceneModel>();
	if (model != nullptr)
	{
		item = model->CreateCameraTimelineModel(cameraName);
		Add(item, shareType);
	}
	return item;
}

Share<ITimelineModel> TimelineModelFactory::CreateLightFromModel(const StringRef& lightName, const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<ITimelineModel> item;
	if (shareType != ResourceShareType::None)
	{
		item = Find(lightName);
		RETURN_SELF_IF_NOT_NULL(item);
	}

	auto model = ModelFactory::Instance().Create(modelName).CastPtr<BaseSceneModel>();
	if (model != nullptr)
	{
		item = model->CreateLightTimelineModel(lightName);
		Add(item, shareType);
	}
	return item;
}

Share<RenderingObjectTimelineModel> TimelineModelFactory::CreateRenderingObjectFromSingleTexture(const StringRef& name, const FileIdRef& textureName, uint coloumn, uint row/*=1*/, uint startIndex /*= 0*/, uint endIndex /*= Math::UIntMaxValue*/,float fps/*=24.f*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		Share<RenderingObjectTimelineModel> val = Find(name).CastPtr<RenderingObjectTimelineModel>();
		RETURN_SELF_IF_NOT_NULL(val);
	}

	auto material = MaterialFactory::Instance().CreateSingleTexture(textureName);
	Share<RenderingObjectTimelineModel> model = new RenderingObjectTimelineModel(name);
	model->InitializeWithSingleTexture(material, coloumn, row,startIndex,endIndex, fps);
	Add(model, shareType);

	return model;
}



Share<RenderingObjectTimelineModel> TimelineModelFactory::CreateRenderingObjectFromTextureAtlas(const StringRef& name,
																				const FileIdRef& atlasFileId,
																				 const StringRef& regionPattern,
																				 TextureAtlasType fileFormat /*= TextureAtlasType::None*/,
																				 const Color4F& color /*= Color4F::White*/,
																				 float fps /*= 24.f*/,
																				 ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		auto val = Find(name).CastPtr<RenderingObjectTimelineModel>();
		RETURN_SELF_IF_NOT_NULL(val);
	}


	SortedDictionary<uint, RenderingObject> outObjects;

	bool isSuccess = RenderingObjectFactory::Instance().CreateFromTextureAtlas(outObjects, regionPattern, atlasFileId, fileFormat, color);
	if (!isSuccess)
	{
		return nullptr;
	}

	Share<RenderingObjectTimelineModel> model = new RenderingObjectTimelineModel(name);
	model->InitializeWithObjects(outObjects, fps);
	Add(model, shareType);

	return model;
}

Share<RenderingObjectTimelineModel> TimelineModelFactory::CreateRenderingObjectFromTextures(const StringRef& name, const StringRef& textureNamePattern, float fps /*= 24.f*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		auto val = Find(name).CastPtr<RenderingObjectTimelineModel>();
		RETURN_SELF_IF_NOT_NULL(val);
	}
	List<RenderingObject> outObjects;
	bool isSuccess = RenderingObjectFactory::Instance().CreateFromTextures(outObjects, textureNamePattern);
	if (!isSuccess)
	{
		Log::FormatError("Cannot find textures with Pattern:{}", textureNamePattern);
		return nullptr;
	}



	Share<RenderingObjectTimelineModel> model = new RenderingObjectTimelineModel(name);
	model->InitializeWithObjects(outObjects, fps);
	Add(model, shareType);

	return model;
}




MEDUSA_END;
