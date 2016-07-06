// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Core/Collection/SortedDictionary.h"
#include "Rendering/IRenderGroup.h"
#include "Resource/Camera/Camera.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class SceneRenderGroup :public IRenderGroup
{
public:
	SceneRenderGroup(const Share<IRenderTarget>& renderTarget, const Share<Camera>& camera);
	virtual ~SceneRenderGroup();
public:
	const Share<IRenderTarget>& RenderTarget() const { return mRenderTarget; }
	void SetRenderTarget(const Share<IRenderTarget>& val) { mRenderTarget = val; }

	const Share<Camera>& GetCamera() const { return mCamera; }
	void SetCamera(const Share<Camera>& val) { mCamera = val; }

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Add(IRenderBatch* batch)override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None)override;
	virtual void Print(HeapString& ioStr, uint level)override;
private:
	Share<IRenderTarget> mRenderTarget;
	Share<Camera> mCamera;

	List<EffectRenderGroup*> mGroups;
};


MEDUSA_END;