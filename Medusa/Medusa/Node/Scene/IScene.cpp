// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IScene.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Resource/Camera/Camera.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Node/Editor/SceneEditorFactory.h"
#include "Core/Command/Processor/MainCommandProcessor.h"
#include "Node/Layer/ILayer.h"
#include "Core/Log/Log.h"
#include "Node/Layer/LayerFactory.h"
#include "Core/Script/ScriptDefines.h"
#include "Node/Scene/SceneFactory.h"
#include "Application/ApplicationStatics.h"
#include "Core/Pattern/IVisitor.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Node/NodeSweeper.h"

MEDUSA_BEGIN;


IScene::IScene(const StringRef& name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:INode(name), mSceneGraph(nullptr)
{
	mScene = this;
	mRenderTarget = nullptr;

	mSize = ResolutionAdapter::Instance().WinSize();

	SetStretch(Stretch::Fill);
	SetSizeToContent(SizeToContent::WidthAndHeight);
	Start();
}


IScene::~IScene(void)
{
	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mCamera);
}

bool IScene::Uninitialize()
{
	SAFE_DELETE(mSceneGraph);
	return true;
}


IRenderTarget* IScene::RenderTarget() const
{
	if (mRenderTarget == nullptr)
	{
		return RenderTargetFactory::Instance().Current();
	}
	return mRenderTarget;
}


void IScene::SetRenderTarget(IRenderTarget* val)
{
	SAFE_ASSIGN_REF(mRenderTarget, val);
}

void IScene::SetCamera(Camera* val)
{
	SAFE_ASSIGN_REF(mCamera, val);
}

Camera* IScene::GetCamera() const
{
	return mCamera;
}

//////////////////////////////////////////////////////////////////////////


ILayer* IScene::CreateLayer(const StringRef& className, const StringRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/, LayerCreateFlags createFlags/*=LayerCreateFlags::None*/)
{
	auto* editor=SceneEditorFactory::Instance().CurrentEditor();
	if (editor!=nullptr)
	{
		return editor->CreateLayer(className,editorFile, e);
	}

	ILayer* layer = LayerFactory::Instance().Create(className, className, e);
	Log::AssertNotNullFormat(layer, "Cannot create layer by name:{}", className.c_str());
	layer->Initialize();

	return layer;
}



bool IScene::DeleteLayer(StringRef editorFile, LayerDeleteFlags deleteFlags/*=LayerDeleteFlags::None*/)
{
	if (deleteFlags.Has(LayerDeleteFlags::Async))
	{
		INode* layer = FindChild(editorFile);
		if (layer != nullptr)
		{
			NodeSweeper::Instance().Add(layer);
		}
		return layer != nullptr;
	}
	else
	{
		return DeleteChild(editorFile);
	}

}


bool IScene::DeleteLayer(ILayer* layer, LayerDeleteFlags deleteFlags /*= LayerDeleteFlags::None*/)
{
	if (deleteFlags.Has(LayerDeleteFlags::Async))
	{
		NodeSweeper::Instance().Add(layer);
		return layer != nullptr;
	}
	else
	{
		return DeleteChild(layer);
	}
}

void IScene::DeleteLayers(const List<StringRef>& names, LayerDeleteFlags deleteFlags/*=LayerDeleteFlags::None*/)
{
	FOR_EACH_COLLECTION(i, names)
	{
		DeleteLayer(*i, deleteFlags);
	}
}

//////////////////////////////////////////////////////////////////////////

ILayer* IScene::CurrentLayer() const
{
	RETURN_NULL_IF_EMPTY(mNodes);
	return (ILayer*)mNodes.Last();
}



