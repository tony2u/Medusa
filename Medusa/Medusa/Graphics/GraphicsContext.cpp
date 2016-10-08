// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GraphicsContext.h"
#include "Graphics/Render/Render.h"

MEDUSA_BEGIN;

GraphicsContext::GraphicsContext()
{
	mAPI = GraphicsAPI::Default;

	mPixelFormat = GraphicsContextPixelFormat::RGBA8;
	mDepthFormat = GraphicsRenderBufferInternalFormat::Depth24AndStencil8;
	mStencilFormat = GraphicsRenderBufferInternalFormat::Depth24AndStencil8;


	mNeedMultipleSampling = false;
	mSampleCount = 4;


}

GraphicsContext::~GraphicsContext(void)
{

}

bool GraphicsContext::Initialize()
{
	Render::SetupRender(mAPI);
	Render::Instance().Initialize();
	//Render::Instance().PrintAll();

	return true;
}


bool GraphicsContext::Uninitialize()
{
	Render::Instance().Uninitialize();
	Render::DestoryRender();

	return true;
}



bool GraphicsContext::IsDepthStencilCombined() const
{
	return DepthStencilFormat() != GraphicsRenderBufferInternalFormat::None;
}

GraphicsRenderBufferInternalFormat GraphicsContext::DepthStencilFormat() const
{
	return CombineDepthStencilFormat(mDepthFormat, mStencilFormat);
}

bool GraphicsContext::NeedDepthBuffer() const
{
	return DepthBufferSize() != 0;
}


byte GraphicsContext::DepthBufferSize() const
{
	switch (mDepthFormat)
	{
	case GraphicsRenderBufferInternalFormat::DepthComponent16:
		return 16;
	case GraphicsRenderBufferInternalFormat::DepthComponent24:
	case GraphicsRenderBufferInternalFormat::Depth24AndStencil8:
		return 24;
	case GraphicsRenderBufferInternalFormat::DepthComponent32:
	case GraphicsRenderBufferInternalFormat::Depth32AndStencil8:
		return 32;
	default:
		return 0;
	}
}


bool GraphicsContext::NeedStencilBuffer() const
{
	return StencilBufferSize() != 0;
}



byte GraphicsContext::StencilBufferSize() const
{
	switch (mStencilFormat)
	{
	case GraphicsRenderBufferInternalFormat::StencilIndex8:
	case GraphicsRenderBufferInternalFormat::Depth24AndStencil8:
	case GraphicsRenderBufferInternalFormat::Depth32AndStencil8:
		return 8;
	default:
		return 0;
	}
}



GraphicsRenderBufferInternalFormat GraphicsContext::CombineDepthStencilFormat(GraphicsRenderBufferInternalFormat depthFormat, GraphicsRenderBufferInternalFormat stencilFormat)
{
	switch (stencilFormat)
	{
	case GraphicsRenderBufferInternalFormat::StencilIndex8:
	case GraphicsRenderBufferInternalFormat::Depth24AndStencil8:
	case GraphicsRenderBufferInternalFormat::Depth32AndStencil8:
		switch (depthFormat)
		{
		case GraphicsRenderBufferInternalFormat::DepthComponent24:
		case GraphicsRenderBufferInternalFormat::Depth24AndStencil8:
			return GraphicsRenderBufferInternalFormat::Depth24AndStencil8;
		case GraphicsRenderBufferInternalFormat::DepthComponent32:
		case GraphicsRenderBufferInternalFormat::Depth32AndStencil8:
			return GraphicsRenderBufferInternalFormat::Depth32AndStencil8;
		case GraphicsRenderBufferInternalFormat::DepthComponent16:
		default:
			return GraphicsRenderBufferInternalFormat::None;
		}
	default:
		return GraphicsRenderBufferInternalFormat::None;
	}

}

MEDUSA_END;