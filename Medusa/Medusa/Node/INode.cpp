// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/INode.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Pattern/LazyStrongPtr.inl"
#include "Core/Action/BaseActionRunner.h"
#include "Resource/Model/IModel.h"
#include "Node/Input/InputManager.h"
#include "Node/Scene/IScene.h"
#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Core/Log/Log.h"
#include "Graphics/ResolutionAdapter.h"
#include "Node/Input/InputDispatcher.h"
#include "Core/Collection/STLPort.h"
#include "Core/Math/Random/Random.h"
#include "Node/NodeFactory.h"
#include "Node/Shape/IShape.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Core/Pattern/IVisitor.h"
#include "Node/Scene/SceneManager.h"
#include "Application/ApplicationStatics.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Geometry/Geometry.h"
#include "Core/Script/ScriptEngine.h"
#include "Node/Component/NodeScriptComponent.h"
#include "Node/Binding/IDataBinding.h"

MEDUSA_BEGIN;

INode::INode(const StringRef& name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IRenderable(name), DefaultRunnable(RunningState::None)
{
	Start();
	MutableInput().Enable(false);	//default disable input
}


INode::~INode(void)
{
	ResolutionAdapter::Instance().TryRemoveDirytNode(this);

	SAFE_DELETE(mInputDispatcher);
	SAFE_DELETE_COLLECTION(mNodes);
	mNodeDict.Clear();
	mManagedNodes.Clear();

	SAFE_DELETE(mBinding);
}


void INode::Clear(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	DeleteAllChilds(flags);
}

void INode::RemoveFromParent()
{
	if (mParent != nullptr)
	{
		mParent->RemoveChild(this);
	}
}

void INode::DeleteFromParent()
{
	if (mParent != nullptr)
	{
		mParent->DeleteChild(this);
	}
}


void INode::AddChild(INode* node)
{
	MEDUSA_ASSERT_NULL(node->Parent(), "");
	MEDUSA_ASSERT(node!=this, "");

	mNodes.Add(node);
	node->SetParent(this);
	if (!node->Name().IsEmpty())
	{
		mNodeDict.Add(node->Name(), node);
	}

	if (node->IsManaged())
	{
		mManagedNodes.Add(node);
	}

	OnLayoutChanged(*node, NodeLayoutChangedFlags::ChildAdded);
	OnRenderQueueChanged();
	OnVisitQueueChanged();
}

bool INode::RemoveChild(INode* node)
{
	RETURN_FALSE_IF_NULL(node);
	if (mNodes.RemoveFirst(node))
	{
		node->SetParent(nullptr);
		mNodeDict.RemoveKey(node->Name());

		if (node->IsManaged())
		{
			mManagedNodes.RemoveFirst(node);
		}

		OnLayoutChanged(*node, NodeLayoutChangedFlags::ChildRemoved);

		OnRenderQueueChanged();
		OnVisitQueueChanged();
		return true;
	}
	return false;

}

bool INode::RemoveChild(const StringRef& name)
{
	INode* node = FindChild(name);
	RETURN_FALSE_IF_NULL(node);
	return RemoveChild(node);
}


void INode::RemoveAllChilds(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	RETURN_IF_EMPTY(mNodes);
	if (mManagedNodes.Count() == mNodes.Count())
	{
		flags = NodeRemoveFlags::All;
	}

	bool hasManaged = !mManagedNodes.IsEmpty();

	switch (flags)
	{
	case NodeRemoveFlags::OnlyChildren:
		if (hasManaged)
		{
			List<size_t> removedIndices;
			size_t count = mNodes.Count();
			FOR_EACH_SIZE(i, count)
			{
				INode* node = mNodes[i];
				if (!mManagedNodes.Contains(node))
				{
					node->SetParent(nullptr);
					removedIndices.Add(i);
					StringRef name = node->Name();
					if (!name.IsEmpty())
					{
						mNodeDict.RemoveKey(name);
					}
				}
			}

			mNodes.RemoveIndexes(removedIndices);
		}
		else
		{
			FOR_EACH_TO(mNodes, SetParent(nullptr));
			mNodes.Clear();
			mNodeDict.Clear();
		}
		break;
	case NodeRemoveFlags::OnlyManaged:
		RETURN_IF_FALSE(hasManaged);
		FOR_EACH_APPLY(mManagedNodes, RemoveChild);
		mManagedNodes.Clear();
		break;
	case NodeRemoveFlags::All:
		RETURN_IF_FALSE(hasManaged);
		FOR_EACH_TO(mNodes, SetParent(nullptr));
		mNodes.Clear();
		mNodeDict.Clear();
		mManagedNodes.Clear();

		break;
	default:
		break;
	}
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ChildRemoved);

	OnRenderQueueChanged();
	OnVisitQueueChanged();
}

