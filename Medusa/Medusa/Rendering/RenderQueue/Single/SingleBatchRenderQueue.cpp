// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SingleBatchRenderQueue.h"

MEDUSA_BEGIN;



SingleBatchRenderQueue::SingleBatchRenderQueue(IRenderTarget* renderTarget/*=nullptr*/, Camera* camera/*=nullptr*/, RenderingStrategy strategy /*= RenderingStrategy::MultipleDynamicBatch*/)
	:BaseSingleBatchRenderQueue(renderTarget, camera,strategy)
{
}

SingleBatchRenderQueue::~SingleBatchRenderQueue(void)
{
}


MEDUSA_END;