// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Core/Collection/SortedDictionary.h"
#include "Rendering/IRenderGroup.h"

MEDUSA_BEGIN;

class SceneRenderGroup :public IRenderGroup
{
public:
	SceneRenderGroup(IRenderTarget* renderTarget, Camera* camera);
	virtual ~SceneRenderGroup();
public:
	IRenderTarget* RenderTarget() const { return mRenderTarget; }
	void SetRenderTarget(IRenderTarget* val);

	Camera* GetCamera() const { return mCamera; }
	void SetCamera(Camera* val);

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Add(IRenderBatch* batch)override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None)override;
	virtual void Print(HeapString& ioStr, uint level)override;
private:
	IRenderTarget* mRenderTarget;
	Camera* mCamera;

	List<EffectRenderGroup*> mGroups;
};


MEDUSA_END;