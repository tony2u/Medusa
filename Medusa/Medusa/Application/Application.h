// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Log/ILogger.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Geometry/Size2.h"
#include "Core/Pattern/Delegate.h"
#include "Platform/EngineFeatures.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Task/FrameTaskStage.h"

MEDUSA_BEGIN;

class Application :public Singleton < Application >
{
	friend class Singleton < Application > ;
private:
	Application();
	~Application(void);
public:
	bool UpdateAndDraw(float dt);
	bool Update(float dt);
	void Draw(float dt);
	bool Step();


public:
	BaseRenderView* RootView() const { return mRootView; }

	IWindow* Window() const { return mWindow; }
	IGame* Game() const { return mGame; }
	void SetGame(IGame* val);

	void RegisterGame(Delegate<IGame*()> val);


	float FrameInterval()const { return mFrameInterval; }
	void SetFrameInterval(float val);

	uint64 FrameCount() const { return mFrameCount; }
	double TimeStamp() const { return mTimeStamp; }
	float FPS()const { return 1.f / mFrameInterval; }

	bool IsInMainThread()const;
public:
	bool Initialize();
	bool Uninitialize();
	bool InitializeRenderEngine();
	bool UninitializeRenderEngine();

	bool Run();

	bool Start();
	bool Pause();
	bool Resume();
	bool Stop();

	void Sleep();
	void Wakeup();
	void ReceiveMemoryWarning();
	void Redraw();
private:

private:
	IGame* mGame;
	IWindow* mWindow;
	BaseRenderView* mRootView;
	Delegate<IGame*()> mCreateGameCallback;

	float mFrameInterval;
	float mFrameIntervalRestore;

	double mTimeStamp;
	uint64 mFrameCount;
	EngineFeatures mEngineFeatures;

	ThreadHandle mMainThread;

	FrameTaskStage mUpdateSystemStage;
	bool mIsInitialized;



};

MEDUSA_END;