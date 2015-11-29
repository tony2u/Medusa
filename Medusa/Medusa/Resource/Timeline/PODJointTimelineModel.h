// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/Geometry/Matrix4.h"
#include "Resource/Model/Scene/PODDefines.h"

MEDUSA_BEGIN;

class PODJointTimelineModel:public ITimelineModel
{
public:
	PODJointTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~PODJointTimelineModel(void);
	virtual bool TryGetMatrix(float frame,Matrix4& outMatrix)const;
	using ITimelineModel::Initialize;
	bool Initialize(const PODNode* node);

private:
	const PODNode* mNode;
};

MEDUSA_END;
