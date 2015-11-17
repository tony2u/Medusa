// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseSingleBatchRenderQueue.h"

MEDUSA_BEGIN;


class SingleBatchRenderQueue :public BaseSingleBatchRenderQueue
{
public:
	SingleBatchRenderQueue(IRenderTarget* renderTarget = nullptr, Camera* camera = nullptr, RenderingStrategy strategy = RenderingStrategy::MultipleDynamicBatch);
	virtual ~SingleBatchRenderQueue(void);

};

MEDUSA_END;
