// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Application/Window/ios/IOSWindow.h"
#include "Application/Window/win/WinWindow.h"
#include "Core/Log/win/WindowsTraceLogger.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Application/Application.h"
#include "Core/Log/Log.h"
#include "Application/Window/WindowFactory.h"
#include "Graphics/Render/Render.h"
#include "Resource/ResourceManager.h"
#include "Core/Profile/ProfileSample.h"
#include "Rendering/RenderEngine.h"
#include "Game/IGame.h"
#include "Node/Input/InputManager.h"
#include "Graphics/ResolutionAdapter.h"
#include "Audio/AudioEngine.h"
#include "Application/ApplicationStatics.h"
#include "Graphics/GraphicsContext.h"
#include "Node/Scene/SceneManager.h"
#include "Core/Profile/StopWatch.h"
#include "Node/Action/Animation/AnimationManager.h"
#include "Node/Particle/ParticleManager.h"
#include "Core/Profile/PerformanceCounter.h"
#include "Core/Threading/Thread.h"
#include "Game/Settings/IGameClientSettings.h"
#include "Core/Threading/ThreadPool.h"
#include "Application/FrameAutoStopWatch.h"
#include "Core/Command/Processor/MainCommandProcessor.h"
#include "Application/View/ViewFactory.h"
#include "Node/NodeSweeper.h"
#include "Node/Scene/SceneSweeper.h"
#include "Application/View/BaseRenderView.h"
#include "Core/System/Environment.h"

MEDUSA_BEGIN;


Application::Application() :mGame(nullptr), mWindow(nullptr)
{
	mTimeStamp = 0.f;
	mFrameCount = 0;
	mRootView = nullptr;
	mFrameInterval = MEDUSA_FRAME_INTERVAL;
	mFrameIntervalRestore = mFrameInterval;
	mIsInitialized = false;
}


Application::~Application(void)
{
	SAFE_DELETE(mGame);
	SAFE_DELETE(mWindow);

}
void Application::RegisterGame(Delegate<IGame*()> val)
{
	mCreateGameCallback = val;
}

void Application::SetGame(IGame* val)
{
	RETURN_IF_EQUAL(mGame, val);
	SAFE_DELETE(mGame);
	mGame = val;

}

bool Application::Initialize()
{
	RETURN_TRUE_IF_NOT_NULL(mWindow);

	mMainThread = Thread::Current();
	ThreadPool::Instance().Initialize();
	Log::Initialize();

	//3.create game
	if (mCreateGameCallback != nullptr)
	{
		mGame = mCreateGameCallback();
	}

	Log::AssertNotNullFormat(mGame, "Cannot create game,forget to set new game callback?");
	MEDUSA_ASSERT_TRUE(mGame->Initialize(), "");

	if (mGame->BaseSettings()!=nullptr)
	{
		mEngineFeatures = mGame->BaseSettings()->EngineFeature();
	}

	//3.init render engine
	InitializeRenderEngine();


	ResolutionAdapter::Instance().InitializeCameras();

#ifdef MEDUSA_DEBUG
	if (mGame->BaseSettings()!=nullptr)
	{
		ApplicationStatics::Instance().Initialize(mGame->BaseSettings()->DebugInfo());
	}
	else
	{
		ApplicationStatics::Instance().Initialize(ApplicationDebugInfoFlags::None);
	}
#else
	ApplicationStatics::Instance().Initialize(ApplicationDebugInfoFlags::None);

#endif

	//4.init update component,order is important
	mUpdateSystemStage.Add(&ResourceManager::Instance());
	mUpdateSystemStage.Add(&AnimationManager::Instance());
	mUpdateSystemStage.Add(&ParticleManager::Instance());
	mUpdateSystemStage.Add(&InputManager::Instance());
	mUpdateSystemStage.Add(&AudioEngine::Instance());	//must be after resource manager

	mUpdateSystemStage.Initialize();
	mUpdateSystemStage.ApplyOptionToAll(!mEngineFeatures.IsMultipleThreadUpdating() ? ExecuteOption::Sync : ExecuteOption::Async);

	//5.update scene
	SceneManager::Instance().Initialize(!mEngineFeatures.IsMultipleThreadRendering());
	ApplicationStatics::Instance().UpdateLabels();
	mIsInitialized = true;
	return true;
}

