// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/IdObjectCache.h"
#include "Core/IO/IFileLoadable.h"
#include "Game/AI/Behavior/IBehavior.h"


MEDUSA_BEGIN;


class BehaviorConfig :public Singleton < BehaviorConfig >, public IdObjectCache < HeapString, IBehavior*>, public IFileLoadable
{
	friend class Singleton < BehaviorConfig > ;
	BehaviorConfig() {}
	~BehaviorConfig(void) {}

public:
	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0);
	virtual void Unload();
	IBehavior* SmartCreate(StringRef name);
private:

};

MEDUSA_END;
