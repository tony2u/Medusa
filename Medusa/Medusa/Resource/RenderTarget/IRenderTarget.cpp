// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Graphics/ResolutionAdapter.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Graphics/State/RenderTargetRenderState.h"
#include "Graphics/Render/Render.h"
#include "Core/Pattern/AutoIncreaseId.h"

MEDUSA_BEGIN;

IRenderTarget::IRenderTarget(const FileIdRef& fileId/*=FileId::Empty*/):IResource(fileId)
{
	mId = AutoIncreaseId<IRenderTarget>::New();

	mViewPort.Origin=Point2I::Zero;
	mViewPort.Size=ResolutionAdapter::Instance().WinSize();

	mClearColor=Color4F::Black;

	mRenderTargetRenderState=new RenderTargetRenderState();
}

IRenderTarget::~IRenderTarget()
{
	SAFE_RELEASE(mRenderTargetRenderState);
}


void IRenderTarget::Resize(const Size2U& val)
{
	FrameBuffer::Resize(val);
	mViewPort.Size=val;
}

void IRenderTarget::Apply()
{
	mRenderTargetRenderState->SetFrameBuffer(mFrameBuffer);
	mRenderTargetRenderState->SetViewPort(mViewPort);
	mRenderTargetRenderState->SetClearColor(mClearColor);
	
	RenderStateMachine::Instance().Push(mRenderTargetRenderState);
}

void IRenderTarget::Restore()
{
	RenderStateMachine::Instance().Pop(mRenderTargetRenderState);

}

void IRenderTarget::OnBeforeDraw()
{

}

void IRenderTarget::OnAfterDraw()
{

}

void IRenderTarget::Clear()
{
	Render::Instance().Clear(mClearMask);
}



MEDUSA_END;