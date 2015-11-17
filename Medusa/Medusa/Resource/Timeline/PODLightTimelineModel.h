// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;

class PODLightTimelineModel:public ITimelineModel
{
public:
	PODLightTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~PODLightTimelineModel(void);
	StringRef TargetNodeName() const { return mTargetNodeName; }
	StringRef LightName() const { return mLightName; }
	using ITimelineModel::Initialize;
	bool Initialize(StringRef lightName,StringRef targetNodeName=StringRef::Empty);
private:
	HeapString mTargetNodeName;
	HeapString mLightName;
};

MEDUSA_END;
