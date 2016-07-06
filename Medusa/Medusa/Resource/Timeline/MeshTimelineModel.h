// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/IO/FileId.h"
#include "Geometry/Rect2.h"
#include "Core/Collection/SortedDictionary.h"
MEDUSA_BEGIN;

class MeshTimelineModel:public ITimelineModel
{
public:
	MeshTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~MeshTimelineModel(void);

	bool InitializeWithSingleTexture(const FileIdRef& textureName, uint coloumn, uint row, float fps = 24.f);
	bool InitializeWithMeshes(SortedDictionary<uint, Share<TextureQuadMesh>>& meshes, float fps = 24.f);

	void AddMesh(float time, const Share<IMesh>& mesh);
	void AddMeshWithInterval(float frameInterval, const Share<IMesh>& mesh);


	virtual Share<IMesh> GetMeshByIndex(uint frame)const;
	virtual Share<IMesh> GetMeshByTime(float time)const;

protected:
	List<Share<IMesh>> mMeshes;
};

MEDUSA_END;
