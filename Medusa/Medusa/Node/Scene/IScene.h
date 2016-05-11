// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Core/Collection/Stack.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Node/NodeStatus.h"
#include "Core/IO/FileIdRef.h"
#include "Node/NodeDefines.h"

MEDUSA_BEGIN;

#define MEDUSA_DECLARE_SCENE_ROOT(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const FileIdRef& EditorFileName()const{return mEditorFileName;}									\
	static const FileIdRef& EditorFileNameStatic(){return mEditorFileName;}									\
	virtual const FileIdRef& ScriptFileName()const{return mScriptFileName;}									\
	static const FileIdRef& ScriptFileNameStatic(){return mScriptFileName;}									\
private:																				\
	const static FileIdRef mEditorFileName;							\
	const static FileIdRef mScriptFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_DECLARE_SCENE(className) 													\
		MEDUSA_DECLARE_RTTI;\
public:																				\
	virtual const FileIdRef& EditorFileName()const override{return mEditorFileName;}									\
	static const FileIdRef& EditorFileNameStatic(){return mEditorFileName;}									\
	virtual const FileIdRef& ScriptFileName()const override{return mScriptFileName;}									\
	static const FileIdRef& ScriptFileNameStatic(){return mScriptFileName;}									\
private:																				\
	const static FileIdRef mEditorFileName;							\
	const static FileIdRef mScriptFileName;							\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_SCENE(className,baseClassName,editorFile,scriptFile) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const FileIdRef className::mEditorFileName=editorFile;					 \
const FileIdRef className::mScriptFileName=scriptFile;					 \
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){SceneFactory::Instance().Register<className>(#className);}


class IScene :public INode
{
	MEDUSA_DECLARE_SCENE(IScene);
public:
	IScene(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~IScene(void);
public:
	virtual bool Is2D()const { return true; }
	ISceneGraph& Graph() { return *mSceneGraph; }
	ISceneGraph* GraphPtr() const { return mSceneGraph; }


	IRenderTarget* RenderTarget() const;
	void SetRenderTarget(IRenderTarget* val);

	Camera* GetCamera() const;
	void SetCamera(Camera* val);

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
	T* PushLayer(LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)PushLayerEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), pushFlags,e); }

	ILayer* PopLayer(LayerPopFlags popFlags = LayerPopFlags::None);
	void PopAllLayer(LayerPopFlags popFlags = LayerPopFlags::IgnorePrevLayer);

	template<typename T>
	T* ReplaceToLayer(LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)ReplaceToLayerEx(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), popFlags, pushFlags,e); }

	template<typename T>
	T* FindLayer() { return (T*)FindChild(T::ClassNameStatic().Name); }
public:
	ILayer* PushLayer(const StringRef& className, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty);
	ILayer* ReplaceToLayer(const StringRef& className, LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty);

	ILayer* PushLayerEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty);
	ILayer* ReplaceToLayerEx(const StringRef& className, const FileIdRef& editorFile = FileIdRef::Empty, const FileIdRef& scriptFile = FileIdRef::Empty, LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty);


	void PushLayer(ILayer* layer, LayerPushFlags pushFlags = LayerPushFlags::None);
	ILayer* ReplaceToLayer(ILayer* toLayer, LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None);

protected:

	template<typename T>
	void DeleteLayer(LayerDeleteFlags deleteFlags = LayerDeleteFlags::None) { DeleteLayer(T::ClassNameStatic().Name); }
	void DeleteLayers(const List<StringRef>& names, LayerDeleteFlags deleteFlags = LayerDeleteFlags::None);
	bool DeleteLayer(StringRef name, LayerDeleteFlags deleteFlags = LayerDeleteFlags::None);
	bool DeleteLayer(ILayer* layer, LayerDeleteFlags deleteFlags = LayerDeleteFlags::None);

private:
	void OnSaveStatus();
	void OnRestoreStatus();
protected:
	ISceneGraph* mSceneGraph;
	IRenderTarget* mRenderTarget;
	Camera* mCamera;

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
