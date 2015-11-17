// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SwitchBehavior.h"
#include "BehaviorFactory.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;


SwitchBehavior::~SwitchBehavior()
{
	FOR_EACH_COLLECTION(i, mItems)
	{
		List<const IBehavior*>* items = i->Value;
		SAFE_DELETE_COLLECTION(*items);
		delete items;
	}

	SAFE_DELETE_COLLECTION(mDefaultItems);
}


const IBehavior* SwitchBehavior::Behave(IBrainBody& brainBody, void* sender) const
{
	int result = Evaluate(sender);
	List<const IBehavior*>* items = mItems.TryGetValueWithFailed(result, nullptr);
	if (items != nullptr)
	{
		FOR_EACH_COLLECTION(i, *items)
		{
			const IBehavior* item = *i;
			const IBehavior* tempResult = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	else
	{
		RETURN_NULL_IF_EMPTY(mDefaultItems);
		FOR_EACH_COLLECTION(i, mDefaultItems)
		{
			const IBehavior* item = *i;
			const IBehavior* tempResult = item->Behave(brainBody, sender);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	return nullptr;
}

const IBehavior* SwitchBehavior::ReceiveEvent(IBrainBody& brainBody, void* sender, IEventArg& e) const
{
	int result = Evaluate(sender);
	List<const IBehavior*>* items = mItems.TryGetValueWithFailed(result, nullptr);
	if (items != nullptr)
	{
		FOR_EACH_COLLECTION(i, *items)
		{
			const IBehavior* item = *i;
			const IBehavior* tempResult = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}

	}
	else
	{
		RETURN_NULL_IF_EMPTY(mDefaultItems);
		FOR_EACH_COLLECTION(i, mDefaultItems)
		{
			const IBehavior* item = *i;
			const IBehavior* tempResult = item->ReceiveEvent(brainBody, sender, e);
			RETURN_SELF_IF_NOT_NULL(tempResult);
		}
	}
	return nullptr;
}

bool SwitchBehavior::LoadFromXmlNode(pugi::xml_node node)
{
	RETURN_FALSE_IF_FALSE(IPredicateBehavior::LoadFromXmlNode(node));

	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;

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

			List<const IBehavior*>* items = mItems.TryGetValueWithFailed(tag, nullptr);
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

MEDUSA_IMPLEMENT_RTTI(SwitchBehavior, IPredicateBehavior);

MEDUSA_END;