// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Command/Executor/TFrameCommandExecutor.h"

MEDUSA_BEGIN;


class RenderDevice :public Singleton<RenderDevice>, public TFrameCommandExecutor<ICommand>
{
	friend class Singleton < RenderDevice > ;
	RenderDevice();
	~RenderDevice(void);
public:
	virtual bool Initialize(bool disableThreading = false)override;
	virtual bool Uninitialize()override;

	bool NeedAsync()const;
protected:
	ThreadId mCurrentThreadId;
};

MEDUSA_END;
