// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/IUpdatable.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/String/HeapString.h"
#include "Core/Module/IModule.h"


MEDUSA_BEGIN;
/*
To support file updating,so we need to support file reloading
Reloading need to release previous res and load new res
*/
class IGame :public IModule, public DefaultRunnable, public IUpdatable
{
public:
	IGame(void);
	virtual ~IGame(void);
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Start()override;
	virtual bool Update(float dt)override;

	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }
protected:
	HeapString mName;
};


#define MEDUSA_DECLARE_GAME() 													\
private:																				\
	const static StaticConstructor mStaticConstructor;							

#define MEDUSA_IMPLEMENT_GAME(className) 																					 \
	const StaticConstructor className::mStaticConstructor([]{Application::Instance().RegisterGame(DefaultNewer<className*>::New);});					 

MEDUSA_END;
