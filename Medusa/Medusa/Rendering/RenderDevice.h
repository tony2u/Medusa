// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Command/Processor/BaseFrameCommandProcessor.h"

MEDUSA_BEGIN;


class RenderDevice :public Singleton<RenderDevice>, public BaseFrameCommandProcessor
{
	friend class Singleton < RenderDevice > ;
	RenderDevice();
	~RenderDevice(void);
public:
	virtual bool Initialize(bool disableThreading = false)override;
	virtual bool Uninitialize()override;

	bool NeedAsync()const;
protected:
	ThreadHandle mCurrentThreadHandle;
};

MEDUSA_END;
