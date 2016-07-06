// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Stack.h"
#include "Node/NodeDefines.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Task/FrameTaskStage.h"
#include "Node/Scene/ChangedNodeCollector.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

class SceneManager :public Singleton < SceneManager >
{
	friend class SceneSweeper;
	friend class Singleton < SceneManager >;
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
	T* Push(NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)PushEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), pushFlag, e); }

	template<typename T>
	T* ReplaceTo(NodePopFlags popFlag = NodePopFlags::None, NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)ReplaceToEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), popFlag, pushFlag, e); }

	IScene* Pop(NodePopFlags popFlag = NodePopFlags::None);
public:
	IScene* Push(const StringRef& className, NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);
	IScene* ReplaceTo(const StringRef& className, NodePopFlags popFlag = NodePopFlags::None, NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);

	IScene* PushEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);
	IScene* ReplaceToEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, NodePopFlags popFlag = NodePopFlags::None, NodePushFlags pushFlag = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);
public:
	IScene* Current()const;

	IScene* ReplaceTo(IScene* scene, NodePopFlags popFlag = NodePopFlags::None, NodePushFlags pushFlag = NodePushFlags::None);
	bool IsSingle()const { return mScenes.Count() == 1; }
	const SceneStack& Scenes() const { return mScenes; }
	SceneStack& MutableScenes() { return mScenes; }
	IScene* Push(IScene* scene, NodePushFlags pushFlag = NodePushFlags::None);

protected:
	bool DeleteScene(IScene* scene, bool isAsync = false);

public:
	void ShowActivityIndicator();
	void HideActivityIndicator();

	void ShowAlertView(StringRef text, Action callback = nullptr);
	void ShowAlertView(WStringRef text, Action callback = nullptr);

	void ShowToast(StringRef text, float duration = 2.0f, ToastPosition position = ToastPosition::Center);
protected:
	SceneStack mScenes;	//scene stack
	bool mIsSceneChanged;


	FrameTaskStage mSceneGraphStage;
	bool mDisableThreading;

	ChangedNodeCollector mChangedNodeCollector;
};

MEDUSA_END;