bool INode::DeleteChild(INode* node)
{
	RETURN_FALSE_IF_NULL(node);
	if (mNodes.RemoveFirst(node))
	{
		mNodeDict.RemoveKey(node->Name());
		if (node->IsManaged())
		{
			mManagedNodes.Remove(node);
		}

		OnLayoutChanged(*node, NodeLayoutChangedFlags::ChildRemoved);

		OnRenderQueueChanged();
		OnVisitQueueChanged();
		SAFE_DELETE(node);


		return true;
	}
	return false;
}

bool INode::DeleteChild(const StringRef& name)
{
	INode* node = FindChild(name);
	RETURN_FALSE_IF_NULL(node);
	return DeleteChild(node);
}


void INode::DeleteAllChilds(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	RETURN_IF_EMPTY(mNodes);

	bool hasManaged = !mManagedNodes.IsEmpty();
	if (mManagedNodes.Count() == mNodes.Count())
	{
		flags = NodeRemoveFlags::All;
	}

	switch (flags)
	{
	case NodeRemoveFlags::OnlyChildren:
		if (hasManaged)
		{
			List<size_t> removedIndices;
			size_t count = mNodes.Count();
			FOR_EACH_SIZE(i, count)
			{
				INode* node = mNodes[i];
				if (!mManagedNodes.Contains(node))
				{
					removedIndices.Add(i);
					StringRef name = node->Name();
					if (!name.IsEmpty())
					{
						mNodeDict.RemoveKey(name);
					}
				}
			}

			Linq::DeleteIndexes(mNodes, removedIndices);
		}
		else
		{
			SAFE_DELETE_COLLECTION(mNodes);
			mNodeDict.Clear();
		}
		break;
	case NodeRemoveFlags::OnlyManaged:
		RETURN_IF_FALSE(hasManaged);
		FOR_EACH_APPLY(mManagedNodes, DeleteChild);
		mManagedNodes.Clear();
		break;
	case NodeRemoveFlags::All:
		RETURN_IF_FALSE(hasManaged);
		SAFE_DELETE_COLLECTION(mNodes);
		mNodeDict.Clear();
		mManagedNodes.Clear();

		break;
	default:
		break;
	}
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ChildCleard);

	OnRenderQueueChanged();
	OnVisitQueueChanged();
}

INode* INode::FindChildWithId(uintp id)
{
	for(auto node: mNodes)
	{
		if (node->Id() == id)
		{
			return node;
		}
	}

	return nullptr;
}

INode* INode::FirstChild()
{
	RETURN_NULL_IF_EMPTY(mNodes);
	return mNodes.First();
}

const INode* INode::FirstChild() const
{
	RETURN_NULL_IF_EMPTY(mNodes);
	return mNodes.First();
}


bool INode::HasChild(INode* node) const
{
	return mNodes.Contains(node);
}

bool INode::HasChild(StringRef name) const
{
	return FindChild(name) != nullptr;
}

bool INode::HasChildRecursively(INode* node) const
{
	bool hasChild = HasChild(node);
	RETURN_TRUE_IF_TRUE(hasChild);

	for(auto i: mNodes)
	{
		hasChild = i->HasChildRecursively(node);
		RETURN_TRUE_IF_TRUE(hasChild);
	}
	return false;
}

bool INode::HasChildRecursively(StringRef name) const
{
	return FindChild(name) != nullptr;
}


INode* INode::FindChildRecursively(StringRef name)
{
	INode* node = FindChild(name);
	RETURN_SELF_IF_NOT_NULL(node);

	for (auto i : mNodes)
	{
		node = i;
		node = node->FindChildRecursively(name);
		RETURN_SELF_IF_NOT_NULL(node);
	}
	return nullptr;
}

