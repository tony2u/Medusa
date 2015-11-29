// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MeshTimelineModel.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/ResourceNames.h"
MEDUSA_BEGIN;


MeshTimelineModel::MeshTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


MeshTimelineModel::~MeshTimelineModel(void)
{
	SAFE_RELEASE_COLLECTION(mMeshes);
}

bool MeshTimelineModel::InitializeWithSingleTexture(const FileIdRef& textureName, uint coloumn, uint row, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;

	IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(textureName);
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
			AddMeshWithInterval(frameInterval, mesh);
		}
	}

	mDuration = row*coloumn*frameInterval;
	return true;
}

bool MeshTimelineModel::InitializeWithMeshes(SortedDictionary<uint, TextureQuadMesh*>& meshes, float fps /*= 24.f*/)
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	float frameInterval = 1.f / fps;
	RETURN_FALSE_IF_EMPTY(meshes);

	FOR_EACH_COLLECTION_STL(i, meshes.STLItems())
	{
		uint order = i->first;
		TextureQuadMesh* mesh = i->second;
		AddMesh(frameInterval*order, mesh);
	}
	uint maxOrder = meshes.LastKey();
	mDuration = frameInterval*(maxOrder+1);
	return true;
}


IMesh* MeshTimelineModel::GetMeshByIndex(uint frame) const
{
	return mMeshes[frame];
}

IMesh* MeshTimelineModel::GetMeshByTime(float time) const
{
	intp index = GetSteppedFrameIndex(time);
	if (index<0)
	{
		return nullptr;
	}
	return GetMeshByIndex((uint)index);
}

void MeshTimelineModel::AddMesh(float time, IMesh* mesh)
{
	SAFE_RETAIN(mesh);
	mMeshes.Add(mesh);
	uint frameIndex = (uint)mMeshes.Count() - 1;
	AddFrame(time, frameIndex,Math::TweenType::None);
}

void MeshTimelineModel::AddMeshWithInterval(float frameInterval, IMesh* mesh)
{
	SAFE_RETAIN(mesh);
	mMeshes.Add(mesh);
	uint frameIndex = (uint)mMeshes.Count() - 1;
	AddFrameWithInterval(frameInterval, frameIndex, Math::TweenType::None);
}


MEDUSA_END;