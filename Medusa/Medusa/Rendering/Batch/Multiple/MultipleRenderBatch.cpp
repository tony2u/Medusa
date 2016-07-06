// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Batch/Multiple/MultipleRenderBatch.h"
#include "Rendering/IRenderable.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;


MultipleRenderBatch::MultipleRenderBatch(RenderingStrategy renderingStrategy)
	:BaseBufferRenderBatch(renderingStrategy)
{
}


MultipleRenderBatch::~MultipleRenderBatch()
{

}



bool MultipleRenderBatch::Update()
{
	mIsFreezed = false;
	uint refVertexIndex = 0;
	uint refIndexIndex = 0;
	bool isInterrupted = false;
	bool isChanged = false;

	for (auto node : mNodes)
	{
		auto mesh = node->Mesh();
		CONTINUE_IF_NULL(mesh);

		if (!isInterrupted)
		{
			IRenderBatch* originalBatch = node->Batch();
			if (originalBatch == this)
			{
				RenderableChangedFlags changeFlag = node->RenderableChangedFlag();
				if (changeFlag==RenderableChangedFlags::None)
				{
					const SegmentU& originalVertexSegment = node->VertexSegment();
					const SegmentU& originalIndexSegment = node->IndexSegment();

					if (refVertexIndex != originalVertexSegment.Position || originalVertexSegment.Length != mesh->VertexCount()
						|| refIndexIndex != originalIndexSegment.Position || originalIndexSegment.Length != mesh->IndexCount())
					{
						MEDUSA_FLAG_ADD(changeFlag, RenderableChangedFlags::DataTotalChanged);
						isInterrupted = true;
					}
					else
					{
						refVertexIndex += originalVertexSegment.Length;
						refIndexIndex += originalIndexSegment.Length;
						continue;
					}
				}

#ifdef MEDUSA_SAFE_CHECK
				if (changeFlag == RenderableChangedFlags::BatchChanged)
				{
					const SegmentU& originalVertexSegment = node->VertexSegment();
					const SegmentU& originalIndexSegment = node->IndexSegment();

					if (refVertexIndex != originalVertexSegment.Position || originalVertexSegment.Length != mesh->VertexCount()
						|| refIndexIndex != originalIndexSegment.Position || originalIndexSegment.Length != mesh->IndexCount())
					{
						Log::AssertFailedFormat("Invalid change flag");
					}
				}
#endif

				if (MEDUSA_FLAG_HAS(changeFlag,RenderableChangedFlags::DataTotalChanged))
				{
					AddNodeToBuffer(refVertexIndex, refIndexIndex, *node);
				}
				else
				{
					UpdateNodeToBuffer(refVertexIndex, refIndexIndex, *node, changeFlag);
				}
				isChanged = true;

			}
			else
			{
				//not in same batch prev
				AddNodeToBuffer(refVertexIndex, refIndexIndex, *node);
				isChanged = true;

			}
		}
		else
		{
			AddNodeToBuffer(refVertexIndex, refIndexIndex, *node);
			isChanged = true;

		}
	}

	TrimBuffer(refVertexIndex, refIndexIndex);
	return isChanged;
}

MEDUSA_END;
