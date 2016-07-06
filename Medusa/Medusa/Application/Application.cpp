// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Application/Application.h"
#include "Core/Log/Log.h"
#include "Game/IGame.h"
#include "Application/ApplicationStatics.h"
#include "Core/Threading/Thread.h"
#include "Application/Compat/AppCompatibilityModule.h"
#include "Application/Window/IWindow.h"
#include "Application/Settings/ApplicationSettings.h"
#include "Core/Module/SingletonModule.h"

MEDUSA_BEGIN;


Application::Application()
	:IModule("Application")
{
	mTimeStamp = 0.f;
	mFrameCount = 0;
	mFrameIntervalSeconds = MEDUSA_FRAME_INTERVAL;
	mFrameIntervalSecondsRestore = mFrameIntervalSeconds;
	mIsInitialized = false;

	mCore = new MedusaCoreModule();
	mEngine = new MedusaModule();
}


Application::~Application(void)
{
	mGame = nullptr;
	mEngine = nullptr;
	mCore = nullptr;
}
void Application::RegisterGame(Delegate<IGame*()> val)
{
	mCreateGameCallback = val;
}


bool Application::Initialize()
{
	RETURN_TRUE_IF_TRUE(mIsInitialized);
	
	if (mCreateGameCallback != nullptr)
	{
		mGame = mCreateGameCallback();
	}

	Log::AssertFormat(mGame!=nullptr, "Cannot create game,forget to set new game callback?");

	AddPrevModule(mCore);

	AddPrevModule(new SingletonModule<ApplicationSettings>("ApplicationSettings"));
	AddPrevModule(new AppCompatibilityModule(), false);
	AddPrevModule(mEngine);

	if (mExtension!=nullptr)
	{
		AddPrevModule(mExtension);
	}

	AddNextModule(mGame);


	return true;
}


bool Application::Uninitialize()
{
	ClearModules();
	mGame = nullptr;
	mEngine = nullptr;
	mCore = nullptr;
	return true;
}

bool Application::OnBeforeLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	Log::Initialize();
	mMainThread = Thread::CurrentId();

	return true;
}

bool Application::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	ApplicationStatics::Instance().Initialize(ApplicationSettings::Instance().ResultDebugInfo());
	ApplicationStatics::Instance().UpdateLabels();

	return true;
}


bool Application::OnAfterLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	mIsInitialized = true;

	Log::Info("*****Application Load*****");
	PublishTarget resultTag = ApplicationSettings::Instance().ResultTag();
	HeapString versionStr = resultTag.Version.ToString();
	HeapString deviceStr = resultTag.Device.ToString();
	HeapString languageStr = resultTag.Language.ToString();
	Log::FormatInfo("Version:{}", versionStr);
	Log::FormatInfo("Device:{}", deviceStr);
	Log::FormatInfo("Language:{}", languageStr);
	auto winSize = ApplicationSettings::Instance().ResultWinSize();
	Log::FormatInfo("WinSize:{},{}", (uint)winSize.Width, (uint)winSize.Height);
	return true;
}

bool Application::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	ApplicationStatics::Instance().Uninitialize();

	return true;
}

bool Application::OnAfterUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	mGame = nullptr;	//release before
	Log::Uninitialize();
	return true;
}

bool Application::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}

bool Application::UpdateAndDraw(float dt)
{
#ifdef MEDUSA_DEBUG
	if (dt > 0.2f)
	{
		dt = mFrameIntervalSeconds;
	}
#endif

	mTimeStamp += dt;
	++mFrameCount;

	Update(dt);
	Draw(dt);

	Log::Update(dt);
	return true;
}

bool Application::Update(float dt)
{
	//order is import
	mCore->BeforeUpdate(dt);
	mEngine->BeforeUpdate(dt);

	mGame->Update(dt);

	mEngine->AfterUpdate(dt);
	mCore->AfterUpdate(dt);

	return true;
}

void Application::Draw(float dt)
{
	mEngine->BeforeDraw(dt);
	ApplicationStatics::Instance().Update(dt);
	ApplicationStatics::Instance().Draw(dt);
	ApplicationStatics::Instance().Reset();
	mEngine->AfterDraw(dt);
}

bool Application::Step()
{
	return Update(mFrameIntervalSeconds);
}

bool Application::Run()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mEngine->Window()->Start();
	return true;

}

bool Application::Start()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mEngine->Window()->Start();
	return true;

}

bool Application::Pause()
{
	RETURN_FALSE_IF_FALSE(mGame->Pause());
	mEngine->Window()->Pause();

	return true;
}

bool Application::Resume()
{
	RETURN_FALSE_IF_FALSE(mGame->Resume());
	mEngine->Window()->Resume();

	return true;
}


bool Application::Stop()
{
	RETURN_FALSE_IF_FALSE(mGame->Stop());
	mEngine->Window()->Stop();

	return true;
}


void Application::Sleep()
{
	mFrameIntervalSecondsRestore = mFrameIntervalSeconds;
	mFrameIntervalSeconds = 1.f;
}

void Application::Wakeup()
{
	mFrameIntervalSeconds = mFrameIntervalSecondsRestore;
	//Redraw();
}

void Application::ReceiveMemoryWarning()
{

}

void Application::SetFrameIntervalSeconds(float val)
{
	mFrameIntervalSeconds = val;
	mFrameIntervalSecondsRestore = val;
}

bool Application::IsInMainThread() const
{
	return Thread::IsCurrent(mMainThread);
}

void Application::Redraw()
{
	if (mIsInitialized)
	{
		UpdateAndDraw(mFrameIntervalSeconds);
	}
}




MEDUSA_END;

