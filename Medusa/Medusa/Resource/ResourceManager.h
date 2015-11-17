// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Resource/IResource.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileId.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;

/*
TODO: Support push/pop state, allow user to push current state and release resources automatically after pop
*/

class ResourceManager:public Singleton<ResourceManager>,public FrameTask
{
	friend class Singleton<ResourceManager>;
protected:
	ResourceManager(void);
	~ResourceManager(void);

public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	void Clear();
	void Shrink();
	void ReleaseCache();

protected:
	virtual void OnUpdate(float dt)override;

protected:
	List<IResourceManageable*> mResourceFactories;
};

MEDUSA_END;