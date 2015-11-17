// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloWorldGame.h"
#include "HelloWorldScene.h"
#include "Core/IO/FileSystem.h"

HelloWorldGame::HelloWorldGame()
{
	mName="HelloWorld";
}

HelloWorldGame::~HelloWorldGame()
{
	
}

bool HelloWorldGame::Initialize()
{
	RETURN_FALSE_IF_FALSE(IGame::Initialize());
	

	return true;
}


bool HelloWorldGame::Start()
{
	SceneManager::Instance().PushScene<HelloWorldScene>();

	return true;
}


bool HelloWorldGame::Uninitialize()
{
	return true;
}

MEDUSA_IMPLEMENT_GAME(HelloWorldGame);