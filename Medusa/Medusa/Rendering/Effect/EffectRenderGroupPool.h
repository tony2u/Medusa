// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/SingleObjectPool.h"
#include "Core/Pattern/Singleton.h"
#include "Rendering/Effect/EffectRenderGroup.h"
MEDUSA_BEGIN;

class EffectRenderGroupPool :public SingleObjectPool<EffectRenderGroup*>, public Singleton < EffectRenderGroupPool >
{
	friend class Singleton < EffectRenderGroupPool >;
	EffectRenderGroupPool() {}
	~EffectRenderGroupPool() {}
};

MEDUSA_END;
