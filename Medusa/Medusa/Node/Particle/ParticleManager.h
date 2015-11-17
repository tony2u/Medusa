// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;


class ParticleManager :public Singleton<ParticleManager>, public FrameTask
{
	friend class Singleton < ParticleManager > ;
	ParticleManager();
	~ParticleManager(void);

public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
protected:
	virtual void OnUpdate(float dt)override;


};

MEDUSA_END;