const INode* INode::FindChildRecursively(StringRef name) const
{
	const INode* node = FindChild(name);
	RETURN_SELF_IF_NOT_NULL(node);

	for (auto i : mNodes)
	{
		node = i;
		node = node->FindChildRecursively(name);
		RETURN_SELF_IF_NOT_NULL(node);
	}
	return nullptr;
}


void INode::SetParent(INode* val)
{
	RETURN_IF_EQUAL(mParent, val);

	mParent = val;
	SetParentMoveable(mParent);
	SetParentRenderable(mParent);
	if (mParent == nullptr)
	{
		mScene = nullptr;
	}
}


IScene* INode::TryGetRootScene() const
{
	RETURN_SELF_IF_NOT_NULL(mScene);
	INode* parent = mParent;
	while (parent != nullptr && !parent->IsA<IScene>())
	{
		parent = parent->Parent();
	}

	return (IScene*)parent;
}

INode* INode::FindChild(StringRef name)
{
	return mNodeDict.GetOptional(name, nullptr);
}

const INode* INode::FindChild(StringRef name) const
{
	return mNodeDict.GetOptional(name, nullptr);
}

void INode::ReorderAllChilds()
{
	mNodes.Sort();
	OnLayoutChanged(*this, NodeLayoutChangedFlags::ChildOrderChanged);
	OnRenderQueueChanged();
}


void INode::OnMoveableDirty(MoveableChangedFlags changedFlags)
{
	IRenderable::OnMoveableDirty(changedFlags);
	if (MEDUSA_FLAG_HAS(changedFlags, MoveableChangedFlags::SizeChanged))
	{
		OnLayoutSizeChanged(mSize);
		OnLayoutChanged(*this, NodeLayoutChangedFlags::SizeChanged);

		if (mDebugDrawShape != nullptr)
		{
			auto quadMesh = mDebugDrawShape->Mesh().CastPtr<ShapeGeneralMesh>();
			quadMesh->ExpandVertexRectSize(mSize.To2D());	//it will override debugBounding box
		}
	}
}



#pragma region Update

void INode::SetRenderingPriorityRecursively(RenderingPriority val)
{
	SetRenderingPriority(val);
	FOR_EACH_TO(mNodes, SetRenderingPriorityRecursively(val));
}


void INode::SetRenderingStrategyRecursively(RenderingStrategy val)
{
	SetRenderingStrategy(val);
	FOR_EACH_TO(mNodes, SetRenderingStrategyRecursively(val));
}


void INode::SetMeshFixTypeRecursively(MeshFixType val)
{
	SetMeshFixType(val);
	FOR_EACH_TO(mNodes, SetMeshFixTypeRecursively(val));
}

bool INode::UpdateRecursively(float dt, const NodeUpdateFlags& flag/*=NodeUpdateFlags::None*/)
{
	size_t count = mNodes.Count();
	if (count == 0)
	{
		ApplicationStatics::Instance().AddUpdateNodeCount();
		RETURN_FALSE_IF_FALSE(OnBeforeUpdate(dt, flag));
		RETURN_FALSE_IF_FALSE(Update(dt, flag));
		return OnAfterUpdate(dt, flag);
	}
	else
	{
		ApplicationStatics::Instance().AddTotalNodeCount(count);

		RETURN_FALSE_IF_FALSE(OnBeforeUpdate(dt, flag));
		count = mNodes.Count();	//re count node if child node is removed in OnBeforeUpdate

		intp i = (intp)count - 1;
		for (; i >= 0; --i)
		{
			INode* child = mNodes[i];
			BREAK_IF(child->mDepth < 0);
			if (child->ForceIsRunning())
			{
				RETURN_FALSE_IF_FALSE(child->UpdateRecursively(dt, flag));
			}
		}

		ApplicationStatics::Instance().AddUpdateNodeCount();
		RETURN_FALSE_IF_FALSE(Update(dt, flag));

		for (; i >= 0; --i)
		{
			INode* child = mNodes[i];
			if (child->ForceIsRunning())
			{
				RETURN_FALSE_IF_FALSE(child->UpdateRecursively(dt, flag));
			}
		}

		RETURN_FALSE_IF_FALSE(OnAfterUpdate(dt, flag));

	}


	return true;
}


