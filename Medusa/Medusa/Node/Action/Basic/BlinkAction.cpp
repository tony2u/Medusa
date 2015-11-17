// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BlinkAction.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

BlinkAction::BlinkAction(float duration) :BaseFiniteAction(duration)
{
	
}


BlinkAction::~BlinkAction(void)
{
}


bool BlinkAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt,blend));
	float percent = Percent();
	if (percent>=1.f)
	{
		INode* node = (INode*)mTarget;
		node->SetVisible(! node->IsVisible());
	}

	return true;
}

BlinkAction* BlinkAction::Create(float duration)
{
	return new BlinkAction(duration);
}

BlinkAction* BlinkAction::Clone() const
{
	return new BlinkAction(mDuration);
}

BlinkAction* BlinkAction::Reverse() const
{
	return new BlinkAction(mDuration);
}

MEDUSA_END;
