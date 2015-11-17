// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "BaseSkeletonTextureAttachmentModel.h"
#include "Core/Geometry/Point2.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/TuplePattern.h"
#include "Resource/Model/Mesh/General/TextureGeneralMesh.h"

MEDUSA_BEGIN;

//vertex:{boneCount:{boneIndex,x,y,weight}+}

MEDUSA_TUPLE_4(VertexWeightInfo, uint, BoneIndex, float, X, float, Y, float, Weight);



class SkeletonSkinnedMeshAttachmentModel :public BaseSkeletonTextureAttachmentModel
{
public:
	SkeletonSkinnedMeshAttachmentModel(const StringRef& name, TextureAtlasRegion* region);
	virtual ~SkeletonSkinnedMeshAttachmentModel();
	virtual SkeletonAttachmentType Type()const override{ return SkeletonAttachmentType::SkinnedMesh; }

	const List<VertexWeightInfo>& Weights() const { return mWeights; }
	List<VertexWeightInfo>& MutableWeights() { return mWeights; }
	void AddWeight(const VertexWeightInfo& val);


	const List<Point2F>& Texcoords() const { return mMesh.Texcoords(); }
	List<Point2F>& MutableTexcoords() { return mMesh.MutableTexcoords(); }

	void AddTexcoord(const Point2F& val);

	const List<uint>& Indices() const { return mMesh.Indices(); }
	List<uint>& MutableIndices() { return mMesh.MutableIndices(); }

	void AddIndex(uint val);

	const TextureGeneralMesh& Mesh() const { return mMesh; }
	virtual IMesh* GetMesh() override { return &mMesh; }
	virtual bool Initialize()override;

protected:
	List<VertexWeightInfo> mWeights;

	TextureGeneralMesh mMesh;

};

MEDUSA_END;
