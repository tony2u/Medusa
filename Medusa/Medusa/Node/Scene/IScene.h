// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Core/Collection/Stack.h"
#include "Core/Command/EventArg/IEventArg.h"

#include "Node/Layer/LayerCreateFlags.h"
#include "Node/Layer/LayerDeleteFlags.h"
#include "Node/Layer/LayerPushFlags.h"
#include "Node/Layer/LayerPopFlags.h"
#include "Node/NodeStatus.h"
#include "Core/Collection/LinkedList.h"


MEDUSA_BEGIN;

#define MEDUSA_DECLARE_SCENE 													\
		MEDUSA_DECLARE_RTTI;\
private:																				\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define MEDUSA_IMPLEMENT_SCENE(className,baseClassName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);\
	const StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){SceneFactory::Instance().Register<className>(#className);}


class IScene :public INode
{
	MEDUSA_DECLARE_RTTI;
public:
	typedef LinkedList<INode*> TempUpdateNodeList;

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
	T* PushLayer(LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)PushLayerByName(T::ClassNameStatic(),T::EditorFileNameStatic(), e, pushFlags); }

	ILayer* PopLayer(LayerPopFlags popFlags = LayerPopFlags::None);
	void PopAllLayer(LayerPopFlags popFlags = LayerPopFlags::IgnorePrevLayer);

	template<typename T>
	T* ReplaceToLayer(LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None, const IEventArg& e = IEventArg::Empty) { return (T*)ReplaceToLayerByName(T::ClassNameStatic(),T::EditorFileNameStatic(),e, popFlags, pushFlags); }

	template<typename T>
	T* FindLayer() { return (T*)FindChild(T::EditorFileNameStatic()); }
public:
	ILayer* PushLayerByName(const StringRef& className, const StringRef& editorFile, const IEventArg& e = IEventArg::Empty, LayerPushFlags pushFlags = LayerPushFlags::None);
	void PushLayerObject(ILayer* layer, LayerPushFlags pushFlags = LayerPushFlags::None);

	ILayer* ReplaceToLayerByName(const StringRef& className,const StringRef& editorFile, const IEventArg& e = IEventArg::Empty, LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None);
	ILayer* ReplaceToLayerObject(ILayer* toLayer, LayerPopFlags popFlags = LayerPopFlags::None, LayerPushFlags pushFlags = LayerPushFlags::None);

	
protected:	

	template<typename T>
	void DeleteLayer(LayerDeleteFlags deleteFlags = LayerDeleteFlags::None) { DeleteLayer(T::EditorFileNameStatic()); }
	void DeleteLayers(const List<StringRef>& names, LayerDeleteFlags deleteFlags = LayerDeleteFlags::None);
	bool DeleteLayer(StringRef editorFile, LayerDeleteFlags deleteFlags = LayerDeleteFlags::None);
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

	size_t mTotalNodeCount;
#pragma endregion Update
};

MEDUSA_END;


#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterIScene(asIScriptEngine* engine);

template <class T>
void RegisterIScene_Methods(asIScriptEngine* engine, const char* typeName)
{
	RegisterINode_Methods<IScene>(engine, typeName);

}

MEDUSA_SCRIPT_END;
#endif