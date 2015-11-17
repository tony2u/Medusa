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

	mWorldColor.SetUpdateDelegate(Bind(&IRenderable::OnUpdateWorldColor,this));
	mWorldRenderState.SetUpdateDelegate(Bind(&IRenderable::OnUpdateWorldRenderState,this));

	mRenderStateTreeNode = RenderStateTree::Instance().EmptyNode();
	mRenderStateTreeNode->Retain();

	mRenderState.OnStateChanged += Bind(&IRenderable::OnStateChanged, this);
	mRenderState.OnStateRemoved += Bind(&IRenderable::OnStateRemoved, this);

}

IRenderable::~IRenderable(void)
{
	if (mMesh!=nullptr)
	{
		mMesh->OnMeshChanged -= Bind(&IRenderable::OnMeshChanged, this);
		mMesh->Release();
		mMesh = nullptr;
	}

	if (mBatch!=nullptr)
	{
		mBatch->RemoveNode(this);
	}
}


bool IRenderable::IsValidToDrawSelf() const
{
	if (IsVisible() && HasValidMesh())
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
	RETURN_IF_EQUAL(mMesh, val);

	if (mMesh!=nullptr)
	{
		mMesh->OnMeshChanged -= Bind(&IRenderable::OnMeshChanged, this);
	}
	RenderableChangedFlags changeFlag = RenderableChangedFlags::DataTotalChanged;
	const IEffect* originalEffect = mMesh != nullptr ? mMesh->Effect() : nullptr;
	const IMaterial* originalMaterial = mMesh != nullptr ? mMesh->Material() : nullptr;
	GraphicsDrawMode originalDrawMode = mMesh != nullptr ? mMesh->DrawMode() : GraphicsDrawMode::Count;

	if (IsValidToRenderQueue())
	{
		bool isValidToDrawPrev = HasValidMesh();
		SAFE_ASSIGN_REF(mMesh, val);

		bool isValidToDrawNow = HasValidMesh();
		if (isValidToDrawPrev != isValidToDrawNow)
		{
			changeFlag |= RenderableChangedFlags::RenderQueueChanged | RenderableChangedFlags::BatchChanged;
		}
		else
		{
			const IEffect* currentEffect = mMesh != nullptr ? mMesh->Effect() : nullptr;
			const IMaterial* currentlMaterial = mMesh != nullptr ? mMesh->Material() : nullptr;
			GraphicsDrawMode currentDrawMode = mMesh != nullptr ? mMesh->DrawMode() : GraphicsDrawMode::Count;

			if (originalEffect != currentEffect || originalMaterial != currentlMaterial || originalDrawMode != currentDrawMode)
			{
				changeFlag |= RenderableChangedFlags::BatchChanged;
			}
		}
	}
	else
	{
		SAFE_ASSIGN_REF(mMesh, val);
	}

	if (mMesh!=nullptr)
	{
		mMesh->OnMeshChanged+= Bind(&IRenderable::OnMeshChanged, this);
	}

	bool hasBlend = mMesh != nullptr&&mMesh->HasBlend();
	EnableBlend(hasBlend);
	OnMeshChanged(changeFlag);
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
		SetScissor(scissor);
	}
	AddRenderableChangedFlags(RenderableChangedFlags::DataTotalChanged);
}

bool IRenderable::HasValidMesh() const
{
	return mMesh != nullptr&&mMesh->IsValid();
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

void IRenderable::EnableBlend(bool val)
{
	mRenderState.EnableBlend(val);
}


void IRenderable::EnableScissor(bool val)
{
	mRenderState.EnableScissor(val);
}

void IRenderable::EnableClipToBound(bool val)
{
	RETURN_IF_EQUAL(mIsClipToBound, val);
	mIsClipToBound = val;
	if (mIsClipToBound)
	{
		EnableScissor(val);
		Rect2F scissor;
		scissor.Origin = Point2F::Zero;
		scissor.Size = mSize.To2D();
		SetScissor(scissor);
	}
	else
	{
		mRenderState.RemoveScissor();
	}
}

void IRenderable::SetScissor(const Rect2F& val)
{
	mRenderState.SetScissorBox(val);
}

void IRenderable::OnStateChanged(IRenderState& state)
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
	return mWorldRenderState.IsDirty() || mRenderStateTreeNode == nullptr || mBatchGroup == 0 || mChangedFlag.IsBatchChanged();
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
		mBatchGroup.Update(mRenderingPriority, *mMesh->Effect(), *mMesh->Material(), *mRenderStateTreeNode, mMesh->DrawMode(), mRenderingStrategy);
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
	if (mMesh != nullptr)
	{
		mMesh->SetFixType(fixType);
	}
}

void IRenderable::OnBatchChanged()
{
	AddRenderableChangedFlags(RenderableChangedFlags::BatchChanged | RenderableChangedFlags::DataTotalChanged);
}


void IRenderable::OnRenderQueueChanged()
{
	AddRenderableChangedFlags(RenderableChangedFlags::RenderQueueChanged | RenderableChangedFlags::BatchChanged | RenderableChangedFlags::DataTotalChanged);
}

void IRenderable::OnRenderChanged(RenderableChangedFlags flag)
{

}

void IRenderable::OnMeshChanged(RenderableChangedFlags flag)
{
	AddRenderableChangedFlags(flag);
}

void IRenderable::ClearChangedFlag()
{
	mChangedFlag = RenderableChangedFlags::None;
}


void IRenderable::AddRenderableChangedFlags(RenderableChangedFlags val)
{
	mChangedFlag |= val;
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
