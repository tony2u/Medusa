// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Rendering/Batch/BaseBufferRenderBatch.h"

MEDUSA_BEGIN;

class SingleRenderBatch:public BaseBufferRenderBatch
{
public:
	SingleRenderBatch(RenderingStrategy renderingStrategy);
	virtual ~SingleRenderBatch();
	virtual bool Update()override;


};


MEDUSA_END;