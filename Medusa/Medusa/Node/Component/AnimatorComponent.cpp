// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AnimatorComponent.h"
#include "Node/INode.h"

MEDUSA_BEGIN;


AnimatorComponent::~AnimatorComponent()
{
	SAFE_DELETE_COLLECTION(mAnimations);
}

bool AnimatorComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IComponent::Update(dt));
	return true;
}

void AnimatorComponent::SwitchTo(const StringRef& name)
{
	Log::Info(name);
	auto action = Find(name);
	SwitchAnimationHelper(action);
}

void AnimatorComponent::Add(IAction* action)
{
	mAnimations.Add(action);
}

bool AnimatorComponent::Enter()
{
	if (!mDefaultAnimation.IsEmpty())
	{
		IAction* action = Find(mDefaultAnimation);
		if (action == nullptr)
		{
			Log::AssertFailedFormat("Failed to find default animation:{}", mDefaultAnimation);
			return false;
		}

		SwitchAnimationHelper(action);
	}

	return true;
}

IAction* AnimatorComponent::Find(const StringRef& name) const
{
	for (auto* action : mAnimations)
	{
		if (action->Name() == name)
		{
			return action;
		}
	}
	return nullptr;
}

void AnimatorComponent::PauseAnimation()
{
	RETURN_IF_NULL(mCurrentAction);
	INode* node = (INode*)mEntity;
	node->PauseAction(mCurrentAction);
}

void AnimatorComponent::ResumeAnimation()
{
	RETURN_IF_NULL(mCurrentAction);
	INode* node = (INode*)mEntity;
	node->ResumeAction(mCurrentAction);
}


void AnimatorComponent::SwitchAnimationHelper(IAction* action)
{
	INode* node = (INode*)mEntity;
	if (mCurrentAction != nullptr)
	{
		if (mCurrentAction->Name() == action->Name())
		{
			//same type
			mCurrentAction->Resume();
			return;
		}
		node->StopAction(mCurrentAction);
	}
	mCurrentAction = action->Clone();
	node->RunAction(mCurrentAction);
}

MEDUSA_IMPLEMENT_COMPONENT(AnimatorComponent, IComponent);
MEDUSA_END;
