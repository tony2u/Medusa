// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloWorldGame.h"
#include "HelloWorldScene.h"
#include "Core/IO/FileSystem.h"

HelloWorldGame::HelloWorldGame()
{
	mName="HelloWorld";

	System::Instance().Initialize("Resource", "Save", "Temp");
}


bool HelloWorldGame::Start()
{
	SceneManager::Instance().Push<HelloWorldScene>();

	return true;
}

MEDUSA_IMPLEMENT_GAME(HelloWorldGame);