// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IComponent.h"


MEDUSA_BEGIN;


IComponent::IComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:mName(name), mPriority(priority), mUserData(userData)
{
	
}


void IComponent::SetEntity(IEntity* val)
{
	RETURN_IF_EQUAL(mEntity, val);
	if (mEntity!=nullptr)
	{
		OnDetached();
	}
	mEntity = val;

	if (mEntity != nullptr)
	{
		if (mIsAutoActive)
		{
			Start();
		}
		OnAttached();
	}
}

bool IComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IsRunning());
	BaseActionRunner::UpdateActions(dt);
	return true;
}

MEDUSA_END;