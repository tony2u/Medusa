// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Scene/SceneManager.h"
#include "Application/Window/IWindow.h"
#include "Rendering/RenderEngine.h"
#include "Node/Scene/IScene.h"
#include "Core/Log/Log.h"
#include "Application/View/BaseRenderView.h"
#include "SceneFactory.h"
#include "Application/ApplicationStatics.h"
#include "Graphics/ResolutionAdapter.h"
#include "Application/FrameAutoStopWatch.h"
#include "Rendering/RenderQueue/IRenderQueue.h"
#include "SceneSweeper.h"

MEDUSA_BEGIN;

SceneManager::SceneManager(void)
{
	mDisableThreading = true;

	Log::AlertViewEvent += Log::AlertViewDelegate(&SceneManager::ShowAlertView, this);
	Log::WAlertViewEvent += Log::WAlertViewDelegate(&SceneManager::ShowAlertView, this);
}


SceneManager::~SceneManager(void)
{

}

bool SceneManager::Initialize(bool disableThreading /*= false*/)
{
	mIsSceneChanged = false;
	mDisableThreading = disableThreading;

	

	return true;
}

bool SceneManager::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mScenes);
	return true;
}


void SceneManager::PushScene(IScene* scene, ScenePushFlags pushFlag /*= ScenePushFlags::None*/)
{
#ifdef MEDUSA_SAFE_CHECK
	if (mScenes.Contains(scene))
	{
		Log::Error("scene has been already pushed.");
		return;
	}
#endif

	IScene* originalScene = RunningScene();
	if (originalScene != nullptr)
	{
		if (pushFlag.Has(ScenePushFlags::HideAllPrevScenes))
		{
			FOR_EACH_COLLECTION(i, mScenes)
			{
				IScene* prevScene = *i;
				if (prevScene->IsVisible())
				{
					prevScene->SetVisible(false);
					prevScene->ExitRecursively();
					prevScene->EnableInput(false);
				}
			}
		}

		if (!pushFlag.Has(ScenePushFlags::ShowPrevScene))
		{
			originalScene->SetVisible(false);
			originalScene->ExitRecursively();
		}
		originalScene->EnableInput(pushFlag.Has(ScenePushFlags::ShowPrevScene));
	}

	mScenes.Push(scene);
	scene->SetVisible(true);
	scene->EnterRecursively();

	if (!pushFlag.Has(ScenePushFlags::SuppressUpdateLogic))
	{
		scene->UpdateLogicRecursively();
	}

	scene->EnableInput(!pushFlag.Has(ScenePushFlags::DisableTouch));

	mIsSceneChanged = true;
}

IScene* SceneManager::PopScene(ScenePopFlags popFlag /*= ScenePopFlags::None*/)
{
	IScene* scene = RunningScene();
	Log::AssertNotNull(scene, "Scene stack should not be empty when pop.");

	if (!popFlag.Has(ScenePopFlags::ShowCurrentScene) || popFlag.Has(ScenePopFlags::DeleteCurrentScene) || popFlag.Has(ScenePopFlags::DeleteCurrentSceneAsync))
	{
		scene->SetVisible(false);
		scene->ExitRecursively();
		scene->EnableInput(false);
	}

	mScenes.Pop();
	mIsSceneChanged = true;

	if (popFlag.Has(ScenePopFlags::DeleteCurrentScene) || popFlag.Has(ScenePopFlags::DeleteCurrentSceneAsync))
	{
		DeleteScene(scene, popFlag.Has(ScenePopFlags::DeleteCurrentSceneAsync));
		scene = nullptr;
	}

	if (!popFlag.Has(ScenePopFlags::IgnorePrevScene))
	{
		IScene* prevScene = RunningScene();
		if (prevScene != nullptr)
		{
			prevScene->SetVisible(true);
			prevScene->EnableInput(!popFlag.Has(ScenePopFlags::DisableTouch));
			if (!popFlag.Has(ScenePopFlags::SuppressUpdateLogic))
			{
				prevScene->UpdateLogicRecursively();
			}
		}
	}

	return scene;
}

