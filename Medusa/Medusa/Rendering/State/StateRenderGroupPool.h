// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/SingleObjectPool.h"
#include "Core/Pattern/Singleton.h"
#include "Rendering/State/StateRenderGroup.h"
MEDUSA_BEGIN;

class StateRenderGroupPool :public SingleObjectPool<StateRenderGroup*>, public Singleton<StateRenderGroupPool>
{
	friend class Singleton < StateRenderGroupPool > ;
	StateRenderGroupPool(){}
	~StateRenderGroupPool(){}
};

MEDUSA_END;
