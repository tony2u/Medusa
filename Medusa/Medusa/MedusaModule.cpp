// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MedusaModule.h"

#include "Core/Script/ScriptEngine.h"

#ifdef MEDUSA_LUA
#include "Binding/Lua/Engine_Binding.h"

#endif

#include "Content/Content.h"
#include "Core/Module/DelegateModule.h"
#include "Graphics/ResolutionAdapter.h"
#include "Application/Application.h"
#include "Rendering/RenderEngine.h"
#include "Application/Window/WindowFactory.h"
#include "Application/View/ViewFactory.h"
#include "Game/IGame.h"
#include "Node/Action/Animation/AnimationManager.h"
#include "Node/Particle/ParticleManager.h"
#include "Node/Input/InputManager.h"
#include "Audio/AudioEngine.h"
#include "Resource/ResourceManager.h"
#include "Application/ApplicationStatics.h"
#include "Application/FrameAutoStopWatch.h"
#include "Node/Editor/NodeEditorFactory.h"
#include "Node/Scene/SceneManager.h"
#include "Node/NodeSweeper.h"
#include "Node/Scene/SceneSweeper.h"
#include "Application/Settings/ApplicationSettings.h"

MEDUSA_BEGIN;

MedusaModule::MedusaModule()
	:IModule("Engine")
{
}

bool MedusaModule::Initialize()
{

#ifdef MEDUSA_LUA
	ScriptBinding::Register_Engine();
#endif

	DelegateModule* module = nullptr;
	module = new DelegateModule("Content");
	module->LoadHandler = [](IEventArg&)
	{
		Content::RegisterToFileSystem();
		return true;
	};
	AddPrevModule(module);
	SAFE_RELEASE(module);
	

	return true;
}

bool MedusaModule::BeforeUpdate(float dt)
{
	SceneSweeper::Instance().Release();
	NodeSweeper::Instance().Release();

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateSystem);
		mUpdateSystemStage.UpdateAndWait(dt);
	}

	return true;
}

bool MedusaModule::AfterUpdate(float dt)
{
	SceneManager::Instance().Update(dt);
	RenderEngine::Instance().Update(dt);
	return true;
}

void MedusaModule::BeforeDraw(float dt)
{
	SceneManager::Instance().Draw(dt);

}

void MedusaModule::AfterDraw(float dt)
{
	RenderEngine::Instance().Draw(dt);

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::SwapBuffer);
		mRootView->SwapBuffers();
	}
}

bool MedusaModule::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	NodeEditorFactory::Instance().Initialize();
	ResolutionAdapter::Instance().Initialize(ApplicationSettings::Instance().ResultWinSize());
	ResolutionAdapter::Instance().InitializeCameras();


	RenderEngine::Instance().InitializeBeforeWindow(!MEDUSA_FLAG_HAS(ApplicationSettings::Instance().Features(),EngineFeatures::MultipleThreadRendering));

	auto game = Application::Instance().Game();
	//1. create window
	mWindow = WindowFactory::Create((MedusaWindowHandle)nullptr, game->Name());
	MEDUSA_ASSERT_NOT_NULL(mWindow, "");
	mWindow->SetSize(ResolutionAdapter::Instance().WinSize());
	MEDUSA_ASSERT_TRUE(mWindow->Initialize(), "");

	//2.create egl view
	mRootView = ViewFactory::CreateGLView(game->Name());
	mWindow->AddView(mRootView);
	MEDUSA_ASSERT_NOT_NULL(mRootView, "");
	mRootView->SetSize(ResolutionAdapter::Instance().WinSize());
	MEDUSA_ASSERT_TRUE(mRootView->Initialize(), "");

	//show window
	mWindow->Show();

	RenderEngine::Instance().InitializeAfterWindow(!MEDUSA_FLAG_HAS(ApplicationSettings::Instance().Features(), EngineFeatures::MultipleThreadRendering));


	mUpdateSystemStage.Add(ResourceManager::InstancePtr());
	mUpdateSystemStage.Add(AnimationManager::InstancePtr());
	mUpdateSystemStage.Add(ParticleManager::InstancePtr());
	mUpdateSystemStage.Add(InputManager::InstancePtr());
	mUpdateSystemStage.Add(AudioEngine::InstancePtr());	//must be after resource manager

	mUpdateSystemStage.Initialize();
	mUpdateSystemStage.ApplyOptionToAll(!MEDUSA_FLAG_HAS(ApplicationSettings::Instance().Features(), EngineFeatures::MultipleThreadUpdating) ? ExecuteOption::Sync : ExecuteOption::Async);


	SceneManager::Instance().Initialize(!MEDUSA_FLAG_HAS(ApplicationSettings::Instance().Features(), EngineFeatures::MultipleThreadRendering));

	return true;
}


bool MedusaModule::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	SceneSweeper::Instance().Release();
	NodeSweeper::Instance().Release();

	SceneManager::Instance().Uninitialize();

	mUpdateSystemStage.Uninitialize();

	RenderEngine::Instance().UninitializeBeforeWindow();

	mRootView->Uninitialize();
	mWindow->Uninitialize();

	SAFE_DELETE(mWindow);
	mRootView = nullptr;

	RenderEngine::Instance().UninitializeAfterWindow();

	ResolutionAdapter::Instance().Uninitialize();
	NodeEditorFactory::Instance().Uninitialize();


	return true;
}
bool MedusaModule::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}


MEDUSA_END;

