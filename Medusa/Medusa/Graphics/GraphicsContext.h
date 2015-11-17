// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Graphics/GraphicsTypes.h"

MEDUSA_BEGIN;


class GraphicsContext :public Singleton<GraphicsContext>
{
	friend class Singleton<GraphicsContext>;
public:
	GraphicsContext();
	~GraphicsContext(void);
public:
	bool Initialize();
	bool Uninitialize();
public:
	GraphicsAPI API() const { return mAPI; }
	void SetAPI(GraphicsAPI val) { mAPI = val; }

	GraphicsContextPixelFormat PixelFormat() const { return mPixelFormat; }
	void SetPixelFormat(GraphicsContextPixelFormat val) { mPixelFormat = val; }

	bool IsDepthStencilCombined()const;
	GraphicsRenderBufferInternalFormat DepthStencilFormat() const;
	void SetDepthStencilFormat(GraphicsRenderBufferInternalFormat val) { mDepthFormat = val; mStencilFormat = val; }

	GraphicsRenderBufferInternalFormat DepthFormat() const { return mDepthFormat; }
	void SetDepthFormat(GraphicsRenderBufferInternalFormat val) { mDepthFormat = val; }

	GraphicsRenderBufferInternalFormat StencilFormat() const { return mStencilFormat; }
	void SetStencilFormat(GraphicsRenderBufferInternalFormat val) { mStencilFormat = val; }

	bool NeedDepthBuffer() const;
	byte DepthBufferSize() const;

	bool NeedStencilBuffer() const;
	byte StencilBufferSize() const;

	bool NeedMultipleSampling() const { return mNeedMultipleSampling; }
	void SetNeedMultipleSampling(bool val) { mNeedMultipleSampling = val; }

	byte SampleCount() const { return mSampleCount; }
	void SetSampleCount(byte val) { mSampleCount = val; }

	static GraphicsRenderBufferInternalFormat CombineDepthStencilFormat(GraphicsRenderBufferInternalFormat depthFormat, GraphicsRenderBufferInternalFormat stencilFormat);

protected:
	GraphicsAPI mAPI;

	GraphicsContextPixelFormat mPixelFormat;
	GraphicsRenderBufferInternalFormat mDepthFormat;
	GraphicsRenderBufferInternalFormat mStencilFormat;

	bool mNeedMultipleSampling;
	byte mSampleCount;	//0,2,4,8,16
};

MEDUSA_END;
