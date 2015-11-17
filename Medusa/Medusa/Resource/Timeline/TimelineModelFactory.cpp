// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TimelineModelFactory.h"
#include "Resource/Timeline/ITimelineModel.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/Model/Scene/BaseSceneModel.h"
#include "Resource/Timeline/MeshTimelineModel.h"
#include "Resource/Model/Mesh/MeshFactory.h"

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



ITimelineModel* TimelineModelFactory::CreateSkeletonFromModel(const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	ITimelineModel* item = Find(modelName);
	RETURN_SELF_IF_NOT_NULL(item);

	BaseSceneModel* model = (BaseSceneModel*)ModelFactory::Instance().Create(modelName);
	if (model != nullptr)
	{
		item = model->CreateSkeletonTimelineModel();
		Add(item, shareType);
	}
	return item;
}

ITimelineModel* TimelineModelFactory::CreateCameraFromModel(const StringRef& cameraName, const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	ITimelineModel* item = Find(cameraName);
	RETURN_SELF_IF_NOT_NULL(item);

	BaseSceneModel* model = (BaseSceneModel*)ModelFactory::Instance().Create(modelName);
	if (model != nullptr)
	{
		item = model->CreateCameraTimelineModel(cameraName);
		Add(item, shareType);
	}
	return item;
}

ITimelineModel* TimelineModelFactory::CreateLightFromModel(const StringRef& lightName, const StringRef& modelName, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	ITimelineModel* item = Find(lightName);
	RETURN_SELF_IF_NOT_NULL(item);

	BaseSceneModel* model = (BaseSceneModel*)ModelFactory::Instance().Create(modelName);
	if (model != nullptr)
	{
		item = model->CreateLightTimelineModel(lightName);
		Add(item, shareType);
	}
	return item;
}

MeshTimelineModel* TimelineModelFactory::CreateMeshFromSingleTexture(const StringRef& name, const FileIdRef& textureName, uint coloumn, uint row/*=1*/, float fps/*=24.f*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		ITimelineModel* val = Find(name);
		RETURN_SELF_IF_NOT_NULL((MeshTimelineModel*)val);
	}


	MeshTimelineModel* model = new MeshTimelineModel(name);
	model->InitializeWithSingleTexture(textureName, coloumn, row, fps);
	Add(model, shareType);

	return model;
}



MeshTimelineModel* TimelineModelFactory::CreateMeshFromTextureAtlas(const StringRef& name,
																				 const StringRef& regionPattern,
																				 const FileIdRef& atlasFileId,
																				 TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/,
																				 uint atlasPageCount /*= 1*/,
																				 const Color4F& color /*= Color4F::White*/,
																				 float fps /*= 24.f*/,
																				 ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		ITimelineModel* val = Find(name);
		RETURN_SELF_IF_NOT_NULL((MeshTimelineModel*)val);
	}


	SortedDictionary<uint, TextureQuadMesh*> outMeshes;
	bool isSuccess = MeshFactory::Instance().CreateTextureQuadMeshesFromAtlas(outMeshes, regionPattern, atlasFileId, fileFormat, atlasPageCount, color);
	if (!isSuccess)
	{
		return nullptr;
	}

	MeshTimelineModel* model = new MeshTimelineModel(name);
	model->InitializeWithMeshes(outMeshes, fps);
	Add(model, shareType);

	return model;
}

MeshTimelineModel* TimelineModelFactory::CreateMeshFromTextures(const StringRef& name, const StringRef& textureNamePattern, float fps /*= 24.f*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		ITimelineModel* val = Find(name);
		RETURN_SELF_IF_NOT_NULL((MeshTimelineModel*)val);
	}

	SortedDictionary<uint, TextureQuadMesh*> outMeshes;
	bool isSuccess = MeshFactory::Instance().CreateTextureQuadMeshesFromTextures(outMeshes, textureNamePattern);
	if (!isSuccess|| outMeshes.IsEmpty())
	{
		Log::FormatError("Cannot find textures with Pattern:{}", textureNamePattern);
		return nullptr;
	}

	MeshTimelineModel* model = new MeshTimelineModel(name);
	model->InitializeWithMeshes(outMeshes, fps);
	Add(model, shareType);

	return model;
}

MEDUSA_END;
