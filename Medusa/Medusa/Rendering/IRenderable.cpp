// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/IRenderable.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Pattern/AutoIncreaseId.h"
#include "Graphics/State/Tree/RenderStateTree.h"
#include "Graphics/State/Tree/RenderStateTreeLeafNode.h"
#include "Core/Log/Log.h"
#include "Rendering/Batch/IRenderBatch.h"

MEDUSA_BEGIN;

IRenderable::IRenderable(const StringRef& name /*= StringRef::Empty*/)
	:mName(name),
	mColor(Color4F::White),
	mWorldColor(Color4F::White)
{
	mId = AutoIncreaseId<IRenderable>::New();

	mWorldColor.SetUpdateDelegate(Bind(&IRenderable::OnUpdateWorldColor, this));
	mWorldRenderState.SetUpdateDelegate(Bind(&IRenderable::OnUpdateWorldRenderState, this));

	mRenderStateTreeNode = RenderStateTree::Instance().EmptyNode();
	mRenderStateTreeNode->Retain();

	mRenderState.OnStateChanged += Bind(&IRenderable::OnStateChanged, this);
	mRenderState.OnStateAdded += Bind(&IRenderable::OnStateAdded, this);
	mRenderState.OnStateRemoved += Bind(&IRenderable::OnStateRemoved, this);

}

IRenderable::~IRenderable(void)
{
	mRenderingObject.UnregisterMeshChanged(Bind(&IRenderable::OnMeshChanged, this));
	mRenderingObject.UnregisterMaterialChanged(Bind(&IRenderable::OnMaterialChanged, this));

	if (mBatch != nullptr)
	{
		mBatch->RemoveNode(this);
	}
	RenderStateTree::Instance().Release(mRenderStateTreeNode);
}


bool IRenderable::IsValidToDrawSelf() const
{
	if (IsVisible() && HasValidRenderingObject())
	{
		float a = mWorldColor.Value().A;
		return a > 0.001f;
	}
	return false;
}

bool IRenderable::IsValidToRenderQueue() const
{
	if (IsVisible())
	{
		float a = mWorldColor.Value().A;
		return a > 0.001f;
	}
	return false;
}


void IRenderable::SetMesh(IMesh* val)
{
	RETURN_IF_EQUAL(mRenderingObject.Mesh(), val);

	mRenderingObject.UnregisterMeshChanged(Bind(&IRenderable::OnMeshChanged, this));
	RenderableChangedFlags changeFlag = RenderableChangedFlags::DataTotalChanged;

	if (IsValidToRenderQueue())
	{
		bool isValidToDrawPrev = mRenderingObject.IsValid();
		mRenderingObject.SetMesh(val);

		bool isValidToDrawNow = mRenderingObject.IsValid();
		if (isValidToDrawPrev != isValidToDrawNow)
		{
			MEDUSA_FLAG_ADD(changeFlag, RenderableChangedFlags::RenderQueueChanged);
			MEDUSA_FLAG_ADD(changeFlag, RenderableChangedFlags::BatchChanged);
		}
	}
	else
	{
		mRenderingObject.SetMesh(val);
	}

	mRenderingObject.RegisterMeshChanged(Bind(&IRenderable::OnMeshChanged, this));

	mRenderState.EnableBlend(mRenderingObject.IsBlend());
	OnMeshChanged(changeFlag);
}

void IRenderable::SetMaterial(IMaterial* val)
{
	RETURN_IF_EQUAL(mRenderingObject.Material(), val);
	mRenderingObject.UnregisterMaterialChanged(Bind(&IRenderable::OnMaterialChanged, this));

	RenderableChangedFlags changeFlag = RenderableChangedFlags::BatchChanged;
	if (IsValidToRenderQueue())
	{
		bool isValidToDrawPrev = mRenderingObject.IsValid();
		mRenderingObject.SetMaterial(val);

		bool isValidToDrawNow = mRenderingObject.IsValid();
		if (isValidToDrawPrev != isValidToDrawNow)
		{
			MEDUSA_FLAG_ADD(changeFlag, RenderableChangedFlags::RenderQueueChanged);
		}
	}
	else
	{
		mRenderingObject.SetMaterial(val);
	}
	mRenderingObject.RegisterMaterialChanged(Bind(&IRenderable::OnMaterialChanged, this));


	mRenderState.EnableBlend(mRenderingObject.IsBlend());
	OnMaterialChanged(changeFlag);

}

