// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AnimationManager.h"

MEDUSA_BEGIN;

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager(void)
{
	
}

bool AnimationManager::Initialize()
{
	return true;
}

bool AnimationManager::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());

	return true;
}


void AnimationManager::OnUpdate(float dt)
{

}

MEDUSA_END;