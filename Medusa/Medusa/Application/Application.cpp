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


MEDUSA_BEGIN;


Application::Application()
	:IModule("Application")
{
	mTimeStamp = 0.f;
	mFrameCount = 0;
	mFrameInterval = MEDUSA_FRAME_INTERVAL;
	mFrameIntervalRestore = mFrameInterval;
	mIsInitialized = false;

	mCore.Retain();	//prevent release
	mEngine.Retain();	//prevent release

}


Application::~Application(void)
{
	

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
		SAFE_RETAIN(mGame);
	}

	Log::AssertNotNullFormat(mGame, "Cannot create game,forget to set new game callback?");

	AddPrevModule(&mCore);

	AddPrevModule(ApplicationSettings::InstancePtr());
	AddPrevModule(new AppCompatibilityModule(), false);
	AddPrevModule(&mEngine);

	if (mExtension!=nullptr)
	{
		AddPrevModule(mExtension);
		mExtension->Release();
	}

	AddNextModule(mGame);
	mGame->Release();


	return true;
}


bool Application::Uninitialize()
{
	ClearModules();
	return true;
}

bool Application::OnBeforeLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	Log::Initialize();
	mMainThread = Thread::Current();

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
	Log::FormatInfo("Version:{}", versionStr.c_str());
	Log::FormatInfo("Device:{}", deviceStr.c_str());
	Log::FormatInfo("Language:{}", languageStr.c_str());
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
	//order is import
	mCore.BeforeUpdate(dt);
	mEngine.BeforeUpdate(dt);

	mGame->Update(dt);

	mCore.AfterUpdate(dt);
	mEngine.AfterUpdate(dt);

	return true;
}

void Application::Draw(float dt)
{
	mEngine.BeforeDraw(dt);
	ApplicationStatics::Instance().Update(dt);
	ApplicationStatics::Instance().Draw(dt);
	ApplicationStatics::Instance().Reset();
	mEngine.AfterDraw(dt);
}

bool Application::Step()
{
	return Update(mFrameInterval);
}

bool Application::Run()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mEngine.Window()->Start();
	return true;

}

bool Application::Start()
{
	RETURN_FALSE_IF_FALSE(mGame->Start());
	mEngine.Window()->Start();
	return true;

}

bool Application::Pause()
{
	RETURN_FALSE_IF_FALSE(mGame->Pause());
	mEngine.Window()->Pause();

	return true;
}

bool Application::Resume()
{
	RETURN_FALSE_IF_FALSE(mGame->Resume());
	mEngine.Window()->Resume();

	return true;
}


bool Application::Stop()
{
	RETURN_FALSE_IF_FALSE(mGame->Stop());
	mEngine.Window()->Stop();

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

