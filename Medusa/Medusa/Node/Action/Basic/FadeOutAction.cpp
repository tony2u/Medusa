// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FadeOutAction.h"
#include "Node/INode.h"
#include "FadeInAction.h"

MEDUSA_BEGIN;

FadeOutAction::FadeOutAction(float duration):BaseFiniteAction(duration)
{
}


FadeOutAction::~FadeOutAction(void)
{
}

bool FadeOutAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt,blend));
	float percent=Percent();
	percent=Math::Clamp(percent,0.f,1.f);
	INode* node = (INode*)mTarget;
	node->SetOpacity(1.f - percent);
	return true;
}

FadeOutAction* FadeOutAction::Create(float duration)
{
	return new FadeOutAction(duration);
}

FadeOutAction* FadeOutAction::Clone() const 
{
	return new FadeOutAction(mDuration);
}

IAction* FadeOutAction::Reverse() const 
{
	return new FadeInAction(mDuration);
}

MEDUSA_END;
