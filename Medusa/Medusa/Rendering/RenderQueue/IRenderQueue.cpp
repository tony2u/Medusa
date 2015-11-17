// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IRenderQueue.h"
#include "Rendering/Batch/BatchPool.h"

#include "Rendering/Command/IRenderingCommand.h"
#include "Rendering/RenderDevice.h"
#include "Rendering/RenderEngine.h"
#include "Rendering/RenderingStatics.h"

#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/IMaterial.h"
#include "Rendering/IRenderable.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;

IRenderQueue::IRenderQueue()
{
	mIsNeedToSort = false;
	mIsCommandChanged = false;
}

IRenderQueue::~IRenderQueue(void)
{
	
}

void IRenderQueue::Clear()
{
	SAFE_RELEASE_COLLECTION(mCommands);
	mIsNeedToSort = false;
	mNodes.Clear();
}
void IRenderQueue::AddNode(IRenderable* node)
{
	mNodes.Add(node);
	if (node->GetRenderingPriority() != RenderingPriority::Main0)
	{
		//has other priority
		mIsNeedToSort = true;
	}
#ifdef MEDUSA_SAFE_CHECK
	if (node->GetBatchGroup()==0)
	{
		Log::AssertFailedFormat("Error batch group");
	}
#endif
}

void IRenderQueue::RemoveNode(IRenderable* node)
{
	mNodes.Remove(node);
	if (node->GetRenderingPriority() != RenderingPriority::Main0)
	{
		//has other priority
		mIsNeedToSort = true;
	}
}

void IRenderQueue::AddCommand(IRenderingCommand* command)
{
	mCommands.Add(command);
}

#ifdef MEDUSA_DEBUG
void IRenderQueue::PrintRenderQueue(const RenderableNodeList& nodes)
{
	HeapString testStr;
	size_t count = nodes.Count();
	FOR_EACH_SIZE(i, count)
	{
		IRenderable* node = (IRenderable*)nodes[i];
		testStr.AppendFormat("{}:{}:{}\n", node->Id(), node->Mesh()->Material()->Name().c_str(), node->Name().c_str());
	}
	Log::Info(testStr);
}

#endif

bool IRenderQueue::OnUpdateCommands(RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	return true;
}

void IRenderQueue::Draw(RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	RenderingStatics::Instance().CountRenderQueue();

	//if (mIsCommandChanged)
	{
		OnUpdateCommands(renderingFlags);
		mIsCommandChanged = false;
	}

	if (!mCommands.IsEmpty())
	{
		RenderDevice::Instance().ReceiveFrame(mCommands);
		RenderEngine::Instance().SetFrameDirty();
	}
}



MEDUSA_END;