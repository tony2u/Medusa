// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TestGame.h"
#include "TestScene.h"
#include "Game/Player/TestPlayer.h"
#include "MedusaExtensionModule.h"
#include "CocosStudio/BinaryEditor.h"
#include "Core/Script/ScriptEngine.h"


TestGame& TestGame::Instance()
{
	return *(TestGame*)Application::Instance().Game();
}

TestGame::TestGame()
{
	mName = "Test";

	FileSystem::Instance().SetCoders(0);
	const static char key[] = "123456";
	FileSystem::Instance().SetCoderKey(MemoryData::FromStatic((const uint8*)key, 6));

	System::Instance().Initialize("Resource", "Save", "Temp");

	Application::Instance().SetExtension(new MedusaExtensionModule());
	
	//ApplicationSettings::Instance().SetDebugInfo(ApplicationDebugInfoFlags::All);
	//ApplicationSettings::Instance().SetSettingsFile("ApplicationSettings.lua");
	//ApplicationSettings::Instance().SetDebugWinSize(msize( 360, 640));
}

TestGame::~TestGame()
{

}

bool TestGame::Initialize()
{
	RETURN_FALSE_IF_FALSE(IGame::Initialize());

	return true;
}

bool TestGame::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(IGame::Uninitialize());

	return true;
}


bool TestGame::Start()
{
	RETURN_FALSE_IF_FALSE(IGame::Start());
	//ApplicationStatics::Instance().ShowAll(false);
	//ApplicationStatics::Instance().ShowPerformance(true);
	//RenderingStatics::Instance().ShowGPU(true);

	//TestScene* scene = new TestScene("Test");
	//scene->Initialize();
	SceneManager::Instance().Push<TestScene>();

	//SceneManager::Instance().Push("MainScene.csb");
	//SceneManager::Instance().Push("MainScene.json");


//	SceneManager::Instance().Push(scene);
	return true;
}



MEDUSA_IMPLEMENT_GAME(TestGame);


