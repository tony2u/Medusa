// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseSkeletonTextureAttachmentModel.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Collection/Array.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"

MEDUSA_BEGIN;


class SkeletonRegionAttachmentModel :public BaseSkeletonTextureAttachmentModel
{
public:
	SkeletonRegionAttachmentModel(const StringRef& name, TextureAtlasRegion* region);
	virtual ~SkeletonRegionAttachmentModel();
	virtual SkeletonAttachmentType Type()const override{ return SkeletonAttachmentType::Region; }
	virtual bool Initialize() override;


	const Point3F& Position() const { return mPosition; }
	void SetPosition(const Point3F& val) { mPosition = val; }

	const Rotation3F& Rotation() const { return mRotation; }
	void SetRotation(Rotation3F& val) { mRotation = val; }

	const Scale3F& Scale() const { return mScale; }
	void SetScale(Scale3F& val) { mScale = val; }

	const TextureQuadMesh& Mesh() const { return mMesh; }
	virtual RenderingObject GetRenderingObject()const;


protected:
	Point3F mPosition;
	Rotation3F mRotation;
	Scale3F mScale;

	TextureQuadMesh mMesh;
};

MEDUSA_END;
