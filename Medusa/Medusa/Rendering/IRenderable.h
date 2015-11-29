// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Moveable/DefaultMoveable.h"
#include "MedusaPreDeclares.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/RenderStateSet.h"
#include "Core/Geometry/Color4.h"

#include "RenderableChangedFlags.h"
#include "Rendering/RenderingFlags.h"
#include "Rendering/Batch/BatchGroup.h"
#include "Core/Geometry/Segment.h"
#include "Rendering/RenderingObject.h"

MEDUSA_BEGIN;



class IRenderable :public DefaultMoveable
{
public:
	IRenderable(const StringRef& name = StringRef::Empty);
	virtual ~IRenderable(void);
public:
	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }

	bool HasValidRenderingObject()const;
	const RenderingObject& GetRenderingObject() const { return mRenderingObject; }
	void SetRenderingObject(const RenderingObject& val);

	IMesh* Mesh()const { return mRenderingObject.Mesh(); }
	void SetMesh(IMesh* val);

	IMaterial* Material() const { return mRenderingObject.Material(); }
	void SetMaterial(IMaterial* val);

	uintp Id() const { return mId; }

	bool IsValidToDrawSelf()const;
	bool IsValidToRenderQueue()const;

	bool IsVisible() const { return mIsVisible; }
	void SetVisible(bool val);
public:
	RenderableChangedFlags RenderableChangedFlag() const { return mChangedFlag; }
	void AddRenderableChangedFlags(RenderableChangedFlags val);
	void ClearChangedFlag();


	const Color4F& Color() const { return mColor; }
	void SetColor(const Color4F& val);
	const Color4F& WorldColor() const { return mWorldColor.Value(); }
	void SetWorldColor(const Color4F& val);
	bool IsWorldColorDirty()const { return mWorldColor.IsDirty(); }
	size_t WorldColorVersion()const { return mWorldColor.Version(); }


	float Opacity()const { return mColor.A; }
	void SetOpacity(float val) { SetColor(Color4F(mColor.R, mColor.G, mColor.B, val)); }
#pragma region State
public:
	const RenderStateSet& RenderState() const { return mRenderState; }
	RenderStateSet& MutableRenderState() { return mRenderState; }

	bool IsWorldRenderStateDirty()const;
	const RenderStateSet& WorldRenderState() const { return mWorldRenderState.Value(); }
	RenderStateTreeLeafNode* RenderStateTreeNode() const { return mRenderStateTreeNode; }

	bool IsClipToBound() const { return mIsClipToBound; }
	void EnableClipToBound(bool val);

	void ForceUpdateRenderState(RenderStateType updateFlag = RenderStateType::None);
#pragma endregion State

#pragma region Batch
public:
	RenderingPriority GetRenderingPriority() const { return mRenderingPriority; }
	void SetRenderingPriority(RenderingPriority val);

	RenderingStrategy GetRenderingStrategy() const { return mRenderingStrategy; }
	void SetRenderingStrategy(RenderingStrategy val);

	void SetMeshFixType(MeshFixType fixType);

	BatchGroup GetBatchGroup() const { return mBatchGroup; }
	IRenderBatch* Batch() const { return mBatch; }
	void SetBatch(IRenderBatch* val) { mBatch = val; }
	const SegmentU& VertexSegment() const { return mVertexSegment; }
	const SegmentU& IndexSegment() const { return mIndexSegment; }

	void SetBatch(IRenderBatch* batch, uint vertexPosition, uint vertexCount, uint indexPosition, uint indexCount);
#pragma endregion Batch
public:
	virtual void OnBeforeDraw() {}
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) {}
	virtual void OnAfterDraw() {}
protected:
	void OnRenderQueueChanged();
	void OnBatchChanged();
	void OnStateChanged(IRenderState& state);
	void OnStateAdded(IRenderState& state);
	void OnStateRemoved(RenderStateType state);
	


	IRenderable* ParentRenderable() const { return mParentRenderable; }
	void SetParentRenderable(IRenderable* val);

	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags);
	virtual void OnRenderChanged(RenderableChangedFlags flag);
	virtual void OnMeshChanged(RenderableChangedFlags flag);
	virtual void OnMaterialChanged(RenderableChangedFlags flag);

private:

	void OnUpdateWorldRenderState(RenderStateSet& outVal, int32 dirtyFlag);
	void OnUpdateWorldColor(Color4F& outColor, int32 dirtyFlag);


protected:
	IRenderable* mParentRenderable=nullptr;

	HeapString mName;
	
	RenderingObject mRenderingObject;
	
	uintp mId;
	bool mIsVisible=true;
	bool mIsClipToBound=false;	//auto clip to bound

	RenderingPriority mRenderingPriority=RenderingPriority::Main0;	//batch
	RenderingStrategy mRenderingStrategy= RenderingStrategy::MultipleDynamicBatch;	//batch

	RenderStateSet mRenderState;	//batch
	LazyValue<RenderStateSet> mWorldRenderState;

	Color4F mColor;
	LazyValue<Color4F> mWorldColor;

	RenderableChangedFlags mChangedFlag; //used to generate render queue quicker

	//Batch 
	RenderStateTreeLeafNode* mRenderStateTreeNode=nullptr;
	BatchGroup mBatchGroup;
	IRenderBatch* mBatch=nullptr;
	SegmentU mVertexSegment;
	SegmentU mIndexSegment;

};




MEDUSA_END;