// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Stack.h"
#include "Node/NodeDefines.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Task/FrameTaskStage.h"
#include "Node/Scene/ChangedNodeCollector.h"
#include "Node/Scene/ScenePushFlags.h"
#include "Node/Scene/ScenePopFlags.h"

MEDUSA_BEGIN;

class SceneManager :public Singleton < SceneManager >
{
	friend class SceneSweeper;
	friend class Singleton < SceneManager > ;
	SceneManager(void);
	~SceneManager(void);
public:
	typedef Stack<IScene*> SceneStack;
public:
	bool Initialize(bool disableThreading = false);
	bool Uninitialize();
	bool IsEmpty()const { return mScenes.IsEmpty(); }

	void Update(float dt);
	void Draw(float dt);
public:
	template<typename T>
	T* PushScene(ScenePushFlags pushFlag = ScenePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)PushSceneByName(T::ClassNameStatic(), pushFlag, e); }

	template<typename T>
	T* ReplaceToScene(ScenePopFlags popFlag = ScenePopFlags::None, ScenePushFlags pushFlag = ScenePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)ReplaceSceneByName(T::ClassNameStatic(), popFlag, pushFlag, e); }

	IScene* PopScene(ScenePopFlags popFlag = ScenePopFlags::None);
public:
	IScene* PushSceneByName(const StringRef& className, ScenePushFlags pushFlag = ScenePushFlags::None, const IEventArg& e = IEventArg::Empty);
	IScene* ReplaceSceneByName(const StringRef& className, ScenePopFlags popFlag = ScenePopFlags::None, ScenePushFlags pushFlag = ScenePushFlags::None, const IEventArg& e = IEventArg::Empty);
public:
	IScene* RunningScene()const;

	IScene* ReplaceToScene(IScene* scene, ScenePopFlags popFlag = ScenePopFlags::None, ScenePushFlags pushFlag = ScenePushFlags::None);
	bool IsSingleScene()const { return mScenes.Count() == 1; }
	const SceneStack& Scenes() const { return mScenes; }
	SceneStack& MutableScenes() { return mScenes; }
	void PushScene(IScene* scene, ScenePushFlags pushFlag = ScenePushFlags::None);

protected:
	bool DeleteScene(IScene* scene, bool isAsync = false);

public:
	void ShowActivityIndicator();
	void HideActivityIndicator();

	void ShowAlertView(StringRef text, Action0 callback = nullptr);
	void ShowAlertView(WStringRef text, Action0 callback = nullptr);

	void ShowToast(StringRef text, float duration = 2.0f, ToastPosition position = ToastPosition::Center);
protected:
	SceneStack mScenes;	//scene stack
	bool mIsSceneChanged;


	FrameTaskStage mSceneGraphStage;
	bool mDisableThreading;

	ChangedNodeCollector mChangedNodeCollector;
};

MEDUSA_END;
