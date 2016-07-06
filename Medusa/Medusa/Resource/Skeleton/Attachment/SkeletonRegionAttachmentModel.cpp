// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonRegionAttachmentModel.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Geometry/Matrix2.h"
#include "Geometry/Matrix4.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"

MEDUSA_BEGIN;


SkeletonRegionAttachmentModel::SkeletonRegionAttachmentModel(const StringRef& name, TextureAtlasRegion* region)
	:BaseSkeletonTextureAttachmentModel(name,region),
	mPosition(Point3F::Zero),
	mRotation(Rotation3F::Zero),
	mScale(Scale3F::One)
{
	mMesh.Retain();
}


SkeletonRegionAttachmentModel::~SkeletonRegionAttachmentModel(void)
{
	
}

bool SkeletonRegionAttachmentModel::Initialize()
{
	RETURN_FALSE_IF_NULL(mRegion);

	const Size2U& regionOriginalSize=mRegion->OriginalSize();

	Scale3F realScale = mScale;
	realScale.X *= mSize.Width / regionOriginalSize.Width;
	realScale.Y *= mSize.Height / regionOriginalSize.Height;

	const auto& vertexes=mRegion->Vertices();
	
	Matrix4 matrix = Matrix4::CreateWorld(mSize, Point3F::Half, realScale, Rotation2F::Zero,mRotation, mPosition);

	auto& vertices= mMesh.MutableVertices();
	FOR_EACH_SIZE(i, vertices.Size)
	{
		vertices[i] = matrix.Transform(vertexes[i]);
	}

	mMesh.SetColorAll(mColor);
	mMesh.SetTexcoords(mRegion->Texcoords());
	mMesh.SetSize(regionOriginalSize);
	return true;
}

RenderingObject SkeletonRegionAttachmentModel::GetRenderingObject() const
{
	return RenderingObject(Share<IMesh>((IMesh*)&mMesh), mRegion->CreateMaterial());
}


MEDUSA_END;