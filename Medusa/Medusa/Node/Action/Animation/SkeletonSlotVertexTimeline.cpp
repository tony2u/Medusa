// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonSlotVertexTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/VertexTimelineModel.h"
#include "Node/Skeleton/SkeletonSlot.h"
#include "Core/Log/Log.h"
#include "Resource/Skeleton/Attachment/ISkeletonAttachmentModel.h"
#include "Resource/Model/Mesh/General/TextureGeneralMesh.h"

MEDUSA_BEGIN;

SkeletonSlotVertexTimeline::SkeletonSlotVertexTimeline(VertexTimelineModel* model, ISkeletonAttachmentModel* attachmentModel, bool isRepeatForever /*= false*/)
	:ITimeline(model, isRepeatForever), mAttachmentModel(attachmentModel)
{
}


SkeletonSlotVertexTimeline::~SkeletonSlotVertexTimeline()
{
}


bool SkeletonSlotVertexTimeline::Initialize(void* target)
{
	RETURN_FALSE_IF_FALSE(ITimeline::Initialize(target));
	INode* node = (INode*)mTarget;
	if (!node->IsA<SkeletonSlot>())
	{
		Log::AssertFailed("SkeletonSlotAttachmentTimeline only accept target inherit from SkeletonSlot");
		return false;
	}

	return true;
}


bool SkeletonSlotVertexTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	SkeletonSlot* slot = (SkeletonSlot*)mTarget;
	if (slot->Attachment() != mAttachmentModel)
	{
		return false;
	}

	const List<Point3F>* prevOffset = nullptr;
	const List<Point3F>* nextOffset = nullptr;
	VertexTimelineModel* model = (VertexTimelineModel*)mModel;
	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	if (model->TryGetFrame(Elapsed(), outPrevFrameIndex, outNextFrameIndex, outPercent))
	{
		if (outNextFrameIndex != outPrevFrameIndex)
		{
			prevOffset = &model->GetVertices(outPrevFrameIndex);
			nextOffset = &model->GetVertices(outNextFrameIndex);
		}
		else
		{
			nextOffset = &model->GetVertices(outNextFrameIndex);
		}
	}
    else
    {
        return false;
    }

	switch (mAttachmentModel->Type().ToInt())
	{
		case SkeletonAttachmentType::Mesh.IntValue:
		case SkeletonAttachmentType::SkinnedMesh.IntValue:
		{
			TextureGeneralMesh* mesh = (TextureGeneralMesh*)slot->Mesh();
			List<Point3F>& vertices = mesh->MutableVertices();
			uintp count = nextOffset->Count();
			if (count>vertices.Count())
			{
				Log::AssertFailedFormat("SkeletonSlotVertexTimeline: offsetCount:{} > meshVerticesCount:{}", count, vertices.Count());
				return false;
			}

			if (prevOffset != nullptr)
			{
				FOR_EACH_SIZE(i, count)
				{
					vertices[i] += (*prevOffset)[i] * (1.f - outPercent) + (*nextOffset)[i] * outPercent;
				}
			}
			else
			{
				FOR_EACH_SIZE(i, count)
				{
					vertices[i] += (*nextOffset)[i];
				}
			}

		}
			break;
		default:
			Log::AssertFailedFormat("SkeletonSlotVertexTimeline:Invalid attachment type:{} ", mAttachmentModel->Type().ToString().c_str());
			return false;
	}



	return true;
}

MEDUSA_END;
