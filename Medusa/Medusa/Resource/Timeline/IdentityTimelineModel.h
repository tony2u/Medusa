// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
MEDUSA_BEGIN;

class IdentityTimelineModel:public ITimelineModel
{
public:
	IdentityTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~IdentityTimelineModel(void);
	virtual bool TryGetMatrix(float frame,Matrix& outMatrix)const;
};

MEDUSA_END;
