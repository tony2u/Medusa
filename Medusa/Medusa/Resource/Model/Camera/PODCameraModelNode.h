// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#include "Resource/Model/Camera/BaseCameraModelNode.h"
MEDUSA_BEGIN;

class PODCameraModelNode:public BaseCameraModelNode
{
public:
	PODCameraModelNode(StringRef name);
	virtual ~PODCameraModelNode(void);
	using BaseCameraModelNode::CreateCamera;
	Share<Camera> CreateCamera(const Size2F& winSize)const;

public:
	int TargetObjectIndex;		//Index of the target object
	float FOV;					//Field of view 
	float Near;					//Near clip plane
	float Far;					//Far clip plane

	List<float> FOVAnimations;

};

MEDUSA_END;