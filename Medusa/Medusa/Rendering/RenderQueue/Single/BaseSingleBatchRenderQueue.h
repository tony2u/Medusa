// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Rendering/RenderQueue/IRenderQueue.h"
#include "Core/Collection/List.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/RenderingTypes.h"
MEDUSA_BEGIN;


class BaseSingleBatchRenderQueue :public IRenderQueue
{
public:
	BaseSingleBatchRenderQueue(IRenderTarget* renderTarget = nullptr, Camera* camera = nullptr, 
							   RenderingStrategy strategy = RenderingStrategy::MultipleDynamicBatch);
	virtual ~BaseSingleBatchRenderQueue(void);
public:
	IRenderTarget* RenderTarget() const { return mRenderTarget; }
	void SetRenderTarget(IRenderTarget* val);

	Camera* GetCamera() const { return mCamera; }
	void SetCamera(Camera* val);
public:
	virtual void Update(RenderableChangedFlags changedFlag)override;
protected:
	virtual bool OnUpdateCommands(RenderingFlags renderingFlags = RenderingFlags::None)override;

protected:
	IRenderTarget* mRenderTarget;
	Camera* mCamera;
	IRenderBatch* mBatch;

};

MEDUSA_END;
