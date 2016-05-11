// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Game/IGame.h"

MEDUSA_BEGIN;

IGame::IGame(void)
	:IModule("Game")
{

}

IGame::~IGame(void)
{
}

bool IGame::Initialize()
{
	return true;
}

bool IGame::Uninitialize()
{
	return true;
}


bool IGame::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IsRunning());

	return true;
}

bool IGame::Start()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
	return true;
}





MEDUSA_END;

