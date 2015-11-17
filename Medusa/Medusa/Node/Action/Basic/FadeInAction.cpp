// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FadeInAction.h"
#include "Node/INode.h"
#include "FadeOutAction.h"

MEDUSA_BEGIN;

FadeInAction::FadeInAction(float duration):BaseFiniteAction(duration)
{
}


FadeInAction::~FadeInAction(void)
{
}

bool FadeInAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt,blend));
	float percent=Percent();
	percent=Math::Clamp(percent,0.f,1.f);
	INode* node = (INode*)mTarget;
	node->SetOpacity(percent);
	return true;
}

FadeInAction* FadeInAction::Create(float duration)
{
	return new FadeInAction(duration);
}

FadeInAction* FadeInAction::Clone() const 
{
	return new FadeInAction(mDuration);
}

IAction* FadeInAction::Reverse() const 
{
	return new FadeOutAction(mDuration);
}

MEDUSA_END;
