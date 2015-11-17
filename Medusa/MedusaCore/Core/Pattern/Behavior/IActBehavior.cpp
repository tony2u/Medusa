// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IActBehavior.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

IActBehavior::IActBehavior()
{
	
}

IActBehavior::~IActBehavior(void)
{
	
}

const IBehavior* IActBehavior::Behave(IBrainBody& brainBody, void* sender) const
{
	if (Enter(brainBody, sender))
	{
		return this;
	}
	return nullptr;
}


bool IActBehavior::LoadFromXmlNode(pugi::xml_node node)
{
	RETURN_FALSE_IF_FALSE(IBehavior::LoadFromXmlNode(node));
	StringRef typeName = node.name();
	StringRef predicateId = node.attribute("Predicate").value();

	if (!predicateId.IsEmpty())
	{
		Log::FormatError("Invalid predicate:{} on {}", predicateId.c_str(), typeName.c_str());
		return false;
	}
	if (node.first_child() != nullptr)
	{
		Log::FormatError("Act behavior cannot have children. {}", typeName.c_str());
		return false;
	}

	return true;
}

MEDUSA_IMPLEMENT_RTTI(IActBehavior, IBehavior);

MEDUSA_END;