void IScene::PushLayerObject(ILayer* layer, LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	Log::Assert(layer != nullptr, "thisLayer should not be null.");
    RETURN_IF_NULL(layer);

#ifdef MEDUSA_SAFE_CHECK
	if (HasChild(layer))
	{
		Log::AssertFailed("The layer pushed is already in layer stack.");
	}
#endif

	if (pushFlags.Has(LayerPushFlags::SaveStatusBeforePush))
	{
		OnSaveStatus();
	}


	ILayer* originalLayer = CurrentLayer();
	if (originalLayer != nullptr)
	{
		if (pushFlags.Has(LayerPushFlags::HideAllPrevLayers))
		{
			FOR_EACH_COLLECTION(i, mNodes)
			{
				INode* prevLayer = *i;
				if (prevLayer->IsVisible())
				{
					prevLayer->SetVisible(false);
					prevLayer->ExitRecursively();
					prevLayer->EnableInput(false);
				}
			}
		}

		if (!pushFlags.Has(LayerPushFlags::ShowPrevLayer))
		{
			originalLayer->SetVisible(false);
			originalLayer->ExitRecursively();
		}
		originalLayer->EnableInput(pushFlags.Has(LayerPushFlags::ShowPrevLayer));
	}

	AddChild(layer);

	layer->SetVisible(true);
	layer->EnterRecursively();

	if (!pushFlags.Has(LayerPushFlags::SuppressUpdateLogic))
	{
		layer->UpdateLogicRecursively();
	}

	layer->EnableInput(!pushFlags.Has(LayerPushFlags::DisableTouch));
}

ILayer* IScene::PushLayerByName(const StringRef& className, const StringRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/, LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	LayerCreateFlags createFlags;
	if (pushFlags.Has(LayerPushFlags::AlwaysCreate))
	{
		createFlags = LayerCreateFlags::AlwaysCreate;
	}

	ILayer* layer = nullptr;
	if (!editorFile.IsEmpty())
	{
		layer = (ILayer*)FindChild(editorFile);
		Log::AssertFormat(layer == nullptr, "Cannot push Layer:{} which is already in stack.", editorFile.c_str());
	}
	
	layer = CreateLayer(className, editorFile, e, createFlags);
	PushLayerObject(layer, pushFlags);

	return layer;
}

ILayer* IScene::PopLayer(LayerPopFlags popFlags/*=LayerPopFlags::None*/)
{
	ILayer* layer = CurrentLayer();
	Log::AssertNotNull(layer, "Layer stack should not be empty when pop.");

	if (!popFlags.Has(LayerPopFlags::ShowCurrentLayer) || popFlags.Has(LayerPopFlags::DeleteCurrentLayer) || popFlags.Has(LayerPopFlags::DeleteCurrentLayerAsync))
	{
		layer->SetVisible(false);
		layer->ExitRecursively();
		layer->EnableInput(false);
	}

	RemoveChild(layer);

	if (popFlags.Has(LayerPopFlags::DeleteCurrentLayer) || popFlags.Has(LayerPopFlags::DeleteCurrentLayerAsync))
	{
		LayerDeleteFlags deleteFlags;
		if (popFlags.Has(LayerPopFlags::DeleteCurrentLayerAsync))
		{
			deleteFlags = LayerDeleteFlags::Async;
		}

		DeleteLayer(layer, deleteFlags);
		layer = nullptr;
	}

	if (!popFlags.Has(LayerPopFlags::IgnorePrevLayer))
	{
		ILayer* prevLayer = CurrentLayer();
		if (prevLayer != nullptr)
		{
			prevLayer->SetVisible(true);
			prevLayer->EnableInput(!popFlags.Has(LayerPopFlags::DisableTouch));
			if (!popFlags.Has(LayerPopFlags::SuppressUpdateLogic))
			{
				prevLayer->UpdateLogicRecursively();
			}
		}
	}

	if (popFlags.Has(LayerPopFlags::RestoreStatusAfterPop))
	{
		OnRestoreStatus();
	}

	return layer;
}

void IScene::PopAllLayer(LayerPopFlags popFlags/*=LayerPopFlags::IgnorePrevLayer*/)
{
	while (!mNodes.IsEmpty())
	{
		PopLayer(popFlags);
	}
}


ILayer* IScene::ReplaceToLayerByName(const StringRef& className, const StringRef& editorFile, const IEventArg& e/*=IEventArg::Empty*/, LayerPopFlags popFlags/*=LayerPopFlags::None*/, LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	PopLayer(popFlags);
	return PushLayerByName(className,editorFile, e, pushFlags);
}

ILayer* IScene::ReplaceToLayerObject(ILayer* toLayer, LayerPopFlags popFlags/*=LayerPopFlags::None*/, LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	ILayer* prevLayer = PopLayer(popFlags);
	PushLayerObject(toLayer, pushFlags);
	return prevLayer;
}

void IScene::OnSaveStatus()
{
	mLayerStatusDict.Clear();
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* layer = *i;
		mLayerStatusDict.Add(layer->Name(), NodeStatus(layer->IsVisible(), layer->IsInputEnabled()));
	}
}