bool Application::InitializeRenderEngine()
{
	RenderEngine::Instance().InitializeBeforeWindow(!mEngineFeatures.IsMultipleThreadRendering());

	//1. create window
	mWindow = WindowFactory::Create((MedusaWindowHandle)nullptr, mGame->Name());
	MEDUSA_ASSERT_NOT_NULL(mWindow, "");
	mWindow->SetSize(ResolutionAdapter::Instance().WinSize());
	MEDUSA_ASSERT_TRUE(mWindow->Initialize(), "");

	//2.create egl view
	mRootView = ViewFactory::CreateGLView(mGame->Name());
	mWindow->AddView(mRootView);
	MEDUSA_ASSERT_NOT_NULL(mRootView, "");
	mRootView->SetSize(ResolutionAdapter::Instance().WinSize());
	MEDUSA_ASSERT_TRUE(mRootView->Initialize(), "");

	//show window
	mWindow->Show();

	RenderEngine::Instance().InitializeAfterWindow(!mEngineFeatures.IsMultipleThreadRendering());

	/*Render::Instance().EnableFeature(GraphicsFeatures::DepthTest, true);
	Render::Instance().SetDepthFunc(GraphicsFuncType::LessOrEqual);
	Render::Instance().SetClearDepth(1.f);*/

	//Render::Instance().EnableFeature(GraphicsFeatures::DepthWritable, true);

	//Render::Instance().EnableFeature(GraphicsFeatures::Blend, true);

	return true;
}


bool Application::UninitializeRenderEngine()
{

	RenderEngine::Instance().UninitializeBeforeWindow();

	mRootView->Uninitialize();
	mWindow->Uninitialize();

	SAFE_DELETE(mWindow);
	RenderEngine::Instance().UninitializeAfterWindow();

	return true;
}

bool Application::Uninitialize()
{
	//complete all works
	SceneSweeper::Instance().Release();
	NodeSweeper::Instance().Release();
	ThreadPool::Instance().Uninitialzie();
	MainCommandProcessor::Instance().Clear();

	mGame->Uninitialize();
	SAFE_DELETE(mGame);

	SceneManager::Instance().Uninitialize();
	ResolutionAdapter::Instance().Uninitialize();

	mUpdateSystemStage.Uninitialize();

	//this order is important
	ApplicationStatics::Instance().Uninitialize();


	UninitializeRenderEngine();



	Log::Uninitialize();


	MEDUSA_PROFILE_PRINT();
	return true;
}


bool Application::UpdateAndDraw(float dt)
{
#ifdef MEDUSA_DEBUG
	if (dt > 0.2f)
	{
		dt = mFrameInterval;
	}
#endif

	mTimeStamp += dt;
	++mFrameCount;

	Update(dt);
	Draw(dt);

	return true;
}


bool Application::Update(float dt)
{
	SceneSweeper::Instance().Release();
	NodeSweeper::Instance().Release();
	MainCommandProcessor::Instance().WaitForComplete();

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateSystem);
		mUpdateSystemStage.UpdateAndWait(dt);
	}

	mGame->Update(dt);
	SceneManager::Instance().Update(dt);
	RenderEngine::Instance().Update(dt);

	return true;
}

void Application::Draw(float dt)
{

	SceneManager::Instance().Draw(dt);

	ApplicationStatics::Instance().Update(dt);
	ApplicationStatics::Instance().Draw(dt);
	ApplicationStatics::Instance().Reset();

	RenderEngine::Instance().Draw(dt);

	
	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::SwapBuffer);
		mRootView->SwapBuffers();
	}
}

bool Application::Step()
{
	return Update(mFrameInterval);
}



bool Application::Run()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mWindow->Start();
	return true;

}

bool Application::Start()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mWindow->Start();
	return true;

}

bool Application::Pause()
{
	RETURN_FALSE_IF_FALSE(mGame->Pause());
	mWindow->Pause();

	return true;
}

bool Application::Resume()
{
	RETURN_FALSE_IF_FALSE(mGame->Resume());
	mWindow->Resume();

	return true;
}


bool Application::Stop()
{
	RETURN_FALSE_IF_FALSE(mGame->Stop());
	mWindow->Stop();

	return true;
}


void Application::Sleep()
{
	mFrameIntervalRestore = mFrameInterval;
	mFrameInterval = 1.f;
}

void Application::Wakeup()
{
	mFrameInterval = mFrameIntervalRestore;
	//Redraw();
}

void Application::ReceiveMemoryWarning()
{

}

void Application::SetFrameInterval(float val)
{
	mFrameInterval = val;
	mFrameIntervalRestore = val;
}

bool Application::IsInMainThread() const
{
	return Thread::IsThreadEqual(mMainThread, Thread::Current());
}

void Application::Redraw()
{
	if (mIsInitialized)
	{
		UpdateAndDraw(mFrameInterval);
	}
}




MEDUSA_END;
