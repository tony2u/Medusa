// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FadeBySpeedAction.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

FadeBySpeedAction::FadeBySpeedAction(float speed):BaseInfiniteAction(),mSpeed(speed)
{
}


FadeBySpeedAction::~FadeBySpeedAction(void)
{
}

bool FadeBySpeedAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Update(dt,blend));
	INode* node = (INode*)mTarget;
	float opacity = node->Opacity();
	opacity+=dt*mSpeed*blend;
	if (opacity<=0.f||opacity>=1.f)
	{
		opacity=Math::Clamp(opacity,0.f,1.f);
		Stop();
	}
	
	node->SetOpacity(opacity);
	return true;
}

FadeBySpeedAction* FadeBySpeedAction::Create(float speed)
{
	return new FadeBySpeedAction(speed);
}

FadeBySpeedAction* FadeBySpeedAction::Clone() const 
{
	return new FadeBySpeedAction(mSpeed);
}

FadeBySpeedAction* FadeBySpeedAction::Reverse() const 
{
	return new FadeBySpeedAction(-mSpeed);
}

MEDUSA_END;
