// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonSkinnedMeshAttachmentModel.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"

MEDUSA_BEGIN;


SkeletonSkinnedMeshAttachmentModel::SkeletonSkinnedMeshAttachmentModel(const StringRef& name, TextureAtlasRegion* region)
	:BaseSkeletonTextureAttachmentModel(name, region)
{
}


SkeletonSkinnedMeshAttachmentModel::~SkeletonSkinnedMeshAttachmentModel(void)
{
	
}

void SkeletonSkinnedMeshAttachmentModel::AddTexcoord(const Point2F& val)
{
	mMesh.AppendTexcoord(val);
}

void SkeletonSkinnedMeshAttachmentModel::AddIndex(uint val)
{
	mMesh.AppendIndex(val);
}

void SkeletonSkinnedMeshAttachmentModel::AddWeight(const VertexWeightInfo& val)
{
	mWeights.Add(val);
}

bool SkeletonSkinnedMeshAttachmentModel::Initialize()
{
	return true;
}

RenderingObject SkeletonSkinnedMeshAttachmentModel::GetRenderingObject() const
{
	return RenderingObject(Share<IMesh>((IMesh*)&mMesh), mRegion->CreateMaterial());
}


MEDUSA_END;