void IScene::OnRestoreStatus()
{
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* layer = *i;
		NodeStatus* statusPtr = mLayerStatusDict.TryGetValue(layer->Name());
		if (statusPtr != nullptr)
		{
			layer->SetVisible(statusPtr->IsVisible);
			layer->EnableInput(statusPtr->InputEnabled);
			if (layer->IsVisible())
			{
				layer->EnterRecursively();
			}
			else
			{
				layer->ExitRecursively();
			}
		}
	}

	mLayerStatusDict.Clear();
}


#pragma region Update

bool IScene::UpdateScene(float dt)
{
	return UpdateRecursively(dt);
}

void IScene::AddNodeRecursivelyToVisitQueue(INode* node)
{
	RETURN_IF_FALSE(node->IsVisible());

	if (node->RenderableChangedFlag() != RenderableChangedFlags::None)
	{
		mVisitNodes.Add(node);
	}

	for (INode* child:node->MutableChildren())
	{
		AddNodeRecursivelyToVisitQueue(child);
	}

}

bool IScene::VisitScene(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag /*= NodeVisitFlags::None*/, RenderStateType renderStateFlag /*= RenderStateUpdateFlags::None*/)
{
	//VisitRecursively(visitor, outFlag, nodeFlag, renderStateFlag);
	//return true;
	if (mIsVisitQueueChanged)
	{
		mVisitNodes.Clear();
		AddNodeRecursivelyToVisitQueue(this);
		mIsVisitQueueChanged = false;
		outFlag|=(RenderableChangedFlags::RenderQueueChanged | RenderableChangedFlags::BatchChanged | RenderableChangedFlags::DataTotalChanged);
	}

	RETURN_TRUE_IF_EMPTY(mVisitNodes);
	ApplicationStatics::Instance().AddVisitNodeCount(mVisitNodes.Count());
	FOR_EACH_COLLECTION(i, mVisitNodes)
	{
		INode* node = *i;
		if (node->NeedVisit())
		{
			node->VisitRecursively(visitor, outFlag, nodeFlag, renderStateFlag);
		}
	}
	mVisitNodes.Clear();

	return true;
}

void IScene::VisitRecursively(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag /*= NodeVisitFlags::None*/, RenderStateType renderStateFlag /*= RenderStateUpdateFlags::None*/)
{
	if (IsWorldMatrixDirty())
	{
		ForceSetWorldMatrix(LocalMatrix());
		nodeFlag |= NodeVisitFlags::ForceUpdateWorldMatrix;
	}

	if (IsWorldColorDirty())
	{
		SetWorldColor(Color());
		nodeFlag |= NodeVisitFlags::ForceUpdateWorldColor;
	}

	if (IsWorldRenderStateDirty())
	{
		MEDUSA_ADD_FLAG(renderStateFlag, mWorldRenderState.DirtyFlag());
		//renderStateFlag |= mWorldRenderState.DirtyFlag();
		ForceUpdateRenderState(renderStateFlag);

	}

	visitor.Visit(this);
	outFlag |= mChangedFlag;

	//update child
	size_t size = mNodes.Count();
	RETURN_IF_ZERO(size);
	FOR_EACH_SIZE(i, size)
	{
		INode* node = mNodes[i];
		if (node->IsVisible())
		{
			node->VisitRecursively(visitor, outFlag, nodeFlag, renderStateFlag);
		}
	}

	mNeedVisit = false;
}


#pragma endregion Update

MEDUSA_IMPLEMENT_RTTI(IScene, INode);





MEDUSA_END;

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterIScene(asIScriptEngine* engine)
{
	int r2;
	r2 = engine->RegisterObjectType(MACRO_TO_STRING(IScene), sizeof(IScene), asOBJ_REF | asOBJ_NOCOUNT); MEDUSA_ASSERT_SILENT(r2 >= 0);
	MEDUSA_SCRIPT_REGISTER_NODE_NEW_DELETE(engine, IScene);

	MEDUSA_SCRIPT_REGISTER_CAST_BASE_DERIVED(engine, INode, IScene);


	RegisterIScene_Methods<IScene>(engine, MACRO_TO_STRING(IScene));

}

MEDUSA_SCRIPT_END;
#endif
