// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Batch/Single/SingleRenderBatch.h"
#include "Rendering/IRenderable.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;

SingleRenderBatch::SingleRenderBatch(RenderingStrategy renderingStrategy)
	:BaseBufferRenderBatch(renderingStrategy)
{

}


SingleRenderBatch::~SingleRenderBatch()
{
}

bool SingleRenderBatch::Update()
{
	mIsFreezed = false;
	uint refVertexIndex = 0;
	uint refIndexIndex = 0;
	bool isChangd = false;

	IRenderable* node = mNodes.First();
	IMesh* mesh = node->Mesh();

	IRenderBatch* originalBatch = node->Batch();
	if (originalBatch == this)
	{
		RenderableChangedFlags changeFlag = node->RenderableChangedFlag();
		if (changeFlag.IsZero())
		{
			const SegmentU& originalVertexSegment = node->VertexSegment();
			const SegmentU& originalIndexSegment = node->IndexSegment();
			if (refVertexIndex != originalVertexSegment.Position || originalVertexSegment.Length != mesh->VertexCount()
				|| refIndexIndex != originalIndexSegment.Position || originalIndexSegment.Length != mesh->IndexCount())
			{
				changeFlag |= RenderableChangedFlags::DataTotalChanged;
			}
			else
			{
				TrimBuffer(refVertexIndex, refIndexIndex);
				return false;
			}
		}

		if (changeFlag.IsDataTotalChanged())
		{
			AddNodeToBuffer(refVertexIndex, refIndexIndex, *node);
		}
		else
		{
			UpdateNodeToBuffer(refVertexIndex, refIndexIndex, *node, changeFlag);
		}
		isChangd = true;
	}
	else
	{
		//not in same batch prev
		AddNodeToBuffer(refVertexIndex, refIndexIndex, *node);
		isChangd = true;

	}


	TrimBuffer(refVertexIndex, refIndexIndex);

	return isChangd;
}

MEDUSA_END;