bool INode::Update(float dt, NodeUpdateFlags flag/*=NodeUpdateFlags::None*/)
{
	if (mInputDispatcher != nullptr)
	{
		mInputDispatcher->Update(dt);
	}

	//update components
	IEntity::UpdateComponents(dt);
	//update action
	if (!MEDUSA_FLAG_HAS(flag, NodeUpdateFlags::SuppressRunningAction))
	{
		BaseActionRunner::UpdateActions(dt);
	}
	return OnUpdate(dt, flag);
}

void INode::VisitRecursively(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag /*= NodeVisitFlags::None*/, RenderStateType renderStateFlag /*= RenderStateUpdateFlags::None*/)
{
	if (MEDUSA_FLAG_HAS(nodeFlag, NodeVisitFlags::ForceUpdateWorldMatrix))
	{
		ForceSetWorldMatrix(LocalMatrix()*mParent->WorldMatrix());
	}
	else
	{
		if (IsWorldMatrixDirty())
		{
			ForceSetWorldMatrix(LocalMatrix()*mParent->WorldMatrix());
			MEDUSA_FLAG_ADD(nodeFlag, NodeVisitFlags::ForceUpdateWorldMatrix);
		}
	}

	//update color
	if (MEDUSA_FLAG_HAS(nodeFlag, NodeVisitFlags::ForceUpdateWorldColor))
	{
		SetWorldColor(Color()*mParent->WorldColor());
	}
	else
	{
		if (IsWorldColorDirty())
		{
			SetWorldColor(Color()*mParent->WorldColor());
			MEDUSA_FLAG_ADD(nodeFlag, NodeVisitFlags::ForceUpdateWorldColor);
		}
	}

	//update state
	if (renderStateFlag != RenderStateType::None)
	{
		MEDUSA_FLAG_ADD(renderStateFlag, mWorldRenderState.DirtyFlag());
		ForceUpdateRenderState(renderStateFlag);

	}
	else
	{
		if (IsWorldRenderStateDirty())
		{
			MEDUSA_FLAG_ADD(renderStateFlag, mWorldRenderState.DirtyFlag());
			ForceUpdateRenderState(renderStateFlag);
		}
	}

	visitor.Visit(this);
	MEDUSA_FLAG_ADD(outFlag, mChangedFlag);

	//update child
	size_t size = mNodes.Count();
	RETURN_IF_ZERO(size);
	FOR_EACH_SIZE(i, size)
	{
		INode* node = mNodes[i];
		//have to visit every node include hidden node! or the hidden node will be in wrong matrix if visible again
		node->VisitRecursively(visitor, outFlag, nodeFlag, renderStateFlag);
	}

	mNeedVisit = false;

}


bool INode::EnterRecursively()
{
	size_t count = mNodes.Count();
	intp i = (intp)count - 1;
	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		BREAK_IF(child->Depth() < 0);
		RETURN_FALSE_IF_FALSE(child->EnterRecursively());
	}

	RETURN_FALSE_IF_FALSE(OnEnter());
	RETURN_FALSE_IF_FALSE(IEntity::EnterComponents());


	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		RETURN_FALSE_IF_FALSE(child->EnterRecursively());
	}

	return true;
}

bool INode::ExitRecursively()
{
	size_t count = mNodes.Count();
	intp i = (intp)count - 1;
	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		BREAK_IF(child->Depth() < 0);
		RETURN_FALSE_IF_FALSE(child->ExitRecursively());
	}

	RETURN_FALSE_IF_FALSE(OnExit());
	RETURN_FALSE_IF_FALSE(IEntity::ExitComponents());

	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		RETURN_FALSE_IF_FALSE(child->ExitRecursively());
	}

	return true;
}


bool INode::UpdateLogicRecursively()
{
	size_t count = mNodes.Count();
	intp i = (intp)count - 1;
	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		BREAK_IF(child->Depth() < 0);
		RETURN_FALSE_IF_FALSE(child->UpdateLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(OnUpdateLogic());

	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		RETURN_FALSE_IF_FALSE(child->UpdateLogicRecursively());
	}

	return true;
}

