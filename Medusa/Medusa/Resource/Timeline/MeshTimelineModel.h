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
	bool InitializeWithMeshes(SortedDictionary<uint, TextureQuadMesh*>& meshes, float fps = 24.f);

	void AddMesh(float time, IMesh* mesh);
	void AddMeshWithInterval(float frameInterval,IMesh* mesh);


	virtual IMesh* GetMeshByIndex(uint frame)const;
	virtual IMesh* GetMeshByTime(float time)const;

protected:
	List<IMesh*> mMeshes;
};

MEDUSA_END;
