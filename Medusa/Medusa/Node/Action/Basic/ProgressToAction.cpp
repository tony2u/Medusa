// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ProgressToAction.h"
#include "Node/Control/ProgressBar/IProgressBar.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;

ProgressToAction::ProgressToAction(float endPercent,float duration):BaseFiniteAction(duration),mEndPercent(endPercent)
{
}

ProgressToAction::ProgressToAction(float beginPercent,float endPercent,float duration)
	:BaseFiniteAction(duration),
	mBeginPercent(beginPercent),
	mEndPercent(endPercent)
{
	mDelta=mEndPercent-mBeginPercent;
}


ProgressToAction::~ProgressToAction(void)
{
}

bool ProgressToAction::Initialize(void* target)
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

bool ProgressToAction::Start()
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Start());
	mBeginPercent = ((IProgressBar*)mTarget)->Percent();
	mDelta = mEndPercent - mBeginPercent;
	return true;
}


bool ProgressToAction::Reset()
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Reset());
	mBeginPercent=((IProgressBar*)mTarget)->Percent();
	mDelta=mEndPercent-mBeginPercent;
	return true;
}


bool ProgressToAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(BaseFiniteAction::Update(dt,blend));
	float delta= mDelta*Percent()*blend;
	((IProgressBar*)mTarget)->SetPercent(mBeginPercent+delta);
	return true;
}

ProgressToAction* ProgressToAction::Create(float percent,float duration)
{
	return new ProgressToAction(percent,duration);
}

ProgressToAction* ProgressToAction::Clone() const 
{
	return new ProgressToAction(mBeginPercent,mEndPercent,this->mDuration);
}

ProgressToAction* ProgressToAction::Reverse() const 
{
	return new ProgressToAction(mEndPercent,mBeginPercent,this->mDuration);
}

MEDUSA_END;