bool INode::ResetLogicRecursively()
{
	size_t count = mNodes.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		BREAK_IF(child->Depth() < 0);
		RETURN_FALSE_IF_FALSE(child->ResetLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(OnResetLogic());

	for (; i >= 0; --i)
	{
		INode* child = mNodes[i];
		RETURN_FALSE_IF_FALSE(child->ResetLogicRecursively());
	}

	return true;
}


void INode::OnVisitQueueChanged()
{
	if (mScene == nullptr)
	{
		mScene = TryGetRootScene();
	}

	if (mScene != nullptr)
	{
		mScene->MarkVisitQueueChanged();
		mNeedVisit = true;
	}
}
void INode::OnRenderChanged(RenderableChangedFlags flag)
{
	bool val = MEDUSA_FLAG_HAS(flag, RenderableChangedFlags::RenderQueueChanged);
	val |= MEDUSA_FLAG_HAS(flag, RenderableChangedFlags::BatchChanged);
	val |= MEDUSA_FLAG_HAS(flag, RenderableChangedFlags::DataTotalChanged);
	val |= MEDUSA_FLAG_HAS(flag, RenderableChangedFlags::NewColor);
	if (val)
	{
		OnVisitQueueChanged();
	}
}

void INode::OnMeshChanged(RenderableChangedFlags flag)
{
	IRenderable::OnMeshChanged(flag);
	if (this->mSizeToContent == SizeToContent::Mesh)
	{
		if (mRenderingObject.Mesh() != nullptr)
		{
			SetSize(mRenderingObject.Mesh()->Size());
		}
		else
		{
			SetSize(Size2F::Zero);
		}
	}

}

#pragma endregion Update

#pragma region Event

const InputDispatcher& INode::Input() const
{
	if (mInputDispatcher == nullptr)
	{
		mInputDispatcher = new InputDispatcher((INode*)this);
	}
	return *mInputDispatcher;
}

InputDispatcher& INode::MutableInput()
{
	if (mInputDispatcher == nullptr)
	{
		mInputDispatcher = new InputDispatcher(this);
	}
	return *mInputDispatcher;
}




#pragma endregion Event

#pragma region Layout


void INode::UpdateLayout(const Size2F& availableSize/*=Size2F::Zero*/)
{
	RETURN_IF_FALSE(mLayoutEnabled);
	if (availableSize != Size2F::Zero)
	{
		Measure(availableSize);
		ArrangeRecursively(Rect2F(Point2F::Zero, availableSize));
	}
	else
	{
		Size2F newAvailableSize;
		if (mParent != nullptr)
		{
			newAvailableSize = mSize.To2D();

			//newAvailableSize=mParent->Size().To2D();
		}
		else
		{
			//newAvailableSize=ResolutionAdapter::Instance().GetWinSize();
			newAvailableSize = mSize.To2D();
		}
		Measure(newAvailableSize);
		ArrangeRecursively(Rect2F(Point2F::Zero, newAvailableSize));
	}
}


void INode::OnLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)
{
	RETURN_IF_FALSE(mLayoutEnabled);
	//RETURN_IF_FALSE(IsSensitiveToChildLayoutChanged(sender, changedFlag));

	bool isNewAdd = ResolutionAdapter::Instance().TryAddDirytNode(this);
	RETURN_IF_FALSE(isNewAdd);

	INode* parent = mParent;
	const ILayoutable* self = &sender;
	while (parent != nullptr)
	{
		RETURN_IF(ResolutionAdapter::Instance().IsNodeLayoutDirty(parent));

		RETURN_IF_FALSE(parent->IsSensitiveToChildLayoutChanged(*self, changedFlag));
		ResolutionAdapter::Instance().TryAddDirytNode(parent);

		self = parent;
		parent = parent->Parent();
	}

}


void INode::Measure(const Size2F& availableSize)
{
	RETURN_IF(mIsCollapsed);

	OnBeforeMeasure(availableSize);

	size_t size = mNodes.Count();
	FOR_EACH_SIZE(i, size)
	{
		INode* node = mNodes[i];
		node->Measure(mMeasuredSize);
	}

	OnAfterMeasure(availableSize);
}

