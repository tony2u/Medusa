// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/IO/FileId.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Collection/SortedDictionary.h"
#include "Rendering/RenderingObject.h"

MEDUSA_BEGIN;

class RenderingObjectTimelineModel:public ITimelineModel
{
public:
	RenderingObjectTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~RenderingObjectTimelineModel(void);

	bool InitializeWithSingleTexture(IMaterial* material, uint coloumn, uint row, float fps = 24.f);
	bool InitializeWithTextures(const SortedDictionary<uint, IMaterial*>& materials, float fps = 24.f);
	bool InitializeWithTextureAtlas(IMaterial* material,const SortedDictionary<uint, IMesh*>& meshes, float fps = 24.f);

	bool InitializeWithObjects(SortedDictionary<uint, RenderingObject>& renderingObjects, float fps = 24.f);

	
	void AddRenderingObject(float time, const RenderingObject& val);
	void AddRenderingObjectWithInterval(float frameInterval, const RenderingObject& val);


	virtual const RenderingObject* GetItemByIndex(uint frame)const;
	virtual const RenderingObject* GetItemByTime(float time)const;

protected:
	List<RenderingObject> mObjects;
};

MEDUSA_END;
