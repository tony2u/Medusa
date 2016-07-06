// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Core/Collection/Stack.h"
#include "Node/NodeStatus.h"

MEDUSA_BEGIN;

class IScene :public INode
{
	MEDUSA_RTTI(IScene,INode);
public:
	IScene(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~IScene(void);
public:
	virtual bool Is2D()const { return true; }
	ISceneGraph& Graph() { return *mSceneGraph; }
	ISceneGraph* GraphPtr() const { return mSceneGraph; }


	const Share<IRenderTarget>& RenderTarget() const;
	void SetRenderTarget(const Share<IRenderTarget>& val);

	const Share<Camera>& GetCamera() const { return mCamera; }
	void SetCamera(const Share<Camera>& val);

	virtual bool Uninitialize()override;

#pragma region Update
public:
	bool UpdateScene(float dt);
	bool VisitScene(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag = NodeVisitFlags::None, RenderStateType renderStateFlag = RenderStateType::None);
	virtual void VisitRecursively(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag = NodeVisitFlags::None, RenderStateType renderStateFlag = RenderStateType::None)override;

	void MarkVisitQueueChanged() { mIsVisitQueueChanged = true; }


#pragma endregion Update
public://Stack
	ILayer* CurrentLayer()const;

	template<typename T>
	T* PushLayer(NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)PushLayerEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), pushFlags,e); }

	ILayer* PopLayer(NodePopFlags popFlags = NodePopFlags::None);
	void PopAllLayer(NodePopFlags popFlags = NodePopFlags::IgnorePrev);

	template<typename T>
	T* ReplaceToLayer(NodePopFlags popFlags = NodePopFlags::None, NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)ReplaceToLayerEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), popFlags, pushFlags,e); }

	template<typename T>
	T* FindLayer() { return (T*)FindChild(T::ClassNameStatic().Name); }
public:
	ILayer* PushLayer(const StringRef& className, NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);
	ILayer* ReplaceToLayer(const StringRef& className, NodePopFlags popFlags = NodePopFlags::None, NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);

	ILayer* PushLayerEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);
	ILayer* ReplaceToLayerEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, NodePopFlags popFlags = NodePopFlags::None, NodePushFlags pushFlags = NodePushFlags::None, const IEventArg& e = IEventArg::Empty);


	ILayer* PushLayer(ILayer* layer, NodePushFlags pushFlags = NodePushFlags::None);
	ILayer* ReplaceToLayer(ILayer* toLayer, NodePopFlags popFlags = NodePopFlags::None, NodePushFlags pushFlags = NodePushFlags::None);

protected:

	template<typename T>
	void DeleteLayer(NodeDeleteFlags deleteFlags = NodeDeleteFlags::None) { DeleteLayer(T::ClassNameStatic().Name); }
	void DeleteLayers(const List<StringRef>& names, NodeDeleteFlags deleteFlags = NodeDeleteFlags::None);
	bool DeleteLayer(StringRef name, NodeDeleteFlags deleteFlags = NodeDeleteFlags::None);
	bool DeleteLayer(ILayer* layer, NodeDeleteFlags deleteFlags = NodeDeleteFlags::None);

private:
	void OnSaveStatus();
	void OnRestoreStatus();
protected:
	ISceneGraph* mSceneGraph;
	Share<IRenderTarget> mRenderTarget;
	Share<Camera> mCamera;

protected:
	Dictionary<StringRef, ILayer*> mCachedLayers;
	Dictionary<StringRef, NodeStatus> mLayerStatusDict;

#pragma region Update
protected:
	void AddNodeRecursivelyToVisitQueue(INode* node);


protected:
	List<INode*> mVisitNodes;
	bool mIsVisitQueueChanged;

#pragma endregion Update
};

MEDUSA_END;