void INode::OnBeforeMeasure(const Size2F& availableSize)
{
	switch (mStretch)
	{
	case Stretch::Fill:
		mMeasuredSize = availableSize;
		break;
	case Stretch::FillWidth:
		if (Math::IsZero(mStretchAspectRatio) && !Math::IsZero(mSize.Height))
		{
			mStretchAspectRatio = mSize.Width / mSize.Height;
		}
		Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::FillWidth.");
		mMeasuredSize.Width = availableSize.Width;
		mMeasuredSize.Height = availableSize.Width / mStretchAspectRatio;
		break;
	case Stretch::FillHeight:
		if (Math::IsZero(mStretchAspectRatio) && !Math::IsZero(mSize.Height))
		{
			mStretchAspectRatio = mSize.Width / mSize.Height;
		}
		Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::FillHeight.");
		mMeasuredSize.Height = availableSize.Height;
		mMeasuredSize.Width = availableSize.Height*mStretchAspectRatio;
		break;
	case Stretch::Uniform:
	{
		if (Math::IsZero(mStretchAspectRatio)&&!Math::IsZero(mSize.Height))
		{
			mStretchAspectRatio = mSize.Width / mSize.Height;
		}

		Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::Uniform.");
		if (Math::IsZero(mSize.Width) || Math::IsZero(mSize.Height))
		{
			if (availableSize.Width < availableSize.Height)
			{
				//fill width
				mMeasuredSize.Width = availableSize.Width;
				mMeasuredSize.Height = availableSize.Width / mStretchAspectRatio;
			}
			else
			{
				//fill height
				mMeasuredSize.Height = availableSize.Height;
				mMeasuredSize.Width = availableSize.Height * mStretchAspectRatio;
			}
		}
		else
		{
			float scaleX = availableSize.Width / mSize.Width;
			float scaleY = availableSize.Height / mSize.Height;
			float scale = Math::Min(scaleX, scaleY);
			mMeasuredSize.Width = mSize.Width*scale;
			mMeasuredSize.Height = mSize.Height*scale;
		}

	}
	break;
	case Stretch::UniformToFill:
	{
		if (Math::IsZero(mStretchAspectRatio) && !Math::IsZero(mSize.Height))
		{
			mStretchAspectRatio = mSize.Width / mSize.Height;
		}
		Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::UniformToFill.");
		if (Math::IsZero(mSize.Width) || Math::IsZero(mSize.Height))
		{
			if (availableSize.Width > availableSize.Height)
			{
				//fill width
				mMeasuredSize.Width = availableSize.Width;
				mMeasuredSize.Height = availableSize.Width / mStretchAspectRatio;
			}
			else
			{
				//fill height
				mMeasuredSize.Height = availableSize.Height;
				mMeasuredSize.Width = availableSize.Height * mStretchAspectRatio;
			}
		}
		else
		{
			float scaleX = availableSize.Width / mSize.Width;
			float scaleY = availableSize.Height / mSize.Height;
			float scale = Math::Max(scaleX, scaleY);

			mMeasuredSize.Width = mSize.Width*scale;
			mMeasuredSize.Height = mSize.Height*scale;
		}
	}
	break;
	case Stretch::Percent:
		mMeasuredSize.Width = availableSize.Width*mStretchPercent.X;
		mMeasuredSize.Height = availableSize.Height*mStretchPercent.Y;
		break;
	case Stretch::ExpandWidth:
		if (availableSize.Width > mSize.Width)
		{
			float scale = Math::IsZero(mSize.Width) ? 0.f : availableSize.Width / mSize.Width;
			mMeasuredSize.Width = availableSize.Width;
			mMeasuredSize.Height = mSize.Height*scale;
		}
		else
		{
			mMeasuredSize = mSize.To2D();
		}
		break;
	case Stretch::ExpandHeight:
		if (availableSize.Height > mSize.Height)
		{
			float scale = Math::IsZero(mSize.Height) ? 0.f : availableSize.Height / mSize.Height;
			mMeasuredSize.Height = availableSize.Height;
			mMeasuredSize.Width = mSize.Width*scale;
		}
		else
		{
			mMeasuredSize = mSize.To2D();
		}
		break;
	case Stretch::None:
		mMeasuredSize = mSize.To2D();
	default:
		break;
	}

	if (mMinSize != Size2F::Zero)
	{
		mMeasuredSize.Width = Math::Max(mMeasuredSize.Width, mMinSize.Width);
		mMeasuredSize.Height = Math::Max(mMeasuredSize.Width, mMinSize.Height);
	}

	if (mMaxSize != Size2F::Zero)
	{
		mMeasuredSize.Width = Math::Min(mMeasuredSize.Width, mMaxSize.Width);
		mMeasuredSize.Height = Math::Min(mMeasuredSize.Width, mMaxSize.Height);
	}

	switch (mSizeToContent)
	{
	case SizeToContent::None:
		break;
	case SizeToContent::Width:
		SetWidth(mMeasuredSize.Width);
		break;
	case SizeToContent::Height:
		SetHeight(mMeasuredSize.Height);
		break;
	case SizeToContent::WidthAndHeight:
		SetSize(mMeasuredSize);
		break;
	default:
		break;
	}
}

