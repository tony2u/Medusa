// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IService.h"
#include "Core/Threading/Thread.h"

MEDUSA_BEGIN;


class IThreadService :public IService
{
	MEDUSA_RTTI(IThreadService,IService);
public:
	IThreadService(const StringRef& options = StringRef::Empty);
	virtual ~IThreadService();

public:
	virtual bool Start()override;
	virtual bool Stop()override;
protected:
	virtual bool OnStart() { return true; }
	virtual void OnRun(Thread& thread);
	virtual bool OnRunOnce(Thread& thread) { return true; }
	virtual bool OnStop() { return true; }

	virtual bool OnFailed() { return true; }

private:
	void OnThread(Thread& thread);
protected:
	Thread mThread;
};

MEDUSA_END;
