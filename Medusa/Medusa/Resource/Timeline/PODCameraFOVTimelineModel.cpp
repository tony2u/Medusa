// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODCameraFOVTimelineModel.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

PODCameraFOVTimelineModel::PODCameraFOVTimelineModel(const FileIdRef& fileId, float duration /*= 0.f*/)
	:ITimelineModel(fileId, duration)
{
}


PODCameraFOVTimelineModel::~PODCameraFOVTimelineModel(void)
{
}

bool PODCameraFOVTimelineModel::Initialize( StringRef cameraName,const List<float>& fovs,StringRef targetNodeName/*=StringRef::Empty*/ )
{
	RETURN_FALSE_IF_FALSE(ITimelineModel::Initialize());
	mCameraName=cameraName;
	mFOVAnimations=fovs;
	mTargetNodeName=targetNodeName;
	return true;
}

bool PODCameraFOVTimelineModel::TryGetFOV( float frame,float& outFOV ) const
{
	RETURN_FALSE_IF(frame<0.f);
	RETURN_FALSE_IF(frame>(float)FrameCount());

	uint frameIndex=(uint)frame;
	float frameBlend=frame-(float)frameIndex;

	if (!mFOVAnimations.IsEmpty())
	{
		if (frameIndex==mFOVAnimations.Size()-1)
		{
			//last frame
			outFOV=mFOVAnimations[frameIndex];
		}
		else
		{
			float fov1=mFOVAnimations[frameIndex];
			float fov2=mFOVAnimations[frameIndex+1];

			outFOV=Math::LinearInterpolate(fov1,fov2,frameBlend);
		}

		return true;
	}
	else
	{
		return false;
	}
}

float PODCameraFOVTimelineModel::GetFov(uint frame) const
{
	return mFOVAnimations[frame];
}


MEDUSA_END;