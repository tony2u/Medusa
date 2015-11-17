// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Application/ApplicationStatics.h"
#include "Node/Control/Label/ILabel.h"
#include "Node/NodeFactory.h"
#include "Resource/Font/FontId.h"
#include "Resource/ResourceManager.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/RenderEngine.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/Camera/Camera.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"
#include "Resource/RenderTarget/DefaultRenderTarget.h"
#include "Resource/RenderTarget/RenderTargetFactory.h"
#include "Rendering/RenderQueue/Single/SingleBatchRenderQueue.h"
#include "Application/Application.h"

MEDUSA_BEGIN;

ApplicationStatics::ApplicationStatics()
	:mEnabled(true),
	mIsDrawingPerformance(false),
	mPerformanceLabel(nullptr),
	mGPULabel(nullptr),
	mIsPrintLog(false),
	mDebugLabel(nullptr),
	mRenderQueue(nullptr)
	
{

	Reset();
}

ApplicationStatics::~ApplicationStatics()
{
	Uninitialize();
}


bool ApplicationStatics::Initialize(ApplicationDebugInfoFlags val)
{
	Memory::ClearZero(mElapseds);
	mEnabled = true;
	mIsDrawingPerformance = false;
	if (mRenderQueue == nullptr)
	{
		mRenderQueue = new SingleBatchRenderQueue();
		mRenderQueue->SetRenderTarget(nullptr);
		mRenderQueue->SetCamera(ResolutionAdapter::Instance().DefaultCamera2D());
	}

	Reset();
	mDebugInfoFlag = val;
	mUpdateWatch.Enable(IsShowPerformance());

	return true;
}

void ApplicationStatics::Uninitialize()
{
	SAFE_DELETE(mDebugLabel);
	SAFE_DELETE(mPerformanceLabel);
	SAFE_DELETE(mGPULabel);
	SAFE_DELETE(mRenderQueue);
}

void ApplicationStatics::Reset()
{
	mUpdateNodeCount = 0;
	mVisitNodeCount = 0;
	mTotalNodeCount = 0;

	RenderingStatics::Instance().Reset();
}

void ApplicationStatics::UpdateLabels()
{
	mRenderQueueChanged |= RenderableChangedFlags::RenderQueueChanged | RenderableChangedFlags::BatchChanged;
	if (IsShowGPU())
	{
		if (mGPULabel == nullptr)
		{
			StringRef versionStr = Render::Instance().GetString(GraphicsStringName::Version);
			StringRef vendorStr = Render::Instance().GetString(GraphicsStringName::Vendor);
			StringRef shaderLanguageVersionStr = Render::Instance().GetString(GraphicsStringName::ShaderLanguageVersion);
			StringRef renderStr = Render::Instance().GetString(GraphicsStringName::Renderer);
			int textureSize = Render::Instance().GetInteger(GraphicsIntegerName::MaxTextureSize);
			Rect2I viewPort;
			Render::Instance().GetIntegerArray(GraphicsIntegerArrayName::Viewport, (int*)&viewPort);

			HeapString text;
			text.AppendLine(versionStr);
			text.AppendLine(vendorStr);
			text.AppendLine(renderStr);
			text.AppendLine(shaderLanguageVersionStr);
			text.AppendFormat("MaxTextureSize:{}", textureSize);
			text.AppendLine();
			text.AppendFormat("ViewPort:{},{} {}*{}", viewPort.Origin.X, viewPort.Origin.Y, viewPort.Size.Width, viewPort.Size.Height);


			mGPULabel = NodeFactory::Instance().CreateMultipleLineLabel(FontId("arial22.fnt", 22), text.c_str(), Alignment::LeftTop, Size2U::Zero, true);
			mGPULabel->EnableLayout(false);

			mGPULabel->SetRenderingStrategy(RenderingStrategy::SingleStaticBatch);
			const Size2F& screenSize = ResolutionAdapter::Instance().WinSize();
			mGPULabel->SetAnchor(Point3F(0.f, 1.f, 0.f));
			//mGPULabel->SetDockPoint(DockPoint::LeftTop);
			mGPULabel->SetPosition(Point3F(0.f, (float)screenSize.Height, 0.f));
			mGPULabel->ForceUpdateRenderState();
			mRenderQueue->AddNode(mGPULabel);
		}
	}
	else
	{
		if (mGPULabel!=nullptr)
		{
			mRenderQueue->RemoveNode(mGPULabel);
		}
		SAFE_DELETE(mGPULabel);

	}

	if (IsShowPerformance())
	{
		if (mPerformanceLabel == nullptr)
		{
			mPerformanceLabel = NodeFactory::Instance().CreateMultipleLineLabel(FontId("arial22.fnt", 22), "6\n123.4567\n52.3");
			mPerformanceLabel->EnableLayout(false);
			mPerformanceLabel->SetDock(DockPoint::LeftBottom);
			mPerformanceLabel->SetAnchorPoint(AnchorPoint::LeftBottom);

			mPerformanceLabel->ForceUpdateRenderState();
			//mPerformanceLabel=NodeFactory::Instance().CreateSingleLineLabel("MedusaFPSLabel",FontInfo("fps","arial22.fnt"),"6\n123.4567\n52.3");
			mRenderQueue->AddNode(mPerformanceLabel);

		}
	}
	else
	{
		if (mPerformanceLabel != nullptr)
		{
			mRenderQueue->RemoveNode(mPerformanceLabel);
		}
		SAFE_DELETE(mPerformanceLabel);
	}

	if (IsShowTouch())
	{
		if (mDebugLabel == nullptr)
		{
			mDebugLabel = NodeFactory::Instance().CreateSingleLineLabel(FontId("arial22.fnt", 22), ",");
			mDebugLabel->EnableLayout(false);
			mDebugLabel->SetAnchorPoint(AnchorPoint::RightBottom);
			const Size2F& screenSize = ResolutionAdapter::Instance().WinSize();
			mDebugLabel->SetPosition(Point3F((float)screenSize.Width, 0.f, 0.f));
			mDebugLabel->ForceUpdateRenderState();
			mRenderQueue->AddNode(mDebugLabel);
		}
	}
	else
	{
		if (mDebugLabel != nullptr)
		{
			mRenderQueue->RemoveNode(mDebugLabel);
		}
		SAFE_DELETE(mDebugLabel);
		
	}

}


