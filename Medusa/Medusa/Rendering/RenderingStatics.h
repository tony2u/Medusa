// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/HashSet.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/ITexture.h"

MEDUSA_BEGIN;


class RenderingStatics :public Singleton < RenderingStatics >
{
	friend class Singleton < RenderingStatics > ;
private:
	RenderingStatics();
	~RenderingStatics();
public:
	void Uninitialize();

	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }

	void Reset();

	size_t BatchDrawCount() const { return mBatchDrawCount; }
	size_t TriangleCount() const { return mTriangleCount; }
	size_t VertexCount() const { return mVertexCount; }
	size_t RenderQueueCount() const { return mRenderQueueCount; }
	size_t RenderPassCount() const { return mRenderPassCount; }
	size_t MaterialCount() const { return mMaterials.Count(); }
	size_t TextureCount() const { return mTextures.Count(); }
	size_t TextureMemorySize() const { return mTextureMemorySize; }
	size_t TextureGPUSize() const { return mTextureGPUSize; }
	size_t DrawModeCount() const { return mDrawModes.Count(); }
	size_t GPUUploadSize() const { return mGPUUploadSize; }
	size_t OriginalDrawCount() const { return mOriginalDrawCount; }
	size_t BufferCount() const { return mBufferCount; }


	void CountBatchDraw();
	void CountOriginalDraw(size_t count = 1);
	void CountOriginalAndBatchDraw();
	void CountVertexCount(size_t count);
	void CountTriangleCount(size_t count);
	void CountRenderQueue(size_t count = 1);
	void CountRenderPass(size_t count = 1);
	void CountMaterial(const Share<IMaterial>& material);
	void CountMaterialTextures(const Share<IMaterial>& material);

	void CountTexture(const Share<ITexture>& texture);
	void CountDrawMode(GraphicsDrawMode mode);
	void IncreaseBuffer(size_t count = 1);
	void DecreaseBuffer(size_t count = 1);


	void CountGPUUploadSize(size_t val);

	void IncreaseTextureMemorySize(size_t size);
	void DecreaseTextureMemorySize(size_t size);
	void IncreaseTextureGPUSize(size_t size);
	void DecreaseTextureGPUSize(size_t size);

	size_t TotalNodeCount() const { return mTotalNodeCount; }
	size_t ChangedNodeCount() const { return mChangedNodeCount; }

	void IncreaseChangedNodeCount(size_t val = 1);
	void IncreaseTotalNodeCount(size_t val);

private:
	size_t mOriginalDrawCount;
	size_t mBatchDrawCount;
	size_t mTriangleCount;
	size_t mVertexCount;
	size_t mRenderQueueCount;
	size_t mRenderPassCount;
	size_t mTextureMemorySize;
	size_t mTextureGPUSize;
	size_t mGPUUploadSize;
	size_t mBufferCount;

	size_t mTotalNodeCount;
	size_t mChangedNodeCount;

	HashSet<Share<IMaterial>> mMaterials;
	HashSet<Share<ITexture>> mTextures;
	HashSet<GraphicsDrawMode, SafeEnumHashCoder> mDrawModes;

	bool mEnabled;


};


MEDUSA_END;