// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/Buffer/FrameBuffer.h"
#include "Graphics/Render/Render.h"
#include "Graphics/Buffer/RenderBuffer.h"
#include "Resource/Texture/ITexture.h"
#include "Core/Log/Log.h"
#include "Graphics/GraphicsContext.h"

MEDUSA_BEGIN;

FrameBuffer::FrameBuffer():mFrameBuffer(0)
{
	
}

FrameBuffer::~FrameBuffer()
{
	SAFE_DELETE_DICTIONARY_VALUE(mRenderBuffers);
}


void FrameBuffer::Generate()
{
	if (mFrameBuffer==0)
	{
		mFrameBuffer=Render::Instance().GenFrameBuffer();
	}
}

void FrameBuffer::Delete()
{
	if (mFrameBuffer!=0)
	{
		Render::Instance().DeleteFrameBuffer(mFrameBuffer);
	}
}

void FrameBuffer::Bind( bool isCurrent )const
{
	if (isCurrent)
	{
		Render::Instance().BindFrameBuffer(mFrameBuffer);
	}
	else
	{
		Render::Instance().BindFrameBuffer(0);
	}
}

void FrameBuffer::AttachRenderBuffer( GraphicsAttachment attachment,RenderBuffer* renderBuffer )
{
	if(mRenderBuffers.ContainsKey(attachment)||mTextures.ContainsKey(attachment))
	{
		MEDUSA_ASSERT_FAILED("Duplicate attachment");
		return;
	}
	mRenderBuffers.Add(attachment,renderBuffer);
	Bind(true);
	Render::Instance().AttachRenderBufferToFrameBuffer(attachment,renderBuffer->Id());
	Bind(false);

	UpdateClearMask(attachment,true);
}

void FrameBuffer::AttachTexture( GraphicsAttachment attachment,GraphicsTextureTarget textureTarget,ITexture* texture,int level )
{
	if(mRenderBuffers.ContainsKey(attachment)||mTextures.ContainsKey(attachment))
	{
		MEDUSA_ASSERT_FAILED("Duplicate attachment");
		return;
	}
	texture->Retain();
	mTextures.Add(attachment,texture);

	Bind(true);
	Render::Instance().AttachTextureToFrameBuffer(attachment,textureTarget,texture->Texture(),level);
	Bind(false);
	UpdateClearMask(attachment,true);

}

void FrameBuffer::AttachDepthStencil(GraphicsRenderBufferInternalFormat depthFormat, GraphicsRenderBufferInternalFormat stencilFormat, const Size2U& size)
{
	auto depthStencilFormat = GraphicsContext::CombineDepthStencilFormat(depthFormat, stencilFormat);
	if (depthStencilFormat != GraphicsRenderBufferInternalFormat::None)
	{
		RenderBuffer* renderBuffer = new RenderBuffer(depthStencilFormat, size);
		renderBuffer->Generate();
		AttachRenderBuffer(GraphicsAttachment::DepthStencil, renderBuffer);
	}
	else
	{
		RenderBuffer* depthBuffer = new RenderBuffer(depthFormat, size);
		depthBuffer->Generate();
		AttachRenderBuffer(GraphicsAttachment::Depth, depthBuffer);

		RenderBuffer* stencilBuffer = new RenderBuffer(stencilFormat, size);
		stencilBuffer->Generate();
		AttachRenderBuffer(GraphicsAttachment::Stencil, stencilBuffer);
	}

}

RenderBuffer* FrameBuffer::DetachRenderBuffer(GraphicsAttachment attachment)
{
	RenderBuffer* renderBuffer=mRenderBuffers.TryGetValueWithFailed(attachment,nullptr);
	if (renderBuffer==nullptr)
	{
		MEDUSA_ASSERT_FAILED("Cannot find attachment");
		return nullptr;
	}
	mRenderBuffers.RemoveKey(attachment);

	Bind(true);
	Render::Instance().AttachRenderBufferToFrameBuffer(attachment,0);
	Bind(false);
	UpdateClearMask(attachment,false);

	return renderBuffer;
}


RenderBuffer* FrameBuffer::GetRenderBuffer(GraphicsAttachment attachment)
{
	return mRenderBuffers.TryGetValueWithFailed(attachment,nullptr);
}


void FrameBuffer::Resize(const Size2U& val)
{
	FOR_EACH_COLLECTION(i,mRenderBuffers)
	{
		RenderBuffer* buffer=i->Value;
		buffer->Resize(val);
	}
}

ITexture* FrameBuffer::DetachTexture( GraphicsAttachment attachment )
{
	ITexture* texture=mTextures.TryGetValueWithFailed(attachment,nullptr);
	if (texture==nullptr)
	{
		MEDUSA_ASSERT_FAILED("Cannot find attachment");
		return nullptr;
	}
    bool isShared=texture->IsShared();
	texture->Release();
	mTextures.RemoveKey(attachment);

	Bind(true);
	Render::Instance().AttachTextureToFrameBuffer(attachment,GraphicsTextureTarget::Texture2D,0,0);	//GraphicsTextureTarget::Texture2D is ignored inside
	Bind(false);
	UpdateClearMask(attachment,false);


    return isShared?texture:nullptr;
}

bool FrameBuffer::Validate()const
{
	Bind(true);
	bool isValid=false;
	GraphicsFrameBufferStatus status=Render::Instance().CheckFrameBufferStatus();

	switch(status)
	{
	case GraphicsFrameBufferStatus::Completed:
		isValid=true;
		break;
	case GraphicsFrameBufferStatus::IncompleteAttachment:
		Log::Error("Not all framebuffer attachment points are framebuffer attachment complete");
		break;

	case GraphicsFrameBufferStatus::IncompleteDimensions:
		Log::Error("Not all attached images have the same width and height.");

		break;

	case GraphicsFrameBufferStatus::IncompleteMissingAttachment:
		Log::Error("No images are attached to the framebuffer.");

		break;

	case GraphicsFrameBufferStatus::Unsupported:
		Log::Error("The combination of internal formats of the attached images violates an implementation-dependent set of restrictions.");

		break;
	}
	
	Bind(false);
	return isValid;
}

void FrameBuffer::UpdateClearMask( GraphicsAttachment attachment,bool isAttach )
{
	switch(attachment)
	{
	case GraphicsAttachment::Color:
		mClearMask.SetOrRemoveIf(GraphicsBufferComponentMask::Color,isAttach);
		break;
	case GraphicsAttachment::Depth:
		mClearMask.SetOrRemoveIf(GraphicsBufferComponentMask::Depth,isAttach);
		break;
	case GraphicsAttachment::Stencil:
		mClearMask.SetOrRemoveIf(GraphicsBufferComponentMask::Stencil,isAttach);
		break;
	case GraphicsAttachment::DepthStencil:
		mClearMask.SetOrRemoveIf(GraphicsBufferComponentMask::Depth, isAttach);
		mClearMask.SetOrRemoveIf(GraphicsBufferComponentMask::Stencil, isAttach);
		break;
	default:
		break;
	}
}


MEDUSA_END;