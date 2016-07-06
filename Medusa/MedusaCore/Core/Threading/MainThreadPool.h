// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ThreadPool.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;


class MainThreadPool :public ThreadPool, public Singleton<MainThreadPool>
{
	friend class Singleton < MainThreadPool >;
	MainThreadPool() = default;
	~MainThreadPool(void) = default;
};

MEDUSA_END;