void ApplicationStatics::EnableDebugInfo(ApplicationDebugInfoFlags val)
{
	RETURN_IF_EQUAL(mDebugInfoFlag, val);
	mDebugInfoFlag = val;
	mUpdateWatch.Enable(IsShowPerformance());

	UpdateLabels();
}

void ApplicationStatics::Resize(const Size2F& newSize)
{
	if (IsShowGPU())
	{
		ShowGPU(false);
		ShowGPU(true);
	}

	if (IsShowTouch())
	{
		ShowTouch(false);
		ShowTouch(true);
	}
}

void ApplicationStatics::Update(float dt)
{
	if (mPerformanceLabel != nullptr)
	{

		/*
		TextureMemorySize/K	- mTextureGPUSize/K - mGPUUploadSize/K - mChangedNodeCount/mTotalNodeCount
		P:mRenderPassCount - M:mMaterialCount - T:mTextureCount - D:mDrawModeCount
		?mVertexCount - ?mTriangleCount | {mOriginalDrawCount} -> [mBatchDrawCount]
		UpdateSystem+UpdateWindow+UpdateLayout+VisitWindow=Update
		GenerateRenderQueue+PrepareDraw+Draw+FinishDraw++SwapBuffer=Draw
		Elpased/ms-dt/ms | 1/Elpased - 1/dt

		mUpdateElapsed/ms + mLoopElapsed/ms - dt/ms
		1/(mLoopElapsed+mLoopElapsed) - 1/dt
		*/
		float updateSystemElapsed = mElapseds[(uint)FrameStep::UpdateSystem];
		float updateSceneElapsed = mElapseds[(uint)FrameStep::UpdateScene];
		float updateLayoutElapsed = mElapseds[(uint)FrameStep::UpdateLayout];
		float visitSceneElapsed = mElapseds[(uint)FrameStep::VisitScene];
		float updateElapsed = updateSystemElapsed + updateSceneElapsed + updateLayoutElapsed + visitSceneElapsed;

		float updateRenderQueueElapsed = mElapseds[(uint)FrameStep::UpdateRenderQueue];
		float drawElapsed = mElapseds[(uint)FrameStep::Draw];
		float swapBufferElapsed = mElapseds[(uint)FrameStep::SwapBuffer];
		float totalDrawElapsed = updateRenderQueueElapsed + drawElapsed + swapBufferElapsed;

		float loopElapsed = updateElapsed + totalDrawElapsed;
		size_t textureMemorySize = RenderingStatics::Instance().TextureMemorySize();
		size_t textureGPUSize = RenderingStatics::Instance().TextureGPUSize();
		size_t gpuUploadSize = RenderingStatics::Instance().GPUUploadSize();
		size_t renderQueueCount = RenderingStatics::Instance().RenderQueueCount();
		size_t renderPassCount = RenderingStatics::Instance().RenderPassCount();
		size_t materialCount = RenderingStatics::Instance().MaterialCount();
		size_t textureCount = RenderingStatics::Instance().TextureCount();
		size_t drawModeCount = RenderingStatics::Instance().DrawModeCount();
		size_t vertexCount = RenderingStatics::Instance().VertexCount();
		size_t triangleCount = RenderingStatics::Instance().TriangleCount();
		size_t originalDrawCount = RenderingStatics::Instance().OriginalDrawCount();
		size_t batchDrawCount = RenderingStatics::Instance().BatchDrawCount();
		size_t totalNodeCount = RenderingStatics::Instance().TotalNodeCount();
		size_t changedNodeCount = RenderingStatics::Instance().ChangedNodeCount();
		size_t bufferCount = RenderingStatics::Instance().BufferCount();


		mPerformanceString.Format(
			L"{:f3}K - {:f3}K - {:f3}K - {}/{}/{} - {}/{}\n"
			L"Q:{} - P:{} - M:{} - T:{} - D:{} - B:{}\n"
			L"?{} - ?{} | {{{}}} -> [{}]\n"
			L"{:f3} + {:f3} + {:f3} + {:f3} = {:f3}\n"
			L"{:f3} + {:f3} + {:f3} = {:f3}\n"
			L"{:f3} - {:f3} | {:f3} - {:f3}",
			textureMemorySize / 1024.f, textureGPUSize / 1024.f, gpuUploadSize / 1024.f, mUpdateNodeCount, mVisitNodeCount, mTotalNodeCount, changedNodeCount, totalNodeCount,
			renderQueueCount, renderPassCount, materialCount, textureCount, drawModeCount, bufferCount,
			vertexCount, triangleCount, originalDrawCount, batchDrawCount,
			updateSystemElapsed, updateSceneElapsed, updateLayoutElapsed, visitSceneElapsed, updateElapsed,
			updateRenderQueueElapsed, drawElapsed, swapBufferElapsed, totalDrawElapsed,
			loopElapsed, dt*1000.f, 1000.f / loopElapsed, 1.f / dt
			);

		if (mIsPrintLog)
		{
			Log::Info(mPerformanceString);
		}
		else
		{
			mPerformanceLabel->SetString(mPerformanceString);
			mPerformanceLabel->AddRenderableChangedFlags(RenderableChangedFlags::DataTotalChanged);
			mRenderQueueChanged |= RenderableChangedFlags::DataTotalChanged;
		}
	}


	if (mDebugLabel != nullptr)
	{
		if (mIsPrintLog)
		{
			Log::Info(mDebugString);
		}
		else
		{
			if (mDebugString.IsEmpty())
			{
				mDebugString = L",";
			}
			mDebugLabel->SetString(mDebugString);
			mDebugLabel->AddRenderableChangedFlags(RenderableChangedFlags::DataTotalChanged);
			mRenderQueueChanged |= RenderableChangedFlags::DataTotalChanged;
		}
	}

	RenderingStatics::Instance().Enable(false);
	mRenderQueue->Update(mRenderQueueChanged);
	RenderingStatics::Instance().Enable(mEnabled);
	mRenderQueueChanged = RenderableChangedFlags::None;
}


