// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Component/IComponent.h"
MEDUSA_BEGIN;

//switch animations on a single node
class AnimatorComponent :public IComponent
{
	MEDUSA_DECLARE_COMPONENT(AnimatorComponent, IComponent);
public:
	using IComponent::IComponent;
	~AnimatorComponent();
	virtual bool Update(float dt)override;

	StringRef DefaultAnimation() const { return mDefaultAnimation; }
	void SetDefaultAnimation(StringRef val) { mDefaultAnimation = val; }

	void SwitchTo(const StringRef& name);
	void Add(IAction* action);

	virtual bool Enter()override;
	IAction* Find(const StringRef& name)const;

	void PauseAnimation();
	void ResumeAnimation();
protected:
	void SwitchAnimationHelper(IAction* action);
protected:
	List<IAction*> mAnimations;
	IAction* mCurrentAction = nullptr;
	HeapString mDefaultAnimation;
	
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(AnimatorComponent);

MEDUSA_END;
