// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BehaviorConfig.h"
#include "Core/Pattern/Predicate/PredicateConfig.h"
#include "Core/Pattern/Behavior/BehaviorFactory.h"
#include "Core/Pattern/Predicate/PredicateFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


bool BehaviorConfig::LoadFromData(StringRef path, const MemoryByteData& data, uint format /*= 0*/)
{
	Unload();
	RETURN_FALSE_IF(data.IsNull());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", path.c_str(), result.description());
		return false;
	}

	FOR_EACH_COLLECTION_STL(i, doc.first_child().children())
	{
		pugi::xml_node child = *i;
		StringRef typeName = child.name();
		StringRef id = child.attribute("Id").value();
		if (id.IsEmpty())
		{
			id = typeName;
		}

#ifdef MEDUSA_SAFE_CHECK
		if (ContainsId(id))
		{
			Log::AssertFailedFormat("Duplicate id:{} in {}", id.c_str(), typeName.c_str());
		}
#endif

		IBehavior* behavior = BehaviorFactory::Instance().SmartCreate(typeName);
		behavior->LoadFromXmlNode(child);
		behavior->Initialize();
		if (id.EndWith("Behavior"))
		{
			Add(id, behavior);
		}
		else
		{
			Add(id + "Behavior", behavior);
		}
	}


	return true;
}


void BehaviorConfig::Unload()
{
	Clear();
}

IBehavior* BehaviorConfig::SmartCreate(StringRef name)
{
	IBehavior* behavior = TryGetObjectWithFailed(name, nullptr);
	if (behavior == nullptr)
	{
		behavior = TryGetObjectWithFailed(name + "Behavior", nullptr);
	}

	if (behavior == nullptr)
	{
		behavior = BehaviorFactory::Instance().SmartCreate(name);
	}

	return behavior;
}

MEDUSA_END;