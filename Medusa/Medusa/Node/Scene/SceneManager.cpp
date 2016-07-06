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
#include "Application/ApplicationStatics.h"
#include "Graphics/ResolutionAdapter.h"
#include "Application/FrameAutoStopWatch.h"
#include "Rendering/RenderQueue/IRenderQueue.h"
#include "SceneSweeper.h"
#include "Core/IO/Path.h"
#include "Core/IO/FileInfo.h"
#include "Node/Editor/NodeEditorFactory.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

SceneManager::SceneManager(void)
{
	mDisableThreading = true;

	//Log::AlertViewEvent += Log::AlertViewDelegate(&SceneManager::ShowAlertView, this);
	//Log::WAlertViewEvent += Log::WAlertViewDelegate(&SceneManager::ShowAlertView, this);
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


IScene* SceneManager::Push(IScene* scene, NodePushFlags pushFlag /*= NodePushFlags::None*/)
{
#ifdef MEDUSA_SAFE_CHECK
	if (mScenes.Contains(scene))
	{
		Log::Error("scene has been already pushed.");
		return scene;
	}
#endif

	IScene* originalScene = Current();
	if (originalScene != nullptr)
	{
		if (MEDUSA_FLAG_HAS(pushFlag, NodePushFlags::HideAllPrevs))
		{
			for (auto prevScene : mScenes)
			{
				if (prevScene->IsVisible())
				{
					prevScene->SetVisible(false);
					prevScene->ExitRecursively();
					prevScene->EnableInput(false);
				}
			}
		}

		if (!MEDUSA_FLAG_HAS(pushFlag, NodePushFlags::ShowPrev))
		{
			originalScene->SetVisible(false);
			originalScene->ExitRecursively();
		}
		originalScene->EnableInput(MEDUSA_FLAG_HAS(pushFlag, NodePushFlags::ShowPrev));
	}

	mScenes.Push(scene);
	scene->SetVisible(true);
	scene->EnterRecursively();

	if (!MEDUSA_FLAG_HAS(pushFlag, NodePushFlags::SuppressUpdateLogic))
	{
		scene->UpdateLogicRecursively();
	}

	scene->EnableInput(!MEDUSA_FLAG_HAS(pushFlag, NodePushFlags::DisableTouch));

	mIsSceneChanged = true;

	return scene;
}

IScene* SceneManager::Pop(NodePopFlags popFlag /*= NodePopFlags::None*/)
{
	IScene* scene = Current();
	Log::AssertNotNull(scene, "Scene stack should not be empty when pop.");

	if (!MEDUSA_FLAG_HAS(popFlag, NodePopFlags::ShowCurrent) || MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DeleteCurrent) || MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DeleteCurrentAsync))
	{
		scene->SetVisible(false);
		scene->ExitRecursively();
		scene->EnableInput(false);
	}

	mScenes.Pop();
	mIsSceneChanged = true;

	if (MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DeleteCurrent) || MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DeleteCurrentAsync))
	{
		DeleteScene(scene, MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DeleteCurrentAsync));
		scene = nullptr;
	}

	if (!MEDUSA_FLAG_HAS(popFlag, NodePopFlags::IgnorePrev))
	{
		IScene* prevScene = Current();
		if (prevScene != nullptr)
		{
			prevScene->SetVisible(true);
			prevScene->EnableInput(!MEDUSA_FLAG_HAS(popFlag, NodePopFlags::DisableTouch));
			if (!MEDUSA_FLAG_HAS(popFlag, NodePopFlags::SuppressUpdateLogic))
			{
				prevScene->UpdateLogicRecursively();
			}
		}
	}

	return scene;
}

IScene* SceneManager::ReplaceTo(IScene* scene, NodePopFlags popFlag /*= NodePopFlags::None*/, NodePushFlags pushFlag /*= NodePushFlags::None*/)
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

IScene* SceneManager::Push(const StringRef& className, NodePushFlags pushFlag /*= NodePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	auto node = NodeFactory::Instance().Create(className);
	if (node == nullptr)
	{
		Log::FormatError("Cannot create scene:{}", className);
		return nullptr;
	}

	if (!node->IsA<IScene>())
	{
		Log::FormatError("Node:{} is not a scene.", className);
		SAFE_DELETE(node);
		return nullptr;
	}
	return Push((IScene*)node, pushFlag);
}


IScene* SceneManager::PushEx(const StringRef& className, const FileIdRef& editorFile /*= FileIdRef::Empty*/, const FileIdRef& scriptFile /*= FileIdRef::Empty*/, NodePushFlags pushFlag /*= NodePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	NodeCreateFlags createFlags = (NodeCreateFlags)((uint)pushFlag&(uint)NodeCreateFlags::All);
	auto node = NodeFactory::Instance().Create(className, editorFile, scriptFile, e, createFlags);
	if (node == nullptr)
	{
		Log::FormatError("Cannot create scene:{}", className);
		return nullptr;
	}

	if (!node->IsA<IScene>())
	{
		Log::FormatError("Node:{} is not a scene.", className);
		SAFE_DELETE(node);
		return nullptr;
	}
	return Push((IScene*)node, pushFlag);
}

IScene* SceneManager::ReplaceTo(const StringRef& className, NodePopFlags popFlag /*= NodePopFlags::None*/, NodePushFlags pushFlag /*= NodePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
{
	Pop(popFlag);
	return Push(className, pushFlag, e);
}

IScene* SceneManager::ReplaceToEx(const StringRef& className, const FileIdRef& editorFile /*= FileIdRef::Empty*/, const FileIdRef& scriptFile /*= FileIdRef::Empty*/, NodePopFlags popFlag /*= NodePopFlags::None*/, NodePushFlags pushFlag /*= NodePushFlags::None*/, const IEventArg& e /*= IEventArg::Empty*/)
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

void SceneManager::ShowAlertView(StringRef text, Action callback /*= nullptr*/)
{
	//TODO: show alert view
	if (callback)
	{
		callback();
		MEDUSA_ASSERT_FAILED_SILENT;
	}
}

void SceneManager::ShowAlertView(WStringRef text, Action callback /*= nullptr*/)
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
		for (auto scene : mScenes)
		{
			ISceneGraph* graph = scene->GraphPtr();
			mSceneGraphStage.Add(graph);
		}

		mSceneGraphStage.ApplyOptionToAll(mDisableThreading ? ExecuteOption::Sync : ExecuteOption::Async);
		mIsSceneChanged = false;
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateScene);
		for (auto scene : mScenes)
		{
			scene->UpdateScene(dt);
		}
	}


	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateLayout);
		ResolutionAdapter::Instance().UpdateLayout();
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::VisitScene);
		for (auto scene : mScenes)
		{
			RenderableChangedFlags outFlag;
			//scene->VisitRecursively(mChangedNodeCollector, outFlag);
			scene->VisitScene(mChangedNodeCollector, outFlag);
			scene->Graph().SetChangedFlag(outFlag);
		}
	}

	{
		FrameAutoStopWatch watch(ApplicationStatics::Instance().UpdateWatch(), FrameStep::UpdateRenderQueue);
		for (auto scene : mScenes)
		{
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
