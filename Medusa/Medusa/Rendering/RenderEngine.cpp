// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/RenderEngine.h"
#include "Rendering/Scene/SceneRenderGroup.h"
#include "Node/Scene/IScene.h"
#include "Graphics/State/RenderStateMachine.h"

#include "Resource/RenderTarget/DefaultRenderTarget.h"

#include "Graphics/ResolutionAdapter.h"
#include "Core/Profile/ProfileSample.h"

#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Rendering/RenderingContext.h"

#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Core/Log/Log.h"
#include "Core/Profile/StopWatch.h"
#include "Rendering/Command/IRenderingCommand.h"
#include "Rendering/RenderDevice.h"

#include "Rendering/Effect/EffectRenderGroupPool.h"
#include "Rendering/Material/MaterialRenderGroupPool.h"
#include "Rendering/State/StateRenderGroupPool.h"
#include "Rendering/Batch/BatchPool.h"

#include "Graphics/State/Tree/RenderStateTree.h"
#include "Graphics/GraphicsContext.h"

MEDUSA_BEGIN;


RenderEngine::RenderEngine()
{
	mIsFrameDirty = true;
}


RenderEngine::~RenderEngine()
{
}

bool RenderEngine::InitializeBeforeWindow(bool disableThreading/* = false*/)
{
	RenderStateTree::Instance().Initialize();

	return true;
}

bool RenderEngine::UninitializeBeforeWindow()
{
	RenderStateTree::Instance().Uninitialize();

	EffectRenderGroupPool::Instance().Clear();
	MaterialRenderGroupPool::Instance().Clear();
	StateRenderGroupPool::Instance().Clear();
	BatchPool::Instance().Clear();

	return true;
}

bool RenderEngine::Initialize()
{
	GraphicsContext::Instance().Initialize();
	return true;
}

bool RenderEngine::InitializeAfterWindow(bool disableThreading /*= false*/)
{
	RETURN_FALSE_IF_FALSE(RenderDevice::Instance().Initialize(disableThreading));
	RenderDevice::Instance().Start();

	RenderStateMachine::Instance().Initialize();
	return true;
}



bool RenderEngine::UninitializeAfterWindow()
{
	RenderStateMachine::Instance().Uninitialize();

	

	RETURN_FALSE_IF_FALSE(RenderDevice::Instance().Uninitialize());
	GraphicsContext::Instance().Uninitialize();
	return true;
}

void RenderEngine::Clear()
{

}

void RenderEngine::Update(float dt)
{
	BatchPool::Instance().Update(dt);
}

void RenderEngine::Draw(float dt)
{
	RETURN_IF_FALSE(mIsFrameDirty);
	//push to render device
	RenderDevice::Instance().StartFrame();
	RenderDevice::Instance().WaitForFrameComplete();
	mIsFrameDirty = true;
}



MEDUSA_END;