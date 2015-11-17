// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;


class ReadWriteLock :private ReadWriteLockImp
{
public:
	ReadWriteLock(bool isInitializeNow = true);
	~ReadWriteLock();

	void Initialize();
	void Uninitialize();

	void BeginRead();
	bool TryBeginRead();
	bool BeginReadTimeout(long milliseconds);
	void EndRead();
	void BeginWrite();
	bool TryBeginWrite();
	bool BeginWriteTimeout(long milliseconds);
	void EndWrite();
private:
	ReadWriteLock(const ReadWriteLock &);
	ReadWriteLock& operator=(const ReadWriteLock &);
private:
};


MEDUSA_END;
