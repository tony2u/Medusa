// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "IScriptComponent.h"
#include "ComponentFactory.h"

MEDUSA_BEGIN;

IScriptComponent::IScriptComponent(const StringRef& name /*= StringRef::Empty*/, int priority/* = 0*/, void* userData /*= nullptr*/)
	:IComponent(name,priority,userData)
{
	mScriptObject = nullptr;
}

IScriptComponent::~IScriptComponent(void)
{
	
}


MEDUSA_IMPLEMENT_COMPONENT(IScriptComponent, IComponent);

MEDUSA_END;

#endif