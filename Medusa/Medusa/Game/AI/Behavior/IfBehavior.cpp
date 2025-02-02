// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IfBehavior.h"
#include "Core/Log/Log.h"
#include "BehaviorFactory.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;


IfBehavior::~IfBehavior()
{
	Clear();
}

const IBehavior* IfBehavior::Behave(IBrainBody& brainBody, void* sender) const
{
	bool predicate = EvaluateBool(sender);
	if (predicate)
	{
		RETURN_NULL_IF_EMPTY(mItems);
		for(auto item: mItems)
		{
			const IBehavior* result = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(result);
		}
	}
	else
	{
		RETURN_NULL_IF_EMPTY(mElseItems);
		for (auto item : mElseItems)
		{
			const IBehavior* result = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(result);
		}
	}
	return nullptr;
}

const IBehavior* IfBehavior::ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e) const
{
	bool predicate = EvaluateBool(sender);
	if (predicate)
	{
		RETURN_NULL_IF_EMPTY(mItems);
		for (auto item : mItems)
		{
			const IBehavior* result = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(result);
		}
	}
	else
	{
		RETURN_NULL_IF_EMPTY(mElseItems);
		for (auto item : mElseItems)
		{
			const IBehavior* result = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(result);
		}
	}
	return nullptr;
}

void IfBehavior::Add(const IBehavior* item)
{
	mItems.Add(item);
}


void IfBehavior::AddElse(const IBehavior* item)
{
	mElseItems.Add(item);
}

void IfBehavior::Clear()
{
	SAFE_DELETE_COLLECTION(mItems);
	SAFE_DELETE_COLLECTION(mElseItems);
}

bool IfBehavior::LoadFromXmlNode(const pugi::xml_node& node)
{
	RETURN_FALSE_IF_FALSE(IPredicateBehavior::LoadFromXmlNode(node));

	for (const auto& child : node.children())
	{
		StringRef typeName = child.name();
		IBehavior* behavior = BehaviorFactory::Instance().SmartCreate(typeName);
		behavior->LoadFromXmlNode(child);
		behavior->Initialize();

		StringRef tagStr = child.attribute("Tag").value();
		if (tagStr.IsEmpty())
		{
			Add(behavior);
		}
		else
		{
			Log::AssertFormat(tagStr == "Else", "IfBehavior child tag should be \"Else\". Now is {}", tagStr.c_str());
			AddElse(behavior);
		}
	}

	return true;
}



MEDUSA_IMPLEMENT_BEHAVIOR(IfBehavior);
MEDUSA_END;