// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "UIRenderQueue.h"

MEDUSA_BEGIN;



UIRenderQueue::UIRenderQueue(IRenderTarget* renderTarget/*=nullptr*/, Camera* camera/*=nullptr*/)
	:BaseMultipleBatchRenderQueue(renderTarget, camera)
{
}

UIRenderQueue::~UIRenderQueue(void)
{
}





MEDUSA_END;