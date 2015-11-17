// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ParticleManager.h"

MEDUSA_BEGIN;

ParticleManager::ParticleManager()
{
	
}

ParticleManager::~ParticleManager(void)
{
	Uninitialize();
}

bool ParticleManager::Initialize()
{
	return true;
}

bool ParticleManager::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());

	return true;
}

void ParticleManager::OnUpdate(float dt)
{

}

MEDUSA_END;