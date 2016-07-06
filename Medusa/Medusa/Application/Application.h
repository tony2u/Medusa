// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Delegate.h"
#include "Platform/EngineFeatures.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Module/IModule.h"
#include "MedusaCoreModule.h"
#include "MedusaModule.h"

MEDUSA_BEGIN;

class Application :public Singleton < Application >,public IModule
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
	void SetExtension(const ShareModule& val) { mExtension = val; }
	
	IGame* Game() const { return mGame.Ptr(); }
	IWindow* Window()const { return mEngine->Window(); }
	void RegisterGame(Delegate<IGame*()> val);


	float FrameIntervalSeconds()const { return mFrameIntervalSeconds; }
	void SetFrameIntervalSeconds(float val);

	uint64 FrameCount() const { return mFrameCount; }
	double TimeStamp() const { return mTimeStamp; }
	float FPS()const { return 1.f / mFrameIntervalSeconds; }

	bool IsInMainThread()const;
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	bool Run();

	bool Start();
	bool Pause();
	bool Resume();
	bool Stop();

	void Sleep();
	void Wakeup();
	void ReceiveMemoryWarning();
	void Redraw();
protected:
	virtual bool OnBeforeLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnAfterLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnAfterUnload(IEventArg& e = IEventArg::Empty) override;

	virtual bool OnReload(IEventArg& e = IEventArg::Empty) override;

private:
	Share<IGame> mGame;
	Share<MedusaCoreModule> mCore;
	Share<MedusaModule> mEngine;
	ShareModule mExtension;

	Delegate<IGame*()> mCreateGameCallback;

	float mFrameIntervalSeconds;
	float mFrameIntervalSecondsRestore;

	double mTimeStamp;
	uint64 mFrameCount;

	ThreadId mMainThread;

	bool mIsInitialized;
	

};

MEDUSA_END;