void INode::OnAfterMeasure(const Size2F& availableSize)
{

}


Rect2F INode::ArrangeSelf(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	Rect2F resultRect;
	if (mStretch != Stretch::None)
	{
		Scale2F outScale;
		Geometry::StretchToRect(mSize.To2D(), limitRect, mStretch, mStretchPercent, outScale, resultRect.Size);
		SetScale(outScale.X, outScale.Y, mScale.Z);
	}
	/*else
	{
		resultRect.Size = mSize.To2D();
	}*/
	resultRect.Size = mSize.To2D();	//keep result size as it already has scaled so have to offer children original size


	if (mDockPoint != DockPoint::None)
	{
		resultRect.Origin = DockToRect(limitRect, this->mDockPoint, mRelativePosition);
	}
	else
	{
		resultRect.Origin = mPosition.To2D();
	}

	if (mMarginEdge != MarginEdges::None)
	{
		auto boundingBox= GetBoundingBox();
		auto newOrigin= Geometry::ApplyMargin(boundingBox.To2D(), limitRect, mMarginEdge, mMargin);
		resultRect.Origin += newOrigin - boundingBox.Origin.To2D();
		SetPosition(resultRect.Origin.X, resultRect.Origin.Y, mPosition.Z);
	}

	resultRect.Origin = Point2F::Zero;
	return resultRect;
}


bool INode::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	size_t size = mNodes.Count();
	FOR_EACH_SIZE(i, size)
	{
		INode* node = mNodes[i];
		node->ArrangeRecursively(limitRect, arrangeFlags);
	}
	return true;
}

bool INode::ArrangeRecursively(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_FALSE_IF(mIsCollapsed);
	RETURN_FALSE_IF_FALSE(mLayoutEnabled);

	Rect2F outRect;
	if (limitRect.IsEmpty())
	{
		outRect.Origin = Point2F::Zero;
		outRect.Size = mMeasuredSize;
	}
	else
	{
		outRect = limitRect;
	}

	if (!MEDUSA_FLAG_HAS(arrangeFlags, NodeLayoutArrangeFlags::SuppressArrangeSelf))
	{
		outRect = ArrangeSelf(outRect, arrangeFlags);
	}
	else
	{
		MEDUSA_FLAG_REMOVE(arrangeFlags, NodeLayoutArrangeFlags::SuppressArrangeSelf);
	}

	RETURN_TRUE_IF(MEDUSA_FLAG_HAS(arrangeFlags, NodeLayoutArrangeFlags::SuppressArrangeChildren));

	return ArrangeChildren(outRect, arrangeFlags);
}


Point2F INode::DockToRect(const Rect2F& rect, DockPoint dock, const Point2F& relativePosition/*=Point2F::Zero*/)
{
	Point2F pos = Geometry::DockToRect(rect, dock, relativePosition);
	SetPosition(pos.X, pos.Y, mPosition.Z);
	return pos;
}

Point2F INode::DockToScreen(DockPoint dock, const Point2F& relativePosition /*= Point2F::Zero*/)
{
	return DockToRect(ResolutionAdapter::Instance().WinRect(), dock, relativePosition);
}

Point2F INode::DockToParent(DockPoint dock, const Point2F& relativePosition /*= Point2F::Zero*/)
{
	if (mParent == nullptr)
	{
		return relativePosition;
	}
	Rect2F rect(Point2F::Zero, mParent->Size().To2D());
	return DockToRect(rect, dock, relativePosition);
}

void INode::StretchToSceen(Stretch stretch, const Scale2F& strecthPercent /*= Scale2F::One*/)
{
	return StretchToRect(ResolutionAdapter::Instance().WinRect(), stretch, strecthPercent);

}

