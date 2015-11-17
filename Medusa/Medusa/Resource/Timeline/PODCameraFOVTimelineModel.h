// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;

class PODCameraFOVTimelineModel:public ITimelineModel
{
public:
	PODCameraFOVTimelineModel(const FileIdRef& fileId, float duration = 0.f);
	virtual ~PODCameraFOVTimelineModel(void);
	StringRef TargetNodeName() const { return mTargetNodeName; }
	StringRef CameraName() const { return mCameraName; }

	virtual bool TryGetFOV(float frame,float& outFOV)const;
	using ITimelineModel::Initialize;
	bool Initialize(StringRef cameraName,const List<float>& fovs,StringRef targetNodeName=StringRef::Empty);

	float GetFov(uint frame)const;

private:
	List<float> mFOVAnimations;
	HeapString mTargetNodeName;
	HeapString mCameraName;
};

MEDUSA_END;
