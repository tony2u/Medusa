// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Command/ICommand.h"

MEDUSA_BEGIN;


class IWaitable
{
public:
	virtual bool Wait() { return true; }
	virtual bool TryWait() { return true; }
	virtual bool WaitTimeout(long milliseconds) { return true; }
	virtual void Set() {}
#ifndef MEDUSA_POSIX_THREADING
	virtual ThreadNativeHandle NativeHandle()const = 0;
#endif
};

MEDUSA_END;
