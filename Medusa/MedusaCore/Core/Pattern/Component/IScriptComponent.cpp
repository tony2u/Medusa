// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IScriptComponent.h"
#include "Core/Script/ScriptObject.h"

MEDUSA_BEGIN;

IScriptComponent::IScriptComponent(const StringRef& name /*= StringRef::Empty*/, int priority/* = 0*/, void* userData /*= nullptr*/)
	:IComponent(name,priority,userData)
{
	mScriptObject = nullptr;
}

IScriptComponent::~IScriptComponent(void)
{
	
}


bool IScriptComponent::Update(float dt)
{
	return mScriptObject->Invoke<bool>("Update", dt);
}

bool IScriptComponent::AcceptEvent(IEventArg& eventArg)
{
	//TODO: 
	return true;
}

MEDUSA_END;