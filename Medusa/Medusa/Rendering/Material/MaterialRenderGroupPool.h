// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Object/SingleObjectPool.h"
#include "Core/Pattern/Singleton.h"
#include "Rendering/Material/MaterialRenderGroup.h"
MEDUSA_BEGIN;

class MaterialRenderGroupPool :public SingleObjectPool<MaterialRenderGroup*>, public Singleton < MaterialRenderGroupPool >
{
	friend class Singleton < MaterialRenderGroupPool >;
	MaterialRenderGroupPool() {}
	~MaterialRenderGroupPool() {}
};

MEDUSA_END;
