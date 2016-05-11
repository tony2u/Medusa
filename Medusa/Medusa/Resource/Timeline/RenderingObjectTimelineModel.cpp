// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderingObjectTimelineModel.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/ResourceNames.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Material/IMaterial.h"
#include "Rendering/RenderingObjectFactory.h"

MEDUSA_BEGIN;


RenderingObjectTimelineModel::RenderingObjectTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


RenderingObjectTimelineModel::~RenderingObjectTimelineModel(void)
{
	
}

bool RenderingObjectTimelineModel::InitializeWithSingleTexture(IMaterial* material, uint coloumn, uint row, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;

	const Size2U& textureSize = material->FirstTexture()->Size();

	Rect2F textureRect;
	textureRect.Size.Width = (float)textureSize.Width / coloumn;
	textureRect.Size.Height = (float)textureSize.Height / row;

	FOR_EACH_SIZE(i, row)
	{
		FOR_EACH_SIZE(j, coloumn)
		{
			textureRect.Origin.X = j*textureRect.Size.Width;
			textureRect.Origin.Y = i*textureRect.Size.Height;
			TextureQuadMesh* mesh = new TextureQuadMesh();
			mesh->Initialize(textureSize, textureRect);
			AddRenderingObjectWithInterval(frameInterval, RenderingObject(mesh,material));
		}
	}

	mDuration = row*coloumn*frameInterval;
	return true;
}

bool RenderingObjectTimelineModel::InitializeWithTextures(const SortedDictionary<uint, IMaterial*>& materials, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;
	RETURN_FALSE_IF_EMPTY(materials);

	FOR_EACH_COLLECTION_STL(i, materials.STLItems())
	{
		uint order = i->first;
		auto* material = i->second;
		RenderingObject renderingObject = RenderingObjectFactory::Instance().CreateFromSingleTextureMaterial(material);
		AddRenderingObject(frameInterval*order, renderingObject);
	}
	uint maxOrder = materials.LastKey();
	mDuration = frameInterval*(maxOrder + 1);
	return true;
}



bool RenderingObjectTimelineModel::InitializeWithTextureAtlas(IMaterial* material, const SortedDictionary<uint, IMesh*>& meshes, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;
	RETURN_FALSE_IF_EMPTY(meshes);

	FOR_EACH_COLLECTION_STL(i, meshes.STLItems())
	{
		uint order = i->first;
		auto* mesh = i->second;
		AddRenderingObject(frameInterval*order, RenderingObject(mesh,material));
	}
	uint maxOrder = meshes.LastKey();
	mDuration = frameInterval*(maxOrder + 1);
	return true;
}

bool RenderingObjectTimelineModel::InitializeWithObjects(SortedDictionary<uint, RenderingObject>& renderingObjects, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;
	RETURN_FALSE_IF_EMPTY(renderingObjects);

	FOR_EACH_COLLECTION_STL(i, renderingObjects.STLItems())
	{
		uint order = i->first;
		AddRenderingObject(frameInterval*order, i->second);
	}
	uint maxOrder = renderingObjects.LastKey();
	mDuration = frameInterval*(maxOrder + 1);
	return true;
}

bool RenderingObjectTimelineModel::InitializeWithObjects(List<RenderingObject>& renderingObjects, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;
	RETURN_FALSE_IF_EMPTY(renderingObjects);

	uint index = 0;
	for(auto& renderingObject: renderingObjects)
	{
		AddRenderingObject(frameInterval*index, renderingObject);
		++index;
	}

	uint maxOrder = renderingObjects.Count()-1;
	mDuration = frameInterval*(maxOrder + 1);
	return true;
}

const RenderingObject* RenderingObjectTimelineModel::GetItemByIndex(uint frame) const
{
	return &mObjects[frame];
}

const RenderingObject* RenderingObjectTimelineModel::GetItemByTime(float time) const
{
	intp index = GetSteppedFrameIndex(time);
	if (index<0)
	{
		return nullptr;
	}
	return GetItemByIndex((uint)index);
}

void RenderingObjectTimelineModel::AddRenderingObject(float time, const RenderingObject& val)
{
	mObjects.Add(val);

	uint frameIndex = (uint)mObjects.Count() - 1;
	AddFrame(time, frameIndex,Math::TweenType::None);
}

void RenderingObjectTimelineModel::AddRenderingObjectWithInterval(float frameInterval, const RenderingObject& val)
{
	mObjects.Add(val);
	uint frameIndex = (uint)mObjects.Count() - 1;
	AddFrameWithInterval(frameInterval, frameIndex, Math::TweenType::None);
}


MEDUSA_END;