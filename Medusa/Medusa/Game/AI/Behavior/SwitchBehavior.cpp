// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SwitchBehavior.h"
#include "BehaviorFactory.h"
#include "Core/String/StringParser.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;


SwitchBehavior::~SwitchBehavior()
{
	for (auto i : mItems)
	{
		List<const IBehavior*>* items = i.Value;
		SAFE_DELETE_COLLECTION(*items);
		delete items;
	}

	SAFE_DELETE_COLLECTION(mDefaultItems);
}


const IBehavior* SwitchBehavior::Behave(IBrainBody& brainBody, void* sender) const
{
	int result = Evaluate(sender);
	List<const IBehavior*>* items = mItems.GetOptional(result, nullptr);
	if (items != nullptr)
	{
		for (auto item : *items)
		{
			const IBehavior* tempResult = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	else
	{
		RETURN_NULL_IF_EMPTY(mDefaultItems);
		for (auto item : mDefaultItems)
		{
			const IBehavior* tempResult = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	return nullptr;
}

const IBehavior* SwitchBehavior::ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e) const
{
	int result = Evaluate(sender);
	List<const IBehavior*>* items = mItems.GetOptional(result, nullptr);
	if (items != nullptr)
	{
		for (auto item : *items)
		{
			const IBehavior* tempResult = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}

	}
	else
	{
		RETURN_NULL_IF_EMPTY(mDefaultItems);
		for (auto item : mDefaultItems)
		{
			const IBehavior* tempResult = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	return nullptr;
}

bool SwitchBehavior::LoadFromXmlNode(const pugi::xml_node& node)
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
			//add default
			mDefaultItems.Add(behavior);
		}
		else
		{
			int tag = StringParser::StringTo<int>(tagStr);

			List<const IBehavior*>* items = mItems.GetOptional(tag, nullptr);
			if (items==nullptr)
			{
				items = new List< const IBehavior*>();
				mItems.Add(tag, items);
			}
			items->Add(behavior);
		}
	}

	return true;
}

MEDUSA_IMPLEMENT_BEHAVIOR(SwitchBehavior);
MEDUSA_END;