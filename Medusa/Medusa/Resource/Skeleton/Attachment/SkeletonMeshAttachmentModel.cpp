// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonMeshAttachmentModel.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"

MEDUSA_BEGIN;


SkeletonMeshAttachmentModel::SkeletonMeshAttachmentModel(const StringRef& name, TextureAtlasRegion* region)
	:BaseSkeletonTextureAttachmentModel(name,region)
{
	
}


SkeletonMeshAttachmentModel::~SkeletonMeshAttachmentModel(void)
{
	
}

void SkeletonMeshAttachmentModel::AddVertex(const Point3F& pos)
{
	mMesh.AppendVertex(pos);
}

void SkeletonMeshAttachmentModel::AddTexcoord(const Point2F& val)
{
	mMesh.AppendTexcoord(val);
}

void SkeletonMeshAttachmentModel::AddIndex(uint val)
{
	mMesh.AppendIndex(val);
}

bool SkeletonMeshAttachmentModel::Initialize()
{
	return true;
}

RenderingObject SkeletonMeshAttachmentModel::GetRenderingObject() const
{
	return RenderingObject((IMesh*)&mMesh, mRegion->GetMaterial());
}


MEDUSA_END;

