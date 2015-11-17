// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Pass/Custom/RenderToTextureRenderPass.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/Shader/Vertex/BaseVertexShader.h"
#include "Resource/Effect/Shader/Pixel/BasePixelShader.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Resource/RenderTarget/CustomRenderTarget.h"
#include "Graphics/Buffer/RenderBuffer.h"
#include "Resource/ResourceNames.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/Texture/GPUTexture.h"

#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Resource/Texture/TextureFactory.h"
MEDUSA_BEGIN;

RenderToTextureRenderPass::RenderToTextureRenderPass(const FileIdRef& fileId)
	:BaseCustomRenderPass(fileId)
{

}

RenderToTextureRenderPass::~RenderToTextureRenderPass()
{
}

bool RenderToTextureRenderPass::Initialize()
{
	CustomRenderTarget* renderTarget=RenderTargetFactory::Instance().CreateCustom("RenderToTextureTarget",false);
	const Size2F& screenSize=ResolutionAdapter::Instance().WinSize();
	GPUTexture* texture= TextureFactory::Instance().CreateGPUTexture("RenderToTextureTexture",screenSize,GraphicsTextureType::Texture2D,
		GraphicsTextureTarget::Texture2D,
		GraphicsInternalFormat::RGBA,0,0,GraphicsPixelFormat::RGBA,GraphicsPixelDataType::Byte,ShaderSamplerNames::Texture);
	texture->SetUnit(GraphicsTextureUnits::Texture0);
	texture->SetMinFilter(GraphicsTextureMinFilter::Nearest);
	texture->SetMagFilter(GraphicsTextureMagFilter::Nearest);

	renderTarget->AttachTexture(GraphicsAttachment::Color,texture->TextureTarget(),texture,texture->Level());


	RenderBuffer* depthRenderBuffer=new RenderBuffer(GraphicsRenderBufferInternalFormat::DepthComponent16,screenSize);
	renderTarget->AttachRenderBuffer(GraphicsAttachment::Depth,depthRenderBuffer);
	renderTarget->SetViewPort(Rect2I(Point2F::Zero,screenSize));
	renderTarget->Validate();


	return true;
}


bool RenderToTextureRenderPass::Uninitialize()
{
	RenderTargetFactory::Instance().Remove("RenderToTextureTarget");
	TextureFactory::Instance().Remove("RenderToTextureTexture");

	return true;
}

void RenderToTextureRenderPass::Apply()
{
	IRenderTarget* renderTarget=RenderTargetFactory::Instance().Find("RenderToTextureTarget");
	renderTarget->Apply();
	renderTarget->Clear();

	BaseCustomRenderPass::Apply();
}

void RenderToTextureRenderPass::Restore()
{
	IRenderTarget* renderTarget=RenderTargetFactory::Instance().Find("RenderToTextureTarget");
	renderTarget->Restore();

	BaseCustomRenderPass::Restore();

}


MEDUSA_END;