void IRenderable::SetVisible(bool val)
{
	RETURN_IF_EQUAL(mIsVisible, val);

	bool isValidToDrawPrev = IsValidToRenderQueue();
	mIsVisible = val;
	bool isValidToDrawNow = IsValidToRenderQueue();
	if (isValidToDrawPrev != isValidToDrawNow)
	{
		OnRenderQueueChanged();
	}

}


void IRenderable::SetColor(const Color4F& val)
{
	RETURN_IF_EQUAL(mColor, val);
	bool isValid = IsValidToRenderQueue();
	mColor = val;
	mWorldColor.SetDirty();

	bool isValid2 = IsValidToRenderQueue();
	mWorldColor.SetDirty();	//reset dirty make sure color will set to children

	if (isValid != isValid2)
	{
		OnRenderQueueChanged();
	}

	AddRenderableChangedFlags(RenderableChangedFlags::NewColor);
}


void IRenderable::OnMoveableDirty(MoveableChangedFlags changedFlags)
{
	if (mIsClipToBound)
	{
		Rect2F scissor;
		scissor.Origin = Point2F::Zero;
		scissor.Size = mSize.To2D();
		mRenderState.SetScissorBox(scissor);
	}
	AddRenderableChangedFlags(RenderableChangedFlags::DataTotalChanged);
}

bool IRenderable::HasValidRenderingObject() const
{
	return mRenderingObject.IsValid();
}

void IRenderable::SetRenderingObject(const RenderingObject& val)
{
	SetMesh(val.Mesh());
	SetMaterial(val.Material());
}

void IRenderable::OnUpdateWorldColor(Color4F& outColor, int32 dirtyFlag)
{
	if (mParentRenderable != nullptr)
	{
		SetWorldColor(mColor*(mParentRenderable->WorldColor()));
	}
	else
	{
		SetWorldColor(mColor);
	}

}

void IRenderable::SetWorldColor(const Color4F& val)
{
	mWorldColor = val;
}


#pragma region State


void IRenderable::EnableClipToBound(bool val)
{
	RETURN_IF_EQUAL(mIsClipToBound, val);
	mIsClipToBound = val;
	if (mIsClipToBound)
	{
		mRenderState.EnableScissor(val);
		Rect2F scissor;
		scissor.Origin = Point2F::Zero;
		scissor.Size = mSize.To2D();
		mRenderState.SetScissorBox(scissor);
	}
	else
	{
		mRenderState.RemoveScissor();
	}
}

void IRenderable::OnStateChanged(IRenderState& state)
{
	mWorldRenderState.AddDirtyFlag((int)state.Type());
	OnBatchChanged();
}

void IRenderable::OnStateAdded(IRenderState& state)
{
	mWorldRenderState.AddDirtyFlag((int)state.Type());
	OnBatchChanged();
}

void IRenderable::OnStateRemoved(RenderStateType state)
{
	mWorldRenderState.AddDirtyFlag((int)state);
	OnBatchChanged();
}

void IRenderable::OnUpdateWorldRenderState(RenderStateSet& outVal, int32 dirtyFlag)
{
	if (mParentRenderable != nullptr)
	{
		outVal.UpdateFromParent(mRenderState, mParentRenderable->WorldRenderState(), WorldMatrix(), RenderStateType(dirtyFlag));
	}
	else
	{
		outVal.UpdateFromSelf(mRenderState, WorldMatrix(), RenderStateType(dirtyFlag));
	}
}


