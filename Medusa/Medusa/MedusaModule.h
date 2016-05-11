// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Module/IModule.h"
#include "Core/Task/FrameTaskStage.h"

MEDUSA_BEGIN;

class MedusaModule :public IModule
{
public:
	MedusaModule();
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override { return true; }

	BaseRenderView* RootView() const { return mRootView; }
	IWindow* Window() const { return mWindow; }

	bool BeforeUpdate(float dt);
	bool AfterUpdate(float dt);

	void BeforeDraw(float dt);
	void AfterDraw(float dt);

protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnReload(IEventArg& e = IEventArg::Empty) override;
protected:
	IWindow* mWindow = nullptr;
	BaseRenderView* mRootView = nullptr;

	FrameTaskStage mUpdateSystemStage;

};

MEDUSA_END;
