// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RenderingStatics.h"
#include "Core/Log/Log.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

RenderingStatics::RenderingStatics()
{
	mTextureMemorySize = 0;
	mTextureGPUSize = 0;
	mGPUUploadSize = 0;
	mTotalNodeCount = 0;
	mChangedNodeCount = 0;
	mEnabled = true;
	mBufferCount = 0;

	Reset();
}

RenderingStatics::~RenderingStatics()
{
}

void RenderingStatics::Reset()
{
	mOriginalDrawCount = 0;
	mBatchDrawCount = 0;
	mTriangleCount = 0;
	mVertexCount = 0;
	mRenderPassCount = 0;
	mRenderQueueCount = 0;
	mGPUUploadSize = 0;
	mMaterials.Clear();
	mTextures.Clear();
	mDrawModes.Clear();

	mTotalNodeCount = 0;	
	mChangedNodeCount = 0;
}

void RenderingStatics::CountBatchDraw()
{
	RETURN_IF_FALSE(mEnabled);
	++mBatchDrawCount;
}

void RenderingStatics::CountOriginalDraw(size_t count/*=1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mOriginalDrawCount += count;
}

void RenderingStatics::CountVertexCount(size_t count)
{
	RETURN_IF_FALSE(mEnabled);
	mVertexCount += count;
}

void RenderingStatics::CountTriangleCount(size_t count)
{
	RETURN_IF_FALSE(mEnabled);
	mTriangleCount += count;
}

void RenderingStatics::CountOriginalAndBatchDraw()
{
	RETURN_IF_FALSE(mEnabled);
	++mOriginalDrawCount;
	++mBatchDrawCount;
}

void RenderingStatics::CountRenderPass(size_t count/*=1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mRenderPassCount += count;
}



void RenderingStatics::CountRenderQueue(size_t count/*=1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mRenderQueueCount += count;
}

void RenderingStatics::CountMaterial(const IMaterial* material)
{
	RETURN_IF_FALSE(mEnabled);
	mMaterials.TryAdd(material);
}


void RenderingStatics::CountMaterialTextures(const IMaterial* material)
{
	const IMaterial::TextureDict& textures = material->Textures();
	FOR_EACH_COLLECTION(i, textures)
	{
		ITexture* texture = i->Value;
		CountTexture(texture);
	}
}

void RenderingStatics::CountTexture(const ITexture* texture)
{
	RETURN_IF_FALSE(mEnabled);
	mTextures.TryAdd(texture);
}

void RenderingStatics::CountGPUUploadSize(size_t val)
{
	RETURN_IF_FALSE(mEnabled);
	mGPUUploadSize += val;
}

void RenderingStatics::CountDrawMode(GraphicsDrawMode mode)
{
	RETURN_IF_FALSE(mEnabled);
	mDrawModes.TryAdd(mode);
}



void RenderingStatics::IncreaseTextureMemorySize(size_t size)
{
	RETURN_IF_FALSE(mEnabled);
	mTextureMemorySize += size;
}

void RenderingStatics::DecreaseTextureMemorySize(size_t size)
{
	RETURN_IF_FALSE(mEnabled);
	if (mTextureMemorySize < size)
	{
		Log::AssertFailedFormat("Invalid DecreaseTextureMemorySize:{} to {}", (uint)size, (uint)mTextureMemorySize);
		return;
	}

	mTextureMemorySize -= size;
}


void RenderingStatics::IncreaseTextureGPUSize(size_t size)
{
	RETURN_IF_FALSE(mEnabled);
	mTextureGPUSize += size;
}

void RenderingStatics::DecreaseTextureGPUSize(size_t size)
{
	RETURN_IF_FALSE(mEnabled);
	if (mTextureGPUSize < size)
	{
		Log::AssertFailedFormat("Invalid DecreaseTextureGPUSize:{} to {}", (uint)size, (uint)mTextureGPUSize);
		return;
	}

	mTextureGPUSize -= size;
}

void RenderingStatics::IncreaseChangedNodeCount(size_t val/*=1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mChangedNodeCount += val;
}

void RenderingStatics::IncreaseTotalNodeCount(size_t val)
{
	RETURN_IF_FALSE(mEnabled);
	mTotalNodeCount += val;
}

void RenderingStatics::IncreaseBuffer(size_t count/*=1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mBufferCount += count;
}

void RenderingStatics::DecreaseBuffer(size_t count /*= 1*/)
{
	RETURN_IF_FALSE(mEnabled);
	mBufferCount -= count;
}
MEDUSA_END;