void ApplicationStatics::Draw(float dt)
{
	mIsDrawingPerformance = true;
	size_t batchDrawCount = RenderingStatics::Instance().BatchDrawCount();
	RenderingFlags renderingFlags = RenderingFlags::KeepRenderTarget;
	if (batchDrawCount<=0)
	{
		renderingFlags = RenderingFlags::None;
		mRenderQueue->SetRenderTarget(RenderTargetFactory::Instance().Default());
	}

	mRenderQueue->Draw(renderingFlags);
	mIsDrawingPerformance = false;
}

void ApplicationStatics::SetDebugTouch(const Point2F& pos)
{
	RETURN_IF_FALSE(IsShowTouch());
	mDebugString.Format(L"{},{}", (int)pos.X, (int)pos.Y);
}

void ApplicationStatics::ShowPerformance(bool val /*= true*/)
{
	RETURN_IF_EQUAL(mDebugInfoFlag.IsPerformance(), val);
	mDebugInfoFlag.SetOrRemoveIf(ApplicationDebugInfoFlags::Performance, val);
	mUpdateWatch.Enable(val);
	UpdateLabels();
}

void ApplicationStatics::ShowGPU(bool val /*= true*/)
{
	RETURN_IF_EQUAL(mDebugInfoFlag.IsGPU(), val);
	mDebugInfoFlag.SetOrRemoveIf(ApplicationDebugInfoFlags::GPU, val);
	UpdateLabels();
}

void ApplicationStatics::ShowTouch(bool val /*= true*/)
{
	RETURN_IF_EQUAL(mDebugInfoFlag.IsTouch(), val);
	mDebugInfoFlag.SetOrRemoveIf(ApplicationDebugInfoFlags::Touch, val);
	UpdateLabels();
}

void ApplicationStatics::SetElpased(FrameStep step, float val)
{
	mElapseds[(uint)step] = val;
}

void ApplicationStatics::AddElpased(FrameStep step, float val)
{
	mElapseds[(uint)step] += val;
}

void ApplicationStatics::AddTotalNodeCount(size_t val)
{
	mTotalNodeCount += val;
}

void ApplicationStatics::AddUpdateNodeCount(size_t val/*=1*/)
{
	mUpdateNodeCount += val;
}

void ApplicationStatics::AddVisitNodeCount(size_t val)
{
	mVisitNodeCount += val;
}


MEDUSA_END;