void INode::StretchToParent(Stretch stretch, const Scale2F& strecthPercent /*= Scale2F::One*/)
{
	RETURN_IF_NULL(mParent);
	Rect2F rect(Point2F::Zero, mParent->Size().To2D());
	return StretchToRect(rect, stretch, strecthPercent);
}

void INode::StretchToRect(const Rect2F& rect, Stretch stretch, const Scale2F& strecthPercent /*= Scale2F::One*/)
{
	Scale2F ouScale;
	Size2F outSize;
	Geometry::StretchToRect(mSize.To2D(), rect, stretch, strecthPercent, ouScale, outSize);
	SetScale(ouScale.X, ouScale.Y, mScale.Z);
	SetSize(outSize.Width, outSize.Height, mSize.Depth);
}


#pragma endregion Layout

#pragma region DataBind

bool INode::SetBinding(IDataBinding* val)
{
	RETURN_FALSE_IF_EQUAL(mBinding, val);
	if (val!=nullptr&&!val->IsValid())
	{
		Log::AssertFailedFormat("{}:SetBinding should accpet a valid binding with both data source and node template.", mName);
		return false;
	}

	SAFE_ASSIGN(mBinding, val);
	if (mBinding!=nullptr)
	{
		mBinding->SetNode(this);
		mBinding->Push();
	}
	return true;
}

#pragma endregion DataBind

void INode::EnableDebugDraw(bool val)
{
	if (val)
	{
		if (mDebugDrawShape == nullptr)
		{
			Color4F color;
			color.A = 1.f;
			color.R = Random::Global().NextFloat();
			color.G = Random::Global().NextFloat();
			color.B = Random::Global().NextFloat();
			//color = Color4F::Red;
			BoundingBox2 debugBoundingBox;
			debugBoundingBox.Origin = Point2F::Zero;
			debugBoundingBox.Size = mSize.To2D();

			mDebugDrawShape = NodeFactory::Instance().CreateRectBorder(debugBoundingBox, color);

			mDebugDrawShape->SetDepth(Math::IntMaxValue);	//always on top
			mDebugDrawShape->SetRenderingPriority(RenderingPriority::Foreground9);
			mDebugDrawShape->EnableManaged();
			AddChild(mDebugDrawShape);
		}
	}
	else
	{
		if (mDebugDrawShape != nullptr)
		{
			DeleteChild(mDebugDrawShape);
			mDebugDrawShape = nullptr;
		}
	}
}

#ifdef MEDUSA_SCRIPT

bool INode::TryAttachScriptObject(StringRef customName /*= StringRef::Empty*/)
{
	if (customName.IsEmpty())
	{
		customName = mName;
	}
	RETURN_TRUE_IF_EMPTY(customName);
	NodeScriptComponent* com = this->FindComponent<NodeScriptComponent>();
	RETURN_TRUE_IF_NOT_NULL(com);

	if (ScriptEngine::ExistsScriptFile(customName))
	{
		ScriptObject sc = ScriptEngine::State()->RequireNew(customName);
		if (sc == nullptr)
		{
			Log::AssertFailedFormat("Cannot load script: {}", customName);
			return nullptr;
		}

		com = this->AddComponent<NodeScriptComponent>();
		com->SetScriptObject(sc);
		return true;

	}
	return false;
}


ScriptObject INode::TryAddScriptFile(const FileIdRef& file)
{
	if (file.IsEmpty())
	{
		return nullptr;
	}
	NodeScriptComponent* com = this->FindComponent<NodeScriptComponent>();
	if (com!=nullptr)
	{
		return com->GetScriptObject();
	}


	ScriptObject classObj = ScriptEngine::State()->DoFileWithReturn(file);
	if (classObj == nullptr)
	{
		Log::FormatError("Cannot find class file:{}", file);
	}
	ScriptObject sc= classObj.InvokeMember<LuaRef>("new");
	com = this->AddComponent<NodeScriptComponent>();
	com->SetScriptObject(sc);
	return sc;
}

void INode::SetScriptObject(ScriptObject object)
{
	NodeScriptComponent* com = this->FindOrCreateComponent<NodeScriptComponent>();
	com->SetScriptObject(object);
}

ScriptObject INode::GetScriptObject() const
{
	NodeScriptComponent* com = this->FindComponent<NodeScriptComponent>();
	RETURN_NULL_IF_NULL(com);
	return com->GetScriptObject();
}

#endif


MEDUSA_END;
