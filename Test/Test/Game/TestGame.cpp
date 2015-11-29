// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TestGame.h"
#include "TestScene.h"
#include "Game/TestSettings.h"
#include "Game/Player/TestPlayer.h"
#include "MedusaExtensionScript.h"
#include "TestScript.h"

TestGame& TestGame::Instance()
{
	return *(TestGame*)Application::Instance().Game();
}

TestGame::TestGame()
{
	mName="Test";
	mCompatibility.SetVersion(1);

	mFeatures = GameFeatures::SupportSceneEditor | GameFeatures::SupportScript;

}

TestGame::~TestGame()
{
	
}

const TestSettings& TestGame::Config() const
{
	return *(TestSettings*)mSettings;
}


const TestPlayer& TestGame::Player() const
{
	return *(TestPlayer*)mPlayer;
}


bool TestGame::OnPrepareSettings()
{
	SAFE_DELETE(mSettings);
	mSettings = new TestSettings();

	return true;
}

bool TestGame::OnLoadSettings()
{
	TestSettings* settings = (TestSettings*)mSettings;
	settings->SetScriptObject(TestScript::Instance().ConfigObject());
	return true;
}

bool TestGame::OnLoadPlayer()
{
	SAFE_DELETE(mPlayer);
	mPlayer = new TestPlayer();
	mPlayer->Load();
	return true;
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
	ApplicationStatics::Instance().ShowAll(false);
	//ApplicationStatics::Instance().ShowPerformance(true);
	//RenderingStatics::Instance().ShowGPU(true);

	TestScene* scene=new TestScene("Test");
	scene->Initialize();

	SceneManager::Instance().PushScene(scene);
	return true;
}



#pragma region Script

bool TestGame::OnRegisterScriptTypes()
{
	RETURN_FALSE_IF_FALSE(IGame::OnRegisterScriptTypes());
#ifdef MEDUSA_SCRIPT
	TestScript::Instance().RegisterTypes();
#endif
	return true;
}

bool TestGame::OnLoadInternalScripts()
{
	RETURN_FALSE_IF_FALSE(IGame::OnLoadInternalScripts());
#ifdef MEDUSA_SCRIPT
	TestScript::Instance().InitializeInternal();
#endif
	return true;
}

bool TestGame::OnUnloadInternalScripts()
{
#ifdef MEDUSA_SCRIPT
	TestScript::Instance().UninitializeInternal();
#endif

	return IGame::OnUnloadInternalScripts();
}

bool TestGame::OnCreateInternalScriptObjects()
{
#ifdef MEDUSA_SCRIPT
	return TestScript::Instance().CreateInternalScriptObjects();
#else
	return true;
#endif
}



#pragma endregion Script



MEDUSA_IMPLEMENT_GAME(TestGame);


