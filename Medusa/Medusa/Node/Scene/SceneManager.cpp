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
#include "Core/IO/Path.h"
#include "Core/IO/FileInfo.h"
#include "Node/Editor/NodeEditorFactory.h"

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


void SceneManager::Push(IScene* scene, ScenePushFlags pushFlag /*= ScenePushFlags::None*/)
{
#ifdef MEDUSA_SAFE_CHECK
	if (mScenes.Contains(scene))
	{
		Log::Error("scene has been already pushed.");
		return;
	}
#endif

	IScene* originalScene = Current();
	if (originalScene != nullptr)
	{
		if (MEDUSA_FLAG_HAS(pushFlag,ScenePushFlags::HideAllPrevScenes))
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

		if (!MEDUSA_FLAG_HAS(pushFlag,ScenePushFlags::ShowPrevScene))
		{
			originalScene->SetVisible(false);
			originalScene->ExitRecursively();
		}
		originalScene->EnableInput(MEDUSA_FLAG_HAS(pushFlag,ScenePushFlags::ShowPrevScene));
	}

	mScenes.Push(scene);
	scene->SetVisible(true);
	scene->EnterRecursively();

	if (!MEDUSA_FLAG_HAS(pushFlag,ScenePushFlags::SuppressUpdateLogic))
	{
		scene->UpdateLogicRecursively();
	}

	scene->EnableInput(!MEDUSA_FLAG_HAS(pushFlag,ScenePushFlags::DisableTouch));

	mIsSceneChanged = true;
}

IScene* SceneManager::Pop(ScenePopFlags popFlag /*= ScenePopFlags::None*/)
{
	IScene* scene = Current();
	Log::AssertNotNull(scene, "Scene stack should not be empty when pop.");

	if (!MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::ShowCurrentScene) || MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DeleteCurrentScene) || MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DeleteCurrentSceneAsync))
	{
		scene->SetVisible(false);
		scene->ExitRecursively();
		scene->EnableInput(false);
	}

	mScenes.Pop();
	mIsSceneChanged = true;

	if (MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DeleteCurrentScene) || MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DeleteCurrentSceneAsync))
	{
		DeleteScene(scene, MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DeleteCurrentSceneAsync));
		scene = nullptr;
	}

	if (!MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::IgnorePrevScene))
	{
		IScene* prevScene = Current();
		if (prevScene != nullptr)
		{
			prevScene->SetVisible(true);
			prevScene->EnableInput(!MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::DisableTouch));
			if (!MEDUSA_FLAG_HAS(popFlag,ScenePopFlags::SuppressUpdateLogic))
			{
				prevScene->UpdateLogicRecursively();
			}
		}
	}

	return scene;
}

IScene* SceneManager::ReplaceTo(IScene* scene, ScenePopFlags popFlag /*= ScenePopFlags::None*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/)
{
	IScene* prevScene = Pop(popFlag);
	Push(scene, pushFlag);
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

IScene* SceneManager::Push(const StringRef& className, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	if (Path::HasExtension(className))	//means a file
	{
		FileType fileType = FileInfo::ExtractType(className);
		if (FileInfo::IsScriptFile(fileType))
		{
			return PushEx(StringRef::Empty, StringRef::Empty, className, pushFlag, e);
		}
		else
		{
			auto editor = NodeEditorFactory::Instance().FindEditor(fileType);
			if (editor != nullptr)
			{
				return PushEx(StringRef::Empty, className, StringRef::Empty, pushFlag, e);
			}
			Log::AssertFailedFormat("Cannot support scene editor file:{}", className);
			return nullptr;
		}
	}
	else
	{
		return PushEx(className,StringRef::Empty, StringRef::Empty, pushFlag, e);
	}

}


IScene* SceneManager::PushEx(const StringRef& className, const FileIdRef& editorFile /*= FileIdRef::Empty*/, const FileIdRef& scriptFile /*= FileIdRef::Empty*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	IScene* scene = SceneFactory::Instance().Create(className, editorFile, e);
	if (!scriptFile.IsEmpty())
	{
		scene->AddScriptFile(scriptFile);
	}

	Push(scene, pushFlag);
	return scene;
}

IScene* SceneManager::ReplaceTo(const StringRef& className, ScenePopFlags popFlag /*= ScenePopFlags::None*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	Pop(popFlag);
	return Push(className, pushFlag, e);
}

IScene* SceneManager::ReplaceToEx(const StringRef& className, const FileIdRef& editorFile /*= FileIdRef::Empty*/, const FileIdRef& scriptFile /*= FileIdRef::Empty*/, ScenePopFlags popFlag /*= ScenePopFlags::None*/, ScenePushFlags pushFlag /*= ScenePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	Pop(popFlag);
	return PushEx(className, editorFile, scriptFile, pushFlag, e);
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

IScene* SceneManager::Current() const
{
	RETURN_NULL_IF_EMPTY(mScenes);
	return mScenes.Top();
}




MEDUSA_END;
