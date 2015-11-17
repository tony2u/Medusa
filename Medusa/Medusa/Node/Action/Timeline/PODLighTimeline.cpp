// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/PODLighTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/PODLightTimelineModel.h"
#include "Resource/Light/LightFactory.h"

MEDUSA_BEGIN;


PODLighTimeline::PODLighTimeline(PODLightTimelineModel* model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{
	mLight = nullptr;

}

PODLighTimeline::PODLighTimeline(PODLightTimelineModel* model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{
	mLight = nullptr;

}


PODLighTimeline::~PODLighTimeline()
{
	SAFE_RELEASE(mLight);	
}

bool PODLighTimeline::Start()
{
	RETURN_FALSE_IF_FALSE((ITimeline::Start()));


	PODLightTimelineModel* ani=(PODLightTimelineModel*)mModel;
	StringRef lightName=ani->LightName();
	StringRef targetName=ani->TargetNodeName();

	mLight=LightFactory::Instance().Find(lightName);
	RETURN_FALSE_IF_NULL(mLight);
	SAFE_RETAIN(mLight);

	

	return true;
}

bool PODLighTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	//float frame=mElapsed*mAnimation->GetFPS();
	//PODLightTimelineModel* ani=(PODLightTimelineModel*)mAnimation;

	//if (mLightState!=nullptr)
	//{
	//	const Matrix4& matrix= mLightState->GetWorldMatrix();
	//	// View position is 0,0,0,1 transformed by world matrix
	//	mLight->SetPosition(matrix.Translation());

	//	if (mLightTargetState!=nullptr)
	//	{
	//		const Matrix4& targetMatrix= mLightTargetState->GetWorldMatrix();
	//		Point3F targetPos=targetMatrix.Translation();
	//		Point3F direction=targetPos-mLight->GetPosition();
	//		mLight->SetDirection(direction);
	//	}
	//	else
	//	{
	//		// View direction is 0,-1,0,0 transformed by world matrix
	//		Point3F targetPos(0.f,-1.f,0.f);
	//		targetPos=matrix.TransformVector(targetPos);
	//		targetPos.Normalize();
	//		mLight->SetDirection(targetPos);
	//	}
	//}

	return true;
}

MEDUSA_END;
