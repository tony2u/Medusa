// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/TextureFileIdTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/TextureFileIdTimelineModel.h"
#include "Rendering/RenderingObjectFactory.h"


MEDUSA_BEGIN;


TextureFileIdTimeline::TextureFileIdTimeline(TextureFileIdTimelineModel* model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{

}

TextureFileIdTimeline::TextureFileIdTimeline(TextureFileIdTimelineModel* model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{

}

TextureFileIdTimeline::~TextureFileIdTimeline()
{
}


bool TextureFileIdTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	TextureFileIdTimelineModel* model = (TextureFileIdTimelineModel*)mModel;
	FileIdRef fileId = model->GetFileId(Elapsed());

	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(fileId);
	INode* node = (INode*)mTarget;
	node->SetRenderingObject(renderingObject);
	return true;
}

MEDUSA_END;
