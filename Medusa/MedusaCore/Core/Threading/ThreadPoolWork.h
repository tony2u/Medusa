// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Command/ICommand.h"
#include "Core/String/HeapString.h"

#include "Core/Threading/win/ThreadPoolWorkImp_win.h"
#include "Core/Threading/posix/ThreadPoolWorkImp_posix.h"

MEDUSA_BEGIN;


class ThreadPoolWork :protected ThreadPoolWorkImp, public ICommand
{
	friend class ThreadPool;
	ThreadPoolWork(ThreadPool* pool, const StringRef& name, const ShareCommand& command);
	~ThreadPoolWork(void);
public:
	StringRef Name() const { return mName; }
	ThreadPool* Pool() const { return mPool; }
	void SetPool(ThreadPool* val) { mPool = val; }

	const ShareCommand& Command() const { return mCommand; }
	void SetCommand(const ShareCommand& val) { mCommand = val; }

	void Sumbit();
	void Wait(bool cancelPending = false);

	virtual bool OnExecute() override;
protected:
	HeapString mName;
	ShareCommand mCommand;

	ThreadPool* mPool = nullptr;

};



MEDUSA_END;
