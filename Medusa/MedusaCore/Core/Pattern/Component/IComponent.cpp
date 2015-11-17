// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IComponent.h"


MEDUSA_BEGIN;


IComponent::IComponent(const StringRef& name /*= StringRef::Empty*/, int priority /*= 0*/, void* userData /*= nullptr*/)
	:mName(name), mPriority(priority), mUserData(userData), mEntity(nullptr)
{

}


bool IComponent::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IsRunning());

	return true;
}

MEDUSA_IMPLEMENT_RTTI_ROOT(IComponent);
MEDUSA_END;