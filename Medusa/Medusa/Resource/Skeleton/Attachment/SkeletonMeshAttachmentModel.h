// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseSkeletonTextureAttachmentModel.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point2.h"
#include "Core/Collection/List.h"
#include "Resource/Model/Mesh/General/TextureGeneralMesh.h"

MEDUSA_BEGIN;


class SkeletonMeshAttachmentModel :public BaseSkeletonTextureAttachmentModel
{
public:
	SkeletonMeshAttachmentModel(const StringRef& name, TextureAtlasRegion* region);
	virtual ~SkeletonMeshAttachmentModel();
	virtual SkeletonAttachmentType Type()const override{ return SkeletonAttachmentType::Mesh; }

	const List<Point3F>& Vertices() const { return mMesh.Vertices(); }
	List<Point3F>& MutableVertices() { return mMesh.MutableVertices(); }
	void AddVertex(const Point3F& pos);

	const List<Point2F>& Texcoords() const { return mMesh.Texcoords(); }
	List<Point2F>& MutableTexcoords() { return mMesh.MutableTexcoords(); }

	void AddTexcoord(const Point2F& val);

	const List<uint>& Indices() const { return mMesh.Indices(); }
	List<uint>& MutableIndices() { return mMesh.MutableIndices(); }

	void AddIndex(uint val);

	const TextureGeneralMesh& Mesh() const { return mMesh; }
	virtual IMesh* GetMesh() override{ return &mMesh; }
	virtual bool Initialize() override;

protected:
	TextureGeneralMesh mMesh;
};

MEDUSA_END;
