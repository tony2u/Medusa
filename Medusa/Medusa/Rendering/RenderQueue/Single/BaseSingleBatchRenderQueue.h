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
	BaseSingleBatchRenderQueue(const Share<IRenderTarget>& renderTarget = nullptr, const Share<Camera>& camera = nullptr,
							   RenderingStrategy strategy = RenderingStrategy::MultipleDynamicBatch);
	virtual ~BaseSingleBatchRenderQueue(void);
public:
	virtual const Share<IRenderTarget>& RenderTarget() const override{ return mRenderTarget; }
	virtual void SetRenderTarget(const Share<IRenderTarget>& val)override;

	virtual const Share<Camera>& GetCamera() const override{ return mCamera; }
	virtual void SetCamera(const Share<Camera>& val)override;
public:
	virtual void Update(RenderableChangedFlags changedFlag)override;
protected:
	virtual bool OnUpdateCommands(RenderingFlags renderingFlags = RenderingFlags::None)override;

protected:
	Share<IRenderTarget> mRenderTarget;
	Share<Camera> mCamera;
	IRenderBatch* mBatch=nullptr;

};

MEDUSA_END;