IScene* SceneManager::ReplaceToScene(IScene* scene, ScenePopFlags popFlag /*= ScenePopFlags::None*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/)
{
	IScene* prevScene = PopScene(popFlag);
	PushScene(scene, pushFlag);
	return prevScene;
}

bool SceneManager::DeleteScene(IScene* scene, bool isAsync /*= false*/)
{
	if (isAsync)
	{
		SceneSweeper::Instance().Add(scene);
		return scene != nullptr;
	}
	else
	{
		bool result = mScenes.Remove(scene);
		SAFE_DELETE(scene);
		mIsSceneChanged = true;
		return result;
	}
}

IScene* SceneManager::PushSceneByName(const StringRef& className, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	IScene* scene = SceneFactory::Instance().Create(className, className, e);
	scene->Initialize();
	PushScene(scene, pushFlag);
	return scene;
}

IScene* SceneManager::ReplaceSceneByName(const StringRef& className, ScenePopFlags popFlag /*= ScenePopFlags::None*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	IScene* scene = SceneFactory::Instance().Create(className, className, e);
	scene->Initialize();

	ReplaceToScene(scene, popFlag, pushFlag);
	return scene;
}


void SceneManager::ShowActivityIndicator()
{

}

void SceneManager::HideActivityIndicator()
{

}

void SceneManager::ShowAlertView(StringRef text, Action0 callback /*= nullptr*/)
{
	//TODO: show alert view
	if (callback)
	{
		callback();
		MEDUSA_ASSERT_FAILED_SILENT;
	}
}

void SceneManager::ShowAlertView(WStringRef text, Action0 callback /*= nullptr*/)
{
	//TODO: show alert view
	if (callback)
	{
		callback();
		MEDUSA_ASSERT_FAILED_SILENT;
	}
}

void SceneManager::ShowToast(StringRef text, float duration /*= 2.0f*/, ToastPosition position /*= ToastPosition::Center*/)
{

}




void SceneManager::Update(float dt)
{
	if (mIsSceneChanged)
	{
		mSceneGraphStage.Clear();
		FOR_EACH_COLLECTION(i, mScenes)
		{
			IScene* scene = *i;
			ISceneGraph* graph = scene->GraphPtr();
			mSceneGraphStage.Add(graph);
		}

		mSceneGraphStage.ApplyOptionToAll(mDisableThreading ? ExecuteOption::Sync : ExecuteOption::Async);
		mIsSceneChanged = false;
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateScene);
		FOR_EACH_COLLECTION(i, mScenes)
		{
			IScene* scene = *i;
			scene->UpdateScene(dt);
		}
	}


	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateLayout);
		ResolutionAdapter::Instance().UpdateLayout();
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::VisitScene);
		FOR_EACH_COLLECTION(i, mScenes)
		{
			IScene* scene = *i;
			RenderableChangedFlags outFlag;
			//scene->VisitRecursively(mChangedNodeCollector, outFlag);
			scene->VisitScene(mChangedNodeCollector, outFlag);
			scene->Graph().SetChangedFlag(outFlag);
		}
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateRenderQueue);
		FOR_EACH_COLLECTION(i, mScenes)
		{
			IScene* scene = *i;
			scene->Graph().Update(dt);
		}

		mChangedNodeCollector.Clear();
	}


	//wait scene graph updating
	mSceneGraphStage.Wait();
}

void SceneManager::Draw(float dt)
{
	//send drawing commands to render engine after sort
	FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::Draw);
	RenderingFlags renderingFlag = RenderingFlags::None;

	for (IScene* scene : mScenes)
	{
		CONTINUE_IF_FALSE(scene->IsValidToRenderQueue());
		ISceneGraph* graph = scene->GraphPtr();
		graph->RenderQueue()->Draw(renderingFlag);
		renderingFlag = RenderingFlags::KeepRenderTarget;
	}

}

IScene* SceneManager::RunningScene() const
{
	RETURN_NULL_IF_EMPTY(mScenes);
	return mScenes.Top();
}




MEDUSA_END;
