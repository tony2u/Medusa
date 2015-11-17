// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ProgressByAction.h"
#include "Node/Control/ProgressBar/IProgressBar.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

ProgressByAction::ProgressByAction(float delta, float duration) :BaseFiniteAction(duration), mDelta(delta)
{
}


ProgressByAction::~ProgressByAction(void)
{
}

bool ProgressByAction::Initialize(void* target)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Initialize(target));
	INode* node = (INode*)mTarget;
	if (!node->IsA<IProgressBar>())
	{
		Log::AssertFailed("ProgressToAction only accept target inherit from BaseProgressBar");
		return false;
	}

	return true;
}


bool ProgressByAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt, blend));
	float percent = dt / mDuration;
	float delta = mDelta*percent*blend;
	((IProgressBar*)mTarget)->AddPercent(delta);
	return true;
}

ProgressByAction* ProgressByAction::Create(float delta, float duration)
{
	return new ProgressByAction(delta, duration);
}

ProgressByAction* ProgressByAction::Clone() const
{
	return new ProgressByAction(mDelta, mDuration);
}

ProgressByAction* ProgressByAction::Reverse() const
{
	return new ProgressByAction(-mDelta, mDuration);
}


MEDUSA_END;