bool IRenderable::IsWorldRenderStateDirty() const
{
	return mWorldRenderState.IsDirty() || mRenderStateTreeNode == nullptr || mBatchGroup == 0 || MEDUSA_FLAG_HAS(mChangedFlag,RenderableChangedFlags::BatchChanged);
}

void IRenderable::ForceUpdateRenderState(RenderStateType updateFlag /*= RenderStateUpdateFlags::None*/)
{
	if (updateFlag != RenderStateType::None)
	{
		if (mParentRenderable != nullptr)
		{
			mWorldRenderState.OldValue().UpdateFromParent(mRenderState, mParentRenderable->WorldRenderState(), WorldMatrix(), updateFlag);
		}
		else
		{
			mWorldRenderState.OldValue().UpdateFromSelf(mRenderState, WorldMatrix(), updateFlag);
		}
		mWorldRenderState.CompleteUpdate();
	}

	RenderStateTreeLeafNode* newVal = RenderStateTree::Instance().FindUniqueNode(mWorldRenderState.OldValue());
	if (mRenderStateTreeNode != newVal)
	{
		newVal->Retain();
		RenderStateTree::Instance().Release(mRenderStateTreeNode);
		mRenderStateTreeNode = newVal;
	}

	if (IsValidToDrawSelf())
	{
		mBatchGroup.Update(mRenderingPriority, *mRenderingObject.Material()->Effect(), *mRenderingObject.Material(), *mRenderStateTreeNode, mRenderingObject.Material()->DrawMode(), mRenderingStrategy);
	}
	else
	{
		mBatchGroup = 0;
	}


}

#pragma endregion State

#pragma region Batch


void IRenderable::SetRenderingPriority(RenderingPriority val)
{
	RETURN_IF_EQUAL(mRenderingPriority, val);
	mRenderingPriority = val;
	OnBatchChanged();
}



void IRenderable::SetRenderingStrategy(RenderingStrategy val)
{
	RETURN_IF_EQUAL(mRenderingStrategy, val);
	mRenderingStrategy = val;
	OnBatchChanged();

}

void IRenderable::SetMeshFixType(MeshFixType fixType)
{
	if (mRenderingObject.Mesh()!=nullptr)
	{
		mRenderingObject.Mesh()->SetFixType(fixType);
	}
}

void IRenderable::OnBatchChanged()
{
	AddRenderableChangedFlags((RenderableChangedFlags)((uint)RenderableChangedFlags::BatchChanged | (uint)RenderableChangedFlags::DataTotalChanged));
}


void IRenderable::OnRenderQueueChanged()
{
	AddRenderableChangedFlags((RenderableChangedFlags)((uint)RenderableChangedFlags::RenderQueueChanged | (uint)RenderableChangedFlags::BatchChanged | (uint)RenderableChangedFlags::DataTotalChanged));
}

void IRenderable::OnRenderChanged(RenderableChangedFlags flag)
{

}

void IRenderable::OnMeshChanged(RenderableChangedFlags flag)
{
	AddRenderableChangedFlags(flag);
}

void IRenderable::OnMaterialChanged(RenderableChangedFlags flag)
{
	AddRenderableChangedFlags(flag);
}

void IRenderable::ClearChangedFlag()
{
	mChangedFlag = RenderableChangedFlags::None;
}


void IRenderable::AddRenderableChangedFlags(RenderableChangedFlags val)
{
	MEDUSA_FLAG_ADD(mChangedFlag, val);
	OnRenderChanged(val);
}

void IRenderable::SetBatch(IRenderBatch* batch, uint vertexPosition, uint vertexCount, uint indexPosition, uint indexCount)
{
	mBatch = batch;
	mVertexSegment.Position = vertexPosition;
	mVertexSegment.Length = vertexCount;
	mIndexSegment.Position = indexPosition;
	mIndexSegment.Length = indexCount;
}


void IRenderable::SetParentRenderable(IRenderable* val)
{
	if (mParentRenderable != val)
	{
		mParentRenderable = val;
		OnBatchChanged();
		OnRenderQueueChanged();
	}
}





#pragma endregion Batch


MEDUSA_END;
