// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Rendering/IRenderGroup.h"
#include "Geometry/Matrix4.h"
#include "Rendering/Batch/BatchGroup.h"

MEDUSA_BEGIN;


class IRenderBatch :public IInitializable
{
public:
	IRenderBatch(RenderingStrategy renderingStrategy);
	virtual ~IRenderBatch();

	virtual bool Initialize() override;
	virtual bool Uninitialize()override;

	RenderingStrategy GetRenderingStrategy()const { return mRenderingStrategy; }

	BatchGroup Group() const { return mGroup; }
	void SetGroup(BatchGroup val) { mGroup = val; }

	Matrix4& GetModelMatrix() { return mModelMatrix; }

	const Share<IEffect>& Effect() const { return mEffect; }
	void SetEffect(const Share<IEffect>& val);

	const Share<IMaterial>& Material() const { return mMaterial; }
	void SetMaterial(const Share<IMaterial>& val);

	const Share<RenderStateTreeLeafNode>& StateTreeNode() const { return mStateTreeNode; }
	void SetStateTreeNode(const Share<RenderStateTreeLeafNode>& val);

	GraphicsDrawMode DrawMode() const { return mDrawMode; }
	void SetDrawMode(GraphicsDrawMode val) { mDrawMode = val; }

	virtual bool IsAvailableFor(size_t newVertexCount, size_t newIndexCount)const { return true; }
	virtual bool IsAvailableFor(const IRenderable& node)const;

	bool IsFreezed() const { return mIsFreezed; }
	void Freeze() { mIsFreezed = true; }
	virtual bool IsEmpty()const = 0;
public:
	void CustomDraw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None);

	virtual void Prepare() = 0;
	virtual void ReleaseBuffer() {}
	virtual void AddNode(IRenderable* node) = 0;
	virtual void RemoveNode(IRenderable* node) = 0;
	virtual void Clear() = 0;

	virtual bool Update() = 0;
	virtual void Apply() = 0;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) = 0;

	virtual void Restore() = 0;
	virtual void Print(HeapString& ioStr, uint level) = 0;

	uint64 RecycleFrameCount() const { return mRecycleFrameCount; }
	void SetRecycleFrameCount(uint64 val) { mRecycleFrameCount = val; }
protected:
	BatchGroup mGroup;
	Matrix4 mModelMatrix;
	RenderingStrategy mRenderingStrategy;

	bool mIsFreezed;

	Share<IEffect> mEffect;
	Share<IMaterial> mMaterial;
	Share<RenderStateTreeLeafNode> mStateTreeNode;
	GraphicsDrawMode mDrawMode;
	uint64 mRecycleFrameCount;
	
};


struct IRenderBatchCompareToBatchGroup
{
	static int Compare(IRenderBatch* batch, BatchGroup id)
	{
		return batch->Group() == id ? 0 : -1;
	}
};
MEDUSA_END;