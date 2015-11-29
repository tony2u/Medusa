// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Rendering/RenderQueue/IRenderQueue.h"
#include "Core/Collection/LinkedList.h"
#include "Core/Pattern/SwapValue.h"

MEDUSA_BEGIN;

struct IRenderableCompareByRenderingPriority
{
	static int Compare(IRenderable* t1, IRenderable* t2);
};

class BaseMultipleBatchRenderQueue :public IRenderQueue
{
public:
	typedef LinkedList<IRenderBatch*> BatchList;
	typedef SwapValue<BatchList> DoubleBatchList;

	BaseMultipleBatchRenderQueue(IRenderTarget* renderTarget = nullptr, Camera* camera = nullptr);
	~BaseMultipleBatchRenderQueue(void);
public:
	virtual void Update(RenderableChangedFlags changedFlag)override;
public:
	virtual IRenderTarget* RenderTarget() const override;
	virtual void SetRenderTarget(IRenderTarget* val)override;

	virtual Camera* GetCamera() const override;
	virtual void SetCamera(Camera* val)override;
protected:
	virtual bool OnUpdateBatchList();
	virtual bool OnUpdateRenderGroup();
	virtual bool OnUpdateCommands(RenderingFlags renderingFlags = RenderingFlags::None)override;
	virtual bool OnUpdateBatchData();

protected:
	DoubleBatchList mBatches;
	SceneRenderGroup* mRenderGroup;
};

MEDUSA_END;
