// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/INode.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.inl"
#include "Core/Action/BaseActionRunner.h"
#include "Resource/Model/IModel.h"
#include "Node/Input/InputManager.h"
#include "Node/Scene/IScene.h"
#include "Node/Scene/SceneGraph/ISceneGraph.h"
#include "Core/Log/Log.h"
#include "Graphics/ResolutionAdapter.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/DataSource/IDataSource.h"
#include "Core/Collection/STLPort.h"
#include "Core/Script/ScriptDefines.h"
#include "Core/Math/Random/Random.h"
#include "Node/NodeFactory.h"
#include "Node/Shape/IShape.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Core/Pattern/IVisitor.h"
#include "Node/Scene/SceneManager.h"
#include "Application/ApplicationStatics.h"
#include "Core/Command/EventArg/UserDataEventArg.h"
#include "Core/Geometry/Geometry.h"

MEDUSA_BEGIN;

INode::INode(const StringRef& name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IRenderable(name), DefaultRunnable(RunningState::None)
{
	Start();
	SetSender(this);
}


INode::~INode(void)
{
	ResolutionAdapter::Instance().TryRemoveDirytNode(this);

	SAFE_DELETE(mInputDispatcher);
	SAFE_DELETE_COLLECTION(mNodes);
	mNodeDict.Clear();
	SAFE_RELEASE(mDataSource);
	mManagedNodes.Clear();
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

	switch (flags.ToInt())
	{
		case NodeRemoveFlags::OnlyChildren.IntValue:
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
				FOR_EACH_COLLECTION(i, mNodes)
				{
					INode* node = *i;
					node->SetParent(nullptr);
				}
				mNodes.Clear();
				mNodeDict.Clear();
			}
			break;
		case NodeRemoveFlags::OnlyManaged.IntValue:
			RETURN_IF_FALSE(hasManaged);
			FOR_EACH_COLLECTION(i, mManagedNodes)
			{
				INode* sprite = *i;
				RemoveChild(sprite);
			}
			mManagedNodes.Clear();
			break;
		case NodeRemoveFlags::All.IntValue:
			RETURN_IF_FALSE(hasManaged);
			FOR_EACH_COLLECTION(i, mNodes)
			{
				INode* node = *i;
				node->SetParent(nullptr);
			}
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

	switch (flags.ToInt())
	{
		case NodeRemoveFlags::OnlyChildren.IntValue:
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
		case NodeRemoveFlags::OnlyManaged.IntValue:
			RETURN_IF_FALSE(hasManaged);
			FOR_EACH_COLLECTION(i, mManagedNodes)
			{
				INode* sprite = *i;
				DeleteChild(sprite);
			}
			mManagedNodes.Clear();
			break;
		case NodeRemoveFlags::All.IntValue:
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
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* node = *i;
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

	FOR_EACH_COLLECTION(i, mNodes)
	{
		hasChild = (*i)->HasChildRecursively(node);
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

	FOR_EACH_COLLECTION(i, mNodes)
	{
		node = *i;
		node = node->FindChildRecursively(name);
		RETURN_SELF_IF_NOT_NULL(node);
	}
	return nullptr;
}

const INode* INode::FindChildRecursively(StringRef name) const
{
	const INode* node = FindChild(name);
	RETURN_SELF_IF_NOT_NULL(node);

	FOR_EACH_COLLECTION(i, mNodes)
	{
		node = *i;
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
	while (parent != nullptr&&!parent->IsA<IScene>())
	{
		parent = parent->Parent();
	}

	return (IScene*)parent;
}

INode* INode::FindChild(StringRef name)
{
	return mNodeDict.TryGetValueWithFailed(name, nullptr);
}

const INode* INode::FindChild(StringRef name) const
{
	return mNodeDict.TryGetValueWithFailed(name, nullptr);
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
	if (changedFlags.Has(MoveableChangedFlags::SizeChanged))
	{
		OnLayoutSizeChanged(mSize);
		OnLayoutChanged(*this, NodeLayoutChangedFlags::SizeChanged);

		if (mDebugDrawShape != nullptr)
		{
			ShapeGeneralMesh* quadMesh = (ShapeGeneralMesh*)mDebugDrawShape->Mesh();
			quadMesh->ExpandVertexRectSize(mSize.To2D());	//it will override debugBounding box
		}
	}
}



#pragma region Update

void INode::SetRenderingPriorityRecursively(RenderingPriority val)
{
	SetRenderingPriority(val);
	FOR_EACH_ITEM_TO(mNodes, SetRenderingPriorityRecursively(val));
}


void INode::SetRenderingStrategyRecursively(RenderingStrategy val)
{
	SetRenderingStrategy(val);
	FOR_EACH_ITEM_TO(mNodes, SetRenderingStrategyRecursively(val));
}


void INode::SetMeshFixTypeRecursively(MeshFixType val)
{
	SetMeshFixType(val);
	FOR_EACH_ITEM_TO(mNodes, SetMeshFixTypeRecursively(val));
}

bool INode::UpdateRecursively(float dt, const NodeUpdateFlags& flag/*=NodeUpdateFlags::None*/)
{
	size_t count = mNodes.Count();
	if (count == 0)
	{
		ApplicationStatics::Instance().AddUpdateNodeCount();
		RETURN_TRUE_IF_FALSE(BeforeUpdate(dt, flag));
		RETURN_TRUE_IF_FALSE(Update(dt, flag));
		return AfterUpdate(dt, flag);
	}
	else
	{
		ApplicationStatics::Instance().AddTotalNodeCount(count);

		RETURN_TRUE_IF_FALSE(BeforeUpdate(dt, flag));
		count = mNodes.Count();	//re count node if child node is removed in BeforeUpdate

		intp i = (intp)count - 1;
		for (; i >= 0; --i)
		{
			INode* child = mNodes[i];
			BREAK_IF(child->mLogicZ < 0);
			if (child->ForceIsRunning())
			{
				RETURN_TRUE_IF_FALSE(child->UpdateRecursively(dt, flag));
			}
		}

		ApplicationStatics::Instance().AddUpdateNodeCount();
		RETURN_TRUE_IF_FALSE(Update(dt, flag));

		for (; i >= 0; --i)
		{
			INode* child = mNodes[i];
			if (child->ForceIsRunning())
			{
				RETURN_FALSE_IF_FALSE(child->UpdateRecursively(dt, flag));
			}
		}

		RETURN_TRUE_IF_FALSE(AfterUpdate(dt, flag));

	}


	return true;
}


bool INode::BeforeUpdate(float dt, NodeUpdateFlags flag /*= NodeUpdateFlags::None*/)
{
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
	if (!flag.Has(NodeUpdateFlags::SuppressRunningAction))
	{
		BaseActionRunner::UpdateActions(dt);
	}

	return true;
}


bool INode::AfterUpdate(float dt, NodeUpdateFlags flag /*= NodeUpdateFlags::None*/)
{
	return true;
}

void INode::VisitRecursively(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag /*= NodeVisitFlags::None*/, RenderStateType renderStateFlag /*= RenderStateUpdateFlags::None*/)
{
	if (nodeFlag.IsForceUpdateWorldMatrix())
	{
		ForceSetWorldMatrix(LocalMatrix()*mParent->WorldMatrix());
	}
	else
	{
		if (IsWorldMatrixDirty())
		{
			ForceSetWorldMatrix(LocalMatrix()*mParent->WorldMatrix());
			nodeFlag |= NodeVisitFlags::ForceUpdateWorldMatrix;
		}
	}

	//update color
	if (nodeFlag.IsForceUpdateWorldColor())
	{
		SetWorldColor(Color()*mParent->WorldColor());
	}
	else
	{
		if (IsWorldColorDirty())
		{
			SetWorldColor(Color()*mParent->WorldColor());
			nodeFlag |= NodeVisitFlags::ForceUpdateWorldColor;
		}
	}

	//update state
	if (renderStateFlag != RenderStateType::None)
	{
		MEDUSA_ADD_FLAG(renderStateFlag, mWorldRenderState.DirtyFlag());
		ForceUpdateRenderState(renderStateFlag);

	}
	else
	{
		if (IsWorldRenderStateDirty())
		{
			MEDUSA_ADD_FLAG(renderStateFlag, mWorldRenderState.DirtyFlag());
			ForceUpdateRenderState(renderStateFlag);
		}
	}

	visitor.Visit(this);
	outFlag |= mChangedFlag;

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
		BREAK_IF(child->LogicZ() < 0);
		RETURN_FALSE_IF_FALSE(child->EnterRecursively());
	}

	RETURN_FALSE_IF_FALSE(Enter());

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
		BREAK_IF(child->LogicZ() < 0);
		RETURN_FALSE_IF_FALSE(child->ExitRecursively());
	}

	RETURN_FALSE_IF_FALSE(Exit());

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
		BREAK_IF(child->LogicZ() < 0);
		RETURN_FALSE_IF_FALSE(child->UpdateLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(UpdateLogic());

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
		BREAK_IF(child->LogicZ() < 0);
		RETURN_FALSE_IF_FALSE(child->ResetLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(ResetLogic());

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
	if (flag.IsRenderQueueChanged() || flag.IsBatchChanged() || flag.IsDataTotalChanged() || flag.IsNewColor())
	{
		OnVisitQueueChanged();
	}
}

void INode::OnMeshChanged(RenderableChangedFlags flag)
{
	IRenderable::OnMeshChanged(flag);
	if (this->mSizeToContent==SizeToContent::Mesh)
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

InputDispatcher& INode::MutableInput()
{
	if (mInputDispatcher == nullptr)
	{
		mInputDispatcher = new InputDispatcher(this);
	}
	return *mInputDispatcher;
}

void INode::ResetInputPassing()
{
	mInputPassingEnabled = false;
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* node = *i;
		if (!node->IsInputPassingEnabled())
		{
			node->ResetInputPassing();
		}
	}
}

void INode::EnableInputPassing()
{
	mInputPassingEnabled = true;
	if (mParent != nullptr&&!mParent->IsInputPassingEnabled())
	{
		mParent->EnableInputPassing();
	}
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
	RETURN_IF_FALSE(IsSensitiveToChildLayoutChanged(sender, changedFlag));

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
			Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::FillWidth.");
			mMeasuredSize.Width = availableSize.Width;
			mMeasuredSize.Height = availableSize.Width / mStretchAspectRatio;
			break;
		case Stretch::FillHeight:
			Log::AssertFormat(!Math::IsZero(mStretchAspectRatio), "StretchAspectRatio==0 when Stretch::FillHeight.");
			mMeasuredSize.Height = availableSize.Height;
			mMeasuredSize.Width = availableSize.Height*mStretchAspectRatio;
			break;
		case Stretch::Uniform:
		{
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
	if (mDockPoint!=DockPoint::None)
	{
		resultRect.Origin = DockToRect(limitRect, this->mDockPoint, mRelativePosition);
		SetPosition(resultRect.Origin.X, resultRect.Origin.Y, mPosition.Z);
	}
	

	if (mStretch!=Stretch::None)
	{
		Scale2F outScale;
		Geometry::StretchToRect(mSize.To2D(), limitRect, mStretch, mStretchPercent, outScale, resultRect.Size);
		SetScale(outScale.X, outScale.Y, mScale.Z);
	}
	else
	{
		resultRect.Size = mSize.To2D();
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

	if (!arrangeFlags.Has(NodeLayoutArrangeFlags::SuppressArrangeSelf))
	{
		outRect = ArrangeSelf(outRect, arrangeFlags);
	}
	else
	{
		arrangeFlags.Remove(NodeLayoutArrangeFlags::SuppressArrangeSelf);
	}

	RETURN_TRUE_IF(arrangeFlags.Has(NodeLayoutArrangeFlags::SuppressArrangeChildren));

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
	SetScale(ouScale.X, ouScale.Y,mScale.Z);
	SetSize(outSize.Width, outSize.Height, mSize.Depth);
}


#pragma endregion Layout

#pragma region DataBind

void INode::SetDataSource(IDataSource* val)
{
	RETURN_IF_EQUAL(mDataSource, val);
	SAFE_ASSIGN_REF(mDataSource, val);
    if(mDataSource!=nullptr)
    {
        mDataSource->OnDataChanged += Bind(&INode::OnDataChanged,this);
    }
}

void INode::ReleaseDataSource()
{
	SAFE_RELEASE(mDataSource);
}

void INode::OnDataChanged(const IDataSource& dataSource)
{

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

			mDebugDrawShape->SetLogicZ(Math::IntMaxValue);	//always on top
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


MEDUSA_IMPLEMENT_RTTI_ROOT(INode);

MEDUSA_END;


#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterINode(asIScriptEngine* engine)
{
	int r2;
	r2 = engine->RegisterObjectType(MACRO_TO_STRING(INode), sizeof(INode), asOBJ_REF | asOBJ_NOCOUNT); MEDUSA_ASSERT_SILENT(r2 >= 0);
	MEDUSA_SCRIPT_REGISTER_NODE_NEW_DELETE(engine, INode);

	RegisterINode_Methods<INode>(engine, MACRO_TO_STRING(INode));
}


MEDUSA_SCRIPT_END;
#endif
